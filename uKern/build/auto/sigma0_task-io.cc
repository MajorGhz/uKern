// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "sigma0_task.h"
#include "sigma0_task_i.h"


#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sigma0_task-io.cpp"


bool
Sigma0_task::v_fabricate(Io_space::V_pfn address, Io_space::Phys_addr *phys,
                         Io_space::Page_order *size, Io_space::Attr *attribs)
{
  // special-cased because we don't do lookup for sigma0
  *size = Io_space::Page_order(Io_space::Map_superpage_shift);
  *phys = cxx::mask_lsb(address, *size);
  if (attribs)
    *attribs = L4_fpage::Rights::FULL();
  return true;
}
