// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "kmem_alloc.h"
#include "kmem_alloc_i.h"

#line 87 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_alloc.cpp"

static Kmem_alloc::Alloc _a;
#line 89 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
Kmem_alloc::Alloc *Kmem_alloc::a = &_a;
#line 90 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
unsigned long Kmem_alloc::_orig_free;
#line 91 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
Kmem_alloc::Lock Kmem_alloc::lock;
#line 92 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
Kmem_alloc* Kmem_alloc::_alloc;
#line 306 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_alloc.cpp"

Kmem_alloc_reaper::Reaper_list Kmem_alloc_reaper::mem_reapers;

#line 110 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_alloc.cpp"


void
Kmem_alloc::allocator(Kmem_alloc *a)
{
  _alloc=a;
}

#line 117 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_alloc.cpp"

FIASCO_INIT
void
Kmem_alloc::init()
{
  static Kmem_alloc al;
  Kmem_alloc::allocator(&al);
}

#line 125 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_alloc.cpp"


void
Kmem_alloc::dump() const
{ a->dump(); }

#line 145 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_alloc.cpp"


void *
Kmem_alloc::unaligned_alloc(unsigned long size)
{
  assert(size >=8 /*NEW INTERFACE PARANIOIA*/);
  void* ret;

  {
    auto guard = lock_guard(lock);
    ret = a->alloc(size);
  }

  if (!ret)
    {
      Kmem_alloc_reaper::morecore (/* desperate= */ true);

      auto guard = lock_guard(lock);
      ret = a->alloc(size);
    }

  return ret;
}

#line 168 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_alloc.cpp"


void
Kmem_alloc::unaligned_free(unsigned long size, void *page)
{
  assert(size >=8 /*NEW INTERFACE PARANIOIA*/);
  auto guard = lock_guard(lock);
  a->free(page, size);
}

#line 177 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_alloc.cpp"


FIASCO_INIT
unsigned long
Kmem_alloc::create_free_map(Kip const *kip, Mem_region_map_base *map)
{
  unsigned long available_size = 0;
  Mem_desc const *md = kip->mem_descs();
  Mem_desc const *const md_end = md + kip->num_mem_descs();

  for (; md < md_end; ++md)
    {
      if (!md->valid())
	{
	  const_cast<Mem_desc*>(md)->type(Mem_desc::Undefined);
	  continue;
	}

      if (md->is_virtual())
	continue;

      unsigned long s = md->start();
      unsigned long e = md->end();

      // Sweep out stupid descriptors (that have the end before the start)

      switch (md->type())
	{
	case Mem_desc::Conventional:
	  s = (s + Config::PAGE_SIZE - 1) & ~(Config::PAGE_SIZE - 1);
	  e = ((e + 1) & ~(Config::PAGE_SIZE - 1)) - 1;
	  if (e <= s)
	    break;
	  available_size += e - s + 1;
	  if (!map->add(Mem_region(s, e)))
	    panic("Kmem_alloc::create_free_map(): memory map too small");
	  break;
	case Mem_desc::Reserved:
	case Mem_desc::Dedicated:
	case Mem_desc::Shared:
	case Mem_desc::Arch:
	case Mem_desc::Bootloader:
	  s = s & ~(Config::PAGE_SIZE - 1);
	  e = ((e + Config::PAGE_SIZE) & ~(Config::PAGE_SIZE - 1)) - 1;
	  if (!map->sub(Mem_region(s, e)))
	    panic("Kmem_alloc::create_free_map(): memory map too small");
	  break;
	default:
	  break;
	}
    }

  return available_size;
}

#line 315 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_alloc.cpp"


size_t
Kmem_alloc_reaper::morecore(bool desperate)
{
  size_t freed = 0;

  for (Reaper_list::Const_iterator reaper = mem_reapers.begin();
       reaper != mem_reapers.end(); ++reaper)
    {
      freed += reaper->_reap(desperate);
    }

  return freed;
}
