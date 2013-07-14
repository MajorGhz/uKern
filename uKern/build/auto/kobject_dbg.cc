// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "kobject_dbg.h"
#include "kobject_dbg_i.h"

#line 57 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_dbg.cpp"


//----------------------------------------------------------------------------

#line 62 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_dbg.cpp"
Spin_lock<> Kobject_dbg::_kobjects_lock;
#line 63 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_dbg.cpp"
Kobject_dbg::Kobject_list Kobject_dbg::_kobjects INIT_PRIORITY(101);
#line 64 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_dbg.cpp"
unsigned long Kobject_dbg::_next_dbg_id;

#line 67 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_dbg.cpp"


Kobject_dbg::Iterator
Kobject_dbg::pointer_to_obj(void const *p)
{
  for (Iterator l = _kobjects.begin(); l != _kobjects.end(); ++l)
    {
      Mword a = l->kobject_start_addr();
      if (a <= Mword(p) && Mword(p) < (a + l->kobject_size()))
        return l;
    }
  return _kobjects.end();
}

#line 80 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_dbg.cpp"


unsigned long
Kobject_dbg::pointer_to_id(void const *p)
{
  Iterator o = pointer_to_obj(p);
  if (o != _kobjects.end())
    return o->dbg_id();
  return ~0UL;
}

#line 90 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_dbg.cpp"


bool
Kobject_dbg::is_kobj(void const *o)
{
  return pointer_to_obj(o) != _kobjects.end();
}

#line 97 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_dbg.cpp"


Kobject_dbg::Iterator
Kobject_dbg::id_to_obj(unsigned long id)
{
  for (Iterator l = _kobjects.begin(); l != _kobjects.end(); ++l)
    {
      if (l->dbg_id() == id)
	return l;
    }
  return end();
}

#line 109 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_dbg.cpp"


unsigned long
Kobject_dbg::obj_to_id(void const *o)
{
  return pointer_to_id(o);
}

#line 116 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_dbg.cpp"



Kobject_dbg::Kobject_dbg()
{
  auto guard = lock_guard(_kobjects_lock);

  _dbg_id = _next_dbg_id++;
  _kobjects.push_back(this);
}
