// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "kobject.h"
#include "kobject_i.h"

#line 111 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"


//---------------------------------------------------------------------------

#line 217 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"

//---------------------------------------------------------------------------


#line 165 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"



inline L4_msg_tag
Kobject::sys_dec_refcnt(L4_msg_tag tag, Utcb const *in, Utcb *out)
{
  if (tag.words() < 2)
    return Kobject_iface::commit_result(-L4_err::EInval);

  Smword diff = in->values[1];
  out->values[0] = dec_cap_refcnt(diff);
  return Kobject_iface::commit_result(0);
}

#line 119 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"


bool  Kobject::is_local(Space *) const { return false; }

#line 122 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"
Mword Kobject::obj_id() const { return ~0UL; }

#line 123 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"
bool  Kobject::put() { return true; }

#line 124 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"
Kobject_mappable *Kobject::map_root() { return this; }

#line 134 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"


void
Kobject::initiate_deletion(Kobject ***reap_list)
{
  existence_lock.invalidate();

  _next_to_reap = 0;
  **reap_list = this;
  *reap_list = &_next_to_reap;
}

#line 145 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"


void
Kobject::destroy(Kobject ***)
{
  LOG_TRACE("Kobject destroy", "des", current(), Log_destroy,
      l->id = dbg_id();
      l->obj = this;
      l->type = kobj_type());
  existence_lock.wait_free();
}

#line 156 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"


Kobject::~Kobject()
{
  LOG_TRACE("Kobject delete (generic)", "del", current(), Log_destroy,
      l->id = dbg_id();
      l->obj = this;
      l->type = "unk");
}

#line 178 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"


L4_msg_tag
Kobject::kobject_invoke(L4_obj_ref, L4_fpage::Rights /*rights*/,
                        Syscall_frame *f,
                        Utcb const *in, Utcb *out)
{
  L4_msg_tag tag = f->tag();

  if (EXPECT_FALSE(tag.words() < 1))
    return Kobject_iface::commit_result(-L4_err::EInval);

  switch (in->values[0])
    {
    case O_dec_refcnt:
      return sys_dec_refcnt(tag, in, out);
    default:
      return Kobject_iface::commit_result(-L4_err::ENosys);
    }

}

#line 234 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"


Kobject_dbg *
Kobject::dbg_info() const
{ return const_cast<Kobject*>(this); }

#line 239 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"


unsigned
Kobject::Log_destroy::print(int max, char *buf) const
{
  return snprintf(buf, max, "obj=%lx [%s] (%p) ram=%lx", id, type, obj, ram);
}
