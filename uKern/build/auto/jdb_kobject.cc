// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_kobject.h"
#include "jdb_kobject_i.h"

#line 100 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"

//--------------------------------------------------------------------------

#line 121 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"

Jdb_kobject_list::Mode::Mode_list Jdb_kobject_list::Mode::modes;
#line 343 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"

void *Jdb_kobject::kobjp;
#line 464 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"

STATIC_INITIALIZE_P(Jdb_kobject, JDB_MODULE_INIT_PRIO);
#line 611 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"

static Jdb_kobject_list::Mode INIT_PRIORITY(JDB_MODULE_INIT_PRIO) all("[ALL]", 0);

#line 215 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"


inline Kobject *
Jdb_kobject_list::next(Kobject *obj)
{
  if (!obj)
    return 0;

  Kobject_dbg::Iterator o = Kobject_dbg::Kobject_list::iter(obj->dbg_info());

  do
    {
      ++o;
      if (o == Kobject_dbg::end())
	return 0;
    }
  while (_filter && !_filter(Kobject::from_dbg(*o)));
  return Kobject::from_dbg(*o);
}

#line 234 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"


inline Kobject *
Jdb_kobject_list::prev(Kobject *obj)
{
  if (!obj)
    return 0;

  Kobject_dbg::Iterator o = Kobject_dbg::Kobject_list::iter(obj->dbg_info());

  do
    {
      --o;
      if (o == Kobject_dbg::end())
	return 0;
    }
  while (_filter && !_filter(Kobject::from_dbg(*o)));
  return Kobject::from_dbg(*o);
}

#line 131 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"


bool
Jdb_kobject_id_hdl::invoke(Kobject_common *o, Syscall_frame *f, Utcb *utcb)
{
  if (   utcb->values[0] != Op_global_id
      && utcb->values[0] != Op_kobj_to_id)
    return false;

  if (utcb->values[0] == Op_global_id)
    utcb->values[0] = o->dbg_info()->dbg_id();
  else
    utcb->values[0] = Kobject_dbg::pointer_to_id((void *)utcb->values[1]);
  f->tag(Kobject_iface::commit_result(0, 1));
  return true;
}

#line 147 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"



void *
Jdb_kobject_list::get_first()
{
  Kobject_dbg::Iterator f = Kobject_dbg::begin();
  while (f != Kobject_dbg::end() && _filter && !_filter(Kobject::from_dbg(f)))
    ++f;
  return Kobject::from_dbg(f);
}

#line 158 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"


Jdb_kobject_list::Jdb_kobject_list(Filter_func *filt)
: Jdb_list(), _current_mode(Mode::modes.end()), _filter(filt)
{ set_start(get_first()); }

#line 163 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"


Jdb_kobject_list::Jdb_kobject_list()
: Jdb_list(), _current_mode(Mode::modes.begin())
{
  if (_current_mode != Mode::modes.end())
    _filter = _current_mode->filter;

  set_start(get_first());
}

#line 173 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"


int
Jdb_kobject_list::show_item(char *buffer, int max, void *item) const
{
  return Jdb_kobject::obj_description(buffer, max, false, static_cast<Kobject*>(item)->dbg_info());
}

#line 180 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"


bool
Jdb_kobject_list::enter_item(void *item) const
{
  Kobject *o = static_cast<Kobject*>(item);
  return Jdb_kobject::module()->handle_obj(o, 1);
}

#line 188 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"


void *
Jdb_kobject_list::follow_link(void *item)
{
  Kobject *o = static_cast<Kobject*>(item);
  if (Jdb_kobject_handler *h = Jdb_kobject::module()->find_handler(o))
    return h->follow_link(o);

  return item;
}

#line 199 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"


bool
Jdb_kobject_list::handle_key(void *item, int keycode)
{
  Kobject *o = static_cast<Kobject*>(item);
  bool handled = false;
  for (Jdb_kobject::Handler_iter h = Jdb_kobject::module()->global_handlers.begin();
       h != Jdb_kobject::module()->global_handlers.end(); ++h)
    handled |= h->handle_key(o, keycode);

  if (Jdb_kobject_handler *h = Jdb_kobject::module()->find_handler(o))
    handled |= h->handle_key(o, keycode);

  return handled;
}

