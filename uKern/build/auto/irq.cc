// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "irq.h"
#include "irq_i.h"

#line 96 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"

//-----------------------------------------------------------------------------

#line 117 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"

FIASCO_DEFINE_KOBJ(Irq);
#line 119 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"

namespace {
static Irq_base *irq_base_dcast(Kobject_iface *o)
{ return Kobject::dcast<Irq*>(o); }

struct Irq_base_cast
{
  Irq_base_cast()
  { Irq_base::dcast = &irq_base_dcast; }
};

static Irq_base_cast register_irq_base_cast;
}
#line 651 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"



 // Irq implementation

static Kmem_slab _irq_allocator(max(sizeof (Irq_sender), sizeof(Irq_muxer)),
                                __alignof__ (Irq), "Irq");

#line 132 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"



void
Irq_muxer::unmask(Mword)
{
  Smword old;
  do
    old = _mask_cnt;
  while (!mp_cas(&_mask_cnt, old, old - 1));

  if (old == 1)
    Irq_base::unmask();
}

#line 146 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"



void
Irq_muxer::mask(Mword)
{
  Smword old;
  do
    old = _mask_cnt;
  while (!mp_cas(&_mask_cnt, old, old + 1));

  if (old == 0)
    Irq_base::mask();
}

#line 160 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"



void
Irq_muxer::unbind(Irq_base *irq)
{
  Irq_base *n;
  for (n = this; n->_next && n->_next != irq; n = n->_next)
    ;

  assert (n->_next == irq);
  n->_next = n->_next->_next;
  if (irq->masked())
    static_cast<Irq_chip&>(*this).unmask(0);

  Irq_chip::unbind(irq);
}

#line 177 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"



void
Irq_muxer::mask_and_ack(Mword)
{}

#line 217 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"


Irq_muxer::Irq_muxer(Ram_quota *q)
: Kobject_h<Irq_muxer, Irq>(q), _mask_cnt(0)
{
  hit_func = &handler_wrapper<Irq_muxer>;
}

#line 224 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"


void
Irq_muxer::destroy(Kobject ***rl)
{
  // FIXME: unchain IRQs

  Irq::destroy(rl);
}

#line 233 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"


L4_msg_tag
Irq_muxer::sys_attach(L4_msg_tag const &tag, Utcb const *utcb, Syscall_frame * /*f*/,
                Obj_space *o_space)
{
  L4_snd_item_iter snd_items(utcb, tag.words());

  Irq *irq = 0;

  if (tag.items() == 0)
    return commit_result(-L4_err::EInval);

  if (tag.items() && snd_items.next())
    {
      L4_fpage bind_irq(snd_items.get()->d);
      if (EXPECT_FALSE(!bind_irq.is_objpage()))
	return commit_error(utcb, L4_error::Overflow);

      irq = Kobject::dcast<Irq*>(o_space->lookup_local(bind_irq.obj_index()));
    }

  if (!irq)
    return commit_result(-L4_err::EInval);

  irq->unbind();

  if (!irq->masked())
    {
      Smword old;
      do
	old = _mask_cnt;
      while (!mp_cas(&_mask_cnt, old, old + 1));
    }

  bind(irq, 0);

  irq->Irq_base::_next = Irq_base::_next;
  Irq_base::_next = irq;

  return commit_result(0);
}

#line 275 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"


L4_msg_tag
Irq_muxer::kinvoke(L4_obj_ref, L4_fpage::Rights /*rights*/, Syscall_frame *f,
                   Utcb const *utcb, Utcb *)
{
  register Context *const c_thread = ::current();
  assert_opt (c_thread);
  register Space *const c_space = c_thread->space();
  assert_opt (c_space);

  L4_msg_tag tag = f->tag();

  if (EXPECT_FALSE(tag.proto() != L4_msg_tag::Label_irq))
    return commit_result(-L4_err::EBadproto);

  if (EXPECT_FALSE(tag.words() < 1))
    return commit_result(-L4_err::EInval);

  switch ((utcb->values[0] & 0xffff))
    {
    case Op_chain:
      return sys_attach(tag, utcb, f, c_space);
    case Op_trigger:
      log();
      hit(0);
      return no_reply();
    default:
      return commit_result(-L4_err::EInval);
    }
}

#line 332 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"


Receiver *
Irq_sender::owner() const { return _irq_thread; }

#line 336 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"

/** Release an device interrupt.
    @param t the receiver that ownes the IRQ
    @return true if t really was the owner of the IRQ and operation was 
            successful
 */

bool
Irq_sender::free(Receiver *t)
{
  bool ret = mp_cas(&_irq_thread, t, reinterpret_cast<Receiver*>(0));

  if (ret)
    {
      auto guard = lock_guard(cpu_lock);
      mask();

      if (EXPECT_TRUE(t != 0))
	{
	  t->abort_send(this);

	  // release cpu-lock early, actually before delete
	  guard.reset();

	  if (t->dec_ref() == 0)
	    delete t;
	}
    }

  return ret;
}

