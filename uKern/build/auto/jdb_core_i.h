// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_core_i_h
#define jdb_core_i_h
#line 137 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"

#include <cstring>
#line 139 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#include <cstdarg>
#line 140 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#include <cstdio>
#line 141 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#include <cstdlib>
#line 142 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#include <cctype>
#line 143 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#include <simpleio.h>
#line 144 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"

#include "div32.h"
#line 146 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#include "l4_types.h"
#line 147 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#include "kernel_console.h"
#line 148 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#include "keycodes.h"
#line 149 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#include "jdb_prompt_ext.h"
#line 150 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#include "jdb_screen.h"
#line 776 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"


//===================
// Std JDB modules
//===================


/**
 * Private 'go' module.
 * 
 * This module handles the 'go' or 'g' command 
 * that continues normal program execution.
 */
class Go_m : public Jdb_module
{
public:
  Go_m() FIASCO_INIT;

public:  
#line 803 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
  Jdb_module::Action_code action( int, void *&, char const *&, int & );
  
#line 809 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
  int num_cmds() const;
  
#line 815 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
  Jdb_module::Cmd const * cmds() const;
};
#line 826 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"


/**
 * Private 'help' module.
 * 
 * This module handles the 'help' or 'h' command and 
 * prints out a help screen.
 */
class Help_m : public Jdb_module
{
public:
  Help_m() FIASCO_INIT;

public:  
#line 845 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
  Jdb_module::Action_code action( int, void *&, char const *&, int & );
  
#line 935 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
  int num_cmds() const;
  
#line 941 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
  Jdb_module::Cmd const * cmds() const;
};

//
// IMPLEMENTATION of inline functions follows
//


#line 386 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"


inline void
Jdb_core::cmd_putchar(int c)
{ if (short_mode) putchar(c); }

#endif // jdb_core_i_h
