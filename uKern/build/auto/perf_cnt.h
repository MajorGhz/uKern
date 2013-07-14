// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef perf_cnt_h
#define perf_cnt_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/perf_cnt.cpp"

#include "types.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

#include "cpu.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
#include "types.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/perf_cnt.cpp"

class Perf_cnt_arch;
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/perf_cnt.cpp"

class Perf_cnt
{
public:
  enum {
    Max_slot = 2,
    Max_pmc  = 4,
  };

  enum Unit_mask_type
    { None, Fixed, Exclusive, Bitmask, };

  typedef Mword (*Perf_read_fn)();

#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
private:

public:
  enum Perf_event_type
    { P5, P6, P4, };

  static Perf_read_fn read_pmc[Max_slot];
  virtual void init_loadcnt() = 0;
  virtual void start_pmc(Mword) = 0;

  static Perf_cnt_arch *pcnt;

private:
  static Perf_read_fn *read_pmc_fns;
  static Perf_read_fn read_pmc_fn[Max_slot];
  static char const *perf_type_str;
  static Perf_event_type perf_event_type;

public:  
#line 863 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  // basic perfcounter detection
  static FIASCO_INIT_CPU
  void
  init();
  
#line 1008 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  static inline void FIASCO_INIT_CPU
  init_ap();
  
#line 1016 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  static inline void
  set_pmc_fn(Mword slot, Mword nr);
  
#line 1020 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  // watchdog supported by performance counter architecture?
  
  static inline int
  have_watchdog();
  
#line 1026 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  // setup watchdog function with timeout in seconds
  
  static inline void
  setup_watchdog(Mword timeout);
  
#line 1036 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  static inline void
  setup_loadcnt();
  
#line 1044 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  static inline void
  start_watchdog();
  
#line 1055 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  static inline void
  stop_watchdog();
  
#line 1063 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  static inline void
  touch_watchdog();
  
#line 1070 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  // return human-readable type of performance counters
  
  static inline char const *
  perf_type();
  
#line 1076 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  // set performance counter counting the selected event in slot #slot
  
  static int
  setup_pmc(Mword slot, Mword event, Mword user, Mword kern, Mword edge);
  
#line 1097 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  // return current selected event for a slot #slot
  
  static int
  mode(Mword slot, const char **mode, const char **name, 
  	       Mword *event, Mword *user, Mword *kern, Mword *edge);
  
#line 1122 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  static Mword
  get_max_perf_event();
  
#line 1126 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  static void
  get_perf_event(Mword nr, unsigned *evntsel, 
  			 const char **name, const char **desc);
  
#line 1140 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  static Mword
  lookup_event(unsigned evntsel);
  
#line 1150 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  static void
  get_unit_mask(Mword nr, Unit_mask_type *type,
  			Mword *default_value, Mword *nvalues);
  
#line 1173 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  static void
  get_unit_mask_entry(Mword nr, Mword idx, 
  			      Mword *value, const char **desc);
  
#line 1191 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  /** Split event into event selector and unit mask (depending on perftype). */
  
  static void
  split_event(Mword event, unsigned *evntsel, Mword *unit_mask);
  
#line 1214 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  /** Combine event from selector and unit mask. */
  
  static void
  combine_event(Mword evntsel, Mword unit_mask, Mword *event);
};
#line 24 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

class Perf_cnt_arch
{
public:
  // basic initialization
  virtual int  init() = 0;

  // set event the counter should count
  virtual void set_pmc_event(Mword slot) = 0;

  inline void touch_watchdog()
    { Cpu::wrmsr(hold_watchdog, _ctr_reg0+pmc_watchdog); }

protected:
  Mword _nr_regs;
  Mword _sel_reg0;
  Mword _ctr_reg0;
  Mword _watchdog;

  struct Event
  {
    char  user;		// 1=count in user mode
    char  kern;		// 1=count in kernel mode
    char  edge;		// 1=count edge / 0=count duration
    Mword pmc;		// # of performance counter
    Mword bitmask;	// counter bitmask
    Mword evnt;		// event selector
  };

