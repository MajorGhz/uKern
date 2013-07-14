// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "perf_cnt.h"
#include "perf_cnt_i.h"


#line 233 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
static inline void
clear_msr_range(Mword base, Mword n);

#line 240 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
//--------------------------------------------------------------------
// dummy

static Mword dummy_read_pmc();

#line 291 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
static Mword p5_read_pmc_0();

#line 293 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
static Mword p5_read_pmc_1();

#line 398 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
static Mword p6_read_pmc_0();

#line 399 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
static Mword p6_read_pmc_1();

#line 448 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
static Mword k7_read_pmc_0();

#line 449 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
static Mword k7_read_pmc_1();

#line 450 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
static Mword k7_read_pmc_2();

#line 451 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
static Mword k7_read_pmc_3();

#line 632 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
static Mword
p4_read_pmc();
#line 75 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

Perf_cnt::Perf_read_fn Perf_cnt::read_pmc[Perf_cnt::Max_slot] =
{ dummy_read_pmc, dummy_read_pmc };
#line 78 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
Perf_cnt::Perf_read_fn Perf_cnt::read_pmc_fn[Perf_cnt::Max_slot] =
{ dummy_read_pmc, dummy_read_pmc };
#line 80 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

Perf_cnt::Perf_read_fn *Perf_cnt::read_pmc_fns;
#line 82 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
Perf_cnt::Perf_event_type Perf_cnt::perf_event_type;
#line 83 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
Perf_cnt_arch *Perf_cnt::pcnt;
#line 84 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
char const *Perf_cnt::perf_type_str = "n/a";
#line 85 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

Mword Perf_cnt_arch::pmc_watchdog = (Mword)-1;
#line 87 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
Mword Perf_cnt_arch::pmc_loadcnt  = (Mword)-1;
#line 88 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
Signed64 Perf_cnt_arch::hold_watchdog;
#line 89 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
Perf_cnt_arch::Event Perf_cnt_arch::pmc_event[Perf_cnt::Max_slot];
#line 90 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
char  Perf_cnt_arch::pmc_alloc[Perf_cnt::Max_pmc];
#line 91 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

static Perf_cnt_p5 perf_cnt_p5 __attribute__ ((init_priority(PERF_CNT_INIT_PRIO)));
#line 93 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
static Perf_cnt_p6 perf_cnt_p6 __attribute__ ((init_priority(PERF_CNT_INIT_PRIO)));
#line 94 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
static Perf_cnt_k7 perf_cnt_k7 __attribute__ ((init_priority(PERF_CNT_INIT_PRIO)));
#line 95 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
static Perf_cnt_p4 perf_cnt_p4 __attribute__ ((init_priority(PERF_CNT_INIT_PRIO)));
#line 96 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
static Perf_cnt_ap perf_cnt_ap __attribute__ ((init_priority(PERF_CNT_INIT_PRIO)));
#line 97 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

enum
{
  Alloc_none            = 0,	// unallocated
  Alloc_perf            = 1,	// allocated as performance counter
  Alloc_watchdog        = 2,	// allocated for watchdog
};
#line 104 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

enum
{
  // Intel P5
  Msr_p5_cesr		= 0x11,
  Msr_p5_ctr0		= 0x12,
  Msr_p5_ctr1		= 0x13,
  P5_evntsel_user	= 0x00000080,
  P5_evntsel_kern	= 0x00000040,
  P5_evntsel_duration	= 0x00000100,

  // Intel P6/PII/PIII
  Msr_p6_perfctr0	= 0xC1,
  Msr_p6_evntsel0	= 0x186,
  P6_evntsel_enable	= 0x00400000,
  P6_evntsel_int	= 0x00100000,
  P6_evntsel_user	= 0x00010000,
  P6_evntsel_kern	= 0x00020000,
  P6_evntsel_edge	= 0x00040000,

  // AMD K7/K8
  Msr_k7_evntsel0	= 0xC0010000,
  Msr_k7_perfctr0	= 0xC0010004,
  K7_evntsel_enable	= P6_evntsel_enable,
  K7_evntsel_int	= P6_evntsel_int,
  K7_evntsel_user	= P6_evntsel_user,
  K7_evntsel_kern	= P6_evntsel_kern,
  K7_evntsel_edge	= P6_evntsel_edge,

  // Intel P4
  Msr_p4_misc_enable	= 0x1A0,
  Msr_p4_perfctr0	= 0x300,
  Msr_p4_bpu_counter0	= 0x300,
  Msr_p4_cccr0		= 0x360,
  Msr_p4_fsb_escr0	= 0x3A2,
  P4_escr_user		= (1<<2),
  P4_escr_kern		= (1<<3),
  Msr_p4_bpu_cccr0	= 0x360,
  P4_cccr_ovf		= (1<<31),
  P4_cccr_ovf_pmi	= (1<<26),
  P4_cccr_complement	= (1<<19),
  P4_cccr_compare	= (1<<18),
  P4_cccr_required	= (3<<16),
  P4_cccr_enable	= (1<<12),

