// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef mem_unit_h
#define mem_unit_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/mem_unit-ia32.cpp"

#include "types.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/mem_unit-ia32.cpp"

class Mem_unit
{

public:  
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/mem_unit-ia32.cpp"
  /** Flush the whole TLB.
   */
  
  static inline void
  tlb_flush();
  
#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/mem_unit-ia32.cpp"
  /** Flush TLB at virtual address.
   */
  
  static inline void
  tlb_flush(Address addr);
  
#line 33 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/mem_unit-ia32.cpp"
  static inline void
  clean_dcache(void *);
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/mem_unit-ia32.cpp"

/** Flush the whole TLB.
 */

inline void
Mem_unit::tlb_flush()
{
  unsigned dummy;
  asm volatile ("mov %%cr3,%0; mov %0,%%cr3 " : "=r"(dummy));
}

#line 21 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/mem_unit-ia32.cpp"


/** Flush TLB at virtual address.
 */

inline void
Mem_unit::tlb_flush(Address addr)
{
  asm volatile ("invlpg %0" : : "m" (*(char*)addr) : "memory");
}

#line 31 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/mem_unit-ia32.cpp"


inline void
Mem_unit::clean_dcache(void *)
{}

#endif // mem_unit_h
