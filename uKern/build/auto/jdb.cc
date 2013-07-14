// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb.h"
#include "jdb_i.h"

#line 77 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"

//---------------------------------------------------------------------------

#line 96 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"

KIP_KERNEL_FEATURE("jdb");
#line 98 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"

Jdb_handler_queue Jdb::jdb_enter;
#line 100 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
Jdb_handler_queue Jdb::jdb_leave;
#line 101 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"

DEFINE_PER_CPU Per_cpu<char[81]> Jdb::error_buffer;
#line 103 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
char Jdb::next_cmd;			// next global command to execute
#line 104 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
char Jdb::last_cmd;
#line 105 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"

char Jdb::hide_statline;		// show status line on enter_kdebugger
#line 107 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
DEFINE_PER_CPU Per_cpu<Jdb_entry_frame*> Jdb::entry_frame;
#line 108 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
Cpu_number Jdb::current_cpu;              // current CPU JDB is running on
#line 109 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
Thread *Jdb::current_active;		// current running thread
#line 110 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
bool Jdb::was_input_error;		// error in command sequence
#line 111 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"

DEFINE_PER_CPU Per_cpu<void (*)(Cpu_number, void *)> Jdb::remote_func;
#line 113 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
DEFINE_PER_CPU Per_cpu<void *> Jdb::remote_func_data;
#line 114 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
DEFINE_PER_CPU Per_cpu<bool> Jdb::remote_func_running;
#line 115 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"

// holds all commands executable in top level (regardless of current mode)
const char *Jdb::toplevel_cmds = "j_";
#line 118 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"

// a short command must be included in this list to be enabled for non-
// interactive execution
const char *Jdb::non_interactive_cmds = "bEIJLMNOPSU^Z";
#line 122 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"

DEFINE_PER_CPU Per_cpu<bool> Jdb::running;	// JDB is already running
#line 124 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
bool Jdb::never_break;		// never enter JDB
#line 125 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
bool Jdb::jdb_active;
#line 126 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
bool Jdb::in_service;
#line 127 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
bool Jdb::leave_barrier;
#line 128 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
unsigned long Jdb::cpus_in_debugger;
#line 930 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"

static Jdb_base_cmds jdb_base_cmds INIT_PRIORITY(JDB_MODULE_INIT_PRIO);
#line 988 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"

//---------------------------------------------------------------------------

#line 994 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"

char Jdb::esc_iret[]     = "\033[36;1m";
#line 996 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
char Jdb::esc_bt[]       = "\033[31m";
#line 997 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
char Jdb::esc_emph[]     = "\033[33;1m";
#line 998 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
char Jdb::esc_emph2[]    = "\033[32;1m";
#line 999 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
char Jdb::esc_mark[]     = "\033[35;1m";
#line 1000 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
char Jdb::esc_line[]     = "\033[37m";
#line 1001 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
char Jdb::esc_symbol[]   = "\033[33;1m";
#line 1138 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


//--------------------------------------------------------------------------


#line 129 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"



bool
Jdb::cpu_in_jdb(Cpu_number cpu)
{ return Cpu::online(cpu) && running.cpu(cpu); }

#line 186 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"

/** Command aborted. If we are interpreting a debug command like
 *  enter_kdebugger("*#...") this is an error
 */

void
Jdb::abort_command()
{
  cursor(Jdb_screen::height(), 6);
  clear_to_eol();

  was_input_error = true;
}

#line 199 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


// go to bottom of screen and print some text in the form "jdb: ..."
// if no text follows after the prompt, prefix the current thread number

