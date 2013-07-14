// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "thread_object.h"
#include "thread_object_i.h"

#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"


// ---------------------------------------------------------------------------


#line 296 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"


inline L4_msg_tag
Thread_object::sys_modify_senders(L4_msg_tag tag, Utcb const *in, Utcb * /*out*/)
{
  if (sender_list()->cursor())
    return Kobject_iface::commit_result(-L4_err::EBusy);

  if (0)
    printf("MODIFY ID (%08lx:%08lx->%08lx:%08lx\n",
           in->values[1], in->values[2],
           in->values[3], in->values[4]);


  int elems = tag.words();

  if (elems < 5)
    return Kobject_iface::commit_result(0);

  --elems;

  elems = elems / 4;

  ::Prio_list_elem *c = sender_list()->first();
  while (c)
    {
      // this is kind of arbitrary
      for (int cnt = 50; c && cnt > 0; --cnt)
	{
	  Sender *s = Sender::cast(c);
	  s->modify_label(&in->values[1], elems);
	  c = sender_list()->next(c);
	}

      if (!c)
	return Kobject_iface::commit_result(0);

      sender_list()->cursor(c);
      Proc::preemption_point();
      c = sender_list()->cursor();
    }
  return Kobject_iface::commit_result(0);
}

#line 339 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"


inline L4_msg_tag
Thread_object::sys_register_delete_irq(L4_msg_tag tag, Utcb const *in, Utcb * /*out*/)
{
  L4_snd_item_iter snd_items(in, tag.words());

  if (!tag.items() || !snd_items.next())
    return Kobject_iface::commit_result(-L4_err::EInval);

  L4_fpage bind_irq(snd_items.get()->d);
  if (EXPECT_FALSE(!bind_irq.is_objpage()))
    return Kobject_iface::commit_error(in, L4_error::Overflow);

  register Context *const c_thread = ::current();
  register Space *const c_space = c_thread->space();
  L4_fpage::Rights irq_rights = L4_fpage::Rights(0);
  Irq_base *irq
    = Irq_base::dcast(c_space->lookup_local(bind_irq.obj_index(), &irq_rights));

  if (!irq)
    return Kobject_iface::commit_result(-L4_err::EInval);

  if (EXPECT_FALSE(!(irq_rights & L4_fpage::Rights::X())))
    return Kobject_iface::commit_result(-L4_err::EPerm);

  register_delete_irq(irq);
  return Kobject_iface::commit_result(0);
}

#line 368 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"



inline L4_msg_tag
Thread_object::sys_control(L4_fpage::Rights rights, L4_msg_tag const &tag, Utcb *utcb)
{
  if (EXPECT_FALSE(!(rights & L4_fpage::Rights::W())))
    return commit_result(-L4_err::EPerm);

  if (EXPECT_FALSE(tag.words() < 6))
    return commit_result(-L4_err::EInval);

  Context *curr = current();
  Space *s = curr->space();
  L4_snd_item_iter snd_items(utcb, tag.words());
  Task *task = 0;
  User<Utcb>::Ptr utcb_addr(0);

  Mword flags = utcb->values[0];

  Mword _old_pager = cxx::int_value<Cap_index>(_pager.raw()) << L4_obj_ref::Cap_shift;
  Mword _old_exc_handler = cxx::int_value<Cap_index>(_exc_handler.raw()) << L4_obj_ref::Cap_shift;

  Thread_ptr _new_pager(Thread_ptr::Invalid);
  Thread_ptr _new_exc_handler(Thread_ptr::Invalid);

  if (flags & Ctl_set_pager)
    _new_pager = Thread_ptr(Cap_index(utcb->values[1] >> L4_obj_ref::Cap_shift));

  if (flags & Ctl_set_exc_handler)
    _new_exc_handler = Thread_ptr(Cap_index(utcb->values[2] >> L4_obj_ref::Cap_shift));

  if (flags & Ctl_bind_task)
    {
      if (EXPECT_FALSE(!tag.items() || !snd_items.next()))
	return commit_result(-L4_err::EInval);

      L4_fpage bind_task(snd_items.get()->d);

      if (EXPECT_FALSE(!bind_task.is_objpage()))
	return commit_result(-L4_err::EInval);

      L4_fpage::Rights task_rights = L4_fpage::Rights(0);
      task = Kobject::dcast<Task*>(s->lookup_local(bind_task.obj_index(), &task_rights));

      if (EXPECT_FALSE(!(task_rights & L4_fpage::Rights::W())))
	return commit_result(-L4_err::EPerm);

      if (!task)
	return commit_result(-L4_err::EInval);

      utcb_addr = User<Utcb>::Ptr((Utcb*)utcb->values[5]);

      if (EXPECT_FALSE(!bind(task, utcb_addr)))
        return commit_result(-L4_err::EInval); // unbind first !!
    }

  Mword del_state = 0;
  Mword add_state = 0;

  long res = control(_new_pager, _new_exc_handler);

  if (res < 0)
    return commit_result(res);

  if ((res = sys_control_arch(utcb)) < 0)
    return commit_result(res);

  // FIXME: must be done xcpu safe, may be some parts above too
  if (flags & Ctl_alien_thread)
    {
      if (utcb->values[4] & Ctl_alien_thread)
	{
	  add_state |= Thread_alien;
	  del_state |= Thread_dis_alien;
	}
      else
	del_state |= Thread_alien;
    }

  if (del_state || add_state)
    drq_state_change(~del_state, add_state);

  utcb->values[1] = _old_pager;
  utcb->values[2] = _old_exc_handler;

  return commit_result(0, 3);
}

