// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef helping_lock_h
#define helping_lock_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/helping_lock.cpp"

#include "lock_guard.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/helping_lock.cpp"
#include "switch_lock.h"

//
// INTERFACE definition follows 
//

#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/helping_lock.cpp"

#ifdef NO_INSTRUMENT
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/helping_lock.cpp"
#undef NO_INSTRUMENT
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/helping_lock.cpp"
#endif
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/helping_lock.cpp"
#define NO_INSTRUMENT __attribute__((no_instrument_function))
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/helping_lock.cpp"

/** A wrapper for Switch_lock that works even when the threading system
    has not been intialized yet.
    This wrapper is necessary because most lock-protected objects are 
    initialized before the threading system has been fired up.
 */
class Helping_lock : private Switch_lock
{

public:
  using Switch_lock::Status;
  using Switch_lock::Not_locked;
  using Switch_lock::Locked;
  using Switch_lock::Invalid;

  using Switch_lock::invalidate;
  using Switch_lock::valid;
  using Switch_lock::wait_free;

  static bool threading_system_active;

public:  
#line 45 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/helping_lock.cpp"
  /** Constructor. */
  
  inline Helping_lock();
  
#line 52 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/helping_lock.cpp"
  /** Acquire the lock with priority inheritance.
      @return true if we owned the lock already.  false otherwise.
   */
  
  inline Helping_lock::Status NO_INSTRUMENT
  test_and_set();
  
#line 65 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/helping_lock.cpp"
  /** Acquire the lock with priority inheritance.
      If the lock is occupied, enqueue in list of helpers and lend CPU 
      to current lock owner until we are the lock owner.
   */
  
  inline Helping_lock::Status NO_INSTRUMENT
  lock();
  
#line 76 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/helping_lock.cpp"
  /** Is lock set?.
      @return true if lock is set.
   */
  
  inline Helping_lock::Status NO_INSTRUMENT
  test();
  
#line 89 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/helping_lock.cpp"
  /** Free the lock.
      Return the CPU to helper or next lock owner, whoever has the higher 
      priority, given that thread's priority is higher that our's.
   */
  
  inline void NO_INSTRUMENT
  clear();
  
#line 104 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/helping_lock.cpp"
  inline void
  set(Status s);
  
#line 111 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/helping_lock.cpp"
  /** Lock owner. 
      @return current owner of the lock.  0 if there is no owner.
   */
  
  inline Context* NO_INSTRUMENT
  lock_owner() const;
};
#line 31 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/helping_lock.cpp"

#undef NO_INSTRUMENT
#line 33 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/helping_lock.cpp"
#define NO_INSTRUMENT

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 36 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/helping_lock.cpp"

#include "globals.h"
#line 38 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/helping_lock.cpp"
#include "panic.h"
#line 39 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/helping_lock.cpp"
#include "std_macros.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 44 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/helping_lock.cpp"

/** Constructor. */

inline Helping_lock::Helping_lock()
{
  Switch_lock::initialize();
}

#line 51 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/helping_lock.cpp"

/** Acquire the lock with priority inheritance.
    @return true if we owned the lock already.  false otherwise.
 */

inline Helping_lock::Status NO_INSTRUMENT
Helping_lock::test_and_set()
{
  if (! threading_system_active) // still initializing?
    return Not_locked;
  
  return Switch_lock::test_and_set();
}

#line 64 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/helping_lock.cpp"

/** Acquire the lock with priority inheritance.
    If the lock is occupied, enqueue in list of helpers and lend CPU 
    to current lock owner until we are the lock owner.
 */

inline Helping_lock::Status NO_INSTRUMENT
Helping_lock::lock()
{
  return test_and_set();
}

#line 75 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/helping_lock.cpp"

/** Is lock set?.
    @return true if lock is set.
 */

inline Helping_lock::Status NO_INSTRUMENT
Helping_lock::test()
{
  if (EXPECT_FALSE( ! threading_system_active) ) // still initializing?
    return Not_locked;

  return Switch_lock::test();
}

#line 88 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/helping_lock.cpp"

/** Free the lock.
    Return the CPU to helper or next lock owner, whoever has the higher 
    priority, given that thread's priority is higher that our's.
 */

inline void NO_INSTRUMENT
Helping_lock::clear()
{
  if (EXPECT_FALSE( ! threading_system_active) ) // still initializing?
    return;

  Switch_lock::clear();
}

#line 102 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/helping_lock.cpp"


inline void
Helping_lock::set(Status s)
{
  if (!s)
    clear();
}

#line 110 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/helping_lock.cpp"

/** Lock owner. 
    @return current owner of the lock.  0 if there is no owner.
 */

inline Context* NO_INSTRUMENT
Helping_lock::lock_owner() const
{
  if (EXPECT_FALSE( ! threading_system_active) ) // still initializing?
    return current();

  return Switch_lock::lock_owner();
}

#endif // helping_lock_h
