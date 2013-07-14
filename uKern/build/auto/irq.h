// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef irq_h
#define irq_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"

#include "ipc_sender.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
#include "irq_chip.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
#include "kobject_helper.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
#include "member_offs.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
#include "sender.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
#include "context.h"

//
// INTERFACE definition follows 
//

#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"

class Ram_quota;
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
class Receiver;
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"


/** Hardware interrupts.  This class encapsulates handware IRQs.  Also,
    it provides a registry that ensures that only one receiver can sign up
    to receive interrupt IPC messages.
 */
class Irq : public Irq_base, public Kobject
{
  MEMBER_OFFSET();
  FIASCO_DECLARE_KOBJ();

private:
  typedef Slab_cache Allocator;

public:
  enum Op
  {
    Op_eoi_1      = 0,
    Op_attach     = 1,
    Op_trigger    = 2,
    Op_chain      = 3,
    Op_eoi_2      = 4,
  };

private:
  Irq(Irq&);

protected:
  Ram_quota *_q;
  Context::Drq _drq;

public:  
#line 665 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  inline void *
  operator new(size_t, void *p);
  
#line 670 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  void
  operator delete(void *_l);
  
#line 682 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  template<typename T> static inline T*
  allocate(Ram_quota *q);
  
#line 694 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  explicit inline Irq(Ram_quota *q = 0);
  
#line 697 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  void
  destroy(Kobject ***rl);

private:  
#line 660 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  static Irq::Allocator *
  allocator();
};
#line 43 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"


/**
 * IRQ Kobject to send IPC messages to a receiving thread.
 */
class Irq_sender
: public Kobject_h<Irq_sender, Irq>,
  public Ipc_sender<Irq_sender>
{
public:
  Mword kobject_size() const { return sizeof(*this); }

private:
  Irq_sender(Irq_sender &);

protected:
  Smword _queued;
  Receiver *_irq_thread;

private:
  Mword _irq_id;

public:  
#line 309 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  /** Bind a receiver to this device interrupt.
      @param t the receiver that wants to receive IPC messages for this IRQ
      @return true if the binding could be established
   */
  
  inline bool
  alloc(Receiver *t);
  
#line 334 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  Receiver *
  owner() const;
  
#line 337 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  /** Release an device interrupt.
      @param t the receiver that ownes the IRQ
      @return true if t really was the owner of the IRQ and operation was 
              successful
   */
  
  bool
  free(Receiver *t);
  
#line 369 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  explicit Irq_sender(Ram_quota *q = 0);
  
#line 376 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  void
  switch_mode(bool is_edge_triggered);
  
#line 383 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  void
  destroy(Kobject ***rl);
  
#line 416 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  inline int
  queued();
  
#line 423 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  /**
   * Predicate used to figure out if the sender shall be enqueued
   * for sending a second message after sending the first.
   */
  
  inline bool
  requeue_sender();
  
#line 432 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  /**
   * Predicate used to figure out if the sender shall be deqeued after
   * sending the request.
   */
  
  inline bool
  dequeue_sender();
  
#line 442 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  inline Syscall_frame *
  transfer_msg(Receiver *recv);
  
#line 456 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  void
  modify_label(Mword const *todo, int cnt);
  
#line 513 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  inline void
  _hit_level_irq(Upstream_irq const *ui);
  
#line 537 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  inline void
  _hit_edge_irq(Upstream_irq const *ui);
  
#line 611 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  L4_msg_tag
  kinvoke(L4_obj_ref, L4_fpage::Rights /*rights*/, Syscall_frame *f,
                      Utcb const *utcb, Utcb *);
  
#line 648 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  Mword
  obj_id() const;

private:  
#line 394 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  /** Consume one interrupt.
      @return number of IRQs that are still pending.
   */
  
  inline Smword
  consume();
  
#line 476 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  static unsigned
  handle_remote_hit(Context::Drq *, Context *, void *arg);
  
#line 486 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  inline Smword
  queue();
  
#line 498 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  inline void
  count_and_send(Smword queued);
  
#line 532 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  static void
  hit_level_irq(Irq_base *i, Upstream_irq const *ui);
  
#line 565 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  static void
  hit_edge_irq(Irq_base *i, Upstream_irq const *ui);
  
#line 571 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  L4_msg_tag
  sys_attach(L4_msg_tag const &tag, Utcb const *utcb, Syscall_frame * /*f*/,
                  Obj_space *o_space);
};
#line 65 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"


/**
 * IRQ Kobject to broadcast IRQs to multiple other IRQ objects.
 *
 * This is useful for PCI shared IRQs.
 */
class Irq_muxer : public Kobject_h<Irq_muxer, Irq>, private Irq_chip
{
public:
  int set_mode(Mword, Irq_chip::Mode) { return 0; }
  bool is_edge_triggered(Mword) const { return false; }
  void switch_mode(bool)
  {
    // the irq object is assumed to be always handled as
    // level triggered
  }

  void set_cpu(Mword, Cpu_number)
  {
    // don't know what to do here, may be multiple targets on different
    // CPUs!
  }

  void ack(Mword) {}

