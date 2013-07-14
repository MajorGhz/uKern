// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_kern_info.h"
#include "jdb_kern_info_i.h"

#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info-bench.cpp"

//---------------------------------------------------------------------------

#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info-bench.cpp"

static Jdb_kern_info_bench k_a INIT_PRIORITY(JDB_MODULE_INIT_PRIO+1);
#line 31 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info-bench.cpp"

//---------------------------------------------------------------------------


#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info-bench.cpp"


Jdb_kern_info_bench::Jdb_kern_info_bench()
  : Jdb_kern_info_module('b', "Benchmark privileged instructions")
{
  Jdb_kern_info::register_subcmd(this);
}

#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info-bench.cpp"


void
Jdb_kern_info_bench::show()
{
  do_mp_benchmark();
  show_arch();
}

#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info-bench.cpp"


void
Jdb_kern_info_bench::do_mp_benchmark()
{}
