// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef std_macros_h
#define std_macros_h

//
// INTERFACE definition follows 
//

#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/std_macros.cpp"

#if (__GNUC__>=3)
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
#  define BUILTIN_EXPECT(exp,c)	__builtin_expect((exp),(c))
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
#  define EXPECT_TRUE(exp)	__builtin_expect((exp),true)
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
#  define EXPECT_FALSE(exp)	__builtin_expect((exp),false)
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
#else
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
#  define BUILTIN_EXPECT(exp,c)	(exp)
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
#  define EXPECT_TRUE(exp)	(exp)
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
#  define EXPECT_FALSE(exp)	(exp)
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
#endif
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/std_macros.cpp"

// Use this for functions which do not examine any values except their
// arguments and have no effects except the return value. Note that a
// function that has pointer arguments and examines the data pointed to
// must _not_ be declared `const'.  Likewise, a function that calls a
// non-`const' function usually must not be `const'.  It does not make
// sense for a `const' function to return `void'.
#define FIASCO_CONST		__attribute__ ((__const__))
#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/std_macros.cpp"

#ifdef __i386__
#line 22 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
#define FIASCO_FASTCALL		__attribute__ ((__regparm__(3)))
#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
#else
#line 24 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
#define FIASCO_FASTCALL
#line 25 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
#endif
#line 26 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/std_macros.cpp"

#if (__GNUC__<3)
#line 28 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
# define MARK_AS_DEPRECATED	/* empty */
#line 29 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
# define ALWAYS_INLINE		/* empty */
#line 30 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
# define FIASCO_NOINLINE
#line 31 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
# define FIASCO_WARN_RESULT
#line 32 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
#else
#line 33 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
# define MARK_AS_DEPRECATED	__attribute__ ((__deprecated__))
#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
# define ALWAYS_INLINE		__attribute__ ((__always_inline__))
#line 35 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
# define FIASCO_NOINLINE        __attribute__ ((__noinline__))
#line 36 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
# define FIASCO_WARN_RESULT     __attribute__ ((warn_unused_result))
#line 37 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
#endif
#line 38 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/std_macros.cpp"

#define FIASCO_NORETURN         __attribute__ ((__noreturn__))

#endif // std_macros_h
