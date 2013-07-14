// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_thread_list.h"
#include "jdb_thread_list_i.h"

#line 43 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

char Jdb_thread_list::subcmd;
#line 45 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
char Jdb_thread_list::long_output;
#line 46 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
Cpu_number Jdb_thread_list::cpu;
#line 47 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"


// available from the jdb_tcb module
extern int jdb_show_tcb(Thread* thread, int level)
  __attribute__((weak));
#line 52 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

char Jdb_thread_list::_pr;
#line 54 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
int  Jdb_thread_list::_mode = LIST_SORT_TID;
#line 55 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
int  Jdb_thread_list::_count;
#line 56 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

Thread *Jdb_thread_list::_t_head;
#line 58 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
Thread *Jdb_thread_list::_t_start;
#line 291 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

// --------------------------------------------------------------------------

#line 871 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

static Jdb_thread_list jdb_list_threads INIT_PRIORITY(JDB_MODULE_INIT_PRIO);

#line 67 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

// return string describing current sorting mode of list

inline const char*
Jdb_thread_list::get_mode_str(void)
{
  static const char * const mode_str[] =
    { "(unsorted)", "(prio-sorted)", "(tid-sorted)", "(space-sorted)" };

  return mode_str[_mode];
}

#line 315 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"


inline Sched_context *
Jdb_thread_list::sc_iter_prev(Sched_context *t)
{ return sc_fp_iter_prev<Jdb_thread_list_policy<Ready_queue_fp<Sched_context> > >(t); }

#line 320 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"


inline Sched_context *
Jdb_thread_list::sc_iter_next(Sched_context *t)
{ return sc_fp_iter_next<Jdb_thread_list_policy<Ready_queue_fp<Sched_context> > >(t); }

#line 376 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"



inline Thread*
Jdb_thread_list::iter_prev(Thread *t)
{
  if (_pr == 'p')
    {
      Kobject_dbg::Iterator o = Kobject_dbg::Kobject_list::iter(t->dbg_info());
      do
	{
	  --o;
	  if (o == Kobject_dbg::end())
	    --o;
	}
      while (!Kobject::dcast<Thread*>(Kobject::from_dbg(*o)));
      return Kobject::dcast<Thread*>(Kobject::from_dbg(*o));
    }
  else
    return static_cast<Thread*>(sc_iter_prev(t->sched())->context());
}

#line 397 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"



inline Thread*
Jdb_thread_list::iter_next(Thread *t)
{
  if (_pr == 'p')
    {
      Kobject_dbg::Iterator o = Kobject_dbg::Kobject_list::iter(t->dbg_info());
      do
	{
	  ++o;
	  if (o == Kobject_dbg::end())
	    ++o;
	}
      while (!Kobject::dcast<Thread*>(Kobject::from_dbg(*o)));
      return Kobject::dcast<Thread*>(Kobject::from_dbg(*o));
    }
  else
    return static_cast<Thread*>(sc_iter_next(t->sched())->context());
}

#line 59 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"


void
Jdb_thread_list::init(char pr, Thread *t_head)
{
  _pr = pr;
  _t_head = t_head;
}

#line 78 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

// switch to next sorting mode

void
Jdb_thread_list::switch_mode(void)
{
  if (++_mode >= LIST_SORT_END)
    _mode = LIST_UNSORTED;
}

#line 87 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

// set _t_start element of list

void
Jdb_thread_list::set_start(Thread *t_start)
{
  _t_start = t_start;
  iter(+Jdb_screen::height()-3, &_t_start);
  iter(-Jdb_screen::height()+3, &_t_start);
}

#line 97 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

// _t_start-- if possible

int
Jdb_thread_list::line_back(void)
{
  return iter(-1, &_t_start);
}

#line 105 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

// _t_start++ if possible

int
Jdb_thread_list::line_forw(void)
{
  Thread *t = _t_start;
  iter(+Jdb_screen::height()-2, &_t_start);
  iter(-Jdb_screen::height()+3, &_t_start);
  return t != _t_start;
}

#line 116 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

// _t_start -= 24 if possible

int
Jdb_thread_list::page_back(void)
{
  return iter(-Jdb_screen::height()+2, &_t_start);
}

#line 124 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

// _t_start += 24 if possible

int
Jdb_thread_list::page_forw(void)
{
  Thread *t = _t_start;
  iter(+Jdb_screen::height()*2-5, &_t_start);
  iter(-Jdb_screen::height()  +3, &_t_start);
  return t != _t_start;
}

