// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "sched_context.h"
#include "sched_context_i.h"

#line 64 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context.cpp"

DEFINE_PER_CPU Per_cpu<Sched_context::Ready_queue> Sched_context::rq;

#line 66 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context.cpp"

/**
 * Set currently active global Sched_context.
 */

void
Sched_context::Ready_queue::set_current_sched(Sched_context *sched)
{
  assert_kdb (sched);
  // Save remainder of previous timeslice or refresh it, unless it had
  // been invalidated
  Timeout * const tt = timeslice_timeout.current();
  Unsigned64 clock = Timer::system_clock();
  if (Sched_context *s = current_sched())
    {
      Signed64 left = tt->get_timeout(clock);
      if (left > 0)
	s->set_left(left);
      else
	s->replenish();

      LOG_SCHED_SAVE(s);
    }

  // Program new end-of-timeslice timeout
  tt->reset();
  tt->set(clock + sched->left(), current_cpu());

  // Make this timeslice current
  activate(sched);

  LOG_SCHED_LOAD(sched);
}

#line 172 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context.cpp"

// sched
unsigned
Tb_entry_sched::print(int maxlen, char *buf) const
{
  Mword t = Kobject_dbg::pointer_to_id(owner);

  return snprintf(buf, maxlen,
              "(ts %s) owner:%lx id:%2x, prio:%2x, left:%6ld/%-6lu",
              mode == 0 ? "save" :
              mode == 1 ? "load" :
              mode == 2 ? "invl" : "????",
              t,
              id, prio, left, quantum);
}
