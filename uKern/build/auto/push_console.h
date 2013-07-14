// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef push_console_h
#define push_console_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/push_console.cpp"

#include "console.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/push_console.cpp"

class Push_console : public Console
{
private:
  char _buffer[256];
  int _in;
  int _out;

public:  
#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/push_console.cpp"
  int
  getchar(bool /*blocking*/);
  
#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/push_console.cpp"
  int
  char_avail() const;
  
#line 41 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/push_console.cpp"
  int
  write(char const * /*str*/, size_t len);
  
#line 48 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/push_console.cpp"
  void
  push(char c);
  
#line 63 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/push_console.cpp"
  inline void
  flush();
  
#line 70 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/push_console.cpp"
  inline Mword
  get_attributes() const;
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 61 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/push_console.cpp"


inline void
Push_console::flush()
{
  _in = _out = 0;
}

#line 68 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/push_console.cpp"


inline Mword
Push_console::get_attributes() const
{
  return PUSH | IN;
}

#endif // push_console_h
