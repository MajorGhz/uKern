// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "dbg_page_info.h"
#include "dbg_page_info_i.h"

#line 68 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/dbg_page_info.cpp"


static Dbg_page_info_table _t;
#line 78 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/dbg_page_info.cpp"

static Kmem_slab_t<Dbg_page_info> _dbg_page_info_allocator("Dbg_page_info");

#line 71 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/dbg_page_info.cpp"


Dbg_page_info_table &
Dbg_page_info::table()
{
  return _t;
}

#line 80 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/dbg_page_info.cpp"


Dbg_page_info::Allocator *
Dbg_page_info::alloc()
{ return &_dbg_page_info_allocator; }

#line 96 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/dbg_page_info.cpp"


Dbg_page_info *
Dbg_page_info_table::operator[](Page_number pfn) const
{
  Entry &e = const_cast<Dbg_page_info_table*>(this)->_tab[hash(pfn)];
  auto g = lock_guard(e.l);
  // we know that *end() is NULL
  return *find(e.h.begin(), e.h.end(), pfn);
}

#line 106 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/dbg_page_info.cpp"


void
Dbg_page_info_table::insert(Dbg_page_info *i)
{
  Entry *e = &_tab[hash(i->_pfn)];
  auto g = lock_guard(e->l);
  e->h.add(i);
}

#line 115 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/dbg_page_info.cpp"


Dbg_page_info *
Dbg_page_info_table::remove(Page_number pfn)
{
  Entry *e = &_tab[hash(pfn)];
  auto g = lock_guard(e->l);

  List::Iterator i = find(e->h.begin(), e->h.end(), pfn);
  if (i == e->h.end())
    return 0;

  Dbg_page_info *r = *i;
  e->h.erase(i);
  return r;
}