  Msr_ap_perfctr0       = 0xC1,
  Msr_ap_evntsel0       = 0x186,
  AP_evntsel_enable     = P6_evntsel_enable,
  AP_evntsel_int        = P6_evntsel_int,
  AP_evntsel_user       = P6_evntsel_user,
  AP_evntsel_kern       = P6_evntsel_kern,
  AP_evntsel_edge       = P6_evntsel_edge,
};
#line 157 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

// -----------------------------------------------------------------------

enum
{
  Perfctr_x86_generic 		= 0,	/* any x86 with rdtsc */
  Perfctr_x86_intel_p5		= 1,	/* no rdpmc */
  Perfctr_x86_intel_p5mmx	= 2,
  Perfctr_x86_intel_p6		= 3,
  Perfctr_x86_intel_pii		= 4,
  Perfctr_x86_intel_piii	= 5,
  Perfctr_x86_intel_p4		= 11,	/* model 0 and 1 */
  Perfctr_x86_intel_p4m2	= 12,	/* model 2 */
  Perfctr_x86_intel_p4m3	= 16,	/* model 3 and above */
  Perfctr_x86_intel_pentm	= 14,
  Perfctr_x86_amd_k7		= 9,
  Perfctr_x86_amd_k8		= 13,
  Perfctr_x86_arch_perfmon      = 14,
};
#line 215 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

// The following functions are only available if the perfctr module
// is linked into the kernel. If not, all symbols perfctr_* are 0. */
//
// show all events
extern "C" void perfctr_set_cputype(unsigned)
  __attribute__((weak));
#line 222 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
extern "C" const struct perfctr_event* perfctr_lookup_event(unsigned,
							    unsigned*)
  __attribute__((weak));
#line 225 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
extern "C" const struct perfctr_event* perfctr_index_event(unsigned)
  __attribute__((weak));
#line 227 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
extern "C" unsigned perfctr_get_max_event(void)
  __attribute__((weak));
#line 229 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
extern "C" const struct perfctr_event_set *perfctr_cpu_event_set(unsigned)
  __attribute__((weak));
#line 295 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

static Perf_cnt::Perf_read_fn p5_read_pmc_fns[] =
{ &p5_read_pmc_0, &p5_read_pmc_1 };
#line 400 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

static Perf_cnt::Perf_read_fn p6_read_pmc_fns[] =
{ &p6_read_pmc_0, &p6_read_pmc_1 };
#line 452 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

static Perf_cnt::Perf_read_fn k7_read_pmc_fns[] =
{ &k7_read_pmc_0, &k7_read_pmc_1, &k7_read_pmc_2, &k7_read_pmc_3 };
#line 634 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

static Perf_cnt::Perf_read_fn p4_read_pmc_fns[] = { &p4_read_pmc };
#line 858 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

//--------------------------------------------------------------------

STATIC_INITIALIZE_P(Perf_cnt, PERF_CNT_INIT_PRIO);

#line 1015 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

inline void
Perf_cnt::set_pmc_fn(Mword slot, Mword nr)
{ read_pmc_fn[slot] = read_pmc_fns[nr]; }

#line 244 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

//--------------------------------------------------------------------
// Intel P5 (Pentium/Pentium MMX) has 2 performance counters. No overflow
// interrupt available. Some events are not symmtetric.

inline Perf_cnt_p5::Perf_cnt_p5()
  : Perf_cnt_arch(Msr_p5_cesr, Msr_p5_ctr0, 2, 0)
{}

#line 298 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"


//--------------------------------------------------------------------
// Intel P6 (PPro/PII/PIII) has 2 performance counters. Overflow interrupt
// is available. Some events are not symmtetric.

inline Perf_cnt_p6::Perf_cnt_p6()
  : Perf_cnt_arch(Msr_p6_evntsel0, Msr_p6_perfctr0, 2, 1)
{}

#line 403 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"


//--------------------------------------------------------------------
// AMD K7 (Athlon, K8=Athlon64) has 4 performance counters. All events
// seem to be symmetric. Overflow interrupts available.

inline Perf_cnt_k7::Perf_cnt_k7()
  : Perf_cnt_p6(Msr_k7_evntsel0, Msr_k7_perfctr0, 4, 1)
{}

#line 502 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"


//--------------------------------------------------------------------
// Intel P4

