// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef irq_chip_pic_h
#define irq_chip_pic_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"

#include "irq_chip_ia32.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"

/**
 * IRQ Chip based on the IA32 legacy PIC.
 *
 * Vectors for the PIC are from 0x20 to 0x2f statically assigned.
 */
class Irq_chip_ia32_pic : public Irq_chip_ia32
{
public:
  char const *chip_type() const { return "PIC"; }

public:  
#line 29 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"
  inline Irq_chip_ia32_pic();
  
#line 33 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"
  bool
  alloc(Irq_base *irq, Mword irqn);
  
#line 48 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"
  void
  mask(Mword irq);
  
#line 56 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"
  void
  mask_and_ack(Mword irq);
  
#line 64 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"
  void
  ack(Mword irq);
  
#line 71 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"
  int
  set_mode(Mword, Mode);
  
#line 76 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"
  bool
  is_edge_triggered(Mword) const;
  
#line 81 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"
  void
  unmask(Mword irq);
  
#line 99 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"
  void
  set_cpu(Mword, Cpu_number);
  
#line 145 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"
  static FIASCO_INIT
  void
  init();
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 27 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"


inline Irq_chip_ia32_pic::Irq_chip_ia32_pic() : Irq_chip_ia32(16)
{}

#endif // irq_chip_pic_h
