// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef irq_chip_ia32_h
#define irq_chip_ia32_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"

#include "globals.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
#include "idt_init.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
#include "irq_chip.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
#include "boot_alloc.h"

//
// INTERFACE definition follows 
//

#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"

/**
 * Allocator for IA32 interrupt vectors in the IDT.
 *
 * Some vectors are fixed purpose, others can be dynamically
 * managed by this allocator to support MSIs and multiple IO-APICs.
 */
class Int_vector_allocator
{
public:
  bool empty() const { return !_first; }
private:
  enum
  {
    /// Start at vector 0x20, note: <0x10 is vorbidden here
    Base = 0x20,

    /// The Last vector + 1 that is managed
    End  = APIC_IRQ_BASE - 0x10
  };

  /// array for free list
  unsigned char _vectors[End - Base];

  /// the first free vector
  unsigned _first;

public:  
#line 138 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
  void
  add_free(unsigned start, unsigned end);
  
#line 154 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
  inline void
  free(unsigned v);
  
#line 164 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
  inline unsigned
  alloc();
};
#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"

/**
 * Entry point for a device IRQ IDT vector.
 *
 * IA32 IRQ Chips use arrays of this entry code pieces
 * and dynamically assign adresses of Irq_base objects to them
 * to directly pass device IRQs to an Irq_base object.
 *
 * The chips also use these objects to manage the assignment of Irq_base
 * objects to the pins of the IRQ controller.
 */
class Irq_entry_code : public Boot_alloced
{
private:
  struct
  {
    char push;
    char mov;
    Signed32 irq_adr;
    char jmp;
    Unsigned32 jmp_adr;
    unsigned char vector;
  } __attribute__((packed)) _d;

public:
  Irq_entry_code() { free(); _d.vector = 0; }

  Irq_base *irq() const
  { return (Irq_base*)((Smword)(_d.irq_adr)); }

  bool is_free() const
  { return !_d.push; }

  void free()
  {
    _d.push = 0;
    _d.irq_adr = 0;
  }

  unsigned char vector() const
  { return _d.vector; }

public:  
#line 116 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
  void
  setup(Irq_base *irq = 0, unsigned char vector = 0);
};
#line 76 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"


/**
 * Generic IA32 IRQ chip class.
 *
 * Uses an array of Idt_entry_code objects to manage
 * the IRQ entry points and the Irq_base objects assigned to the
 * pins of a specific controller.
 */
class Irq_chip_ia32 : public Irq_chip_icu
{
public:
  /// Number of pins at this chip.
  unsigned nr_irqs() const { return _irqs; }

protected:
  unsigned const _irqs;
  Irq_entry_code *const _entry;
  static Int_vector_allocator _vectors;

public:  
#line 176 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
  explicit inline Irq_chip_ia32(unsigned irqs);
  
#line 188 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
  Irq_base *
  irq(Mword irqn) const;
  
#line 270 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
  bool
  reserve(Mword irqn);
  
#line 284 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
  void
  unbind(Irq_base *irq);

protected:  
#line 197 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
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
  valloc(Irq_base *irq, Mword pin, unsigned vector);
  
#line 253 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
  bool
  vfree(Irq_base *irq, void *handler);
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 152 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"


inline void
Int_vector_allocator::free(unsigned v)
{
  assert (Base <= v && v < End);

  _vectors[v - Base] = _first;
  _first = v;
}

#line 162 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"


inline unsigned
Int_vector_allocator::alloc()
{
  if (!_first)
    return 0;

  unsigned r = _first;
  _first = _vectors[r - Base];
  return r;
}

#line 174 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"


inline Irq_chip_ia32::Irq_chip_ia32(unsigned irqs)
: _irqs(irqs),
  _entry(new Irq_entry_code[irqs])
{
  // add vectors from 0x40 upo to APIC_IRQ_BASE - 0x10 as free
  // if we are the first IA32 chip ctor running
  if (_vectors.empty())
    _vectors.add_free(0x40, APIC_IRQ_BASE - 0x10);
}

#endif // irq_chip_ia32_h
