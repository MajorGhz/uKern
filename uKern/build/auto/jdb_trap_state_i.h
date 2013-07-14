// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_trap_state_i_h
#define jdb_trap_state_i_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trap_state.cpp"

#include <cstdio>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trap_state.cpp"
#include "simpleio.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trap_state.cpp"

#include "jdb.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trap_state.cpp"
#include "jdb_module.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trap_state.cpp"
#include "static_init.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trap_state.cpp"
#include "types.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trap_state.cpp"


/**
 * Private 'exit' module.
 * 
 * This module handles the 'exit' or '^' command that
 * makes a call to exit() and virtually reboots the system.
 */
class Jdb_trap_state_module : public Jdb_module
{
public:
  Jdb_trap_state_module() FIASCO_INIT;

public:  
#line 43 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trap_state.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&argbuf, char const *&fmt, int &next);
  
#line 69 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trap_state.cpp"
  int
  num_cmds() const;
  
#line 76 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trap_state.cpp"
  Jdb_module::Cmd const *
  cmds() const;

private:  
#line 28 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trap_state.cpp"
  static void
  print_trap_state(Cpu_number cpu);
};

#endif // jdb_trap_state_i_h
