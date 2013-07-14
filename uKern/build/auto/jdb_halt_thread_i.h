// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_halt_thread_i_h
#define jdb_halt_thread_i_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_halt_thread.cpp"

#include <cstdio>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_halt_thread.cpp"
#include "entry_frame.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_halt_thread.cpp"
#include "gdt.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_halt_thread.cpp"
#include "jdb_module.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_halt_thread.cpp"
#include "jdb_kobject.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_halt_thread.cpp"
#include "static_init.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_halt_thread.cpp"
#include "thread_object.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_halt_thread.cpp"

class Jdb_halt_thread : public Jdb_module
{
public:
  Jdb_halt_thread() FIASCO_INIT;
private:
  static Kobject *threadid;

public:  
#line 22 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_halt_thread.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&, char const *&, int &);
  
#line 42 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_halt_thread.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 55 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_halt_thread.cpp"
  int
  num_cmds() const;
};

#endif // jdb_halt_thread_i_h
