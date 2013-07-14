// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "receiver.h"
#include "receiver_i.h"


#line 299 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/receiver.cpp"


unsigned
Receiver::handle_remote_abort_send(Drq *, Context *, void *_rq)
{
  Ipc_remote_dequeue_request *rq = (Ipc_remote_dequeue_request*)_rq;
  if (rq->sender->in_sender_list())
    {
      // really cancled IPC
      rq->state = Abt_ipc_cancel;
      rq->sender->sender_dequeue(rq->partner->sender_list());
      rq->partner->vcpu_update_state();
    }
  else if (rq->partner->in_ipc(rq->sender))
    rq->state = Abt_ipc_in_progress;
  return 0;
}

#line 316 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/receiver.cpp"


Receiver::Abort_state
Receiver::abort_send(Sender *sender)
{
  Ipc_remote_dequeue_request rq;
  rq.partner = this;
  rq.sender = sender;
  rq.state = Abt_ipc_done;
  if (current_cpu() != cpu())
    drq(handle_remote_abort_send, &rq);
  else
    handle_remote_abort_send(0, 0, &rq);
  return rq.state;
}
