// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_bt_i_h
#define jdb_bt_i_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"

#include <cstdio>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
#include <cctype>
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"

#include "config.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
#include "jdb.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
#include "jdb_input.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
#include "jdb_kobject.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
#include "jdb_lines.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
#include "jdb_module.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
#include "jdb_symbol.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
#include "mem_layout.h"
#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
#include "keycodes.h"
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
#include "thread_object.h"
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
#include "task.h"
#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"

class Jdb_bt : public Jdb_module, public Jdb_input_task_addr
{
public:
  Jdb_bt() FIASCO_INIT;
private:
  static char     dummy;
  static char     first_char;
  static char     first_char_addr;
  static Address  addr;
  static Thread * tid;
  static Kobject *ko_tid;
  static Space *  task;

public:  
#line 309 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&args, char const *&fmt, int &next_char);
  
#line 415 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 429 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
  int
  num_cmds() const;

private:  
#line 40 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
  // determine the user level ebp and eip considering the current thread state
  static void
  get_user_eip_ebp(Address &eip, Address &ebp);
  
#line 111 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
  static Mword
  get_user_ebp_following_kernel_stack();
  
#line 162 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
  static void
  get_kernel_eip_ebp(Mword &eip1, Mword &eip2, Mword &ebp);
  
#line 217 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
  /** Show one backtrace item we found. Add symbol name and line info */
  static void
  show_item(int nr, Address ksp, Address addr, Address_type user);
  
#line 255 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
  static void
  show_without_ebp();
  
#line 269 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
  static void
  show(Mword ebp, Mword eip1, Mword eip2, Address_type user);
};
#line 146 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"

struct Is_current
{
  Thread *tid;
  mutable Thread *c;
  mutable Cpu_number cpu;

  void operator () (Cpu_number _cpu) const
  {
    Thread *t = Jdb::get_thread(_cpu);
    if (t == tid)
      { c = t; cpu = _cpu; }
  }

};

#endif // jdb_bt_i_h
