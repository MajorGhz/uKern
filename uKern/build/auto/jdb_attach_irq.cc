// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_attach_irq.h"
#include "jdb_attach_irq_i.h"


#line 199 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
static bool
filter_irqs(Kobject_common const *o);
#line 32 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"

char     Jdb_attach_irq::subcmd;
#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
static Jdb_attach_irq jdb_attach_irq INIT_PRIORITY(JDB_MODULE_INIT_PRIO);
#line 99 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"


/* This macro does kind of hacky magic, It uses heuristics to compare
 * If a C++ object object has a desired type. Therefore the vtable pointer
 * (*z) of an object is compared to a desired vtable pointer (with some fuzz).
 * The fuzz is necessary because there is usually a prefix data structure
 * in each vtable and the size depends on the compiler.
 * We use a range from x to x + 6 * wordsize.
 *
 * It is generally uncritical if this macro delivers a false negative. In
 * such a case the JDB may deliver less information to the user. However, it
 * critical to have a false positive, because JDB would probably crash.
 */
#define FIASCO_JDB_CMP_VTABLE(n, o) \
  extern char n[]; \
  char const *const *z = reinterpret_cast<char const* const*>(o); \
  return (*z >= n && *z <= n + 6 * sizeof(Mword)) ? (o) : 0
#line 202 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"

static Jdb_kobject_list::Mode INIT_PRIORITY(JDB_MODULE_INIT_PRIO) tnt("[IRQs]", filter_irqs);
#line 204 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"

static Jdb_kobject_irq jdb_kobject_irq INIT_PRIORITY(JDB_MODULE_INIT_PRIO);

#line 35 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"


Jdb_attach_irq::Jdb_attach_irq()
  : Jdb_module("INFO")
{}

#line 40 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"


Jdb_module::Action_code
Jdb_attach_irq::action( int cmd, void *&args, char const *&, int & )
{
  if (cmd)
    return NOTHING;

  if ((char*)args == &subcmd)
    {
      switch (subcmd)
        {
        case 'l': // list
            {
              Irq_base *r;
              putchar('\n');
	      unsigned n = Irq_mgr::mgr->nr_irqs();
              for (unsigned i = 0; i < n; ++i)
                {
                  r = static_cast<Irq*>(Irq_mgr::mgr->irq(i));
                  if (!r)
                    continue;
                  printf("IRQ %02x/%02d\n", i, i);
                }
              return NOTHING;
            }
        }
    }
  return NOTHING;
}

#line 70 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"


int
Jdb_attach_irq::num_cmds() const
{
  return 1;
}

#line 77 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"


Jdb_module::Cmd const *
Jdb_attach_irq::cmds() const
{
  static Cmd cs[] =
    {   { 0, "R", "irq", " [l]ist/[a]ttach: %c",
	   "R{l}\tlist IRQ threads", &subcmd }
    };

  return cs;
}

#line 116 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"



Irq_sender *
Jdb_kobject_irq::dcast_h(Irq_sender *i)
{
  FIASCO_JDB_CMP_VTABLE(_ZTV10Irq_sender, i);
}

#line 124 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"


Irq_muxer *
Jdb_kobject_irq::dcast_h(Irq_muxer *i)
{
  FIASCO_JDB_CMP_VTABLE(_ZTV9Irq_muxer, i);
}

#line 150 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"


char const *
Jdb_kobject_irq::kobject_type() const
{
  return JDB_ANSI_COLOR(white) "IRQ" JDB_ANSI_COLOR(default);
}

#line 157 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"



bool
Jdb_kobject_irq::handle_key(Kobject_common *o, int key)
{
  (void)o; (void)key;
  return false;
}

#line 166 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"




Kobject_common *
Jdb_kobject_irq::follow_link(Kobject_common *o)
{
  Irq_sender *t = Jdb_kobject_irq::dcast<Irq_sender*>(o);
  Kobject_common *k = t ? Kobject::from_dbg(Kobject_dbg::pointer_to_obj(t->owner())) : 0;
  return k ? k : o;
}

#line 177 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"


bool
Jdb_kobject_irq::show_kobject(Kobject_common *, int)
{ return true; }

#line 182 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"


int
Jdb_kobject_irq::show_kobject_short(char *buf, int max, Kobject_common *o)
{
  Irq *i = Kobject::dcast<Irq*>(o);
  Kobject_common *w = follow_link(o);
  Irq_sender *t = Jdb_kobject_irq::dcast<Irq_sender*>(o);

  return snprintf(buf, max, " I=%3lx %s L=%lx T=%lx F=%x Q=%d",
                  i->pin(), i->chip()->chip_type(), i->obj_id(),
                  w != o ?  w->dbg_info()->dbg_id() : 0,
		  (unsigned)i->flags(),
                  t ? t->queued() : -1);
}

#line 197 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"


static bool
filter_irqs(Kobject_common const *o)
{ return Kobject::dcast<Irq const *>(o); }
