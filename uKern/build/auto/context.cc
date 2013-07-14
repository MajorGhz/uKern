// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "context.h"
#include "context_i.h"

#line 393 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

// --------------------------------------------------------------------------

#line 415 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

DEFINE_PER_CPU Per_cpu<Clock> Context::_clock(true);
#line 417 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
DEFINE_PER_CPU Per_cpu<Context *> Context::_kernel_ctxt;
#line 537 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


/** @name State manipulation */
//@{
//-
#line 676 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

//@}
//-
#line 701 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/** @name Lock counting
    These functions count the number of locks
    this context holds.  A context must not be deleted if its lock
    count is nonzero. */
//@{
//-
#line 922 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

// queue operations

// XXX for now, synchronize with global kernel lock
//-
#line 1663 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

//----------------------------------------------------------------------------

#line 2151 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"



// --------------------------------------------------------------------------


#line 927 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/**
 * Enqueue current() if ready to fix up ready-list invariant.
 */

inline void
Context::update_ready_list()
{
  assert_kdb (this == current());

  if ((state() & Thread_ready_mask) && sched()->left())
    Sched_context::rq.current().ready_enqueue(sched());
}

#line 1730 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"



inline void
Context::shutdown_drqs()
{ _drq_q.handle_requests(Drq_q::Drop); }

#line 499 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/** Destroy context.
 */

Context::~Context()
{}

#line 737 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

//@}

/**
 * Switch active timeslice of this Context.
 * @param next Sched_context to switch to
 */

void
Context::switch_sched(Sched_context *next, Sched_context::Ready_queue *queue)
{
  queue->switch_sched(sched(), next);
  set_sched(next);
}

#line 751 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/**
 * Select a different context for running and activate it.
 */

void
Context::schedule()
{
  auto guard = lock_guard(cpu_lock);
  assert (!Sched_context::rq.current().schedule_in_progress);

  CNT_SCHEDULE;

  // Ensure only the current thread calls schedule
  assert_kdb (this == current());

  Cpu_number current_cpu = Cpu_number::nil();
  Sched_context::Ready_queue *rq = 0;

  // Enqueue current thread into ready-list to schedule correctly
  update_ready_list();

  // Select a thread for scheduling.
  Context *next_to_run;

  do
    {
      // I may've been migrated during the switch_exec_locked in the while
      // statement below. So check out if I've to use a new ready queue.
        {
          Cpu_number new_cpu = access_once(&_cpu);
          if (new_cpu != current_cpu)
            {
              Mem::barrier();
              current_cpu = new_cpu;
              rq = &Sched_context::rq.current();
              if (rq->schedule_in_progress)
                return;
            }
        }

      for (;;)
	{
	  next_to_run = rq->next_to_run()->context();

	  // Ensure ready-list sanity
	  assert_kdb (next_to_run);

	  if (EXPECT_TRUE (next_to_run->state() & Thread_ready_mask))
	    break;

          rq->ready_dequeue(next_to_run->sched());

	  rq->schedule_in_progress = this;

	  cpu_lock.clear();
	  Proc::irq_chance();
	  cpu_lock.lock();

	  // check if we've been migrated meanwhile
	  if (EXPECT_FALSE(current_cpu != access_once(&_cpu)))
	    {
	      current_cpu = _cpu;
              Mem::barrier();
	      rq = &Sched_context::rq.current();
	      if (rq->schedule_in_progress)
		return;
	    }
	  else
	    rq->schedule_in_progress = 0;
	}
    }
  while (EXPECT_FALSE(schedule_switch_to_locked(next_to_run)));
}

#line 951 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


/**
 * \brief Activate a newly created thread.
 *
 * This function sets a new thread onto the ready list and switches to
 * the thread if it can preempt the currently running thread.
 */

bool
Context::activate()
{
  auto guard = lock_guard(cpu_lock);
  if (cpu() == current_cpu())
    {
      state_add_dirty(Thread_ready);
      if (Sched_context::rq.current().deblock(sched(), current()->sched(), true))
	{
	  current()->switch_to_locked(this);
	  return true;
	}
    }
  else
    remote_ready_enqueue();

  return false;
}

