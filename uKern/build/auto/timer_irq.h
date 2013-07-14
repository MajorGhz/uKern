// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef timer_irq_h
#define timer_irq_h

//
// INTERFACE definition follows 
//


#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/timer_irq.cpp"
/** Slow version of timer interrupt.  Activated on every clock tick.
    Checks if something related to debugging is to do. After returning
    from this function, the real timer interrupt handler is called.
 */
extern "C"
void
thread_timer_interrupt_slow(void);

#endif // timer_irq_h