  static Mword    pmc_watchdog;                   // # perfcounter of watchdog
  static Mword    pmc_loadcnt;                    // # perfcounter of loadcnt
  static Signed64 hold_watchdog;
  static Event    pmc_event[Perf_cnt::Max_slot];  // index is slot number
  static char     pmc_alloc[Perf_cnt::Max_pmc];   // index is # of perfcounter

public:  
#line 657 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  inline Mword
  watchdog_allocated();
  
#line 662 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  inline Mword
  loadcnt_allocated();
  
#line 750 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  virtual void
  clear_pmc(Mword reg_nr);
  
#line 755 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  void
  mode(Mword slot, const char **mode, 
  		    Mword *event, Mword *user, Mword *kern, Mword *edge);
  
#line 773 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  void
  setup_pmc(Mword slot, Mword bitmask, 
  			 Mword event, Mword user, Mword kern, Mword edge);
  
#line 791 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  virtual void
  start_pmc(Mword /*reg_nr*/);
  
#line 797 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  // watchdog supported by performance counter architecture?
  
  inline int
  have_watchdog();
  
#line 804 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  void
  setup_watchdog(Mword timeout);
  
#line 826 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  void
  setup_loadcnt();
  
#line 838 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  virtual void
  init_watchdog();
  
#line 843 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  virtual void
  init_loadcnt();
  
#line 847 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  // start watchdog (enable generation of overflow interrupt)
  
  virtual void
  start_watchdog();
  
#line 853 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  // stop watchdog (disable generation of overflow interrupt)
  
  virtual void
  stop_watchdog();

protected:  
#line 638 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  //--------------------------------------------------------------------
  
  
  inline Perf_cnt_arch(Mword sel_reg0, Mword ctr_reg0, 
  			     Mword nr_regs, Mword watchdog);

private:  
#line 666 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  void
  alloc_watchdog();
  
#line 683 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  void
  alloc_loadcnt();
  
#line 707 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  // allocate a performance counter according to bitmask (some events depend
  // on specific counters)
  
  int
  alloc_pmc(Mword slot, Mword bitmask);
};
#line 59 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

class Perf_cnt_p5 : public Perf_cnt_arch {
public:  
#line 245 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  //--------------------------------------------------------------------
  // Intel P5 (Pentium/Pentium MMX) has 2 performance counters. No overflow
  // interrupt available. Some events are not symmtetric.
  
  inline Perf_cnt_p5();

private:  
#line 253 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  FIASCO_INIT_CPU
  int
  init();
  
#line 261 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  void
  set_pmc_event(Mword slot);
};
#line 61 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
class Perf_cnt_p6 : public Perf_cnt_arch {
public:  
#line 300 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  //--------------------------------------------------------------------
  // Intel P6 (PPro/PII/PIII) has 2 performance counters. Overflow interrupt
  // is available. Some events are not symmtetric.
  
  inline Perf_cnt_p6();

protected:  
#line 309 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  Perf_cnt_p6(Mword sel_reg0, Mword ctr_reg0, 
        			 Mword nr_regs, Mword watchdog);

private:  
#line 314 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  FIASCO_INIT_CPU
  int
  init();
  
#line 326 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  void
  set_pmc_event(Mword slot);
  
#line 343 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  void
  start_pmc(Mword /*reg_nr*/);
  
#line 353 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  void
  init_watchdog();
  
#line 365 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  void
  init_loadcnt();
  
#line 378 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  void
  start_watchdog();
  
#line 388 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  void
  stop_watchdog();
};
#line 62 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
class Perf_cnt_k7 : public Perf_cnt_p6   {
public:  
#line 405 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  //--------------------------------------------------------------------
  // AMD K7 (Athlon, K8=Athlon64) has 4 performance counters. All events
  // seem to be symmetric. Overflow interrupts available.
  
