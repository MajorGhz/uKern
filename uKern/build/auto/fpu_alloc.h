// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef fpu_alloc_h
#define fpu_alloc_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/fpu_alloc.cpp"

#include "fpu.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/fpu_alloc.cpp"
#include "slab_cache.h"

//
// INTERFACE definition follows 
//

#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/fpu_alloc.cpp"

class Ram_quota;
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/fpu_alloc.cpp"

class Fpu_alloc : public Fpu
{

public:  
#line 29 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/fpu_alloc.cpp"
  static bool
  alloc_state(Ram_quota *q, Fpu_state *s);
  
#line 45 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/fpu_alloc.cpp"
  static void
  free_state(Fpu_state *s);

private:  
#line 22 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/fpu_alloc.cpp"
  static Slab_cache *
  slab_alloc();
};

#endif // fpu_alloc_h
