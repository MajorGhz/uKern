// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef obj_space_h
#define obj_space_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space.cpp"

#include "obj_space_types.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space.cpp"
#include "config.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space.cpp"
#include "l4_types.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space.cpp"
#include "template_math.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space-virt.cpp"

#include "mem.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space-virt.cpp"
#include "mem_space.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space-virt.cpp"
#include "ram_quota.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space-virt.cpp"
#include "obj_space_virt_util.h"

//
// INTERFACE definition follows 
//

#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space.cpp"

class Kobject;
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space.cpp"
class Space;
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space.cpp"


template< typename SPACE >
class Generic_obj_space

: Obj_space_virt<Generic_obj_space<SPACE> >
{
  friend class Jdb_obj_space;
  friend class Jdb_tcb;

public:
  static char const * const name;

  typedef Obj::Attr Attr;
  typedef Obj::Capability Capability;
  typedef Obj::Entry Entry;
  typedef Kobject *Reap_list;
  typedef Kobject_iface *Phys_addr;

  typedef Obj::Cap_addr V_pfn;
  typedef Cap_diff V_pfc;
  typedef Order Page_order;


  enum
  {
    Need_insert_tlb_flush = 0,
    Need_xcpu_tlb_flush = 0,
    Map_page_size = 1,
    Page_shift = 0,
    Map_max_address = 1UL << 20, /* 20bit obj index */
    Whole_space = 20,
    Identity_map = 0,
  };

  enum Status
  {
    Insert_ok = Obj::Insert_ok,		///< Mapping was added successfully.
    Insert_warn_exists = Obj::Insert_warn_exists,	///< Mapping already existed
    Insert_warn_attrib_upgrade = Obj::Insert_warn_attrib_upgrade,	///< Mapping already existed, attribs upgrade
    Insert_err_nomem = Obj::Insert_err_nomem,	///< Couldn't alloc new page table
    Insert_err_exists = Obj::Insert_err_exists	///< A mapping already exists at the target addr
  };

  struct Fit_size
  {
    Order operator () (Order s) const
    {
      return s >= Order(Obj::Caps_per_page_ld2)
             ? Order(Obj::Caps_per_page_ld2)
             : Order(0);
    }
  };

  Fit_size fitting_sizes() const { return Fit_size(); }

  static Phys_addr page_address(Phys_addr o, Order) { return o; }
  static Phys_addr subpage_address(Phys_addr addr, V_pfc) { return addr; }
  static V_pfn page_address(V_pfn addr, Order) { return addr; }
  static V_pfc subpage_offset(V_pfn addr, Order o) { return cxx::get_lsb(addr, o); }

  static Phys_addr to_pfn(Phys_addr p) { return p; }
  static V_pfn to_pfn(V_pfn p) { return p; }
  static V_pfc to_pcnt(Order s) { return V_pfc(1) << s; }

  static V_pfc to_size(Page_order p)
  { return V_pfc(1) << p; }

  FIASCO_SPACE_VIRTUAL
  bool v_lookup(V_pfn const &virt, Phys_addr *phys = 0,
                Page_order *size = 0, Attr *attribs = 0);

  FIASCO_SPACE_VIRTUAL
  L4_fpage::Rights v_delete(V_pfn virt, Order size,
                            L4_fpage::Rights page_attribs);

  FIASCO_SPACE_VIRTUAL
  Status v_insert(Phys_addr phys, V_pfn const &virt, Order size,
                  Attr page_attribs);

  FIASCO_SPACE_VIRTUAL
  Capability lookup(Cap_index virt);

  FIASCO_SPACE_VIRTUAL
  V_pfn obj_map_max_address() const;

  FIASCO_SPACE_VIRTUAL
  void caps_free();

  Kobject_iface *lookup_local(Cap_index virt, L4_fpage::Rights *rights = 0);

  inline V_pfn map_max_address() const
  { return obj_map_max_address(); }

#line 109 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space.cpp"
private:

public:
  FIASCO_SPACE_VIRTUAL Entry *jdb_lookup_cap(Cap_index index);

#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space-virt.cpp"
private:

  typedef Obj_space_virt<Generic_obj_space<SPACE> > Base;

public:  
#line 121 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space.cpp"
  static inline Mword
  xlate_flush(L4_fpage::Rights rights);
  
#line 127 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space.cpp"
  static inline bool
  is_full_flush(L4_fpage::Rights rights);
  
#line 133 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space.cpp"
  static inline L4_fpage::Rights
  xlate_flush_result(Mword /*attribs*/);
  
#line 139 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space.cpp"
  inline ~Generic_obj_space();
  
#line 151 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space.cpp"
  inline bool
  v_fabricate(V_pfn const &address,
                                        Phys_addr *phys, Page_order *size,
                                        Attr* attribs = 0);
  
#line 162 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space.cpp"
  static inline void
  tlb_flush_spaces(bool, Generic_obj_space<SPACE> *,
                                             Generic_obj_space<SPACE> *);
  
#line 169 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space.cpp"
  static inline void
  tlb_flush();
  
#line 175 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space.cpp"
  static inline typename Generic_obj_space<SPACE>::V_pfn
  canonize(V_pfn v);
  
#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space-virt.cpp"
  static inline Ram_quota *
  ram_quota(Base const *base);
  
#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space-virt.cpp"
  static inline Mem_space *
  mem_space(Base *base);
  
#line 78 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space-virt.cpp"
  static inline SPACE *
  get_space(Base *base);
};
#line 102 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space.cpp"