inline Perf_cnt_p4::Perf_cnt_p4()
  : Perf_cnt_arch(Msr_p4_bpu_cccr0, Msr_p4_bpu_counter0, 2, 1)
{}

#line 510 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"


inline Mword
Perf_cnt_p4::escr_event_select(Mword n)
{ return n << 25; }

#line 515 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"


inline Mword
Perf_cnt_p4::escr_event_mask(Mword n)
{ return n << 9; }

#line 520 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"


inline Mword
Perf_cnt_p4::cccr_threshold(Mword n)
{ return n << 20; }

#line 525 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"


inline Mword
Perf_cnt_p4::cccr_escr_select(Mword n)
{ return n << 13; }

#line 455 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"


//--------------------------------------------------------------------
// Arch Perfmon. Intel Core architecture

inline Perf_cnt_ap::Perf_cnt_ap()
  : Perf_cnt_p6(Msr_ap_evntsel0, Msr_ap_perfctr0, 2, 1)
{
  Unsigned32 eax, ebx, ecx;
  Cpu::boot_cpu()->arch_perfmon_info(&eax, &ebx, &ecx);
  _nr_regs = (eax & 0x0000ff00) >> 8;
}

#line 231 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"


static inline void
clear_msr_range(Mword base, Mword n)
{
  for (Mword i=0; i<n; i++)
    Cpu::wrmsr(0, base+i);
}

#line 239 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

//--------------------------------------------------------------------
// dummy

static Mword dummy_read_pmc() { return 0; }

#line 252 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

FIASCO_INIT_CPU
int
Perf_cnt_p5::init()
{
  Cpu::wrmsr(0, Msr_p5_cesr); // disable both counters
  return 1;
}

#line 260 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

void
Perf_cnt_p5::set_pmc_event(Mword slot)
{
  Unsigned64 msr;
  Mword event;
    
  event = pmc_event[slot].evnt;
  if (pmc_event[slot].user)
    event += P5_evntsel_user;
  if (pmc_event[slot].kern)
    event += P5_evntsel_kern;
  if (pmc_event[slot].kern)
    event += P5_evntsel_kern;
  if (!pmc_event[slot].edge)
    event += P5_evntsel_duration;

  msr = Cpu::rdmsr(Msr_p5_cesr);
  if (pmc_event[slot].pmc == 0)
    {
      msr &= 0xffff0000;
      msr |= event;
    }
  else
    {
      msr &= 0x0000ffff;
      msr |= (event << 16);
    }
  Cpu::wrmsr(event, Msr_p5_cesr);
}

#line 290 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

static Mword p5_read_pmc_0()
{ return Cpu::rdmsr(Msr_p5_ctr0); }

#line 293 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
static Mword p5_read_pmc_1()
{ return Cpu::rdmsr(Msr_p5_ctr1); }

#line 307 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"


Perf_cnt_p6::Perf_cnt_p6(Mword sel_reg0, Mword ctr_reg0, 
      			 Mword nr_regs, Mword watchdog)
  : Perf_cnt_arch(sel_reg0, ctr_reg0, nr_regs, watchdog)
{}

#line 313 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

FIASCO_INIT_CPU
int
Perf_cnt_p6::init()
{
  for (Mword i=0; i<_nr_regs; i++)
    {
      Cpu::wrmsr(0, _sel_reg0+i);
      Cpu::wrmsr(0, _ctr_reg0+i);
    }
  return 1;
}

#line 325 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

void
Perf_cnt_p6::set_pmc_event(Mword slot)
{
  Mword event;

  event = pmc_event[slot].evnt;
  if (pmc_event[slot].user)
    event += P6_evntsel_user;
  if (pmc_event[slot].kern)
    event += P6_evntsel_kern;
  if (pmc_event[slot].edge)
    event += P6_evntsel_edge;

  // select event
  Cpu::wrmsr(event, _sel_reg0+pmc_event[slot].pmc);
}

#line 342 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

void
Perf_cnt_p6::start_pmc(Mword /*reg_nr*/)
{
  Unsigned64 msr;

  msr = Cpu::rdmsr(_sel_reg0);
  msr |= P6_evntsel_enable;  // enable both!! counters
  Cpu::wrmsr(msr, _sel_reg0);
}

#line 352 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

void
Perf_cnt_p6::init_watchdog()
{
  Unsigned64 msr;

  msr = P6_evntsel_int  // Int enable: enable interrupt on overflow
      | P6_evntsel_kern // Monitor kernel-level events
      | P6_evntsel_user // Monitor user-level events
      | 0x79;           // #clocks CPU is not halted
  Cpu::wrmsr(msr, _sel_reg0+pmc_watchdog);
}

#line 364 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

