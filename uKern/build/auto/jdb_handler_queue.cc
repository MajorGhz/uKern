// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_handler_queue.h"
#include "jdb_handler_queue_i.h"


#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_handler_queue.cpp"


void
Jdb_handler_queue::execute() const
{
  Jdb_handler *h = first;
  while(h)
    {
      h->execute();
      h = h->next;
    }
}
