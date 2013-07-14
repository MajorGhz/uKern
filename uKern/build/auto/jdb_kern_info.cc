// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_kern_info.h"
#include "jdb_kern_info_i.h"

#line 61 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info.cpp"


char Jdb_kern_info::_subcmd;
#line 64 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info.cpp"
Jdb_kern_info::Module_list Jdb_kern_info::modules;
#line 135 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info.cpp"

static Jdb_kern_info jdb_kern_info INIT_PRIORITY(JDB_MODULE_INIT_PRIO);

#line 48 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info.cpp"


//===================
// Std JDB modules
//===================



Jdb_kern_info_module::Jdb_kern_info_module(char subcmd, char const *descr)
{
  _subcmd = subcmd;
  _descr  = descr;
}

#line 65 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info.cpp"


void
Jdb_kern_info::register_subcmd(Jdb_kern_info_module *m)
{
  Module_iter p;
  for (p = modules.begin();
       p != modules.end()
       && (tolower(p->_subcmd) < tolower(m->_subcmd)
           || (tolower(p->_subcmd) == tolower(m->_subcmd)
               && p->_subcmd > m->_subcmd));
      ++p)
    ;

  modules.insert_before(m, p);
}

#line 81 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info.cpp"


Jdb_module::Action_code
Jdb_kern_info::action(int cmd, void *&args, char const *&, int &)
{
  if (cmd != 0)
    return NOTHING;

  char c = *(char*)(args);
  Module_iter kim;

  for (kim = modules.begin(); kim != modules.end(); ++kim)
    {
      if (kim->_subcmd == c)
	{
	  putchar('\n');
	  kim->show();
	  putchar('\n');
	  return NOTHING;
	}
    }

  putchar('\n');
  for (kim = modules.begin(); kim != modules.end(); ++kim)
    printf("  k%c   %s\n", kim->_subcmd, kim->_descr);

  putchar('\n');
  return NOTHING;
}

#line 110 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info.cpp"


int
Jdb_kern_info::num_cmds() const
{
  return 1;
}

#line 117 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info.cpp"


Jdb_module::Cmd const *
Jdb_kern_info::cmds() const
{
  static Cmd cs[] =
    {
	{ 0, "k", "k", "%c",
	   "k\tshow various kernel information (kh=help)", &_subcmd }
    };

  return cs;
}

#line 130 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kern_info.cpp"


Jdb_kern_info::Jdb_kern_info()
  : Jdb_module("INFO")
{}
