// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "thread_lock.h"
#include "thread_lock_i.h"


#line 91 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_lock.cpp"

/** Lock a context.
    @return true if we owned the lock already.  false otherwise.
 */

Thread_lock::Status
Thread_lock::test_and_set()
{
  auto guard = lock_guard(cpu_lock);
  return test_and_set_dirty();
}

#line 153 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_lock.cpp"

/** Free the lock.
    First return the CPU to helper or next lock owner, whoever has the higher
    priority, given that thread's priority is higher that ours.
    Finally, switch to locked thread if that thread has a higher priority,
    and/or the switch hint says we should.
 */

void
Thread_lock::clear()
{
  Switch_hint hint = _switch_hint;	// Save hint before unlocking

  auto guard = lock_guard(cpu_lock);

  // Passing on the thread lock implies both passing _switch_lock
  // and setting context()'s donatee to the new owner.  This must be
  // accomplished atomically.  There are two cases to consider:
  // 1. _switch_lock.clear() does not switch to the new owner.
  // 2. _switch_lock.clear() switches to the new owner.
  // To cope with both cases, we set the owner both here (*) and in
  // Thread_lock::test_and_set().  The assignment that is executed
  // first is always atomic with _switch_lock.clear().  The
  // assignment that comes second is redundant.
  // Note: Our assignment (*) might occur at a time when there is no
  // lock owner or even when the context() has been killed.
  // Fortunately, it works anyway because contexts live in
  // type-stable memory.
  Lock::clear();
  context()->set_donatee(lock_owner());

  // We had locked ourselves, remain current
  if (context() == current())
    return;

  // Unlocked thread not ready, remain current
  if (!(context()->state() & Thread_ready))
    return;

  // Switch to lockee's execution context if the switch hint says so
  if (hint == SWITCH_ACTIVATE_LOCKEE)
    {
      check(!current()->switch_exec_locked (context(), Context::Not_Helping));
      return;
    }

  // Switch to lockee's execution context and timeslice if its priority
  // is higher than the current priority
  if (Sched_context::rq.current().deblock(context()->sched(), current()->sched(), true))
    current()->switch_to_locked(context());
}

#line 212 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_lock.cpp"

/** Free the lock.
    First return the CPU to helper or next lock owner, whoever has the higher 
    priority, given that thread's priority is higher that ours.
    Finally, switch to locked thread if that thread has a higher priority,
    and/or the switch hint says we should.
    Assumes caller hold cpu lock
 */

void
Thread_lock::clear_dirty()
{
  assert(cpu_lock.test());

  Switch_hint hint = _switch_hint;

  if(test())
    {
      Lock::clear_dirty();
      context()->set_donatee(lock_owner());
    }
  else
    {
      //      assert(!context()->donatee());
    }

  assert(cpu_lock.test());

  // We had locked ourselves, remain current
  if (context() == current())
    return;

  // Unlocked thread not ready, remain current
  if (!(context()->state() & Thread_ready))
    return;

  // Switch to lockee's execution context if the switch hint says so
  if (hint == SWITCH_ACTIVATE_LOCKEE)
    {
      check(!current()->switch_exec_locked(context(), Context::Not_Helping));
      return;
    }

  // Switch to lockee's execution context and timeslice if its priority
  // is higher than the current priority
  if (Sched_context::rq.current().deblock(context()->sched(), current()->sched(), true))
    current()->switch_to_locked(context());
}
