// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "boot_info.h"
#include "boot_info_i.h"

#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"

//-----------------------------------------------------------------------------

#line 21 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"

// these members needs to be initialized with some
// data to go into the data section and not into bss
unsigned Boot_info::_flag          = 3;
#line 25 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"
unsigned Boot_info::_checksum_ro   = 15;
#line 26 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"
unsigned Boot_info::_checksum_rw   = 16;

#line 50 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"
//@}



void
Boot_info::init()
{}

#line 78 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"


void
Boot_info::reset_checksum_ro(void)
{
  set_checksum_ro(Checksum::get_checksum_ro());
}
