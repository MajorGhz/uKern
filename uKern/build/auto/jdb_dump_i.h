// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_dump_i_h
#define jdb_dump_i_h
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_dump.cpp"

#include <cstdio>
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include <cctype>
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_dump.cpp"

#include "config.h"
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include "jdb.h"
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include "jdb_disasm.h"
#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include "jdb_table.h"
#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include "jdb_input.h"
#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include "jdb_module.h"
#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include "jdb_screen.h"
#line 21 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include "jdb_symbol.h"
#line 22 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include "kernel_console.h"
#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include "keycodes.h"
#line 24 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include "simpleio.h"
#line 25 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include "static_init.h"
#line 26 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include "types.h"
#line 27 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include "task.h"
#line 28 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_dump.cpp"

class Jdb_dump : public Jdb_module, public Jdb_table
{
public:
  Jdb_dump() FIASCO_INIT;
  unsigned long cols() const { return Jdb_screen::cols(); }
  unsigned long rows() const { return Jdb_screen::rows(); }
  void draw_entry(unsigned long row, unsigned long col);
  void print_statline();

private:
  enum
    {
      B_MODE = 'b',	// byte
      C_MODE = 'c',	// char
      D_MODE = 'd',	// word
    };
  
  static const unsigned elb = sizeof(Mword);
  static char show_adapter_memory;
  static Address highlight_start, highlight_end;

  int level;
  Space *task;
  char dump_type;
  static Address virt_addr;

public:  
#line 73 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
  unsigned
  col_width(unsigned col) const;
  
#line 85 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
  void
  print_statline(unsigned long row, unsigned long col);
  
#line 175 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
  Jdb_module::Action_code
  dump(Address virt, Space *task, int level);
  
#line 193 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
  bool
  edit_entry(unsigned long row, unsigned long col, unsigned cx, unsigned cy);
  
#line 215 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
  unsigned
  key_pressed(int c, unsigned long &row, unsigned long &col);
  
#line 371 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&args, char const *&fmt, int &next_char);
  
#line 397 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 410 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
  int
  num_cmds() const;

private:  
#line 66 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
  inline Address
  virt(unsigned long row, unsigned long col);
};

//
// IMPLEMENTATION of inline functions follows
//


#line 64 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_dump.cpp"


inline Address
Jdb_dump::virt(unsigned long row, unsigned long col)
{
  return (col-1) * elb + row * (cols()-1) * elb;
}

#endif // jdb_dump_i_h
