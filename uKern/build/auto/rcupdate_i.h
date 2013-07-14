// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef rcupdate_i_h
#define rcupdate_i_h
#line 175 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/rcupdate.cpp"

#include "logdefs.h"
#line 190 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/rcupdate.cpp"

#include "cpu.h"
#line 194 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/rcupdate.cpp"
#include "kdb_ke.h"
#line 196 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/rcupdate.cpp"
#include "mem.h"
#line 197 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/rcupdate.cpp"
#include "static_init.h"
#line 198 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/rcupdate.cpp"
#include "timeout.h"
#line 199 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/rcupdate.cpp"
#include "logdefs.h"
#line 200 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/rcupdate.cpp"

// XXX: includes for debugging
// #include "logdefs.h"


class Rcu_timeout : public Timeout
{

private:  
#line 209 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/rcupdate.cpp"
  /**
   * Timeout expiration callback function
   * @return true if reschedule is necessary, false otherwise
   */
  
  bool
  expired();
};

#endif // rcupdate_i_h