  char const *chip_type() const { return "Bcast"; }

private:
  Smword _mask_cnt;

public:  
#line 135 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  void
  unmask(Mword);
  
#line 149 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  void
  mask(Mword);
  
#line 163 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  void
  unbind(Irq_base *irq);
  
#line 180 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  void
  mask_and_ack(Mword);
  
#line 185 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  inline void
  handle(Upstream_irq const *ui);
  
#line 219 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  explicit Irq_muxer(Ram_quota *q = 0);
  
#line 226 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  void
  destroy(Kobject ***rl);
  
#line 277 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  L4_msg_tag
  kinvoke(L4_obj_ref, L4_fpage::Rights /*rights*/, Syscall_frame *f,
                     Utcb const *utcb, Utcb *);

private:  
#line 235 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
  L4_msg_tag
  sys_attach(L4_msg_tag const &tag, Utcb const *utcb, Syscall_frame * /*f*/,
                  Obj_space *o_space);
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 101 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
#include "atomic.h"
#line 103 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
#include "cpu_lock.h"
#line 109 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"
#include "lock_guard.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 663 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"


inline void *
Irq::operator new(size_t, void *p)
{ return p; }

#line 679 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"

 

template<typename T> inline T*
Irq::allocate(Ram_quota *q)
{
  void *nq =allocator()->q_alloc(q);
  if (nq)
    return new (nq) T(q);

  return 0;
}

#line 691 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"



inline Irq::Irq(Ram_quota *q) : _q(q) {}

#line 306 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"



/** Bind a receiver to this device interrupt.
    @param t the receiver that wants to receive IPC messages for this IRQ
    @return true if the binding could be established
 */

inline bool
Irq_sender::alloc(Receiver *t)
{
  bool ret = mp_cas(&_irq_thread, reinterpret_cast<Receiver*>(0), t);

  if (ret)
    {
      if (EXPECT_TRUE(t != 0))
	{
          t->inc_ref();
	  _chip->set_cpu(pin(), t->cpu());
	}

      _queued = 0;
    }

  return ret;
}

#line 414 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"


inline int
Irq_sender::queued()
{
  return _queued;
}

#line 392 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"


/** Consume one interrupt.
    @return number of IRQs that are still pending.
 */

inline Smword
Irq_sender::consume()
{
  Smword old;

  do
    {
      old = _queued;
    }
  while (!mp_cas (&_queued, old, old - 1));

  if (old == 2 && hit_func == &hit_edge_irq)
    unmask();

  return old - 1;
}

#line 421 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"


/**
 * Predicate used to figure out if the sender shall be enqueued
 * for sending a second message after sending the first.
 */

inline bool
Irq_sender::requeue_sender()
{ return consume() > 0; }

#line 431 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"

/**
 * Predicate used to figure out if the sender shall be deqeued after
 * sending the request.
 */

inline bool
Irq_sender::dequeue_sender()
{ return consume() < 1; }

#line 440 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"


inline Syscall_frame *
Irq_sender::transfer_msg(Receiver *recv)
{
  Syscall_frame* dst_regs = recv->rcv_regs();

  // set ipc return value: OK
  dst_regs->tag(L4_msg_tag(0));

  // set ipc source thread id
  dst_regs->from(_irq_id);

  return dst_regs;
}

#line 495 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"



inline void
Irq_sender::count_and_send(Smword queued)
{
  if (EXPECT_TRUE (queued == 0) && EXPECT_TRUE(_irq_thread != 0))	// increase hit counter
    {
      if (EXPECT_FALSE(_irq_thread->cpu() != current_cpu()))
	_irq_thread->drq(&_drq, handle_remote_hit, this, 0,
	                 Context::Drq::Target_ctxt, Context::Drq::No_wait);
      else
	send_msg(_irq_thread);
    }
}

#line 484 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"


inline Smword
Irq_sender::queue()
{
  Smword old;
  do
    old = _queued;
  while (!mp_cas(&_queued, old, old + 1));
  return old;
}

#line 510 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"



inline void
Irq_sender::_hit_level_irq(Upstream_irq const *ui)
{
  // We're entered holding the kernel lock, which also means irqs are
  // disabled on this CPU (XXX always correct?).  We never enable irqs
  // in this stack frame (except maybe in a nonnested invocation of
  // switch_exec() -> switchin_context()) -- they will be re-enabled
  // once we return from it (iret in entry.S:all_irqs) or we switch to
  // a different thread.

  // LOG_MSG_3VAL(current(), "IRQ", dbg_id(), 0, _queued);

  assert (cpu_lock.test());
  mask_and_ack();
  ui->ack();
  count_and_send(queue());
}

#line 535 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"


inline void
Irq_sender::_hit_edge_irq(Upstream_irq const *ui)
{
  // We're entered holding the kernel lock, which also means irqs are
  // disabled on this CPU (XXX always correct?).  We never enable irqs
  // in this stack frame (except maybe in a nonnested invocation of
  // switch_exec() -> switchin_context()) -- they will be re-enabled
  // once we return from it (iret in entry.S:all_irqs) or we switch to
  // a different thread.

  // LOG_MSG_3VAL(current(), "IRQ", dbg_id(), 0, _queued);

  assert (cpu_lock.test());
  Smword q = queue();

  // if we get a second edge triggered IRQ before the first is
  // handled we can mask the IRQ.  The consume function will
  // unmask the IRQ when the last IRQ is dequeued.
  if (!q)
    ack();
  else
    mask_and_ack();

  ui->ack();
  count_and_send(q);
}

#line 183 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"


inline void
Irq_muxer::handle(Upstream_irq const *ui)
{
  assert (cpu_lock.test());
  Irq_base::mask_and_ack();
  ui->ack();

  if (EXPECT_FALSE (!Irq_base::_next))
    return;

  int irqs = 0;
  for (Irq_base *n = Irq_base::_next; n;)
    {
      ++irqs;
      n->__mask();
      n = n->Irq_base::_next;
    }

    {
      Smword old;
      do
	old = _mask_cnt;
      while (!mp_cas(&_mask_cnt, old, old + irqs));
    }

  for (Irq_base *n = Irq_base::_next; n;)
    {
      Irq *i = nonull_static_cast<Irq*>(n);
      i->hit(0);
      n = i->Irq_base::_next;
    }
}

#endif // irq_h
