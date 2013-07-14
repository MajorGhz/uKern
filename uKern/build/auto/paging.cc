// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "paging.h"
#include "paging_i.h"

#line 124 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/paging.cpp"

//---------------------------------------------------------------------------


#line 127 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/paging.cpp"


Address
Pdir::virt_to_phys(Address virt) const
{
  Virt_addr va(virt);
  auto i = walk(va);
  if (!i.is_valid())
    return ~0;

  return i.page_addr() | cxx::get_lsb(virt, i.page_order());
}
