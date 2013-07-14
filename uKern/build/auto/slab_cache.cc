// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "slab_cache.h"
#include "slab_cache_i.h"


#line 65 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"

// default deallocator must not be called -- must use explicit destruction

inline void 
Slab::operator delete(void* /*block*/)
{
  assert (!"slab::operator delete called");
}

#line 201 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"


inline Slab *
Slab_cache::get_available_locked()
{
  Slab *s = _partial.front();
  if (s)
    return s;

  s = _empty.front();
  if (s)
    {
      --_num_empty;
      _empty.remove(s);
      _partial.add(s);
    }

  return s;
}

#line 73 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"


Slab::Slab(unsigned elems, unsigned entry_size, void *mem)
: _elems(elems), _in_use(0)
{
  // Compute pointer to first data element, now taking into account
  // the latest colorization offset
  char *data = reinterpret_cast<char*>(mem);

  // Initialize the cache elements
  for (unsigned i = elems; i > 0; --i)
    {
      Slab_entry *e = reinterpret_cast<Slab_entry *>(data);
      _free.push_front(e);
      data += entry_size;
    }
}

#line 90 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"


void *
Slab::alloc()
{
  Slab_entry *e = _free.pop_front();

  if (! e)
    return 0;

  ++_in_use;
  return e;
}

#line 103 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"


void
Slab::free(void *entry)
{
  _free.add(reinterpret_cast<Slab_entry *>(entry));

  assert(_in_use);
  --_in_use;
}

#line 187 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"



Slab_cache::~Slab_cache()
{
  // the derived class should call destroy() before deleting us.
  // assert(_first_slab == 0);
}

#line 220 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"


void *
Slab_cache::alloc()	// request initialized member from cache
{
  void *unused_block = 0;
  void *ret;
    {
      auto guard = lock_guard(lock);

      Slab *s = get_available_locked();

      if (EXPECT_FALSE(!s))
	{
	  guard.reset();

	  char *m = (char*)block_alloc(_slab_size, _slab_size);
	  Slab *new_slab = 0;
	  if (m)
	    new_slab = new (m + _slab_size - sizeof(Slab)) Slab(_elem_num, _entry_size, m);

	  guard.lock(&lock);

	  // retry gettin a slab that might be allocated by a different
	  // CPU meanwhile
	  s = get_available_locked();

	  if (!s)
	    {
	      // real OOM
	      if (!m)
		return 0;

	      _partial.add(new_slab);
	      s = new_slab;
	    }
	  else
	    unused_block = m;
	}

      ret = s->alloc();
      assert(ret);

      if (s->is_full())
	{
	  cxx::H_list<Slab>::remove(s);
	  _full.add(s);
	}
    }

  if (unused_block)
    block_free(unused_block, _slab_size);

  return ret;
}

#line 292 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"


void
Slab_cache::free(void *cache_entry) // return initialized member to cache
{
  Slab *to_free = 0;
    {
      auto guard = lock_guard(lock);

      Slab *s = reinterpret_cast<Slab*>
	((reinterpret_cast<unsigned long>(cache_entry) & ~(_slab_size - 1)) + _slab_size - sizeof(Slab));

      bool was_full = s->is_full();

      s->free(cache_entry);

      if (was_full)
	{
	  cxx::H_list<Slab>::remove(s);
	  _partial.add(s);
	}
      else if (s->is_empty())
	{
	  cxx::H_list<Slab>::remove(s);
	  if (_num_empty < 2)
	    {
	      _empty.add(s);
	      ++_num_empty;
	    }
	  else
	    to_free = s;
	}
      else
	{
	  // We weren't either full or empty; we already had free
	  // elements.  This changes nothing in the queue, and there
	  // already must have been a _first_available_slab.
	}
    }

  if (to_free)
    {
      to_free->~Slab();
      block_free(reinterpret_cast<char *>(to_free + 1) - _slab_size, _slab_size);
    }
}

#line 347 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"


unsigned long
Slab_cache::reap()		// request that cache returns memory to system
{
  Slab *s = 0;
  unsigned long sz = 0;

  for (;;)
    {
	{
	  auto guard = lock_guard(lock);

	  s = _empty.front();
	  // nothing to free
	  if (!s)
	    return 0;

	  cxx::H_list<Slab>::remove(s);
	}

      // explicitly call destructor to delete s;
      s->~Slab();
      block_free(reinterpret_cast<char *>(s + 1) - _slab_size, _slab_size);
      sz += _slab_size;
    }

  return sz;
}

#line 380 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"



void
Slab_cache::debug_dump()
{
  printf ("%s: %lu-KB slabs (elems per slab=%d ",
	  _name, _slab_size / 1024, _elem_num);

  unsigned count = 0, total = 0, total_elems = 0;
  for (Slab_list::Const_iterator s = _full.begin(); s != _full.end(); ++s)
    {
      if (!s->is_full())
	printf ("\n*** wrongly-enqueued full slab found\n");

      ++count;
      total_elems += s->in_use();
    }

  total += count;

  printf ("%u full, ", count);

  count = 0;
  for (Slab_list::Const_iterator s = _partial.begin(); s != _partial.end(); ++s)
    {
      if (s->is_full() || s->is_empty())
	printf ("\n*** wrongly-enqueued full slab found\n");

      count++;
      total_elems += s->in_use();
    }

  total += count;

  printf ("%u used, ", count);

  count = 0;
  for (Slab_list::Const_iterator s = _empty.begin(); s != _empty.end(); ++s)
    {
      if (! s->is_empty())
	printf ("\n*** wrongly-enqueued nonempty slab found\n");
      count++;
    }

  unsigned total_used = total;
  total += count;

  printf ("%u empty = %u total) = %lu KB,\n  %u elems (size=%u)",
	  count, total, total * _slab_size / 1024,
	  total_elems, _entry_size);

  if (total_elems)
    printf (", overhead = %lu B (%lu B)  = %lu%% (%lu%%) \n",
	    total * _slab_size - total_elems * _entry_size,
	    total_used * _slab_size - total_elems * _entry_size,
	    100 - total_elems * _entry_size * 100 / (total * _slab_size),
	    100 - total_elems * _entry_size * 100 / (total_used * _slab_size));
  else
    printf ("\n");
}
