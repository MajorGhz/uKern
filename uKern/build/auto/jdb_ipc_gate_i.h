// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_ipc_gate_i_h
#define jdb_ipc_gate_i_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ipc_gate.cpp"

#include <climits>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ipc_gate.cpp"
#include <cstring>
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ipc_gate.cpp"
#include <cstdio>
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ipc_gate.cpp"

#include "jdb.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ipc_gate.cpp"
#include "jdb_core.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ipc_gate.cpp"
#include "jdb_module.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ipc_gate.cpp"
#include "jdb_screen.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ipc_gate.cpp"
#include "jdb_kobject.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ipc_gate.cpp"
#include "simpleio.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ipc_gate.cpp"
#include "static_init.h"
#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ipc_gate.cpp"
#include "ipc_gate.h"
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ipc_gate.cpp"

class Jdb_ipc_gate : public Jdb_kobject_handler
{
public:
  Jdb_ipc_gate() FIASCO_INIT;

public:  
#line 30 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ipc_gate.cpp"
  Kobject_common *
  follow_link(Kobject_common *o);
  
#line 38 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ipc_gate.cpp"
  bool
  show_kobject(Kobject_common *, int);
  
#line 43 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ipc_gate.cpp"
  int
  show_kobject_short(char *buf, int max, Kobject_common *o);
  
#line 56 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ipc_gate.cpp"
  char const *
  kobject_type() const;
};

#endif // jdb_ipc_gate_i_h
