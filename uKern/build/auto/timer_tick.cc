// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "timer_tick.h"
#include "timer_tick_i.h"

#line 53 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timer_tick.cpp"

// ------------------------------------------------------------------------


#line 120 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timer_tick.cpp"


unsigned
Timer_tick::Log::print(int maxlen, char *buf) const
{
  return snprintf(buf, maxlen, "u-ip=0x%lx", user_ip);
}
