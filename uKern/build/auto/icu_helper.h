// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef icu_helper_h
#define icu_helper_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/icu_helper.cpp"

#include "irq.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/icu_helper.cpp"
#include "kobject_helper.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/icu_helper.cpp"
#include "l4_buf_iter.h"

//
// INTERFACE definition follows 
//

#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/icu_helper.cpp"

class Icu_h_base
{
public:
  enum Op
  {
    Op_bind       = 0,
    Op_unbind     = 1,
    Op_info       = 2,
    Op_msi_info   = 3,
    Op_eoi        = Irq::Op_eoi_2, // 4
    Op_unmask     = Op_eoi,
    Op_mask       = 5,
    Op_set_mode   = 6,
  };

  enum Feature
  {
    Msi_bit = 0x80000000
  };

protected:  
#line 45 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/icu_helper.cpp"
  Irq *
  deref_irq(L4_msg_tag *tag, Utcb const *utcb);
};
#line 27 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/icu_helper.cpp"


template< typename REAL_ICU >
class Icu_h : public Kobject_h<REAL_ICU>, public Icu_h_base
{
protected:
  REAL_ICU const *this_icu() const
  { return nonull_static_cast<REAL_ICU const *>(this); }

  REAL_ICU *this_icu()
  { return nonull_static_cast<REAL_ICU *>(this); }

public:  
#line 87 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/icu_helper.cpp"
  inline void
  icu_mask_irq(bool mask, unsigned irqnum);
  
#line 103 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/icu_helper.cpp"
  inline L4_msg_tag
  icu_unbind_irq(unsigned irqnum);
  
#line 116 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/icu_helper.cpp"
  inline L4_msg_tag
  icu_get_msi_info(Mword msi, Utcb *out);
  
#line 126 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/icu_helper.cpp"
  inline L4_msg_tag
  icu_invoke(L4_obj_ref, L4_fpage::Rights /*rights*/,
                              Syscall_frame *f,
                              Utcb const *utcb, Utcb *out);
  
#line 183 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/icu_helper.cpp"
  L4_msg_tag
  kinvoke(L4_obj_ref ref, L4_fpage::Rights rights,
                           Syscall_frame *f,
                           Utcb const *in, Utcb *out);
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 83 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/icu_helper.cpp"




template<typename REAL_ICU> inline void
Icu_h<REAL_ICU>::icu_mask_irq(bool mask, unsigned irqnum)
{
  Irq_base *i = this_icu()->icu_get_irq(irqnum);

  if (EXPECT_FALSE(!i))
    return;

  if (mask)
    i->mask();
  else
    i->unmask();
}

#line 100 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/icu_helper.cpp"



template<typename REAL_ICU> inline L4_msg_tag
Icu_h<REAL_ICU>::icu_unbind_irq(unsigned irqnum)
{
  Irq_base *irq = this_icu()->icu_get_irq(irqnum);

  if (irq)
    irq->unbind();

  return Kobject_iface::commit_result(0);
}

#line 113 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/icu_helper.cpp"



template<typename REAL_ICU> inline L4_msg_tag
Icu_h<REAL_ICU>::icu_get_msi_info(Mword msi, Utcb *out)
{
  (void) msi;
  (void) out;
  return Kobject_iface::commit_result(-L4_err::EInval);
}

#line 123 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/icu_helper.cpp"



template< typename REAL_ICU > inline L4_msg_tag
Icu_h<REAL_ICU>::icu_invoke(L4_obj_ref, L4_fpage::Rights /*rights*/,
                            Syscall_frame *f,
                            Utcb const *utcb, Utcb *out)
{
  L4_msg_tag tag = f->tag();

  switch (utcb->values[0])
    {
    case Op_bind:
      if (tag.words() < 2)
	return Kobject_iface::commit_result(-L4_err::EInval);

      if (Irq *irq = deref_irq(&tag, utcb))
	return this_icu()->icu_bind_irq(irq, utcb->values[1]);
      else
	return tag;

    case Op_unbind:
      if (tag.words() < 2)
	return Kobject_iface::commit_result(-L4_err::EInval);

      if (deref_irq(&tag, utcb))
	return this_icu()->icu_unbind_irq(utcb->values[1]);
      else
	return tag;

    case Op_info:
      this_icu()->icu_get_info(&out->values[0], &out->values[1], &out->values[2]);
      return Kobject_iface::commit_result(0, 3);

    case Op_msi_info:
      if (tag.words() < 2)
	return Kobject_iface::commit_result(-L4_err::EInval);
      return this_icu()->icu_get_msi_info(utcb->values[1], out);

    case Op_unmask:
    case Op_mask:
      if (tag.words() < 2)
	return Kobject_h<REAL_ICU>::no_reply();

      this_icu()->icu_mask_irq(utcb->values[0] == Op_mask, utcb->values[1]);
      return Kobject_h<REAL_ICU>::no_reply();

    case Op_set_mode:
      if (tag.words() >= 3)
        return this_icu()->icu_set_mode(utcb->values[1],
                                        Irq_chip::Mode(utcb->values[2]));
      return Kobject_iface::commit_result(-L4_err::EInval);

    default:
      return Kobject_iface::commit_result(-L4_err::ENosys);
    }
}

//
// IMPLEMENTATION of function templates
//


#line 180 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/icu_helper.cpp"



template< typename REAL_ICU > L4_msg_tag
Icu_h<REAL_ICU>::kinvoke(L4_obj_ref ref, L4_fpage::Rights rights,
                         Syscall_frame *f,
                         Utcb const *in, Utcb *out)
{
  L4_msg_tag tag = f->tag();

  if (EXPECT_FALSE(tag.proto() != L4_msg_tag::Label_irq))
    return Kobject_iface::commit_result(-L4_err::EBadproto);

  return icu_invoke(ref, rights, f, in, out);
}

#endif // icu_helper_h
