// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef io_apic_h
#define io_apic_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

#include <types.h>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
#include "initcalls.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
#include <spin_lock.h>
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
#include "irq_chip_ia32.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
#include <cxx/bitfield>

//
// INTERFACE definition follows 
//

#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

class Acpi_madt;
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

class Io_apic_entry
{
  friend class Io_apic;
private:
  Unsigned64 _e;

public:
  enum Delivery { Fixed, Lowest_prio, SMI, NMI = 4, INIT, ExtINT = 7 };
  enum Dest_mode { Physical, Logical };
  enum Polarity { High_active, Low_active };
  enum Trigger { Edge, Level };

  Io_apic_entry() {}
  Io_apic_entry(Unsigned8 vector, Delivery d, Dest_mode dm, Polarity p,
                Trigger t, Unsigned32 dest)
    : _e(  vector_bfm_t::val(vector) | delivery_bfm_t::val(d) | mask_bfm_t::val(1)
         | dest_mode_bfm_t::val(dm)  | polarity_bfm_t::val(p)
         | trigger_bfm_t::val(t)     | dest_bfm_t::val(dest >> 24))
  {}

  CXX_BITFIELD_MEMBER( 0,  7, vector, _e);
  CXX_BITFIELD_MEMBER( 8, 10, delivery, _e);
  CXX_BITFIELD_MEMBER(11, 11, dest_mode, _e);
  CXX_BITFIELD_MEMBER(13, 13, polarity, _e);
  CXX_BITFIELD_MEMBER(15, 15, trigger, _e);
  CXX_BITFIELD_MEMBER(16, 16, mask, _e);
  CXX_BITFIELD_MEMBER(56, 63, dest, _e);
};
#line 39 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


class Io_apic : public Irq_chip_ia32
{
  friend class Jdb_io_apic_module;

private:
  struct Apic
  {
    Unsigned32 volatile adr;
    Unsigned32 dummy[3];
    Unsigned32 volatile data;

    unsigned num_entries();
    Mword read(int reg);
    void modify(int reg, Mword set_bits, Mword del_bits);
    void write(int reg, Mword value);
  } __attribute__((packed));

  Apic *_apic;
  mutable Spin_lock<> _l;
  unsigned _offset;
  Io_apic *_next;

  static unsigned _nr_irqs;
  static Io_apic *_first;
  static Acpi_madt const *_madt;

public:  
#line 154 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  explicit inline Io_apic(Io_apic::Apic *addr, unsigned irqs, unsigned gsi_base);
  
#line 161 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  inline Io_apic_entry
  read_entry(unsigned i) const;
  
#line 173 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  inline void
  write_entry(unsigned i, Io_apic_entry const &e);
  
#line 182 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  static FIASCO_INIT
  bool
  init(Cpu_number cpu);
  
#line 269 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  static unsigned
  total_irqs();
  
#line 274 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  static unsigned
  legacy_override(unsigned i);
  
#line 296 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  void
  dump();
  
#line 313 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  inline bool
  valid() const;
  
#line 335 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  inline bool
  masked(unsigned irq);
  
#line 344 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  inline void
  sync();
  
#line 351 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  inline void
  set_dest(unsigned irq, Mword dst);
  
#line 360 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  inline unsigned
  gsi_offset() const;
  
#line 364 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  static Io_apic *
  find_apic(unsigned irqnum);
  
#line 375 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  void
  mask(Mword irq);
  
#line 382 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  void
  ack(Mword);
  
#line 388 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  void
  mask_and_ack(Mword irq);
  
#line 396 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  void
  unmask(Mword irq);
  
#line 402 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  void
  set_cpu(Mword irq, Cpu_number cpu);
  
#line 424 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  int
  set_mode(Mword pin, Mode mode);
  
#line 438 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  bool
  is_edge_triggered(Mword pin) const;
  
#line 446 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  bool
  alloc(Irq_base *irq, Mword pin);
  
#line 461 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  void
  unbind(Irq_base *irq);
  
#line 472 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  inline char const *
  chip_type() const;
  
#line 477 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  static inline bool
  active();

private:  
#line 317 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  inline void
  _mask(unsigned irq);
  
#line 326 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  inline void
  _unmask(unsigned irq);
};
#line 113 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 74 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
#include "kdb_ke.h"
#line 76 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
#include "lock_guard.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 152 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline Io_apic::Io_apic(Io_apic::Apic *addr, unsigned irqs, unsigned gsi_base)
: Irq_chip_ia32(irqs), _apic(addr), _l(Spin_lock<>::Unlocked),
  _offset(gsi_base), _next(0)
{}

#line 158 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"



inline Io_apic_entry
Io_apic::read_entry(unsigned i) const
{
  auto g = lock_guard(_l);
  Io_apic_entry e;
  //assert_kdb(i <= num_entries());
  e._e = (Unsigned64)_apic->read(0x10+2*i) | (((Unsigned64)_apic->read(0x11+2*i)) << 32);
  return e;
}

#line 170 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"



inline void
Io_apic::write_entry(unsigned i, Io_apic_entry const &e)
{
  auto g = lock_guard(_l);
  //assert_kdb(i <= num_entries());
  _apic->write(0x10+2*i, e._e);
  _apic->write(0x11+2*i, e._e >> 32);
}

#line 311 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline bool
Io_apic::valid() const { return _apic; }

#line 333 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline bool
Io_apic::masked(unsigned irq)
{
  auto g = lock_guard(_l);
  //assert_kdb(irq <= _apic->num_entries());
  return _apic->read(0x10 + irq * 2) & (1UL << 16);
}

#line 342 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline void
Io_apic::sync()
{
  (void)_apic->data;
}

#line 349 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline void
Io_apic::set_dest(unsigned irq, Mword dst)
{
  auto g = lock_guard(_l);
  //assert_kdb(irq <= _apic->num_entries());
  _apic->modify(0x11 + irq * 2, dst & (~0UL << 24), ~0UL << 24);
}

#line 358 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline unsigned
Io_apic::gsi_offset() const { return _offset; }

#line 470 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline char const *
Io_apic::chip_type() const
{ return "IO-APIC"; }

#line 475 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline bool
Io_apic::active()
{ return _first; }

#line 113 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"



inline Mword
Io_apic::Apic::read(int reg)
{
  adr = reg;
  asm volatile ("": : :"memory");
  return data;
}

#line 123 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline void
Io_apic::Apic::modify(int reg, Mword set_bits, Mword del_bits)
{
  register Mword tmp;
  adr = reg;
  asm volatile ("": : :"memory");
  tmp = data;
  tmp &= ~del_bits;
  tmp |= set_bits;
  data = tmp;
}

#line 136 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline void
Io_apic::Apic::write(int reg, Mword value)
{
  adr = reg;
  asm volatile ("": : :"memory");
  data = value;
}

#line 145 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline unsigned
Io_apic::Apic::num_entries()
{
  return (read(1) >> 16) & 0xff;
}

#endif // io_apic_h
