// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kobject_h
#define kobject_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"

#include "lock.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"
#include "obj_space.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"
#include <cxx/hlist>
#line 40 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"

#include "context.h"
#line 42 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"
#include "kobject_dbg.h"
#line 43 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"
#include "kobject_iface.h"
#line 44 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"
#include "l4_error.h"
#line 45 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"
#include "rcupdate.h"
#line 46 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"
#include "space.h"
#line 202 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"

#include "tb_entry.h"

//
// INTERFACE definition follows 
//

#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"


class Kobject_mappable
{
private:
  friend class Kobject_mapdb;
  friend class Jdb_mapdb;

  Obj::Mapping::List _root;
  Smword _cnt;
  Lock _lock;

public:
  Kobject_mappable() : _cnt(0) {}
  bool no_mappings() const { return _root.empty(); }

  /**
   * Insert the root mapping of an object.
   */
  template<typename M>
  bool insert(void *, Space *, M &m)
  {
    m._c->put_as_root();
    _root.add(m._c);
    _cnt = 1;
    return true;
  }

  Smword cap_ref_cnt() const { return _cnt; }

public:  
#line 127 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"
  inline Smword
  dec_cap_refcnt(Smword diff);
};
#line 36 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"


//----------------------------------------------------------------------------

#line 47 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"

class Kobject :
  public Kobject_iface,
  private Kobject_mappable,
  private Kobject_dbg
{
  template<typename T>
  friend class Map_traits;

private:
  template<typename T>
  class Tconv {};

  template<typename T>
  class Tconv<T*> { public: typedef T Base; };

public:
  template<typename T>
  static T dcast(Kobject_common *_o)
  {
    if (EXPECT_FALSE(!_o))
      return 0;

    if (EXPECT_TRUE(_o->kobj_type() == Tconv<T>::Base::static_kobj_type))
      return reinterpret_cast<T>(_o->kobject_start_addr());
    return 0;
  }

  template<typename T>
  static T dcast(Kobject_common const *_o)
  {
    if (EXPECT_FALSE(!_o))
      return 0;

    if (EXPECT_TRUE(_o->kobj_type() == Tconv<T>::Base::static_kobj_type))
      return reinterpret_cast<T>(_o->kobject_start_addr());
    return 0;
  }

  using Kobject_dbg::dbg_id;

  Lock existence_lock;

public:
  Kobject *_next_to_reap;

public:
  enum Op {
    O_dec_refcnt = 0,
  };


#line 204 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"
private:

protected:
  struct Log_destroy : public Tb_entry
  {
    Kobject    *obj;
    Mword       id;
    char const *type;
    Mword       ram;
    unsigned print(int max, char *buf) const;
  };

public:  
#line 121 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"
  bool  is_local(Space *) const;
  
#line 122 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"
  Mword obj_id() const;
  
#line 123 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"
  virtual bool  put();
  
#line 124 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"
  Kobject_mappable *map_root();
  
#line 136 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"
  void
  initiate_deletion(Kobject ***reap_list);
  
#line 147 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"
  virtual void
  destroy(Kobject ***);
  
#line 158 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"
  virtual ~Kobject();
  
#line 180 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"
  L4_msg_tag
  kobject_invoke(L4_obj_ref, L4_fpage::Rights /*rights*/,
                          Syscall_frame *f,
                          Utcb const *in, Utcb *out);
  
#line 222 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"
  static inline Kobject *
  from_dbg(Kobject_dbg *d);
  
#line 227 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"
  static inline Kobject *
  from_dbg(Kobject_dbg::Iterator const &d);
  
#line 236 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"
  Kobject_dbg *
  dbg_info() const;

private:  
#line 168 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"
  inline L4_msg_tag
  sys_dec_refcnt(L4_msg_tag tag, Utcb const *in, Utcb *out);
};
#line 99 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"

#define FIASCO_DECLARE_KOBJ() \
  public: static char const *const static_kobj_type; \
          char const *kobj_type() const; \
          Address kobject_start_addr() const; \
          Mword kobject_size() const;
#line 105 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"

#define FIASCO_DEFINE_KOBJ(t) \
  char const *const t::static_kobj_type = #t; \
  char const *t::kobj_type() const { return static_kobj_type; } \
  Address t::kobject_start_addr() const { return (Address)this; } \
  Mword t::kobject_size() const { return sizeof(*this); }
#line 199 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"

//---------------------------------------------------------------------------

#line 239 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 118 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"
#include "lock_guard.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 125 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"


inline Smword
Kobject_mappable::dec_cap_refcnt(Smword diff)
{
  auto g = lock_guard(_lock);
  _cnt -= diff;
  return _cnt;
}

#line 220 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"


inline Kobject *
Kobject::from_dbg(Kobject_dbg *d)
{ return static_cast<Kobject*>(d); }

#line 225 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject.cpp"


inline Kobject *
Kobject::from_dbg(Kobject_dbg::Iterator const &d)
{
  if (d != Kobject_dbg::end())
    return static_cast<Kobject*>(*d);
  return 0;
}

#endif // kobject_h
