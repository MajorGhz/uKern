// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_regex.h"
#include "jdb_regex_i.h"

#line 52 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_regex.cpp"

char       Jdb_regex::_init_done;
#line 54 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_regex.cpp"
regex_t    Jdb_regex::_r;
#line 55 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_regex.cpp"
regmatch_t Jdb_regex::_matches[1];
#line 56 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_regex.cpp"


STATIC_INITIALIZE_P(Jdb_regex, JDB_MODULE_INIT_PRIO);

#line 59 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_regex.cpp"


void FIASCO_INIT
Jdb_regex::init()
{
  if (!_init_done)
    {
      char *heap = (char*)Kmem_alloc::allocator()->unaligned_alloc(heap_size);
      if (!heap)
	panic("No memory for regex heap");
      regex_init(heap, heap_size);
      _init_done = 1;
    }
}

#line 73 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_regex.cpp"


int
Jdb_regex::start(const char *searchstr)
{
  // clear regex heap
  regex_reset();
  // compile expression
  return regcomp(&Jdb_regex::_r, searchstr, REG_EXTENDED) ? 0 : 1;
}

#line 83 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_regex.cpp"


int
Jdb_regex::find(const char *buffer, const char **beg, const char **end)
{
  // execute expression
  int ret = regexec(&Jdb_regex::_r, buffer, 
		    sizeof(Jdb_regex::_matches)/sizeof(Jdb_regex::_matches[0]),
		    Jdb_regex::_matches, 0);

  if (ret == REG_NOMATCH)
    return 0;

  if (beg)
    *beg = buffer + Jdb_regex::_matches[0].rm_so;
  if (end)
    *end = buffer + Jdb_regex::_matches[0].rm_eo;
  return 1;
}
