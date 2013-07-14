// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef startup_h
#define startup_h

//
// INTERFACE definition follows 
//

#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/startup.cpp"

class Startup
{
public:
  // startup code for the early startup phase
  // this code is executed before anything else, inparticular before
  // any I/O is initialized
  static void stage1();

  // startup code that runs after console I/O is initialized
  static void stage2();
};

#endif // startup_h
