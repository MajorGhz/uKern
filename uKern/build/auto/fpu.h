// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef fpu_h
#define fpu_h
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/fpu.cpp"

#include "initcalls.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/fpu.cpp"
#include "per_cpu_data.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/fpu.cpp"
#include "types.h"

//
// INTERFACE definition follows 
//

#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/fpu.cpp"

class Context;
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/fpu.cpp"
class Fpu_state;
#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/fpu.cpp"
class Trap_state;
#line 1 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/fpu.cpp"
/*
 * Fiasco
 * Floating point unit code
 */


#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/fpu.cpp"


class Fpu
{
public:
  // all the following methods are arch dependent
  static void init(Cpu_number cpu) FIASCO_INIT_CPU;

  static unsigned state_size();
  static unsigned state_align();
  static void init_state(Fpu_state *);
  static void restore_state(Fpu_state *);
  static void save_state(Fpu_state *);
  static void disable();
  static void enable();

  static Per_cpu<Fpu> fpu;

  Context *owner() const { return _owner; }
  void set_owner(Context *owner) { _owner = owner; }
  bool is_owner(Context *owner) const { return _owner == owner; }

private:
  Context *_owner;

#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/fpu-ia32-ux.cpp"
private:


private:
  struct fpu_regs       // saved FPU registers
  {
    long    cwd;
    long    swd;
    long    twd;
    long    fip;
    long    fcs;
    long    foo;
    long    fos;
    long    st_space[20];   /* 8*10 bytes for each FP-reg = 80 bytes */
  };

  struct sse_regs
  {
    Unsigned16 cwd;
    Unsigned16 swd;
    Unsigned16 twd;
    Unsigned16 fop;
    Unsigned32 fip;
    Unsigned32 fcs;
    Unsigned32 foo;
    Unsigned32 fos;
    Unsigned32 mxcsr;
    Unsigned32 reserved;
    Unsigned32 st_space[32];   /*  8*16 bytes for each FP-reg  = 128 bytes */
    Unsigned32 xmm_space[64];  /* 16*16 bytes for each XMM-reg = 256 bytes */
    Unsigned32 padding[24];
  };

  struct Xsave_buffer
  {
    sse_regs sse;
    Unsigned64 header[8];
  };

  enum Variants
  {
    Variant_fpu,
    Variant_fxsr,
    Variant_xsave,
  };

  enum Variants _variant;

