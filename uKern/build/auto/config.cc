// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "config.h"
#include "config_i.h"

#line 220 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/config.cpp"

KIP_KERNEL_ABI_VERSION(STRINGIFY(FIASCO_KERNEL_SUBVERSION));
#line 222 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/config.cpp"

// class variables
bool Config::esc_hack = false;
#line 225 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/config.cpp"
#ifdef CONFIG_SERIAL
#line 226 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/config.cpp"
int  Config::serial_esc = Config::SERIAL_NO_ESC;
#line 227 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/config.cpp"
#endif
#line 228 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/config.cpp"

unsigned Config::tbuf_entries = 0x20000 / sizeof(Mword); //1024;
#line 230 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/config.cpp"
bool Config::getchar_does_hlt_works_ok = false;
#line 231 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/config.cpp"
unsigned Config::num_ap_cpus;
#line 232 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/config.cpp"

#ifdef CONFIG_FINE_GRAINED_CPUTIME
#line 234 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/config.cpp"
KIP_KERNEL_FEATURE("fi_gr_cputime");
#line 235 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/config.cpp"
#endif
#line 236 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/config.cpp"

//-----------------------------------------------------------------------------


#line 239 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/config.cpp"

FIASCO_INIT
void Config::init()
{
  init_arch();

  if (Koptions::o()->opt(Koptions::F_esc))
    esc_hack = true;

#ifdef CONFIG_SERIAL
  if (    Koptions::o()->opt(Koptions::F_serial_esc)
      && !Koptions::o()->opt(Koptions::F_noserial)
# ifdef CONFIG_KDB
      &&  Koptions::o()->opt(Koptions::F_nokdb)
# endif
      && !Koptions::o()->opt(Koptions::F_nojdb))
    {
      serial_esc = SERIAL_ESC_IRQ;
    }
#endif
}
