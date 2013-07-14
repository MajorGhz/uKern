// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef utcb_init_h
#define utcb_init_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/utcb_init.cpp"

#include "initcalls.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/utcb_init.cpp"
#include "types.h"

//
// INTERFACE definition follows 
//

#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/utcb_init.cpp"

class Cpu;
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/utcb_init-ia32.cpp"

class Cpu;
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/utcb_init.cpp"

class Utcb_init
{
public:
  /**
   * UTCB access initialization.
   *
   * Allocates the UTCB pointer page and maps it to Kmem::utcb_ptr_page.
   * Setup both segment selector and gs register to allow gs:0 access.
   *
   * @post user can access the utcb pointer via gs:0.
   */
  static void init() FIASCO_INIT;

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/utcb_init-ia32.cpp"
private:

public:
  /**
   * Value for GS and FS.
   * @return Value the GS and FS register has to be loaded with when
   *         entering user mode.
   */
  static Unsigned32 utcb_segment();
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/utcb_init-ia32.cpp"
#include "gdt.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 25 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/utcb_init-ia32.cpp"


inline Unsigned32
Utcb_init::utcb_segment()
{ return Gdt::gdt_utcb | Gdt::Selector_user; }

#line 30 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/utcb_init-ia32.cpp"



inline void
Utcb_init::init()
{}

#endif // utcb_init_h
