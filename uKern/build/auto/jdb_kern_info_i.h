// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_kern_info_i_h
#define jdb_kern_info_i_h
#line 39 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info.cpp"

#include <cctype>
#line 41 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info.cpp"
#include <cstdio>
#line 42 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info.cpp"

#include "cpu.h"
#line 44 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info.cpp"
#include "jdb.h"
#line 45 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info.cpp"
#include "jdb_module.h"
#line 46 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info.cpp"
#include "static_init.h"
#line 47 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info.cpp"
#include "kmem_alloc.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"

#include <cstdio>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"
#include <cstring>
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"
#include "simpleio.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"

#include "config.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"
#include "cpu.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"
#include "gdt.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"
#include "idt.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"
#include "jdb_symbol.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"
#include "perf_cnt.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"
#include "pic.h"
#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"
#include "space.h"
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"
#include "tss.h"
#line 84 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"

#include "io.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-ux.cpp"

#include <cstdio>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-ux.cpp"
#include <cstring>
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-ux.cpp"
#include "simpleio.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-ux.cpp"
#include "jdb_screen.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info-apic.cpp"

#include <cstdio>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info-apic.cpp"
#include "simpleio.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info-apic.cpp"

#include "apic.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info-apic.cpp"
#include "static_init.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-pci.cpp"

#include <cstdio>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-pci.cpp"
#include "pci.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-pci.cpp"
#include "simpleio.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-pci.cpp"
#include "static_init.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/32/jdb_kern_info-bench-ia32-32.cpp"

#include <cstdio>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/32/jdb_kern_info-bench-ia32-32.cpp"
#include "cpu.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/32/jdb_kern_info-bench-ia32-32.cpp"
#include "div32.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/32/jdb_kern_info-bench-ia32-32.cpp"
#include "gdt.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/32/jdb_kern_info-bench-ia32-32.cpp"
#include "simpleio.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/32/jdb_kern_info-bench-ia32-32.cpp"
#include "static_init.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/32/jdb_kern_info-bench-ia32-32.cpp"
#include "timer_tick.h"
#line 77 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/32/jdb_kern_info-bench-ia32-32.cpp"


#include "apic.h"
#line 80 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/32/jdb_kern_info-bench-ia32-32.cpp"
#include "cpu.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-dr.cpp"

#include <cstdio>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-dr.cpp"
#include "simpleio.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-dr.cpp"

#include "jdb_bp.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-dr.cpp"
#include "static_init.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-mtrr.cpp"

#include "static_init.h"
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"


class Jdb_kern_info_idt : public Jdb_kern_info_module
{

public:  
#line 25 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"
  Jdb_kern_info_idt();
  
#line 32 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"
  void
  show();
};
#line 56 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"

class Jdb_kern_info_test_tsc_scaler : public Jdb_kern_info_module
{

public:  
#line 64 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"
  Jdb_kern_info_test_tsc_scaler();
  
#line 71 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"
  void
  show();
};
#line 86 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"

class Jdb_kern_info_pic_state : public Jdb_kern_info_module
{

public:  
#line 94 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"
  Jdb_kern_info_pic_state();

private:  
#line 100 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"
  void
  show();
};
#line 143 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"


class Jdb_kern_info_misc : public Jdb_kern_info_module
{

public:  
#line 152 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"
  Jdb_kern_info_misc();
  
#line 159 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"
  void
  show();

private:  
#line 136 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-ux.cpp"
  inline void
  show_pdir();
};
#line 200 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"

class Jdb_kern_info_cpu : public Jdb_kern_info_module
{

public:  
#line 208 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"
  Jdb_kern_info_cpu();
  
#line 215 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"
  void
  show();
  
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-ux.cpp"
  void
  show_f_bits(unsigned features, const char *const *table,
                                 unsigned first_pos, unsigned &last_pos,
                                 unsigned &colon);
  
#line 33 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-ux.cpp"
  void
  show_features();
};
#line 272 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"

class Jdb_kern_info_gdt : public Jdb_kern_info_module
{
private:
  static unsigned line;

public:  
#line 284 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"
  Jdb_kern_info_gdt();
  
#line 317 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"
  void
  show();

private:  
#line 291 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-amd64.cpp"
  static void
  show_gdt(Cpu_number cpu);
};
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info-apic.cpp"

class Jdb_kern_info_apic : public Jdb_kern_info_module
{

public:  
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info-apic.cpp"
  Jdb_kern_info_apic();
  
#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info-apic.cpp"
  void
  show();
};
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-pci.cpp"

class Jdb_kern_info_pci : public Jdb_kern_info_module
{

public:  
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-pci.cpp"
  Jdb_kern_info_pci();
  
#line 22 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-pci.cpp"
  void
  show();
};
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-dr.cpp"

class Jdb_kern_info_dr : public Jdb_kern_info_module
{

public:  
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-dr.cpp"
  Jdb_kern_info_dr();
  
#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-dr.cpp"
  void
  show();
};
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-mtrr.cpp"

class Jdb_kern_info_mtrr : public Jdb_kern_info_module
{
  Address size_or_mask;

public:  
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-mtrr.cpp"
  Jdb_kern_info_mtrr();
  
#line 56 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-mtrr.cpp"
  void
  show();

private:  
#line 24 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-mtrr.cpp"
  void
  get_var_mtrr(int reg, Address *ret_base,
                                   Address *ret_size, int *ret_type);
};

//
// IMPLEMENTATION of inline functions follows
//


#line 134 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-ia32-ux.cpp"


inline void
Jdb_kern_info_misc::show_pdir()
{
  Mem_space *s = Mem_space::current_mem_space(Cpu_number::boot_cpu());
  printf("%s" L4_PTR_FMT "\n",
         Jdb_screen::Root_page_table, (Address)s->dir());
}

#endif // jdb_kern_info_i_h
