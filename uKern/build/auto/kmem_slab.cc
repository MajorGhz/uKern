// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "kmem_slab.h"
#include "kmem_slab_i.h"

#line 30 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_slab.cpp"

Kmem_slab::Reap_list Kmem_slab::reap_list;
#line 32 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_slab.cpp"

// Kmem_slab -- A type-independent slab cache allocator for Fiasco,
// derived from a generic slab cache allocator (Slab_cache in
// lib/slab.cpp).

// This specialization adds low-level page allocation and locking to
// the slab allocator implemented in our base class (Slab_cache).
//-
#line 121 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_slab.cpp"

static Kmem_alloc_reaper kmem_slab_reaper(Kmem_slab::reap_all);

#line 46 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_slab.cpp"

// Specializations providing their own block_alloc()/block_free() can
// also request slab sizes larger than one page.

Kmem_slab::Kmem_slab(unsigned long slab_size,
				   unsigned elem_size,
				   unsigned alignment,
				   char const *name)
  : Slab_cache(slab_size, elem_size, alignment, name)
{
  reap_list.add(this, mp_cas<cxx::S_list_item*>);
}

#line 58 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_slab.cpp"

// Specializations providing their own block_alloc()/block_free() can
// also request slab sizes larger than one page.

Kmem_slab::Kmem_slab(unsigned elem_size,
                     unsigned alignment,
                     char const *name,
                     unsigned long min_size,
                     unsigned long max_size)
  : Slab_cache(elem_size, alignment, name, min_size, max_size)
{
  reap_list.add(this, mp_cas<cxx::S_list_item*>);
}

#line 71 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_slab.cpp"


Kmem_slab::~Kmem_slab()
{
  destroy();
}

#line 77 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_slab.cpp"


// Callback functions called by our super class, Slab_cache, to
// allocate or free blocks

void *
Kmem_slab::block_alloc(unsigned long size, unsigned long)
{
  assert (size >= Buddy_alloc::Min_size);
  assert (size <= Buddy_alloc::Max_size);
  assert (!(size & (size - 1)));
  (void)size;
  return Kmem_alloc::allocator()->unaligned_alloc(size);
}

#line 91 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_slab.cpp"

void
Kmem_slab::block_free(void *block, unsigned long size)
{
  Kmem_alloc::allocator()->unaligned_free(size, block);
}

#line 97 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_slab.cpp"

// 
// Memory reaper
// 

size_t
Kmem_slab::reap_all(bool desperate)
{
  size_t freed = 0;

  for (Reap_list::Const_iterator alloc = reap_list.begin();
       alloc != reap_list.end(); ++alloc)
    {
      size_t got;
      do
	{
	  got = alloc->reap();
	  freed += got;
	}
      while (desperate && got);
    }

  return freed;
}
