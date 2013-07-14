// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef delayloop_h
#define delayloop_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/delayloop.cpp"

#include "std_macros.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/delayloop.cpp"
#include "initcalls.h"

//
// INTERFACE definition follows 
//

#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/delayloop.cpp"

class Delay
{
private:
  static unsigned count;

public:
  static void init() FIASCO_INIT;

public:  
#line 42 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/delayloop.cpp"
  /**
   * Hint: ms is actually the timer granularity, which
   *       currently happens to be milliseconds
   */
  static void
  delay(unsigned ms);
};

#endif // delayloop_h
