// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_space.h"
#include "jdb_space_i.h"


#line 99 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"
static bool space_filter(Kobject_common const *o);

#line 131 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"
static bool
filter_task_thread(Kobject_common const *o);
#line 28 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"

Task *Jdb_space::task;
#line 136 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"
static Jdb_space jdb_space INIT_PRIORITY(JDB_MODULE_INIT_PRIO);
#line 137 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"
static Jdb_kobject_list::Mode INIT_PRIORITY(JDB_MODULE_INIT_PRIO) tnt("[Tasks + Threads]", filter_task_thread);

#line 30 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"


Jdb_space::Jdb_space()
  : Jdb_module("INFO"), Jdb_kobject_handler(Task::static_kobj_type)
{
  Jdb_kobject::module()->register_handler(this);
}

#line 37 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"


bool
Jdb_space::show_kobject(Kobject_common *o, int lvl)
{
  Task *t = Kobject::dcast<Task*>(o);
  show(t);
  if (lvl)
    {
      Jdb::getchar();
      return true;
    }

  return false;
}

#line 52 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"


char const *
Jdb_space::kobject_type() const
{
  return JDB_ANSI_COLOR(red) "Task" JDB_ANSI_COLOR(default);
}

#line 59 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"


int
Jdb_space::show_kobject_short(char *buf, int max, Kobject_common *o)
{
  Task *t = Kobject::dcast<Task*>(o);
  int cnt = 0;
  if (t == Kernel_task::kernel_task())
    {
      cnt = snprintf(buf, max, " {KERNEL}");
      max -= cnt;
      buf += cnt;
    }
  return cnt + snprintf(buf, max, " R=%ld", t->ref_cnt());
}

#line 74 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"


void
Jdb_space::print_space(Space *s)
{
  printf("%p", s);
}

#line 81 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"


void
Jdb_space::show(Task *t)
{
  printf("Space %p (Kobject*)%p\n", t, static_cast<Kobject*>(t));

  for (Space::Ku_mem_list::Const_iterator m = t->_ku_mem.begin(); m != t->_ku_mem.end();
       ++m)
    printf("  utcb area: user_va=%p kernel_va=%p size=%x\n",
           m->u_addr.get(), m->k_addr, m->size);

  unsigned long m = t->ram_quota()->current();
  unsigned long l = t->ram_quota()->limit();
  printf("  mem usage:  %ld (%ldKB) of %ld (%ldKB) @%p\n", 
         m, m/1024, l, l/1024, t->ram_quota());
}

#line 98 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"

static bool space_filter(Kobject_common const *o)
{ return Kobject::dcast<Task const *>(o); }

#line 101 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"


Jdb_module::Action_code
Jdb_space::action(int cmd, void *&, char const *&, int &)
{
  if (cmd == 0)
    {
      Jdb_kobject_list list(space_filter);
      list.do_list();
    }
  return NOTHING;
}

#line 113 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"


Jdb_module::Cmd const *
Jdb_space::cmds() const
{
  static Cmd cs[] =
    {
	{ 0, "s", "spacelist", "", "s\tshow task list", 0 },
    };
  return cs;
}

#line 124 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"
  

int
Jdb_space::num_cmds() const
{ return 1; }

#line 129 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_space.cpp"


static bool
filter_task_thread(Kobject_common const *o)
{
  return Kobject::dcast<Task const *>(o) || Kobject::dcast<Thread_object const *>(o);
}