void
Perf_cnt_p6::init_loadcnt()
{
  Unsigned64 msr;

  msr = P6_evntsel_kern // Monitor kernel-level events
      | P6_evntsel_user // Monitor user-level events
      | 0x79;           // #clocks CPU is not halted
  Cpu::wrmsr(msr, _sel_reg0+pmc_loadcnt);

  printf("Load counter initialized (read with rdpmc(0x%02lX))\n", pmc_loadcnt);
}

#line 377 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

void
Perf_cnt_p6::start_watchdog()
{
  Unsigned64 msr;

  msr = Cpu::rdmsr(_sel_reg0+pmc_watchdog);
  msr |= P6_evntsel_int; // Int enable: enable interrupt on overflow
  Cpu::wrmsr(msr, _sel_reg0+pmc_watchdog);
}

#line 387 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

void
Perf_cnt_p6::stop_watchdog()
{
  Unsigned64 msr;

  msr = Cpu::rdmsr(_sel_reg0+pmc_watchdog);
  msr &= ~P6_evntsel_int; // Int enable: enable interrupt on overflow
  Cpu::wrmsr(msr, _sel_reg0+pmc_watchdog);
}

#line 397 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

static Mword p6_read_pmc_0() { return Cpu::rdpmc(0, 0xC1); }

#line 399 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
static Mword p6_read_pmc_1() { return Cpu::rdpmc(1, 0xC2); }

#line 412 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

void
Perf_cnt_k7::start_pmc(Mword reg_nr)
{
  Unsigned64 msr;

  msr = Cpu::rdmsr(_sel_reg0+reg_nr);
  msr |= K7_evntsel_enable;
  Cpu::wrmsr(msr, _sel_reg0+reg_nr);
}

#line 422 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

void
Perf_cnt_k7::init_watchdog()
{
  Unsigned64 msr;

  msr = K7_evntsel_int  // Int enable: enable interrupt on overflow
      | K7_evntsel_kern // Monitor kernel-level events
      | K7_evntsel_user // Monitor user-level events
      | 0x76;           // #clocks CPU is running
  Cpu::wrmsr(msr, _sel_reg0+pmc_watchdog);
}

#line 434 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

void
Perf_cnt_k7::init_loadcnt()
{
  Unsigned64 msr;

  msr = K7_evntsel_kern // Monitor kernel-level events
      | K7_evntsel_user // Monitor user-level events
      | 0x76;           // #clocks CPU is running
  Cpu::wrmsr(msr, _sel_reg0+pmc_loadcnt);

  printf("Load counter initialized (read with rdpmc(0x%02lX))\n", pmc_loadcnt);
}

#line 447 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

static Mword k7_read_pmc_0() { return Cpu::rdpmc(0, 0xC0010004); }

#line 449 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
static Mword k7_read_pmc_1() { return Cpu::rdpmc(1, 0xC0010005); }

#line 450 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
static Mword k7_read_pmc_2() { return Cpu::rdpmc(2, 0xC0010006); }

#line 451 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
static Mword k7_read_pmc_3() { return Cpu::rdpmc(3, 0xC0010007); }

#line 467 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

void
Perf_cnt_ap::start_pmc(Mword reg_nr)
{
  Unsigned64 msr;

  msr = Cpu::rdmsr(_sel_reg0 + reg_nr);
  msr |= AP_evntsel_enable;
  Cpu::wrmsr(msr, _sel_reg0 + reg_nr);
}

#line 477 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

void
Perf_cnt_ap::init_watchdog()
{
  Unsigned64 msr;

  msr = AP_evntsel_int    // Int enable: enable interrupt on overflow
        | AP_evntsel_kern // Monitor kernel-level events
        | AP_evntsel_user // Monitor user-level events
        | 0x3C;           // #clocks CPU is running
  Cpu::wrmsr(msr, _sel_reg0 + pmc_watchdog);
}

#line 489 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

void
Perf_cnt_ap::init_loadcnt()
{
  Unsigned64 msr;

  msr = AP_evntsel_kern   // Monitor kernel-level events
        | AP_evntsel_user // Monitor user-level events
        | 0x3C;           // #clocks CPU is running
  Cpu::wrmsr(msr, _sel_reg0 + pmc_loadcnt);

  printf("Load counter initialized (read with rdpmc(0x%02lX))\n", pmc_loadcnt);
}

#line 530 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

