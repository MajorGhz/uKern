// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "ipc_timeout.h"
#include "ipc_timeout_i.h"


#line 47 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_timeout.cpp"

/**
 * Timeout expiration callback function
 * @return true if reschedule is necessary, false otherwise
 */

bool
IPC_timeout::expired()
{
  Receiver * const _owner = owner();

  Mword ipc_state = _owner->state() & Thread_ipc_mask;
  if (!ipc_state || (ipc_state & Thread_receive_in_progress))
    return false;

  _owner->state_change_dirty(~Thread_ipc_mask, Thread_ready | Thread_timeout);

  // Flag reschedule if owner's priority is higher than the current
  // thread's (own or timeslice-donated) priority.
  return Sched_context::rq.current().deblock(_owner->sched(), current()->sched(), false);
}