#line 135 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

// _t_start = first element of list

int
Jdb_thread_list::goto_home(void)
{
  return iter(-9999, &_t_start);
}

#line 143 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

// _t_start = last element of list

int
Jdb_thread_list::goto_end(void)
{
  Thread *t = _t_start;
  iter(+9999, &_t_start);
  iter(-Jdb_screen::height()+2, &_t_start);
  return t != _t_start;
}

#line 154 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

// search index of t_search starting from _t_start

int
Jdb_thread_list::lookup(Thread *t_search)
{
  unsigned i;
  Thread *t;

  for (i=0, t=_t_start; i<Jdb_screen::height()-3; i++)
    {
      if (t == t_search)
	break;
      iter(+1, &t);
    }

  return i;
}

#line 172 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

// get y'th element of thread list starting from _t_start

Thread*
Jdb_thread_list::index(int y)
{
  Thread *t = _t_start;

  iter(y, &t);
  return t;
}

#line 183 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

// helper function for iter() -- use priority as sorting key

long
Jdb_thread_list::get_prio(Thread *t)
{
  return t->sched()->prio();
}

#line 191 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

// helper function for iter() -- use thread id as sorting key

long
Jdb_thread_list::get_tid(Thread *t)
{
  return t->dbg_info()->dbg_id();
}

#line 199 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

// helper function for iter() -- use space as sorting key

long
Jdb_thread_list::get_space_dbgid(Thread *t)
{
  return Kobject_dbg::pointer_to_id(t->space());
}

#line 418 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

// walk though list <count> times
// abort walking if no more elements
// do iter if iter != 0

bool
Jdb_thread_list::iter(int count, Thread **t_start,
		      void (*iter)(Thread *t))
{
  int i = 0;
  int forw = (count >= 0);
  Thread *t, *t_new = *t_start, *t_head = _t_head;
  long (*get_key)(Thread *t) = 0;

  if (count == 0)
    return false;  // nothing changed

  if (count < 0)
    count = -count;

  // if we are stepping backwards, begin at end-of-list
  if (!forw)
    t_head = iter_prev(t_head);

  switch (_mode)
    {
    case LIST_UNSORTED:
      // list threads in order of list
      if (iter)
	iter(*t_start);

      t = *t_start;
      do
	{
	  t = forw ? iter_next(t) : iter_prev(t);

	  if (t == t_head)
	    break;

	  if (iter)
	    iter(t);

	  t_new = t;
	  i++;

	} while (i < count);
      break;

    case LIST_SORT_PRIO:
      // list threads sorted by priority
    case LIST_SORT_SPACE:
      // list threads sorted by space
      if (!get_key)
	get_key = (_mode == LIST_SORT_SPACE) ? get_space_dbgid : get_prio;

      // fall through

    case LIST_SORT_TID:
      // list threads sorted by thread id
	{
	  long key;
	  int start_skipped = 0;

	  if (!get_key)
	    get_key = get_tid;

	  long key_current = get_key(*t_start);
	  long key_next = (forw) ? LONG_MIN : LONG_MAX;
          t = t_head;
	  if (iter)
	    iter(*t_start);
	  do
	    {
	      if (t == *t_start)
		start_skipped = 1;

	      key = get_key(t);
	      // while walking through the current list, look for next key
	      if (   ( forw && (key > key_next) && (key < key_current))
		  || (!forw && (key < key_next) && (key > key_current)))
		key_next = key;

              if (t_head == (t = (forw) ? iter_next(t) : iter_prev(t)))
		{
		  if (   ( forw && (key_next == LONG_MIN))
		      || (!forw && (key_next == LONG_MAX)))
		    break;
		  key_current = key_next;
		  key_next = forw ? LONG_MIN : LONG_MAX;
                }

	      if (start_skipped && (get_key(t) == key_current))
		{
		  if (iter)
		    iter(t);

		  i++;
		  t_new = t;
		}
	    } while (i < count);
	}
      break;
    }

  _count = i;

  bool changed = (*t_start != t_new);
  *t_start = t_new;

  return changed;
}

#line 529 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

// show complete page using show callback function

int
Jdb_thread_list::page_show(void (*show)(Thread *t))
{
  Thread *t = _t_start;

  iter(Jdb_screen::height()-3, &t, show);
  return _count;
}

#line 540 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

// show complete list using show callback function

