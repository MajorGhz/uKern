// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef dbg_page_info_h
#define dbg_page_info_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/dbg_page_info.cpp"

#include "types.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/dbg_page_info.cpp"
#include "lock_guard.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/dbg_page_info.cpp"
#include "spin_lock.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/dbg_page_info.cpp"
#include "slab_cache.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/dbg_page_info.cpp"
#include <cxx/slist>

//
// INTERFACE definition follows 
//

#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/dbg_page_info.cpp"

class Dbg_page_info_table;
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/dbg_page_info.cpp"

class Dbg_page_info : public cxx::S_list_item
{
  friend class Dbg_page_info_table;

private:
  Page_number const _pfn;
  typedef unsigned long Buf[5];
  Buf _buf;

  char *b() { return reinterpret_cast<char*>(_buf); }
  char const *b() const { return reinterpret_cast<char const*>(_buf); }

  typedef Slab_cache Allocator;

public:
  void *operator new (size_t) throw() { return alloc()->alloc(); }
  void operator delete (void *p, size_t) { alloc()->free(p); }

  enum { Buffer_size = sizeof(Buf) };

  Dbg_page_info(Page_number pfn) : _pfn(pfn) {}

  bool match(Page_number p) { return _pfn == p; }

  template<typename T>
  T *info()
  { return reinterpret_cast<T*>(b()); }

  template<typename T>
  T const *info() const
  { return reinterpret_cast<T const*>(b()); }

public:  
#line 73 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/dbg_page_info.cpp"
  static Dbg_page_info_table &
  table();

private:  
#line 82 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/dbg_page_info.cpp"
  static Dbg_page_info::Allocator *
  alloc();
};
#line 43 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/dbg_page_info.cpp"

class Dbg_page_info_table
{
private:
  typedef cxx::S_list_bss<Dbg_page_info> List;

public:
  struct Entry
  {
    List h;
    Spin_lock<> l;
  };
  enum { Hash_tab_size = 1024 };

private:
  Entry _tab[Hash_tab_size];
  static unsigned hash(Page_number p)
  { return cxx::int_value<Page_number>(p) % Hash_tab_size; }

public:  
#line 88 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/dbg_page_info.cpp"
  template<typename B, typename E> static inline B
  find(B const &b, E const &e, Page_number p);
  
#line 98 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/dbg_page_info.cpp"
  Dbg_page_info *
  operator[](Page_number pfn) const;
  
#line 108 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/dbg_page_info.cpp"
  void
  insert(Dbg_page_info *i);
  
#line 117 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/dbg_page_info.cpp"
  Dbg_page_info *
  remove(Page_number pfn);
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 85 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/dbg_page_info.cpp"


 
template<typename B, typename E> inline B
Dbg_page_info_table::find(B const &b, E const &e, Page_number p)
{
  for (B i = b; i != e; ++i)
    if (i->match(p))
      return i;
  return e;
}

#endif // dbg_page_info_h