#line 456 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"



inline L4_msg_tag
Thread_object::sys_vcpu_control(L4_fpage::Rights, L4_msg_tag const &tag,
                                Utcb *utcb)
{
  if (!space())
    return commit_result(-L4_err::EInval);

  User<Vcpu_state>::Ptr vcpu(0);

  if (tag.words() >= 2)
    vcpu = User<Vcpu_state>::Ptr((Vcpu_state*)utcb->values[1]);

  Mword del_state = 0;
  Mword add_state = 0;

  if (vcpu)
    {
      Mword size = sizeof(Vcpu_state);
      if (utcb->values[0] & 0x10000)
        {
          size = Config::PAGE_SIZE;
          add_state |= Thread_ext_vcpu_enabled;
        }

      Space::Ku_mem const *vcpu_m
        = space()->find_ku_mem(vcpu, size);

      if (!vcpu_m)
        return commit_result(-L4_err::EInval);

      add_state |= Thread_vcpu_enabled;
      _vcpu_state.set(vcpu, vcpu_m->kern_addr(vcpu));

      Vcpu_state *s = _vcpu_state.access();
      arch_init_vcpu_state(s, add_state & Thread_ext_vcpu_enabled);
      arch_update_vcpu_state(s);
    }
  else
    return commit_result(-L4_err::EInval);

  /* hm, we do not allow to disable vCPU mode, it's one way enable
  else
    {
      del_state |= Thread_vcpu_enabled | Thread_vcpu_user_mode
                   | Thread_vcpu_fpu_disabled | Thread_ext_vcpu_enabled;
    }
  */

  drq_state_change(~del_state, add_state);

  return commit_result(0);
}

#line 598 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"


inline L4_msg_tag
Thread_object::sys_ex_regs(L4_msg_tag const &tag, Utcb *utcb)
{
  if (tag.words() != 3)
    return commit_result(-L4_err::EInval);

  if (current() == this)
    return ex_regs(utcb);

  Remote_syscall params;
  params.thread = current_thread();

  drq(handle_remote_ex_regs, &params, 0, Drq::Any_ctxt);
  return params.result;
}

#line 615 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"


inline L4_msg_tag
Thread_object::sys_thread_switch(L4_msg_tag const &/*tag*/, Utcb *utcb)
{
  Context *curr = current();

  if (curr == this)
    return commit_result(0);

  if (current_cpu() != cpu())
    return commit_result(0);

#ifdef FIXME
  Sched_context * const cs = current_sched();
#endif

  if (curr != this && (state() & Thread_ready_mask))
    {
      curr->switch_exec_schedule_locked (this, Not_Helping);
      reinterpret_cast<Utcb::Time_val*>(utcb->values)->t = 0; // Assume timeslice was used up
      return commit_result(0, Utcb::Time_val::Words);
    }

#if 0 // FIXME: provide API for multiple sched contexts
      // Compute remaining quantum length of timeslice
      regs->left(timeslice_timeout.cpu(cpu())->get_timeout(Timer::system_clock()));

      // Yield current global timeslice
      cs->owner()->switch_sched(cs->id() ? cs->next() : cs);
#endif
  reinterpret_cast<Utcb::Time_val*>(utcb->values)->t
    = timeslice_timeout.current()->get_timeout(Timer::system_clock());
  curr->schedule();

  return commit_result(0, Utcb::Time_val::Words);
}

#line 673 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"


inline L4_msg_tag
Thread_object::sys_thread_stats(L4_msg_tag const &/*tag*/, Utcb *utcb)
{
  Clock::Time value;

  if (cpu() != current_cpu())
    drq(handle_sys_thread_stats_remote, &value, 0, Drq::Any_ctxt);
  else
    {
      // Respect the fact that the consumed time is only updated on context switch
      if (this == current())
        update_consumed_time();
      value = consumed_time();
    }

  reinterpret_cast<Utcb::Time_val *>(utcb->values)->t = value;

  return commit_result(0, Utcb::Time_val::Words);
}

#line 70 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"


Thread_object::Thread_object() : Thread() {}

#line 73 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"


Thread_object::Thread_object(Context_mode_kernel k) : Thread(k) {}

#line 76 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"


bool
Thread_object::put()
{ return dec_ref() == 0; }

#line 81 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"




