// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_kern_info.h"
#include "jdb_kern_info_i.h"

#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-dr.cpp"

static Jdb_kern_info_dr k_d INIT_PRIORITY(JDB_MODULE_INIT_PRIO+1);

#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-dr.cpp"


Jdb_kern_info_dr::Jdb_kern_info_dr()
  : Jdb_kern_info_module('d', "Debug registers")
{
  Jdb_kern_info::register_subcmd(this);
}

#line 21 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-dr.cpp"


void
Jdb_kern_info_dr::show()
{
  printf("dr0: " L4_PTR_FMT "\n"
         "dr1: " L4_PTR_FMT "\n"
         "dr2: " L4_PTR_FMT "\n"
         "dr3: " L4_PTR_FMT "\n"
         "dr6: " L4_PTR_FMT "\n"
         "dr7: " L4_PTR_FMT "\n",
	 Jdb_bp::get_dr(0),
	 Jdb_bp::get_dr(1),
	 Jdb_bp::get_dr(2),
	 Jdb_bp::get_dr(3),
	 Jdb_bp::get_dr(6),
	 Jdb_bp::get_dr(7));
}