#line 253 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"


int
Jdb_kobject_list::seek(int cnt, void **item)
{
  Kobject *c = static_cast<Kobject*>(*item);
  int i;
  if (cnt > 0)
    {
      for (i = 0; i < cnt; ++i)
	{
	  Kobject *n = next(c);
	  if (!n)
	    break;
	  c = n;
	}
    }
  else if (cnt < 0)
    {
      for (i = 0; i < -cnt; ++i)
	{
	  Kobject *n = prev(c);
	  if (!n)
	    break;
	  c = n;
	}
    }
  else
    return 0;

  if (*item != c)
    {
      *item = c;
      return i;
    }

  return 0;
}

#line 291 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"


char const *
Jdb_kobject_list::show_head() const
{
  return "[Objects]";
}

#line 298 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"



char const *
Jdb_kobject_list::get_mode_str() const
{
  if (_current_mode == Mode::modes.end())
    return "[Objects]";
  return _current_mode->name;
}

#line 308 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"




void
Jdb_kobject_list::next_mode()
{
  if (_current_mode == Mode::modes.end())
    return;

  ++_current_mode;
  if (_current_mode == Mode::modes.end())
    _current_mode = Mode::modes.begin();

  _filter = _current_mode->filter;
}

#line 324 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"

/* When the mode changes the current object may get invisible,
 * get a new visible one */

void *
Jdb_kobject_list::get_valid(void *o)
{
  if (!_filter)
    return o;

  if (_filter && _filter(static_cast<Kobject*>(o)))
    return o;
  return get_first();
}

#line 338 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"


bool
Jdb_kobject_handler::invoke(Kobject_common *, Syscall_frame *, Utcb *)
{ return false; }

#line 345 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"


Jdb_kobject::Jdb_kobject()
  : Jdb_module("INFO")
{}

#line 350 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"



void
Jdb_kobject::register_handler(Jdb_kobject_handler *h)
{
  if (h->is_global())
    global_handlers.push_back(h);
  else
    handlers.push_back(h);
}

#line 361 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"


Jdb_kobject_handler *
Jdb_kobject::find_handler(Kobject_common *o)
{
  for (Handler_iter h = handlers.begin(); h != handlers.end(); ++h)
    if (o->kobj_type() == h->kobj_type)
      return *h;

  return 0;
}

#line 372 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"


bool
Jdb_kobject::handle_obj(Kobject *o, int lvl)
{
  if (Jdb_kobject_handler *h = find_handler(o))
    return h->show_kobject(o, lvl);

  return true;
}

#line 382 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"


char const *
Jdb_kobject::kobject_type(Kobject_common *o)
{
  if (Jdb_kobject_handler *h = module()->find_handler(o))
    return h->kobject_type();

  return o->kobj_type();
}

#line 392 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"



int
Jdb_kobject::obj_description(char *buffer, int max, bool dense, Kobject_dbg *o)
{
  int pos = snprintf(buffer, max,
                     dense ? "%lx %lx [%-*s]" : "%8lx %08lx [%-*s]",
                     o->dbg_id(), (Mword)Kobject::from_dbg(o), 7, kobject_type(Kobject::from_dbg(o)));

  for (Handler_iter h = module()->global_handlers.begin();
       h != module()->global_handlers.end(); ++h)
    pos += h->show_kobject_short(buffer + pos, max-pos, Kobject::from_dbg(o));

  if (Jdb_kobject_handler *oh = Jdb_kobject::module()->find_handler(Kobject::from_dbg(o)))
    pos += oh->show_kobject_short(buffer + pos, max-pos, Kobject::from_dbg(o));

  return pos;
}

#line 411 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"


void
Jdb_kobject::print_kobj(Kobject *o)
{
  printf("%p [type=%s]", o, o->kobj_type());
}

#line 418 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"


