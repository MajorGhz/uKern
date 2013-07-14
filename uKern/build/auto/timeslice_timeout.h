// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef timeslice_timeout_h
#define timeslice_timeout_h
#line 3 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeslice_timeout.cpp"

#include "timeout.h"

//
// INTERFACE definition follows 
//

#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeslice_timeout.cpp"

class Timeslice_timeout : public Timeout
{

public:  
#line 22 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeslice_timeout.cpp"
  Timeslice_timeout(Cpu_number cpu);

private:  
#line 28 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeslice_timeout.cpp"
  /**
   * Timeout expiration callback function
   * @return true to force a reschedule
   */
  
  bool
  expired();
};

#endif // timeslice_timeout_h
