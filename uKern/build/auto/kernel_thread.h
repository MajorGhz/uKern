// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kernel_thread_h
#define kernel_thread_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread.cpp"

#include "thread_object.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread.cpp"

class Kernel_thread : public Thread_object
{
private:
  /**
   * Frees the memory of the initcall sections.
   *
   * Virtually initcall sections are freed by not marking them
   * reserved in the KIP. This method just invalidates the contents of
   * the memory, by filling it with some invalid data and may be
   * unmapping it.
   */
  void free_initcall_section();
  void bootstrap() asm ("call_bootstrap") FIASCO_FASTCALL;
  void bootstrap_arch();
  void run();
  void do_idle() __attribute__((noreturn));

protected:
  void init_workload();

public:  
#line 49 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread.cpp"
  Kernel_thread();
  
#line 53 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread.cpp"
  inline Mword *
  init_stack();
  
#line 128 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread.cpp"
  inline void
  idle_op();

private:  
#line 139 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread-std.cpp"
  inline Address
  init_workload_s0_stack();
  
#line 48 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kernel_thread-ia32.cpp"
  static void inline
  boot_app_cpus();
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 39 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread.cpp"
#include "processor.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kernel_thread-ia32.cpp"
#include "mem_layout.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 51 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread.cpp"


inline Mword *
Kernel_thread::init_stack()
{ return _kernel_sp; }

#line 126 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread.cpp"


inline void
Kernel_thread::idle_op()
{
  if (Config::hlt_works_ok)
    Proc::halt();			// stop the CPU, waiting for an int
  else
    Proc::pause();
}

#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kernel_thread-ia32.cpp"


inline void
Kernel_thread::free_initcall_section()
{
  // just fill up with invalid opcodes
  for (unsigned short *i = (unsigned short *) &Mem_layout::initcall_start;   
                       i < (unsigned short *) &Mem_layout::initcall_end; i++)
    *i = 0x0b0f;	// UD2 opcode
}

#endif // kernel_thread_h
