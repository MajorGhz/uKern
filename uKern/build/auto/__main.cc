// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "__main.h"
#include "__main_i.h"

#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/__main.cpp"

void kernel_main(void);

#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/__main.cpp"

extern "C" FIASCO_FASTCALL FIASCO_INIT
void
__main(Address /*mbi_phys*/, unsigned aflag, unsigned checksum_ro)
{
  /* set global to be used in the constructors */
  Boot_info::set_flags(aflag);
  Boot_info::set_checksum_ro(checksum_ro);
  Boot_info::init();

  atexit(&static_destruction);
  static_construction();

  kernel_main();
  exit(0);
}
