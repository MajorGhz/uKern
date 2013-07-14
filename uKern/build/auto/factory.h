// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef factory_h
#define factory_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"

#include "fiasco_defs.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"
#include "ram_quota.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"
#include "slab_cache.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"
#include "kobject_helper.h"
#line 300 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"

#include "tb_entry.h"

//
// INTERFACE definition follows 
//

#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"

class Factory : public Ram_quota, public Kobject_h<Factory>
{
  FIASCO_DECLARE_KOBJ();

private:
  typedef Slab_cache Self_alloc;

#line 302 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"
private:

private:
  struct Log_entry : public Tb_entry
  {
    Smword op;
    Cap_index buffer;
    Mword id;
    Mword ram;
    Mword newo;
    unsigned print(int max, char *buf) const;
  };

public:  
#line 35 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"
  inline Factory();
  
#line 53 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"
  static inline Factory * FIASCO_PURE
  root();
  
#line 75 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"
  void operator delete(void *_f);
  
#line 179 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"
  L4_msg_tag
  kinvoke(L4_obj_ref ref, L4_fpage::Rights rights, Syscall_frame *f,
                   Utcb const *utcb, Utcb *);

private:  
#line 40 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"
  inline Factory(Ram_quota *q, unsigned long max);
  
#line 48 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"
  static Factory::Self_alloc *
  allocator();
  
#line 59 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"
  Factory *
  create_factory(unsigned long max);
  
#line 91 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"
  L4_msg_tag
  map_obj(Kobject_iface *o, Cap_index cap, Space *c_space,
                   Obj_space *o_space);
  
#line 110 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"
  inline Kobject_iface *
  new_factory(Utcb const *u, int *);
  
#line 119 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"
  inline Kobject_iface *
  new_task(Utcb const *u, int *);
  
#line 133 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"
  inline Kobject_iface *
  new_thread(Utcb const *, int *);
  
#line 138 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"
  inline Kobject_iface *
  new_gate(L4_msg_tag const &tag, Utcb const *utcb, Obj_space *o_space,
                    int *err);
  
#line 169 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"
  inline Kobject_iface *
  new_irq(unsigned w, Utcb const *utcb, int *);
  
#line 291 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"
  inline Kobject_iface *
  new_vm(Utcb const *, int *err);
};
#line 297 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"

// ------------------------------------------------------------------------

#line 319 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 33 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"


inline Factory::Factory()
  : Ram_quota()
{}

#line 51 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/factory.cpp"


inline Factory * FIASCO_PURE
Factory::root()
{ return nonull_static_cast<Factory*>(Ram_quota::root); }

#endif // factory_h