FIASCO_INIT_CPU
int
Perf_cnt_p4::init()
{
  Unsigned32 misc_enable = Cpu::rdmsr(Msr_p4_misc_enable);

  // performance monitoring available?
  if (!(misc_enable & (1<<7)))
    return 0;

  // disable precise event based sampling
  if (!(misc_enable & (1<<12)))
    clear_msr_range(0x3F1, 2);

  // ensure sane state of performance counter registers
  clear_msr_range(0x3A0, 26);
  if (Cpu::boot_cpu()->model() <= 2)
    clear_msr_range(0x3BA, 2);
  clear_msr_range(0x3BC, 3);
  clear_msr_range(0x3C0, 6);
  clear_msr_range(0x3C8, 6);
  clear_msr_range(0x3E0, 2);
  clear_msr_range(Msr_p4_cccr0, 18);
  clear_msr_range(Msr_p4_perfctr0, 18);

  return 1;
}

#line 558 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

void
Perf_cnt_p4::set_pmc_event(Mword /*slot*/)
{}

#line 562 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

void
Perf_cnt_p4::start_pmc(Mword reg_nr)
{
  Unsigned64 msr;

  msr = Cpu::rdmsr(Msr_p4_bpu_cccr0 + reg_nr);
  msr |= P4_cccr_enable;
  Cpu::wrmsr(msr, Msr_p4_bpu_cccr0 + reg_nr);
}

#line 572 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

void
Perf_cnt_p4::init_watchdog()
{
  Unsigned64 msr;
  
  msr = escr_event_select(0x13) // global power events
      | escr_event_mask(1)      // the processor is active (non-halted)
      | P4_escr_kern            // Monitor kernel-level events
      | P4_escr_user;           // Monitor user-level events
  Cpu::wrmsr(msr, Msr_p4_fsb_escr0);

  msr = P4_cccr_ovf_pmi         // performance monitor interrupt on overflow
      | P4_cccr_required	// must be set
      | cccr_escr_select(6);    // select ESCR to select events to be counted
  Cpu::wrmsr(msr, Msr_p4_bpu_cccr0 + pmc_watchdog);
}

#line 589 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

void
Perf_cnt_p4::init_loadcnt()
{
  Unsigned64 msr;
  
  msr = escr_event_select(0x13) // global power events
      | escr_event_mask(1)      // the processor is active (non-halted)
      | P4_escr_kern            // Monitor kernel-level events
      | P4_escr_user;           // Monitor user-level events
  Cpu::wrmsr(msr, Msr_p4_fsb_escr0);

  msr = P4_cccr_required	// must be set
      | cccr_escr_select(6);    // select ESCR to select events to be counted

  Cpu::wrmsr(msr, Msr_p4_bpu_cccr0 + pmc_loadcnt);

  printf("Load counter initialized (read with rdpmc(0x%02lX))\n", 
          pmc_loadcnt + 0);
}

#line 609 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

void
Perf_cnt_p4::start_watchdog()
{
  Unsigned64 msr;

  msr = Cpu::rdmsr(Msr_p4_bpu_cccr0);
  msr |= P4_cccr_ovf_pmi | P4_cccr_enable; // Int enable, Ctr enable
  msr &= ~P4_cccr_ovf;                     // clear Overflow
  Cpu::wrmsr(msr, Msr_p4_bpu_cccr0 + pmc_watchdog);
}

#line 620 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

void
Perf_cnt_p4::stop_watchdog()
{
  Unsigned64 msr;

  msr = Cpu::rdmsr(Msr_p4_bpu_cccr0);
  msr &= ~(P4_cccr_ovf_pmi | P4_cccr_enable); // Int disable, Ctr disable
  Cpu::wrmsr(msr, Msr_p4_bpu_cccr0 + pmc_watchdog);
}

#line 630 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"


static Mword
p4_read_pmc() { return 0; }

#line 665 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

void
Perf_cnt_arch::alloc_watchdog()
{
  if (!_watchdog)
    panic("Watchdog not available");

  for (Mword pmc=0; pmc<_nr_regs; pmc++)
    if (pmc_alloc[pmc] == Alloc_none)
      {
	pmc_alloc[pmc] = Alloc_watchdog;
	pmc_watchdog   = pmc;
	return;
      }

  panic("No performance counter available for watchdog");
}

#line 682 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

void
Perf_cnt_arch::alloc_loadcnt()
{
  if (pmc_alloc[0] == Alloc_watchdog)
    {
      // allocate the watchdog counter
      pmc_alloc[0] = Alloc_perf;
      pmc_loadcnt  = 0;
      // move the watchdog to another counter
      pmc_watchdog = (Mword)-1;
      alloc_watchdog();
      return;
    }

  if (pmc_alloc[0] == Alloc_none)
    {
      pmc_alloc[0] = Alloc_perf;
      pmc_loadcnt  = 0;
      return;
    }

  panic("No performance counter available for loadcounter");
}

#line 706 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

