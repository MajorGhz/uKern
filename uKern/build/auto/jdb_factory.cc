// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_factory.h"
#include "jdb_factory_i.h"

#line 52 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_factory.cpp"

static Jdb_factory jdb_factory INIT_PRIORITY(JDB_MODULE_INIT_PRIO);

#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_factory.cpp"


Jdb_factory::Jdb_factory()
  : Jdb_kobject_handler(Factory::static_kobj_type)
{
  Jdb_kobject::module()->register_handler(this);
}

#line 30 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_factory.cpp"


bool
Jdb_factory::show_kobject(Kobject_common *, int )
{
  return true;
}

#line 37 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_factory.cpp"


char const *
Jdb_factory::kobject_type() const
{
  return JDB_ANSI_COLOR(yellow) "Factory" JDB_ANSI_COLOR(default);
}

#line 44 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_factory.cpp"


int
Jdb_factory::show_kobject_short(char *buf, int max, Kobject_common *o)
{
  Factory *t = Kobject::dcast<Factory*>(o);
  return snprintf(buf, max, " c=%ld l=%ld", t->current(), t->limit());
}
