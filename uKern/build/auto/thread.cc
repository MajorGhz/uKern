// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "thread.h"
#include "thread_i.h"

#line 190 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"

FIASCO_DEFINE_KOBJ(Thread);
#line 192 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"

DEFINE_PER_CPU Per_cpu<unsigned long> Thread::nested_trap_recover;
#line 339 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"

Del_irq_chip Del_irq_chip::chip;
#line 819 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"




//---------------------------------------------------------------------------


#line 194 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"



Thread::Dbg_stack::Dbg_stack()
{
  stack_top = Kmem_alloc::allocator()->unaligned_alloc(Stack_size); 
  if (stack_top)
    stack_top = (char *)stack_top + Stack_size;
  //printf("JDB STACK start= %p - %p\n", (char *)stack_top - Stack_size, (char *)stack_top);
}

#line 224 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"


bool
Thread::bind(Task *t, User<Utcb>::Ptr utcb)
{
  // _utcb == 0 for all kernel threads
  Space::Ku_mem const *u = t->find_ku_mem(utcb, sizeof(Utcb));

  // kernel thread?
  if (EXPECT_FALSE(utcb && !u))
    return false;

  auto guard = lock_guard(_space.lock());
  if (_space.space() != Kernel_task::kernel_task())
    return false;

  _space.space(t);
  t->inc_ref();

  if (u)
    {
      _utcb.set(utcb, u->kern_addr(utcb));
      arch_setup_utcb_ptr();
    }

  return true;
}

#line 304 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"


/** Destructor.  Reestablish the Context constructor's precondition.
    @pre current() == thread_lock()->lock_owner()
         && state() == Thread_dead
    @pre lock_cnt() == 0
    @post (_kernel_sp == 0)  &&  (* (stack end) == 0)  &&  !exists()
 */

Thread::~Thread()		// To be called in locked state.
{

  unsigned long *init_sp = reinterpret_cast<unsigned long*>
    (reinterpret_cast<unsigned long>(this) + Size - sizeof(Entry_frame));


  _kernel_sp = 0;
  *--init_sp = 0;
  Fpu_alloc::free_state(fpu_state());
  _state = Thread_invalid;
}

#line 365 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"


void
Thread::register_delete_irq(Irq_base *irq)
{
  irq->unbind();
  Del_irq_chip::chip.bind(irq, (Mword)this);
  _del_observer = irq;
}

#line 374 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"


void
Thread::remove_delete_irq()
{
  if (!_del_observer)
    return;

  Irq_base *tmp = _del_observer;
  _del_observer = 0;
  tmp->unbind();
}

#line 448 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"



void
Thread::halt()
{
  // Cancel must be cleared on all kernel entry paths. See slowtraps for
  // why we delay doing it until here.
  state_del(Thread_cancel);

  // we haven't been re-initialized (cancel was not set) -- so sleep
  if (state_change_safely(~Thread_ready, Thread_cancel | Thread_dead))
    while (! (state() & Thread_ready))
      schedule();
}

#line 463 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"


void
Thread::halt_current()
{
  for (;;)
    {
      current_thread()->halt();
      kdb_ke("Thread not halted");
    }
}

#line 490 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"


void
Thread::leave_and_kill_myself()
{
  current_thread()->do_kill();
#ifdef CONFIG_JDB
  WARN("dead thread scheduled: %lx\n", current_thread()->dbg_id());
#endif
  kdb_ke("DEAD SCHED");
}

#line 501 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"


unsigned
Thread::handle_kill_helper(Drq *src, Context *, void *)
{
  delete nonull_static_cast<Thread*>(src->context());
  return Drq::No_answer | Drq::Need_resched;
}

#line 509 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"



bool
Thread::do_kill()
{
  auto guard = lock_guard(thread_lock());

  if (state() == Thread_invalid)
    return false;

  //
  // Kill this thread
  //

  // But first prevent it from being woken up by asynchronous events

  {
    auto guard = lock_guard(cpu_lock);

    // if IPC timeout active, reset it
    if (_timeout)
      _timeout->reset();

    // Switch to time-sharing mode
    set_mode(Sched_mode(0));

    Sched_context::Ready_queue &rq = Sched_context::rq.current();

    // Switch to time-sharing scheduling context
    if (sched() != sched_context())
      switch_sched(sched_context(), &rq);

    if (!rq.current_sched() || rq.current_sched()->context() == this)
      rq.set_current_sched(current()->sched());
  }

  // if other threads want to send me IPC messages, abort these
  // operations
  {
    auto guard = lock_guard(cpu_lock);
    while (Sender *s = Sender::cast(sender_list()->first()))
      {
	s->sender_dequeue(sender_list());
	vcpu_update_state();
	s->ipc_receiver_aborted();
	Proc::preemption_point();
      }
  }

  // if engaged in IPC operation, stop it
  if (in_sender_list())
    {
      while (Locked_prio_list *q = wait_queue())
	{
	  auto g = lock_guard(q->lock());
	  if (wait_queue() == q)
	    {
	      sender_dequeue(q);
	      set_wait_queue(0);
	      break;
	    }
	}
    }

  Context::do_kill();

  vcpu_update_state();

  unbind();
  vcpu_set_user_space(0);

  cpu_lock.lock();

  state_change_dirty(0, Thread_dead);

  // dequeue from system queues
  Sched_context::rq.current().ready_dequeue(sched());

  if (_del_observer)
    {
      _del_observer->unbind();
      _del_observer = 0;
    }

  if (dec_ref())
    while (1)
      {
	state_del_dirty(Thread_ready_mask);
	schedule();
	WARN("woken up dead thread %lx\n", dbg_id());
	kdb_ke("X");
      }

  rcu_wait();

  state_del_dirty(Thread_ready_mask);

  Sched_context::rq.current().ready_dequeue(sched());

  kernel_context_drq(handle_kill_helper, 0);
  kdb_ke("Im dead");
  return true;
}

