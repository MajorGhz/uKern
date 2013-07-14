// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef io_apic_i_h
#define io_apic_i_h
#line 69 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

#include "acpi.h"
#line 71 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
#include "apic.h"
#line 72 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
#include "irq_mgr.h"
#line 73 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
#include "kmem.h"
#line 75 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
#include "kip.h"
#line 77 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
#include "boot_alloc.h"
#line 82 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


class Io_apic_mgr : public Irq_mgr
{

public:  
#line 88 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  Irq_mgr::Irq
  chip(Mword irq) const;
  
#line 99 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  unsigned
  nr_irqs() const;
  
#line 106 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  unsigned
  nr_msis() const;
  
#line 110 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  unsigned
  legacy_override(Mword i);
};

//
// IMPLEMENTATION of inline functions follows
//


#line 315 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline void
Io_apic::_mask(unsigned irq)
{
  auto g = lock_guard(_l);
  //assert_kdb(irq <= _apic->num_entries());
  _apic->modify(0x10 + irq * 2, 1UL << 16, 0);
}

#line 324 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline void
Io_apic::_unmask(unsigned irq)
{
  auto g = lock_guard(_l);
  //assert_kdb(irq <= _apic->num_entries());
  _apic->modify(0x10 + irq * 2, 0, 1UL << 16);
}

#endif // io_apic_i_h
