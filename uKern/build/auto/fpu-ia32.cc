// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "fpu.h"
#include "fpu_i.h"

#line 185 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/fpu-ia32.cpp"
/*
 * Fiasco ia32
 * Architecture specific floating point unit code
 */



#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/fpu-ia32.cpp"


void
Fpu::init_xsave(Cpu_number cpu)
{
  Unsigned32 eax, ebx, ecx, edx;

  Cpu::cpus.cpu(cpu).cpuid_0xd(0, &eax, &ebx, &ecx, &edx);

  Unsigned64 valid_xcr0 = ((Unsigned64)edx << 32) | eax;

  // enable AVX and friends
  Cpu::cpus.cpu(cpu).set_cr4(Cpu::cpus.cpu(cpu).get_cr4() | CR4_OSXSAVE);
  asm volatile("xsetbv"
               :
               : "a" ((Mword)valid_xcr0),
                 "d" ((Mword)(valid_xcr0 >> 32)),
                 "c" (0));
}

#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/fpu-ia32.cpp"


void
Fpu::init_disable()
{
  // disable Coprocessor Emulation to allow exception #7/NM on TS
  // enable Numeric Error (exception #16/MF, native FPU mode)
  // enable Monitor Coprocessor
  Cpu::set_cr0((Cpu::get_cr0() & ~CR0_EM) | CR0_NE | CR0_MP);
}
