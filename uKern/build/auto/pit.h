// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef pit_h
#define pit_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/pit-i8254.cpp"

#include "initcalls.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/pit-i8254.cpp"

class Pit
{
  enum
  {
    Clock_tick_rate = 1193180,
  };

public:  
#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/pit-i8254.cpp"
  static inline void
  done();
  
#line 27 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/pit-i8254.cpp"
  static FIASCO_INIT_CPU
  void
  setup_channel2_to_20hz();
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/pit-i8254.cpp"

#include "io.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/pit-i8254.cpp"


inline void
Pit::done()
{
  // set counter channel 0 to one-shot mode
  Io::out8_p(0x30, 0x43);
}

#endif // pit_h
