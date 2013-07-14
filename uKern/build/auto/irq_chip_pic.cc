// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "irq_chip_pic.h"
#include "irq_chip_pic_i.h"


#line 31 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"


bool
Irq_chip_ia32_pic::alloc(Irq_base *irq, Mword irqn)
{
  // no mor than 16 IRQs
  if (irqn > 0xf)
    return false;

  // PIC uses vectors from 0x20 to 0x2f statically
  unsigned vector = 0x20 + irqn;

  return valloc(irq, irqn, vector);
}

#line 45 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"



void
Irq_chip_ia32_pic::mask(Mword irq)
{
  Pic::disable_locked(irq);
}

#line 53 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"



void
Irq_chip_ia32_pic::mask_and_ack(Mword irq)
{
  Pic::disable_locked(irq);
  Pic::acknowledge_locked(irq);
}

#line 62 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"


void
Irq_chip_ia32_pic::ack(Mword irq)
{
  Pic::acknowledge_locked(irq);
}

#line 69 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"


int
Irq_chip_ia32_pic::set_mode(Mword, Mode)
{ return 0; }

#line 74 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"


bool
Irq_chip_ia32_pic::is_edge_triggered(Mword) const
{ return false; }

#line 79 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"


void
Irq_chip_ia32_pic::unmask(Mword irq)
{
  Pic::enable_locked(irq, 0xa); //prio);
#if 0
  unsigned long prio;

  if (EXPECT_FALSE(!Irq::self(this)->owner()))
    return;
  if (Irq::self(this)->owner() == (Receiver*)-1)
    prio = ~0UL; // highes prio for JDB IRQs
  else
    prio = Irq::self(this)->owner()->sched()->prio();
#endif

}

#line 97 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"


void
Irq_chip_ia32_pic::set_cpu(Mword, Cpu_number)
{}

#line 109 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"

Irq_mgr::Irq
Pic_irq_mgr::chip(Mword irq) const
{
  if (irq < 16)
    return Irq(&_pic, irq);

  return Irq();
}

#line 118 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"


unsigned
Pic_irq_mgr::nr_irqs() const
{
  return 16;
}

#line 125 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"


unsigned
Pic_irq_mgr::nr_msis() const
{ return 0; }

#line 144 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"

FIASCO_INIT
void
Irq_chip_ia32_pic::init()
{
  Irq_mgr::mgr = new Boot_object<Pic_irq_mgr>();
  //
  // initialize interrupts
  //
  Irq_mgr::mgr->reserve(2);		// reserve cascade irq
  Irq_mgr::mgr->reserve(7);		// reserve spurious vect
  Irq_mgr::mgr->reserve(0xf);		// reserve spurious vect

  Pic::enable_locked(2);		// allow cascaded irqs
}