void
Thread_object::operator delete(void *_t)
{
  Thread_object * const t = nonull_static_cast<Thread_object*>(_t);
  Ram_quota * const q = t->_quota;
  Kmem_alloc::allocator()->q_unaligned_free(q, Thread::Size, t);

  LOG_TRACE("Kobject delete", "del", current(), Log_destroy,
      l->id = t->dbg_id();
      l->obj = t;
      l->type = "Thread";
      l->ram = q->current());
}

#line 98 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"



void
Thread_object::destroy(Kobject ***rl)
{
  Kobject::destroy(rl);
  check_kdb(kill());
  assert_kdb(_magic == magic);
}

#line 108 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"


void
Thread_object::invoke(L4_obj_ref /*self*/, L4_fpage::Rights rights, Syscall_frame *f, Utcb *utcb)
{
  register L4_obj_ref::Operation op = f->ref().op();
  if (((op != 0) && !(op & L4_obj_ref::Ipc_send))
      || (op & L4_obj_ref::Ipc_reply)
      || f->tag().proto() != L4_msg_tag::Label_thread)
    {
      /* we do IPC */
      Thread *ct = current_thread();
      Thread *sender = 0;
      Thread *partner = 0;
      bool have_rcv = false;

      if (EXPECT_FALSE(!check_sys_ipc(op, &partner, &sender, &have_rcv)))
	{
	  utcb->error = L4_error::Not_existent;
	  return;
	}

      ct->do_ipc(f->tag(), partner, partner, have_rcv, sender,
                 f->timeout(), f, rights);
      return;
    }

  switch (utcb->values[0] & Opcode_mask)
    {
    case Op_control:
      f->tag(sys_control(rights, f->tag(), utcb));
      return;
    case Op_ex_regs:
      f->tag(sys_ex_regs(f->tag(), utcb));
      return;
    case Op_switch:
      f->tag(sys_thread_switch(f->tag(), utcb));
      return;
    case Op_stats:
      f->tag(sys_thread_stats(f->tag(), utcb));
      return;
    case Op_vcpu_resume:
      f->tag(sys_vcpu_resume(f->tag(), utcb));
      return;
    case Op_register_del_irq:
      f->tag(sys_register_delete_irq(f->tag(), utcb, utcb));
      return;
    case Op_modify_senders:
      f->tag(sys_modify_senders(f->tag(), utcb, utcb));
      return;
    case Op_vcpu_control:
      f->tag(sys_vcpu_control(rights, f->tag(), utcb));
      return;
    default:
      f->tag(invoke_arch(f->tag(), utcb));
      return;
    }
}

#line 511 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"


// -------------------------------------------------------------------
// Thread::ex_regs class system calls


bool
Thread_object::ex_regs(Address ip, Address sp,
                Address *o_ip, Address *o_sp, Mword *o_flags,
                Mword ops)
{
  if (state(false) == Thread_invalid || !space())
    return false;

  if (current() == this)
    spill_user_state();

  if (o_sp) *o_sp = user_sp();
  if (o_ip) *o_ip = user_ip();
  if (o_flags) *o_flags = user_flags();

  // Changing the run state is only possible when the thread is not in
  // an exception.
  if (!(ops & Exr_cancel) && (state() & Thread_in_exception))
    // XXX Maybe we should return false here.  Previously, we actually
    // did so, but we also actually didn't do any state modification.
    // If you change this value, make sure the logic in
    // sys_thread_ex_regs still works (in particular,
    // ex_regs_cap_handler and friends should still be called).
    return true;

  if (state() & Thread_dead)	// resurrect thread
    state_change_dirty(~Thread_dead, Thread_ready);

  else if (ops & Exr_cancel)
    // cancel ongoing IPC or other activity
    state_add_dirty(Thread_cancel | Thread_ready);

  if (ops & Exr_trigger_exception)
    {
      extern char leave_by_trigger_exception[];
      do_trigger_exception(regs(), leave_by_trigger_exception);
    }

  if (ip != ~0UL)
    user_ip(ip);

  if (sp != ~0UL)
    user_sp (sp);

  if (current() == this)
    fill_user_state();

  return true;
}

#line 589 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"


unsigned
Thread_object::handle_remote_ex_regs(Drq *, Context *self, void *p)
{
  Remote_syscall *params = reinterpret_cast<Remote_syscall*>(p);
  params->result = nonull_static_cast<Thread_object*>(self)->ex_regs(params->thread->utcb().access());
  return params->result.proto() == 0 ? Drq::Need_resched : 0;
}

#line 652 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"



// -------------------------------------------------------------------
// Gather statistics information about thread execution


unsigned
Thread_object::sys_thread_stats_remote(void *data)
{
  update_consumed_time();
  *(Clock::Time *)data = consumed_time();
  return 0;
}

#line 666 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread_object.cpp"


unsigned
Thread_object::handle_sys_thread_stats_remote(Drq *, Context *self, void *data)
{
  return nonull_static_cast<Thread_object*>(self)->sys_thread_stats_remote(data);
}
