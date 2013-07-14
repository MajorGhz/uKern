// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "irq_msi.h"
#include "irq_msi_i.h"

#line 139 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"

STATIC_INITIALIZE(Irq_mgr_msi);

#line 31 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"


bool
Irq_chip_msi::alloc(Irq_base *irq, Mword pin)
{
  return valloc(irq, pin, 0);
}

#line 38 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"


void
Irq_chip_msi::unbind(Irq_base *irq)
{
  extern char entry_int_apic_ignore[];
  //Mword n = irq->pin();
  // hm: no way to mask an MSI: mask(n);
  vfree(irq, &entry_int_apic_ignore);
  Irq_chip_icu::unbind(irq);
}

#line 49 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"


Mword
Irq_chip_msi::msg(Mword pin)
{
  if (pin < _irqs)
    return _entry[pin].vector();

  return 0;
}

#line 59 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"

int
Irq_chip_msi::set_mode(Mword, Mode)
{ return 0; }

#line 63 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"

bool
Irq_chip_msi::is_edge_triggered(Mword) const
{ return true; }

#line 67 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"

void
Irq_chip_msi::set_cpu(Mword, Cpu_number)
{}

#line 71 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"

void
Irq_chip_msi::mask(Mword)
{}

#line 75 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"

void
Irq_chip_msi::ack(Mword)
{ ::Apic::irq_ack(); }

#line 79 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"

void
Irq_chip_msi::mask_and_ack(Mword)
{ ::Apic::irq_ack(); }

#line 83 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"

void
Irq_chip_msi::unmask(Mword)
{}

#line 91 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"

Irq_mgr::Irq
Irq_mgr_msi::chip(Mword irq) const
{
  if (irq & 0x80000000)
    return Irq(&_chip, irq & ~0x80000000);
  else
    return _orig->chip(irq);
}

#line 100 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"


unsigned
Irq_mgr_msi::nr_irqs() const
{ return _orig->nr_irqs(); }

#line 105 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"


unsigned
Irq_mgr_msi::nr_msis() const
{ return _chip.nr_irqs(); }

#line 110 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"


Mword
Irq_mgr_msi::msg(Mword irq) const
{
  if (irq & 0x80000000)
    return _chip.msg(irq & ~0x80000000);
  else
    return 0;
}

#line 120 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"

unsigned
Irq_mgr_msi::legacy_override(Mword irq)
{
  if (irq & 0x80000000)
    return irq;
  else
    return _orig->legacy_override(irq);
}

#line 129 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"


FIASCO_INIT
void
Irq_mgr_msi::init()
{
  Irq_mgr_msi *m;
  Irq_mgr::mgr = m =  new Boot_object<Irq_mgr_msi>(Irq_mgr::mgr);
  printf("Enable MSI support: chained IRQ mgr @ %p\n", m->_orig);
}
