// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef scheduler_h
#define scheduler_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"

#include "context.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"
#include "icu_helper.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"
#include "types.h"

//
// INTERFACE definition follows 
//

#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"

class Scheduler : public Icu_h<Scheduler>, public Irq_chip_soft
{
  FIASCO_DECLARE_KOBJ();
  typedef Icu_h<Scheduler> Icu;

public:
  enum Operation
  {
    Info       = 0,
    Run_thread = 1,
    Idle_time  = 2,
  };

  static Scheduler scheduler;
private:
  Irq_base *_irq;

public:  
#line 37 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"
  void
  operator delete(void *);
  
#line 45 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"
  inline Scheduler();
  
#line 169 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"
  inline Irq_base *
  icu_get_irq(unsigned irqnum);
  
#line 179 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"
  inline void
  icu_get_info(Mword *features, Mword *num_irqs, Mword *num_msis);
  
#line 188 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"
  L4_msg_tag
  icu_bind_irq(Irq *irq_o, unsigned irqnum);
  
#line 203 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"
  L4_msg_tag
  icu_set_mode(Mword pin, Irq_chip::Mode);
  
#line 215 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"
  inline void
  trigger_hotplug_event();
  
#line 223 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"
  L4_msg_tag
  kinvoke(L4_obj_ref ref, L4_fpage::Rights rights, Syscall_frame *f,
                     Utcb const *iutcb, Utcb *outcb);

private:  
#line 52 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"
  L4_msg_tag
  sys_run(L4_fpage::Rights, Syscall_frame *f, Utcb const *utcb);
  
#line 123 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"
  L4_msg_tag
  sys_idle_time(L4_fpage::Rights,
                           Syscall_frame *f, Utcb *utcb);
  
#line 142 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"
  L4_msg_tag
  sys_info(L4_fpage::Rights, Syscall_frame *f,
                      Utcb const *iutcb, Utcb *outcb);
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 43 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"


inline Scheduler::Scheduler() : _irq(0)
{
  initial_kobjects.register_obj(this, 7);
}

#line 167 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"


inline Irq_base *
Scheduler::icu_get_irq(unsigned irqnum)
{
  if (irqnum > 0)
    return 0;

  return _irq;
}

#line 177 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"


inline void
Scheduler::icu_get_info(Mword *features, Mword *num_irqs, Mword *num_msis)
{
  *features = 0; // supported features (only normal irqs)
  *num_irqs = 1;
  *num_msis = 0;
}

#line 213 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"


inline void
Scheduler::trigger_hotplug_event()
{
  if (_irq)
    _irq->hit(0);
}

#endif // scheduler_h
