// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "vkey.h"
#include "vkey_i.h"

#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vkey.cpp"


// ---------------------------------------------------------------------------

#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vkey.cpp"

static Irq_base *vkey_irq;
#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vkey.cpp"

// ---------------------------------------------------------------------------

#line 35 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vkey.cpp"

static Vkey::Echo_type vkey_echo;
#line 37 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vkey.cpp"
static char     vkey_buffer[256];
#line 38 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vkey.cpp"
static unsigned vkey_tail, vkey_head;
#line 39 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vkey.cpp"
static Console *uart = Kconsole::console()->find_console(Console::UART);

#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vkey.cpp"


void
Vkey::irq(Irq_base *i)
{ vkey_irq = i; }

#line 40 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vkey.cpp"


void
Vkey::set_echo(Echo_type echo)
{
  vkey_echo = echo;
}

#line 47 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vkey.cpp"


bool
Vkey::add(int c)
{
  bool hit = false;
  unsigned nh = (vkey_head + 1) % sizeof(vkey_buffer);
  unsigned oh = vkey_head;
  if (nh != vkey_tail)
    {
      vkey_buffer[vkey_head] = c;
      vkey_head = nh;
    }

  if (oh == vkey_tail)
    hit = true;

  if (vkey_echo == Vkey::Echo_crnl && c == '\r')
    c = '\n';

  if (vkey_echo)
    putchar(c);

  return hit;
}

#line 72 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vkey.cpp"


bool
Vkey::add(const char *seq)
{
  bool hit = false;
  for (; *seq; ++seq)
    hit |= add(*seq);
  return hit;
}

#line 82 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vkey.cpp"


void
Vkey::trigger()
{
  if (vkey_irq)
    vkey_irq->hit(0);
}

#line 90 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vkey.cpp"


void
Vkey::add_char(int v)
{
  if (add(v))
    trigger();
}

#line 98 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vkey.cpp"


int
Vkey::check_()
{
  if (!uart)
    return 1;

  int  ret = 1;
  bool hit = false;

  // disable last branch recording, branch trace recording ...
  Cpu::cpus.cpu(current_cpu()).debugctl_disable();

  while (1)
    {
      int c = uart->getchar(false);

      if (c == -1)
	break;

      if (c == KEY_ESC)
	{
	  ret = 0;  // break into kernel debugger
	  break;
	}

      switch (c)
	{
	case KEY_CURSOR_UP:    hit |= add("\033[A"); break;
	case KEY_CURSOR_DOWN:  hit |= add("\033[B"); break;
	case KEY_CURSOR_LEFT:  hit |= add("\033[D"); break;
	case KEY_CURSOR_RIGHT: hit |= add("\033[C"); break;
	case KEY_CURSOR_HOME:  hit |= add("\033[1~"); break;
	case KEY_CURSOR_END:   hit |= add("\033[4~"); break;
	case KEY_PAGE_UP:      hit |= add("\033[5~"); break;
	case KEY_PAGE_DOWN:    hit |= add("\033[6~"); break;
	case KEY_INSERT:       hit |= add("\033[2~"); break;
	case KEY_DELETE:       hit |= add("\033[3~"); break;
	case KEY_F1:           hit |= add("\033OP"); break;
	case KEY_BACKSPACE:    hit |= add(127); break;
	case KEY_TAB:          hit |= add(9); break;
	case KEY_ESC:          hit |= add(27); break;
	case KEY_RETURN:       hit |= add(13); break;
	default:               hit |= add(c); break;
	}
    }

  if (hit)
    trigger();

  // Hmmm, we assume that a console with the UART flag set is of type Uart
  if (Config::serial_esc == Config::SERIAL_ESC_IRQ)
    static_cast<Uart*>(uart)->enable_rcv_irq();

  // reenable debug stuff (undo debugctl_disable)
  Cpu::cpus.cpu(current_cpu()).debugctl_enable();

  return ret;
}

#line 158 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vkey.cpp"


int
Vkey::get()
{
  if (vkey_tail != vkey_head)
    return vkey_buffer[vkey_tail];

  return -1;
}

#line 168 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vkey.cpp"


void
Vkey::clear()
{
  if (vkey_tail != vkey_head)
    vkey_tail = (vkey_tail + 1) % sizeof(vkey_buffer);
}
