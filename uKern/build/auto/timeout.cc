// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "timeout.h"
#include "timeout_i.h"

#line 77 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"

//----------------------------------------------------------------------------------

#line 90 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"


DEFINE_PER_CPU Per_cpu<Timeout_q> Timeout_q::timeout_queue;

#line 155 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"

/* Yeah, i know, an derived and specialized timeout class for
   the root node would be nicer. I already had done this, but
   it was significantly slower than this solution */
bool
Timeout::expired()
{
  kdb_ke("Wakeup List Terminator reached");
  return false;
}
