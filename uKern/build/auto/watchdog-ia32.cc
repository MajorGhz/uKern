// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "watchdog.h"
#include "watchdog_i.h"

#line 26 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"

// ------------------------------------------------------------------------

#line 39 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"

#define WATCHDOG_TIMEOUT_S	2
#line 41 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"

void (*Watchdog::touch)(void)     = Watchdog::do_nothing;
#line 43 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"
void (*Watchdog::enable)(void)    = Watchdog::do_nothing;
#line 44 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"
void (*Watchdog::disable)(void)   = Watchdog::do_nothing;
#line 45 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"

Watchdog::Watchdog_flags Watchdog::flags;
#line 106 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"

STATIC_INITIALIZE_P(Watchdog, WATCHDOG_INIT);

#line 47 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"

void
Watchdog::do_nothing()
{}

#line 51 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"

void
Watchdog::perf_enable()
{
  if (flags.active && flags.user_active)
    {
      Perf_cnt::touch_watchdog();
      Perf_cnt::start_watchdog();
      Apic::set_perf_nmi();
    }
}

#line 62 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"

void
Watchdog::perf_disable()
{
  if (flags.active)
    Perf_cnt::stop_watchdog();
}

#line 69 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"

void
Watchdog::perf_touch()
{
  if (flags.active && flags.user_active && flags.no_user_control)
    Perf_cnt::touch_watchdog();
}

#line 108 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"


void FIASCO_INIT
Watchdog::init()
{
  if (!Config::watchdog)
    return;

  printf("Watchdog: LAPIC=%s, PCINT=%s, PC=%s\n",
         Apic::is_present() ? "yes" : "no",
         Apic::have_pcint() ? "yes" : "no",
         Perf_cnt::have_watchdog() ? "yes" : "no");

  if (   !Apic::is_present()
      || !Apic::have_pcint()
      || !Perf_cnt::have_watchdog())
    panic("Cannot initialize watchdog (no/bad Local APIC)");

  // attach performance counter interrupt tom NMI
  Apic::set_perf_nmi();

  // start counter
  Perf_cnt::setup_watchdog(WATCHDOG_TIMEOUT_S);

  touch   = perf_touch;
  enable  = perf_enable;
  disable = perf_disable;

  flags.active = 1;
  flags.user_active = 1;
  flags.no_user_control = 1;

  printf("Watchdog initialized\n");
}
