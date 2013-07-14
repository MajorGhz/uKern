// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef spin_lock_h
#define spin_lock_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/spin_lock.cpp"

#include "cpu_lock.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/spin_lock.cpp"

class Spin_lock_base : protected Cpu_lock
{
public:
  enum Lock_init { Unlocked = 0 };
};
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/spin_lock.cpp"

/**
 * \brief Basic spin lock.
 *
 * Also disables lock IRQs for the time the lock is held.
 * In the UP case it is in fact just the Cpu_lock.
 */
template<typename Lock_t = char>
class Spin_lock : public Spin_lock_base
{

#line 24 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/spin_lock.cpp"
private:

public:
  Spin_lock() {}
  explicit Spin_lock(Lock_init) {}
  void init() {}

  using Cpu_lock::Status;
  using Cpu_lock::test;
  using Cpu_lock::lock;
  using Cpu_lock::clear;
  using Cpu_lock::test_and_set;
  using Cpu_lock::set;

};
#line 21 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/spin_lock.cpp"

//--------------------------------------------------------------------------

#line 40 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/spin_lock.cpp"

/**
 * \brief Version of a spin lock that is colocated with another value.
 */
template< typename T >
class Spin_lock_coloc : public Spin_lock<Mword>
{
private:
  enum { Arch_lock = 1 };
  Mword _lock;

public:  
#line 80 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/spin_lock.cpp"
  inline Spin_lock_coloc();
  
#line 84 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/spin_lock.cpp"
  inline Spin_lock_coloc(Lock_init i);
  
#line 88 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/spin_lock.cpp"
  inline T
  get_unused() const;
  
#line 94 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/spin_lock.cpp"
  inline void
  set_unused(T val);
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 77 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/spin_lock.cpp"



template< typename T > inline Spin_lock_coloc<T>::Spin_lock_coloc() {}

#line 81 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/spin_lock.cpp"



template< typename T > inline Spin_lock_coloc<T>::Spin_lock_coloc(Lock_init i) : Spin_lock<Mword>(i) {}

#line 85 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/spin_lock.cpp"



template< typename T > inline T
Spin_lock_coloc<T>::get_unused() const
{ return (T)(_lock & ~Arch_lock); }

#line 91 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/spin_lock.cpp"



template< typename T > inline void
Spin_lock_coloc<T>::set_unused(T val)
{ _lock = (_lock & Arch_lock) | (Mword)val; }

#endif // spin_lock_h
