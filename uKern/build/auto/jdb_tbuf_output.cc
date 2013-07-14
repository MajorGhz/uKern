// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_tbuf_output.h"
#include "jdb_tbuf_output_i.h"


#line 45 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"
static void
console_log_entry(Tb_entry *e, const char *);

#line 136 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"
static unsigned
formatter_default(Tb_entry *tb, const char *tidstr, unsigned tidlen,
		 char *buf, int maxlen);
#line 40 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"


Jdb_tbuf_output::Format_entry_fn *Jdb_tbuf_output::_format_entry_fn[Tbuf_dynentries];
#line 43 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"
bool Jdb_tbuf_output::show_names;
#line 83 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"

STATIC_INITIALIZE(Jdb_tbuf_output);

#line 44 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"

static void
console_log_entry(Tb_entry *e, const char *)
{
  static char log_message[80];

  // disable all interrupts to stop other threads
  Watchdog::disable();
  Proc::Status s = Proc::cli_save();

  Jdb_tbuf_output::print_entry(e, log_message, sizeof(log_message));
  printf("%s\n", log_message);

  // do not use getchar here because we ran cli'd
  // and getchar may do halt
  int c;
  Jdb::enter_getchar();
  while ((c=Kconsole::console()->getchar(false)) == -1)
    Proc::pause();
  Jdb::leave_getchar();
  if (c == 'i')
    kdb_ke("LOG");
  if (c == '^')
    terminate(1);

  // enable interrupts we previously disabled
  Proc::sti_restore(s);
  Watchdog::enable();
}

#line 73 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"


unsigned
Jdb_tbuf_output::dummy_format_entry(Tb_entry *tb, const char *, unsigned,
				     char *buf, int maxlen)
{
  int len = snprintf(buf, maxlen,
      " << no format_entry_fn for type %d registered >>", tb->type());
  return len >= maxlen ? maxlen-1 : len;
}

#line 85 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"


void FIASCO_INIT
Jdb_tbuf_output::init()
{
  unsigned i;

  Jdb_tbuf::direct_log_entry = &console_log_entry;
  for (i=0; i<sizeof(_format_entry_fn)/sizeof(_format_entry_fn[0]); i++)
    if (!_format_entry_fn[i])
      _format_entry_fn[i] = dummy_format_entry;
}

#line 97 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"


void
Jdb_tbuf_output::register_ff(Unsigned8 type, Format_entry_fn format_entry_fn)
{
  assert(type < Tbuf_dynentries);

  if (   (_format_entry_fn[type] != 0)
      && (_format_entry_fn[type] != dummy_format_entry))
    panic("format entry function for type %d already registered", type);

  _format_entry_fn[type] = format_entry_fn;
}

#line 110 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"

// return thread+ip of entry <e_nr>

int
Jdb_tbuf_output::thread_ip(int e_nr, Thread const **th, Mword *ip)
{
  Tb_entry *e = Jdb_tbuf::lookup(e_nr);

  if (!e)
    return false;

  *th = static_cast<Thread const *>(e->ctx());

  *ip = e->ip();

  return true;
}

#line 127 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"


void
Jdb_tbuf_output::toggle_names()
{
  show_names = !show_names;
}

#line 134 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"


static unsigned
formatter_default(Tb_entry *tb, const char *tidstr, unsigned tidlen,
		 char *buf, int maxlen)
{
  if (tb->type() < Tbuf_dynentries)
    return 0;

  int idx = tb->type()-Tbuf_dynentries;

  Tb_entry_formatter *fmt = _log_table[idx].fmt;
  char const *sc = _log_table[idx].name;
  sc += strlen(sc) + 1;

  unsigned l = snprintf(buf, maxlen, "%-3s: %-*s ", sc, tidlen, tidstr);
  buf += l;
  maxlen -= l;

  if (!fmt)
    {
      Tb_entry_ke_reg *e = static_cast<Tb_entry_ke_reg*>(tb);
      char ip_buf[32];
      snprintf(ip_buf, sizeof(ip_buf), " @ " L4_PTR_FMT, e->ip());
      snprintf(buf, maxlen, "\"%s\" "
               L4_PTR_FMT " " L4_PTR_FMT " " L4_PTR_FMT "%s",
               e->msg(), e->v[0], e->v[1], e->v[2],
               e->ip() ? ip_buf : "");

      return maxlen;
    }

  return fmt->print(tb, maxlen, buf);
}

#line 168 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"


void
Jdb_tbuf_output::print_entry(int e_nr, char *buf, int maxlen)
{
  Tb_entry *tb = Jdb_tbuf::lookup(e_nr);

  if (tb)
    print_entry(tb, buf, maxlen);
}

#line 178 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"


void
Jdb_tbuf_output::print_entry(Tb_entry *tb, char *buf, int maxlen)
{
  assert(tb->type() < Tbuf_max);

  char tidstr[32];
  Thread const *t = static_cast<Thread const *>(tb->ctx());

  if (!t || !Kobject_dbg::is_kobj(t))
    strcpy(tidstr, "????");
  else
    {
      Jdb_kobject_name *ex
        = Jdb_kobject_extension::find_extension<Jdb_kobject_name>(t);
      if (show_names && ex)
        snprintf(tidstr, sizeof(tidstr), "%04lx %-*.*s", t->dbg_info()->dbg_id(), ex->max_len(), ex->max_len(), ex->name());
      else
        snprintf(tidstr, sizeof(tidstr), "%04lx", t->dbg_info()->dbg_id());
    }

  if (Config::Max_num_cpus > 1)
    {
      snprintf(buf, maxlen, Config::Max_num_cpus > 16 ? "%02d " : "%d ", tb->cpu());
      buf    += 2 + (Config::Max_num_cpus > 16);
      maxlen -= 2 + (Config::Max_num_cpus > 16);
    }

  unsigned len;

  if (tb->type() >= Tbuf_dynentries)
    len = formatter_default(tb, tidstr, show_names ? 21 : 4, buf, maxlen);
  else
    len = _format_entry_fn[tb->type()](tb, tidstr,
                                       show_names ? 21 : 4, buf, maxlen);

  // terminate string
  buf += maxlen-len;
  while (len--)
    *buf++ = ' ';
  buf[-1] = '\0';
}

#line 221 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"


bool
Jdb_tbuf_output::set_filter(const char *filter_str, Mword *entries)
{
  if (*filter_str && Jdb_regex::avail() && !Jdb_regex::start(filter_str))
    return false;

  if (!*filter_str)
    {
      for (Mword n=0; n<Jdb_tbuf::unfiltered_entries(); n++)
	Jdb_tbuf::unfiltered_lookup(n)->unhide();

      Jdb_tbuf::disable_filter();
      if (entries)
	*entries = Jdb_tbuf::unfiltered_entries();
      return true;
    }

  Mword cnt = 0;

  for (Mword n=0; n<Jdb_tbuf::unfiltered_entries(); n++)
    {
      Tb_entry *e = Jdb_tbuf::unfiltered_lookup(n);
      char s[80];

      print_entry(e, s, sizeof(s));
      if (Jdb_regex::avail())
	{
	  if (Jdb_regex::find(s, 0, 0))
	    {
	      e->unhide();
	      cnt++;
	      continue;
	    }
	}
      else
	{
	  if (strstr(s, filter_str))
	    {
	      e->unhide();
	      cnt++;
	      continue;
	    }
	}
      e->hide();
    }

  if (entries)
    *entries = cnt;
  Jdb_tbuf::enable_filter();
  return true;
}
