// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_prompt_ext.h"
#include "jdb_prompt_ext_i.h"

#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_ext.cpp"

Jdb_prompt_ext::List Jdb_prompt_ext::exts;

#line 25 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_ext.cpp"


Jdb_prompt_ext::Jdb_prompt_ext()
{
  exts.push_front(this);
}

#line 33 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_ext.cpp"


void Jdb_prompt_ext::update()
{}

#line 37 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_ext.cpp"


void Jdb_prompt_ext::do_all()
{
  for (Iter e = exts.begin(); e != exts.end(); ++e)
    e->ext();
}

#line 44 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_ext.cpp"


void Jdb_prompt_ext::update_all()
{
  for (Iter e = exts.begin(); e != exts.end(); ++e)
    e->update();
}
