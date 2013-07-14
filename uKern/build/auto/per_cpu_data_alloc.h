// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef per_cpu_data_alloc_h
#define per_cpu_data_alloc_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/per_cpu_data_alloc.cpp"

#include "per_cpu_data.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/per_cpu_data_alloc.cpp"

class Per_cpu_data_alloc : public Per_cpu_data
{
public:
  static bool alloc(Cpu_number cpu);
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/per_cpu_data_alloc.cpp"


inline bool Per_cpu_data_alloc::alloc(Cpu_number)
{ return true; }

#endif // per_cpu_data_alloc_h
