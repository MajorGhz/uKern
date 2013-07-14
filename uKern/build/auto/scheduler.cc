// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "scheduler.h"
#include "scheduler_i.h"

#line 24 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"

// ----------------------------------------------------------------------------

#line 32 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"

FIASCO_DEFINE_KOBJ(Scheduler);
#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"

Scheduler Scheduler::scheduler;

#line 36 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"

void
Scheduler::operator delete(void *)
{
  printf("WARNING: tried to delete kernel scheduler object.\n"
         "         The system is now useless\n");
}

#line 49 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"



L4_msg_tag
Scheduler::sys_run(L4_fpage::Rights, Syscall_frame *f, Utcb const *utcb)
{
  L4_msg_tag const tag = f->tag();
  Cpu_number const curr_cpu = current_cpu();

  Obj_space *s = current()->space();
  assert(s);

  L4_snd_item_iter snd_items(utcb, tag.words());

  if (EXPECT_FALSE(tag.words() < 5))
    return commit_result(-L4_err::EInval);

  unsigned long sz = sizeof (L4_sched_param_legacy);

    {
      L4_sched_param const *sched_param = reinterpret_cast<L4_sched_param const*>(&utcb->values[1]);
      if (sched_param->sched_class < 0)
        sz = sched_param->length;

      sz += sizeof(Mword) - 1;
      sz /= sizeof(Mword);

      if (sz + 1 > tag.words())
	return commit_result(-L4_err::EInval);
    }

  if (EXPECT_FALSE(!tag.items() || !snd_items.next()))
    return commit_result(-L4_err::EInval);

  L4_fpage _thread(snd_items.get()->d);
  if (EXPECT_FALSE(!_thread.is_objpage()))
    return commit_result(-L4_err::EInval);

  Thread *thread = Kobject::dcast<Thread_object*>(s->lookup_local(_thread.obj_index()));
  if (!thread)
    return commit_result(-L4_err::EInval);


  Mword _store[sz];
  memcpy(_store, &utcb->values[1], sz * sizeof(Mword));

  L4_sched_param const *sched_param = reinterpret_cast<L4_sched_param const *>(_store);

  Thread::Migration info;

  Cpu_number const t_cpu = thread->cpu();

  if (Cpu::online(t_cpu) && sched_param->cpus.contains(t_cpu))
    info.cpu = t_cpu;
  else if (sched_param->cpus.contains(curr_cpu))
    info.cpu = curr_cpu;
  else
    info.cpu = sched_param->cpus.first(Cpu::online_mask(), Config::max_num_cpus());

  info.sp = sched_param;
  if (0)
    printf("CPU[%u]: run(thread=%lx, cpu=%u (%lx,%u,%u)\n",
           cxx::int_value<Cpu_number>(curr_cpu), thread->dbg_id(),
           cxx::int_value<Cpu_number>(info.cpu),
           utcb->values[2],
           cxx::int_value<Cpu_number>(sched_param->cpus.offset()),
           cxx::int_value<Order>(sched_param->cpus.granularity()));

  thread->migrate(&info);

  return commit_result(0);
}

#line 121 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"


L4_msg_tag
Scheduler::sys_idle_time(L4_fpage::Rights,
                         Syscall_frame *f, Utcb *utcb)
{
  if (f->tag().words() < 3)
    return commit_result(-L4_err::EInval);

  L4_cpu_set cpus = access_once(reinterpret_cast<L4_cpu_set const *>(&utcb->values[1]));
  Cpu_number const cpu = cpus.first(Cpu::online_mask(), Config::max_num_cpus());
  if (EXPECT_FALSE(cpu == Config::max_num_cpus()))
    return commit_result(-L4_err::EInval);

  reinterpret_cast<Utcb::Time_val *>(utcb->values)->t
    = Context::kernel_context(cpu)->consumed_time();

  return commit_result(0, Utcb::Time_val::Words);
}

#line 140 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"


L4_msg_tag
Scheduler::sys_info(L4_fpage::Rights, Syscall_frame *f,
                    Utcb const *iutcb, Utcb *outcb)
{
  if (f->tag().words() < 2)
    return commit_result(-L4_err::EInval);

  L4_cpu_set_descr const s = access_once(reinterpret_cast<L4_cpu_set_descr const*>(&iutcb->values[1]));
  Mword rm = 0;
  Cpu_number max = Config::max_num_cpus();
  Cpu_number const offset = s.offset() << s.granularity();
  if (offset >= max)
    return commit_result(-L4_err::EInval);

  if (max > offset + Cpu_number(MWORD_BITS) << s.granularity())
    max = offset + Cpu_number(MWORD_BITS) << s.granularity();

  for (Cpu_number i = Cpu_number::first(); i < max - offset; ++i)
    if (Cpu::online(i + offset))
      rm |= (1 << cxx::int_value<Cpu_number>(i >> s.granularity()));

  outcb->values[0] = rm;
  outcb->values[1] = Config::Max_num_cpus;
  return commit_result(0, 2);
}

#line 186 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"


L4_msg_tag
Scheduler::icu_bind_irq(Irq *irq_o, unsigned irqnum)
{
  if (irqnum > 0)
    return commit_result(-L4_err::EInval);

  if (_irq)
    _irq->unbind();

  Irq_chip_soft::bind(irq_o, irqnum);
  _irq = irq_o;
  return commit_result(0);
}

#line 201 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"


L4_msg_tag
Scheduler::icu_set_mode(Mword pin, Irq_chip::Mode)
{
  if (pin != 0)
    return commit_result(-L4_err::EInval);

  if (_irq)
    _irq->switch_mode(true);
  return commit_result(0);
}

#line 221 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/scheduler.cpp"


L4_msg_tag
Scheduler::kinvoke(L4_obj_ref ref, L4_fpage::Rights rights, Syscall_frame *f,
                   Utcb const *iutcb, Utcb *outcb)
{
  switch (f->tag().proto())
    {
    case L4_msg_tag::Label_irq:
      return Icu::icu_invoke(ref, rights, f, iutcb,outcb);
    case L4_msg_tag::Label_scheduler:
      break;
    default:
      return commit_result(-L4_err::EBadproto);
    }

  switch (iutcb->values[0])
    {
    case Info:       return sys_info(rights, f, iutcb, outcb);
    case Run_thread: return sys_run(rights, f, iutcb);
    case Idle_time:  return sys_idle_time(rights, f, outcb);
    default:         return commit_result(-L4_err::ENosys);
    }
}
