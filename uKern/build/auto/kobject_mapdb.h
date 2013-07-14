// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kobject_mapdb_h
#define kobject_mapdb_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_mapdb.cpp"

#include "types.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_mapdb.cpp"
#include "space.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_mapdb.cpp"
#include "kobject.h"

//
// INTERFACE definition follows 
//

#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_mapdb.cpp"

class Kobject;
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_mapdb.cpp"

/** A mapping database.
 */
class Kobject_mapdb
{
public:
  // TYPES

  typedef Obj_space::Phys_addr Phys_addr;
  typedef Obj_space::V_pfn Vaddr;
  typedef Obj::Mapping Mapping;

  class Iterator;
  class Frame 
  {
    friend class Kobject_mapdb;
    friend class Kobject_mapdb::Iterator;
    Kobject_mappable* frame;

  public:
    inline size_t size() const;
  };

  /**
   * We'll never iterate over some thing, because we have
   * no child relationship for capability passing.
   */
  class Iterator
  {
  public:
    inline Mapping* operator->() const { return 0; }
    inline Mapping* operator * () const { return 0; }
    inline operator Mapping*() const   { return 0; }
    Iterator() {}

    Iterator(Frame const &, Mapping *, Obj_space::V_pfn, Obj_space::V_pfn) {}

    Iterator &operator ++ () { return *this; }
  };

public:  
#line 60 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_mapdb.cpp"
  static inline bool
  lookup(Space *, Vaddr va, Phys_addr obj,
                        Mapping** out_mapping, Frame* out_lock);
  
#line 78 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_mapdb.cpp"
  static inline bool
  valid_address(Phys_addr obj);
  
#line 83 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_mapdb.cpp"
  // FAKE
  
  static inline Page_number
  vaddr(const Frame&, Mapping*);
  
#line 90 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_mapdb.cpp"
  inline Kobject_mapdb::Mapping *
  check_for_upgrade(Obj_space::Phys_addr,
                                   Space *, Obj_space::V_pfn,
                                   Space *, Obj_space::V_pfn,
                                   Frame *);
  
#line 101 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_mapdb.cpp"
  static inline Kobject_mapdb::Mapping *
  insert(const Frame&, Mapping*, Space *,
                        Vaddr va, Obj_space::Phys_addr o, Obj_space::V_pfc size);
  
#line 122 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_mapdb.cpp"
  static inline bool
  grant(const Frame &f, Mapping *sm, Space *,
                       Vaddr va);
  
#line 140 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_mapdb.cpp"
  static inline void 
  free(const Frame& f);
  
#line 147 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_mapdb.cpp"
  static inline void
  flush(const Frame& f, Mapping *m, L4_map_mask mask,
                       Obj_space::V_pfn, Obj_space::V_pfn);
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 58 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_mapdb.cpp"


inline bool
Kobject_mapdb::lookup(Space *, Vaddr va, Phys_addr obj,
                      Mapping** out_mapping, Frame* out_lock)
{
  Kobject_mappable *rn = obj->map_root(); 
  rn->_lock.lock();
  if (va._c->obj() == obj)
    {
      *out_mapping = va._c;
      out_lock->frame = rn;
      return true;
    }

  rn->_lock.clear();
  return false;
}

#line 76 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_mapdb.cpp"


inline bool
Kobject_mapdb::valid_address(Phys_addr obj)
{ return obj; }

#line 81 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_mapdb.cpp"


// FAKE

inline Page_number
Kobject_mapdb::vaddr(const Frame&, Mapping*)
{ return Page_number(0); }

#line 88 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_mapdb.cpp"


inline Kobject_mapdb::Mapping *
Kobject_mapdb::check_for_upgrade(Obj_space::Phys_addr,
                                 Space *, Obj_space::V_pfn,
                                 Space *, Obj_space::V_pfn,
                                 Frame *)
{
  // Hm we never or seldomly do upgrades on cap anyway
  return 0;
}

#line 99 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_mapdb.cpp"


inline Kobject_mapdb::Mapping *
Kobject_mapdb::insert(const Frame&, Mapping*, Space *,
                      Vaddr va, Obj_space::Phys_addr o, Obj_space::V_pfc size)
{
  (void)size;
  (void)o;
  assert (size == Obj_space::V_pfc(1));

  Mapping *m = va._c;
  Kobject_mappable *rn = o->map_root();
  //LOG_MSG_3VAL(current(), "ins", o->dbg_id(), (Mword)m, (Mword)va._a.value());
  rn->_root.add(m);

  Obj::Entry *e = static_cast<Obj::Entry*>(m);
  if (e->ref_cnt()) // counted
    ++rn->_cnt;

  return m;
}

#line 120 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_mapdb.cpp"


inline bool
Kobject_mapdb::grant(const Frame &f, Mapping *sm, Space *,
                     Vaddr va)
{
  Obj::Entry *re = va._c;
  Obj::Entry *se = static_cast<Obj::Entry*>(sm);
  //LOG_MSG_3VAL(current(), "gra", f.frame->dbg_id(), (Mword)sm, (Mword)va._a.value());

  // replace the source cap with the destination cap in the list
  Mapping::List::replace(se, re);

  if (se->ref_cnt() && !re->ref_cnt())
    --f.frame->_cnt;

  return true;
}

#line 138 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_mapdb.cpp"


inline void 
Kobject_mapdb::free(const Frame& f)
{
  f.frame->_lock.clear();
} // free()

#line 145 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_mapdb.cpp"


inline void
Kobject_mapdb::flush(const Frame& f, Mapping *m, L4_map_mask mask,
                     Obj_space::V_pfn, Obj_space::V_pfn)
{
  //LOG_MSG_3VAL(current(), "unm", f.frame->dbg_id(), (Mword)m, 0);
  if (!mask.self_unmap())
    return;

  bool flush = false;

  if (mask.do_delete() && m->delete_rights())
    flush = true;
  else
    {
      Obj::Entry *e = static_cast<Obj::Entry*>(m);
      if (e->ref_cnt()) // counted
	flush = --f.frame->_cnt <= 0;

      if (!flush)
	Mapping::List::remove(m);
    }

  if (flush)
    {
      for (Mapping::List::Iterator i = f.frame->_root.begin();
           i != Mapping::List::end(); ++i)
	{
	  Obj::Entry *e = static_cast<Obj::Entry*>(*i);
	  if (e->ref_cnt()) // counted
	    --f.frame->_cnt;
	  e->invalidate();
	}
      f.frame->_root.clear();
    }

} // flush()

#endif // kobject_mapdb_h
