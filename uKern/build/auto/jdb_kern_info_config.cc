// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_kern_info_config.h"
#include "jdb_kern_info_config_i.h"

#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info_config.cpp"

static Jdb_kern_info_config k_C INIT_PRIORITY(JDB_MODULE_INIT_PRIO+1);
#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info_config.cpp"

extern "C" const char _binary_gblcfg_o_txt_start;
#line 21 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info_config.cpp"
extern "C" const char _binary_gblcfg_o_txt_end;

#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info_config.cpp"


Jdb_kern_info_config::Jdb_kern_info_config()
  : Jdb_kern_info_module('C', "Kernel config")
{
  Jdb_kern_info::register_subcmd(this);
}

#line 22 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info_config.cpp"


void
Jdb_kern_info_config::show()
{
  printf("%*.*s",
      (unsigned)(&_binary_gblcfg_o_txt_end - &_binary_gblcfg_o_txt_start),
      (unsigned)(&_binary_gblcfg_o_txt_end - &_binary_gblcfg_o_txt_start),
      &_binary_gblcfg_o_txt_start);
}
