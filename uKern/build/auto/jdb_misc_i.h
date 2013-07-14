// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_misc_i_h
#define jdb_misc_i_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"

#include <cstdio>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
#include "config.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
#include "cpu.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
#include "jdb.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
#include "jdb_ktrace.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
#include "jdb_module.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
#include "jdb_symbol.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
#include "jdb_screen.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
#include "static_init.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
#include "task.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
#include "x86desc.h"
#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"

class Jdb_misc_general : public Jdb_module
{
public:
  Jdb_misc_general() FIASCO_INIT;
private:
  static char first_char;

public:  
#line 27 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&, char const *&, int &);
  
#line 48 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 61 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
  int
  num_cmds() const;
};
#line 74 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"


//---------------------------------------------------------------------------//

class Jdb_misc_debug : public Jdb_module
{
public:
  Jdb_misc_debug() FIASCO_INIT;
private:
  static char     first_char;
  static Mword    task;

public:  
#line 101 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&args, char const *&fmt, int &);
  
#line 205 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 222 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
  int
  num_cmds() const;

private:  
#line 90 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
  static void
  show_lbr_entry(const char *str, Address addr);
  
#line 237 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
  static void
  show_ldt();
};
#line 271 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"

class Jdb_misc_info : public Jdb_module
{
public:
  Jdb_misc_info() FIASCO_INIT;
private:
  static char       first_char;
  static Address    addr;
  static Mword      value;
  static Unsigned64 value64;

public:  
#line 289 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&args, char const *&fmt, int &);
  
#line 374 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 390 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
  int
  num_cmds() const;
};

#endif // jdb_misc_i_h