int
Jdb_thread_list::complete_show(void (*show)(Thread *t))
{
  Thread *t = _t_start;

  iter(9999, &t, show);
  return _count;
}

#line 551 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"


Jdb_thread_list::Jdb_thread_list()
  : Jdb_module("INFO")
{}

#line 556 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"


Jdb_module::Action_code
Jdb_thread_list::action(int cmd, void *&argbuf, char const *&fmt, int &)
{
  static char const *const cpu_fmt = " cpu=%i\n";
  static char const *const nfmt = "";
  if (cmd == 0)
    {
      if (fmt != cpu_fmt && fmt != nfmt)
	{
	  if (subcmd == 'c')
	    {
	      argbuf = &cpu;
	      fmt = cpu_fmt;
	    }
	  else
	    fmt = nfmt;
	  return EXTRA_INPUT;
	}

      Thread *t = Jdb::get_current_active();
      switch (subcmd)
	{
        case 'r': cpu = Cpu_number::first(); list_threads(t, 'r'); break;
	case 'p': list_threads(t, 'p'); break;
	case 'c':
		  if (Cpu::online(cpu))
		    list_threads(Jdb::get_thread(cpu), 'r');
		  else
		    printf("\nCPU %u is not online!\n", Cpu_number::val(cpu));
		  cpu = Cpu_number::first();
		  break;
	case 't': Jdb::execute_command("lt"); break; // other module
	case 's': Jdb::execute_command("ls"); break; // other module
	}
    }
  else if (cmd == 1)
    {
      Console *gzip = Kconsole::console()->find_console(Console::GZIP);
      if (gzip)
	{
	  Thread *t = Jdb::get_current_active();
	  gzip->state(gzip->state() | Console::OUTENABLED);
	  long_output = 1;
	  Jdb_thread_list::init('p', t);
	  Jdb_thread_list::set_start(t);
	  Jdb_thread_list::goto_home();
	  Jdb_thread_list::complete_show(list_threads_show_thread);
	  long_output = 0;
	  gzip->state(gzip->state() & ~Console::OUTENABLED);
	}
      else
	puts(" gzip module not available");
    }

  return NOTHING;
}

#line 630 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

void
Jdb_thread_list::list_threads_show_thread(Thread *t)
{
  char to[24];
  int  waiting_for = 0;

  *to = '\0';

  Kconsole::console()->getchar_chance();

  Jdb_kobject::print_uid(t, 5);

  printf(" %-3u ", cxx::int_value<Cpu_number>(t->cpu()));

  print_thread_name(t);

  printf("  %2lx ", get_prio(t));

  if (get_space_dbgid(t) == ~0L)
    printf(" ----- ");
  else
    printf(" %5lx ", get_space_dbgid(t));

  if (Jdb_thread::has_partner(t))
    {
      Jdb_thread::print_partner(t, 5);
      waiting_for = 1;
    }
  else if (Jdb_thread::has_snd_partner(t))
    {
      Jdb_thread::print_snd_partner(t, 5);
      putchar(' ');
      waiting_for = 1;
    }
  else
    putstr("      ");

  if (waiting_for)
    {
      if (t->_timeout && t->_timeout->is_set())
	{
	  Signed64 diff = (t->_timeout->get_timeout(Kip::k()->clock));
	  if (diff < 0)
	    strcpy(to, " over");
	  else if (diff >= 100000000LL)
	    strcpy(to, " >99s");
	  else
	    {
	      int us = (int)diff;
	      if (us < 0)
		us = 0;
	      if (us >= 1000000)
		snprintf(to, sizeof(to), " %3us", us / 1000000);
	      else if (us >= 1000)
		snprintf(to, sizeof(to), " %3um", us / 1000);
	      else
		snprintf(to, sizeof(to), " %3u%c", us, Config::char_micro);
	    }
	}
    }

  printf("%-6s", to);

  if (long_output)
    {
      Jdb_thread::print_state_long(t, 47);
      putchar('\n');
    }
  else
    {
      if (Config::Stack_depth)
	{
	  Mword i, stack_depth;
	  char *c  = (char*)t + sizeof (Thread);
	  for (i = sizeof (Thread), stack_depth = Context::Size;
	      i < Context::Size;
	      i++, stack_depth--, c++)
	    if (*c != '5')
	      break;

	  printf("(%4ld) ", stack_depth - sizeof (Thread));
	  Jdb_thread::print_state_long(t, 23);
	}
      else
	Jdb_thread::print_state_long(t, 30);
      putstr("\033[K\n");
    }
}

