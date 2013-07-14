// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "rcupdate.h"
#include "rcupdate_i.h"

#line 171 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/rcupdate.cpp"


// --------------------------------------------------------------------------

#line 186 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/rcupdate.cpp"


//--------------------------------------------------------------------------

#line 217 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/rcupdate.cpp"


Rcu_glbl Rcu::_rcu INIT_PRIORITY(EARLY_INIT_PRIO);
#line 220 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/rcupdate.cpp"
DEFINE_PER_CPU Per_cpu<Rcu_data> Rcu::_rcu_data(true);
#line 221 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/rcupdate.cpp"
DEFINE_PER_CPU static Per_cpu<Rcu_timeout> _rcu_timeout;

#line 252 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/rcupdate.cpp"


inline bool
Rcu_data::do_batch()
{
  int count = 0;
  bool need_resched = false;
  for (Rcu_list::Const_iterator l = _d.begin(); l != _d.end();)
    {
      Rcu_item *i = *l;
      ++l;

      need_resched |= i->_call_back(i);
      ++count;
    }

  // XXX: I do not know why this and the former stuff is w/o cpu lock
  //      but the couting needs it ?
  _d.clear();

  // XXX: we use clear, we seemingly worked through the whole list
  //_d.head(l);

    {
      auto guard = lock_guard(cpu_lock);
      _len -= count;
    }
#if 0
  if (_d.full())
    {
      Timeout *t = &_rcu_timeout.cpu(_cpu);
      t->set(t->get_timeout(0) + Rcu::Period, _cpu);
    }
#endif
  return need_resched;
}

#line 288 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/rcupdate.cpp"


inline void
Rcu_glbl::start_batch()
{
  if (_next_pending && _completed == _current)
    {
      _next_pending = 0;
      Mem::mp_wmb();
      ++_current;
      Mem::mp_mb();
      _cpus = _active_cpus;
    }
}

#line 345 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/rcupdate.cpp"



inline void
Rcu_glbl::cpu_quiet(Cpu_number cpu)
{
  _cpus.clear(cpu);
  if (_cpus.empty())
    {
      _completed = _current;
      start_batch();
    }
}

#line 177 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/rcupdate.cpp"


unsigned
Rcu::Log_rcu::print(int max, char *buf) const
{
  char const *events[] = { "call", "process"};
  return snprintf(buf, max, "rcu-%s (cpu=%u) item=%p", events[event],
                  cxx::int_value<Cpu_number>(cpu), item);
}

#line 208 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/rcupdate.cpp"

/**
 * Timeout expiration callback function
 * @return true if reschedule is necessary, false otherwise
 */

bool
Rcu_timeout::expired()
{ return Rcu::process_callbacks(); }

#line 222 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/rcupdate.cpp"


Rcu_glbl::Rcu_glbl()
: _current(-300),
  _completed(-300)
{}

#line 228 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/rcupdate.cpp"


Rcu_data::Rcu_data(Cpu_number cpu)
: _idle(true),
  _cpu(cpu)
{}

#line 302 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/rcupdate.cpp"


void
Rcu_data::enter_idle(Rcu_glbl *rgp)
{
  if (EXPECT_TRUE(!_idle))
    {
      _idle = true;

      auto guard = lock_guard(rgp->_lock);
      rgp->_active_cpus.clear(_cpu);

      if (_q_batch != rgp->_current || _pending)
        {
          _q_batch = rgp->_current;
          _pending = 0;
          rgp->cpu_quiet(_cpu);
          assert (!pending(rgp));
        }
    }
}

#line 358 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/rcupdate.cpp"


void
Rcu_data::check_quiescent_state(Rcu_glbl *rgp)
{
  if (_q_batch != rgp->_current)
    {
      // start new grace period
      _pending = 1;
      _q_passed = 0;
      _q_batch = rgp->_current;
      return;
    }

  // Is the grace period already completed for this cpu?
  // use _pending, not bitmap to avoid cache trashing
  if (!_pending)
    return;

  // Was there a quiescent state since the beginning of the grace period?
  if (!_q_passed)
    return;

  _pending = 0;

  auto guard = lock_guard(rgp->_lock);

  if (EXPECT_TRUE(_q_batch == rgp->_current))
    rgp->cpu_quiet(_cpu);
}

#line 388 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/rcupdate.cpp"


//inline NEEDS["cpu_lock.h", "globals.h", "lock_guard.h", "logdefs.h"]
void
Rcu::call(Rcu_item *i, bool (*cb)(Rcu_item *))
{
  i->_call_back = cb;
  LOG_TRACE("Rcu call", "rcu", ::current(), Log_rcu,
      l->cpu   = current_cpu();
      l->event = Rcu_call;
      l->item = i;
      l->cb = (void*)cb);

  auto guard = lock_guard(cpu_lock);

  Rcu_data *rdp = &_rcu_data.current();
  rdp->enqueue(i);
}

#line 406 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/rcupdate.cpp"


void
Rcu_data::move_batch(Rcu_list &l)
{
  auto guard = lock_guard(cpu_lock);
  _n.append(l);
}

#line 414 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/rcupdate.cpp"



Rcu_data::~Rcu_data()
{
  if (current_cpu() == _cpu)
    return;

  Rcu_data *current_rdp = &Rcu::_rcu_data.current();
  Rcu_glbl *rgp = Rcu::rcu();

    {
      auto guard = lock_guard(rgp->_lock);
      if (rgp->_current != rgp->_completed)
	rgp->cpu_quiet(_cpu);
    }

  current_rdp->move_batch(_c);
  current_rdp->move_batch(_n);
  current_rdp->move_batch(_d);
}

#line 435 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/rcupdate.cpp"


bool FIASCO_WARN_RESULT
Rcu_data::process_callbacks(Rcu_glbl *rgp)
{
  LOG_TRACE("Rcu callbacks", "rcu", ::current(), Rcu::Log_rcu,
      l->cpu = _cpu;
      l->item = 0;
      l->event = Rcu::Rcu_process);

  if (!_c.empty() && rgp->_completed >= _batch)
    _d.append(_c);

  if (!_n.empty() && _c.empty())
    {
	{
	  auto guard = lock_guard(cpu_lock);
	  _c = cxx::move(_n);
	}

      // start the next batch of callbacks

      _batch = rgp->_current + 1;
      Mem::mp_rmb();

      if (!rgp->_next_pending)
	{
	  // start the batch and schedule start if it's a new batch
	  auto guard = lock_guard(rgp->_lock);
	  rgp->_next_pending = 1;
	  rgp->start_batch();
	}
    }

  check_quiescent_state(rgp);
  if (!_d.empty())
    return do_batch();

  return false;
}

#line 531 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/rcupdate.cpp"


void
Rcu::schedule_callbacks(Cpu_number cpu, Unsigned64 clock)
{
  Timeout *t = &_rcu_timeout.cpu(cpu);
  if (!t->is_set())
    t->set(clock, cpu);
}
