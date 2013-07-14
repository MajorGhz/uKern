// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef platform_control_h
#define platform_control_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/platform_control.cpp"

#include "types.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/platform_control.cpp"

class Platform_control
{
public:
  static void init(Cpu_number);
  static bool cpu_offline_available();
  static int resume_cpu(Cpu_number cpu);
  static int suspend_cpu(Cpu_number cpu);
  static int system_suspend();
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/platform_control.cpp"

#include "l4_types.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/platform_control.cpp"


inline void
Platform_control::init(Cpu_number)
{}

#line 24 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/platform_control.cpp"


inline int
Platform_control::system_suspend()
{ return -L4_err::EBusy; }

#line 29 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/platform_control.cpp"


inline bool
Platform_control::cpu_offline_available()
{ return false; }

#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/platform_control.cpp"


inline int
Platform_control::suspend_cpu(Cpu_number)
{ return -L4_err::ENodev; }

#line 39 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/platform_control.cpp"


inline int
Platform_control::resume_cpu(Cpu_number)
{ return -L4_err::ENodev; }

#endif // platform_control_h
