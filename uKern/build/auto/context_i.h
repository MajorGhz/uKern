// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef context_i_h
#define context_i_h
#line 396 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

#include <cassert>
#line 399 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "cpu.h"
#line 400 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "cpu_lock.h"
#line 402 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "fpu.h"
#line 403 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "globals.h"		// current()
#line 404 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "kdb_ke.h"
#line 405 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "lock_guard.h"
#line 408 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "mem_layout.h"
#line 409 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "processor.h"
#line 410 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "space.h"
#line 411 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "std_macros.h"
#line 412 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "thread_state.h"
#line 413 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "timer.h"
#line 414 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "timeout.h"
#line 427 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"



#include <cstdio>
#line 1666 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

#include "warn.h"
#line 2156 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

#include "kobject_dbg.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/context-ia32.cpp"

#include "cpu.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/context-ia32.cpp"
#include "kmem.h"
#line 146 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context-vcpu.cpp"

#include "kobject_dbg.h"

//
// IMPLEMENTATION of inline functions follows
//


#line 1150 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"



inline Context *
Context::handle_helping(Context *t)
{
  // XXX: maybe we do not need this on MP, because we have no helping there
  assert_kdb (current() == this);
  // Time-slice lending: if t is locked, switch to its locker
  // instead, this is transitive
  while (t->donatee() &&		// target thread locked
         t->donatee() != t)		// not by itself
    {
      // Special case for Thread::kill(): If the locker is
      // current(), switch to the locked thread to allow it to
      // release other locks.  Do this only when the target thread
      // actually owns locks.
      if (t->donatee() == this)
        {
          if (t->lock_cnt() > 0)
            break;

          return this;
        }

      t = t->donatee();
    }
  return t;
}

#endif // context_i_h
