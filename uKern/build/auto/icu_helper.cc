// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "icu_helper.h"
#include "icu_helper_i.h"


#line 42 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/icu_helper.cpp"



Irq *
Icu_h_base::deref_irq(L4_msg_tag *tag, Utcb const *utcb)
{
  L4_snd_item_iter snd_items(utcb, tag->words());
  Irq *irq;

  if (!tag->items() || !snd_items.next())
    {
      *tag = Kobject_iface::commit_result(-L4_err::EInval);
      return 0;
    }

  L4_fpage bind_irq(snd_items.get()->d);
  if (EXPECT_FALSE(!bind_irq.is_objpage()))
    {
      *tag = Kobject_iface::commit_error(utcb, L4_error::Overflow);
      return 0;
    }

  register Context *const c_thread = ::current();
  register Space *const c_space = c_thread->space();
  L4_fpage::Rights irq_rights = L4_fpage::Rights(0);
  irq = Kobject::dcast<Irq*>(c_space->lookup_local(bind_irq.obj_index(), &irq_rights));

  if (!irq)
    {
      *tag = Kobject_iface::commit_result(-L4_err::EInval);
      return 0;
    }

  if (EXPECT_FALSE(!(irq_rights & L4_fpage::Rights::X())))
    {
      *tag = Kobject_iface::commit_result(-L4_err::EPerm);
      return 0;
    }

  return irq;
}
