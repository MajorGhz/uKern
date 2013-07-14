// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "paging.h"
#include "paging_i.h"

#line 33 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"


//---------------------------------------------------------------------------

#line 39 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"

bool Pt_entry::_have_superpages;
#line 41 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
unsigned  Pt_entry::_super_level;
#line 264 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"

Unsigned32 Pt_entry::_cpu_global = Pt_entry::L4_global;
