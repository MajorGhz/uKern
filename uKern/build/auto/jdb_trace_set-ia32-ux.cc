// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_trace_set.h"
#include "jdb_trace_set_i.h"

#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"

extern "C" void entry_sys_ipc_log (void);
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"
extern "C" void entry_sys_ipc_c (void);
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"
extern "C" void entry_sys_ipc (void);
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"
extern "C" void entry_sys_fast_ipc_log (void);
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"
extern "C" void entry_sys_fast_ipc_c (void);
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"
extern "C" void entry_sys_fast_ipc (void);
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"

extern "C" void sys_ipc_wrapper (void);
#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"
extern "C" void ipc_short_cut_wrapper (void);
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"
extern "C" void sys_ipc_log_wrapper (void);
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"
extern "C" void sys_ipc_trace_wrapper (void);

#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"


void
Jdb_set_trace::ia32_set_fast_entry(Cpu_number cpu, void *entry)
{
  Cpu::cpus.cpu(cpu).set_fast_entry((Fast_entry_func*)entry);
}

#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"


void
Jdb_set_trace::set_ipc_vector()
{
  void (*int30_entry)(void);
  void (*fast_entry)(void);

  if (Jdb_ipc_trace::_trace || Jdb_ipc_trace::_slow_ipc || 
      Jdb_ipc_trace::_log   || Jdb_nextper_trace::_log)
    {
      int30_entry = entry_sys_ipc_log;
      fast_entry  = entry_sys_fast_ipc_log;
    }
  else
    {
      int30_entry = entry_sys_ipc_c;
      fast_entry  = entry_sys_fast_ipc_c;
    }

  Idt::set_entry(0x30, (Address) int30_entry, true);
  Jdb::foreach_cpu(Set_fast_entry(fast_entry));

  if (Jdb_ipc_trace::_trace)
    syscall_table[0] = sys_ipc_trace_wrapper;
  else if ((Jdb_ipc_trace::_log && !Jdb_ipc_trace::_slow_ipc) ||
	   Jdb_nextper_trace::_log)            
    syscall_table[0] = sys_ipc_log_wrapper;
  else
    syscall_table[0] = sys_ipc_wrapper;
}

#line 65 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"

FIASCO_NOINLINE
void
Jdb_set_trace::set_cpath()
{
  Jdb_ipc_trace::_cpath = 0;
  BEGIN_LOG_EVENT("Context switches", "csw", Tb_entry_empty)
  Jdb_ipc_trace::_cpath = 1;
  END_LOG_EVENT;
  BEGIN_LOG_EVENT("Shortcut", "sc", Tb_entry_empty)
  Jdb_ipc_trace::_cpath = 1;
  END_LOG_EVENT;
  set_ipc_vector();
}

#line 79 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"

void
jdb_trace_set_cpath(void)
{
  Jdb_set_trace::set_cpath();
}

#line 85 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"

void
Jdb_set_trace::next_preiod_tracing(bool enable)
{
  if (enable)
    Jdb_nextper_trace::_log = 1;
  else
    Jdb_nextper_trace::_log = 0;

  set_ipc_vector();
}

#line 96 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"

void
Jdb_set_trace::page_fault_tracing(bool /*enable*/)
{
}

#line 101 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"

void
Jdb_set_trace::ipc_tracing(Mode mode)
{
  switch (mode)
    {
    case Off:
      Jdb_ipc_trace::_trace = 0;
      Jdb_ipc_trace::_log = 0;
      Jdb_ipc_trace::_cshortcut = 0;
      Jdb_ipc_trace::_slow_ipc = 0;
      break;
    case Log:
      Jdb_ipc_trace::_trace = 0;
      Jdb_ipc_trace::_log = 1;
      Jdb_ipc_trace::_log_to_buf = 0;
      Jdb_ipc_trace::_cshortcut = 0;
      Jdb_ipc_trace::_slow_ipc = 0;
      break;
    case Log_to_buf:
      Jdb_ipc_trace::_trace = 0;
      Jdb_ipc_trace::_log = 1;
      Jdb_ipc_trace::_log_to_buf = 1;
      Jdb_ipc_trace::_cshortcut = 0;
      Jdb_ipc_trace::_slow_ipc = 0;
      break;
    case Trace:
      Jdb_ipc_trace::_trace = 1;
      Jdb_ipc_trace::_cshortcut = 0;
      Jdb_ipc_trace::_log = 0;
      Jdb_ipc_trace::_slow_ipc = 0;
      break;
    case Use_c_short_cut:
      Jdb_ipc_trace::_cshortcut = 1;
      break;
    case Use_slow_path:
      Jdb_ipc_trace::_slow_ipc = 1;
      break;
    }
  set_ipc_vector();
}

#line 142 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"



void
Jdb_set_trace::set_unmap_vector()
{
}

#line 149 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"

void
Jdb_set_trace::unmap_tracing(bool /*enable*/)
{
}
