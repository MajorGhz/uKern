// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef thread_object_h
#define thread_object_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"

#include "kobject.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
#include "thread.h"

//
// INTERFACE definition follows 
//

#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"

class Thread_object : public Thread
{
private:
  struct Remote_syscall
  {
    Thread *thread;
    L4_msg_tag result;
  };

public:  
#line 72 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
  Thread_object();
  
#line 75 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
  Thread_object(Context_mode_kernel k);
  
#line 78 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
  virtual bool
  put();
  
#line 85 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
  void
  operator delete(void *_t);
  
#line 101 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
  void
  destroy(Kobject ***rl);
  
#line 110 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
  void
  invoke(L4_obj_ref /*self*/, L4_fpage::Rights rights, Syscall_frame *f, Utcb *utcb);
  
#line 513 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
  // -------------------------------------------------------------------
  // Thread::ex_regs class system calls
  
  
  bool
  ex_regs(Address ip, Address sp,
                  Address *o_ip = 0, Address *o_sp = 0, Mword *o_flags = 0,
                  Mword ops = 0);
  
#line 568 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
  inline L4_msg_tag
  ex_regs(Utcb *utcb);

private:  
#line 169 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
  inline L4_msg_tag
  sys_vcpu_resume(L4_msg_tag const &tag, Utcb *utcb);
  
#line 298 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
  inline L4_msg_tag
  sys_modify_senders(L4_msg_tag tag, Utcb const *in, Utcb * /*out*/);
  
#line 341 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
  inline L4_msg_tag
  sys_register_delete_irq(L4_msg_tag tag, Utcb const *in, Utcb * /*out*/);
  
#line 371 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
  inline L4_msg_tag
  sys_control(L4_fpage::Rights rights, L4_msg_tag const &tag, Utcb *utcb);
  
#line 459 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
  inline L4_msg_tag
  sys_vcpu_control(L4_fpage::Rights, L4_msg_tag const &tag,
                                  Utcb *utcb);
  
#line 591 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
  static unsigned
  handle_remote_ex_regs(Drq *, Context *self, void *p);
  
#line 600 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
  inline L4_msg_tag
  sys_ex_regs(L4_msg_tag const &tag, Utcb *utcb);
  
#line 617 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
  inline L4_msg_tag
  sys_thread_switch(L4_msg_tag const &/*tag*/, Utcb *utcb);
  
#line 655 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
  // -------------------------------------------------------------------
  // Gather statistics information about thread execution
  
  
  unsigned
  sys_thread_stats_remote(void *data);
  
#line 668 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
  static unsigned
  handle_sys_thread_stats_remote(Drq *, Context *self, void *data);
  
#line 675 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
  inline L4_msg_tag
  sys_thread_stats(L4_msg_tag const &/*tag*/, Utcb *utcb);
};
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"

class Obj_cap : public L4_obj_ref
{

public:  
#line 36 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
  inline Obj_cap(L4_obj_ref const &o);
  
#line 39 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
  inline Kobject_iface *
  deref(L4_fpage::Rights *rights = 0, bool dbg = false);
  
#line 65 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
  inline bool
  revalidate(Kobject_iface *o);
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 28 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
#include "processor.h"
#line 31 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
#include "timer.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 566 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"


inline L4_msg_tag
Thread_object::ex_regs(Utcb *utcb)
{
  Address ip = utcb->values[1];
  Address sp = utcb->values[2];
  Mword flags;
  Mword ops = utcb->values[0];

  LOG_TRACE("Ex-regs", "exr", current(), Log_thread_exregs,
      l->id = dbg_id();
      l->ip = ip; l->sp = sp; l->op = ops;);

  if (!ex_regs(ip, sp, &ip, &sp, &flags, ops))
    return commit_result(-L4_err::EInval);

  utcb->values[0] = flags;
  utcb->values[1] = ip;
  utcb->values[2] = sp;

  return commit_result(0, 3);
}

#line 32 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"




inline Obj_cap::Obj_cap(L4_obj_ref const &o) : L4_obj_ref(o) {}

#line 37 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"


inline Kobject_iface *
Obj_cap::deref(L4_fpage::Rights *rights, bool dbg)
{
  Thread *current = current_thread();
  if (op() & L4_obj_ref::Ipc_reply)
    {
      if (rights) *rights = current->caller_rights();
      Thread *ca = static_cast<Thread*>(current->caller());
      if (!dbg)
	current->set_caller(0, L4_fpage::Rights(0));
      return ca;
    }

  if (EXPECT_FALSE(special()))
    {
      if (!self())
	return 0;

      if (rights) *rights = L4_fpage::Rights::RWX();
      return current_thread();
    }

  return current->space()->lookup_local(cap(), rights);
}

#line 63 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"


inline bool
Obj_cap::revalidate(Kobject_iface *o)
{
  return deref() == o;
}

#endif // thread_object_h
