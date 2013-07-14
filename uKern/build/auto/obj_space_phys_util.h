// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef obj_space_phys_util_h
#define obj_space_phys_util_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"

#include "assert_opt.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
#include "obj_space_types.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
#include "ram_quota.h"

//
// INTERFACE definition follows 
//

#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"

template< typename SPACE >
class Obj_space_phys
{
public:
  typedef Obj::Attr Attr;
  typedef Obj::Capability Capability;
  typedef Obj::Entry Entry;
  typedef Kobject_iface *Phys_addr;

  typedef Obj::Cap_addr V_pfn;
  typedef Cap_diff V_pfc;
  typedef Order Page_order;

  bool v_lookup(V_pfn const &virt, Phys_addr *phys,
                Page_order *size, Attr *attribs);

  L4_fpage::Rights v_delete(V_pfn virt, Order size,
                            L4_fpage::Rights page_attribs);
  Obj::Insert_result v_insert(Phys_addr phys, V_pfn const &virt, Order size,
                              Attr page_attribs);

  Capability lookup(Cap_index virt);

private:
  enum
  {
    Slots_per_dir = Config::PAGE_SIZE / sizeof(void*)
  };

  struct Cap_table { Entry e[Obj::Caps_per_page]; };
  struct Cap_dir   { Cap_table *d[Slots_per_dir]; };
  Cap_dir *_dir;

