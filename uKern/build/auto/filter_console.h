// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef filter_console_h
#define filter_console_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/filter_console.cpp"

#include "console.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/filter_console.cpp"
#include "types.h"

//
// INTERFACE definition follows 
//

#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/filter_console.cpp"

class Filter_console : public Console
{
public:
  ~Filter_console() {}

private:
  Console *const _o;
  int csi_timeout;
  enum State
  {
    NORMAL,
    UNKNOWN_ESC,
    GOT_CSI, ///< control sequence introducer
  };

  State state;
  unsigned pos;
  char ibuf[32];
  unsigned arg;
  int args[4];

public:  
#line 39 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/filter_console.cpp"
  int char_avail() const;
  
#line 56 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/filter_console.cpp"
  explicit inline Filter_console(Console *o, int to = 10);
  
#line 65 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/filter_console.cpp"
  int
  write(char const *str, size_t len);
  
#line 123 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/filter_console.cpp"
  int
  getchar(bool b = true);
  
#line 264 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/filter_console.cpp"
  Mword
  get_attributes() const;

private:  
#line 112 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/filter_console.cpp"
  inline int
  getchar_timeout(unsigned timeout);
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 54 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/filter_console.cpp"


inline Filter_console::Filter_console(Console *o, int to)
  : _o(o), csi_timeout(to), state(NORMAL), pos(0), arg(0)
{
  if (o->failed())
    fail();
}

#endif // filter_console_h
