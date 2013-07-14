// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef obj_space_types_h
#define obj_space_types_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_types.cpp"

#include <cxx/cxx_int>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_types.cpp"
#include <cxx/hlist>
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_types.cpp"

#include "config.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_types.cpp"
#include "types.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_types.cpp"
#include "l4_types.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_types.cpp"
#include "l4_msg_item.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_types.cpp"
#include "template_math.h"
#line 164 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_types.cpp"

#include "dbg_page_info.h"
#line 166 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_types.cpp"
#include "warn.h"

//
// INTERFACE definition follows 
//

#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_types.cpp"

class Kobject_iface;
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_types.cpp"
class Kobject_mapdb;
#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_types.cpp"
class Jdb_mapdb;
#line 167 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_types.cpp"

class Space;
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_types.cpp"

namespace Obj {

  struct Attr
  : cxx::int_type_base<unsigned char, Attr>,
    cxx::int_bit_ops<Attr>
  {
    Attr() = default;
    explicit Attr(unsigned char r)
    : cxx::int_type_base<unsigned char, Attr>(r) {}

    Attr(L4_fpage::Rights r, unsigned char extra)
    : cxx::int_type_base<unsigned char, Attr>(cxx::int_value<L4_fpage::Rights>(r) | extra)
    {}


    L4_fpage::Rights rights() const { return L4_fpage::Rights(_v & 0x0f); }
    unsigned char extra() const { return _v & 0xf0; }

    static Attr Full() { return Attr(0xff); }
  };

  class Capability
  {
  private:
    Mword _obj;

  public:
    Capability() {}
    explicit Capability(Mword v) : _obj(v) {}
    Kobject_iface *obj() const { return (Kobject_iface *)(_obj & ~3UL); }
    void set(Kobject_iface *obj, unsigned char rights)
    { _obj = Mword(obj) | rights; }
    bool valid() const { return _obj; }
    void invalidate() { _obj = 0; }
    unsigned char rights() const { return _obj & 3; }
    void add_rights(unsigned char r) { _obj |= r & 3; }
    void del_rights(L4_fpage::Rights r)
    { _obj &= ~(cxx::int_value<L4_fpage::Rights>(r) & 3); }

    bool operator == (Capability const &c) const { return _obj == c._obj; }
  };

  /**
   * Tn the case of a flat copy model for capabilities, we have some
   * extra mapping information directly colocated within the cap tables.
   */
  class Mapping : public cxx::H_list_item
  {
    friend class ::Kobject_mapdb;
    friend class ::Jdb_mapdb;

  public:
    typedef cxx::H_list<Mapping> List;

    enum Flag
    {
      Delete  = 0x08, //L4_fpage::CD
      Ref_cnt = 0x10,

      Initial_flags = Delete | Ref_cnt | L4_msg_item::C_ctl_rights
    };

  protected:
    Mword _flags : 8;
    Mword _pad   : 24;

  public:
    Mapping() : _flags(0) {}
    // fake this really badly
    Mapping *parent() { return this; }
    Mword delete_rights() const { return _flags & Delete; }
    Mword ref_cnt() const { return _flags & Ref_cnt; }

    void put_as_root() { _flags = Initial_flags; }
  };


  class Entry : public Capability, public Mapping
  {
  public:
    Entry() {}
    explicit Entry(Mword v) : Capability(v) {}

    Attr rights() const
    { return Attr(Capability::rights() | (_flags & ~3)); }

    void set(Kobject_iface *obj, Attr rights)
    {
      Capability::set(obj, cxx::int_value<Attr>(rights) & 3);
      _flags = cxx::int_value<Attr>(rights) & 0xf8;
    }
    void add_rights(Attr r)
    {
      Capability::add_rights(cxx::int_value<Attr>(r) & 3);
      _flags |= (cxx::int_value<Attr>(r) & 0xf8);
    }

    void del_rights(L4_fpage::Rights r)
    {
      Capability::del_rights(r);
      _flags &= ~(cxx::int_value<L4_fpage::Rights>(r) & 0xf8);
    }
  };

  struct Cap_addr
  : public cxx::int_type_order_base<unsigned long, Cap_addr, Order, Cap_diff>
  {
  private:
    typedef cxx::int_type_order_base<unsigned long, Cap_addr, Order, Cap_diff> Base;

  public:
    mutable Entry *_c;
    Cap_addr() {}
    Cap_addr(unsigned long a, Entry *c) : Base(a), _c(c) {}
    explicit Cap_addr(Cap_index idx)
    : Base(cxx::int_value<Cap_index>(idx)), _c(0)
    {}

    explicit Cap_addr(unsigned long v) : Base(v), _c(0) {}

    operator Cap_index () const { return Cap_index(_v); }

    void set_entry(Entry *e) const { _c = e; }
  };

  inline void set_entry(Cap_addr const &ca, Entry *e)
  { ca.set_entry(e); }

  enum Insert_result
  {
    Insert_ok = 0,		///< Mapping was added successfully.
    Insert_warn_exists,		///< Mapping already existed
    Insert_warn_attrib_upgrade,	///< Mapping already existed, attribs upgrade
    Insert_err_nomem,		///< Couldn't alloc new page table
    Insert_err_exists		///< A mapping already exists at the target addr
  };

  enum
  {
    Caps_per_page_max = Config::PAGE_SIZE / sizeof(Obj::Entry),
    Caps_per_page_ld2 = Tl_math::Ld<Caps_per_page_max>::Res,
    Caps_per_page     = 1 << Caps_per_page_ld2,
  };
  static_assert(Caps_per_page == Caps_per_page_max, "hm, not a power of two caps on a single memory page");
}
#line 161 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_types.cpp"

// ------------------------------------------------------------------------

#line 169 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/obj_space_types.cpp"

namespace Obj
{
  struct Cap_page_dbg_info
  {
    Address offset;
    Space *s;
  };

  inline void add_cap_page_dbg_info(void *p, Space *s, Address cap)
  {
    Dbg_page_info *info = new Dbg_page_info(Virt_addr((Address)p));

    if (EXPECT_FALSE(!info))
      {
        WARN("oom: could not allocate debug info fo page %p\n", p);
        return;
      }

    info->info<Cap_page_dbg_info>()->s = s;
    info->info<Cap_page_dbg_info>()->offset = (cap / Caps_per_page) * Caps_per_page;
    Dbg_page_info::table().insert(info);
  }

  inline void remove_cap_page_dbg_info(void *p)
  {
    Dbg_page_info *info = Dbg_page_info::table().remove(Virt_addr((Address)p));
    if (info)
      delete info;
    else
      WARN("could not find debug info for page %p\n", p);
  }
}

#endif // obj_space_types_h
