// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "pit.h"
#include "pit_i.h"

#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/pit-i8254.cpp"


//----------------------------------------------------------------------------


#line 26 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/pit-i8254.cpp"

FIASCO_INIT_CPU
void
Pit::setup_channel2_to_20hz()
{
  // set gate high, disable speaker
  Io::out8((Io::in8(0x61) & ~0x02) | 0x01, 0x61);

  // set counter channel 2 to binary, mode0, lsb/msb
  Io::out8(0xb0, 0x43);

  // set counter frequency
  const unsigned latch = Clock_tick_rate / 20; // 50ms
  Io::out8(latch & 0xff, 0x42);
  Io::out8(latch >> 8,   0x42);
}
