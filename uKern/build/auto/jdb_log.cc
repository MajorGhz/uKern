// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_log.h"
#include "jdb_log_i.h"


#line 270 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
static void swap(Tb_log_table_entry *a, Tb_log_table_entry *b);

#line 277 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
static bool lt_cmp(Tb_log_table_entry *a, Tb_log_table_entry *b);

#line 285 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"
static void sort_tb_log_table();
#line 32 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"

Tb_log_table_entry *Jdb_log_list::_end;
#line 371 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"

static Jdb_log jdb_log INIT_PRIORITY(JDB_MODULE_INIT_PRIO);

#line 41 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"


bool
Jdb_log_list_hdl::invoke(Kobject_common *, Syscall_frame *f, Utcb *utcb)
{
  switch (utcb->values[0])
    {
      case Op_query_log_typeid:
          {
            unsigned char const idx = utcb->values[1];
            if (f->tag().words() < 3 || _log_table + idx >= &_log_table_end)
              {
                f->tag(Kobject_iface::commit_result(-L4_err::EInval));
                return true;
              }

            char nbuf[32];
            strncpy(nbuf, (char const *)&utcb->values[2], sizeof(nbuf));
            nbuf[sizeof(nbuf) - 1] = 0;

            Tb_log_table_entry *r;
            r = Jdb_log_list::find_next_log(nbuf, nbuf, _log_table + idx);

            utcb->values[0] = r ? (r - _log_table) + Tbuf_dynentries : ~0UL;
            f->tag(Kobject_iface::commit_result(0, 1));
            return true;
          }
      case Op_query_log_name:
          {
            unsigned char const idx = utcb->values[1];
            if (f->tag().words() != 2 || _log_table + idx >= &_log_table_end)
              {
                f->tag(Kobject_iface::commit_result(-L4_err::EInval));
                return true;
              }

            Tb_log_table_entry *e = _log_table + idx;
	    char *dst = (char *)&utcb->values[0];
            unsigned sz = strlen(e->name) + 1;
            sz += strlen(e->name + sz) + 1;
            if (sz > sizeof(utcb->values))
              sz = sizeof(utcb->values);
            memcpy(dst, e->name, sz);
            dst[sz - 1] = 0;

            f->tag(Kobject_iface::commit_result(0));
            return true;
          }
      case Op_switch_log:
          {
            if (f->tag().words() < 3)
              {
                f->tag(Kobject_iface::commit_result(-L4_err::EInval));
                return true;
              }

            bool on = utcb->values[1];
            char nbuf[32];
            strncpy(nbuf, (char const *)&utcb->values[2], sizeof(nbuf));
            nbuf[sizeof(nbuf) - 1] = 0;

            Tb_log_table_entry *r = _log_table;
            while ((r = Jdb_log_list::find_next_log(nbuf, nbuf, r)))
              {
                Jdb_log_list::patch_item(r, on ? Jdb_log_list::patch_val(r) : 0);
                r++;
              }

            f->tag(Kobject_iface::commit_result(0));
            return true;
          }
    }

  return false;
}

#line 116 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"


int
Jdb_log_list::show_item(char *buffer, int max, void *item) const
{
  Tb_log_table_entry const *e = static_cast<Tb_log_table_entry const*>(item);
  char const *sc = e->name;
  sc += strlen(e->name) + 1;
  int pos = snprintf(buffer, max, "%s %s (%s)",
                     *(e->patch) ? "[on ]" : "[off]",  e->name, sc);
  return pos;
}

#line 133 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"


Tb_log_table_entry *
Jdb_log_list::find_next_log(const char *name, const char *sc,
                            Tb_log_table_entry *i)
{
  for (; i < _end; ++i)
    if (   !strcmp(name, i->name)
        || !strcmp(sc, i->name + strlen(i->name) + 1))
      return i;
  return 0;
}

#line 145 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"


bool
Jdb_log_list::enter_item(void *item) const
{
  Tb_log_table_entry const *e = static_cast<Tb_log_table_entry const*>(item);
  patch_item(e, *(e->patch) ? 0 : patch_val(e));
  return true;
}

#line 154 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"


