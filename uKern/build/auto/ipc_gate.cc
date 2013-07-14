// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "ipc_gate.h"
#include "ipc_gate_i.h"

#line 69 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"

//---------------------------------------------------------------------------

#line 85 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"

FIASCO_DEFINE_KOBJ(Ipc_gate_obj);
#line 162 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"

static Kmem_slab_t<Ipc_gate_obj> _ipc_gate_allocator("Ipc_gate");
#line 370 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"

//---------------------------------------------------------------------------


#line 197 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"


inline L4_msg_tag
Ipc_gate_ctl::bind_thread(L4_obj_ref, L4_fpage::Rights,
                          Syscall_frame *f, Utcb const *in, Utcb *)
{
  L4_msg_tag tag = f->tag();
  L4_snd_item_iter snd_items(in, tag.words());

  if (tag.words() < 2 || !tag.items() || !snd_items.next())
    return commit_result(-L4_err::EInval);

  L4_fpage bind_thread(snd_items.get()->d);
  if (EXPECT_FALSE(!bind_thread.is_objpage()))
    return commit_error(in, L4_error::Overflow);

  register Context *const c_thread = ::current();
  assert_opt(c_thread);
  register Space *const c_space = c_thread->space();
  assert_opt (c_space);
  L4_fpage::Rights t_rights(0);
  Thread *t = Kobject::dcast<Thread_object*>(c_space->lookup_local(bind_thread.obj_index(), &t_rights));

  if (!(t_rights & L4_fpage::Rights::CS()))
    return commit_result(-L4_err::EPerm);


  Ipc_gate_obj *g = static_cast<Ipc_gate_obj*>(this);
  g->_id = in->values[1];
  Mem::mp_wmb();
  g->_thread = t;
  Mem::mp_wmb();
  g->unblock_all();
  c_thread->rcu_wait();
  g->unblock_all();

  return commit_result(0);
}

#line 235 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"


inline L4_msg_tag
Ipc_gate_ctl::get_infos(L4_obj_ref, L4_fpage::Rights,
                        Syscall_frame *, Utcb const *, Utcb *out)
{
  Ipc_gate_obj *g = static_cast<Ipc_gate_obj*>(this);
  out->values[0] = g->_id;
  return commit_result(0, 1);
}

#line 280 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"


inline L4_error
Ipc_gate::block(Thread *ct, L4_timeout const &to, Utcb *u)
{
  Unsigned64 t = 0;
  if (!to.is_never())
    {
      t = to.microsecs(Timer::system_clock(), u);
      if (!t)
	return L4_error::Timeout;
    }

    {
      auto g = lock_guard(_wait_q.lock());
      ct->set_wait_queue(&_wait_q);
      ct->sender_enqueue(&_wait_q, ct->sched_context()->prio());
    }
  ct->state_change_dirty(~Thread_ready, Thread_send_wait);

  IPC_timeout timeout;
  if (t)
    {
      timeout.set(t, ct->cpu(true));
      ct->set_timeout(&timeout);
    }

  ct->schedule();

  ct->state_change(~Thread_ipc_mask, Thread_ready);
  ct->reset_timeout();

  if (EXPECT_FALSE(ct->in_sender_list() && timeout.has_hit()))
    {
      auto g = lock_guard(_wait_q.lock());
      if (!ct->in_sender_list())
	return L4_error::None;

      ct->sender_dequeue(&_wait_q);
      return L4_error::Timeout;
    }
  return L4_error::None;
}

#line 87 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"


::Kobject_mappable *
Ipc_gate_obj::map_root()
{ return Ipc_gate::map_root(); }

#line 92 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"


Kobject_iface *
Ipc_gate_obj::downgrade(unsigned long attr)
{
  if (attr & L4_msg_item::C_obj_right_1)
    return static_cast<Ipc_gate*>(this);
  else
    return static_cast<Ipc_gate_ctl*>(this);
}

#line 112 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"


void
Ipc_gate_obj::unblock_all()
{
  while (::Prio_list_elem *h = _wait_q.first())
    {
      auto g1 = lock_guard(cpu_lock);
      Thread *w;
	{
	  auto g2 = lock_guard(_wait_q.lock());
	  if (EXPECT_FALSE(h != _wait_q.first()))
	    continue;

	  w = static_cast<Thread*>(Sender::cast(h));
	  w->sender_dequeue(&_wait_q);
	}
      w->activate();
    }
}

#line 132 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"


void
Ipc_gate_obj::initiate_deletion(Kobject ***r)
{
  if (_thread)
    _thread->ipc_gate_deleted(_id);

  Kobject::initiate_deletion(r);
}

#line 142 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"