void
Jdb::printf_statline(const char *prompt, const char *help,
                     const char *format, ...)
{
  cursor(Jdb_screen::height(), 1);
  unsigned w = Jdb_screen::width();
  prompt_start();
  if (prompt)
    {
      putstr(prompt);
      putstr(": ");
      w -= strlen(prompt) + 2;
    }
  else
    {
      Jdb::prompt();
      w -= Jdb::prompt_len();
    }
  prompt_end();
  // work around for ealier gccs complaining about "empty format strings"
  if (format && (format[0] != '_' || format[1] != '\0'))
    {
      char s[w];
      va_list list;
      va_start(list, format);
      vsnprintf(s, sizeof(s), format, list);
      va_end(list);
      s[sizeof(s) - 1] = 0;
      putstr(s);
      w -= print_len(s);
    }
  if (help && print_len(help) < w)
    printf("%*.*s", w, w, help);
  else
    clear_to_eol();
}

#line 240 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


bool Jdb::is_toplevel_cmd(char c)
{
  char cm[] = {c, 0};
  Jdb_core::Cmd cmd = Jdb_core::has_cmd(cm);

  if (cmd.cmd || (0 != strchr(toplevel_cmds, c)))
    {
      set_next_cmd(c);
      return true;
    }

  return false;
}

#line 255 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"



int
Jdb::execute_command(const char *s, int first_char)
{
  Jdb_core::Cmd cmd = Jdb_core::has_cmd(s);

  if (cmd.cmd)
    return Jdb_core::exec_cmd(cmd, 0, first_char) == 2 ? 1 : 0;

  return 0;
}

#line 268 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


Push_console *
Jdb::push_cons()
{
  static Push_console c;
  return &c;
}

#line 276 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"

// Interprete str as non interactive commands for Jdb. We allow mostly 
// non-interactive commands here (e.g. we don't allow d, t, l, u commands)

int
Jdb::execute_command_ni(Space *task, char const *str, int len)
{
  char tmp = 0;
  for (; len && peek(str, task, tmp) && tmp; ++str, --len)
    if ((unsigned char)tmp != 0xff)
      push_cons()->push(tmp);

  if ((unsigned char)tmp != 0xff)
    push_cons()->push('_'); // terminating return


  // prevent output of sequences
  Kconsole::console()->change_state(0, 0, ~Console::OUTENABLED, 0);

  for (;;)
    {
      int c = getchar();

      was_input_error = true;
      if (0 != strchr(non_interactive_cmds, c))
	{
	  char _cmd[] = {(char)c, 0};
	  Jdb_core::Cmd cmd = Jdb_core::has_cmd(_cmd);

	  if (cmd.cmd)
	    {
	      if (Jdb_core::exec_cmd (cmd, 0) != 3)
                was_input_error = false;
	    }
	}

      if (c == KEY_RETURN || c == ' ' || was_input_error)
	{
	  push_cons()->flush();
	  // re-enable all consoles but GZIP
	  Kconsole::console()->change_state(0, Console::GZIP,
					    ~0U, Console::OUTENABLED);
	  return c == KEY_RETURN || c == ' ';
	}
    }
}

#line 322 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


bool
Jdb::input_short_mode(Jdb::Cmd *cmd, char const **args, int &cmd_key)
{
  *args = 0;
  for (;;)
    {
      int c;
      do
	{
	  if ((c = get_next_cmd()))
	    set_next_cmd(0);
	  else
	    c = getchar();
	}
      while (c < ' ' && c != KEY_RETURN);

      if (c == KEY_F1)
	c = 'h';

      printf("\033[K%c", c); // clreol + print key

      char cmd_buffer[2] = { (char)c, 0 };

      *cmd = Jdb_core::has_cmd(cmd_buffer);
      if (cmd->cmd)
	{
	  cmd_key = c;
	  return false; // do not leave the debugger
	}
      else if (!handle_special_cmds(c))
	return true; // special command triggered a JDB leave
      else if (c == KEY_RETURN)
	{
	  hide_statline = false;
	  cmd_key = c;
	  return false;
	}
    }
}

#line 415 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"



