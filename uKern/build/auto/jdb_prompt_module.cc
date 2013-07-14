// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_prompt_module.h"
#include "jdb_prompt_module_i.h"

#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"

char Jdb_pcm::subcmd;
#line 36 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"
char Jdb_pcm::prompt_color;
#line 37 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"
char Jdb_pcm::direct_enable;
#line 38 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"
int  Jdb_pcm::screen_height;
#line 39 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"
int  Jdb_pcm::screen_width;
#line 40 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"

static Jdb_pcm jdb_pcm INIT_PRIORITY(JDB_MODULE_INIT_PRIO);

#line 42 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"


int
Jdb_pcm::get_coords(Console *cons, unsigned &x, unsigned &y)
{
  cons->write("\033[6n", 4);

  if (!wait_for_escape(cons))
    return 0;

  if (cons->getchar(true) != '[')
    return 0;

  for (y=0; ;)
    {
      int c = cons->getchar(true);
      if (c == ';')
	break;
      if (c < '0' || c > '9')
	return 0;
      y = y*10+c-'0';
    }
  for (x=0; ;)
    {
      int c = cons->getchar(true);
      if (c == 'R')
	break;
      if (c < '0' || c > '9')
	return 0;
      x = x*10+c-'0';
    }
  return 1;
}

#line 75 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"


void
Jdb_pcm::detect_screensize()
{
  unsigned x, y, max_x, max_y;
  char str[20];
  Console *uart;

  if (!(uart = Kconsole::console()->find_console(Console::UART)))
    return;

  while (uart->getchar(false) != -1)
    ;
  if (!get_coords(uart, x, y))
    return;
  // set scroll region to the max + set cursor to the max
  uart->write("\033[1;199r\033[199;199H", 18);
  if (!get_coords(uart, max_x, max_y))
    return;
  Jdb_screen::set_width(max_x);
  Jdb_screen::set_height(max_y);
  // adapt scroll region, restore cursor
  snprintf(str, sizeof(str), "\033[1;%ur\033[%u;%uH", max_y, y, x);
  uart->write(str, strlen(str));
}

#line 101 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"


Jdb_module::Action_code
Jdb_pcm::action(int cmd, void *&args, char const *&fmt, int &)
{
  if (cmd)
    return NOTHING;

  if (args == &subcmd)
    {
      switch (subcmd)
        {
        case 'c':
          fmt  = " promptcolor=%c";
          args = &prompt_color;
          return EXTRA_INPUT;
	case 'd':
	  fmt = "%c";
	  args = &direct_enable;
	  return EXTRA_INPUT;
        case 'h':
          fmt  = " screenheight=%d";
          args = &screen_height;
          return EXTRA_INPUT;
        case 'w':
          fmt  = " screenwidth=%d";
          args = &screen_width;
          return EXTRA_INPUT;
	case 'H':
	case 'S':
	  detect_screensize();
	  return NOTHING;
	case 'o':
	  printf("\nConnected consoles:\n");
	  Kconsole::console()->list_consoles();
	  return NOTHING;
        case 'i':
          printf("\nScreen dimensions: %dx%d Cols: %ld\n",
                 Jdb_screen::width(), Jdb_screen::height(),
                 Jdb_screen::cols());
          return NOTHING;
	default:
	  return ERROR;
        }
    }
  else if (args == &screen_height)
    {
      // set screen height
      if (24 < screen_height && screen_height < 100)
        Jdb_screen::set_height(screen_height);
    }
  else if (args == &screen_width)
    {
      // set screen height
      if (80 < screen_width && screen_width < 600)
        Jdb_screen::set_width(screen_width);
    }
  else if (args == &prompt_color)
    {
      if (!Jdb::set_prompt_color(prompt_color) )
        {
          putchar(prompt_color);
          puts(" - color expected (lLrRgGbByYmMcCwW)!");
        }
    }
  else if (args == &direct_enable)
    {
      printf(" Direct console %s\n",
	  direct_enable == '+' ? "enabled" : "disabled");
      Jdb_screen::enable_direct(direct_enable == '+');
      if (direct_enable == '+')
	Kconsole::console()->change_state(Console::DIRECT, 0,
					  ~0U, Console::OUTENABLED);
      else
	Kconsole::console()->change_state(Console::DIRECT, 0,
					  ~Console::OUTENABLED, 0);
    }

  return NOTHING;
}

#line 181 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"


int Jdb_pcm::num_cmds() const
{
  return 1;
}

#line 187 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"


Jdb_module::Cmd const * Jdb_pcm::cmds() const
{
  static Cmd cs[] =
    {
	{ 0, "J", "Jdb options", "%c",
	   "Jc<color>\tset the Jdb prompt color, <color> must be:\n"
	   "\tnN: noir(black), rR: red, gG: green, bB: blue,\n"
	   "\tyY: yellow, mM: magenta, cC: cyan, wW: white;\n"
	   "\tthe capital letters are for bold text.\n"
	   "Jd{+|-}\ton/off Jdb output to VGA/Hercules console\n"
	   "Jh\tset Jdb screen height\n"
	   "Jw\tset Jdb screen width\n"
	   "JS\tdetect screen size using ESCape sequence ESC [ 6 n\n"
           "Ji\tshow screen information\n"
	   "Jo\tlist attached consoles",
	   &subcmd }
    };

  return cs;
}

#line 209 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"


Jdb_pcm::Jdb_pcm()
  : Jdb_module("GENERAL")
{}

#line 219 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"


int
Jdb_pcm::wait_for_escape(Console *cons)
{
  Unsigned64 to = Cpu::boot_cpu()->ns_to_tsc (Cpu::boot_cpu()->tsc_to_ns (Cpu::rdtsc()) + 200000000);

  // This is just a sanity check to ensure that a tool like minicom is attached
  // at the other end of the serial line and this tools responds to the magical
  // escape sequence.
  for (;;)
    {
      int c = cons->getchar(false);
      if (c == '\033')
	return 1;
      if (c != -1 || Cpu::rdtsc() > to)
	return 0;
      Proc::pause();
    }
}
