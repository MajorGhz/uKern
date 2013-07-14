// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kip_init_h
#define kip_init_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kip_init-ia32.cpp"

#include "initcalls.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kip_init-ia32.cpp"
#include "types.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kip_init-ia32.cpp"
#include "kip.h"

//
// INTERFACE definition follows 
//

#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kip_init-ia32.cpp"

class Cpu;
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kip_init-ia32.cpp"


class Kip_init
{
public:
  /**
   * Insert memory descriptor for the Kmem region and finish the memory
   * info field.
   * @post no more memory descriptors may be added
   */
  static void setup_kmem_region (Address kmem_base, Address kmem_size);

public:  
#line 39 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kip_init-ia32.cpp"
  /** KIP initialization. */
  static FIASCO_INIT
  void
  init_freq(Cpu const &cpu);
  
#line 86 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kip_init-ia32.cpp"
  static FIASCO_INIT
  //IMPLEMENT
  void init();
  
#line 148 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kip_init-ia32.cpp"
  static FIASCO_INIT
  void
  setup_user_virtual(Kip *kinfo);

private:  
#line 24 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kip_init-ia32.cpp"
  static inline void
  setup_ux(Kip *);
  
#line 142 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kip_init-ia32.cpp"
  static inline void
  reserve_amd64_hole();
};

#endif // kip_init_h