// allocate a performance counter according to bitmask (some events depend
// on specific counters)

int
Perf_cnt_arch::alloc_pmc(Mword slot, Mword bitmask)
{
  // free previous allocated counter
  Mword pmc = pmc_event[slot].pmc;
  if (pmc != (Mword)-1 && pmc_alloc[pmc] == Alloc_perf)
    {
      pmc_event[slot].pmc = (Mword)-1;
      pmc_alloc[pmc]      = Alloc_none;
    }

  // search counter according to bitmask
  for (pmc=0; pmc<_nr_regs; pmc++)
    if ((pmc_alloc[pmc] == Alloc_none) && (bitmask & (1<<pmc)))
      {
	pmc_event[slot].pmc = pmc;
	pmc_alloc[pmc]      = Alloc_perf;
	Perf_cnt::set_pmc_fn(slot, pmc);
	return 1;
      }

  // did not found an appropriate free counter (restricted by bitmask) so try
  // to re-assign the watchdog because the watchdog usually uses a more general
  // counter with no restrictions
  if (watchdog_allocated() && (bitmask & (1<<pmc_watchdog)))
    {
      // allocate the watchdog counter
      pmc_event[slot].pmc     = pmc_watchdog;
      pmc_alloc[pmc_watchdog] = Alloc_perf;
      Perf_cnt::set_pmc_fn(slot, pmc_watchdog);
      // move the watchdog to another counter
      pmc_watchdog            = (Mword)-1;
      alloc_watchdog();
      return 1;
    }

  return 0;
}

#line 748 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"


void
Perf_cnt_arch::clear_pmc(Mword reg_nr)
{ Cpu::wrmsr(0, _ctr_reg0+reg_nr); }

#line 753 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"


void
Perf_cnt_arch::mode(Mword slot, const char **mode, 
		    Mword *event, Mword *user, Mword *kern, Mword *edge)
{
  static const char * const mode_str[2][2][2] =
    { { { "off", "off" }, { "d.K",   "e.K"   } },
      { { "d.U", "e.U" }, { "d.K+U", "e.K+U" } } };

  *mode    = mode_str[(int)pmc_event[slot].user]
		     [(int)pmc_event[slot].kern]
		     [(int)pmc_event[slot].edge];
  *event   = pmc_event[slot].evnt;
  *user    = pmc_event[slot].user;
  *kern    = pmc_event[slot].kern;
  *edge    = pmc_event[slot].edge;
}

#line 771 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"


void
Perf_cnt_arch::setup_pmc(Mword slot, Mword bitmask, 
			 Mword event, Mword user, Mword kern, Mword edge)
{
  if (alloc_pmc(slot, bitmask))
    {
      pmc_event[slot].user    = user;
      pmc_event[slot].kern    = kern;
      pmc_event[slot].edge    = edge;
      pmc_event[slot].evnt    = event;
      pmc_event[slot].bitmask = bitmask;
      set_pmc_event(slot);
      clear_pmc(pmc_event[slot].pmc);
      start_pmc(pmc_event[slot].pmc);
    }
}

#line 789 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"


void
Perf_cnt_arch::start_pmc(Mword /*reg_nr*/)
{
  // nothing to do per default
}

#line 802 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"


void
Perf_cnt_arch::setup_watchdog(Mword timeout)
{
  alloc_watchdog();
  if (watchdog_allocated())
    {
      hold_watchdog = ((Signed64)((Cpu::boot_cpu()->frequency() >> 16) * timeout)) << 16;
      // The maximum value a performance counter register can be written to
      // is 0x7ffffffff. The 31st bit is extracted to the bits 32-39 (see 
      // "IA-32 Intel Architecture Software Developer's Manual. Volume 3: 
      // Programming Guide" section 14.10.2: PerfCtr0 and PerfCtr1 MSRs.
      if (hold_watchdog > 0x7fffffff)
	hold_watchdog = 0x7fffffff;
      hold_watchdog = -hold_watchdog;
      init_watchdog();
      touch_watchdog();
      start_watchdog();
      start_pmc(pmc_watchdog);
    }
}

#line 824 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"


void
Perf_cnt_arch::setup_loadcnt()
{
  alloc_loadcnt();
  if (loadcnt_allocated())
    {
      init_loadcnt();
      start_pmc(pmc_loadcnt);
    }
}

#line 836 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"


void
Perf_cnt_arch::init_watchdog()
{} // no watchdog per default

#line 841 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"


void
Perf_cnt_arch::init_loadcnt()
{ panic("Cannot initialize load counter"); }

#line 846 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

// start watchdog (enable generation of overflow interrupt)

void
Perf_cnt_arch::start_watchdog()
{} // no watchdog per default

#line 852 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

