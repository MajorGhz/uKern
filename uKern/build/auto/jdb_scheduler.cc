// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_scheduler.h"
#include "jdb_scheduler_i.h"

#line 55 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_scheduler.cpp"

static Jdb_cpu jdb_cpu INIT_PRIORITY(JDB_MODULE_INIT_PRIO);

#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_scheduler.cpp"


Jdb_cpu::Jdb_cpu()
  : Jdb_kobject_handler(Scheduler::static_kobj_type)
{
  Jdb_kobject::module()->register_handler(this);
}

#line 30 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_scheduler.cpp"


bool
Jdb_cpu::show_kobject(Kobject_common *, int )
{
  return true;
}

#line 37 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_scheduler.cpp"


char const *
Jdb_cpu::kobject_type() const
{
  return JDB_ANSI_COLOR(blue) "Sched" JDB_ANSI_COLOR(default);
}
