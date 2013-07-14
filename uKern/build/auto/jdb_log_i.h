// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_log_i_h
#define jdb_log_i_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"

#include <climits>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
#include <cstring>
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
#include <cstdio>
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"

#include "jdb.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
#include "jdb_core.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
#include "jdb_module.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
#include "jdb_kobject.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
#include "jdb_list.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
#include "jdb_screen.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
#include "kernel_console.h"
#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
#include "keycodes.h"
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
#include "mem_unit.h"
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
#include "ram_quota.h"
#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
#include "simpleio.h"
#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
#include "task.h"
#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
#include "static_init.h"
#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"


class Jdb_log_list : public Jdb_list
{
  friend class Jdb_log_list_hdl;
public:
  void *get_head() const { return _log_table; }
  char const *show_head() const { return "[Log]"; }

private:
  static Tb_log_table_entry *_end;

public:  
#line 118 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
  int
  show_item(char *buffer, int max, void *item) const;
  
#line 147 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
  bool
  enter_item(void *item) const;
  
#line 238 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
  int
  seek(int cnt, void **item);
  
#line 297 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
  static void
  move_dups();

private:  
#line 130 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
  static inline unsigned
  patch_val(Tb_log_table_entry const *e);
  
#line 135 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
  static Tb_log_table_entry *
  find_next_log(const char *name, const char *sc,
                              Tb_log_table_entry *i);
  
#line 156 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
  static void
  patch_item(Tb_log_table_entry const *e, unsigned char val);
  
#line 176 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
  static bool
  equal(Tb_log_table_entry const *a, Tb_log_table_entry const *b);
  
#line 192 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
  bool
  next(void **item);
  
#line 214 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
  bool
  pref(void **item);
};
#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"

class Jdb_log_list_hdl : public Jdb_kobject_handler
{
public:
  Jdb_log_list_hdl() : Jdb_kobject_handler(0) {}
  virtual bool show_kobject(Kobject_common *, int) { return true; }

public:  
#line 43 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
  bool
  invoke(Kobject_common *, Syscall_frame *f, Utcb *utcb);
};
#line 261 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"

class Jdb_log : public Jdb_module
{
public:
  Jdb_log() FIASCO_INIT;
private:

public:  
#line 343 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
  Jdb_module::Action_code
  action(int, void *&, char const *&, int &);
  
#line 357 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 368 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
  int
  num_cmds() const;
};

//
// IMPLEMENTATION of inline functions follows
//


#line 128 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"


inline unsigned
Jdb_log_list::patch_val(Tb_log_table_entry const *e)
{ return (e - _log_table) + Tbuf_dynentries; }

#endif // jdb_log_i_h
