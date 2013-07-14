// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef processor_h
#define processor_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/processor.cpp"

#include "types.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/processor.cpp"

/// Central processor specific methods.
class Proc
{
public:

  typedef Mword Status;

  /// Block external interrupts
  static void cli();

  /// Unblock external inetrrupts
  static void sti();

  /// Are external interrupts enabled ?
  static Status interrupts();

  /// Block external interrupts and save the old state
  static Status cli_save();

  /// Conditionally unblock external interrupts
  static void sti_restore( Status );

  static void pause();

  static void halt();

  static void irq_chance();

  static void stack_pointer(Mword sp);

  static Mword stack_pointer();

  static Mword program_counter();

  static inline
  void preemption_point()
  {
    sti();
    irq_chance();
    cli();
  }

};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/ia32/processor-ia32.cpp"


inline Mword Proc::stack_pointer()
{
  Mword sp;
  asm volatile ("movl %%esp, %0" : "=r" (sp));
  return sp;
}

#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/ia32/processor-ia32.cpp"


inline void Proc::stack_pointer(Mword sp)
{
  asm volatile ("movl %0, %%esp \n" : : "r"(sp));
}

#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/ia32/processor-ia32.cpp"


inline Mword Proc::program_counter()
{
  Mword pc;
  asm volatile ("call 1f ; 1: pop %0" : "=r"(pc));
  return pc;
}

#line 27 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/ia32/processor-ia32.cpp"


inline void Proc::pause()
{
  asm volatile (" .byte 0xf3, 0x90 #pause \n" ); 
}

#line 33 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/ia32/processor-ia32.cpp"

/*
 * The following simple ASM statements need the clobbering to work around
 * a bug in (at least) gcc-3.2.x up to x == 1. The bug was fixed on
 * Jan 9th 2003 (see gcc-bugs #9242 and #8832), so a released gcc-3.2.2
 * won't have it. It's safe to take the clobber statements out after
 * some time (e.g. when gcc-3.3 is used as a standard compiler).
 */


inline void Proc::halt()
{
  asm volatile (" hlt" : : : "memory");
}

#line 47 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/ia32/processor-ia32.cpp"


inline void Proc::cli()
{
  asm volatile ("cli" : : : "memory");
}

#line 53 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/ia32/processor-ia32.cpp"


inline void Proc::sti()
{
  asm volatile ("sti" : : : "memory");
}

#line 59 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/ia32/processor-ia32.cpp"


inline Proc::Status Proc::cli_save()
{
  Status ret;
  asm volatile ("pushfl	\n\t"
		"popl %0	\n\t"
		"cli		\n\t"
		: "=g"(ret) : /* no input */ : "memory");
  return ret;
}

#line 70 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/ia32/processor-ia32.cpp"


inline void Proc::sti_restore(Status st)
{
  if (st & 0x0200)
    asm volatile ("sti" : : : "memory");
}

#line 77 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/ia32/processor-ia32.cpp"


inline Proc::Status Proc::interrupts()
{
  Status ret;
  asm volatile ("pushfl         \n"
                "popl %0        \n"
                : "=g"(ret) : /* no input */ : "memory");
  return ret & 0x0200;
}

#line 87 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/ia32/processor-ia32.cpp"


inline void Proc::irq_chance()
{
  asm volatile ("nop; nop;" : : : "memory");
}

#endif // processor_h
