// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_sender_list_i_h
#define jdb_sender_list_i_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"

#include <cstdio>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"
#include <cstring>
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"

#include "thread_object.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"
#include "jdb.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"
#include "jdb_kobject.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"
#include "jdb_module.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"
#include "ipc_gate.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"


class Jdb_sender_list : public Jdb_module, public Jdb_kobject_handler
{
public:
  Jdb_sender_list() FIASCO_INIT;

  virtual bool show_kobject(Kobject_common *, int) { return true; }
private:
  static Kobject *object;

public:  
#line 64 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&, char const *&, int &);
  
#line 88 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"
  bool
  handle_key(Kobject_common *o, int keycode);
  
#line 106 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"
  int num_cmds() const;
  
#line 110 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"
  Jdb_module::Cmd const * cmds() const;

private:  
#line 29 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"
  void
  show_sender_list(Prio_list *t, int printlines);
};

#endif // jdb_sender_list_i_h
