// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_kobject_names_i_h
#define jdb_kobject_names_i_h
#line 30 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"

#include <cstdio>
#line 32 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"

#include <feature.h>
#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
#include "context.h"
#line 35 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
#include "kmem_alloc.h"
#line 36 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
#include "minmax.h"
#line 37 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
#include "panic.h"
#line 38 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
#include "space.h"
#line 39 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
#include "thread.h"
#line 40 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
#include "static_init.h"
#line 124 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"

class Jdb_name_hdl : public Jdb_kobject_handler
{
public:
  Jdb_name_hdl() : Jdb_kobject_handler(0) {}
  virtual bool show_kobject(Kobject_common *, int) { return true; }
  virtual ~Jdb_name_hdl() {}

public:  
#line 134 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
  int
  show_kobject_short(char *buf, int max, Kobject_common *o);
  
#line 147 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
  bool
  invoke(Kobject_common *o, Syscall_frame *f, Utcb *utcb);
};

#endif // jdb_kobject_names_i_h
