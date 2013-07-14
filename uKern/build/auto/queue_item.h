// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef queue_item_h
#define queue_item_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/queue_item.cpp"

#include <cxx/dlist>

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/queue_item.cpp"

class Queue;
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/queue_item.cpp"

class Queue_item : public cxx::D_list_item
{
  friend class Queue;
public:
  enum Status { Ok, Retry, Invalid };

private:
  Queue *_q;

public:  
#line 25 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/queue_item.cpp"
  inline bool
  queued() const;
  
#line 30 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/queue_item.cpp"
  inline Queue *
  queue() const;
  
#line 38 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/queue_item.cpp"
  inline Queue_item::Status
  status() const;
} __attribute__((aligned(16)));

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/queue_item.cpp"

#include "kdb_ke.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/queue_item.cpp"


inline bool
Queue_item::queued() const
{ return cxx::D_list_cyclic<Queue_item>::in_list(this); }

#line 28 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/queue_item.cpp"


inline Queue *
Queue_item::queue() const
{
  assert_kdb (queued());
  return _q;
}

#line 36 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/queue_item.cpp"


inline Queue_item::Status
Queue_item::status() const
{
  assert_kdb (!queued());
  return Status((unsigned long)_q);
}

#endif // queue_item_h
