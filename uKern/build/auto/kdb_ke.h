// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kdb_ke_h
#define kdb_ke_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kdb_ke.cpp"

#include "std_macros.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kdb_ke.cpp"
# include <cstdio>

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kdb_ke.cpp"

#ifdef NDEBUG
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kdb_ke.cpp"
# define assert_kdb(expression) do {} while (0)
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kdb_ke.cpp"
# define check_kdb(expr) (void)(expr)
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kdb_ke.cpp"

#else /* ! NDEBUG */
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kdb_ke.cpp"
# define assert_kdb(expression) \
    do { if (EXPECT_FALSE(!(expression))) \
	  { printf("%s:%d: ASSERTION FAILED (%s)\n", __FILE__, __LINE__, #expression); \
	kdb_ke("XXX");} } while (0)
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kdb_ke.cpp"
# define check_kdb(expr) assert_kdb(expr)
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kdb_ke.cpp"
#endif /* ! NDEBUG */
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kdb_ke-ia32.cpp"

#define kdb_ke(msg)			\
  asm ("int3           		\n\t"	\
       "jmp 1f			\n\t"	\
       ".ascii " #msg  "	\n\t"	\
       "1:			\n\t")
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kdb_ke-ia32.cpp"

#define kdb_ke_sequence(msg)		\
  asm ("int3			\n\t"	\
       "jmp 1f			\n\t"	\
       ".ascii \"*##\"		\n\t"	\
       "1:			\n\t"	\
       : : "a"(msg))

#endif // kdb_ke_h
