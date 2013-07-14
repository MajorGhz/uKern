// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kobject_iface_h
#define kobject_iface_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_iface.cpp"

#include "l4_types.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_iface.cpp"

class Kobject;
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_iface.cpp"
class Kobject_dbg;
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_iface.cpp"
class Kobject_mappable;
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_iface.cpp"

class Space;
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_iface.cpp"
class Syscall_frame;
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_iface.cpp"
class Utcb;
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_iface.cpp"

class Kobject_common
{
public:
  virtual char const *kobj_type() const = 0;
  virtual Address kobject_start_addr() const = 0;

  virtual bool is_local(Space *) const  = 0;
  virtual Mword obj_id() const  = 0;
  virtual void initiate_deletion(Kobject ***) = 0;

  virtual Kobject_mappable *map_root() = 0;
  virtual ~Kobject_common() = 0;

public:  
#line 63 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_iface.cpp"
  virtual Kobject_dbg *dbg_info() const = 0;
};
#line 26 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_iface.cpp"

class Kobject_iface : public Kobject_common
{
public:
  virtual void invoke(L4_obj_ref self, L4_fpage::Rights rights, Syscall_frame *, Utcb *) = 0;

public:  
#line 38 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_iface.cpp"
  static inline L4_msg_tag
  commit_result(Mword error,
                               unsigned words = 0, unsigned items = 0);
  
#line 46 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_iface.cpp"
  static inline L4_msg_tag
  commit_error(Utcb const *utcb, L4_error const &e,
                              L4_msg_tag const &tag = L4_msg_tag(0, 0, 0, 0));
  
#line 55 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_iface.cpp"
  virtual Kobject_iface *
  downgrade(unsigned long del_attribs);
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_iface.cpp"

inline Kobject_common::~Kobject_common() {}

#line 36 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_iface.cpp"


inline L4_msg_tag
Kobject_iface::commit_result(Mword error,
                             unsigned words, unsigned items)
{
  return L4_msg_tag(words, items, 0, error);
}

#line 44 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_iface.cpp"


inline L4_msg_tag
Kobject_iface::commit_error(Utcb const *utcb, L4_error const &e,
                            L4_msg_tag const &tag)
{
  const_cast<Utcb*>(utcb)->error = e;
  return L4_msg_tag(tag, L4_msg_tag::Error);
}

#endif // kobject_iface_h
