// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kernel_thread_i_h
#define kernel_thread_i_h
#line 28 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread.cpp"

#include <cstdlib>
#line 30 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread.cpp"
#include <cstdio>
#line 31 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread.cpp"

#include "config.h"
#line 33 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread.cpp"
#include "cpu.h"
#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread.cpp"
#include "delayloop.h"
#line 35 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread.cpp"
#include "globals.h"
#line 36 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread.cpp"
#include "helping_lock.h"
#line 37 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread.cpp"
#include "kernel_task.h"
#line 38 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread.cpp"
#include "per_cpu_data_alloc.h"
#line 40 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread.cpp"
#include "task.h"
#line 41 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread.cpp"
#include "thread.h"
#line 42 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread.cpp"
#include "thread_state.h"
#line 43 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread.cpp"
#include "timer.h"
#line 44 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread.cpp"
#include "timer_tick.h"
#line 45 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread.cpp"
#include "watchdog.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread-std.cpp"

#include "assert_opt.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread-std.cpp"
#include "config.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread-std.cpp"
#include "factory.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread-std.cpp"
#include "initcalls.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread-std.cpp"
#include "ipc_gate.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread-std.cpp"
#include "irq.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread-std.cpp"
#include "koptions.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread-std.cpp"
#include "map_util.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread-std.cpp"
#include "mem_layout.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread-std.cpp"
#include "sigma0_task.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread-std.cpp"
#include "task.h"
#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread-std.cpp"
#include "thread_object.h"
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread-std.cpp"
#include "types.h"
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread-std.cpp"
#include "ram_quota.h"
#line 3 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kernel_thread-ia32.cpp"

#include "apic.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kernel_thread-ia32.cpp"
#include "config.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kernel_thread-ia32.cpp"
#include "cpu.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kernel_thread-ia32.cpp"
#include "io_apic.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kernel_thread-ia32.cpp"
#include "irq_mgr.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kernel_thread-ia32.cpp"
#include "koptions.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kernel_thread-ia32.cpp"
#include "pic.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kernel_thread-ia32.cpp"
#include "trap_state.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kernel_thread-ia32.cpp"
#include "watchdog.h"

//
// IMPLEMENTATION of inline functions follows
//


#line 137 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread-std.cpp"


inline Address
Kernel_thread::init_workload_s0_stack()
{
  // push address of kernel info page to sigma0's stack
  Address sp = Kip::k()->sigma0_sp - sizeof(Mword);
  // assume we run in kdir 1:1 mapping
  *reinterpret_cast<Address*>(sp) = Kmem::virt_to_phys(Kip::k());
  return sp;
}

#endif // kernel_thread_i_h