bool
Jdb::input_long_mode(Jdb::Cmd *cmd, char const **args)
{
  static Cmd_buffer buf;
  buf.flush();
  for (;;)
    {
      int c = getchar();

      switch (c)
	{
	case KEY_BACKSPACE:
	  if (buf.len() > 0)
	    {
	      cursor(Cursor_left);
	      clear_to_eol();
	      buf.cut(-1);
	    }
	  continue;

	case ' ':
	  if (buf.len() == 0)
	    continue;
	  break;

	case KEY_TAB:
	    {
	      bool multi_match = false;
	      *cmd = Jdb_core::complete_cmd(buf.buffer(), multi_match);
	      if (cmd->cmd && multi_match)
		{
		  printf("\n");
		  unsigned prefix_len = Jdb_core::print_alternatives(buf.buffer());
		  print_prompt();
		  buf.overlay(cmd->cmd->cmd, prefix_len);
		  putnstr(buf.buffer(), buf.len());
		}
	      else if (cmd->cmd)
		{
		  putstr(cmd->cmd->cmd + buf.len());
		  putchar(' ');
		  buf.overlay(cmd->cmd->cmd, strlen(cmd->cmd->cmd));
		  buf.append(' ');
		}
	      continue;
	    }
	  break;

	case KEY_RETURN:
	  puts("");
	  if (!buf.len())
	    {
	      hide_statline = false;
	      cmd->cmd = 0;
	      return false;
	    }
	  break;

	default:
	  buf.append(c);
	  printf("\033[K%c", c);
	  continue;
	}

      *cmd = Jdb_core::has_cmd(buf.buffer());
      if (cmd->cmd)
	{
	  unsigned cmd_len = strlen(cmd->cmd->cmd);
	  *args = buf.buffer() + cmd_len;
	  while (**args == ' ')
	    ++(*args);
	  return false; // do not leave the debugger
	}
      else
	{
	  printf("unknown command: '%s'\n", buf.buffer());
	  print_prompt();
	  buf.flush();
	}
    }
}

#line 499 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


int
Jdb::execute_command()
{
  char const *args;
  Jdb_core::Cmd cmd(0,0);
  bool leave;
  int cmd_key;

  if (short_mode)
    leave = input_short_mode(&cmd, &args, cmd_key);
  else
    leave = input_long_mode(&cmd, &args);

  if (leave)
    return 0;

  if (cmd.cmd)
    {
      int ret = Jdb_core::exec_cmd( cmd, args );

      if (!ret)
	hide_statline = false;

      last_cmd = cmd_key;
      return ret;
    }

  last_cmd = 0;
  return 1;
}

#line 531 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


bool
Jdb::open_debug_console(Cpu_number cpu)
{
  in_service = 1;
  save_disable_irqs(cpu);
  if (cpu == Cpu_number::boot_cpu())
    jdb_enter.execute();

  if (!stop_all_cpus(cpu))
    return false; // CPUs other than 0 never become interacitve

  if (!Jdb_screen::direct_enabled())
    Kconsole::console()->
      change_state(Console::DIRECT, 0, ~Console::OUTENABLED, 0);

  return true;
}

#line 550 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"



void
Jdb::close_debug_console(Cpu_number cpu)
{
  Proc::cli();
  Mem::barrier();
  if (cpu == Cpu_number::boot_cpu())
    {
      running.cpu(cpu) = 0;
      // eat up input from console
      while (Kconsole::console()->getchar(false)!=-1)
	;

      Kconsole::console()->
	change_state(Console::DIRECT, 0, ~0UL, Console::OUTENABLED);

      in_service = 0;
      leave_wait_for_others();
      jdb_leave.execute();
    }

  Mem::barrier();
  restore_irqs(cpu);
}

#line 576 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


void
Jdb::remote_work(Cpu_number cpu, void (*func)(Cpu_number, void *), void *data,
                 bool sync)
{
  if (cpu == Cpu_number::boot_cpu())
    func(cpu, data);
  else
    {
      while (1)
	{
	  Mem::barrier();
	  if (!Jdb::remote_func_running.cpu(cpu))
	    break;
	  Proc::pause();
	}

      Jdb::remote_func_running.cpu(cpu) = 1;
      Jdb::remote_func_data.cpu(cpu) = data;
      Mem::barrier();
      set_monitored_address(&Jdb::remote_func.cpu(cpu), func);
      Mem::barrier();

      while (sync)
	{
	  Mem::barrier();
	  if (!Jdb::remote_func_running.cpu(cpu))
	    break;
	  Proc::pause();
	}
    }
}

