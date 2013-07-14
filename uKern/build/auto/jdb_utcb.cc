// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_utcb.h"
#include "jdb_utcb_i.h"

#line 1 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
/**
 * @brief Jdb-Utcb module
 *
 * This module shows the user tcbs and the vCPU state of a thread/vcpu
 */


#line 28 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"


static Jdb_utcb Jdb_utcb INIT_PRIORITY(JDB_MODULE_INIT_PRIO);
#line 31 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"

Kobject *Jdb_utcb::thread;
#line 132 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"

STATIC_INITIALIZE(Jdb_kobject_utcb_hdl);

#line 33 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"


Jdb_utcb::Jdb_utcb()
  : Jdb_module("INFO")
{}

#line 38 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"


void
Jdb_utcb::print(Thread *t)
{
  if (t->utcb().kern())
    {
      printf("\nUtcb-addr: %p\n", t->utcb().kern());
      t->utcb().kern()->print();
    }

  if (t->state(false) & Thread_vcpu_enabled)
    {
      Vcpu_state *v = t->vcpu_state().kern();
      printf("\nVcpu-state-addr: %p\n", v);
      printf("state: %x    saved-state:  %x  sticky: %x\n",
             (int)v->state, (int)v->_saved_state, (int)v->sticky_flags);
      printf("entry_sp = %lx    entry_ip = %lx  sp = %lx\n",
             v->_entry_sp, v->_entry_ip, v->_sp);
      v->_ts.dump();
    }
}

#line 60 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"


Jdb_module::Action_code
Jdb_utcb::action( int cmd, void *&, char const *&, int &)
{
  if (cmd)
    return NOTHING;

  Thread *t = Kobject::dcast<Thread_object *>(thread);
  if (!t)
    {
      printf(" Invalid thread\n");
      return NOTHING;
    }

  print(t);

  return NOTHING;
}

#line 79 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"


int
Jdb_utcb::num_cmds() const
{ return 1; }

#line 84 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"


Jdb_module::Cmd
const * Jdb_utcb::cmds() const
{
  static Cmd cs[] =
    {
      { 0, "z", "z", "%q", "z<thread>\tshow UTCB and vCPU state", &thread }
    };
  return cs;
}

#line 106 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"

FIASCO_INIT
void
Jdb_kobject_utcb_hdl::init()
{
  static Jdb_kobject_utcb_hdl hdl;
  Jdb_kobject::module()->register_handler(&hdl);
}

#line 114 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"


bool
Jdb_kobject_utcb_hdl::handle_key(Kobject_common *o, int keycode)
{
  if (keycode == 'z')
    {
      Thread *t = Kobject::dcast<Thread_object *>(o);
      if (!t)
        return false;

      Jdb_utcb::print(t);
      Jdb::getchar();
      return true;
    }

  return false;
}
