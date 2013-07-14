// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_tcb_i_h
#define jdb_tcb_i_h
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"

#include <cstdio>
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
#include <cstring>
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"

#include "entry_frame.h"
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
#include "jdb.h"
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
#include "jdb_disasm.h"
#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
#include "jdb_handler_queue.h"
#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
#include "jdb_input.h"
#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
#include "jdb_kobject.h"
#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
#include "jdb_kobject_names.h"
#line 21 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
#include "jdb_module.h"
#line 22 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
#include "jdb_screen.h"
#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
#include "jdb_thread.h"
#line 24 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
#include "jdb_util.h"
#line 25 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
#include "kernel_console.h"
#line 26 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
#include "kernel_task.h"
#line 27 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
#include "keycodes.h"
#line 28 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
#include "l4_types.h"
#line 29 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
#include "push_console.h"
#line 30 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
#include "simpleio.h"
#line 31 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
#include "static_init.h"
#line 32 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
#include "task.h"
#line 33 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
#include "thread_object.h"
#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
#include "thread_state.h"
#line 35 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
#include "types.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/32/jdb_tcb-ia32-ux.cpp"

#include "config.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/32/jdb_tcb-ia32-ux.cpp"
#include "jdb.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/32/jdb_tcb-ia32-ux.cpp"
#include "jdb_disasm.h"
#line 45 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"

class Jdb_tcb_ptr
{
public:
  Jdb_tcb_ptr(Address addr = 0)
    : _base(addr & ~(Context::Size-1)),
      _offs(addr &  (Context::Size-1))
  {}

  Jdb_tcb_ptr(Jdb_tcb_ptr const &p)
    : _base(p.base()), _offs(p.offs())
  {}

  inline bool valid() const
  { return _offs <= Context::Size-sizeof(Mword); }

  bool operator > (int offs) const
  {
    return offs < 0 ? _offs > Context::Size + offs*sizeof(Mword)
                    : _offs > offs*sizeof(Mword);
  }

  Jdb_tcb_ptr &operator += (int offs)
  { _offs += offs*sizeof(Mword); return *this; }

  inline Address addr() const
  { return _base + _offs; }

  inline Mword value() const
  { return *(Mword*)(_base + _offs); }

  inline void value(Mword v)
  { *(Mword*)(_base + _offs) = v; }

  inline bool is_user_value() const;

  inline const char *user_value_desc() const;

  inline Mword top_value(int offs) const
  { return *((Mword*)(Cpu::stack_align(_base + Context::Size)) + offs); }

  inline Address base() const
  { return _base; }

  inline Address offs() const
  { return _offs; }

  inline void offs(Address offs)
  { _offs = offs; }

  inline bool is_kern_code() const
  { return (Address)&Mem_layout::image_start <= value()
           && value() <= (Address)&Mem_layout::ecode;  };

  inline bool is_kobject() const
  { return Kobject_dbg::is_kobj(reinterpret_cast<void *>(value())); }

private:
  Address  _base;
  Address  _offs;
};
#line 106 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"

class Jdb_disasm_view
{
public:
  unsigned _x, _y;

public:  
#line 384 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  Jdb_disasm_view(unsigned x, unsigned y);
  
#line 389 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  void
  show(Jdb_tcb_ptr const &p, Space *s);
};
#line 112 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


class Jdb_stack_view
{
public:
  bool is_current;
  Jdb_entry_frame *ef;
  Jdb_tcb_ptr current;
  unsigned start_y;
  Address absy;
  Address addy, addx;
  bool memdump_is_colored;

  bool edit_registers();

public:  
#line 160 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  Jdb_stack_view(unsigned y);
  
#line 165 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  static inline Mword
  cols();
  
#line 172 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  static inline Mword
  bytes_per_line();
  
#line 177 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  void
  init(Address ksp, Jdb_entry_frame *_ef, bool _is_current);
  
#line 190 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  void
  print_value(Jdb_tcb_ptr const &p, bool highl = false);
  
#line 234 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  void
  dump();//Jdb_tcb_ptr const &current)
  
  
#line 269 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  void
  highlight(bool highl);
  
#line 308 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  bool
  handle_key(int key, bool *redraw);
  
#line 331 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  void
  edit_stack(bool *redraw);

private:  
#line 259 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  inline unsigned
  posx();
  
#line 264 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  inline unsigned
  posy();
};
#line 127 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


class Jdb_tcb : public Jdb_module, public Jdb_kobject_handler
{
  static Kobject *threadid;
  static Address address;
  static char    first_char;
  static char    auto_tcb;

private:
  static void print_return_frame_regs(Jdb_tcb_ptr const &current, Mword ksp);
  static void print_entry_frame_regs(Thread *t);
  static void info_thread_state(Thread *t);

  static Jdb_disasm_view _disasm_view;
  static Jdb_stack_view  _stack_view;

#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/32/jdb_tcb-ia32-ux.cpp"
private:

  enum
  {
    Disasm_x = 41,
    Disasm_y = 11,
    Stack_y  = 17,
  };


public:  
#line 406 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  Jdb_tcb();
  
#line 429 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  virtual Kobject *
  parent(Kobject *o);
  
#line 455 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  static Jdb_module::Action_code
  show(Thread *t, int level);
  
#line 753 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  /* --- original L4 screen ------------------------------------------------------
  thread: 0081 (001.01) <00020401 00080000>                               prio: 10
  state : 85, ready                            lists: 81                   mcp: ff
  
  wait for: --                             rcv descr: 00000000   partner: 00000000
  sndq    : 0081 0081                       timeouts: 00000000   waddr0/1: 000/000
  cpu time: 0000000000 timeslice: 01/0a
  
  pager   : --                            prsent lnk: 0080 0080
  ipreempt: --                            ready link : 0080 0080
  xpreempt: --
                                          soon wakeup lnk: 
  EAX=00202dfe  ESI=00020401  DS=0008     late wakeup lnk: 
  EBX=00000028  EDI=00080000  ES=0008
  ECX=00000003  EBP=e0020400
  EDX=00000001  ESP=e00207b4
  
  700:
  720:
  740:
  760:
  780:
  7a0:                                                  0000897b 00000020 00240082
  7c0:  00000000 00000000 00000000 00000000    00000000 00000000 00000000 00000000
  7e0:  00000000 00000000 ffffff80 00000000    0000001b 00003200 00000000 00000013
  L4KD: 
  ------------------------------------------------------------------------------*/
  
  
  Jdb_module::Action_code
  action(int cmd, void *&args, char const *&fmt, int &next_char);
  
#line 839 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  Kobject_common *
  follow_link(Kobject_common *o);
  
#line 849 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  bool
  show_kobject(Kobject_common *o, int level);
  
#line 864 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  int
  show_kobject_short(char *buf, int max, Kobject_common *o);
  
#line 889 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  char const *
  kobject_type() const;
  
#line 896 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 910 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  int
  num_cmds() const;

private:  
#line 415 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  static void
  at_jdb_enter();
  
#line 440 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  static inline char *
  vcpu_state_str(Mword state, char *s, int len);
  
#line 857 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  static bool
  is_current(Thread *t);
  
#line 921 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  static inline void
  print_thread_uid_raw(Thread *t);
  
#line 928 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  static void
  print_kobject(Cap_index n);
  
#line 935 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  static void
  print_kobject(Kobject *o);
  
#line 942 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
  static void
  print_kobject(Thread *t, Cap_index capidx);
};
#line 962 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"

//
//-----------------------------------------------------------------------------
// prompt extension for thread names
class Jdb_thread_name_ext : public Jdb_prompt_ext
{
public:
  void ext();
  void update();
};

//
// IMPLEMENTATION of inline functions follows
//


#line 203 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/32/jdb_tcb-ia32-ux.cpp"


inline bool
Jdb_tcb_ptr::is_user_value() const
{
  return _offs >= Context::Size - 5 * sizeof(Mword);
}

#line 210 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/32/jdb_tcb-ia32-ux.cpp"


inline const char *
Jdb_tcb_ptr::user_value_desc() const
{
  const char *desc[] = { "SS", "SP", "EFL", "CS", "IP" };
  return desc[(Context::Size - _offs) / sizeof(Mword) - 1];
}

#line 163 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


inline Mword
Jdb_stack_view::cols()
{
  return Jdb_screen::cols() - 1;
}

#line 170 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


inline Mword
Jdb_stack_view::bytes_per_line()
{ return cols() * sizeof(Mword); }

#line 257 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


inline unsigned
Jdb_stack_view::posx()
{ return addx * (Jdb_screen::Mword_size_bmode + 1) + 9; }

#line 262 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


inline unsigned
Jdb_stack_view::posy()
{ return addy + start_y; }

#line 438 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


inline char *
Jdb_tcb::vcpu_state_str(Mword state, char *s, int len)
{
  snprintf(s, len, "%c%c%c%c%c%c",
           (state & Vcpu_state::F_fpu_enabled) ? 'F' : 'f',
           (state & Vcpu_state::F_user_mode)   ? 'U' : 'u',
           (state & Vcpu_state::F_debug_exc)   ? 'D' : 'd',
           (state & Vcpu_state::F_exceptions)  ? 'E' : 'e',
           (state & Vcpu_state::F_page_faults) ? 'P' : 'p',
           (state & Vcpu_state::F_irqs)        ? 'I' : 'i');
  s[len - 1] = 0;
  return s;
}

#line 919 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


inline void
Jdb_tcb::print_thread_uid_raw(Thread *t)
{
  printf(" <%p> ", t);
}

#endif // jdb_tcb_i_h