#line 719 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

void
Jdb_thread_list::show_header()
{
  Jdb::cursor();
  printf("%s   id cpu name             pr     sp  wait    to%s state\033[m\033[K",
         Jdb::esc_emph, Config::Stack_depth ? "  stack" : "");
}

#line 727 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

void
Jdb_thread_list::list_threads(Thread *t_start, char pr)
{
  unsigned y, y_max;
  Thread *t, *t_current = t_start;

    {
      // Hm, we are in JDB, however we have to make the assertion in
      // ready_enqueue happy.
      auto g = lock_guard(cpu_lock);
      // enqueue current, which may not be in the ready list due to lazy queueing
      if (!t_current->in_ready_list())
        Sched_context::rq.cpu(t_current->cpu()).ready_enqueue(t_current->sched());
    }

  Jdb::clear_screen();
  show_header();
  Jdb_thread_list::init(pr, t_current);

  for (;;)
    {
      Jdb_thread_list::set_start(t_current);

      // set y to position of t_current in current displayed list
      y = Jdb_thread_list::lookup(t_current);

      for (bool resync=false; !resync;)
	{
	  Jdb::cursor(2, 1);
	  y_max = Jdb_thread_list::page_show(list_threads_show_thread);

	  // clear rest of screen (if where less than 24 lines)
	  for (unsigned i=y_max; i < Jdb_screen::height()-3; i++)
            putstr("\033[K\n");

	  Jdb::printf_statline(pr=='r' ? "ready list" : "present list",
			       "<Space>=mode " /*"<Tab>=partner "*/ "<CR>=select",
			       "%-15s", Jdb_thread_list::get_mode_str());

	  // key event loop
	  for (bool redraw=false; !redraw; )
	    {
	      Jdb::cursor(y+2, 6);
	      switch (int c=Jdb_core::getchar())
		{
		case KEY_CURSOR_UP:
		case 'k':
		  if (y > 0)
		    y--;
		  else
		    redraw = Jdb_thread_list::line_back();
		  break;
		case KEY_CURSOR_DOWN:
		case 'j':
		  if (y < y_max)
		    y++;
		  else
		    redraw = Jdb_thread_list::line_forw();
		  break;
		case KEY_PAGE_UP:
		case 'K':
		  if (!(redraw = Jdb_thread_list::page_back()))
		    y = 0;
		  break;
		case KEY_PAGE_DOWN:
		case 'J':
		  if (!(redraw = Jdb_thread_list::page_forw()))
		    y = y_max;
		  break;
		case KEY_CURSOR_HOME:
		case 'H':
		  redraw = Jdb_thread_list::goto_home();
		  y = 0;
		  break;
		case KEY_CURSOR_END:
		case 'L':
		  redraw = Jdb_thread_list::goto_end();
		  y = y_max;
		  break;
		case ' ': // switch mode
		  t_current = Jdb_thread_list::index(y);
		  Jdb_thread_list::switch_mode();
		  redraw = true;
		  resync = true;
		  break;
#if 0
		case KEY_TAB: // goto thread we are waiting for
		  t = Jdb_thread_list::index(y);
		  if (t->partner()
		      && (t->state(false) & (Thread_receiving |
					Thread_busy  |
					Thread_rcvlong_in_progress))
		      && (!t->partner()->id().is_irq() ||
		           t->partner()->id().irq() > Config::Max_num_dirqs))
		    {
		      t_current = static_cast<Thread*>(t->partner());
		      redraw = true;
		      resync = true;
		    }
		  break;
#endif
		case KEY_RETURN: // show current tcb
		  if (jdb_show_tcb != 0)
		    {
		      t = Jdb_thread_list::index(y);
		      if (!jdb_show_tcb(t, 1))
			return;
		      show_header();
		      redraw = 1;
		    }
		  break;
		case KEY_ESC:
		  Jdb::abort_command();
		  return;
		default:
		  if (Jdb::is_toplevel_cmd(c)) 
		    return;
		}
	    }
	}
    }
}

#line 850 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"



Jdb_module::Cmd const *
Jdb_thread_list::cmds() const
{
  static Cmd cs[] =
    {
	{ 0, "l", "list", "%C", "l{r|p}\tshow ready/present list", &subcmd },
        { 1, "lgzip", "", "", 0 /* invisible */, 0 },
    };

  return cs;
}

#line 864 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"


int
Jdb_thread_list::num_cmds() const
{
  return 2;
}
