// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_rcupdate.h"
#include "jdb_rcupdate_i.h"

#line 91 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_rcupdate.cpp"

static Jdb_rcupdate jdb_rcupdate INIT_PRIORITY(JDB_MODULE_INIT_PRIO);

#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_rcupdate.cpp"


Jdb_rcupdate::Jdb_rcupdate()
  : Jdb_module("INFO")
{}

#line 28 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_rcupdate.cpp"


void
Jdb_rcupdate::print_batch(Rcu_batch const &b)
{
  printf("#%ld", b._b);
}

#line 35 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_rcupdate.cpp"


Jdb_module::Action_code
Jdb_rcupdate::action(int cmd, void *&, char const *&, int &)
{ printf("\nRCU--------------------------\n");
  if (cmd == 0)
    {
      printf("RCU:\n  current batch=");
      print_batch(Rcu::_rcu._current); puts("");
      printf("  completed=");
      print_batch(Rcu::_rcu._completed); puts("");
      printf("  next_pending=%s\n"
             "  cpus=", Rcu::_rcu._next_pending?"yes":"no");
      for (Cpu_number i = Cpu_number::first(); i < Config::max_num_cpus(); ++i)
	printf("%s%s", Rcu::_rcu._cpus.get(i)?"1":"0", cxx::int_value<Cpu_number>(i) % 4 == 3?" ":"");

      puts("");

      for (Cpu_number i = Cpu_number::first(); i < Config::max_num_cpus(); ++i)
	{
	  if (!Cpu::online(i))
	    continue;

	  printf("  CPU[%2u]:", cxx::int_value<Cpu_number>(i));
	  Rcu_data const *d = &Rcu::_rcu_data.cpu(i);
	  printf("    quiescent batch=");
	  print_batch(d->_q_batch); puts("");
	  printf("    quiescent state passed: %s\n", d->_q_passed?"yes":"no");
	  printf("    wait for quiescent state: %s\n", d->_pending?"yes":"no");
	  printf("    batch=");
	  print_batch(d->_batch); puts("");
	  printf("    next list:    h=%p len=%ld\n", d->_n.front(), d->_len);
	  printf("    current list: h=%p \n", d->_c.front());
	  printf("    done list:    h=%p\n", d->_d.front());
	}

      return NOTHING;
    }
  return NOTHING;
}

#line 75 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_rcupdate.cpp"


Jdb_module::Cmd const *
Jdb_rcupdate::cmds() const
{
  static Cmd cs[] =
    {
	{ 0, 0, "rcupdate", "", "rcupdate\tshow RCU information", 0},
    };
  return cs;
}

#line 86 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_rcupdate.cpp"
  

int
Jdb_rcupdate::num_cmds() const
{ return 1; }
