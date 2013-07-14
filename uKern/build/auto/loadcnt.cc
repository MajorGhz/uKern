// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "loadcnt.h"
#include "loadcnt_i.h"

#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/loadcnt.cpp"

STATIC_INITIALIZE_P(Loadcnt, WATCHDOG_INIT);

#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/loadcnt.cpp"


void FIASCO_INIT_CPU
Loadcnt::init()
{
  if (Koptions::o()->opt(Koptions::F_loadcnt))
    Perf_cnt::setup_loadcnt();
}