// stop watchdog (disable generation of overflow interrupt)

void
Perf_cnt_arch::stop_watchdog()
{} // no watchdog per default

#line 862 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

// basic perfcounter detection
FIASCO_INIT_CPU
void
Perf_cnt::init()
{
  Cpu const &cpu = *Cpu::boot_cpu();
  Mword perfctr_type = Perfctr_x86_generic;
  Unsigned32 eax, ebx, ecx;

  for (Mword i=0; i<Perf_cnt::Max_slot; i++)
    read_pmc_fn[i] = dummy_read_pmc;

  if (cpu.tsc() && cpu.can_wrmsr())
    {
      cpu.arch_perfmon_info(&eax, &ebx, &ecx);
      if ((eax & 0xff) && (((eax>>8) & 0xff) > 1))
        {
          perfctr_type  = Perfctr_x86_arch_perfmon;
          perf_type_str = "PA";
          read_pmc_fns  = p6_read_pmc_fns;
          pcnt          = &perf_cnt_ap;
        }
      if (perfctr_type == Perfctr_x86_generic)
        {
          if (cpu.vendor() == cpu.Vendor_intel)
            {
              // Intel
              switch (cpu.family())
                {
                case 5:
                perf_event_type  = P5;
                if (cpu.local_features() & Cpu::Lf_rdpmc)
                  {
                    perfctr_type  = Perfctr_x86_intel_p5mmx;
                    perf_type_str = "P5MMX";
                    read_pmc_fns  = p6_read_pmc_fns;
                  }
                else
                  {
                    perfctr_type  = Perfctr_x86_intel_p5;
                    perf_type_str = "P5";
                    read_pmc_fns  = p5_read_pmc_fns;
                  }
                pcnt = &perf_cnt_p5;
                break;

                case 6:
                  perf_event_type = P6;
                  if (cpu.model() == 9 || cpu.model() == 13)
                    {
                      perfctr_type  = Perfctr_x86_intel_pentm;
                      perf_type_str = "PntM";
                    }
                  else if (cpu.model() >= 7)
                    {
                      perfctr_type  = Perfctr_x86_intel_piii;
                      perf_type_str = "PIII";
                    }
                  else if (cpu.model() >= 3)
                    {
                      perfctr_type  = Perfctr_x86_intel_pii;
                      perf_type_str = "PII";
                    }
                  else
                    {
                      perfctr_type  = Perfctr_x86_intel_p6;
                      perf_type_str = "PPro";
                    }
                  read_pmc_fns = p6_read_pmc_fns;
                  pcnt = &perf_cnt_p6;
                  break;

                case 15:
                  perf_event_type = P4;
                  if (cpu.model() >= 3)
                    {
                      perfctr_type = Perfctr_x86_intel_p4m3;
                      perf_type_str = "P4M3";
                    }
                  else if (cpu.model() >= 2)
                    {
                      perfctr_type = Perfctr_x86_intel_p4m2;
                      perf_type_str = "P4M2";
                    }
                  else
                    {
                      perfctr_type = Perfctr_x86_intel_p4;
                      perf_type_str = "P4";
                    }
                  read_pmc_fns = p4_read_pmc_fns;
                  pcnt = &perf_cnt_p4;
                  break;
                }
            }
          else if (cpu.vendor() == Cpu::Vendor_amd)
            {
              // AMD
              switch (cpu.family())
                {
                case 6:
                case 15:
                case 16:
                  if (cpu.family() == 15)
                    {
                      perf_type_str = "K8";
                      perfctr_type  = Perfctr_x86_amd_k8;
                    }
                  else
                    {
                      perf_type_str = "K7";
                      perfctr_type  = Perfctr_x86_amd_k7;
                    }
                  perf_event_type = P6;
                  read_pmc_fns    = k7_read_pmc_fns;
                  pcnt            = &perf_cnt_k7;
                  break;
                }
            }
        }

      // set PCE-Flag in CR4 to enable read of performace measurement
      // counters in usermode. PMC were introduced in Pentium MMX and
      // PPro processors.
      if (cpu.local_features() & Cpu::Lf_rdpmc)
        cpu.enable_rdpmc();
    }

  if (pcnt && !pcnt->init())
    {
      perfctr_type = Perfctr_x86_generic;
      pcnt         = 0;  // init failed, no performance counters available
    }

  if (perfctr_cpu_event_set != 0 && perfctr_cpu_event_set(perfctr_type) == 0)
    {
      perfctr_type = Perfctr_x86_generic;
      pcnt         = 0;  // init failed, no performance counters available
    }

  // tell perflib the cpu type
  if (perfctr_set_cputype != 0)
    perfctr_set_cputype(perfctr_type);

}

