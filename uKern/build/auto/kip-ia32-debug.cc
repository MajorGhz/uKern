// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "kip.h"
#include "kip_i.h"


#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/ia32/kip-ia32-debug.cpp"


void
Kip::debug_print_syscalls() const
{
  unsigned kips = kip_sys_calls;
  static char const* const KIPS[] = {"No KIP syscalls supported",
				     "KIP syscalls via KIP relative stubs",
				     "KIP syscalls via absolute stubs",
				     "KIP syscalls ERROR: bad value"};

  if (kips > 3)
    kips = 3;

  printf("%s\n", KIPS[kips]);
}
