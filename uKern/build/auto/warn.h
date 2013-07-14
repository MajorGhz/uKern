// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef warn_h
#define warn_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/warn.cpp"

#include <cstdio>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/warn.cpp"

#include "config.h"

//
// INTERFACE definition follows 
//

#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/warn.cpp"

enum Warn_level
{
  Error   = 0,
  Warning = 1,
  Info    = 2,
};
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/warn.cpp"

#define WARNX(level,fmt...) \
  do {							\
       if (level   <= (int)Config::Warn_level)		\
	 printf("\n\033[31mKERNEL\033[m: Warning: " fmt);	\
     } while (0)
#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/warn.cpp"

#define WARN(fmt...) WARNX(Warning, fmt)

#endif // warn_h