#line 1075 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

// set performance counter counting the selected event in slot #slot

int
Perf_cnt::setup_pmc(Mword slot, Mword event, Mword user, Mword kern, Mword edge)
{
  if (!pcnt)
    return 0;

  unsigned nr, evntsel;
  Mword bitmask, unit_mask;
  const struct perfctr_event *pe = 0;

  split_event(event, &evntsel, &unit_mask);
  if (perfctr_lookup_event != 0)
    pe = perfctr_lookup_event(evntsel, &nr);
  bitmask = pe ? pe->counters_set : 0xffff;
  pcnt->setup_pmc(slot, bitmask, event, user, kern, edge);
  Tb_entry::set_rdcnt(slot, (kern | user) ? read_pmc_fn[slot] : 0);
  return 1;
}

#line 1096 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

// return current selected event for a slot #slot

int
Perf_cnt::mode(Mword slot, const char **mode, const char **name, 
	       Mword *event, Mword *user, Mword *kern, Mword *edge)
{
  if (!perf_type() || !pcnt)
    {
      *mode  = "off";
      *event = *user = *kern  = 0;
      return 0;
    }

  unsigned nr, evntsel;
  Mword unit_mask;
  const struct perfctr_event *pe = 0;

  pcnt->mode(slot, mode, event, user, kern, edge);
  split_event(*event, &evntsel, &unit_mask);
  if (perfctr_lookup_event != 0)
    pe = perfctr_lookup_event(evntsel, &nr);
  *name  = pe ? pe->name : "";
  return 1;
}

#line 1121 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

Mword
Perf_cnt::get_max_perf_event()
{ return (perfctr_get_max_event != 0) ? perfctr_get_max_event() : 0; }

#line 1125 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

void
Perf_cnt::get_perf_event(Mword nr, unsigned *evntsel, 
			 const char **name, const char **desc)
{
  const struct perfctr_event *pe = 0;

  if (perfctr_index_event != 0)
    pe = perfctr_index_event(nr);

  *name    = pe ? pe->name        : 0;
  *desc    = pe ? pe->description : 0;
  *evntsel = pe ? pe->evntsel     : 0;
}

#line 1139 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

Mword
Perf_cnt::lookup_event(unsigned evntsel)
{
  unsigned nr;

  if (perfctr_lookup_event != 0 && perfctr_lookup_event(evntsel, &nr) != 0)
    return nr;
  return (Mword)-1;
}

#line 1149 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

void
Perf_cnt::get_unit_mask(Mword nr, Unit_mask_type *type,
			Mword *default_value, Mword *nvalues)
{
  const struct perfctr_event *event = 0;
  
  if (perfctr_index_event != 0) 
    event = perfctr_index_event(nr);

  *type = None;
  if (event && event->unit_mask)
    {
      *default_value = event->unit_mask->default_value;
      switch (event->unit_mask->type)
	{
	case perfctr_um_type_fixed:	*type = Fixed; break;
	case perfctr_um_type_exclusive:	*type = Exclusive; break;
	case perfctr_um_type_bitmask:	*type = Bitmask; break;
	}
      *nvalues = event->unit_mask->nvalues;
    }
}

#line 1172 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

void
Perf_cnt::get_unit_mask_entry(Mword nr, Mword idx, 
			      Mword *value, const char **desc)
{
  const struct perfctr_event *event = 0;
  
  if (perfctr_index_event != 0)
    event = perfctr_index_event(nr);

  *value = 0;
  *desc  = 0;
  if (event && event->unit_mask && (idx < event->unit_mask->nvalues))
    {
      *value = event->unit_mask->values[idx].value;
      *desc  = event->unit_mask->values[idx].description;
    }
}

#line 1190 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

/** Split event into event selector and unit mask (depending on perftype). */

void
Perf_cnt::split_event(Mword event, unsigned *evntsel, Mword *unit_mask)
{
  switch (perf_event_type)
    {
    case P5:
      *evntsel   = event;
      *unit_mask = 0;
      break;
    case P6:
      *evntsel   =  event & 0x000000ff;
      *unit_mask = (event & 0x0000ff00) >> 8;
      break;
    case P4:
    default:
      *evntsel   = 0;
      *unit_mask = 0;
      break;
    }
}

#line 1213 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

/** Combine event from selector and unit mask. */

void
Perf_cnt::combine_event(Mword evntsel, Mword unit_mask, Mword *event)
{
  switch (perf_event_type)
    {
    case P5:
      *event = evntsel;
      break;
    case P6:
      *event = (evntsel & 0x000000ff) + ((unit_mask & 0x000000ff) << 8);
      break;
    case P4:
      break;
    }
}
