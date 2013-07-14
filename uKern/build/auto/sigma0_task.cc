// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "sigma0_task.h"
#include "sigma0_task_i.h"


#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sigma0_task.cpp"


bool
Sigma0_task::v_fabricate(Mem_space::Vaddr address,
                         Mem_space::Phys_addr *phys, Mem_space::Page_order *size,
                         Mem_space::Attr *attribs)
{
  // special-cased because we don't do ptab lookup for sigma0
  *size = static_cast<Mem_space const &>(*this).largest_page_size();
  *phys = cxx::mask_lsb(Virt_addr(address), *size);

  if (attribs)
    *attribs = Mem_space::Attr(L4_fpage::Rights::URWX());

  return true;
}
