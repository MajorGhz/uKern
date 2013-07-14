// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "kernel_thread.h"
#include "kernel_thread_i.h"

#line 44 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kernel_thread-ia32.cpp"

//--------------------------------------------------------------------------


#line 24 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kernel_thread-ia32.cpp"


FIASCO_INIT
void
Kernel_thread::bootstrap_arch()
{
  // 
  // install our slow trap handler
  //
  nested_trap_handler      = Trap_state::base_handler;
  Trap_state::base_handler = thread_handle_trap;

  // initialize the profiling timer
  bool user_irq0 = Koptions::o()->opt(Koptions::F_irq0);

  if ((int)Config::Scheduler_mode == Config::SCHED_PIT && user_irq0)
    panic("option -irq0 not possible since irq 0 is used for scheduling");

  boot_app_cpus();
}

#line 47 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kernel_thread-ia32.cpp"

void inline
Kernel_thread::boot_app_cpus()
{}
