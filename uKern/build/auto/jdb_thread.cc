// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_thread.h"
#include "jdb_thread_i.h"


#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread.cpp"


void
Jdb_thread::print_state_long(Thread *t, unsigned cut_on_len)
{
  static char const * const state_names[] =
    {
      "ready",         "drq_rdy",       "send",        "rcv_wait",
      "rcv_in_progr",  "transfer",      "<unk>",       "cancel",
      "timeout",       "dead",          "suspended",   "<unk>",
      "<unk>",         "<unk>",         "<unk>",       "fpu",
      "alien",         "dealien",       "exc_progr",   "<unk>",
      "drq",           "lock_wait",     "vcpu",        "vcpu_user",
      "vcpu_fpu_disabled", "vcpu_ext"
    };

  unsigned chars = 0;
  bool comma = false;

  Mword bits = t->state(false);

  for (unsigned i = 0; i < sizeof (state_names) / sizeof (char *);
       i++, bits >>= 1)
    {
      if (!(bits & 1))
        continue;

      if (cut_on_len)
        {
          unsigned add = strlen(state_names[i]) + comma;
          if (chars + add > cut_on_len)
            {
              if (chars < cut_on_len - 4)
                putstr(",...");
              break;
            }
          chars += add;
        }

      printf("%s%s", &","[!comma], state_names[i]);

      comma = 1;
    }
}

#line 62 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread.cpp"


bool
Jdb_thread::has_partner(Thread *t)
{
  return (t->state(false) & Thread_ipc_mask) == Thread_receive_wait;
}

#line 69 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread.cpp"


bool
Jdb_thread::has_snd_partner(Thread *t)
{
  return t->state(false) & Thread_send_wait;
}

#line 76 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread.cpp"


void
Jdb_thread::print_snd_partner(Thread *t, int task_format)
{
  if (has_snd_partner(t))
    Jdb_kobject::print_uid(Kobject::from_dbg(Kobject_dbg::pointer_to_obj(t->wait_queue())), task_format);
  else
    // receiver() not valid
    putstr("   ");
}

#line 87 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread.cpp"


void
Jdb_thread::print_partner(Thread *t, int task_format)
{
  Sender *p = t->partner();

  if (!has_partner(t))
    {
      printf("%*s ", task_format, " ");
      return;
    }

  if (!p)
    {
      printf("%*s ", task_format, "-");
      return;
    }

  if (Kobject *o = Kobject::from_dbg(Kobject_dbg::pointer_to_obj(p)))
    {
      char flag = '?';
      const char *n = o->kobj_type();

      if (n == Thread_object::static_kobj_type)
        flag = ' ';
      else if (n == Irq::static_kobj_type)
        flag = '*';

      printf("%*.lx%c", task_format, o->dbg_info()->dbg_id(), flag);
    }
  else
    printf("\033[31;1m%p\033[m ", p);
}
