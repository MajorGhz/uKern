// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_tbuf_show_i_h
#define jdb_tbuf_show_i_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"

#include <cstdio>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include <cstring>
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"

#include "config.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "cpu.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "jdb.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "jdb_disasm.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "jdb_input.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "jdb_module.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "jdb_screen.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "jdb_symbol.h"
#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "jdb_regex.h"
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "jdb_tbuf.h"
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "jdb_tbuf_output.h"
#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "kern_cnt.h"
#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "kernel_console.h"
#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "keycodes.h"
#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "perf_cnt.h"
#line 21 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "simpleio.h"
#line 22 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "static_init.h"
#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "thread.h"
#line 24 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"

class Entry_group
{
public:
  enum { Max_group_size = 10 };
  typedef Tb_entry::Group_order Group_order;

  struct Item
  {
    Tb_entry const *e;
    Mword y;
    Group_order order;
    Item() : e(0), y(0), order(Group_order::none()) {}
  };

  Entry_group() : _c(0) {}

  Item const &operator [] (unsigned i) const { return _i[i]; }
  Item &operator [] (unsigned i) { return _i[i]; }
  unsigned size() const { return _c; }
  bool full() const { return _c >= Max_group_size; }
  unsigned push_back(Tb_entry const *e, Mword y, Group_order t)
  {
    unsigned p = _c++;
    Item *u = &_i[p];
    u->e = e;
    u->y = y;
    u->order = t;
    return p;
  }

private:
  unsigned _c;
  Item _i[Max_group_size];
};
#line 59 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"

class Jdb_tbuf_show : public Jdb_module
{
public:
  Jdb_tbuf_show() FIASCO_INIT;

private:
  static char  _search_str[40];
  static char  _filter_str[40];
  static char  _buffer_str[512];
  static Mword _status_type;
  static Mword _absy;
  static Mword _nr_cur;
  static Mword _nr_ref;
  static Mword _nr_pos[10];
  static Mword y_offset;

  enum
  {
    Index_mode        = 0, // number of event
    Tsc_delta_mode    = 1, // tsc ticks starting from last event
    Tsc_ref_mode      = 2, // tsc ticks starting from reference event
    Tsc_start_mode    = 3, // tsc ticks starting from 0
    Kclock_ref_mode   = 4, // kernel clock units (us) since reference event
    Kclock_start_mode = 5, // kernel clock units (us) since start of system
    Pmc1_delta_mode   = 6, // ticks of ctr 1 starting from last event
    Pmc2_delta_mode   = 7, // ticks of ctr 2 starting from last event
    Pmc1_ref_mode     = 8, // ticks of ctr 1 starting from reference event
    Pmc2_ref_mode     = 9, // ticks of ctr 2 starting from reference event
  };

  enum
  {
    Tbuf_start_line   = 3,
  };

  enum
  {
    Status_ok         = 0,
    Status_redraw     = 1,
    Status_error      = 2,
  };

  enum
  {
    Nil               = (Mword)-1,
  };

public:  
#line 1105 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&, char const *&, int &);
  
#line 1129 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 1144 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
  int
  num_cmds() const;

private:  
#line 120 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
  static void
  error(const char * const msg);
  
#line 127 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
  static int
  get_string(char *string, unsigned size);
  
#line 160 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
  static void
  show_perf_event_unit_mask_entry(Mword nr, Mword idx,
  					       Mword unit_mask, int exclusive);
  
#line 176 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
  static void
  show_perf_event(Mword nr);
  
#line 199 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
  static Mword
  select_perf_event_unit_mask(Mword nr, Mword unit_mask);
  
#line 295 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
  static Mword
  select_perf_event(Mword event);
  
#line 393 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
  static void
  show_events(Mword n, Mword ref, Mword count, Unsigned8 mode,
  			   Unsigned8 time_mode, int long_output);
  
#line 539 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
  // search in tracebuffer
  static Mword
  search(Mword start, Mword entries, const char *str,
  		      Unsigned8 direction);
  
#line 605 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
  static void
  find_group(Entry_group *g, Tb_entry const *e, bool older, unsigned lines,
                            unsigned depth);
  
#line 660 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
  static void
  show();
};

#endif // jdb_tbuf_show_i_h
