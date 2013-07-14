// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_factory_i_h
#define jdb_factory_i_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_factory.cpp"

#include <climits>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_factory.cpp"
#include <cstring>
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_factory.cpp"
#include <cstdio>
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_factory.cpp"

#include "jdb.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_factory.cpp"
#include "jdb_core.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_factory.cpp"
#include "jdb_module.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_factory.cpp"
#include "jdb_screen.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_factory.cpp"
#include "jdb_kobject.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_factory.cpp"
#include "kernel_console.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_factory.cpp"
#include "keycodes.h"
#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_factory.cpp"
#include "factory.h"
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_factory.cpp"
#include "simpleio.h"
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_factory.cpp"
#include "static_init.h"
#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_factory.cpp"

class Jdb_factory : public Jdb_kobject_handler
{
public:
  Jdb_factory() FIASCO_INIT;

public:  
#line 32 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_factory.cpp"
  bool
  show_kobject(Kobject_common *, int );
  
#line 39 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_factory.cpp"
  char const *
  kobject_type() const;
  
#line 46 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_factory.cpp"
  int
  show_kobject_short(char *buf, int max, Kobject_common *o);
};

#endif // jdb_factory_i_h
