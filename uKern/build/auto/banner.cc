// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "banner.h"
#include "banner_i.h"


#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/banner.cpp"

FIASCO_INIT
void
Banner::init()
{
  extern char _initkip_start[];
  printf("\n%s\n", _initkip_start);
  if (Config::kernel_warn_config_string && *Config::kernel_warn_config_string)
    printf("\033[31mPerformance-critical config option(s) detected:\n"
	   "%s\033[m", Config::kernel_warn_config_string);
  putchar('\n');
}
