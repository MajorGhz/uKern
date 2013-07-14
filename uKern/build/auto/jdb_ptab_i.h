// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_ptab_i_h
#define jdb_ptab_i_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"

#include <cstdio>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"

#include "config.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"
#include "jdb.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"
#include "jdb_kobject.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"
#include "jdb_module.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"
#include "jdb_screen.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"
#include "jdb_table.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"
#include "kernel_console.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"
#include "kmem.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"
#include "keycodes.h"
#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"
#include "space.h"
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"
#include "task.h"
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"
#include "thread_object.h"
#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"
#include "static_init.h"
#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"
#include "types.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab-ia32-ux-arm.cpp"

#include "paging.h"
#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"

class Jdb_ptab_m : public Jdb_module, public Jdb_kobject_handler
{
public:
  Jdb_ptab_m() FIASCO_INIT;
private:
  Address task;
  static char first_char;
  bool show_kobject(Kobject_common *, int) { return false; }

public:  
#line 159 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"
  bool
  handle_key(Kobject_common *o, int code);
  
#line 271 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&args, char const *&fmt, int &next_char);
  
#line 327 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 340 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"
  int
  num_cmds() const;
};
#line 29 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"

class Jdb_ptab : public Jdb_table
{
private:
  Address base;
  Address virt_base;
  int _level;
  Space *_task;
  unsigned entries;
  unsigned char cur_pt_level;
  char dump_raw;

  static unsigned entry_is_pt_ptr(Pdir::Pte_ptr const &entry,
                                  unsigned *entries, unsigned *next_level);
  static Address entry_phys(Pdir::Pte_ptr const &entry);

  void print_entry(Pdir::Pte_ptr const &);
  void print_head(void *entry);

public:  
#line 52 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"
  // arch-dependent type
  
  
  Jdb_ptab(void *pt_base = 0, Space *task = 0,
                     unsigned char pt_level = 0, unsigned entries = 0,
                     Address virt_base = 0, int level = 0);
  
#line 66 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"
  unsigned
  col_width(unsigned column) const;
  
#line 76 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"
  unsigned long
  cols() const;
  
#line 89 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"
  void
  draw_entry(unsigned long row, unsigned long col);
  
#line 182 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"
  unsigned 
  key_pressed(int c, unsigned long &row, unsigned long &col);
  
#line 245 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"
  unsigned long
  rows() const;
  
#line 254 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"
  void
  print_statline(unsigned long row, unsigned long col);

private:  
#line 119 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"
  inline int
  index(unsigned row, unsigned col);
  
#line 131 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"
  inline void *
  pte(int index);
  
#line 237 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"
  Address
  disp_virt(int idx);
};
#line 50 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"

typedef Mword My_pte;			// shoud be replaced by

//
// IMPLEMENTATION of inline functions follows
//


#line 116 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"



inline int
Jdb_ptab::index(unsigned row, unsigned col)
{
  Mword e = (col-1) + (row * (cols()-1));
  if (e < Pdir::Levels::length(cur_pt_level))
    return e;
  else
    return -1;
}

#line 128 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"



inline void *
Jdb_ptab::pte(int index)
{
  return (void*)(base + index * Pdir::Levels::entry_size(cur_pt_level));
}

#endif // jdb_ptab_i_h
