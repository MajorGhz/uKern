// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "l4_error.h"
#include "l4_error_i.h"

#line 45 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/l4_error.cpp"


//----------------------------------------------------------------------------

#line 49 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/l4_error.cpp"

static char const *__errors[] =
{ "OK", "timeout", "not existent", "canceled", "overflow",
  "xfer snd", "xfer rcv", "aborted", "map failed" };

#line 53 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/l4_error.cpp"




char const *
L4_error::str_error()
{
  return __errors[(_raw >> 1) & 0xf];
}
