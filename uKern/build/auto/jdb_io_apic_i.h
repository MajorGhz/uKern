// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_io_apic_i_h
#define jdb_io_apic_i_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_io_apic.cpp"

#include <cstdio>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_io_apic.cpp"
#include "simpleio.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_io_apic.cpp"

#include "apic.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_io_apic.cpp"
#include "io_apic.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_io_apic.cpp"
#include "jdb.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_io_apic.cpp"
#include "jdb_module.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_io_apic.cpp"
#include "jdb_screen.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_io_apic.cpp"
#include "static_init.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_io_apic.cpp"
#include "types.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_io_apic.cpp"


/**
 * Private 'exit' module.
 * 
 * This module handles the 'exit' or '^' command that
 * makes a call to exit() and virtually reboots the system.
 */
class Jdb_io_apic_module : public Jdb_module
{
public:
  Jdb_io_apic_module() FIASCO_INIT;

public:  
#line 60 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_io_apic.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&, char const *&, int &);
  
#line 111 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_io_apic.cpp"
  int
  num_cmds() const;
  
#line 118 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_io_apic.cpp"
  Jdb_module::Cmd const *
  cmds() const;

private:  
#line 30 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_io_apic.cpp"
  static void
  print_lapic(Cpu_number cpu, void *);
  
#line 53 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_io_apic.cpp"
  static void
  remote_print_lapic(Cpu_number cpu);
};

#endif // jdb_io_apic_i_h
