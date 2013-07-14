// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_trace.h"
#include "jdb_trace_i.h"

#line 68 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"

int         Jdb_ipc_trace::_other_thread;
#line 70 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
Mword       Jdb_ipc_trace::_gthread;
#line 71 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
int         Jdb_ipc_trace::_other_task;
#line 72 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
Mword       Jdb_ipc_trace::_task;
#line 73 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
int         Jdb_ipc_trace::_snd_only;
#line 74 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
int         Jdb_ipc_trace::_log;
#line 75 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
int         Jdb_ipc_trace::_log_to_buf;
#line 76 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
int         Jdb_ipc_trace::_log_result;
#line 77 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
int         Jdb_ipc_trace::_trace;
#line 78 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
int         Jdb_ipc_trace::_slow_ipc;
#line 79 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
int         Jdb_ipc_trace::_cpath;
#line 80 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
int         Jdb_ipc_trace::_cshortcut;
#line 81 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"

int         Jdb_pf_trace::_other_thread;
#line 83 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
Mword       Jdb_pf_trace::_gthread;
#line 84 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
Addr_range  Jdb_pf_trace::_addr;
#line 85 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
int         Jdb_pf_trace::_log;
#line 86 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
int         Jdb_pf_trace::_log_to_buf;
#line 87 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"

int         Jdb_unmap_trace::_other_thread;
#line 89 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
Mword       Jdb_unmap_trace::_gthread;
#line 90 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
Addr_range  Jdb_unmap_trace::_addr;
#line 91 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
int         Jdb_unmap_trace::_log;
#line 92 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
int         Jdb_unmap_trace::_log_to_buf;
#line 93 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"

int         Jdb_nextper_trace::_log;

#line 116 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"


void 
Jdb_ipc_trace::clear_restriction()
{
  _other_thread = 0;
  _gthread      = 0;
  _other_task   = 0;
  _task         = 0;
  _snd_only    = 0;
}

#line 127 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"


void
Jdb_ipc_trace::show()
{
  if (_trace)
    putstr("IPC tracing to tracebuffer enabled");
  else if (_log)
    {
      printf("IPC logging%s%s enabled%s",
	  _log_result ? " incl. results" : "",
	  _log_to_buf ? " to tracebuffer" : "",
          _log_to_buf ? "" : " (exit with 'i', proceed with other key)");
      if (_gthread != 0)
	{
	  printf("\n    restricted to thread%s %lx%s",
		 _other_thread ? "s !=" : "",
		 _gthread,
		 _snd_only ? ", snd-only" : "");
	}
      if (_task != 0)
	{
	  printf("\n    restricted to task%s %lx",
	      _other_task ? "s !=" : "", _task);
	}
    }
  else
    {
      printf("IPC logging disabled -- using the IPC %s path",
	  _slow_ipc
	    ? "slow" 
	    : "C fast");
    }

  putchar('\n');
}

#line 177 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"


void
Jdb_pf_trace::show()
{
  if (_log)
    {
      int res_enabled = 0;
      BEGIN_LOG_EVENT("Page fault results", "pfr", Tb_entry_pf)
      res_enabled = 1;
      END_LOG_EVENT;
      printf("PF logging%s%s enabled",
	     res_enabled ? " incl. results" : "",
	     _log_to_buf ? " to tracebuffer" : "");
      if (_gthread != 0)
	{
    	  printf(", restricted to thread%s %lx",
		 _other_thread ? "s !=" : "",
		 _gthread);
	}
      if (_addr.lo || _addr.hi)
	{
     	  if (_gthread != 0)
	    putstr(" and ");
	  else
    	    putstr(", restricted to ");
	  if (_addr.lo <= _addr.hi)
	    printf(L4_PTR_FMT " <= pfa <= " L4_PTR_FMT
		   , _addr.lo, _addr.hi);
	  else
    	    printf("pfa < " L4_PTR_FMT " || pfa > " L4_PTR_FMT,
		   _addr.hi, _addr.lo);
	}
    }
  else
    putstr("PF logging disabled");
  putchar('\n');
}

#line 215 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"


void 
Jdb_pf_trace::clear_restriction()
{
  _other_thread = 0;
  _gthread      = 0;
  _addr.lo      = 0;
  _addr.hi      = 0;
}

#line 240 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"


void
Jdb_unmap_trace::show()
{
  if (_log)
    {
      printf("UNMAP logging%s enabled",
	      _log_to_buf ? " to tracebuffer" : "");
      if (_gthread != 0)
	{
    	  printf(", restricted to thread%s %lx",
		 _other_thread ? "s !=" : "",
		 _gthread);
	}
      if (_addr.lo | _addr.hi)
	{
     	  if (_gthread != 0)
	    putstr(" and ");
	  else
    	    putstr(", restricted to ");
	  if (_addr.lo <= _addr.hi)
	    printf(L4_PTR_FMT " <= addr <= " L4_PTR_FMT,
		   _addr.lo, _addr.hi);
	  else
    	    printf("addr < " L4_PTR_FMT " || addr > " L4_PTR_FMT
		   , _addr.hi, _addr.lo);
	}
    }
  else
    putstr("UNMAP logging disabled");
  putchar('\n');
}

#line 273 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"


void 
Jdb_unmap_trace::clear_restriction()
{
  _other_thread = 0;
  _gthread      = 0;
  _addr.lo      = 0;
  _addr.hi      = 0;
}

#line 285 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"


void
Jdb_nextper_trace::show()
{
  if (_log)
    puts("Next period logging to tracebuffer enabled");
  else
    puts("Next period logging to tracebuffer disabled");
}
