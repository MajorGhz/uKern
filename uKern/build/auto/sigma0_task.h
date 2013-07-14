// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef sigma0_task_h
#define sigma0_task_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sigma0_task.cpp"

#include "task.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sigma0_task.cpp"

class Sigma0_task : public Task
{
public:
  explicit Sigma0_task(Ram_quota *q, Caps c) : Task(q, c) {}
  bool is_sigma0() const { return true; }
  Address virt_to_phys_s0(void *virt) const
  { return (Address)virt; }

public:  
#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sigma0_task.cpp"
  bool
  v_fabricate(Mem_space::Vaddr address,
                           Mem_space::Phys_addr *phys, Mem_space::Page_order *size,
                           Mem_space::Attr *attribs = 0);
  
#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sigma0_task.cpp"
  inline Page_number
  mem_space_map_max_address() const;
  
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sigma0_task-io.cpp"
  bool
  v_fabricate(Io_space::V_pfn address, Io_space::Phys_addr *phys,
                           Io_space::Page_order *size, Io_space::Attr *attribs = 0);
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 32 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sigma0_task.cpp"


inline Page_number
Sigma0_task::mem_space_map_max_address() const
{ return Page_number(1UL << (MWORD_BITS - Mem_space::Page_shift)); }

#endif // sigma0_task_h
