// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_exit_module.h"
#include "jdb_exit_module_i.h"

#line 25 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"

static Jdb_exit_module jdb_exit_module INIT_PRIORITY(JDB_MODULE_INIT_PRIO);

#line 27 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"


Jdb_module::Action_code
Jdb_exit_module::action(int cmd, void *&, char const *&, int &)
{
  if (cmd != 0)
    return NOTHING;

  // re-enable output of all consoles but GZIP and DEBUG
  Kconsole::console()->change_state(0, Console::GZIP | Console::DEBUG,
				    ~0UL, Console::OUTENABLED);
  // re-enable input of all consoles but PUSH and DEBUG
  Kconsole::console()->change_state(0, Console::PUSH | Console::DEBUG,
				    ~0UL, Console::INENABLED);

  Jdb::screen_scroll(1, 127);
  Jdb::blink_cursor(Jdb_screen::height(), 1);
  Jdb::cursor(127, 1);
  vmx_off();
  terminate(1);
  return LEAVE;
}

#line 49 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"


int
Jdb_exit_module::num_cmds() const
{
  return 1;
}

#line 56 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"


Jdb_module::Cmd const *
Jdb_exit_module::cmds() const
{
  static Cmd cs[] =
    { { 0, "^", "exit", "", "^\treboot the system", 0 } };

  return cs;
}

#line 66 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"


Jdb_exit_module::Jdb_exit_module()
  : Jdb_module("GENERAL")
{}

#line 104 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"


void
Jdb_exit_module::vmx_off() const {}
