// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_tbuf_output_h
#define jdb_tbuf_output_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"

#include "initcalls.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"
#include "l4_types.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"
#include "thread.h"

//
// INTERFACE definition follows 
//

#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"

class Tb_entry;
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"

class Jdb_tbuf_output
{
private:
  typedef unsigned (Format_entry_fn)(Tb_entry *tb, const char *tidstr,
				     unsigned tidlen, char *buf, int maxlen);
  static Format_entry_fn *_format_entry_fn[];
  static bool show_names;

public:  
#line 87 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"
  static void FIASCO_INIT
  init();
  
#line 99 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"
  static void
  register_ff(Unsigned8 type, Format_entry_fn format_entry_fn);
  
#line 111 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"
  // return thread+ip of entry <e_nr>
  
  static int
  thread_ip(int e_nr, Thread const **th, Mword *ip);
  
#line 129 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"
  static void
  toggle_names();
  
#line 170 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"
  static void
  print_entry(int e_nr, char *buf, int maxlen);
  
#line 180 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"
  static void
  print_entry(Tb_entry *tb, char *buf, int maxlen);
  
#line 223 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"
  static bool
  set_filter(const char *filter_str, Mword *entries);

private:  
#line 75 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"
  static unsigned
  dummy_format_entry(Tb_entry *tb, const char *, unsigned,
  				     char *buf, int maxlen);
};

#endif // jdb_tbuf_output_h
