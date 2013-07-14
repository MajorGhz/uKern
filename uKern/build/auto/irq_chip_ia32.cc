// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "irq_chip_ia32.h"
#include "irq_chip_ia32_i.h"

#line 99 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
enum { Register_arg0 = 0 }; // eax
#line 111 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"

// The global INT vector allocator for IRQs uses these data
Int_vector_allocator Irq_chip_ia32::_vectors;

#line 114 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"


void
Irq_entry_code::setup(Irq_base *irq, unsigned char vector)
{
  extern char __generic_irq_entry[];
  // push %eax/%rdi
  _d.push = 0x50 + Register_arg0;

  // mov imm32, %eax/%rdi
  _d.mov = 0xb8 + Register_arg0;
  _d.irq_adr = (Address)irq;

  // jmp __generic_irq_entry
  _d.jmp = 0xe9;
  _d.jmp_adr = (Address)__generic_irq_entry - (Address)&_d - 11;


  // no code, our currently assigned IRQ vector
  // 0 means no vector allocated
  _d.vector = vector;
}

#line 136 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"


void
Int_vector_allocator::add_free(unsigned start, unsigned end)
{
  assert (Base > 0x10);
  assert (End > Base);
  assert (start >= Base);
  assert (end <= End);

  for (unsigned v = start - Base; v < end - Base - 1; ++v)
    _vectors[v] = v + Base + 1;

  _vectors[end - Base - 1] = _first;
  _first = start;
}

#line 185 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"



Irq_base *
Irq_chip_ia32::irq(Mword irqn) const
{
  if (irqn >= _irqs)
    return 0;

  return _entry[irqn].irq();
}

#line 196 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"

/**
 * Generic binding of an Irq_base object to a specific pin and a 
 * an INT vector.
 *
 * \param irq The Irq_base object to bind
 * \param pin The pin number at this IRQ chip
 * \param vector The INT vector to use, or 0 for dynamic allocation
 * \return the INT vector used an success, or 0 on failure.
 *
 * This function does the following:
 * 1. Some sanity checks
 * 2. Check if PIN is unassigned
 * 3. Check if no vector is given:
 *    a) Use vector that was formerly assigned to this PIN
 *    b) Try to allocate a new vector for the PIN
 * 4. Prepare the entry code to point to \a irq
 * 5. Point IDT entry to the PIN's entry code
 * 6. Return the assigned vector number
 */

unsigned
Irq_chip_ia32::valloc(Irq_base *irq, Mword pin, unsigned vector)
{
  if (pin >= _irqs)
    return 0;

  if (vector >= APIC_IRQ_BASE - 0x10)
    return 0;

  Irq_entry_code *const e = &_entry[pin];

  if (!e->is_free())
    return 0;

  if (!vector)
    vector = e->vector();

  if (!vector)
    vector = _vectors.alloc();

  if (!vector)
    return 0;

  Irq_chip::bind(irq, pin);

  e->setup(irq, vector);

  // force code to memory before setting IDT entry
  Mem::barrier();

  Idt::set_entry(vector, (Address)e, false);
  return vector;
}

#line 250 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"



bool
Irq_chip_ia32::vfree(Irq_base *irq, void *handler)
{
  Irq_entry_code *e = &_entry[irq->pin()];

  assert (!e->is_free());
  assert (e->irq() == irq);

  Idt::set_entry(e->vector(), (Address)handler, false);

  e->free();

  return true;
}

#line 267 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"



bool
Irq_chip_ia32::reserve(Mword irqn)
{
  if (irqn >= _irqs)
    return false;

  if (!_entry[irqn].is_free())
    return false;

  _entry[irqn].setup();
  return true;
}

#line 282 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"


void
Irq_chip_ia32::unbind(Irq_base *irq)
{
  extern char entry_int_pic_ignore[];
  Mword n = irq->pin();
  mask(n);
  vfree(irq, &entry_int_pic_ignore);
  Irq_chip_icu::unbind(irq);
}
