// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_exit_module_i_h
#define jdb_exit_module_i_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"

#include <cstdio>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"
#include "simpleio.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"

#include "jdb.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"
#include "jdb_module.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"
#include "jdb_screen.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"
#include "kernel_console.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"
#include "static_init.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"
#include "terminate.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"
#include "types.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"

/**
 * Private 'exit' module.
 *
 * This module handles the 'exit' or '^' command that
 * makes a call to exit() and virtually reboots the system.
 */
class Jdb_exit_module : public Jdb_module
{
public:
  Jdb_exit_module() FIASCO_INIT;

public:  
#line 29 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&, char const *&, int &);
  
#line 51 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"
  int
  num_cmds() const;
  
#line 58 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"
  Jdb_module::Cmd const *
  cmds() const;

private:  
#line 106 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"
  void
  vmx_off() const;
};

#endif // jdb_exit_module_i_h
