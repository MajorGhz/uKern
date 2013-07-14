// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef vmem_alloc_h
#define vmem_alloc_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vmem_alloc.cpp"

#include "paging.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vmem_alloc.cpp"

class Mem_space;
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vmem_alloc.cpp"

class Vmem_alloc
{
public:

  enum Zero_fill {
    NO_ZERO_FILL = 0,
    ZERO_FILL,		///< Fill the page with zeroes.
  };

  enum
  {
    Kernel = 0,
    User = 1
  };

  static void init();

  static void *page_unmap(void *page);

  /**
   * Allocate a page of kernel memory and insert it into the master
   * page directory.
   *
   * @param address the virtual address where to map the page.
   * @param zf zero fill or zero map.
   * @param pa page attributes to use for the page table entry.
   */
  static void *page_alloc(void *address,
			  Zero_fill zf = NO_ZERO_FILL,
			  unsigned mode = Kernel);

private:
  static void page_map(void *address, int order, Zero_fill zf,
                       Address phys);
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 60 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/vmem_alloc-ia32.cpp"


inline void
Vmem_alloc::page_map(void * /*address*/, int /*order*/, Zero_fill /*zf*/,
		     Address /*phys*/)
{}

#endif // vmem_alloc_h