void
Jdb_log_list::patch_item(Tb_log_table_entry const *e, unsigned char val)
{
  if (e->patch)
    {
      *(e->patch) = val;
      Mem_unit::clean_dcache(e->patch);
    }

  for (Tb_log_table_entry *x = _end; x < &_log_table_end; ++x)
    {
      if (equal(x, e) && x->patch)
        {
          *(x->patch) = val;
          Mem_unit::clean_dcache(x->patch);
        }
    }
}

#line 174 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"


bool
Jdb_log_list::equal(Tb_log_table_entry const *a, Tb_log_table_entry const *b)
{
  if (strcmp(a->name, b->name))
    return false;

  char const *sca = a->name; sca += strlen(sca) + 1;
  char const *scb = b->name; scb += strlen(scb) + 1;

  if (strcmp(sca, scb))
    return false;

  return a->fmt == b->fmt;
}

#line 190 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"


bool
Jdb_log_list::next(void **item)
{
  Tb_log_table_entry *e = static_cast<Tb_log_table_entry*>(*item);

  while (e + 1 < &_log_table_end)
    {
#if 0
      if (equal(e, e+1))
	++e;
      else
#endif
	{
	  *item  = e+1;
	  return true;
	}
    }

  return false;
}

#line 212 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"


bool
Jdb_log_list::pref(void **item)
{
  Tb_log_table_entry *e = static_cast<Tb_log_table_entry*>(*item);

  if (e > _log_table)
    --e;
  else
    return false;
#if 0
  while (e > _log_table)
    {
      if (equal(e, e-1))
	--e;
      else
	break;
    }
#endif

  *item  = e;
  return true;
}

#line 236 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"


int
Jdb_log_list::seek(int cnt, void **item)
{
  Tb_log_table_entry *e = static_cast<Tb_log_table_entry*>(*item);
  if (cnt > 0)
    {
      if (e + cnt >= _end)
	cnt = _end - e - 1;
    }
  else if (cnt < 0)
    {
      if (e + cnt < _log_table)
	cnt = _log_table - e;
    }

  if (cnt)
    {
      *item = e + cnt;
      return cnt;
    }

  return 0;
}

#line 268 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"


static void swap(Tb_log_table_entry *a, Tb_log_table_entry *b)
{
  Tb_log_table_entry x = *a;
  *a = *b;
  *b = x;
}

#line 276 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"

static bool lt_cmp(Tb_log_table_entry *a, Tb_log_table_entry *b)
{
  if (strcmp(a->name, b->name) < 0)
    return true;
  else
    return false;
}

#line 284 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"

static void sort_tb_log_table()
{
  for (Tb_log_table_entry *p = _log_table; p < &_log_table_end; ++p)
    {
      for (Tb_log_table_entry *x = &_log_table_end -1; x > p; --x)
	if (lt_cmp(x, x - 1))
	  swap(x - 1, x);
    }
}

#line 294 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"



void
Jdb_log_list::move_dups()
{
  _end = &_log_table_end;
  Tb_log_table_entry *const tab_end = &_log_table_end;
  for (Tb_log_table_entry *p = _log_table + 1; p < _end;)
    {
      if (equal(p-1, p))
	{
	  --_end;
	  if (p < _end)
	    {
	      Tb_log_table_entry tmp = *p;
	      memmove(p, p + 1, sizeof(Tb_log_table_entry) * (tab_end - p - 1));
	      *(tab_end - 1) = tmp;
	    }
	  else
	    break;
	}
      else
	++p;
    }
}

#line 328 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"



Jdb_log::Jdb_log()
  : Jdb_module("MONITORING")
{
  //disable_all();
  sort_tb_log_table();
  Jdb_log_list::move_dups();

  static Jdb_log_list_hdl hdl;
  Jdb_kobject::module()->register_handler(&hdl);
}

#line 341 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"


Jdb_module::Action_code
Jdb_log::action(int, void *&, char const *&, int &)
{
  if (_log_table >= &_log_table_end)
    return NOTHING;

  Jdb_log_list list;
  list.set_start(_log_table);
  list.do_list();

  return NOTHING;
}

#line 355 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"


Jdb_module::Cmd const *
Jdb_log::cmds() const
{
  static Cmd cs[] =
    {
	{ 0, "O", "log", "", "O\tselect log events", 0 },
    };
  return cs;
}

#line 366 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_log.cpp"


int
Jdb_log::num_cmds() const
{ return 1; }