template< typename SPACE >
char const * const Generic_obj_space<SPACE>::name = "Obj_space";
#line 105 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space.cpp"


// ------------------------------------------------------------------------------


//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 118 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space.cpp"



template< typename SPACE > inline Mword
Generic_obj_space<SPACE>::xlate_flush(L4_fpage::Rights rights)
{ return L4_fpage::Rights::val(rights); }

#line 124 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space.cpp"



template< typename SPACE > inline bool
Generic_obj_space<SPACE>::is_full_flush(L4_fpage::Rights rights)
{ return rights & L4_fpage::Rights::R(); }

#line 130 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space.cpp"



template< typename SPACE > inline L4_fpage::Rights
Generic_obj_space<SPACE>::xlate_flush_result(Mword /*attribs*/)
{ return L4_fpage::Rights(0); }

#line 136 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space.cpp"



template< typename SPACE > inline Generic_obj_space<SPACE>::~Generic_obj_space()
{
  this->caps_free();
}

#line 148 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space.cpp"



template< typename SPACE > inline bool
Generic_obj_space<SPACE>::v_fabricate(V_pfn const &address,
                                      Phys_addr *phys, Page_order *size,
                                      Attr* attribs)
{
  return this->v_lookup(address, phys, size, attribs);
}

#line 158 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space.cpp"




template< typename SPACE > inline void
Generic_obj_space<SPACE>::tlb_flush_spaces(bool, Generic_obj_space<SPACE> *,
                                           Generic_obj_space<SPACE> *)
{}

#line 166 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space.cpp"



template< typename SPACE > inline void
Generic_obj_space<SPACE>::tlb_flush()
{}

#line 172 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space.cpp"



template< typename SPACE > inline typename Generic_obj_space<SPACE>::V_pfn
Generic_obj_space<SPACE>::canonize(V_pfn v)
{ return v; }

#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space-virt.cpp"

 

template< typename SPACE > inline Ram_quota *
Generic_obj_space<SPACE>::ram_quota(Base const *base)
{ return static_cast<SPACE const *>(base)->ram_quota(); }

#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space-virt.cpp"


 
template< typename SPACE > inline Mem_space *
Generic_obj_space<SPACE>::mem_space(Base *base)
{ return static_cast<SPACE*>(base); }

#line 76 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space-virt.cpp"

 
template< typename SPACE > inline SPACE *
Generic_obj_space<SPACE>::get_space(Base *base)
{ return static_cast<SPACE*>(base); }

#line 143 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space.cpp"

 
template< typename SPACE > inline void __attribute__((__flatten__))
Generic_obj_space<SPACE>::caps_free()
{ Base::caps_free(); }

#line 26 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space-virt.cpp"

//
// Utilities for map<Generic_obj_space> and unmap<Generic_obj_space>
//



template< typename SPACE > inline bool __attribute__((__flatten__))
Generic_obj_space<SPACE>::v_lookup(V_pfn const &virt, Phys_addr *phys,
                                   Page_order *size, Attr *attribs)
{
  return Base::v_lookup(virt, phys, size, attribs);
}

#line 39 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space-virt.cpp"


template< typename SPACE > inline __attribute__((__flatten__))
typename Generic_obj_space<SPACE>::Capability __attribute__((__flatten__))
Generic_obj_space<SPACE>::lookup(Cap_index virt)
{ return Base::lookup(virt); }

#line 45 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space-virt.cpp"


template< typename SPACE > inline __attribute__((__flatten__))
Kobject_iface *
Generic_obj_space<SPACE>::lookup_local(Cap_index virt, L4_fpage::Rights *rights)
{ return Base::lookup_local(virt, rights); }

#line 51 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space-virt.cpp"



template< typename SPACE > inline __attribute__((__flatten__))
L4_fpage::Rights __attribute__((__flatten__))
Generic_obj_space<SPACE>::v_delete(V_pfn virt, Order size,
                                   L4_fpage::Rights page_attribs)
{ return  Base::v_delete(virt, size, page_attribs); }

#line 59 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space-virt.cpp"


template< typename SPACE > inline __attribute__((__flatten__))
typename Generic_obj_space<SPACE>::Status __attribute__((__flatten__))
Generic_obj_space<SPACE>::v_insert(Phys_addr phys, V_pfn const &virt, Order size,
                                   Attr page_attribs)
{ return (Status)Base::v_insert(phys, virt, size, page_attribs); }

#line 66 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space-virt.cpp"



template< typename SPACE > inline __attribute__((__flatten__))
typename Generic_obj_space<SPACE>::V_pfn
Generic_obj_space<SPACE>::obj_map_max_address() const
{ return Base::obj_map_max_address(); }

#line 81 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space-virt.cpp"

 
template< typename SPACE > inline typename Generic_obj_space<SPACE>::Entry *
Generic_obj_space<SPACE>::jdb_lookup_cap(Cap_index index)
{ return Base::jdb_lookup_cap(index); }

#endif // obj_space_h