#line 367 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"


Irq_sender::Irq_sender(Ram_quota *q)
: Kobject_h<Irq_sender, Irq>(q), _queued(0), _irq_thread(0), _irq_id(~0UL)
{
  hit_func = &hit_level_irq;
}

#line 374 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"


void
Irq_sender::switch_mode(bool is_edge_triggered)
{
  hit_func = is_edge_triggered ? &hit_edge_irq : &hit_level_irq;
}

#line 381 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"


void
Irq_sender::destroy(Kobject ***rl)
{
  auto g = lock_guard(cpu_lock);
  if (_irq_thread)
    free(_irq_thread);

  Irq::destroy(rl);
}

#line 455 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"

void
Irq_sender::modify_label(Mword const *todo, int cnt)
{
  for (int i = 0; i < cnt*4; i += 4)
    {
      Mword const test_mask = todo[i];
      Mword const test      = todo[i+1];
      if ((_irq_id & test_mask) == test)
	{
	  Mword const set_mask = todo[i+2];
	  Mword const set      = todo[i+3];

	  _irq_id = (_irq_id & ~set_mask) | set;
	  return;
	}
    }
}

#line 473 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"



unsigned
Irq_sender::handle_remote_hit(Context::Drq *, Context *, void *arg)
{
  Irq_sender *irq = (Irq_sender*)arg;
  irq->set_cpu(current_cpu());
  irq->send_msg(irq->_irq_thread);
  return Context::Drq::No_answer;
}

#line 530 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"


void
Irq_sender::hit_level_irq(Irq_base *i, Upstream_irq const *ui)
{ nonull_static_cast<Irq_sender*>(i)->_hit_level_irq(ui); }

#line 563 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"


void
Irq_sender::hit_edge_irq(Irq_base *i, Upstream_irq const *ui)
{ nonull_static_cast<Irq_sender*>(i)->_hit_edge_irq(ui); }

#line 568 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"



L4_msg_tag
Irq_sender::sys_attach(L4_msg_tag const &tag, Utcb const *utcb, Syscall_frame * /*f*/,
                Obj_space *o_space)
{
  L4_snd_item_iter snd_items(utcb, tag.words());

  Receiver *thread = 0;
  unsigned mode = utcb->values[0] >> 16;

  if (tag.items() == 0)
    {
      // detach
      free(_irq_thread);
      _irq_id = ~0UL;
      return commit_result(0);
    }

  if (tag.items() && snd_items.next())
    {
      L4_fpage bind_thread(snd_items.get()->d);
      if (EXPECT_FALSE(!bind_thread.is_objpage()))
	return commit_error(utcb, L4_error::Overflow);

      thread = Kobject::dcast<Thread_object*>(o_space->lookup_local(bind_thread.obj_index()));
    }

  if (!thread)
    thread = current_thread();

  if (alloc(thread))
    {
      _irq_id = utcb->values[1];
      return commit_result(0);
    }

  return commit_result(-L4_err::EInval);
}

#line 608 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"



L4_msg_tag
Irq_sender::kinvoke(L4_obj_ref, L4_fpage::Rights /*rights*/, Syscall_frame *f,
                    Utcb const *utcb, Utcb *)
{
  register Context *const c_thread = ::current();
  assert_opt (c_thread);
  register Space *const c_space = c_thread->space();
  assert_opt (c_space);

  L4_msg_tag tag = f->tag();

  if (EXPECT_FALSE(tag.proto() != L4_msg_tag::Label_irq))
    return commit_result(-L4_err::EBadproto);

  if (EXPECT_FALSE(tag.words() < 1))
    return commit_result(-L4_err::EInval);

  switch ((utcb->values[0] & 0xffff))
    {
    case Op_eoi_1:
    case Op_eoi_2:
      if (_queued < 1)
	unmask();

      return no_reply();
    case Op_attach: /* ATTACH, DETACH */
      return sys_attach(tag, utcb, f, c_space);
    case Op_trigger:
      log();
      hit(0);
      return no_reply();
    default:
      return commit_result(-L4_err::EInval);
    }
}

#line 646 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"


Mword
Irq_sender::obj_id() const
{ return _irq_id; }

#line 658 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"


Irq::Allocator *
Irq::allocator()
{ return &_irq_allocator; }

#line 668 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"


void
Irq::operator delete(void *_l)
{
  Irq *l = reinterpret_cast<Irq*>(_l);
  if (l->_q)
    l->_q->free(sizeof(Irq));

  allocator()->free(l);
}

#line 695 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq.cpp"


void
Irq::destroy(Kobject ***rl)
{
  Irq_base::destroy();
  Kobject::destroy(rl);
}
