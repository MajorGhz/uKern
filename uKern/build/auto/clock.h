// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef clock_h
#define clock_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/clock.cpp"

#include "l4_types.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/clock-ia32.cpp"

#include "l4_types.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/clock.cpp"

class Clock_base
{

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/clock-ia32.cpp"
private:

protected:
  typedef Unsigned64 Counter;
};
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/clock.cpp"

class Clock : public Clock_base
{
public:
  typedef Unsigned64 Time;

  Clock(Cpu_number cpu);

  Time delta();

  Cpu_time us(Time t);


private:
  Cpu_number _cpu_id;
  Counter _last_value;

  Counter read_counter() const;
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/clock-ia32.cpp"

#include "cpu.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 29 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/clock.cpp"


inline Clock::Clock(Cpu_number cpu)
  : _cpu_id(cpu), _last_value(read_counter())
{}

#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/clock.cpp"



inline Clock::Time
Clock::delta()
{
  Counter t = read_counter();
  Counter r = t - _last_value;
  _last_value = t;
  return Time(r);
}

#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/clock-ia32.cpp"


inline Clock::Counter
Clock::read_counter() const
{
  return Cpu::rdtsc();
}

#line 22 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/clock-ia32.cpp"


inline Cpu_time
Clock::us(Time t)
{
  return Cpu::cpus.cpu(_cpu_id).tsc_to_us(t);
}

#endif // clock_h
