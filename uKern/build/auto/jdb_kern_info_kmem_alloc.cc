// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_kern_info_kmem_alloc.h"
#include "jdb_kern_info_kmem_alloc_i.h"

#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info_kmem_alloc.cpp"

static Jdb_kern_info_memory k_m INIT_PRIORITY(JDB_MODULE_INIT_PRIO+1);

#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info_kmem_alloc.cpp"


Jdb_kern_info_memory::Jdb_kern_info_memory()
  : Jdb_kern_info_module('m', "kmem_alloc::debug_dump")
{
  Jdb_kern_info::register_subcmd(this);
}

#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info_kmem_alloc.cpp"


void
Jdb_kern_info_memory::show()
{
  ((Kmem_alloc*)Kmem_alloc::allocator())->debug_dump();
  typedef Kmem_slab::Reap_list::Const_iterator Iter;

  // Slab allocators
  for (Iter alloc = Kmem_slab::reap_list.begin();
       alloc != Kmem_slab::reap_list.end(); ++alloc)
    alloc->debug_dump();
}
