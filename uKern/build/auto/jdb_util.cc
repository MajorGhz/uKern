// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_util.h"
#include "jdb_util_i.h"


#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_util.cpp"


bool
Jdb_util::is_mapped(void const *x)
{
  return Kmem::virt_to_phys(x) != ~0UL;
}