#line 609 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


int
Jdb::getchar(void)
{
  int res = Kconsole::console()->getchar();
  check_for_cpus(false);
  return res;
}

#line 618 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


void Jdb::cursor_home()
{
  putstr("\033[H");
}

#line 624 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


void Jdb::cursor_end_of_screen()
{
  putstr("\033[127;1H");
}

#line 630 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"

//-------- pretty print functions ------------------------------

void
Jdb::write_ll_ns(Signed64 ns, char *buf, int maxlen, bool sign)
{
  Unsigned64 uns = (ns < 0) ? -ns : ns;

  if (uns >= 3600000000000000ULL)
    {
      snprintf(buf, maxlen, ">999 h ");
      return;
    }

  if (maxlen && sign)
    {
      *buf++ = (ns < 0) ? '-' : (ns == 0) ? ' ' : '+';
      maxlen--;
    }

  if (uns >= 60000000000000ULL)
    {
      // 1000min...999h
      Mword _h  = uns / 3600000000000ULL;
      Mword _m  = (uns % 3600000000000ULL) / 60000000000ULL;
      snprintf(buf, maxlen, "%3lu:%02lu h  ", _h, _m);
      return;
    }

  if (uns >= 1000000000000ULL)
    {
      // 1000s...999min
      Mword _m  = uns / 60000000000ULL;
      Mword _s  = (uns % 60000000000ULL) / 1000ULL;
      snprintf(buf, maxlen, "%3lu:%02lu M  ", _m, _s);
      return;
    }

  if (uns >= 1000000000ULL)
    {
      // 1...1000s
      Mword _s  = uns / 1000000000ULL;
      Mword _ms = (uns % 1000000000ULL) / 1000000ULL;
      snprintf(buf, maxlen, "%3lu.%03lu s ", _s, _ms);
      return;
    }

  if (uns >= 1000000)
    {
      // 1...1000ms
      Mword _ms = uns / 1000000UL;
      Mword _us = (uns % 1000000UL) / 1000UL;
      snprintf(buf, maxlen, "%3lu.%03lu ms", _ms, _us);
      return;
    }

  if (uns == 0)
    {
      snprintf(buf, maxlen, "  0       ");
      return;
    }

  Console* gzip = Kconsole::console()->find_console(Console::GZIP);
  Mword _us = uns / 1000UL;
  Mword _ns = uns % 1000UL;
  snprintf(buf, maxlen, "%3lu.%03lu %c ", _us, _ns,
           gzip && gzip->state() & Console::OUTENABLED
             ? '\265' 
             : Config::char_micro);
}

#line 700 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


void
Jdb::write_ll_hex(Signed64 x, char *buf, int maxlen, bool sign)
{
  // display 40 bits
  Unsigned64 xu = (x < 0) ? -x : x;

  if (sign)
    snprintf(buf, maxlen, "%s%03lx" L4_PTR_FMT,
			  (x < 0) ? "-" : (x == 0) ? " " : "+",
			  (Mword)((xu >> 32) & 0xfff), (Mword)xu);
  else
    snprintf(buf, maxlen, "%04lx" L4_PTR_FMT,
			  (Mword)((xu >> 32) & 0xffff), (Mword)xu);
}

#line 716 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


void
Jdb::write_ll_dec(Signed64 x, char *buf, int maxlen, bool sign)
{
  Unsigned64 xu = (x < 0) ? -x : x;

  // display no more than 11 digits
  if (xu >= 100000000000ULL)
    {
      snprintf(buf, maxlen, "%12s", ">= 10^11");
      return;
    }

  if (sign && x != 0)
    snprintf(buf, maxlen, "%+12lld", x);
  else
    snprintf(buf, maxlen, "%12llu", xu);
}

