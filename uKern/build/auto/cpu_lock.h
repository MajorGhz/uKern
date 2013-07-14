// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef cpu_lock_h
#define cpu_lock_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/cpu_lock.cpp"

#include "types.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/cpu_lock.cpp"

/** 
 * Global CPU lock. When held, irqs are disabled on the current CPU 
 * (preventing nested irq handling, and preventing the current 
 * thread from being preempted).  It must only be held for very short
 * amounts of time.
 *
 * A generic (cli, sti) implementation of the lock can be found in 
 * cpu_lock-generic.cpp.
 */
class Cpu_lock
{
public:
  /// The return type of test methods
  typedef Mword Status;

  enum { Locked = 1, Not_locked = 0 };

  /// ctor.
  inline Cpu_lock();

  /**
   * Test if the lock is already held.
   * @return 0 if the lock is not held, not 0 if it already is held.
   */
  Status test() const;

  /**
   * Acquire the CPU lock.
   * The CPU lock disables IRQ's it should be held only for a very 
   * short amount of time.
   */
  void lock();

  /**
   * Release the CPU lock.
   */
  void clear();

  /**
   * Acquire the CPU lock and return the old status.
   * @return something else that 0 if the lock was already held and
   *   0 if it was not held. 
   */
  Status test_and_set();

  /**
   * Set the CPU lock according to the given status.
   * @param state the state to set (0 clear, else lock).
   */
  void set(Status state);

private:
  /// Default copy constructor not implemented.
  Cpu_lock (const Cpu_lock&);

};
#line 61 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/cpu_lock.cpp"

/**
 * The global CPU lock, contains the locking data necessary for some
 * special implementations.
 */
extern Cpu_lock cpu_lock;

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/cpu_lock-generic.cpp"
/**
 * Generic implementation of the CPU lock. 
 * This implementation uses Proc::cli and
 * Proc::sti from the processor headers.
 *
 */

#include "processor.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 73 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/cpu_lock.cpp"


//NEEDS [Cpu_lock::lock, Cpu_lock::test]
inline Cpu_lock::Status Cpu_lock::test_and_set()
{
  Status ret = test();
  lock();
  return ret;
}

#line 82 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/cpu_lock.cpp"



//NEEDS [Cpu_lock::lock, Cpu_lock::clear]
inline void Cpu_lock::set(Cpu_lock::Status state)
{
  if (state)
    lock();
  else
    clear();
}

#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/cpu_lock-generic.cpp"


inline Cpu_lock::Cpu_lock()
{}

#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/cpu_lock-generic.cpp"


inline void Cpu_lock::lock()
{
  Proc::cli();
}

#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/cpu_lock-generic.cpp"


inline void
Cpu_lock::clear()
{
  Proc::sti();
}

#line 27 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/cpu_lock-generic.cpp"


inline Cpu_lock::Status Cpu_lock::test() const
{
  return ! Proc::interrupts();
}

#endif // cpu_lock_h
