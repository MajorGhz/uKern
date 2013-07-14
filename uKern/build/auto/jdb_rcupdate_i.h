// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_rcupdate_i_h
#define jdb_rcupdate_i_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_rcupdate.cpp"

#include <climits>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_rcupdate.cpp"
#include <cstring>
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_rcupdate.cpp"
#include <cstdio>
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_rcupdate.cpp"

#include "jdb.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_rcupdate.cpp"
#include "jdb_core.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_rcupdate.cpp"
#include "jdb_module.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_rcupdate.cpp"
#include "jdb_screen.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_rcupdate.cpp"
#include "kernel_console.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_rcupdate.cpp"
#include "keycodes.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_rcupdate.cpp"
#include "ram_quota.h"
#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_rcupdate.cpp"
#include "simpleio.h"
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_rcupdate.cpp"
#include "rcupdate.h"
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_rcupdate.cpp"
#include "static_init.h"
#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_rcupdate.cpp"

class Jdb_rcupdate : public Jdb_module
{
public:
  Jdb_rcupdate() FIASCO_INIT;

public:  
#line 37 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_rcupdate.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&, char const *&, int &);
  
#line 77 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_rcupdate.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 88 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_rcupdate.cpp"
  int
  num_cmds() const;

private:  
#line 30 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_rcupdate.cpp"
  static void
  print_batch(Rcu_batch const &b);
};

#endif // jdb_rcupdate_i_h
