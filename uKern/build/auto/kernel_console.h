// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kernel_console_h
#define kernel_console_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_console.cpp"

#include "mux_console.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_console.cpp"
#include "std_macros.h"

//
// INTERFACE definition follows 
//

#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_console.cpp"

class Kconsole : public Mux_console
{
public:
  int  getchar(bool blocking = true);
  void getchar_chance();

  static Mux_console *console() FIASCO_CONST
  { return _c; }

private:
  static Static_object<Kconsole> _c;

public:  
#line 51 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_console.cpp"
  inline Kconsole();
  
#line 59 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_console.cpp"
  static FIASCO_NOINLINE
  void
  init();
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 48 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_console.cpp"



inline Kconsole::Kconsole()
{
  Console::stdout = this;
  Console::stderr = this;
  Console::stdin  = this;
}

#endif // kernel_console_h
