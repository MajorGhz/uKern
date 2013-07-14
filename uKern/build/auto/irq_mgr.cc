// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "irq_mgr.h"
#include "irq_mgr_i.h"

#line 80 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_mgr.cpp"

//--------------------------------------------------------------------------

#line 85 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_mgr.cpp"

Irq_mgr *Irq_mgr::mgr;

#line 122 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_mgr.cpp"


void
Irq_mgr::set_cpu(Mword irqnum, Cpu_number cpu) const
{
  WARNX(Warning, "IRQ%ld: ignoring CPU setting (%d).\n", irqnum,
        cxx::int_value<Cpu_number>(cpu));
}
