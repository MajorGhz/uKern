// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "keyb.h"
#include "keyb_i.h"


#line 25 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/keyb.cpp"


int
Keyb::write(char const *, size_t len)
{
  return len;
}

#line 32 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/keyb.cpp"


Mword
Keyb::get_attributes() const
{
  return DIRECT | IN;
}
