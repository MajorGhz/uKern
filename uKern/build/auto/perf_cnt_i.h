// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef perf_cnt_i_h
#define perf_cnt_i_h
#line 67 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

#include <cstring>
#line 69 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
#include <cstdio>
#line 70 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
#include <panic.h>
#line 71 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
#include "cpu.h"
#line 72 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
#include "regdefs.h"
#line 73 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
#include "static_init.h"
#line 74 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"
#include "tb_entry.h"
#line 176 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

enum perfctr_unit_mask_type
{
  perfctr_um_type_fixed,	/* one fixed (required) value */
  perfctr_um_type_exclusive,	/* exactly one of N values */
  perfctr_um_type_bitmask,	/* bitwise 'or' of N power-of-2 values */
};
#line 183 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

struct perfctr_unit_mask_value
{
  unsigned int value;
  const char *description;	/* [NAME:]text */
};
#line 189 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

struct perfctr_unit_mask
{
  unsigned int default_value;
  enum perfctr_unit_mask_type type:16;
  unsigned short nvalues;
  struct perfctr_unit_mask_value values[1/*nvalues*/];
};
#line 197 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

struct perfctr_event
{
  unsigned int evntsel;
  unsigned int counters_set; /* P4 force this to be CPU-specific */
  const struct perfctr_unit_mask *unit_mask;
  const char *name;
  const char *description;
};
#line 206 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/perf_cnt-ia32.cpp"

struct perfctr_event_set
{
  unsigned int cpu_type;
  const char *event_prefix;
  const struct perfctr_event_set *include;
  unsigned int nevents;
  const struct perfctr_event *events;
};

#endif // perf_cnt_i_h
