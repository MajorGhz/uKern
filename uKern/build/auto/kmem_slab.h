// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kmem_slab_h
#define kmem_slab_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_slab.cpp"

#include <cstddef>		// size_t
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_slab.cpp"
#include "buddy_alloc.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_slab.cpp"
#include "config.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_slab.cpp"
#include "lock_guard.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_slab.cpp"
#include "spin_lock.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_slab.cpp"

#include "slab_cache.h"		// Slab_cache
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_slab.cpp"
#include <cxx/slist>

//
// INTERFACE definition follows 
//

#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_slab.cpp"

class Kmem_slab : public Slab_cache, public cxx::S_list_item
{
  friend class Jdb_kern_info_memory;
  typedef cxx::S_list_bss<Kmem_slab> Reap_list;

  // STATIC DATA
  static Reap_list reap_list;

public:  
#line 59 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_slab.cpp"
  // Specializations providing their own block_alloc()/block_free() can
  // also request slab sizes larger than one page.
  
  Kmem_slab(unsigned elem_size,
                       unsigned alignment,
                       char const *name,
                       unsigned long min_size = Buddy_alloc::Min_size,
                       unsigned long max_size = Buddy_alloc::Max_size);
  
#line 73 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_slab.cpp"
  ~Kmem_slab();
  
#line 98 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_slab.cpp"
  // 
  // Memory reaper
  // 
  
  static size_t
  reap_all(bool desperate);

protected:  
#line 47 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_slab.cpp"
  // Specializations providing their own block_alloc()/block_free() can
  // also request slab sizes larger than one page.
  
  Kmem_slab(unsigned long slab_size,
  				   unsigned elem_size,
  				   unsigned alignment,
  				   char const *name);

private:  
#line 79 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_slab.cpp"
  // Callback functions called by our super class, Slab_cache, to
  // allocate or free blocks
  
  virtual void *
  block_alloc(unsigned long size, unsigned long);
  
#line 92 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_slab.cpp"
  virtual void
  block_free(void *block, unsigned long size);
};
#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kmem_slab.cpp"

template< typename T >
class Kmem_slab_t : public Kmem_slab
{
public:
  explicit Kmem_slab_t(char const *name)
  : Kmem_slab(sizeof(T), __alignof(T), name) {}
};

#endif // kmem_slab_h
