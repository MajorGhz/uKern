// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef irq_controller_h
#define irq_controller_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_controller.cpp"

#include "irq.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_controller.cpp"
#include "ram_quota.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_controller.cpp"
#include "icu_helper.h"

//
// INTERFACE definition follows 
//

#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_controller.cpp"

class Irq_chip;
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_controller.cpp"

class Icu : public Icu_h<Icu>
{
  FIASCO_DECLARE_KOBJ();

  friend class Icu_h<Icu>;

public:  
#line 29 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_controller.cpp"
  void
  operator delete(void *);
  
#line 37 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_controller.cpp"
  inline Irq_base *
  icu_get_irq(unsigned irqnum);
  
#line 45 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_controller.cpp"
  inline L4_msg_tag
  icu_bind_irq(Irq *irq, unsigned irqnum);
  
#line 57 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_controller.cpp"
  inline L4_msg_tag
  icu_set_mode(Mword pin, Irq_chip::Mode mode);
  
#line 76 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_controller.cpp"
  inline void
  icu_get_info(Mword *features, Mword *num_irqs, Mword *num_msis);
  
#line 85 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_controller.cpp"
  inline L4_msg_tag
  icu_get_msi_info(Mword msi, Utcb *out);
  
#line 94 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_controller.cpp"
  inline Icu();
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_controller.cpp"
#include "irq_mgr.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 35 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_controller.cpp"


inline Irq_base *
Icu::icu_get_irq(unsigned irqnum)
{
  return Irq_mgr::mgr->irq(irqnum);
}

#line 42 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_controller.cpp"



inline L4_msg_tag
Icu::icu_bind_irq(Irq *irq, unsigned irqnum)
{
  irq->unbind();

  if (!Irq_mgr::mgr->alloc(irq, irqnum))
    return commit_result(-L4_err::EPerm);

  return commit_result(0);
}

#line 55 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_controller.cpp"


inline L4_msg_tag
Icu::icu_set_mode(Mword pin, Irq_chip::Mode mode)
{
  Irq_mgr::Irq i = Irq_mgr::mgr->chip(pin);

  if (!i.chip)
    return commit_result(-L4_err::ENodev);

  int r = i.chip->set_mode(i.pin, mode);

  Irq_base *irq = i.chip->irq(i.pin);
  if (irq)
    irq->switch_mode(i.chip->is_edge_triggered(i.pin));

  return commit_result(r);
}

#line 73 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_controller.cpp"



inline void
Icu::icu_get_info(Mword *features, Mword *num_irqs, Mword *num_msis)
{
  *num_irqs = Irq_mgr::mgr->nr_irqs();
  *num_msis = Irq_mgr::mgr->nr_msis();
  *features = *num_msis ? (unsigned)Msi_bit : 0;
}

#line 83 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_controller.cpp"


inline L4_msg_tag
Icu::icu_get_msi_info(Mword msi, Utcb *out)
{
  out->values[0] = Irq_mgr::mgr->msg(msi);
  return commit_result(0, 1);
}

#line 91 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_controller.cpp"



inline Icu::Icu()
{
  initial_kobjects.register_obj(this, 6);
}

#endif // irq_controller_h