#line 1179 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


/**
 * Switch to a specific different execution context.
 *        If that context is currently locked, switch to its locker instead
 *        (except if current() is the locker)
 * @pre current() == this  &&  current() != t
 * @param t thread that shall be activated.
 * @param mode helping mode; we either help, don't help or leave the
 *             helping state unchanged
 */

bool  FIASCO_WARN_RESULT //L4_IPC_CODE
Context::switch_exec_locked(Context *t, enum Helping_mode mode)
{
  // Must be called with CPU lock held
  assert_kdb (t->cpu() != Cpu::invalid());
  assert_kdb (t->cpu() == current_cpu());
  assert_kdb (cpu() == current_cpu());
  assert_kdb (cpu_lock.test());
  assert_kdb (current() != t);
  assert_kdb (current() == this);
  assert_kdb (timeslice_timeout.cpu(cpu())->is_set()); // Coma check

  // only for logging
  Context *t_orig = t;
  (void)t_orig;

  // Time-slice lending: if t is locked, switch to its locker
  // instead, this is transitive
  t = handle_helping(t);

  if (t == this)
    return handle_drq();

  LOG_CONTEXT_SWITCH;
  CNT_CONTEXT_SWITCH;

  // Can only switch to ready threads!
  if (EXPECT_FALSE (!(t->state() & Thread_ready_mask)))
    {
      assert_kdb (state() & Thread_ready_mask);
      return false;
    }


  // Ensure kernel stack pointer is non-null if thread is ready
  assert_kdb (t->_kernel_sp);

  t->set_helper(mode);

  update_ready_list();
  assert_kdb (!(state() & Thread_ready_mask) || !sched()->left()
              || in_ready_list());

  switch_fpu(t);
  switch_cpu(t);

  return handle_drq();
}

#line 1368 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/**
 * \brief Forced dequeue from lock wait queue, or DRQ queue.
 */

void
Context::force_dequeue()
{
  Queue_item *const qi = queue_item();

  if (qi->queued())
    {
      // we're waiting for a lock or have a DRQ pending
      Queue *const q = qi->queue();
	{
	  auto guard = lock_guard(q->q_lock());
	  // check again, with the queue lock held.
	  // NOTE: we may be already removed from the queue on another CPU
	  if (qi->queued() && qi->queue())
	    {
	      // we must never be taken from one queue to another on a
	      // different CPU
	      assert_kdb(q == qi->queue());
	      // pull myself out of the queue, mark reason as invalidation
	      q->dequeue(qi, Queue_item::Invalid);
	    }
	}
    }
}

#line 1397 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/**
 * \brief Dequeue from lock and DRQ queues, abort pending DRQs
 */

void
Context::shutdown_queues()
{
  force_dequeue();
  shutdown_drqs();
}

#line 1429 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


/**
 * \brief Handle all pending DRQs.
 * \pre cpu_lock.test() (The CPU lock must be held).
 * \pre current() == this (only the currently running context is allowed to
 *      call this function).
 * \return true if re-scheduling is needed (ready queue has changed),
 *         false if not.
 */
//inline
bool
Context::handle_drq()
{
  assert_kdb (check_for_current_cpu());
  assert_kdb (cpu_lock.test());

  try_finish_migration();

  if (EXPECT_TRUE(!drq_pending()))
    return false;

  Mem::barrier();
  bool ret = _drq_q.handle_requests();
  state_del_dirty(Thread_drq_ready);

  //LOG_MSG_3VAL(this, "xdrq", state(), ret, cpu_lock.test());

  /*
   * When the context is marked as dead (Thread_dead) then we must not execute
   * any usual context code, however DRQ handlers may run.
   */
  if (state() & Thread_dead)
    {
      // so disable the context after handling all DRQs and flag a reschedule.
      state_del_dirty(Thread_ready_mask);
      return true;
    }

  return ret || !(state() & Thread_ready_mask);
}

#line 1488 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/**
 * \brief DRQ handler for state_change.
 *
 * This function basically wraps Context::state_change().
 */

