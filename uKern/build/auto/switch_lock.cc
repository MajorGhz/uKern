// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "switch_lock.h"
#include "switch_lock_i.h"


#line 166 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/switch_lock.cpp"

/** Acquire the lock with priority inheritance.
 *  If the lock is occupied, enqueue in list of helpers and lend CPU 
 *  to current lock owner until we are the lock owner.
 *  @return #Locked if the lock was already locked by the current context.
 *          #Not_locked if the current context got the lock (the usual case).
 *          #Invalid if the lock does not exist (see valid()).
 */

Switch_lock::Status NO_INSTRUMENT
Switch_lock::lock()
{
  auto guard = lock_guard(cpu_lock);
  return lock_dirty();
}

#line 312 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/switch_lock.cpp"

/** Free the lock.  
    Return the CPU to helper if there is one, since it had to have a
    higher priority to be able to help (priority may be its own, it
    may run on a donated timeslice or round robin scheduling may have
    selected a thread on the same priority level as me)

    @pre The lock must be valid (see valid()).
 */

void NO_INSTRUMENT
Switch_lock::clear()
{
  auto guard = lock_guard(cpu_lock);

  switch_dirty(clear_no_switch_dirty());
}

#line 329 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/switch_lock.cpp"


void NO_INSTRUMENT
Switch_lock::set(Status s)
{
  if (s == Not_locked)
    clear();
}

#line 365 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/switch_lock.cpp"


void NO_INSTRUMENT
Switch_lock::wait_free()
{
  auto guard = lock_guard(cpu_lock);

  assert (!valid());

  // have we already the lock?
  if ((_lock_owner & ~1UL) == (Address)current())
    {
      set_lock_owner(0);
      current()->dec_lock_cnt();
      return;
    }

  while (Address(_lock_owner) & ~1UL)
    {
      assert(cpu_lock.test());

      // Help lock owner until lock becomes free
      //      while (test())
      check (!current()->switch_exec_locked((Context*)(Address(_lock_owner & ~1UL)), Context::Helping));

      Proc::irq_chance();
    }
}
