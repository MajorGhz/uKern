// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef receiver_i_h
#define receiver_i_h
#line 56 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/receiver.cpp"

#include "l4_types.h"
#line 59 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/receiver.cpp"

#include "cpu_lock.h"
#line 61 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/receiver.cpp"
#include "globals.h"
#line 62 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/receiver.cpp"
#include "lock_guard.h"
#line 63 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/receiver.cpp"
#include "logdefs.h"
#line 65 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/receiver.cpp"
#include "thread_lock.h"
#line 66 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/receiver.cpp"
#include "entry_frame.h"
#line 289 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/receiver.cpp"


// --------------------------------------------------------------------------

struct Ipc_remote_dequeue_request
{
  Receiver *partner;
  Sender *sender;
  Receiver::Abort_state state;
};

#endif // receiver_i_h
