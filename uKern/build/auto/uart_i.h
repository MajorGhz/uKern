// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef uart_i_h
#define uart_i_h
#line 77 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"
#include "processor.h"

//
// IMPLEMENTATION of inline functions follows
//


#line 100 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"



inline void Uart::mcr(Unsigned8 b)
{
  outb(b, MCR);
}

#line 107 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"


inline Unsigned8 Uart::mcr() const
{
  return inb(MCR);
}

#line 113 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"


inline void Uart::fcr(Unsigned8 b)
{
  outb(b, FCR);
}

#line 119 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"


inline void Uart::lcr(Unsigned8 b)
{
  outb(b, LCR);
}

#line 125 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"


inline Unsigned8 Uart::lcr() const
{
  return inb(LCR);
}

#line 143 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"


inline Unsigned8 Uart::iir() const
{
  return inb(IIR);
}

#line 149 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"


inline Unsigned8 Uart::msr() const
{
  return inb(MSR);
}

#line 155 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"


inline Unsigned8 Uart::lsr() const
{
  return inb(LSR);
}

#line 161 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"


inline void Uart::trb(Unsigned8 b)
{
  outb(b, TRB);
}

#line 167 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"


inline Unsigned8 Uart::trb() const
{
  return inb(TRB);
}

#endif // uart_i_h
