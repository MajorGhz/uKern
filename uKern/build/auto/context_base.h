// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef context_base_h
#define context_base_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context_base.cpp"

#include "types.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context_base.cpp"
#include "config_tcbsize.h"

//
// INTERFACE definition follows 
//

#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context_base.cpp"

class Context;
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context_base.cpp"

class Context_base
{
public:
  enum
  {
    Size = THREAD_BLOCK_SIZE
  };

  // This virtual dtor enforces that Context / Thread / Context_base
  // all start at offset 0
  virtual ~Context_base() = 0;

protected:
  friend Cpu_number &__cpu_of(const void *);
  Mword _state;
  Cpu_number _cpu;
};

#line 36 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context_base.cpp"
inline Context *context_of(const void *ptr);

#line 43 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context_base.cpp"
inline Context *current();

#line 47 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context_base.cpp"
inline Cpu_number &__cpu_of(const void *ptr);

#line 51 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context_base.cpp"
inline void set_cpu_of(const void *ptr, Cpu_number cpu);

#line 56 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context_base.cpp"
inline Cpu_number cpu_of(const void *ptr);

#line 63 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context_base.cpp"
inline Cpu_number current_cpu();

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 29 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context_base.cpp"

#include "config.h"
#line 31 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context_base.cpp"
#include "processor.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 32 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context_base.cpp"

inline Context_base::~Context_base() {}

#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context_base.cpp"


inline Context *context_of(const void *ptr)
{
  return reinterpret_cast<Context *>
    (reinterpret_cast<unsigned long>(ptr) & ~(Context_base::Size - 1));
}

#line 41 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context_base.cpp"


inline Context *current()
{ return context_of((void *)Proc::stack_pointer()); }

#line 45 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context_base.cpp"


inline Cpu_number &__cpu_of(const void *ptr)
{ return reinterpret_cast<Context_base*>(context_of(ptr))->_cpu; }

#line 49 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context_base.cpp"


inline void set_cpu_of(const void *ptr, Cpu_number cpu)
{ __cpu_of(ptr) = cpu; }

#line 53 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context_base.cpp"



inline Cpu_number cpu_of(const void *ptr)
{ return __cpu_of(ptr); }

#line 61 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context_base.cpp"


inline Cpu_number current_cpu()
{ return Cpu_number::boot_cpu(); }

#endif // context_base_h
