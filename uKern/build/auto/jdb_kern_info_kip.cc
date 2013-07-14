// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_kern_info_kip.h"
#include "jdb_kern_info_kip_i.h"

#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info_kip.cpp"

static Jdb_kern_info_kip k_f INIT_PRIORITY(JDB_MODULE_INIT_PRIO+1);

#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info_kip.cpp"


Jdb_kern_info_kip::Jdb_kern_info_kip()
  : Jdb_kern_info_module('f', "Kernel Interface Page (KIP)")
{
  Jdb_kern_info::register_subcmd(this);
}

#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info_kip.cpp"


void
Jdb_kern_info_kip::show()
{
  Kip::k()->print();
}
