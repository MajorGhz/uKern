// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "syscalls.h"
#include "syscalls_i.h"

#line 31 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/syscalls.cpp"


//---------------------------------------------------------------------------

#line 38 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/syscalls.cpp"

extern "C" void sys_invoke_debug(Kobject_iface *o, Syscall_frame *f) __attribute__((weak));
#line 64 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/syscalls.cpp"


//---------------------------------------------------------------------------

#line 68 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/syscalls.cpp"

void (*syscall_table[])() =
{
  sys_ipc_wrapper,
  0,
  sys_invoke_debug_wrapper,
};

#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/syscalls.cpp"

extern "C"
void  __attribute__((flatten))
sys_ipc_wrapper()
{
  assert_kdb (!(current()->state() & Thread_drq_ready));

#ifndef NDEBUG
  if ((current()->state() & Thread_vcpu_enabled)
      && (current()->vcpu_state().access()->state & Vcpu_state::F_irqs))
    WARN("VCPU makes syscall with IRQs enabled: PC=%lx\n", current()->regs()->ip());
#endif

  Thread *curr = current_thread();
  Syscall_frame *f = curr->regs();

  Obj_cap obj = f->ref();
  Utcb *utcb = curr->utcb().access(true);
  L4_fpage::Rights rights;
  Kobject_iface *o = obj.deref(&rights);
  L4_msg_tag e;
  if (EXPECT_TRUE(o!=0))
    o->invoke(obj, rights, f, utcb);
  else
    f->tag(curr->commit_error(utcb, L4_error::Not_existent));
}

#line 40 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/syscalls.cpp"

extern "C" void  __attribute__((flatten)) sys_invoke_debug_wrapper()
{
  Thread *curr = current_thread();
  Syscall_frame *f = curr->regs();
  //printf("sys_invoke_debugger(f=%p, obj=%lx)\n", f, f->ref().raw());
  Kobject_iface *o = curr->space()->lookup_local(f->ref().cap());
  if (o && &::sys_invoke_debug)
    ::sys_invoke_debug(o, f);
  else
    f->tag(curr->commit_error(curr->utcb().access(true), L4_error::Not_existent));
}