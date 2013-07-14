// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef timer_h
#define timer_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timer.cpp"

#include "initcalls.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timer.cpp"
#include "l4_types.h"

//
// INTERFACE definition follows 
//

#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timer.cpp"

class Timer
{
public:
  /**
   * Static constructor for the interval timer.
   *
   * The implementation is platform specific. Two x86 implementations
   * are timer-pit and timer-rtc.
   */
  static void init(Cpu_number cpu) FIASCO_INIT_CPU;

  /**
   * Initialize the system clock.
   */
  static void init_system_clock();

  /**
   * Advances the system clock.
   */
  static void update_system_clock(Cpu_number cpu);

  /**
   * Get the current system clock.
   */
  static Unsigned64 system_clock();

  /**
   * reprogram the one-shot timer to the next event.
   */
  static void update_timer(Unsigned64 wakeup);

  static void master_cpu(Cpu_number cpu) { _cpu = cpu; }

private:
  static Cpu_number _cpu;

public:  
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/timer-apic.cpp"
  // no IRQ line for the LAPIC
  static inline int irq();
  
#line 45 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/timer-apic.cpp"
  static inline void
  acknowledge();

private:  
#line 50 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/timer-apic.cpp"
  static void
  update_one_shot(Unsigned64 wakeup);
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/timer-ia32-amd64-ux.cpp"
#include "globals.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/timer-ia32-amd64-ux.cpp"
#include "kip.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/timer-apic.cpp"
#include "config.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/timer-apic.cpp"
#include "cpu.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/timer-apic.cpp"

// no IRQ line for the LAPIC
inline int Timer::irq() { return -1; }

#line 43 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/timer-apic.cpp"


inline void
Timer::acknowledge()
{}

#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/timer-ia32-amd64-ux.cpp"


inline void
Timer::init_system_clock()
{
  if (Config::Kip_timer_uses_rdtsc)
    Kip::k()->clock = Cpu::cpus.cpu(_cpu).time_us();
  else
    Kip::k()->clock = 0;
}

#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/timer-ia32-amd64-ux.cpp"


inline Unsigned64
Timer::system_clock()
{
  if (current_cpu() == Cpu_number::boot_cpu()
      && Config::Kip_timer_uses_rdtsc)
    Kip::k()->clock = Cpu::cpus.cpu(_cpu).time_us();

  return Kip::k()->clock;
}

#line 28 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/timer-ia32-amd64-ux.cpp"


inline void
Timer::update_system_clock(Cpu_number cpu)
{
  if (cpu != Cpu_number::boot_cpu())
    return;

  if (Config::Kip_timer_uses_rdtsc)
    Kip::k()->clock = Cpu::cpus.cpu(Cpu_number::boot_cpu()).time_us();
  else
    Kip::k()->clock += Config::Scheduler_granularity;
}

#line 75 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/timer-apic.cpp"


inline void
Timer::update_timer(Unsigned64 wakeup)
{
  if (Config::Scheduler_one_shot)
    update_one_shot(wakeup);
}

#endif // timer_h
