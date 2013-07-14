// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef irq_msi_i_h
#define irq_msi_i_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"

#include "idt.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
#include "irq_chip.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
#include "irq_mgr.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
#include "irq_chip_ia32.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"

#include "apic.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
#include "static_init.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
#include "boot_alloc.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"

class Irq_chip_msi : public Irq_chip_ia32
{
public:
  // this is somehow arbitrary
  enum { Max_msis = 0x40 };
  Irq_chip_msi() : Irq_chip_ia32(Max_msis) {}

public:  
#line 28 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  inline char const *
  chip_type() const;
  
#line 33 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  bool
  alloc(Irq_base *irq, Mword pin);
  
#line 40 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  void
  unbind(Irq_base *irq);
  
#line 51 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  Mword
  msg(Mword pin);
  
#line 60 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  int
  set_mode(Mword, Mode);
  
#line 64 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  bool
  is_edge_triggered(Mword) const;
  
#line 68 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  void
  set_cpu(Mword, Cpu_number);
  
#line 72 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  void
  mask(Mword);
  
#line 76 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  void
  ack(Mword);
  
#line 80 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  void
  mask_and_ack(Mword);
  
#line 84 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  void
  unmask(Mword);
};
#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"

class Irq_mgr_msi : public Irq_mgr
{
private:
  mutable Irq_chip_msi _chip;
  Irq_mgr *_orig;

public:  
#line 90 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  explicit inline Irq_mgr_msi(Irq_mgr *o);
  
#line 92 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  Irq_mgr::Irq
  chip(Mword irq) const;
  
#line 102 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  unsigned
  nr_irqs() const;
  
#line 107 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  unsigned
  nr_msis() const;
  
#line 112 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  Mword
  msg(Mword irq) const;
  
#line 121 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  unsigned
  legacy_override(Mword irq);
  
#line 131 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  static FIASCO_INIT
  void
  init();
};

//
// IMPLEMENTATION of inline functions follows
//


#line 26 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"


inline char const *
Irq_chip_msi::chip_type() const
{ return "MSI"; }

#line 87 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"



inline Irq_mgr_msi::Irq_mgr_msi(Irq_mgr *o) : _orig(o) {}

#endif // irq_msi_i_h
