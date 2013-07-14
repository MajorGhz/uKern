// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef ipc_gate_h
#define ipc_gate_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"

#include "kobject.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"
#include "kobject_helper.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"
#include "ref_ptr.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"
#include "slab_cache.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"
#include "thread_object.h"
#line 54 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"

#include "tb_entry.h"

//
// INTERFACE definition follows 
//

#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"

class Ram_quota;
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"

class Ipc_gate_obj;
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"

class Ipc_gate_ctl : public Kobject_h<Ipc_gate_ctl, Kobject_iface>
{
private:
  enum Operation
  {
    Op_bind     = 0x10,
    Op_get_info = 0x11,
  };

public:  
#line 247 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  void
  invoke(L4_obj_ref self, L4_fpage::Rights rights, Syscall_frame *f, Utcb *utcb);
  
#line 258 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  L4_msg_tag
  kinvoke(L4_obj_ref self, L4_fpage::Rights rights,
                        Syscall_frame *f, Utcb const *in, Utcb *out);

private:  
#line 199 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  inline L4_msg_tag
  bind_thread(L4_obj_ref, L4_fpage::Rights,
                            Syscall_frame *f, Utcb const *in, Utcb *);
  
#line 237 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  inline L4_msg_tag
  get_infos(L4_obj_ref, L4_fpage::Rights,
                          Syscall_frame *, Utcb const *, Utcb *out);
};
#line 22 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"

class Ipc_gate : public Kobject
{
  friend class Ipc_gate_ctl;
  friend class Jdb_sender_list;
protected:

  Ref_ptr<Thread> _thread;
  Mword _id;
  Ram_quota *_quota;
  Locked_prio_list _wait_q;

#line 56 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"
private:

protected:
  struct Log_ipc_gate_invoke : public Tb_entry
  {
    Mword gate_dbg_id;
    Mword thread_dbg_id;
    Mword label;
    unsigned print(int max, char *buf) const;
  };


public:  
#line 104 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  inline Ipc_gate(Ram_quota *q, Thread *t, Mword id);
  
#line 171 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  static Ipc_gate_obj *
  create(Ram_quota *q, Thread *t, Mword id);
  
#line 326 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  void
  invoke(L4_obj_ref /*self*/, L4_fpage::Rights rights, Syscall_frame *f, Utcb *utcb);

private:  
#line 282 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  inline L4_error
  block(Thread *ct, L4_timeout const &to, Utcb *u);
};
#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"

class Ipc_gate_obj : public Ipc_gate, public Ipc_gate_ctl
{
  FIASCO_DECLARE_KOBJ();

private:
  friend class Ipc_gate;
  typedef Slab_cache Self_alloc;

public:
  bool put() { return Ipc_gate::put(); }

  Thread *thread() const { return _thread.ptr(); }
  Mword id() const { return _id; }
  Mword obj_id() const { return _id; }
  bool is_local(Space *s) const { return _thread && _thread->space() == s; }

public:  
#line 89 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  ::Kobject_mappable *
  map_root();
  
#line 94 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  Kobject_iface *
  downgrade(unsigned long attr);
  
#line 109 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  inline Ipc_gate_obj(Ram_quota *q, Thread *t, Mword id);
  
#line 114 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  void
  unblock_all();
  
#line 134 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  virtual void
  initiate_deletion(Kobject ***r);
  
#line 144 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  virtual void
  destroy(Kobject ***r);
  
#line 153 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  ~Ipc_gate_obj();
  
#line 159 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  inline void *
  operator new(size_t, void *b) throw();
  
#line 188 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  void operator delete(void *_f);
  
#line 375 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  ::Kobject_dbg *
  dbg_info() const;

private:  
#line 166 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  static Ipc_gate_obj::Self_alloc *
  allocator();
};
#line 51 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"

//---------------------------------------------------------------------------

#line 378 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 72 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"

#include <cstddef>
#line 74 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"

#include "assert_opt.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 102 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"


inline Ipc_gate::Ipc_gate(Ram_quota *q, Thread *t, Mword id)
  : _thread(t), _id(id), _quota(q), _wait_q()
{}

#line 107 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"


inline Ipc_gate_obj::Ipc_gate_obj(Ram_quota *q, Thread *t, Mword id)
  : Ipc_gate(q, t, id)
{}

#line 157 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"


inline void *
Ipc_gate_obj::operator new(size_t, void *b) throw()
{ return b; }

#endif // ipc_gate_h
