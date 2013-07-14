// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_gzip_i_h
#define jdb_gzip_i_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"

#include <cstring>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
#include <cstdio>
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"

#include "config.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
#include "console.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
#include "gzip.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
#include "kernel_console.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
#include "kmem_alloc.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
#include "panic.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
#include "static_init.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"

class Jdb_gzip : public Console
{
  static const unsigned heap_pages = 28;
  char   active;
  char   init_done;
  static Console *uart;

public:  
#line 42 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
  inline void
  enable();
  
#line 56 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
  inline void
  disable();
  
#line 66 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
  void
  state(Mword new_state);
  
#line 81 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
  int
  write(char const *str, size_t len);
  
#line 89 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
  static Console*
  console();
  
#line 97 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
  Mword
  get_attributes() const;
  
#line 103 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
  static FIASCO_INIT
  void
  init();

private:  
#line 24 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
  Jdb_gzip();
  
#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
  static void
  raw_write(const char *s, size_t len);
};

#endif // jdb_gzip_i_h
