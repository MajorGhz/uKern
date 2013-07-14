// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef thread_lock_h
#define thread_lock_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_lock.cpp"

#include "member_offs.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_lock.cpp"
#include "context.h"		// Switch_hint
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_lock.cpp"
#include "panic.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_lock.cpp"
#include "switch_lock.h"

//
// INTERFACE definition follows 
//

#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_lock.cpp"

enum Switch_hint
{
  SWITCH_ACTIVATE_HIGHER = 0,	// Activate thread with higher priority
  SWITCH_ACTIVATE_LOCKEE,	// Activate thread that was locked
};
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_lock.cpp"


/** Thread lock.
    This lock uses the basic priority-inheritance mechanism (Switch_lock)
    and extends it in two ways: First, it has a hinting mechanism that
    allows a locker to specify whether the clear() operation should
    switch to the thread that was locked.  Second, it maintains the current
    locker for Context; this locker automatically gets CPU time allocated
    to the locked thread (Context's ``donatee''); 
    Context::switch_exec() uses that hint.
    To make clear, which stuff in the TCB the lock not protects:
    -the thread state
    -queues
    -the raw kernelstack
    The rest is protected with this lock, this includes the
    kernelstackpointer (kernel_sp).
 */
class Thread_lock : private Switch_lock
{
  MEMBER_OFFSET();

private:
  typedef Switch_lock Lock;

public:
  using Lock::Invalid;
  using Lock::Locked;
  using Lock::Not_locked;

  using Lock::Lock_context;
  
  using Lock::test;
  using Lock::lock_owner;
  using Lock::Status;

  /*
   * Can use the Switch_lock version, because we assume the context
   * is invalid during switch_dirty and we do not need to consider it
   * for scheduling any more.
   */
  using Lock::clear_no_switch_dirty;
  using Lock::switch_dirty;

private:
  Switch_hint _switch_hint;

public:  
#line 82 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_lock.cpp"
  /** Set switch hint.
      @param hint a hint to the clear() function
   */
  
  inline void
  set_switch_hint(Switch_hint const hint);
  
#line 92 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_lock.cpp"
  /** Lock a context.
      @return true if we owned the lock already.  false otherwise.
   */
  
  Thread_lock::Status
  test_and_set();
  
#line 130 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_lock.cpp"
  /** Lock a thread.
      If the lock is occupied, enqueue in list of helpers and lend CPU
      to current lock owner until we are the lock owner.
   */
  
  inline Thread_lock::Status
  lock();
  
#line 141 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_lock.cpp"
  /** Lock a thread.
      If the lock is occupied, enqueue in list of helpers and lend CPU 
      to current lock owner until we are the lock owner.
      @pre caller holds cpu lock
   */
  
  inline Thread_lock::Status
  lock_dirty();
  
#line 154 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_lock.cpp"
  /** Free the lock.
      First return the CPU to helper or next lock owner, whoever has the higher
      priority, given that thread's priority is higher that ours.
      Finally, switch to locked thread if that thread has a higher priority,
      and/or the switch hint says we should.
   */
  
  void
  clear();
  
#line 206 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_lock.cpp"
  inline void
  set(Status s);
  
#line 213 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_lock.cpp"
  /** Free the lock.
      First return the CPU to helper or next lock owner, whoever has the higher 
      priority, given that thread's priority is higher that ours.
      Finally, switch to locked thread if that thread has a higher priority,
      and/or the switch hint says we should.
      Assumes caller hold cpu lock
   */
  
  void
  clear_dirty();
  
#line 261 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_lock.cpp"
  /** Free the lock.
      First return the CPU to helper or next lock owner, whoever has the higher 
      priority, given that thread's priority is higher that ours.
      Finally, switch to locked thread if that thread has a higher priority,
      and/or the switch hint says we should.
      Assumes caller hold cpu lock
   */
  
  inline void
  clear_dirty_dont_switch();

private:  
#line 68 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_lock.cpp"
  /** Context this thread lock belongs to.
      @return context locked by this thread lock
   */
  
  inline Context *
  context() const;
  
#line 103 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_lock.cpp"
  /** Lock a context.
      @return true if we owned the lock already.  false otherwise.
      @pre caller holds cpu lock
   */
  
  inline Thread_lock::Status
  test_and_set_dirty();
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 61 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_lock.cpp"

#include "globals.h"
#line 64 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_lock.cpp"
#include "cpu_lock.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 81 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_lock.cpp"

/** Set switch hint.
    @param hint a hint to the clear() function
 */

inline void
Thread_lock::set_switch_hint(Switch_hint const hint)
{
  _switch_hint = hint;
}

#line 128 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_lock.cpp"


/** Lock a thread.
    If the lock is occupied, enqueue in list of helpers and lend CPU
    to current lock owner until we are the lock owner.
 */

inline Thread_lock::Status
Thread_lock::lock()
{
  return test_and_set();
}

#line 67 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_lock.cpp"

/** Context this thread lock belongs to.
    @return context locked by this thread lock
 */

inline Context *
Thread_lock::context() const
{
  // We could have saved our context in our constructor, but computing
  // it this way is easier and saves space.  We can do this as we know
  // that thread_locks are always embedded in their corresponding
  // context.
  return context_of (this);
}

#line 102 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_lock.cpp"

/** Lock a context.
    @return true if we owned the lock already.  false otherwise.
    @pre caller holds cpu lock
 */

inline Thread_lock::Status
Thread_lock::test_and_set_dirty()
{
  assert(cpu_lock.test());

  switch (Status r = Lock::test_and_set ())
    {
    case Invalid:
    case Locked:
      return r;
    case Not_locked:
      break;
    }

  context()->set_donatee (current()); // current get time of context

  set_switch_hint (SWITCH_ACTIVATE_HIGHER);

  return Not_locked;
}

#line 140 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_lock.cpp"

/** Lock a thread.
    If the lock is occupied, enqueue in list of helpers and lend CPU 
    to current lock owner until we are the lock owner.
    @pre caller holds cpu lock
 */

inline Thread_lock::Status
Thread_lock::lock_dirty()
{
  // removed assertion, because we do lazy locking
  return test_and_set_dirty();
}

#line 204 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_lock.cpp"


inline void
Thread_lock::set(Status s)
{
  if (s == Not_locked)
    clear();
}

#line 260 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_lock.cpp"

/** Free the lock.
    First return the CPU to helper or next lock owner, whoever has the higher 
    priority, given that thread's priority is higher that ours.
    Finally, switch to locked thread if that thread has a higher priority,
    and/or the switch hint says we should.
    Assumes caller hold cpu lock
 */

inline void
Thread_lock::clear_dirty_dont_switch()
{
  assert(cpu_lock.test());

  if(EXPECT_TRUE(!test()))
    return;

  Lock::clear_dirty();
  context()->set_donatee(lock_owner());

  assert(cpu_lock.test());
}

#endif // thread_lock_h
