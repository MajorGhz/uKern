// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_thread_h
#define jdb_thread_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread.cpp"

#include "thread_object.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread.cpp"

class Jdb_thread
{

public:  
#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread.cpp"
  static void
  print_state_long(Thread *t, unsigned cut_on_len = 0);
  
#line 64 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread.cpp"
  static bool
  has_partner(Thread *t);
  
#line 71 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread.cpp"
  static bool
  has_snd_partner(Thread *t);
  
#line 78 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread.cpp"
  static void
  print_snd_partner(Thread *t, int task_format = 0);
  
#line 89 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread.cpp"
  static void
  print_partner(Thread *t, int task_format = 0);
};

#endif // jdb_thread_h
