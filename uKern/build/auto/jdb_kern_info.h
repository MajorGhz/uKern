// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_kern_info_h
#define jdb_kern_info_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info.cpp"

#include "jdb_module.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info.cpp"
#include <cxx/slist>
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info-bench.cpp"

#include "jdb.h"

//
// INTERFACE definition follows 
//

#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info.cpp"

class Jdb_kern_info_module;
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info.cpp"

/**
 * 'kern info' module.
 *
 * This module handles the 'k' command, which
 * prints out various kernel information.
 */
class Jdb_kern_info : public Jdb_module
{
public:
  Jdb_kern_info() FIASCO_INIT;
private:
  typedef cxx::S_list_bss<Jdb_kern_info_module> Module_list;
  typedef Module_list::Iterator Module_iter;
  static char                 _subcmd;
  static Module_list modules;

public:  
#line 67 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info.cpp"
  static void
  register_subcmd(Jdb_kern_info_module *m);
  
#line 83 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&args, char const *&, int &);
  
#line 112 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info.cpp"
  int
  num_cmds() const;
  
#line 119 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info.cpp"
  Jdb_module::Cmd const *
  cmds() const;
};
#line 24 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info.cpp"


class Jdb_kern_info_module : public cxx::S_list_item
{
  friend class Jdb_kern_info;
public:
  Jdb_kern_info_module(char subcmd, char const *descr) FIASCO_INIT;
private:
  virtual void show(void) = 0;
  char                 _subcmd;
  char const           *_descr;
};
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info-bench.cpp"

class Jdb_kern_info_bench : public Jdb_kern_info_module
{
private:
  static Unsigned64 get_time_now();
  static void show_arch();

public:  
#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info-bench.cpp"
  Jdb_kern_info_bench();
  
#line 25 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info-bench.cpp"
  void
  show();

private:  
#line 36 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info-bench.cpp"
  void
  do_mp_benchmark();
  
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/32/jdb_kern_info-bench-ia32-32.cpp"
  static void
  show_time(Unsigned64 time, Unsigned32 rounds,
  			       const char *descr);
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/32/jdb_kern_info-bench-ia32-32.cpp"


inline Unsigned64
Jdb_kern_info_bench::get_time_now()
{ return Cpu::rdtsc(); }

#endif // jdb_kern_info_h