  static unsigned _state_size;
  static unsigned _state_align;

private:  
#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/fpu-ia32.cpp"
  static void
  init_xsave(Cpu_number cpu);
  
#line 36 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/fpu-ia32.cpp"
  static void
  init_disable();
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 61 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/fpu-ia32-ux.cpp"

#include <cstring>
#line 64 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/fpu-ia32-ux.cpp"
#include "fpu_state.h"
#line 67 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/fpu-ia32-ux.cpp"
#include "static_assert.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/fpu-ia32.cpp"

#include "cpu.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/fpu-ia32.cpp"
#include "globalconfig.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/fpu-ia32.cpp"
#include "globals.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/fpu-ia32.cpp"
#include "regdefs.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/fpu-ia32.cpp"

#include <cassert>

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 71 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/fpu-ia32-ux.cpp"

/*
 * Initialize FPU or SSE state
 * We don't use finit, because it is slow. Initializing the context in
 * memory and fetching it via restore_state is supposedly faster
 */


inline void
Fpu::init_state(Fpu_state *s)
{
  Cpu const &_cpu = Cpu::cpus.cpu(current_cpu());
  if (_cpu.features() & FEAT_FXSR)
    {
      assert (_state_size >= sizeof (sse_regs));
      sse_regs *sse = reinterpret_cast<sse_regs *>(s->state_buffer());

      memset(sse, 0, sizeof (*sse));
      sse->cwd = 0x37f;

      if (_cpu.features() & FEAT_SSE)
	sse->mxcsr = 0x1f80;

      if (_cpu.ext_features() & FEATX_XSAVE)
        memset(reinterpret_cast<Xsave_buffer *>(s->state_buffer())->header, 0,
	       sizeof (Xsave_buffer::header));

      static_assert(sizeof (sse_regs) == 512, "SSE-regs size not 512 bytes");
    }
  else
    {
      fpu_regs *fpu = reinterpret_cast<fpu_regs *>(s->state_buffer());

      assert (_state_size >= sizeof (*fpu));
      memset(fpu, 0, sizeof (*fpu));
      fpu->cwd = 0xffff037f;
      fpu->swd = 0xffff0000;
      fpu->twd = 0xffffffff;
      fpu->fos = 0xffff0000;
    }
}

#line 162 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/fpu-ia32-ux.cpp"


/**
 * Return size of FPU context structure, depending on i387 or SSE
 * @return size of FPU context structure
 */

inline unsigned
Fpu::state_size()
{
  return _state_size;
}

#line 174 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/fpu-ia32-ux.cpp"

/**
 * Return recommended FPU context alignment, depending on i387 or SSE
 * @return recommended FPU context alignment
 */

inline unsigned
Fpu::state_align()
{
  return _state_align;
}

#line 44 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/fpu-ia32.cpp"

/*
 * Save FPU or SSE state
 */

inline void
Fpu::save_state(Fpu_state *s)
{
  assert (s->state_buffer());

  // Both fxsave and fnsave are non-waiting instructions and thus
  // cannot cause exception #16 for pending FPU exceptions.

  switch (fpu.current()._variant)
    {
    case Variant_xsave:
      asm volatile("xsave (%2)" : : "a" (~0UL), "d" (~0UL), "r" (s->state_buffer()) : "memory");
      break;
    case Variant_fxsr:
      asm volatile ("fxsave (%0)" : : "r" (s->state_buffer()) : "memory");
      break;
    case Variant_fpu:
      asm volatile ("fnsave (%0)" : : "r" (s->state_buffer()) : "memory");
      break;
    }
}

#line 70 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/fpu-ia32.cpp"

/*
 * Restore a saved FPU or SSE state
 */


inline void
Fpu::restore_state(Fpu_state *s)
{
  assert (s->state_buffer());

  // Only fxrstor is a non-waiting instruction and thus
  // cannot cause exception #16 for pending FPU exceptions.
  Fpu &f = fpu.current();

  switch (f._variant)
    {
    case Variant_xsave:
      asm volatile ("xrstor (%2)" : : "a" (~0UL), "d" (~0UL), "r" (s->state_buffer()));
      break;
    case Variant_fxsr:
        {
#if !defined (CONFIG_WORKAROUND_AMD_FPU_LEAK)
          asm volatile ("fxrstor (%0)" : : "r" (s->state_buffer()));
#else
          /* The code below fixes a security leak on AMD CPUs, where
           * some registers of the FPU are not restored from the state_buffer
           * if there are no FPU exceptions pending. The old values, from the
           * last FPU owner, are therefore leaked to the new FPU owner.
           */
          static Mword int_dummy = 0;

          asm volatile(
              "fnstsw	%%ax    \n\t"   // save fpu flags in ax
              "ffree	%%st(7) \n\t"   // make enough space for the fildl
              "bt       $7,%%ax \n\t"   // test if exception bit is set
              "jnc      1f      \n\t"
              "fnclex           \n\t"   // clear it
              "1: fildl %1      \n\t"   // dummy load which sets the
              // affected to def. values
              "fxrstor (%0)     \n\t"   // finally restore the state
              : : "r" (s->state_buffer()), "m" (int_dummy) : "ax");
#endif
        }
      break;
    case Variant_fpu:
      // frstor is a waiting instruction and we must make sure no
      // FPU exceptions are pending here. We distinguish two cases:
      // 1) If we had a previous FPU owner, we called save_state before and
      //    invoked fnsave which re-initialized the FPU and cleared exceptions
      // 2) Otherwise we call fnclex instead to clear exceptions.

      if (!f.owner())
        asm volatile ("fnclex");

      asm volatile ("frstor (%0)" : : "r" (s->state_buffer()));
      break;
    }
}

#line 129 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/fpu-ia32.cpp"

/*
 * Mark the FPU busy. The next attempt to use it will yield a trap.
 */

inline void
Fpu::disable()
{
  Cpu::set_cr0(Cpu::get_cr0() | CR0_TS);
}

#line 139 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/fpu-ia32.cpp"

/*
 * Mark the FPU no longer busy. Subsequent FPU access won't trap.
 */

inline void
Fpu::enable()
{
  asm volatile ("clts");
}

#endif // fpu_h
