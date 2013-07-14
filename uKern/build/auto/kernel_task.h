// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kernel_task_h
#define kernel_task_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_task.cpp"

#include "task.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_task.cpp"
#include "types.h"

//
// INTERFACE definition follows 
//

#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_task.cpp"

class Kernel_thread;
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_task.cpp"

class Kernel_task : public Task
{
  friend class Kernel_thread;
  friend class Static_object<Kernel_task>;
private:
  static Static_object<Kernel_task> _t;

public:  
#line 32 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_task.cpp"
  static Task*
  kernel_task();
  
#line 37 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_task.cpp"
  static inline void
  init();

private:  
#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_task.cpp"
  inline Kernel_task();
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_task.cpp"
#include "globals.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 21 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_task.cpp"


inline Kernel_task::Kernel_task()
: Task(Ram_quota::root, Kmem::kdir, Caps::none())
{}

#line 35 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_task.cpp"


inline void
Kernel_task::init()
{ _t.construct(); }

#endif // kernel_task_h
