// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_scheduler_i_h
#define jdb_scheduler_i_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_scheduler.cpp"

#include <climits>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_scheduler.cpp"
#include <cstring>
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_scheduler.cpp"
#include <cstdio>
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_scheduler.cpp"

#include "scheduler.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_scheduler.cpp"
#include "jdb.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_scheduler.cpp"
#include "jdb_core.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_scheduler.cpp"
#include "jdb_module.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_scheduler.cpp"
#include "jdb_screen.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_scheduler.cpp"
#include "jdb_kobject.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_scheduler.cpp"
#include "kernel_console.h"
#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_scheduler.cpp"
#include "keycodes.h"
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_scheduler.cpp"
#include "simpleio.h"
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_scheduler.cpp"
#include "static_init.h"
#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_scheduler.cpp"

class Jdb_cpu : public Jdb_kobject_handler
{
public:
  Jdb_cpu() FIASCO_INIT;

public:  
#line 32 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_scheduler.cpp"
  bool
  show_kobject(Kobject_common *, int );
  
#line 39 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_scheduler.cpp"
  char const *
  kobject_type() const;
};

#endif // jdb_scheduler_i_h
