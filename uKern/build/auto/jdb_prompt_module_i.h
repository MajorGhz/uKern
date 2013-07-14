// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_prompt_module_i_h
#define jdb_prompt_module_i_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"

#include <cstdio>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"
#include <cstring>
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"

#include "jdb.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"
#include "jdb_module.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"
#include "jdb_screen.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"
#include "kernel_console.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"
#include "static_init.h"
#line 217 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"

#include "cpu.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"


//===================
// Std JDB modules
//===================

/**
 * Jdb-prompt module.
 *
 * This module handles some commands that
 * change Jdb prompt and screen settings.
 */
class Jdb_pcm : public Jdb_module
{
public:
  Jdb_pcm() FIASCO_INIT;
private:
  static char subcmd;
  static char prompt_color;
  static char direct_enable;
  static int  screen_height;
  static int  screen_width;

public:  
#line 103 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&args, char const *&fmt, int &);
  
#line 183 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"
  int num_cmds() const;
  
#line 189 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"
  Jdb_module::Cmd const * cmds() const;

private:  
#line 44 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"
  int
  get_coords(Console *cons, unsigned &x, unsigned &y);
  
#line 77 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"
  void
  detect_screensize();
  
#line 221 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"
  int
  wait_for_escape(Console *cons);
};

#endif // jdb_prompt_module_i_h
