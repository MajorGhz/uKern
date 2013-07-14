// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef irq_chip_pic_i_h
#define irq_chip_pic_i_h
#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"

#include <cassert>
#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"

#include "boot_alloc.h"
#line 22 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"
#include "cpu_lock.h"
#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"
#include "globalconfig.h"
#line 24 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"
#include "globals.h"
#line 25 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"
#include "irq_mgr.h"
#line 26 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"
#include "pic.h"
#line 102 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"


class Pic_irq_mgr : public Irq_mgr
{
private:
  mutable Irq_chip_ia32_pic _pic;

public:  
#line 110 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"
  Irq_mgr::Irq
  chip(Mword irq) const;
  
#line 120 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"
  unsigned
  nr_irqs() const;
  
#line 127 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"
  unsigned
  nr_msis() const;
};

#endif // irq_chip_pic_i_h
