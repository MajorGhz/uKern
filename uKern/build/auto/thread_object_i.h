// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef thread_object_i_h
#define thread_object_i_h
#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"

#include "context.h"
#line 25 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
#include "fpu.h"
#line 26 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
#include "irq_chip.h"
#line 27 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
#include "map_util.h"
#line 29 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
#include "task.h"
#line 30 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"
#include "thread_state.h"

//
// IMPLEMENTATION of inline functions follows
//


#line 166 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"



inline L4_msg_tag
Thread_object::sys_vcpu_resume(L4_msg_tag const &tag, Utcb *utcb)
{
  if (this != current() || !(state() & Thread_vcpu_enabled))
    return commit_result(-L4_err::EInval);

  Space *s = space();
  Vcpu_state *vcpu = vcpu_state().access(true);

  L4_obj_ref user_task = vcpu->user_task;
  if (user_task.valid() && user_task.op() == 0)
    {
      L4_fpage::Rights task_rights = L4_fpage::Rights(0);
      Task *task = Kobject::dcast<Task*>(s->lookup_local(user_task.cap(),
                                                         &task_rights));

      if (EXPECT_FALSE(task && !(task_rights & L4_fpage::Rights::W())))
        return commit_result(-L4_err::EPerm);

      if (task != vcpu_user_space())
        vcpu_set_user_space(task);

      reinterpret_cast<Mword &>(vcpu->user_task) |= L4_obj_ref::Ipc_send;
    }
  else if (user_task.op() == L4_obj_ref::Ipc_reply)
    vcpu_set_user_space(0);

  L4_snd_item_iter snd_items(utcb, tag.words());
  int items = tag.items();
  if (vcpu_user_space())
    for (; items && snd_items.more(); --items)
      {
        if (EXPECT_FALSE(!snd_items.next()))
          break;

        Lock_guard<Lock> guard;
        if (!guard.check_and_lock(&static_cast<Task *>(vcpu_user_space())->existence_lock))
          return commit_result(-L4_err::ENoent);

        cpu_lock.clear();

        L4_snd_item_iter::Item const *const item = snd_items.get();
        L4_fpage sfp(item->d);

        Reap_list rl;
        L4_error err = fpage_map(space(), sfp,
                                 vcpu_user_space(), L4_fpage::all_spaces(),
                                 item->b, &rl);
        rl.del();

        cpu_lock.lock();

        if (EXPECT_FALSE(!err.ok()))
          return commit_error(utcb, err);
      }

  if ((vcpu->_saved_state & Vcpu_state::F_irqs)
      && (vcpu->sticky_flags & Vcpu_state::Sf_irq_pending))
    {
      assert_kdb(cpu_lock.test());
      do_ipc(L4_msg_tag(), 0, 0, true, 0,
	     L4_timeout_pair(L4_timeout::Zero, L4_timeout::Zero),
	     &vcpu->_ipc_regs, L4_fpage::Rights::FULL());

      vcpu = vcpu_state().access(true);

      if (EXPECT_TRUE(!vcpu->_ipc_regs.tag().has_error()
	              || this->utcb().access(true)->error.error() == L4_error::R_timeout))
	{
	  vcpu->_ts.set_ipc_upcall();

	  Address sp;

	  // tried to resume to user mode, so an IRQ enters from user mode
	  if (vcpu->_saved_state & Vcpu_state::F_user_mode)
            sp = vcpu->_entry_sp;
	  else
            sp = vcpu->_ts.sp();

          arch_load_vcpu_kern_state(vcpu, true);

	  LOG_TRACE("VCPU events", "vcpu", this, Vcpu_log,
	      l->type = 4;
	      l->state = vcpu->state;
	      l->ip = vcpu->_entry_ip;
	      l->sp = sp;
	      l->space = static_cast<Task*>(_space.vcpu_aware())->dbg_id();
	      );

	  fast_return_to_user(vcpu->_entry_ip, sp, vcpu_state().usr().get());
	}
    }

  vcpu->state = vcpu->_saved_state;
  Task *target_space = nonull_static_cast<Task*>(space());
  bool user_mode = false;

  if (vcpu->state & Vcpu_state::F_user_mode)
    {
      if (!vcpu_user_space())
        return commit_result(-L4_err::ENoent);

      user_mode = true;

      if (!(vcpu->state & Vcpu_state::F_fpu_enabled))
	{
	  state_add_dirty(Thread_vcpu_fpu_disabled);
	  Fpu::disable();
	}
      else
        state_del_dirty(Thread_vcpu_fpu_disabled);

      target_space = static_cast<Task*>(vcpu_user_space());

      arch_load_vcpu_user_state(vcpu, true);
    }

  LOG_TRACE("VCPU events", "vcpu", this, Vcpu_log,
      l->type = 0;
      l->state = vcpu->state;
      l->ip = vcpu->_ts.ip();
      l->sp = vcpu->_ts.sp();
      l->space = target_space->dbg_id();
      );

  return commit_result(target_space->resume_vcpu(this, vcpu, user_mode));
}

#endif // thread_object_i_h