unsigned
Context::handle_drq_state_change(Drq * /*src*/, Context *self, void * _rq)
{
  State_request *rq = reinterpret_cast<State_request*>(_rq);
  self->state_change_dirty(rq->del, rq->add);
  //LOG_MSG_3VAL(c, "dsta", c->state(), (Mword)src, (Mword)_rq);
  return false;
}

#line 1624 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


bool
Context::rcu_unblock(Rcu_item *i)
{
  assert_kdb(cpu_lock.test());
  Context *const c = static_cast<Context*>(i);
  c->state_change_dirty(~Thread_waiting, Thread_ready);
  Sched_context::rq.current().deblock(c->sched());
  return true;
}

#line 1640 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


void
Context::xcpu_tlb_flush(...)
{
  // This should always be optimized away
  assert(0);
}

#line 1689 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"



void
Context::remote_ready_enqueue()
{
  WARN("Context::remote_ready_enqueue(): in UP system !\n");
  kdb_ke("Fiasco BUG");
}

#line 1698 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


bool
Context::enqueue_drq(Drq *rq, Drq::Exec_mode /*exec*/)
{
  assert_kdb (cpu_lock.test());

  if (access_once(&_cpu) != current_cpu())
    {
      bool do_sched = _drq_q.execute_request(rq, Drq_q::No_drop, true);
      //LOG_MSG_3VAL(this, "drqX", access_once(&_cpu), current_cpu(), state());
      if (access_once(&_cpu) == current_cpu() && (state() & Thread_ready_mask))
        {
          Sched_context::rq.current().ready_enqueue(sched());
          return true;
        }
      return do_sched;
    }
  else
    { // LOG_MSG_3VAL(this, "adrq", state(), (Mword)current(), (Mword)rq);

      bool do_sched = _drq_q.execute_request(rq, Drq_q::No_drop, true);
      if (!in_ready_list() && (state() & Thread_ready_mask))
	{
	  Sched_context::rq.current().ready_enqueue(sched());
	  return true;
	}

      return do_sched;
    }
  return false;
}

#line 2158 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


unsigned
Context::Drq_log::print(int maxlen, char *buf) const
{
  static char const *const _types[] =
    { "send", "request", "reply", "done" };

  char const *t = "unk";
  if ((unsigned)type < sizeof(_types)/sizeof(_types[0]))
    t = _types[(unsigned)type];

  return snprintf(buf, maxlen, "%s(%s) rq=%p to ctxt=%lx/%p (func=%p, reply=%p) cpu=%u",
      t, wait ? "wait" : "no-wait", rq, Kobject_dbg::pointer_to_id(thread),
      thread, func, reply, cxx::int_value<Cpu_number>(target_cpu));
}

#line 2174 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

// context switch

unsigned
Tb_entry_ctx_sw::print(int maxlen, char *buf) const
{
  char symstr[24];
  int max = maxlen;

  Context *sctx = 0;
  Mword sctxid = ~0UL;
  Mword dst;
  Mword dst_orig;

  sctx = from_sched->context();
  sctxid = Kobject_dbg::pointer_to_id(sctx);

  dst = Kobject_dbg::pointer_to_id(this->dst);
  dst_orig = Kobject_dbg::pointer_to_id(this->dst_orig);

  snprintf(symstr, sizeof(symstr), L4_PTR_FMT, kernel_ip); // Jdb_symbol::...

  if (sctx != ctx())
    maxlen -= snprintf(buf, maxlen, "(%lx)", sctxid);

  maxlen -= snprintf(buf, maxlen, " ==> %lx ", dst);

  if (dst != dst_orig || lock_cnt)
    maxlen -= snprintf(buf, maxlen, "(");

  if (dst != dst_orig)
    maxlen -= snprintf(buf, maxlen, "want %lx", dst_orig);

  if (dst != dst_orig && lock_cnt)
    maxlen -= snprintf(buf, maxlen, " ");

  if (lock_cnt)
    maxlen -= snprintf(buf, maxlen, "lck %ld", lock_cnt);

  if (dst != dst_orig || lock_cnt)
    maxlen -= snprintf(buf, maxlen, ") ");

  maxlen -= snprintf(buf, maxlen, " krnl %s", symstr);

  return max - maxlen;
}
