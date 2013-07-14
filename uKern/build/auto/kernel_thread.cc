// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "kernel_thread.h"
#include "kernel_thread_i.h"

#line 123 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread.cpp"

// ------------------------------------------------------------------------


#line 46 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread.cpp"



Kernel_thread::Kernel_thread() : Thread_object(Thread::Kernel)
{}

#line 56 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread.cpp"

// the kernel bootstrap routine
FIASCO_INIT
void
Kernel_thread::bootstrap()
{
  // Initializations done -- Helping_lock can now use helping lock
  Helping_lock::threading_system_active = true;

  // we need per CPU data for our never running dummy CPU too
  // FIXME: we in fact need only the _pending_rqq lock
  Per_cpu_data_alloc::alloc(Cpu::invalid());

  set_cpu_of(this, Cpu::boot_cpu()->id());
  Mem::barrier();

  state_change_dirty(0, Thread_ready);		// Set myself ready

  Timer::init_system_clock();
  Sched_context::rq.current().set_idle(this->sched());

  Kernel_task::kernel_task()->make_current();

  // Setup initial timeslice
  Sched_context::rq.current().set_current_sched(sched());

  Timer_tick::setup(cpu(true));
  assert (cpu(true) == Cpu_number::boot_cpu()); // currently the boot cpu must be 0
  Timer_tick::enable(cpu(true));
  enable_tlb(cpu(true));

  bootstrap_arch();

  Per_cpu_data::run_late_ctors(Cpu_number::boot_cpu());

  Proc::sti();
  Watchdog::enable();
  printf("Calibrating timer loop... ");
  // Init delay loop, needs working timer interrupt
  Delay::init();
  printf("done.\n");

  run();
}

#line 100 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread.cpp"

/**
 * The idle loop
 * NEVER inline this function, because our caller is an initcall
 */
FIASCO_NOINLINE FIASCO_NORETURN
void
Kernel_thread::run()
{
  free_initcall_section();

  // No initcalls after this point!

  kernel_context(cpu(), this);

  Rcu::leave_idle(cpu());
  // init_workload cannot be an initcall, because it fires up the userland
  // applications which then have access to initcall frames as per kinfo page.
  init_workload();

  for (;;)
    idle_op();
}
