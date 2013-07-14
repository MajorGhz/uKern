// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "ipc_sender.h"
#include "ipc_sender_i.h"


#line 37 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_sender.cpp"


void
Ipc_sender_base::ipc_receiver_aborted()
{
  assert (wait_queue());
  set_wait_queue(0);
}