void
Ipc_gate_obj::destroy(Kobject ***r)
{
  Kobject::destroy(r);
  _thread = 0;
  unblock_all();
}

#line 151 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"


Ipc_gate_obj::~Ipc_gate_obj()
{
  unblock_all();
}

#line 164 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"


Ipc_gate_obj::Self_alloc *
Ipc_gate_obj::allocator()
{ return &_ipc_gate_allocator; }

#line 169 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"


Ipc_gate_obj *
Ipc_gate::create(Ram_quota *q, Thread *t, Mword id)
{
  Auto_quota<Ram_quota> quota(q, sizeof(Ipc_gate_obj));

  if (EXPECT_FALSE(!quota))
    return 0;

  void *nq = Ipc_gate_obj::allocator()->alloc();
  if (EXPECT_FALSE(!nq))
    return 0;

  quota.release();
  return new (nq) Ipc_gate_obj(q, t, id);
}

#line 186 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"


void Ipc_gate_obj::operator delete(void *_f)
{
  register Ipc_gate_obj *f = (Ipc_gate_obj*)_f;
  Ram_quota *p = f->_quota;

  allocator()->free(f);
  if (p)
    p->free(sizeof(Ipc_gate_obj));
}

#line 245 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"


void
Ipc_gate_ctl::invoke(L4_obj_ref self, L4_fpage::Rights rights, Syscall_frame *f, Utcb *utcb)
{
  if (f->tag().proto() == L4_msg_tag::Label_kobject)
    Kobject_h<Ipc_gate_ctl, Kobject_iface>::invoke(self, rights, f, utcb);
  else
    static_cast<Ipc_gate_obj*>(this)->Ipc_gate::invoke(self, rights, f, utcb);
}

#line 255 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"



L4_msg_tag
Ipc_gate_ctl::kinvoke(L4_obj_ref self, L4_fpage::Rights rights,
                      Syscall_frame *f, Utcb const *in, Utcb *out)
{
  L4_msg_tag tag = f->tag();

  if (EXPECT_FALSE(tag.proto() != L4_msg_tag::Label_kobject))
    return commit_result(-L4_err::EBadproto);

  if (EXPECT_FALSE(tag.words() < 1))
    return commit_result(-L4_err::EInval);

  switch (in->values[0])
    {
    case Op_bind:
      return bind_thread(self, rights, f, in, out);
    case Op_get_info:
      return get_infos(self, rights, f, in, out);
    default:
      return static_cast<Ipc_gate_obj*>(this)->kobject_invoke(self, rights, f, in, out);
    }
}

#line 323 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"



void
Ipc_gate::invoke(L4_obj_ref /*self*/, L4_fpage::Rights rights, Syscall_frame *f, Utcb *utcb)
{
  Syscall_frame *ipc_f = f;
  //LOG_MSG_3VAL(current(), "gIPC", Mword(_thread), _id, f->obj_2_flags());
  //printf("Invoke: Ipc_gate(%lx->%p)...\n", _id, _thread);
  Thread *ct = current_thread();
  Thread *sender = 0;
  Thread *partner = 0;
  bool have_rcv = false;

  if (EXPECT_FALSE(!_thread.ptr()))
    {
      L4_error e = block(ct, f->timeout().snd, utcb);
      if (!e.ok())
	{
	  f->tag(commit_error(utcb, e));
	  return;
	}

      if (EXPECT_FALSE(!_thread.ptr()))
	{
	  f->tag(commit_error(utcb, L4_error::Not_existent));
	  return;
	}
    }

  bool ipc = _thread->check_sys_ipc(f->ref().op(), &partner, &sender, &have_rcv);

  LOG_TRACE("IPC Gate invoke", "gate", current(), Log_ipc_gate_invoke,
      l->gate_dbg_id = dbg_id();
      l->thread_dbg_id = _thread->dbg_id();
      l->label = _id | cxx::int_value<L4_fpage::Rights>(rights);
  );

  if (EXPECT_FALSE(!ipc))
    f->tag(commit_error(utcb, L4_error::Not_existent));
  else
    {
      ipc_f->from(_id | cxx::int_value<L4_fpage::Rights>(rights));
      ct->do_ipc(f->tag(), partner, partner, have_rcv, sender,
                 f->timeout(), f, rights);
    }
}

#line 373 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"


::Kobject_dbg *
Ipc_gate_obj::dbg_info() const
{ return Ipc_gate::dbg_info(); }

#line 378 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_gate.cpp"


unsigned
Ipc_gate::Log_ipc_gate_invoke::print(int max, char *buf) const
{
  return snprintf(buf, max, "D-gate=%lx D-thread=%lx L=%lx",
                  gate_dbg_id, thread_dbg_id, label);
}
