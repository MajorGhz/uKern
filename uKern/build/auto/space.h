// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef space_h
#define space_h
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"

#include "config.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"
#include "io_space.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"
#include "l4_types.h"
#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"

#include "mem_space.h"
#line 21 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"
#include "member_offs.h"
#line 22 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"
#include "obj_space.h"
#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"
#include "spin_lock.h"
#line 24 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"
#include "ref_obj.h"
#line 25 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"
#include "slab_cache.h"
#line 26 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"
#include <cxx/slist>
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/space-ia32.cpp"

#include "spin_lock.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space-io.cpp"

#include "config.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space-io.cpp"
#include "io_space.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space-io.cpp"
#include "l4_types.h"

//
// INTERFACE definition follows 
//

#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"

class Space;
#line 27 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"

class Ram_quota;
#line 29 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"
class Context;
#line 30 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"
class Kobject;
#line 31 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"

class Space;
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"

/** Global definition of Io_space for map_util stuff. */
typedef Generic_io_space<Space> Io_space;
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"

//--------------------------------------------------------------------------

#line 33 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"

typedef Generic_obj_space<Space> Obj_space;
#line 35 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"

class Space
: public Ref_cnt_obj,
  public Mem_space,
  public Generic_obj_space<Space>

, public Generic_io_space<Space>
{
  MEMBER_OFFSET();
  friend class Jdb_space;

public:

  struct Caps
  : cxx::int_type_base<unsigned char, Caps>,
    cxx::int_bit_ops<Caps>,
    cxx::int_null_chk<Caps>
  {
    Caps() = default;
    explicit Caps(unsigned char v)
    : cxx::int_type_base<unsigned char, Caps>(v) {}

    static Caps none() { return Caps(0); }
    static Caps mem() { return Caps(1); }
    static Caps obj() { return Caps(2); }
    static Caps io() { return Caps(4); }
    static Caps all() { return Caps(7); }
  };

  explicit Space(Ram_quota *q, Caps c) : Mem_space(q), _caps(c) {}
  virtual ~Space() = 0;

  enum State
  { // we must use values with the two lest significant bits == 0
    Starting    = 0x00,
    Ready       = 0x08,
    In_deletion = 0x10
  };

  struct Ku_mem : public cxx::S_list_item
  {
    User<void>::Ptr u_addr;
    void *k_addr;
    unsigned size;

    static Slab_cache *a;

    void *operator new (size_t, Ram_quota *q) throw()
    { return a->q_alloc(q); }

    void free(Ram_quota *q) throw()
    { a->q_free(q, this); }

    template<typename T>
    T *kern_addr(Smart_ptr<T, Simple_ptr_policy, User_ptr_discr> ua) const
    {
      typedef Address A;
      return (T*)((A)ua.get() - (A)u_addr.get() + (A)k_addr);
    }
  };

  Caps caps() const { return _caps; }


protected:
  Space(Ram_quota *q, Mem_space::Dir_type* pdir, Caps c)
  : Mem_space(q, pdir), _caps(c) {}

  const Caps _caps;

private:
  void switchin_ldt() const;

protected:
  typedef cxx::S_list<Ku_mem> Ku_mem_list;
  Ku_mem_list _ku_mem;

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/space-ia32.cpp"
private:

protected:
  class Ldt
  {
  public:
    Ldt() : _addr(0), _size(0) {}
    Address addr() const { return (Address)_addr; }
    Mword   size() const { return _size; }

    void size(Mword);
    void alloc();

    ~Ldt();

  private:
    void *_addr;
    Mword _size;
  };

  friend class Jdb_misc_debug;

  Ldt _ldt;

#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space-io.cpp"
private:

public:  
#line 122 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"
  //
  // class Space
  //
  
  inline Ram_quota * ram_quota() const;
  
#line 132 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"
  Space::Ku_mem const *
  find_ku_mem(User<void>::Ptr p, unsigned size);
  
#line 156 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"
  inline void
  switchin_context(Space *from);
  
#line 169 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"
  static inline bool
  is_user_memory(Address address, Mword len);
};
#line 36 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/space-ia32.cpp"

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 116 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"
#include "kdb_ke.h"
#line 32 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/space-ia32.cpp"

#include "cpu.h"
#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/space-ia32.cpp"
#include "globals.h"
#line 35 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/space-ia32.cpp"
#include "mem.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 121 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"

//
// class Space
//

inline Ram_quota * Space::ram_quota() const
{ return Mem_space::ram_quota(); }

#line 154 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"


inline void
Space::switchin_context(Space *from)
{
  assert_kdb (this);
  if (this != from)
    {
      Mem_space::switchin_context(from);
      switchin_ldt();
    }
}

#line 166 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"



inline bool
Space::is_user_memory(Address address, Mword len)
{
  return    address < Mem_layout::User_max
         && address < address + len // prevent overflow
         && address + len <= Mem_layout::User_max;
}

#line 128 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/space.cpp"

inline Space::~Space() {}

#line 59 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/space-ia32.cpp"



inline void
Space::switchin_ldt() const
{
  Cpu::cpus.cpu(current_cpu()).enable_ldt(_ldt.addr(), _ldt.size());
}

#line 36 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/space-ia32.cpp"


inline void
Space::Ldt::size(Mword size)
{ _size = size; }

#line 41 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/space-ia32.cpp"


inline void
Space::Ldt::alloc()
{
  // LDT maximum size is one page
  _addr = Kmem_alloc::allocator()->alloc(Config::PAGE_SHIFT);
  Mem::memset_mwords(reinterpret_cast<void *>(addr()), 0,
                     Config::PAGE_SIZE / sizeof(Mword));
}

#line 51 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/space-ia32.cpp"


inline Space::Ldt::~Ldt()
{
  if (addr())
    Kmem_alloc::allocator()->free(Config::PAGE_SHIFT,
                                  reinterpret_cast<void*>(addr()));
}

#endif // space_h
