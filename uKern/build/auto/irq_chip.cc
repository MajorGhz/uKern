// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "irq_chip.h"
#include "irq_chip_i.h"

#line 203 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"


//--------------------------------------------------------------------------

#line 212 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"

Irq_chip_soft Irq_chip_soft::sw_chip INIT_PRIORITY(EARLY_INIT_PRIO);
#line 214 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"
Irq_base *(*Irq_base::dcast)(Kobject_iface *);
#line 322 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"


// --------------------------------------------------------------------------


#line 331 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"


unsigned
Irq_base::Irq_log::print(int maxlen, char *buf) const
{
  Kobject_dbg::Const_iterator irq = Kobject_dbg::pointer_to_obj(obj);

  if (irq != Kobject_dbg::end())
    return snprintf(buf, maxlen, "0x%lx/%lu @ chip %s(%p) D:%lx",
                    pin, pin, chip->chip_type(), chip,
                    irq->dbg_id());
  else
    return snprintf(buf, maxlen, "0x%lx/%lu @ chip %s(%p) irq=%p",
                    pin, pin, chip->chip_type(), chip,
                    obj);
}
