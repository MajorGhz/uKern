// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_counters_i_h
#define jdb_counters_i_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_counters.cpp"

#include <cstdio>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_counters.cpp"
#include <cstring>
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_counters.cpp"
#include "config.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_counters.cpp"
#include "jdb_tbuf.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_counters.cpp"
#include "jdb_module.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_counters.cpp"
#include "kern_cnt.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_counters.cpp"
#include "simpleio.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_counters.cpp"
#include "static_init.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_counters.cpp"

class Jdb_counters : public Jdb_module
{
public:
  Jdb_counters() FIASCO_INIT;
private:
  static char counters_cmd;

public:  
#line 41 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_counters.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&, char const *&, int &);
  
#line 67 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_counters.cpp"
  Jdb_counters::Cmd const *
  cmds() const;
  
#line 79 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_counters.cpp"
  int
  num_cmds() const;

private:  
#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_counters.cpp"
  void
  show();
  
#line 33 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_counters.cpp"
  void
  reset();
};

#endif // jdb_counters_i_h