#line 749 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"

/// handling of standard cursor keys (Up/Down/PgUp/PgDn)

int
Jdb::std_cursor_key(int c, Mword cols, Mword lines, Mword max_absy, Mword *absy,
                    Mword *addy, Mword *addx, bool *redraw)
{
  switch (c)
    {
    case KEY_CURSOR_LEFT:
    case 'h':
      if (addx)
	{
	  if (*addx > 0)
	    (*addx)--;
	  else if (*addy > 0)
	    {
	      (*addy)--;
	      *addx = cols - 1;
	    }
	  else if (*absy > 0)
	    {
	      (*absy)--;
	      *addx = cols - 1;
	      *redraw = true;
	    }
	}
      else
	return 0;
      break;
    case KEY_CURSOR_RIGHT:
    case 'l':
      if (addx)
	{   
	  if (*addx < cols - 1)
	    (*addx)++;
	  else if (*addy < lines - 1)
	    {
	      (*addy)++; 
	      *addx = 0;
	    }
	  else if (*absy < max_absy)
	    {
	      (*absy)++;
	      *addx = 0;
	      *redraw = true;
	    }
	}
      else
	return 0;
      break;
    case KEY_CURSOR_UP:
    case 'k':
      if (*addy > 0)
	(*addy)--;
      else if (*absy > 0)
	{
	  (*absy)--;
	  *redraw = true;
	}
      break;
    case KEY_CURSOR_DOWN:
    case 'j':
      if (*addy < lines-1)
	(*addy)++;
      else if (*absy < max_absy)
	{
	  (*absy)++;
	  *redraw = true;
	}
      break;
    case KEY_CURSOR_HOME:
    case 'H':
      *addy = 0;
      if (addx)
	*addx = 0;
      if (*absy > 0)
	{
	  *absy = 0;
	  *redraw = true;
	}
      break;
    case KEY_CURSOR_END:
    case 'L':
      *addy = lines-1;
      if (addx)
	*addx = cols - 1;
      if (*absy < max_absy)
	{
	  *absy = max_absy;
	  *redraw = true;
	}
      break;
    case KEY_PAGE_UP:
    case 'K':
      if (*absy >= lines)
	{
	  *absy -= lines;
	  *redraw = true;
	}
      else
	{
	  if (*absy > 0)
	    {
	      *absy = 0;
	      *redraw = true;
	    }
	  else if (*addy > 0)
	    *addy = 0;
	  else if (addx)
	    *addx = 0;
	}
      break;
    case KEY_PAGE_DOWN:
    case 'J':
      if (*absy+lines-1 < max_absy)
	{
	  *absy += lines;
	  *redraw = true;
	}
      else
	{
	  if (*absy < max_absy)
	    {
	      *absy = max_absy;
	      *redraw = true;
	    }
	  else if (*addy < lines-1)
      	    *addy = lines-1;
	  else if (addx)
	    *addx = cols - 1;
	}
      break;
    default:
      return 0;
    }

  return 1;
}

#line 932 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


Jdb_module::Action_code
Jdb_base_cmds::action(int cmd, void *&, char const *&, int &)
{
  if (cmd!=0)
    return NOTHING;

  Jdb_core::short_mode = !Jdb_core::short_mode;
  printf("\ntoggle mode: now in %s command mode (use '%s' to switch back)\n",
         Jdb_core::short_mode ? "short" : "long",
         Jdb_core::short_mode ? "*" : "mode");
  return NOTHING;
}

#line 946 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


int
Jdb_base_cmds::num_cmds() const
{ 
  return 1;
}

#line 953 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


Jdb_module::Cmd const *
Jdb_base_cmds::cmds() const
{
  static Cmd cs[] =
    { { 0, "*", "mode", "", "*|mode\tswitch long and short command mode",
	(void*)0 } };

  return cs;
}

