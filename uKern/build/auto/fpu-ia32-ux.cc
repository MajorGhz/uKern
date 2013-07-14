// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "fpu.h"
#include "fpu_i.h"

#line 68 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/fpu-ia32-ux.cpp"

unsigned Fpu::_state_size;
#line 70 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/fpu-ia32-ux.cpp"
unsigned Fpu::_state_align;

#line 112 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/fpu-ia32-ux.cpp"


void
Fpu::init(Cpu_number cpu)
{
  // Mark FPU busy, so that first FPU operation will yield an exception
  disable();

  // At first, noone owns the FPU
  Fpu &f = Fpu::fpu.cpu(cpu);

  f.set_owner(0);

  init_disable();

  printf("FPU%d: %s%s\n", cxx::int_value<Cpu_number>(cpu),
         Cpu::cpus.cpu(cpu).features() & FEAT_SSE  ? "SSE "  : "",
	 Cpu::cpus.cpu(cpu).ext_features() & FEATX_AVX ? "AVX "  : "");

  unsigned cpu_align = 0, cpu_size  = 0;

  if (Cpu::cpus.cpu(cpu).ext_features() & FEATX_XSAVE)
    {
      init_xsave(cpu);

      Cpu::cpus.cpu(cpu).update_features_info();

      Unsigned32 eax, ecx, edx;
      Cpu::cpus.cpu(cpu).cpuid_0xd(0, &eax, &cpu_size, &ecx, &edx);
      cpu_align = 64;
      f._variant = Variant_xsave;
    }
  else if (Cpu::have_fxsr())
    {
      cpu_size  = sizeof(sse_regs);
      cpu_align = 16;
      f._variant  = Variant_fxsr;
    }
  else
    {
      cpu_size  = sizeof(fpu_regs);
      cpu_align = 4;
      f._variant  = Variant_fpu;
    }

  if (cpu_size > _state_size)
    _state_size = cpu_size;
  if (cpu_align > _state_align)
    _state_align = cpu_align;
}
