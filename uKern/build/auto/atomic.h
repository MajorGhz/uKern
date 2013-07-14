// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef atomic_h
#define atomic_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"

#include "types.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"

extern "C" void cas_error_type_with_bad_size_used(void);
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"

#define MACRO_CAS_ASSERT(rs,cs) \
  if( (rs) != (cs) ) \
    cas_error_type_with_bad_size_used()
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"


template< typename A, typename B >
struct Pair
{
  A first;
  B second;

  Pair() {}
  Pair(A const &a, B const &b) : first(a), second(b) {}
};

#line 27 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"
template< typename Type > inline bool
cas(Type *ptr, Type oldval, Type newval);

#line 36 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"
template< typename Type > inline bool
cas2(Type *ptr, Type *oldval, Type *newval);

#line 46 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"
template <typename T> inline T
atomic_change(T *ptr, T mask, T bits);

#line 62 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"
inline void
atomic_mp_and(Mword *l, Mword value);

#line 69 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"
inline void
atomic_mp_or(Mword *l, Mword value);

#line 77 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"
inline void
atomic_mp_add(Mword *l, Mword value);

#line 84 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"
inline void
atomic_add(Mword *l, Mword value);

#line 91 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"
inline void
atomic_and(Mword *l, Mword mask);

#line 98 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"
inline void
atomic_or(Mword *l, Mword bits);

#line 104 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"
// ``unsafe'' stands for no safety according to the size of the given type.
// There are type safe versions of the cas operations in the architecture
// independent part of atomic that use the unsafe versions and make a type
// check.


inline bool
cas_unsafe(Mword *ptr, Mword oldval, Mword newval);

#line 126 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"
inline bool
mp_cas_arch(Mword *m, Mword o, Mword n);

#line 141 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"
inline bool
cas2_unsafe(Mword *ptr, Mword *oldval, Mword *newval);

#line 159 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"
inline bool
mp_cas2_arch(char *m, Mword o1, Mword o2, Mword n1, Mword n2);

#line 358 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"
template< typename T > inline bool
mp_cas(T *m, T o, T n);

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 25 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"

 
template< typename Type > inline bool
cas(Type *ptr, Type oldval, Type newval)
{
  MACRO_CAS_ASSERT(sizeof(Type),sizeof(Mword));
  return cas_unsafe(reinterpret_cast<Mword*>(ptr),
                    (Mword)oldval, (Mword)newval);
}

#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"

 
template< typename Type > inline bool
cas2(Type *ptr, Type *oldval, Type *newval)
{
  MACRO_CAS_ASSERT(sizeof(Type),(sizeof(Mword)*2));
  return cas2_unsafe(reinterpret_cast<Mword*>(ptr),
                     reinterpret_cast<Mword*>(oldval),
                     reinterpret_cast<Mword*>(newval));
}

#line 44 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"

 
template <typename T> inline T
atomic_change(T *ptr, T mask, T bits)
{
  T old;
  do
    {
      old = *ptr;
    }
  while (!cas(ptr, old, (old & mask) | bits));
  return old;
}

#line 60 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"


inline void
atomic_mp_and(Mword *l, Mword value)
{
  asm volatile ("lock; andl %1, %2" : "=m"(*l) : "ir"(value), "m"(*l));
}

#line 67 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"


inline void
atomic_mp_or(Mword *l, Mword value)
{
  asm volatile ("lock; orl %1, %2" : "=m"(*l) : "ir"(value), "m"(*l));
}

#line 74 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"



inline void
atomic_mp_add(Mword *l, Mword value)
{
  asm volatile ("lock; addl %1, %2" : "=m"(*l) : "ir"(value), "m"(*l));
}

#line 82 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"


inline void
atomic_add(Mword *l, Mword value)
{
  asm volatile ("addl %1, %2" : "=m"(*l) : "ir"(value), "m"(*l));
}

#line 89 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"


inline void
atomic_and(Mword *l, Mword mask)
{
  asm volatile ("andl %1, %2" : "=m"(*l) : "ir"(mask), "m"(*l));
}

#line 96 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"


inline void
atomic_or(Mword *l, Mword bits)
{
  asm volatile ("orl %1, %2" : "=m"(*l) : "ir"(bits), "m"(*l));
}

#line 103 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"

// ``unsafe'' stands for no safety according to the size of the given type.
// There are type safe versions of the cas operations in the architecture
// independent part of atomic that use the unsafe versions and make a type
// check.


inline bool
cas_unsafe(Mword *ptr, Mword oldval, Mword newval)
{
  Mword tmp;

  asm volatile
    ("cmpxchgl %1, %2"
     : "=a" (tmp)
     : "r" (newval), "m" (*ptr), "a" (oldval)
     : "memory");

  return tmp == oldval;
}

#line 123 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"



inline bool
mp_cas_arch(Mword *m, Mword o, Mword n)
{
  Mword tmp;

  asm volatile
    ("lock; cmpxchgl %1, %2"
     : "=a" (tmp)
     : "r" (n), "m" (*m), "a" (o)
     : "memory");

  return tmp == o;
}

#line 139 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"


inline bool
cas2_unsafe(Mword *ptr, Mword *oldval, Mword *newval)
{
  char ret;
  asm volatile
    ("cmpxchg8b %3 ; sete %%cl"
     : "=c" (ret), 
       "=a" (* oldval), 
       "=d" (*(oldval+1))
     : "m" (*ptr) , 
       "a" (* oldval), "d" (*(oldval+1)), 
       "b" (* newval), "c" (*(newval+1))
     : "memory");

  return ret;
}

#line 157 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"


inline bool
mp_cas2_arch(char *m, Mword o1, Mword o2, Mword n1, Mword n2)
{
  char ret;
  asm volatile
    ("lock; cmpxchg8b %3 ; sete %%cl"
     : "=c" (ret), "=a" (o1), "=d" (o2)
     : "m" (*m), "a" (o1), "d" (o2),
       "b" (n1), "c" (n2)
     : "memory");

  return ret;
}

#line 356 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/atomic.cpp"

 
template< typename T > inline bool
mp_cas(T *m, T o, T n)
{ return cas(m,o,n); }

#endif // atomic_h
