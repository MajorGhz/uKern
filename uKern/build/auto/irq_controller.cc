// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "irq_controller.h"
#include "irq_controller_i.h"

#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_controller.cpp"


//----------------------------------------------------------------------------

#line 26 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_controller.cpp"

FIASCO_DEFINE_KOBJ(Icu);
#line 98 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_controller.cpp"

static Icu icu;

#line 28 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_controller.cpp"

void
Icu::operator delete(void *)
{
  printf("WARNING: tried to delete kernel ICU object.\n"
         "         The system is now useless\n");
}
