// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "io_apic.h"
#include "io_apic_i.h"


#line 409 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
static inline Mword to_io_apic_trigger(Irq_chip::Mode mode);

#line 417 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
static inline Mword to_io_apic_polarity(Irq_chip::Mode mode);
#line 78 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

Acpi_madt const *Io_apic::_madt;
#line 80 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
unsigned Io_apic::_nr_irqs;
#line 81 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
Io_apic *Io_apic::_first;

#line 407 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


static inline Mword to_io_apic_trigger(Irq_chip::Mode mode)
{
  return mode.level_triggered()
         ? Io_apic_entry::Level
         : Io_apic_entry::Edge;
}

#line 415 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


static inline Mword to_io_apic_polarity(Irq_chip::Mode mode)
{
  return mode.polarity() == Irq_chip::Mode::Polarity_high
         ? Io_apic_entry::High_active
         : Io_apic_entry::Low_active;
}

#line 87 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

Irq_mgr::Irq
Io_apic_mgr::chip(Mword irq) const
{
  Io_apic *a = Io_apic::find_apic(irq);
  if (a)
    return Irq(a, irq - a->gsi_offset());

  return Irq(0, 0);
}

#line 97 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


unsigned
Io_apic_mgr::nr_irqs() const
{
  return Io_apic::total_irqs();
}

#line 104 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


unsigned
Io_apic_mgr::nr_msis() const
{ return 0; }

#line 109 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

unsigned
Io_apic_mgr::legacy_override(Mword i)
{ return Io_apic::legacy_override(i); }

#line 181 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

FIASCO_INIT
bool
Io_apic::init(Cpu_number cpu)
{
  _madt = Acpi::find<Acpi_madt const *>("APIC");

  if (_madt == 0)
    {
      printf("Could not find APIC in RSDT nor XSDT, skipping init\n");
      return false;
    }
  printf("IO-APIC: MADT = %p\n", _madt);

  int n_apics = 0;

  for (n_apics = 0;
       Acpi_madt::Io_apic const *ioapic = static_cast<Acpi_madt::Io_apic const *>(_madt->find(Acpi_madt::IOAPIC, n_apics));
       ++n_apics)
    {
      printf("IO-APIC[%2d]: struct: %p adr=%x\n", n_apics, ioapic, ioapic->adr);

      Address offs;
      Address va = Mem_layout::alloc_io_vmem(Config::PAGE_SIZE);
      assert (va);

      Kmem::map_phys_page(ioapic->adr, va, false, true, &offs);

      Kip::k()->add_mem_region(Mem_desc(ioapic->adr, ioapic->adr + Config::PAGE_SIZE -1, Mem_desc::Reserved));

      Io_apic::Apic *a = (Io_apic::Apic*)(va + offs);
      a->write(0, 0);

      unsigned const irqs = a->num_entries() + 1;
      Io_apic *apic = new Boot_object<Io_apic>(a, irqs, ioapic->irq_base);

      if ((apic->_offset + irqs) > _nr_irqs)
	_nr_irqs = apic->_offset + irqs;

      for (unsigned i = 0; i < irqs; ++i)
        {
          int v = 0x20+i;
          Io_apic_entry e(v, Io_apic_entry::Fixed, Io_apic_entry::Physical,
              Io_apic_entry::High_active, Io_apic_entry::Edge,
              ::Apic::apic.cpu(cpu)->apic_id());
          apic->write_entry(i, e);
        }

      Io_apic **c = &_first;
      while (*c && (*c)->_offset < apic->_offset)
	c = &((*c)->_next);

      apic->_next = *c;
      *c = apic;

      printf("IO-APIC[%2d]: pins %u\n", n_apics, irqs);
      apic->dump();
    }

  if (!n_apics)
    {
      printf("IO-APIC: Could not find IO-APIC in MADT, skip init\n");
      return false;
    }


  printf("IO-APIC: dual 8259: %s\n", _madt->apic_flags & 1 ? "yes" : "no");

  for (unsigned tmp = 0;;++tmp)
    {
      Acpi_madt::Irq_source const *irq
	= static_cast<Acpi_madt::Irq_source const *>(_madt->find(Acpi_madt::Irq_src_ovr, tmp));

      if (!irq)
	break;

      printf("IO-APIC: ovr[%2u] %02x -> %x\n", tmp, irq->src, irq->irq);
    }

  Irq_mgr::mgr = new Boot_object<Io_apic_mgr>();

  // in the case we use the IO-APIC not the PIC we can dynamically use
  // INT vectors from 0x20 to 0x2f too
  _vectors.add_free(0x20, 0x30);
  return true;
};

