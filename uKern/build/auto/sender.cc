// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "sender.h"
#include "sender_i.h"


#line 103 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sender.cpp"



//PROTECTED inline NEEDS [<cassert>, "cpu_lock.h", "lock_guard.h",
//                      Sender::replace_node, Sender::tree_insert]
void Sender::sender_enqueue(Prio_list *head, unsigned short prio)
{
  assert(prio < 256);

  auto guard = lock_guard(cpu_lock);
  head->insert(this, prio);
}