  inline Perf_cnt_k7();

private:  
#line 413 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  void
  start_pmc(Mword reg_nr);
  
#line 423 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  void
  init_watchdog();
  
#line 435 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  void
  init_loadcnt();
};
#line 63 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
class Perf_cnt_p4 : public Perf_cnt_arch {
public:  
#line 504 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  //--------------------------------------------------------------------
  // Intel P4
  
  inline Perf_cnt_p4();

private:  
#line 512 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  static inline Mword
  escr_event_select(Mword n);
  
#line 517 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  static inline Mword
  escr_event_mask(Mword n);
  
#line 522 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  static inline Mword
  cccr_threshold(Mword n);
  
#line 527 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  static inline Mword
  cccr_escr_select(Mword n);
  
#line 531 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  FIASCO_INIT_CPU
  int
  init();
  
#line 559 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  void
  set_pmc_event(Mword /*slot*/);
  
#line 563 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  void
  start_pmc(Mword reg_nr);
  
#line 573 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  void
  init_watchdog();
  
#line 590 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  void
  init_loadcnt();
  
#line 610 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  void
  start_watchdog();
  
#line 621 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  void
  stop_watchdog();
};
#line 64 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
class Perf_cnt_ap : public Perf_cnt_p6   {
public:  
#line 457 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  //--------------------------------------------------------------------
  // Arch Perfmon. Intel Core architecture
  
  inline Perf_cnt_ap();

private:  
#line 468 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  void
  start_pmc(Mword reg_nr);
  
#line 478 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  void
  init_watchdog();
  
#line 490 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
  void
  init_loadcnt();
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 1007 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

inline void FIASCO_INIT_CPU
Perf_cnt::init_ap()
{
  Perf_cnt::pcnt->init();
  Perf_cnt::pcnt->init_loadcnt();
  Perf_cnt::pcnt->start_pmc(0);
}

#line 1019 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

// watchdog supported by performance counter architecture?

inline int
Perf_cnt::have_watchdog()
{ return (pcnt && pcnt->have_watchdog()); }

#line 1025 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

// setup watchdog function with timeout in seconds

inline void
Perf_cnt::setup_watchdog(Mword timeout)
{
  if (pcnt)
    pcnt->setup_watchdog(timeout);
}

#line 1034 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"


inline void
Perf_cnt::setup_loadcnt()
{
  if (pcnt)
    pcnt->setup_loadcnt();
}

#line 1042 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"


inline void
Perf_cnt::start_watchdog()
{
  if (pcnt && pcnt->watchdog_allocated())
    {
      pcnt->touch_watchdog();
      pcnt->start_watchdog();
    }
}

#line 1053 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"


inline void
Perf_cnt::stop_watchdog()
{
  if (pcnt && pcnt->watchdog_allocated())
    pcnt->stop_watchdog();
}

#line 1061 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"


inline void
Perf_cnt::touch_watchdog()
{
  if (pcnt && pcnt->watchdog_allocated())
    pcnt->touch_watchdog();
}

#line 1069 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

// return human-readable type of performance counters

inline char const *
Perf_cnt::perf_type()
{ return perf_type_str; }

#line 655 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"


inline Mword
Perf_cnt_arch::watchdog_allocated()
{ return (pmc_watchdog != (Mword)-1); }

#line 660 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"


inline Mword
Perf_cnt_arch::loadcnt_allocated()
{ return (pmc_loadcnt != (Mword)-1); }

#line 796 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

// watchdog supported by performance counter architecture?

inline int
Perf_cnt_arch::have_watchdog()
{ return _watchdog; }

#line 636 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"


//--------------------------------------------------------------------


inline Perf_cnt_arch::Perf_cnt_arch(Mword sel_reg0, Mword ctr_reg0, 
			     Mword nr_regs, Mword watchdog)
{
  _sel_reg0 = sel_reg0;
  _ctr_reg0 = ctr_reg0;
  _nr_regs  = nr_regs;
  _watchdog = watchdog;

  for (Mword slot=0; slot<Perf_cnt::Max_slot; slot++)
    {
      pmc_event[slot].pmc  = (Mword)-1;
      pmc_event[slot].edge = 0;
    }
}

#endif // perf_cnt_h
