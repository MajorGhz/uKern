// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_sender_list.h"
#include "jdb_sender_list_i.h"

#line 22 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"

static Jdb_sender_list jdb_sender_list INIT_PRIORITY(JDB_MODULE_INIT_PRIO);
#line 24 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"

Kobject *Jdb_sender_list::object;

#line 26 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"



void
Jdb_sender_list::show_sender_list(Prio_list *t, int printlines)
{
  puts(printlines ? Jdb_screen::Line : "");
  Jdb::clear_to_eol();

  Prio_list::P_list::Iterator p = t->begin();
  if (p == t->end())
    {
      Jdb::clear_to_eol();
      printf("Nothing in sender list\n");
      if (printlines)
        puts(Jdb_screen::Line);
      return;
    }

  for (; p != t->end(); ++p)
    {
      Jdb::clear_to_eol();
      printf("%02x: ", p->prio());
      Prio_list::S_list::Iterator s = Prio_list::S_list::iter(*p);
      do
        {
          Thread *ts = static_cast<Thread *>(Sender::cast(*s));
          printf("%s %lx", *s == *p ? "" : ",", ts->dbg_info()->dbg_id());
          ++s;
        } while (*s != *p);
      puts("");
    }

  if (printlines)
    puts(Jdb_screen::Line);
}

#line 62 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"


Jdb_module::Action_code
Jdb_sender_list::action(int cmd, void *&, char const *&, int &)
{
  if (cmd)
    return NOTHING;

  if (Thread *t = Kobject::dcast<Thread_object *>(object))
    {
      printf("Thread: %lx\n", t->dbg_id());
      show_sender_list(t->sender_list(), 0);
      return NOTHING;
    }
  else if (Ipc_gate *g = Kobject::dcast<Ipc_gate_obj *>(object))
    {
      printf("Ipc_gate: %lx\n", g->dbg_id());
      show_sender_list(&g->_wait_q, 0);
      return NOTHING;
    }

  printf(" Invalid object\n");
  return NOTHING;
}

#line 86 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"


bool
Jdb_sender_list::handle_key(Kobject_common *o, int keycode)
{
  if (keycode != 'S')
    return false;

  if (Thread *t = Kobject::dcast<Thread_object *>(o))
    show_sender_list(t->sender_list(), 1);
  else if (Ipc_gate *g = Kobject::dcast<Ipc_gate_obj *>(o))
    show_sender_list(&g->_wait_q, 1);
  else
    return false;

  Jdb::getchar();
  return true;
}

#line 104 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"


int Jdb_sender_list::num_cmds() const
{ return 1; }

#line 108 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"


Jdb_module::Cmd const * Jdb_sender_list::cmds() const
{
  static Cmd cs[] =
    {
	{ 0, "ls", "senderlist", "%q",
          "senderlist\tshow sender-list of thread", &object }
    };

  return cs;
}

#line 120 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"


Jdb_sender_list::Jdb_sender_list()
  : Jdb_module("INFO"), Jdb_kobject_handler(0)
{
  Jdb_kobject::module()->register_handler(this);
}
