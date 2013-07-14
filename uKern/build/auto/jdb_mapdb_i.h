// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_mapdb_i_h
#define jdb_mapdb_i_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"

#include <cstdio>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"

#include "jdb.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
#include "jdb_input.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
#include "jdb_screen.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
#include "kernel_console.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
#include "kobject.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
#include "keycodes.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
#include "mapdb.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
#include "mapdb_i.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
#include "map_util.h"
#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
#include "simpleio.h"
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
#include "static_init.h"
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
#include "task.h"
#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
#include "jdb_kobject.h"
#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
#include "jdb_kobject_names.h"
#line 470 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"

#include "dbg_page_info.h"
#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"

class Jdb_mapdb : public Jdb_module
{
  friend class Jdb_kobject_mapdb_hdl;
public:
  Jdb_mapdb() FIASCO_INIT;
private:
  static Mword pagenum;
  static char  subcmd;

public:  
#line 298 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&args, char const *&fmt, int &next_char);
  
#line 357 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 372 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
  int
  num_cmds() const;

private:  
#line 49 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
  static unsigned long long
  val(Mdb_types::Pfn p, Mdb_types::Order base_size);
  
#line 57 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
  static bool
  show_tree(Treemap* pages, Mapping::Pcnt offset, Mdb_types::Order base_size,
  		     unsigned &screenline, unsigned indent = 1);
  
#line 180 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
  static Address
  end_address(Mapdb* mapdb);
  
#line 187 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
  static void
  show(Mapping::Pfn page, char which_mapdb);
  
#line 474 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
  static bool
  show_simple_tree(Kobject_common *f, unsigned indent = 1);
  
#line 541 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
  static void
  dump_all_cap_trees();
};
#line 384 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"

// --------------------------------------------------------------------------
// Handler for kobject list

class Jdb_kobject_mapdb_hdl : public Jdb_kobject_handler
{
public:
  Jdb_kobject_mapdb_hdl() : Jdb_kobject_handler(0) {}
  virtual bool show_kobject(Kobject_common *, int) { return true; }
  virtual ~Jdb_kobject_mapdb_hdl() {}

public:  
#line 396 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
  static FIASCO_INIT
  void
  init();
  
#line 405 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
  bool
  handle_key(Kobject_common *o, int keycode);
};

#endif // jdb_mapdb_i_h
