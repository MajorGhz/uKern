// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef globals_h
#define globals_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/globals.cpp"

#include <cassert>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/globals.cpp"

#include "panic.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/globals.cpp"
#include "per_cpu_data.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/globals.cpp"
#include "types.h"

//
// INTERFACE definition follows 
//

#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/globals.cpp"

class Timeout;
#line 29 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/globals.cpp"

class Kobject_iface;
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/globals.cpp"

extern Per_cpu<Timeout *> timeslice_timeout;
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/globals.cpp"

/* the check macro is like assert(), but it evaluates its argument
   even if NDEBUG is defined */
#ifndef check
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/globals.cpp"
#ifdef NDEBUG
#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/globals.cpp"
# define check(expression) ((void)(expression))
#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/globals.cpp"
#else /* ! NDEBUG */
#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/globals.cpp"
# ifdef ASSERT_KDB_KE
#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/globals.cpp"
#  define check(expression) assert(expression)
#line 21 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/globals.cpp"
# else
#line 22 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/globals.cpp"
#  define check(expression) \
          ((void)((expression) ? 0 : \
                 (panic(__FILE__":%u: failed check `"#expression"'", \
                         __LINE__), 0)))
#line 26 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/globals.cpp"
# endif
#line 27 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/globals.cpp"
#endif /* ! NDEBUG */
#line 28 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/globals.cpp"
#endif /* check */
#line 31 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/globals.cpp"

class Initial_kobjects
{
public:
  enum
  {
    Max = 5,
    First_cap = 5,

    End_cap = First_cap + Max,
  };

  static Cap_index first() { return Cap_index(First_cap); }
  static Cap_index end() { return Cap_index(End_cap); }

  void register_obj(Kobject_iface *o, unsigned cap)
  {
    assert (cap >= First_cap);
    assert (cap < End_cap);

    cap -= First_cap;

    assert (!_v[cap]);

    _v[cap] = o;
  }

  Kobject_iface *obj(Cap_index cap) const
  {
    assert (cap >= first());
    assert (cap < end());

    return _v[cxx::int_value<Cap_diff>(cap - first())];
  }

private:
  Kobject_iface *_v[Max];
};
#line 69 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/globals.cpp"


extern Initial_kobjects initial_kobjects;

#endif // globals_h
