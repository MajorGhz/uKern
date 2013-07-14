// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef switch_lock_i_h
#define switch_lock_i_h
#line 78 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/switch_lock.cpp"

#include <cassert>
#line 83 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/switch_lock.cpp"
#include "cpu_lock.h"
#line 84 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/switch_lock.cpp"
#include "lock_guard.h"

//
// IMPLEMENTATION of inline functions follows
//


#line 142 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/switch_lock.cpp"

/** Try to acquire the lock.
    @return #Locked if successful: current context is now the owner of the lock.
            #Not_locked if lock has previously been set.  Returns Not_locked
	    even if the current context is already the lock owner.
	    The result is #Invalid if the lock does not exist (see valid()).
 */


inline Switch_lock::Status NO_INSTRUMENT
Switch_lock::try_lock()
{
  auto guard = lock_guard(cpu_lock);

  if (EXPECT_FALSE(!valid()))
    return Invalid;

  bool ret = cas(&_lock_owner, (Address)0, Address(current()));

  if (ret)
    current()->inc_lock_cnt();	// Do not lose this lock if current is deleted

  return ret ? Locked : Not_locked;
}

#endif // switch_lock_i_h
