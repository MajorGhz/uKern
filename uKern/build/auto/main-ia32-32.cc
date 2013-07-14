// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "main.h"
#include "main_i.h"


#line 25 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/main-ia32-32.cpp"


FIASCO_INIT
void
kernel_main(void)
{
  unsigned dummy;

  Cpu const &cpu = *Cpu::boot_cpu();

  // caution: no stack variables in this function because we're going
  // to change the stack pointer!
  cpu.print();
  cpu.show_cache_tlb_info("");

  printf ("\nFreeing init code/data: %lu bytes (%lu pages)\n\n",
          (Address)(&Mem_layout::initcall_end - &Mem_layout::initcall_start),
          (Address)(&Mem_layout::initcall_end - &Mem_layout::initcall_start
	     >> Config::PAGE_SHIFT));

  // Perform architecture specific initialization
  main_arch();

  // create kernel thread
  static Kernel_thread *kernel = new (Ram_quota::root) Kernel_thread;
  assert_opt (kernel);
  Task *const ktask = Kernel_task::kernel_task();
  check(kernel->bind(ktask, User<Utcb>::Ptr(0)));

  // switch to stack of kernel thread and bootstrap the kernel
  asm volatile
    ("	movl %%esi, %%esp	\n\t"	// switch stack
     "	call call_bootstrap	\n\t"	// bootstrap kernel thread
     : "=a" (dummy), "=c" (dummy), "=d" (dummy)
     : "a"(kernel), "S" (kernel->init_stack()));
}
