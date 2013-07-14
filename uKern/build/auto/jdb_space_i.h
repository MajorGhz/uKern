// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_space_i_h
#define jdb_space_i_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"

#include <climits>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"
#include <cstring>
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"
#include <cstdio>
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"

#include "jdb.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"
#include "jdb_core.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"
#include "jdb_module.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"
#include "jdb_screen.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"
#include "jdb_kobject.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"
#include "kernel_console.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"
#include "kernel_task.h"
#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"
#include "keycodes.h"
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"
#include "ram_quota.h"
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"
#include "simpleio.h"
#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"
#include "task.h"
#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"
#include "thread_object.h"
#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"
#include "static_init.h"
#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"

class Jdb_space : public Jdb_module, public Jdb_kobject_handler
{
public:
  Jdb_space() FIASCO_INIT;
private:
  static Task *task;

public:  
#line 39 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"
  bool
  show_kobject(Kobject_common *o, int lvl);
  
#line 54 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"
  char const *
  kobject_type() const;
  
#line 61 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"
  int
  show_kobject_short(char *buf, int max, Kobject_common *o);
  
#line 103 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&, char const *&, int &);
  
#line 115 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 126 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"
  int
  num_cmds() const;

private:  
#line 76 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"
  static void
  print_space(Space *s);
  
#line 83 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"
  void
  show(Task *t);
};

#endif // jdb_space_i_h