Jdb_module::Action_code
Jdb_kobject::action(int cmd, void *&, char const *&, int &)
{
  if (cmd == 0)
    {
      puts("");
      Kobject_dbg::Iterator i = Kobject_dbg::pointer_to_obj(kobjp);
      if (i == Kobject_dbg::end())
	printf("Not a kobj.\n");
      else
        {
          Kobject *k = Kobject::from_dbg(i);
          if (!handle_obj(k, 0))
            printf("Kobj w/o handler: ");
          print_kobj(k);
          puts("");
        }
      return NOTHING;
    }
  else if (cmd == 1)
    {
      Jdb_kobject_list list;
      list.do_list();
    }
  return NOTHING;
}

#line 446 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"


Jdb_module::Cmd const *
Jdb_kobject::cmds() const
{
  static Cmd cs[] =
    {
	{ 0, "K", "kobj", "%p", "K<kobj_ptr>\tshow information for kernel object", 
	  &kobjp },
	{ 1, "Q", "listkobj", "", "Q\tshow information for kernel objects", 0 },
    };
  return cs;
}

#line 459 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"


int
Jdb_kobject::num_cmds() const
{ return 2; }

#line 466 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"


int
Jdb_kobject::fmt_handler(char /*fmt*/, int *size, char const *cmd_str, void *arg)
{
  char buffer[20];

  int pos = 0;
  int c;
  Address n;

  *size = sizeof(void*);

  while((c = Jdb_core::cmd_getchar(cmd_str)) != ' ' && c!=KEY_RETURN)
    {
      if(c==KEY_ESC)
	return 3;

      if(c==KEY_BACKSPACE && pos>0)
	{
	  putstr("\b \b");
	  --pos;
	}

      if (pos < (int)sizeof(buffer) - 1)
	{
	  putchar(c);
	  buffer[pos++] = c;
	  buffer[pos] = 0;
	}
    }

  Kobject **a = (Kobject**)arg;

  if (!pos)
    {
      *a = 0;
      return 0;
    }

  char const *num = buffer;
  if (buffer[0] == 'P')
    num = buffer + 1;

  n = strtoul(num, 0, 16);

  Kobject_dbg::Iterator ko;

  if (buffer[0] != 'P')
    ko = Kobject_dbg::id_to_obj(n);
  else
    ko = Kobject_dbg::pointer_to_obj((void*)n);

  if (ko != Kobject_dbg::end())
    *a = Kobject::from_dbg(ko);
  else
    *a = 0;

  return 0;
}

#line 526 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"


void
Jdb_kobject::init()
{
  module();

  Jdb_core::add_fmt_handler('q', fmt_handler);

//  static Jdb_handler enter(at_jdb_enter);

  static Jdb_kobject_id_hdl id_hdl;
  module()->register_handler(&id_hdl);
}

#line 540 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"


Jdb_kobject *
Jdb_kobject::module()
{
  static Jdb_kobject jdb_kobj_module;
  return &jdb_kobj_module;
}

#line 548 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"

// Be robust if this object is invalid

void
Jdb_kobject::print_uid(Kobject_common *o, int task_format)
{
  if (!o)
    {
      printf("%*.s", task_format, "---");
      return;
    }

  if (Kobject_dbg::is_kobj(o))
    {
      printf("%*.lx", task_format, o->dbg_info()->dbg_id());
      return;
    }

  printf("\033[31;1m%*s%p\033[m", task_format, "???", o);
  return;
}

#line 569 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"


extern "C" void
sys_invoke_debug(Kobject_iface *o, Syscall_frame *f)
{
  if (!o)
    {
      f->tag(Kobject_iface::commit_result(-L4_err::EInval));
      return;
    }

  Utcb *utcb = current_thread()->utcb().access();
  //printf("sys_invoke_debug: [%p] -> %p\n", o, f);
  Jdb_kobject_handler *h = Jdb_kobject::module()->find_handler(o);
  if (h && h->invoke(o, f, utcb))
    return;

  for (Jdb_kobject::Handler_iter i = Jdb_kobject::module()->global_handlers.begin();
       i != Jdb_kobject::module()->global_handlers.end(); ++i)
    if (i->invoke(o, f, utcb))
      return;

  f->tag(Kobject_iface::commit_result(-L4_err::ENosys));
}