#line 964 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


Jdb_base_cmds::Jdb_base_cmds()
  : Jdb_module("GENERAL")
{}

#line 1002 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"





int
Jdb::enter_jdb(Jdb_entry_frame *e, Cpu_number cpu)
{
  if (e->debug_ipi())
    {
      if (!remote_work_ipi_process(cpu))
        return 0;
      if (!in_service)
	return 0;
    }

  enter_trap_handler(cpu);

  if (handle_conditional_breakpoint(cpu))
    {
      // don't enter debugger, only logged breakpoint
      leave_trap_handler(cpu);
      return 0;
    }

  if (!running.cpu(cpu))
    entry_frame.cpu(cpu) = e;

  volatile bool really_break = true;

  static jmp_buf recover_buf;
  static Jdb_entry_frame nested_trap_frame;

  if (running.cpu(cpu))
    {
      nested_trap_frame = *e;

      // Since we entered the kernel debugger a second time,
      // Thread::nested_trap_recover
      // has a value of 2 now. We don't leave this function so correct the
      // entry counter
      Thread::nested_trap_recover.cpu(cpu)--;

      longjmp(recover_buf, 1);
    }

  // all following exceptions are handled by jdb itself
  running.cpu(cpu) = true;

  if (!open_debug_console(cpu))
    { // not on the master CPU just wait
      close_debug_console(cpu);
      leave_trap_handler(cpu);
      return 0;
    }

  Jdb::current_cpu = cpu;
  // check for int $3 user debugging interface
  if (foreach_cpu(&handle_user_request, true))
    {
      close_debug_console(cpu);
      leave_trap_handler(cpu);
      return 0;
    }

  hide_statline = false;

  // clear error message
  *error_buffer.cpu(cpu) = '\0';

  really_break = foreach_cpu(&handle_debug_traps, false);

  while (setjmp(recover_buf))
    {
      // handle traps which occured while we are in Jdb
      Kconsole::console()->end_exclusive(Console::GZIP);
      handle_nested_trap(&nested_trap_frame);
    }

  if (!never_break && really_break) 
    {
      // determine current task/thread from stack pointer
      update_prompt();

      LOG_MSG(current_active, "=== enter jdb ===");

      do
	{
	  screen_scroll(1, Jdb_screen::height());
	  if (!hide_statline)
	    {
	      cursor(Jdb_screen::height(), 1);
	      printf("\n%s%s    %.*s\033[m      \n",
	             esc_prompt,
	             test_checksums()
	               ? ""
	               : "    WARNING: Fiasco kernel checksum differs -- "
	                 "read-only data has changed!\n",
	             Jdb_screen::width()-11,
	             Jdb_screen::Line);
	      for (Cpu_number i = Cpu_number::first(); i < Config::max_num_cpus(); ++i)
		if (Cpu::online(i))
		  {
		    if (running.cpu(i))
		      printf("    CPU%2u [" L4_PTR_FMT "]: %s\n",
                             cxx::int_value<Cpu_number>(i),
		             entry_frame.cpu(i)->ip(), error_buffer.cpu(i));
		    else
		      printf("    CPU%2u: is not in JDB (not responding)\n",
                             cxx::int_value<Cpu_number>(i));
		  }
	      hide_statline = true;
	    }

	  printf_statline(0, 0, "_");

	} while (execute_command());

      // reset scrolling region of serial terminal
      screen_scroll(1,127);

      // reset cursor
      blink_cursor(Jdb_screen::height(), 1);

      // goto end of screen
      Jdb::cursor(127, 1);
    }

  // reenable interrupts
  close_debug_console(cpu);

  rcv_uart_enable();

  leave_trap_handler(cpu);
  return 0;
}

#line 1142 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


bool
Jdb::stop_all_cpus(Cpu_number)
{ return true; }

#line 1147 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"



void
Jdb::leave_wait_for_others()
{}

#line 1153 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


bool
Jdb::check_for_cpus(bool)
{ return true; }