#line 267 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


unsigned
Io_apic::total_irqs()
{ return _nr_irqs; }

#line 272 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


unsigned
Io_apic::legacy_override(unsigned i)
{
  if (!_madt)
    return i;

  unsigned tmp = 0;
  for (;;++tmp)
    {
      Acpi_madt::Irq_source const *irq
	= static_cast<Acpi_madt::Irq_source const *>(_madt->find(Acpi_madt::Irq_src_ovr, tmp));

      if (!irq)
	break;

      if (irq->src == i)
	return irq->irq;
    }
  return i;
}

#line 294 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


void
Io_apic::dump()
{
  for (unsigned i = 0; i < _irqs; ++i)
    {
      Io_apic_entry e = read_entry(i);
      printf("  PIN[%2u%c]: vector=%2x, del=%u, dm=%s, dest=%u (%s, %s)\n",
	     i, e.mask() ? 'm' : '.',
	     (unsigned)e.vector(), (unsigned)e.delivery(), e.dest_mode() ? "logical" : "physical",
	     (unsigned)e.dest(),
	     e.polarity() ? "low" : "high",
	     e.trigger() ? "level" : "edge");
    }

}

#line 362 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


Io_apic *
Io_apic::find_apic(unsigned irqnum)
{
  for (Io_apic *a = _first; a; a = a->_next)
    {
      if (a->_offset <= irqnum && a->_offset + a->_irqs > irqnum)
	return a;
    }
  return 0;
};

#line 374 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

void
Io_apic::mask(Mword irq)
{
  _mask(irq);
  sync();
}

#line 381 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

void
Io_apic::ack(Mword)
{
  ::Apic::irq_ack();
}

#line 387 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

void
Io_apic::mask_and_ack(Mword irq)
{
  _mask(irq);
  sync();
  ::Apic::irq_ack();
}

#line 395 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

void
Io_apic::unmask(Mword irq)
{
  _unmask(irq);
}

#line 401 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

void
Io_apic::set_cpu(Mword irq, Cpu_number cpu)
{
  set_dest(irq, ::Apic::apic.cpu(cpu)->apic_id());
}

#line 423 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

int
Io_apic::set_mode(Mword pin, Mode mode)
{
  if (!mode.set_mode())
    return 0;

  Io_apic_entry e = read_entry(pin);
  e.polarity() = to_io_apic_polarity(mode);
  e.trigger() = to_io_apic_trigger(mode);
  write_entry(pin, e);
  return 0;
}

#line 436 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


bool
Io_apic::is_edge_triggered(Mword pin) const
{
  Io_apic_entry e = read_entry(pin);
  return e.trigger() == Io_apic_entry::Edge;
}

#line 444 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


bool
Io_apic::alloc(Irq_base *irq, Mword pin)
{
  unsigned v = valloc(irq, pin, 0);

  if (!v)
    return false;

  Io_apic_entry e = read_entry(pin);
  e.vector() = v;
  write_entry(pin, e);
  return true;
}

#line 459 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


void
Io_apic::unbind(Irq_base *irq)
{
  extern char entry_int_apic_ignore[];
  Mword n = irq->pin();
  mask(n);
  vfree(irq, &entry_int_apic_ignore);
  Irq_chip_icu::unbind(irq);
}
