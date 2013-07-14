// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "kernel_console.h"
#include "kernel_console_i.h"

#line 25 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_console.cpp"

Static_object<Kconsole> Kconsole::_c;

#line 27 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_console.cpp"



int Kconsole::getchar(bool blocking)
{
  if (!blocking)
    return Mux_console::getchar(false);

  while (1)
    {
      int c;
      if ((c = Mux_console::getchar(false)) != -1)
        return c;

      if (Config::getchar_does_hlt_works_ok // wakeup timer is enabled
          && Proc::interrupts())            // does'nt work without ints
        Proc::halt();
      else
        Proc::pause();
    }
}

#line 57 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_console.cpp"


FIASCO_NOINLINE
void
Kconsole::init()
{ _c.construct(); }
