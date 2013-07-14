// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef filter_console_i_h
#define filter_console_i_h
#line 30 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/filter_console.cpp"

#include <cstdio>
#line 32 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/filter_console.cpp"
#include <cstring>
#line 33 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/filter_console.cpp"
#include <cctype>
#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/filter_console.cpp"
#include "keycodes.h"
#line 35 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/filter_console.cpp"
#include "delayloop.h"

//
// IMPLEMENTATION of inline functions follows
//


#line 110 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/filter_console.cpp"


inline int
Filter_console::getchar_timeout(unsigned timeout)
{
  int c;
  while ((c= _o->getchar(false)) == -1 && timeout--)
    Delay::delay(1);
  return c;
}

#endif // filter_console_i_h
