// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_utcb_i_h
#define jdb_utcb_i_h
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"

#include <cassert>
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
#include <cstdio>
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
#include "l4_types.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
#include "config.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
#include "jdb.h"
#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
#include "jdb_kobject.h"
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
#include "jdb_module.h"
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
#include "space.h"
#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
#include "static_init.h"
#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
#include "thread_object.h"
#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
#include "thread_state.h"
#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"

class Jdb_utcb : public Jdb_module
{
public:
  Jdb_utcb() FIASCO_INIT;
private:
  static Kobject *thread;

public:  
#line 40 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
  static void
  print(Thread *t);
  
#line 62 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
  virtual Jdb_module::Action_code
  action( int cmd, void *&, char const *&, int &);
  
#line 81 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
  int
  num_cmds() const;
  
#line 86 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
  Jdb_module::Cmd
  const * cmds() const;
};
#line 95 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"

// --------------------------------------------------------------------------
// Handler for kobject list

class Jdb_kobject_utcb_hdl : public Jdb_kobject_handler
{
public:
  Jdb_kobject_utcb_hdl() : Jdb_kobject_handler(0) {}
  virtual bool show_kobject(Kobject_common *, int) { return true; }
  virtual ~Jdb_kobject_utcb_hdl() {}

public:  
#line 107 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
  static FIASCO_INIT
  void
  init();
  
#line 116 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
  bool
  handle_key(Kobject_common *o, int keycode);
};

#endif // jdb_utcb_i_h
