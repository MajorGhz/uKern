// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef factory_i_h
#define factory_i_h
#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"

#include "ipc_gate.h"
#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"
#include "kmem_slab.h"
#line 21 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"
#include "task.h"
#line 22 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"
#include "thread_object.h"
#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"
#include "static_init.h"
#line 24 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"
#include "l4_buf_iter.h"
#line 25 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"
#include "l4_types.h"
#line 26 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"
#include "irq.h"
#line 27 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"
#include "map_util.h"
#line 28 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"
#include "logdefs.h"
#line 29 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"
#include "entry_frame.h"

//
// IMPLEMENTATION of inline functions follows
//


#line 38 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"


inline Factory::Factory(Ram_quota *q, unsigned long max)
  : Ram_quota(q, max)
{}

#endif // factory_i_h
