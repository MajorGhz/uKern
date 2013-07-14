// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_trace_h
#define jdb_trace_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"

#include "l4_types.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"

class Syscall_frame;
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
typedef struct
{
  Address lo, hi;
} Addr_range;
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"

class Jdb_ipc_trace
{
private:
  static int         _other_thread;
  static Mword       _gthread;
  static int         _other_task;
  static Mword       _task;
  static int         _snd_only;
  static int         _log;
  static int         _log_to_buf;
  static int         _log_result;
  static int         _trace;
  static int         _slow_ipc;
  static int         _cpath;
  static int         _cshortcut;
  friend class Jdb_set_trace;

public:  
#line 96 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static inline int log();
  
#line 97 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static inline int log_buf();
  
#line 98 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static inline int log_result();
  
#line 101 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static inline int
  check_restriction(Mword id,
  				  Mword task,
  				  Syscall_frame *ipc_regs,
  				  Mword dst_task);
  
#line 118 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static void 
  clear_restriction();
  
#line 129 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static void
  show();
};
#line 28 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"

class Jdb_pf_trace
{
private:
  static int         _other_thread;
  static Mword       _gthread;
  static Addr_range  _addr;
  static int         _log;
  static int         _log_to_buf;
  friend class Jdb_set_trace;

public:  
#line 164 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static inline int log();
  
#line 165 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static inline int log_buf();
  
#line 168 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static inline int
  check_restriction(Mword id, Address pfa);
  
#line 179 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static void
  show();
  
#line 217 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static void 
  clear_restriction();
};
#line 39 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"

class Jdb_unmap_trace
{
private:
  static int         _other_thread;
  static Mword       _gthread;
  static Addr_range  _addr;
  static int         _log;
  static int         _log_to_buf;
  friend class Jdb_set_trace;

public:  
#line 226 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static inline int log();
  
#line 227 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static inline int log_buf();
  
#line 230 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static inline int
  check_restriction(Mword id, Address addr);
  
#line 242 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static void
  show();
  
#line 275 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static void 
  clear_restriction();
};
#line 50 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"

class Jdb_nextper_trace
{
private:
  static int         _log;
  friend class Jdb_set_trace;

public:  
#line 284 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static inline int log();
  
#line 287 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static void
  show();
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 60 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"

#include <cstdio>
#line 64 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
#include "entry_frame.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 95 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"

inline int Jdb_ipc_trace::log()        { return _log; }

#line 97 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
inline int Jdb_ipc_trace::log_buf()    { return _log_to_buf; }

#line 98 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
inline int Jdb_ipc_trace::log_result() { return _log_result; }

#line 99 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"


inline int
Jdb_ipc_trace::check_restriction(Mword id,
				  Mword task,
				  Syscall_frame *ipc_regs,
				  Mword dst_task)
{
  return (   ((_gthread == 0)
	      || ((_other_thread) ^ (_gthread == id))
	      )
	   && ((!_snd_only || ipc_regs->ref().valid()))
	   && ((_task == 0)
	      || ((_other_task)   
		  ^ ((_task == task) || (_task == dst_task))))
	  );
}

#line 163 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"

inline int Jdb_pf_trace::log()     { return _log; }

#line 165 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
inline int Jdb_pf_trace::log_buf() { return _log_to_buf; }

#line 166 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"


inline int
Jdb_pf_trace::check_restriction(Mword id, Address pfa)
{
  return (   (((_gthread == 0)
	      || ((_other_thread) ^ (_gthread == id))))
	  && (!(_addr.lo | _addr.hi)
	      || (_addr.lo <= _addr.hi && pfa >= _addr.lo && pfa <= _addr.hi)
	      || (_addr.lo >  _addr.hi && pfa <  _addr.hi && pfa >  _addr.lo)));
}

#line 225 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"

inline int Jdb_unmap_trace::log() { return _log; }

#line 227 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
inline int Jdb_unmap_trace::log_buf() { return _log_to_buf; }

#line 228 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"


inline int
Jdb_unmap_trace::check_restriction(Mword id, Address addr)
{
  return (   (((_gthread == 0)
	      || ((_other_thread) ^ (_gthread == id))))
	  && (!(_addr.lo | _addr.hi)
	      || (_addr.lo <= _addr.hi && addr >= _addr.lo && addr <= _addr.hi)
	      || (_addr.lo >  _addr.hi && addr <  _addr.hi && addr >  _addr.lo)
	      ));
}

#line 283 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_trace.cpp"

inline int Jdb_nextper_trace::log() { return _log; }

#endif // jdb_trace_h
