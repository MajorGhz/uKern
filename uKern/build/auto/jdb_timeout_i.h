// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_timeout_i_h
#define jdb_timeout_i_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"

#include <cstdio>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include <cstring>
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"

#include "config.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "globals.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "ipc_timeout.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "jdb.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "jdb_kobject.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "jdb_kobject_names.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "jdb_module.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "jdb_screen.h"
#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "kernel_console.h"
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "keycodes.h"
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "kmem.h"
#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "simpleio.h"
#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "static_init.h"
#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "timeout.h"
#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "timeslice_timeout.h"
#line 21 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "thread.h"
#line 22 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"

class Jdb_list_timeouts : public Jdb_module
{
public:
  Jdb_list_timeouts() FIASCO_INIT;
private:
  enum
  {
    Timeout_ipc       = 1,
    Timeout_deadline  = 2,
    Timeout_timeslice = 3
  };

public:  
#line 422 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&, char const *&, int &);
  
#line 432 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 444 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
  int
  num_cmds() const;

private:  
#line 188 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
  // use implicit knowledge to determine the type of a timeout because we
  // cannot use dynamic_cast (we compile with -fno-rtti)
  
  static int
  get_type(Timeout *t);
  
#line 209 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
  static Thread*
  get_owner(Timeout *t);
  
#line 231 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
  static void
  show_header();
  
#line 240 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
  static void
  list_timeouts_show_timeout(Timeout *t);
  
#line 303 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
  static void
  list();
};

#endif // jdb_timeout_i_h
