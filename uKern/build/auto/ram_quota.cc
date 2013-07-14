// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "ram_quota.h"
#include "ram_quota_i.h"

#line 22 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ram_quota.cpp"

Ram_quota *Ram_quota::root;

#line 31 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ram_quota.cpp"


Ram_quota::Ram_quota()
  : _parent(0), _current(0), _max (~0UL)
{
  root = this;
}

#line 38 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ram_quota.cpp"


Ram_quota::Ram_quota(Ram_quota *p, unsigned long max)
  : _parent(p), _current(0), _max (max)
{}

#line 43 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ram_quota.cpp"


unsigned long
Ram_quota::current() const
{ return _current; }

#line 48 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ram_quota.cpp"


bool
Ram_quota::alloc(signed long bytes)
{ 
  auto guard = lock_guard(cpu_lock);
  if (unlimited() || _current + bytes <= _max)
    {
      _current += bytes;
      return true;
    }

  return false;
}
