// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "dirq.h"
#include "dirq_i.h"


#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/dirq-ia32-ux.cpp"
// screen spinner for debugging purposes
static inline void irq_spinners(int irqnum);

#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/dirq-ia32-ux.cpp"

// screen spinner for debugging purposes
static inline void irq_spinners(int irqnum)
{
#ifdef CONFIG_IRQ_SPINNER
  Unsigned16 *p = (Unsigned16 *)Mem_layout::Adap_vram_cga_beg;
  p += (20 + cxx::int_value<Cpu_number>(current_cpu())) * 80 + irqnum;
  if (p < (Unsigned16 *)Mem_layout::Adap_vram_cga_end)
    (*p)++;
#else
  (void)irqnum;
#endif
}

#line 30 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/dirq-ia32-ux.cpp"

/** Hardware interrupt entry point.  Calls corresponding Dirq instance's
    Dirq::hit() method.
    @param irqobj hardware-interrupt object
 */
extern "C" FIASCO_FASTCALL
void
irq_interrupt(Mword _irqobj, Mword ip)
{
  Mword irqobj = (Smword)((Signed32)_irqobj);
  Thread::assert_irq_entry();

  CNT_IRQ;
  (void)ip;

  // we're entered with disabled irqs
  Irq_base *i = (Irq_base*)irqobj;
  i->log();
  irq_spinners(i->pin());
  i->hit(0);
}
