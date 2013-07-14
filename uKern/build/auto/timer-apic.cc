// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "timer.h"
#include "timer_i.h"


#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/timer-apic.cpp"


void
Timer::init(Cpu_number)
{
  Apic::timer_assign_irq_vector(Config::Apic_timer_vector);

  if (Config::Scheduler_one_shot)
    {
      Apic::timer_set_one_shot();
      Apic::timer_reg_write(0xffffffff);
    }
  else
    {
      Apic::timer_set_periodic();
      Apic::timer_reg_write(Apic::us_to_apic(Config::Scheduler_granularity));
    }

  // make sure that PIT does pull its interrupt line
  Pit::done();

  if (!Config::Scheduler_one_shot)
    // from now we can save energy in getchar()
    Config::getchar_does_hlt_works_ok = Config::hlt_works_ok;

  printf ("Using the Local APIC timer on vector %x (%s Mode) for scheduling\n",
          Config::Apic_timer_vector,
          Config::Scheduler_one_shot ? "One-Shot" : "Periodic");
}

#line 48 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/timer-apic.cpp"


void
Timer::update_one_shot(Unsigned64 wakeup)
{
  Unsigned32 apic;
  Unsigned64 now = Kip::k()->clock;
  if (EXPECT_FALSE (wakeup <= now))
    // already expired
    apic = 1;
  else
    {
      Unsigned64 delta = wakeup - now;
      if (delta < Config::One_shot_min_interval_us)
	apic = Apic::us_to_apic(Config::One_shot_min_interval_us);
      else if (delta > Config::One_shot_max_interval_us)
	apic = Apic::us_to_apic(Config::One_shot_max_interval_us);
      else
        apic = Apic::us_to_apic(delta);

      if (EXPECT_FALSE (apic < 1))
	// timeout too small
	apic = 1;
    }

  Apic::timer_reg_write(apic);
}