#line 613 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"


unsigned
Thread::handle_remote_kill(Drq *, Context *self, void *)
{
  Thread *c = nonull_static_cast<Thread*>(self);
  c->state_add_dirty(Thread_cancel | Thread_ready);
  c->_exc_cont.restore(c->regs());
  c->do_trigger_exception(c->regs(), (void*)&Thread::leave_and_kill_myself);
  return 0;
}

#line 624 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"



bool
Thread::kill()
{
  auto guard = lock_guard(cpu_lock);
  inc_ref();


  if (cpu() == current_cpu())
    {
      state_add_dirty(Thread_cancel | Thread_ready);
      Sched_context::rq.current().deblock(sched());
      _exc_cont.restore(regs()); // overwrite an already triggered exception
      do_trigger_exception(regs(), (void*)&Thread::leave_and_kill_myself);
//          current()->switch_exec (this, Helping);
      return true;
    }

  drq(Thread::handle_remote_kill, 0, 0, Drq::Any_ctxt);

  return true;
}

#line 648 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"



void
Thread::set_sched_params(L4_sched_param const *p)
{
  Sched_context *sc = sched_context();
  // FIXME: do not know how to figure this out currently, however this
  // seems to be just an optimization
#if 0
  bool const change = prio != sc->prio()
                   || quantum != sc->quantum();
  bool const ready_queued = in_ready_list();

  if (!change && (ready_queued || this == current()))
    return;
#endif

  Sched_context::Ready_queue &rq = Sched_context::rq.cpu(cpu());
  rq.ready_dequeue(sched());

  sc->set(p);
  sc->replenish();

  if (sc == rq.current_sched())
    rq.set_current_sched(sc);

  if (state() & Thread_ready_mask) // maybe we could ommit enqueueing current
    rq.ready_enqueue(sched());
}

#line 678 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"


long
Thread::control(Thread_ptr const &pager, Thread_ptr const &exc_handler)
{
  if (pager.is_valid())
    _pager = pager;

  if (exc_handler.is_valid())
    _exc_handler = exc_handler;

  return 0;
}

#line 737 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"


unsigned
Thread::handle_migration_helper(Drq *rq, Context *, void *p)
{
  Migration *inf = reinterpret_cast<Migration *>(p);
  Thread *v = static_cast<Thread*>(context_of(rq));
  Cpu_number target_cpu = access_once(&inf->cpu);
  v->migrate_away(inf, false);
  v->migrate_to(target_cpu, false);
  return Drq::Need_resched | Drq::No_answer;
}

#line 772 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"


bool
Thread::do_migration()
{
  Migration *inf = start_migration();

  if ((Mword)inf & 3)
    return (Mword)inf & 1; // already migrated, nothing to do

  spill_fpu_if_owner();

  if (current() == this)
    {
      assert_kdb (current_cpu() == cpu());
      kernel_context_drq(handle_migration_helper, inf);
    }
  else
    {
      Cpu_number target_cpu = access_once(&inf->cpu);
      migrate_away(inf, false);
      migrate_to(target_cpu, false);
    }
  return false; // we already are chosen by the scheduler...
}

#line 797 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"

bool
Thread::initiate_migration()
{
  assert (current() != this);
  Migration *inf = start_migration();

  if ((Mword)inf & 3)
    return (Mword)inf & 1;

  spill_fpu_if_owner();

  Cpu_number target_cpu = access_once(&inf->cpu);
  migrate_away(inf, false);
  migrate_to(target_cpu, false);
  return false;
}

#line 814 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"


void
Thread::finish_migration()
{ enqueue_timeout_again(); }

#line 1008 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"


void
Thread::migrate(Migration *info)
{
  assert_kdb (cpu_lock.test());

  LOG_TRACE("Thread migration", "mig", this, Migration_log,
      l->state = state(false);
      l->src_cpu = cpu();
      l->target_cpu = info->cpu;
      l->user_ip = regs()->ip();
  );

  _migration = info;
  current()->schedule_if(do_migration());
}

#line 1282 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"


unsigned
Thread::Migration_log::print(int maxlen, char *buf) const
{
  return snprintf(buf, maxlen, "migrate from %u to %u (state=%lx user ip=%lx)",
      cxx::int_value<Cpu_number>(src_cpu),
      cxx::int_value<Cpu_number>(target_cpu), state, user_ip);
}
