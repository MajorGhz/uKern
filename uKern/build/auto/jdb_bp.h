// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_bp_h
#define jdb_bp_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"

#include "initcalls.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
#include "l4_types.h"

//
// INTERFACE definition follows 
//

#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"

class Thread;
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
class Task;
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
class Space;
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"

class Breakpoint
{
public:
  enum Mode { INSTRUCTION=0, WRITE=1, PORTIO=2, ACCESS=3 };
  enum Log  { BREAK=0, LOG=1 };

private:
  typedef struct 
    {
      int other;
      Mword thread; 
    } Bp_thread_res;

  typedef struct
    {
      int other;
      Mword task;
    } Bp_task_res;

  typedef struct 
    {
      char reg;
      Address y, z;
    } Bp_reg_res;

  typedef struct 
    {
      unsigned char len;
      Address addr;
      Address y, z;
    } Bp_mem_res;
  
  typedef struct 
    {
      Bp_thread_res thread;
      Bp_task_res   task;
      Bp_reg_res    reg;
      Bp_mem_res    mem;
    } Restriction;

  Address      addr;
  Unsigned8    len;
  Address_type user;
  Mode         mode;
  Log          log;
  Restriction  restrict;
  static char const * const mode_names[4];

public:  
#line 133 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  Breakpoint();
  
#line 140 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  inline void
  kill();
  
#line 147 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  inline int
  unused();
  
#line 154 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  inline int
  break_at_instruction();
  
#line 161 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  inline int
  match_addr(Address virt, Mode m);
  
#line 168 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  inline void
  set_logmode(char m);
  
#line 175 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  inline int
  is_break();
  
#line 182 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  inline void
  restrict_task(int other, Mword task);
  
#line 190 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  inline void
  restrict_thread(int other, Mword thread);
  
#line 198 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  inline void
  restrict_register(char reg, Mword y, Mword z);
  
#line 207 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  inline void
  restrict_memory(Mword addr, Mword len, Mword y, Mword z);
  
#line 217 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  inline void 
  clear_restriction();
  
#line 227 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  void
  show();
  
#line 291 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  // return TRUE  if the breakpoint does NOT match
  // return FALSE if all restrictions do match
  
  int
  restricted(Thread *t);
  
#line 348 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  int
  test_break(Thread *t, char *errbuf, size_t bufsize);
  
#line 380 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  // Create log entry if breakpoint matches
  
  void
  test_log(Thread *t);
  
#line 26 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"
  inline void
  set(Address _addr, Mword _len, Mode _mode, Log _log);
};
#line 58 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"

class Jdb_bp 
{
public:
  static int		global_breakpoints();
  static void		init_arch();

private:
  static void		at_jdb_enter();
  static void		at_jdb_leave();
  static Breakpoint	bps[4];

#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"
private:

private:
  static int		test_sstep();
  static int		test_break(char *errbuf, size_t bufsize);
  static int		test_other(char *errbuf, size_t bufsize);
  static int		test_log_only();
  static Mword		dr7;

#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/32/jdb_bp-ia32.cpp"
private:

  enum
  {
    Val_enter      = 0x0000ff00,
    Val_leave      = 0x00000000,
    Val_test_sstep = 0x00004000,
    Val_test       = 0x0000000f,
    Val_test_other = 0x0000e00f,
  };

public:  
#line 417 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static FIASCO_INIT
  void
  init();
  
#line 450 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static int
  set_breakpoint(int num, Address addr, Mword len,
  		       Breakpoint::Mode mode, Breakpoint::Log log,
  		       Task *task);
  
#line 465 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static void 
  clr_breakpoint(int num);
  
#line 473 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static inline void
  logmode_breakpoint(int num, char mode);
  
#line 480 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static int
  first_unused();
  
#line 491 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  // Return 1 if a breakpoint hits
  
  static int
  test_break(Mword dr6, char *errbuf, size_t bufsize);
  
#line 511 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  // Create log entry if breakpoint matches.
  // Return 1 if debugger should stop
  
  static void
  test_log(Mword &dr6);
  
#line 537 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static Mword
  test_match(Address addr, Breakpoint::Mode mode);
  
#line 548 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static int
  instruction_bp_at_addr(Address addr);
  
#line 554 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static inline void
  restrict_task(int num, int other, Mword task);
  
#line 561 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static inline void
  restrict_thread(int num, int other, Mword thread);
  
#line 568 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static inline void
  restrict_register(int num, char reg, Mword y, Mword z);
  
#line 575 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static inline void
  restrict_memory(int num, Mword addr, Mword len, Mword y, Mword z);
  
#line 582 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static inline void
  clear_restriction(int num);
  
#line 589 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static void 
  list();
  
#line 37 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"
  static inline Mword
  get_dr(Mword i);

private:  
#line 431 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static inline void
  clr_dr7(int num, Mword &dr7);
  
#line 438 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static inline void
  set_dr7(int num, Mword len, Breakpoint::Mode mode, Mword &dr7);
  
#line 60 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"
  static int
  set_debug_address_register(int num, Mword addr, Mword len,
  				   Breakpoint::Mode mode, Space *);
  
#line 78 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"
  static void
  clr_debug_address_register(int num);
};
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"

#define write_debug_register(num, val) \
    asm volatile("mov %0, %%db" #num : : "r" ((Mword)val))
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"

#define read_debug_register(num) \
    ({Mword val; asm volatile("mov %%db" #num ",%0" : "=r"(val)); val;})

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"

#include "kmem.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 180 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


inline void
Breakpoint::restrict_task(int other, Mword task)
{
  restrict.task.other = other;
  restrict.task.task  = task;
}

#line 24 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"


inline void
Breakpoint::set(Address _addr, Mword _len, Mode _mode, Log _log)
{
  addr = _addr;
  mode = _mode;
  user = Kmem::is_kmem_page_fault(_addr, 0) ? ADDR_KERNEL : ADDR_USER;
  log  = _log;
  len  = _len;
}

#line 35 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"


inline Mword
Jdb_bp::get_dr(Mword i)
{
  switch (i)
    {
    case 0: return read_debug_register(0);
    case 1: return read_debug_register(1);
    case 2: return read_debug_register(2);
    case 3: return read_debug_register(3);
    case 6: return read_debug_register(6);
    case 7: return dr7;
    default: return 0;
    }
}

#endif // jdb_bp_h