  Ram_quota *ram_quota() const
  {
    assert_opt (this);
    return SPACE::ram_quota(this);
  }

public:  
#line 65 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
  inline Obj_space_phys();
  
#line 116 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
  void
  caps_free();
  
#line 180 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
  inline Kobject_iface *
  lookup_local(Cap_index virt, L4_fpage::Rights *rights);
  
#line 254 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
  inline typename Obj_space_phys<SPACE>::V_pfn
  obj_map_max_address() const;
  
#line 264 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
  typename Obj_space_phys<SPACE>::Entry *
  jdb_lookup_cap(Cap_index index);

private:  
#line 74 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
  typename Obj_space_phys<SPACE>::Entry *
  get_cap(Cap_index index);
  
#line 94 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
  typename Obj_space_phys<SPACE>::Entry *
  caps_alloc(Cap_index virt);
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 50 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"

#include <cstring>
#line 52 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
#include <cassert>
#line 53 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"

#include "atomic.h"
#line 55 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
#include "config.h"
#line 56 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
#include "cpu.h"
#line 57 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
#include "kmem_alloc.h"
#line 58 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
#include "mem.h"
#line 59 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
#include "mem_layout.h"
#line 60 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
#include "ram_quota.h"
#line 61 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
#include "static_assert.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 62 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"



template< typename SPACE > inline Obj_space_phys<SPACE>::Obj_space_phys()
{
  static_assert(sizeof(Cap_dir) == Config::PAGE_SIZE, "cap_dir size mismatch");
  _dir = (Cap_dir*)Kmem_alloc::allocator()->q_unaligned_alloc(ram_quota(), Config::PAGE_SIZE);
  if (_dir)
    Mem::memset_mwords(_dir, 0, Config::PAGE_SIZE / sizeof(Mword));
}

#line 177 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"



template< typename SPACE > inline Kobject_iface *
Obj_space_phys<SPACE>::lookup_local(Cap_index virt, L4_fpage::Rights *rights)
{
  Entry *c = get_cap(virt);

  if (EXPECT_FALSE(!c))
    return 0;

  Capability cap = *c;

  if (rights)
    *rights = L4_fpage::Rights(cap.rights());

  return cap.obj();
}

#line 250 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"




template< typename SPACE > inline typename Obj_space_phys<SPACE>::V_pfn
Obj_space_phys<SPACE>::obj_map_max_address() const
{
  return V_pfn(Slots_per_dir * Obj::Caps_per_page);
}

#line 137 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"

//
// Utilities for map<Obj_space_phys> and unmap<Obj_space_phys>
//



template< typename SPACE > inline bool __attribute__((__flatten__))
Obj_space_phys<SPACE>::v_lookup(V_pfn const &virt, Phys_addr *phys,
                                Page_order *size, Attr *attribs)
{
  if (size) *size = Page_order(0);
  Entry *cap = get_cap(virt);

  if (EXPECT_FALSE(!cap))
    {
      if (size) *size = Page_order(Obj::Caps_per_page_ld2);
      return false;
    }

  Capability c = *cap;

  Obj::set_entry(virt, cap);
  if (phys) *phys = c.obj();
  if (c.valid() && attribs) *attribs = cap->rights();
  return c.valid();
}

#line 164 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"



template< typename SPACE > inline typename Obj_space_phys<SPACE>::Capability __attribute__((__flatten__))
Obj_space_phys<SPACE>::lookup(Cap_index virt)
{
  Capability *c = get_cap(virt);

  if (EXPECT_FALSE(!c))
    return Capability(0); // void

  return *c;
}

#line 195 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"




template< typename SPACE > inline L4_fpage::Rights __attribute__((__flatten__))
Obj_space_phys<SPACE>::v_delete(V_pfn virt, Page_order size,
                                   L4_fpage::Rights page_attribs)
{
  (void)size;
  assert (size == Page_order(0));
  Capability *c = get_cap(virt);

  if (c && c->valid())
    {
      if (page_attribs & L4_fpage::Rights::R())
        c->invalidate();
      else
	c->del_rights(page_attribs);
    }

  return L4_fpage::Rights(0);
}

#line 217 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"



template< typename SPACE > inline typename Obj::Insert_result __attribute__((__flatten__))
Obj_space_phys<SPACE>::v_insert(Phys_addr phys, V_pfn const &virt, Page_order size,
                                Attr page_attribs)
{
  (void)size;
  assert (size == Page_order(0));

  Entry *c = get_cap(virt);

  if (!c && !(c = caps_alloc(virt)))
    return Obj::Insert_err_nomem;

  if (c->valid())
    {
      if (c->obj() == phys)
	{
	  if (EXPECT_FALSE(c->rights() == page_attribs))
	    return Obj::Insert_warn_exists;

	  c->add_rights(page_attribs);
	  return Obj::Insert_warn_attrib_upgrade;
	}
      else
	return Obj::Insert_err_exists;
    }

  Obj::set_entry(virt, c);
  c->set(phys, page_attribs);
  return Obj::Insert_ok;
}

//
// IMPLEMENTATION of function templates
//


#line 72 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"


template< typename SPACE > typename Obj_space_phys<SPACE>::Entry *
Obj_space_phys<SPACE>::get_cap(Cap_index index)
{
  if (EXPECT_FALSE(!_dir))
    return 0;

  unsigned d_idx = cxx::int_value<Cap_index>(index) >> Obj::Caps_per_page_ld2;
  if (EXPECT_FALSE(d_idx >= Slots_per_dir))
    return 0;

  Cap_table *tab = _dir->d[d_idx];

  if (EXPECT_FALSE(!tab))
    return 0;

  unsigned offs  = cxx::get_lsb(cxx::int_value<Cap_index>(index), Obj::Caps_per_page_ld2);
  return &tab->e[offs];
}

#line 92 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"


template< typename SPACE > typename Obj_space_phys<SPACE>::Entry *
Obj_space_phys<SPACE>::caps_alloc(Cap_index virt)
{
  static_assert(sizeof(Cap_table) == Config::PAGE_SIZE, "cap table size mismatch");
  unsigned d_idx = cxx::int_value<Cap_index>(virt) >> Obj::Caps_per_page_ld2;
  if (EXPECT_FALSE(d_idx >= Slots_per_dir))
    return 0;

  void *mem = Kmem_alloc::allocator()->q_unaligned_alloc(ram_quota(), Config::PAGE_SIZE);

  if (!mem)
    return 0;

  Obj::add_cap_page_dbg_info(mem, SPACE::get_space(this),  cxx::int_value<Cap_index>(virt));

  Mem::memset_mwords(mem, 0, Config::PAGE_SIZE / sizeof(Mword));

  Cap_table *tab = _dir->d[d_idx] = (Cap_table*)mem;
  return &tab->e[ cxx::get_lsb(cxx::int_value<Cap_index>(virt), Obj::Caps_per_page_ld2)];
}

#line 114 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"


template< typename SPACE > void
Obj_space_phys<SPACE>::caps_free()
{
  if (!_dir)
    return;

  Cap_dir *d = _dir;
  _dir = 0;

  Kmem_alloc *a = Kmem_alloc::allocator();
  for (unsigned i = 0; i < Slots_per_dir; ++i)
    {
      if (!d->d[i])
        continue;

      Obj::remove_cap_page_dbg_info(d->d[i]);
      a->q_unaligned_free(ram_quota(), Config::PAGE_SIZE, d->d[i]);
    }

  a->q_unaligned_free(ram_quota(), Config::PAGE_SIZE, d);
}

#line 262 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"


template< typename SPACE > typename Obj_space_phys<SPACE>::Entry *
Obj_space_phys<SPACE>::jdb_lookup_cap(Cap_index index)
{ return get_cap(index); }

#endif // obj_space_phys_util_h
