// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_regex_h
#define jdb_regex_h
#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_regex.cpp"

#include "initcalls.h"
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_regex.cpp"
#include "regex.h"

//
// INTERFACE definition follows 
//

#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_regex.cpp"

class Jdb_regex
{
private:
  static const unsigned heap_size = 64 * 1024;
  static char _init_done;

public:
  static bool avail() { return true; }

  static regex_t     _r;
  static regmatch_t  _matches[1];

public:  
#line 61 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_regex.cpp"
  static void FIASCO_INIT
  init();
  
#line 75 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_regex.cpp"
  static int
  start(const char *searchstr);
  
#line 85 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_regex.cpp"
  static int
  find(const char *buffer, const char **beg, const char **end);
};

#endif // jdb_regex_h
