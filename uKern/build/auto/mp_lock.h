// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef mp_lock_h
#define mp_lock_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mp_lock.cpp"

#include "queue.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mp_lock.cpp"

class Mp_lock
{
public:
  enum Status { Not_locked, Locked, Invalid };

private:
  /** queue of blocked threads */
  Queue _q;

public:  
#line 70 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mp_lock.cpp"
  //#include "logdefs.h"
  
  
  
  inline Mp_lock::Status
  test_and_set();
  
#line 78 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mp_lock.cpp"
  inline Mp_lock::Status
  lock();
  
#line 83 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mp_lock.cpp"
  inline void
  clear();
  
#line 111 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mp_lock.cpp"
  inline void
  wait_free();
  
#line 142 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mp_lock.cpp"
  inline bool
  test() const;
  
#line 148 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mp_lock.cpp"
  inline void
  set(Status s);
  
#line 156 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mp_lock.cpp"
  void
  invalidate();
  
#line 180 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mp_lock.cpp"
  inline bool
  invalid() const;
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mp_lock.cpp"

#include "context.h"
#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mp_lock.cpp"
#include "cpu_lock.h"
#line 21 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mp_lock.cpp"
#include "globals.h"
#line 22 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mp_lock.cpp"
#include "kdb_ke.h"
#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mp_lock.cpp"
#include "lock_guard.h"
#line 24 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mp_lock.cpp"
#include "thread_state.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 25 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mp_lock.cpp"
//#include "logdefs.h"



inline Mp_lock::Status
Mp_lock::test_and_set()
{
  //assert_kdb (cpu_lock.test());

  Context *const c = current();

  auto g = lock_guard(cpu_lock);

    {
      auto guard = lock_guard(_q.q_lock());
      if (EXPECT_FALSE(_q.invalid()))
	return Invalid;

      if (!_q.blocked())
	{
	  // lock was free, take it
	  _q.block();
	  return Not_locked;
	}

      _q.enqueue(c->queue_item());
    }
  // LOG_MSG_3VAL(c, "block", (Mword)this, current_cpu(), *((Mword*)this));
  assert_kdb (!(c->state() & Thread_drq_ready));
  while (1)
    {
      c->state_change_dirty(~Thread_ready, Thread_waiting);
      c->schedule();

      if (!c->queue_item()->queued())
	break;
    }

  c->state_del_dirty(Thread_waiting);

  // LOG_MSG_3VAL(c, "woke", (Mword)this, current_cpu(), 0);

  switch (c->queue_item()->status())
    {
    case Queue_item::Ok:      return Not_locked;
    case Queue_item::Invalid: return Invalid;
    case Queue_item::Retry:   assert_kdb (false);
    }

  return Invalid;
}

#line 76 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mp_lock.cpp"


inline Mp_lock::Status
Mp_lock::lock()
{ return test_and_set(); }

#line 81 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mp_lock.cpp"



inline void
Mp_lock::clear()
{
  //assert_kdb (cpu_lock.test());

  Queue_item *f;

    {
      auto guard = lock_guard(_q.q_lock());
      //LOG_MSG_3VAL(current(), "clear", (Mword)this, current_cpu(), *((Mword*)this));
      assert_kdb (_q.blocked());

      f = _q.first();
      if (!f)
	{
	  _q.unblock();
	  return;
	}

      _q.dequeue(f, Queue_item::Ok);
    }
  // LOG_MSG_3VAL(current(), "wake", Mword(context_of(f)), (Mword)this, current_cpu());
  assert_kdb (current()->state() & Thread_ready_mask);
  context_of(f)->activate();
}

#line 109 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mp_lock.cpp"


inline void
Mp_lock::wait_free()
{

  Context *const c = current();

  auto g = lock_guard(cpu_lock);

    {
      auto guard = lock_guard(_q.q_lock());
      assert_kdb (invalid());

      if (!_q.blocked())
	return;

      _q.enqueue(c->queue_item());
    }

  while (1)
    {
      c->state_change_dirty(~Thread_ready, Thread_waiting);
      c->schedule();

      if (!c->queue_item()->queued())
	break;
    }

  c->state_del_dirty(Thread_waiting);
}

#line 140 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mp_lock.cpp"


inline bool
Mp_lock::test() const
{ return _q.blocked(); }

#line 145 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mp_lock.cpp"



inline void
Mp_lock::set(Status s)
{
  if (s == Not_locked)
    clear();
}

#line 178 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mp_lock.cpp"


inline bool
Mp_lock::invalid() const
{ return _q.invalid(); }

#endif // mp_lock_h
