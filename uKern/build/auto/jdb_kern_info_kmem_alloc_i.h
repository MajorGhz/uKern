// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_kern_info_kmem_alloc_i_h
#define jdb_kern_info_kmem_alloc_i_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info_kmem_alloc.cpp"

#include "static_init.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info_kmem_alloc.cpp"
#include "jdb_kern_info.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info_kmem_alloc.cpp"
#include "kmem_alloc.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info_kmem_alloc.cpp"
#include "kmem_slab.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info_kmem_alloc.cpp"

class Jdb_kern_info_memory : public Jdb_kern_info_module
{
public:  
#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info_kmem_alloc.cpp"
  Jdb_kern_info_memory();
  
#line 21 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info_kmem_alloc.cpp"
  void
  show();
};

#endif // jdb_kern_info_kmem_alloc_i_h
