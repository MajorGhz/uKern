// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "space.h"
#include "space_i.h"

#line 110 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"


//---------------------------------------------------------------------------


#line 130 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"


Space::Ku_mem const *
Space::find_ku_mem(User<void>::Ptr p, unsigned size)
{
  Address const pa = (Address)p.get();

  // alignment check
  if (EXPECT_FALSE(pa & (sizeof(double) - 1)))
    return 0;

  // overflow check
  if (EXPECT_FALSE(pa + size < pa))
    return 0;

  for (Ku_mem_list::Const_iterator f = _ku_mem.begin(); f != _ku_mem.end(); ++f)
    {
      Address const a = (Address)f->u_addr.get();
      if (a <= pa && (a + f->size) >= (pa + size))
	return *f;
    }

  return 0;
}
