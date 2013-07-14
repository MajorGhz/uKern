// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kmem_alloc_i_h
#define kmem_alloc_i_h
#line 79 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_alloc.cpp"

#include "config.h"
#line 81 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
#include "kdb_ke.h"
#line 82 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
#include "kip.h"
#line 84 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
#include "mem_region.h"
#line 85 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
#include "buddy_alloc.h"
#line 86 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
#include "panic.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem_alloc-ia32.cpp"

#include <cstdio>
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem_alloc-ia32.cpp"

#include "kip.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem_alloc-ia32.cpp"
#include "koptions.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem_alloc-ia32.cpp"
#include "mem_region.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem_alloc-ia32.cpp"
#include "panic.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem_alloc-ia32.cpp"
#include "types.h"
#line 157 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem_alloc-ia32.cpp"

#include "div32.h"

//
// IMPLEMENTATION of inline functions follows
//


#line 172 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem_alloc-ia32.cpp"


inline unsigned long
Kmem_alloc::orig_free()
{
  return _orig_free;
}

#endif // kmem_alloc_i_h
