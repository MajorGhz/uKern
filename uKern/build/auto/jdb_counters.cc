// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_counters.h"
#include "jdb_counters_i.h"

#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_counters.cpp"

char Jdb_counters::counters_cmd;
#line 89 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_counters.cpp"

static Jdb_counters jdb_counters INIT_PRIORITY(JDB_MODULE_INIT_PRIO);

#line 21 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_counters.cpp"


void
Jdb_counters::show()
{
  putchar('\n');
  for (unsigned i=0; i<Kern_cnt_max; i++)
    printf("  %-25s%10ld\n", Kern_cnt::get_str(i), *Kern_cnt::get_ctr(i));
  putchar('\n');
}

#line 31 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_counters.cpp"


void
Jdb_counters::reset()
{
  memset(Jdb_tbuf::status()->kerncnts, 0, 
         sizeof(Jdb_tbuf::status()->kerncnts));
}

#line 39 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_counters.cpp"


Jdb_module::Action_code
Jdb_counters::action(int cmd, void *&, char const *&, int &)
{
  if (!Config::Jdb_accounting)
    {
      puts(" accounting disabled");
      return ERROR;
    }

  if (cmd == 0)
    {
      switch (counters_cmd)
	{
	case 'l':
	  show();
	  break;
	case 'r':
	  reset();
	  putchar('\n');
	  break;
	}
    }
  return NOTHING;
}

#line 65 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_counters.cpp"


Jdb_counters::Cmd const *
Jdb_counters::cmds() const
{
  static Cmd cs[] =
    {
	{ 0, "C", "cnt", "%c",
	  "C{l|r}\tshow/reset kernel event counters", &counters_cmd },
    };
  return cs;
}

#line 77 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_counters.cpp"


int
Jdb_counters::num_cmds() const
{
  return 1;
}

#line 84 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_counters.cpp"


Jdb_counters::Jdb_counters()
  : Jdb_module("MONITORING")
{}
