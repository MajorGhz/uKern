// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "fpu_alloc.h"
#include "fpu_alloc_i.h"

#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/fpu_alloc.cpp"

static Kmem_slab _fpu_state_allocator(Fpu::state_size() + sizeof(Ram_quota*),
                                      Fpu::state_align(), "Fpu state");

#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/fpu_alloc.cpp"


Slab_cache *
Fpu_alloc::slab_alloc()
{
  return &_fpu_state_allocator;
}

#line 27 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/fpu_alloc.cpp"


bool
Fpu_alloc::alloc_state(Ram_quota *q, Fpu_state *s) 
{
  unsigned long sz = Fpu::state_size();
  void *b;
  if (!(b = slab_alloc()->q_alloc(q)))
    return false;

  *((Ram_quota **)((char*)b + sz)) = q;
  s->_state_buffer = b;
  Fpu::init_state(s);

  return true;
}

#line 43 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/fpu_alloc.cpp"


void
Fpu_alloc::free_state(Fpu_state *s) 
{
  if (s->_state_buffer) 
    {
      unsigned long sz = Fpu::state_size();
      Ram_quota *q = *((Ram_quota **)((char*)(s->_state_buffer) + sz));
      slab_alloc()->q_free (q, s->_state_buffer);
      s->_state_buffer = 0;

      // transferred FPU state may leed to quotas w/o a task but only FPU 
      // contexts allocated
      if (q->current()==0)
	delete q;
    }
}
