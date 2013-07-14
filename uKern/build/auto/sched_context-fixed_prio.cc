// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "sched_context.h"
#include "sched_context_i.h"


#line 73 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context-fixed_prio.cpp"


/**
 * Constructor
 */

Sched_context::Sched_context()
: _prio(Config::Default_prio),
  _quantum(Config::Default_time_slice),
  _left(Config::Default_time_slice)
{}

#line 95 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context-fixed_prio.cpp"


int
Sched_context::set(L4_sched_param const *_p)
{
  Sp const *p = reinterpret_cast<Sp const *>(_p);
  if (p->p.sched_class >= 0)
    {
      // legacy fixed prio
      _prio = p->legacy_fixed_prio.prio;
      if (p->legacy_fixed_prio.prio > 255)
        _prio = 255;

      _quantum = p->legacy_fixed_prio.quantum;
      if (p->legacy_fixed_prio.quantum == 0)
        _quantum = Config::Default_time_slice;
      return 0;
    }

  switch (p->p.sched_class)
    {
    case L4_sched_param_fixed_prio::Class:
      _prio = p->fixed_prio.prio;
      if (p->fixed_prio.prio > 255)
        _prio = 255;

      _quantum = p->fixed_prio.quantum;
      if (p->fixed_prio.quantum == 0)
        _quantum = Config::Default_time_slice;
      break;

    default:
      return L4_err::ERange;
    };
  return 0;
}
