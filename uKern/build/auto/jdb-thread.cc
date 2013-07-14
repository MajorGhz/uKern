// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb.h"
#include "jdb_i.h"

#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-thread.cpp"

//---------------------------------------------------------------------------


#line 28 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-thread.cpp"


void
Jdb_tid_ext::ext()
{
  if (Jdb::get_current_active())
    printf("(%p) ", Jdb::get_current_active());
}

#line 36 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-thread.cpp"


void
Jdb_tid_ext::update()
{
  Jdb::get_current(Jdb::current_cpu);
}

#line 65 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-thread.cpp"


void
Jdb::get_current(Cpu_number cpu)
{
  current_active = get_thread(cpu);
}
