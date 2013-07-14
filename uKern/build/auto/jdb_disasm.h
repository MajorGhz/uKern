// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_disasm_h
#define jdb_disasm_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_disasm.cpp"

#include "jdb_module.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_disasm.cpp"
#include "l4_types.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_disasm.cpp"
#include "types.h"

//
// INTERFACE definition follows 
//

#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_disasm.cpp"

class Space;
#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_disasm.cpp"

class Jdb_disasm : public Jdb_module
{
public:
  Jdb_disasm() FIASCO_INIT;
  static bool avail() { return true; }
private:
  static char show_intel_syntax;
  static char show_lines;

public:  
#line 153 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_disasm.cpp"
  static bool
  show_disasm_line(int len, Address &addr,
  			     int show_symbols, Space *task);
  
#line 182 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_disasm.cpp"
  static Jdb_module::Action_code
  show(Address virt, Space *task, int level, bool do_clear_screen = false);
  
#line 310 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_disasm.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&args, char const *&fmt, int &next_char);
  
#line 335 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_disasm.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 349 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_disasm.cpp"
  int
  num_cmds() const;

private:  
#line 73 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_disasm.cpp"
  static bool
  disasm_line(char *buffer, int buflen, Address &addr,
  			int show_symbols, Space *task);
  
#line 92 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_disasm.cpp"
  static int
  at_symbol(Address addr, Space *task);
  
#line 99 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_disasm.cpp"
  static int
  at_line(Address addr, Space *task);
  
#line 107 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_disasm.cpp"
  static Address
  disasm_offset(Address &start, int offset, Space *task);
};

#endif // jdb_disasm_h
