// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "timer_tick.h"
#include "timer_tick_i.h"


#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/timer_tick-apic.cpp"


void
Timer_tick::setup(Cpu_number)
{}

#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/timer_tick-apic.cpp"


void
Timer_tick::enable(Cpu_number)
{
  Apic::timer_enable_irq();
  Apic::irq_ack();
}

#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/timer_tick-apic.cpp"


void
Timer_tick::disable(Cpu_number)
{
  Apic::timer_disable_irq();
}

#line 32 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/timer_tick-apic.cpp"


void
Timer_tick::set_vectors_stop()
{
  extern char entry_int_timer_stop[];
  // acknowledge timer interrupt once to keep timer interrupt alive because
  // we could be called from thread_timer_interrupt_slow() before ack
  Apic::irq_ack();

  // set timer interrupt to dummy doing nothing
  Idt::set_entry(Config::scheduler_irq_vector, (Address)entry_int_timer_stop, false);
#if 0
  // From ``8259A PROGRAMMABLE INTERRUPT CONTROLLER (8259A 8259A-2)'': If no
  // interrupt request is present at step 4 of either sequence (i. e. the
  // request was too short in duration) the 8259A will issue an interrupt
  // level 7. Both the vectoring bytes and the CAS lines will look like an
  // interrupt level 7 was requested.
  set_entry(0x27, (Address)entry_int_pic_ignore, false);
  set_entry(0x2f, (Address)entry_int_pic_ignore, false);
#endif
}

#line 54 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/timer_tick-apic.cpp"

// We are entering with disabled interrupts!
extern "C" FIASCO_FASTCALL
void
thread_timer_interrupt(Address ip)
{
  (void)ip;
  Timer_tick::handler_all(0, 0); //Timer_tick::_glbl_timer);
}

#line 63 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/timer_tick-apic.cpp"

/** Extra version of timer interrupt handler which is used when the jdb is
    active to prevent busy waiting. */
extern "C"
void
thread_timer_interrupt_stop(void)
{
  Apic::irq_ack();
}
