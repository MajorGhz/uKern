// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_obj_space_i_h
#define jdb_obj_space_i_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"

#include <cstdio>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"

#include "config.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
#include "jdb.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
#include "jdb_screen.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
#include "jdb_table.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
#include "jdb_kobject.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
#include "kernel_console.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
#include "kmem.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
#include "keycodes.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
#include "space.h"
#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
#include "task.h"
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
#include "thread_object.h"
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
#include "static_init.h"
#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
#include "types.h"
#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"


class Jdb_obj_space : public Jdb_table, public Jdb_kobject_handler
{
public:
  enum Mode
  {
    Name,
    Raw,
    End_mode
  };

private:
  Address _base;
  Space  *_task;
  Mode    _mode;

  bool show_kobject(Kobject_common *, int) { return false; }


public:  
#line 53 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
  //char Jdb_obj_space_m::first_char;
  
  
  Jdb_obj_space(Address base = 0, int level = 0);
  
#line 67 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
  unsigned
  col_width(unsigned column) const;
  
#line 77 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
  unsigned long
  cols() const;
  
#line 84 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
  unsigned long
  rows() const;
  
#line 89 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
  void
  print_statline(unsigned long row, unsigned long col);
  
#line 109 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
  void
  print_entry(Cap_index entry);
  
#line 140 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
  void
  draw_entry(unsigned long row, unsigned long col);
  
#line 177 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
  unsigned
  key_pressed(int c, unsigned long &row, unsigned long &col);
  
#line 200 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
  bool
  handle_key(Kobject_common *o, int code);
  
#line 225 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
  Kobject_iface *
  item(Cap_index entry, unsigned *rights);

private:  
#line 150 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
  Cap_index
  index(unsigned long row, unsigned long col);
  
#line 158 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
  bool
  handle_user_keys(int c, Kobject_iface *o);
};

#endif // jdb_obj_space_i_h
