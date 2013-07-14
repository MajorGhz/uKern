// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_bp_i_h
#define jdb_bp_i_h
#line 73 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"

#include <cstdio>
#line 75 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"

#include "jdb.h"
#line 77 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
#include "jdb_input.h"
#line 78 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
#include "jdb_module.h"
#line 79 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
#include "jdb_handler_queue.h"
#line 80 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
#include "jdb_screen.h"
#line 81 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
#include "jdb_tbuf.h"
#line 82 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
#include "l4_types.h"
#line 83 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
#include "static_init.h"
#line 84 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
#include "task.h"
#line 85 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
#include "thread.h"
#line 86 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"

class Jdb_set_bp : public Jdb_module, public Jdb_input_task_addr
{
public:
  Jdb_set_bp() FIASCO_INIT;
private:
  static char     breakpoint_cmd;
  static char     breakpoint_restrict_cmd;
  static Mword    breakpoint_number;
  static Mword    breakpoint_length;
  static Mword    breakpoint_restrict_task;
  static Mword    breakpoint_restrict_thread;
  typedef struct
    {
      char        reg;
      Mword       low;
      Mword       high;
    } Restrict_reg;
  static Restrict_reg breakpoint_restrict_reg;
  typedef struct
    {
      Address     addr;
      Mword       low;
      Mword       high;
    } Restrict_addr;
  static Restrict_addr breakpoint_restrict_addr;
  static int      state;

public:  
#line 612 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&args, char const *&fmt, int &next_char);
  
#line 813 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 832 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  int
  num_cmds() const;
};

//
// IMPLEMENTATION of inline functions follows
//


#line 429 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


inline void
Jdb_bp::clr_dr7(int num, Mword &dr7)
{
  dr7 &= ~(((3 + (3 <<2)) << (16 + 4*num)) + (3 << (2*num)));
}

#line 436 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


inline void
Jdb_bp::set_dr7(int num, Mword len, Breakpoint::Mode mode, Mword &dr7)
{
  // the encoding of length 8 is special
  if (len == 8)
    len = 3;

  dr7 |= ((((mode & 3) + ((len-1)<<2)) << (16 + 4*num)) + (2 << (2*num)));
  dr7 |= 0x200; /* exact breakpoint enable (not available on P6 and below) */
}

#endif // jdb_bp_i_h
