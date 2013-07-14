// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_trace_set_i_h
#define jdb_trace_set_i_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace_set.cpp"

#include <cstdio>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace_set.cpp"

#include "config.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace_set.cpp"
#include "cpu.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace_set.cpp"
#include "jdb_module.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace_set.cpp"
#include "jdb_tbuf.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace_set.cpp"
#include "jdb_trace.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace_set.cpp"
#include "keycodes.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace_set.cpp"
#include "simpleio.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace_set.cpp"
#include "static_init.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"
#include "syscalls.h"
#line 3 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"
#include "idt.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"
#include "jdb.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace_set.cpp"

class Jdb_set_trace : public Jdb_module
{
public:
  enum Mode { Off, Log, Log_to_buf, Trace, Use_c_short_cut, Use_slow_path };
  
  Jdb_set_trace() FIASCO_INIT;
  void ipc_tracing(Mode mode);
  void next_preiod_tracing(bool enable);
  void page_fault_tracing(bool enable);
  void unmap_tracing(bool enable);
  
private:
  static char first_char;
  static char second_char;

public:  
#line 44 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace_set.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&args, char const *&fmt, int &);
  
#line 331 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace_set.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 361 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace_set.cpp"
  int
  num_cmds() const;
  
#line 21 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"
  static void
  ia32_set_fast_entry(Cpu_number cpu, void *entry);
  
#line 66 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"
  static FIASCO_NOINLINE
  void
  set_cpath();

private:  
#line 36 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"
  static void
  set_ipc_vector();
  
#line 145 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"
  static void
  set_unmap_vector();
};
#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"

typedef void (Fast_entry_func)(void);
#line 26 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"

struct Set_fast_entry
{
  void *entry;
  Set_fast_entry(Fast_entry_func *entry) : entry((void*)entry) {}
  void operator () (Cpu_number cpu) const
  { Jdb::remote_work(cpu, Jdb_set_trace::ia32_set_fast_entry, entry, true); }
};

#endif // jdb_trace_set_i_h
