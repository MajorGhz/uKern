// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "mp_lock.h"
#include "mp_lock_i.h"

#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mp_lock.cpp"


//----------------------------------------------------------------------------


#line 154 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mp_lock.cpp"


void
Mp_lock::invalidate()
{
    {
      auto guard = lock_guard(_q.q_lock());
      _q.invalidate();
    }
      
  Queue_item *f;
  while (1)
    {
      auto guard = lock_guard(_q.q_lock());
      f = _q.first();

      //LOG_MSG_3VAL(current(), "deq", Mword(f), 0, 0);
      if (!f)
	break;

      _q.dequeue(f, Queue_item::Invalid);
      context_of(f)->activate();
    }
}
