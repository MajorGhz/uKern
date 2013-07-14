// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_list.h"
#include "jdb_list_i.h"

#line 24 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"


// ---------------------------------------------------------------------------


#line 40 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"




Jdb_list::Jdb_list()
  : _start(0), _current(0)
{}

#line 47 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"

// set _t_start element of list

void
Jdb_list::set_start(void *start)
{
  _start = start;
}

#line 79 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"

// _t_start -= 24 if possible

bool
Jdb_list::page_back()
{ return seek(-Jdb_screen::height()+2, &_start); }

#line 85 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"

// _t_start += 24 if possible

bool
Jdb_list::page_forw()
{
  int fwd = seek(Jdb_screen::height()-2, &_last);
  if (fwd)
    return seek(fwd, &_start);
  return false;
}

#line 104 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"

// _t_start = first element of list

bool
Jdb_list::goto_home()
{ return seek(-99999, &_start); }

#line 110 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"

// _t_start = last element of list

bool
Jdb_list::goto_end()
{ return seek(99999, &_start); }

#line 123 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"

// search index of t_search starting from _t_start

int
Jdb_list::lookup_in_visible_area(void *search)
{
  unsigned i;
  void *t;

  for (i=0, t = _start; i < Jdb_screen::height()-3; ++i)
    {
      if (t == search)
	return i;

      seek(1, &t);
    }

  return -1;
}

#line 142 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"

// get y'th element of thread list starting from _t_start

void *
Jdb_list::index(int y)
{
  void *t = _start;

  seek(y, &t);
  return t;
}

#line 153 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"



void
Jdb_list::show_line(void *i)
{
  static char buffer[256];
  Kconsole::console()->getchar_chance();
  int pos = 0;
  void *p = i;
  while ((p = parent(p)))
    {
      buffer[pos] = ' ';
      ++pos;
    }

  pos += show_item(buffer + pos, sizeof(buffer) - pos, i);
  if (i)
    printf("%.*s\033[K\n", min((int)Jdb_screen::width(), pos), buffer);
}

#line 173 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"

// show complete page using show callback function

int
Jdb_list::page_show()
{
  void *t = _start;
  unsigned i = 0;
  for (i = 0; i < Jdb_screen::height()-3; ++i)
    {
      if (!t)
	break;
      else
	_last = t;

      show_line(t);

      if (!seek(1,&t))
	return i;
    }

  return i - 1;
}

#line 196 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"

// show complete list using show callback function

int
Jdb_list::complete_show()
{
  void *t = _start;
  int i = 0;
  for (i = 0; ; ++i, seek(1, &t))
    {
      if (!t)
	break;

      show_line(t);
    }

  return i;
}

#line 273 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"



void
Jdb_list::show_header()
{
  Jdb::cursor();
  printf("%.*s\033[K\n", Jdb_screen::width(), show_head());
}

#line 282 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"



void
Jdb_list::do_list()
{
  int y, y_max;
  void *t;

  if (!_start)
    _start = get_head();

  if (!_current)
    _current = _start;

  Jdb::clear_screen();
  show_header();

  if (!_start)
    {
      printf("[EMPTY]\n");
      return;
    }


  for (;;)
    {
      // set y to position of t_current in current displayed list
      y = lookup_in_visible_area(_current);
      if (y == -1)
	{
	  _start = _current;
	  y = 0;
	}

      for (bool resync=false; !resync;)
	{
	  Jdb::cursor(2, 1);
	  y_max = page_show();

	  // clear rest of screen (if where less than 24 lines)
	  for (unsigned i = y_max; i < Jdb_screen::height()-3; ++i)
            putstr("\033[K\n");

	  Jdb::printf_statline("Objs",
			       "<Space>=mode <Tab>=link <CR>=select",
			       "%-15s", get_mode_str());

	  // key event loop
	  for (bool redraw=false; !redraw; )
	    {
	      Jdb::cursor(y+2, 1);
	      switch (int c=Jdb_core::getchar())
		{
		case KEY_CURSOR_UP:
		case 'k':
		  if (y > 0)
		    y--;
		  else
		    redraw = line_back();
		  break;
		case KEY_CURSOR_DOWN:
		case 'j':
		  if (y < y_max)
		    y++;
		  else
		    redraw = line_forw();
		  break;
		case KEY_PAGE_UP:
		case 'K':
		  if (!(redraw = page_back()))
		    y = 0;
		  break;
		case KEY_PAGE_DOWN:
		case 'J':
		  if (!(redraw = page_forw()))
		    y = y_max;
		  break;
		case KEY_CURSOR_HOME:
		case 'H':
		  redraw = goto_home();
		  y = 0;
		  break;
		case KEY_CURSOR_END:
		case 'L':
		  redraw = goto_end();
		  y = y_max;
		  break;
		case 's': // switch sort
		  _current = index(y);
		  next_sort();
		  redraw = true;
		  resync = true;
		  break;
		case ' ': // switch mode
                  _current = index(y);
		  next_mode();
		  _current = get_valid(_current);
                  _start   = get_valid(_start);
		  redraw = true;
		  resync = true;
		  break;
		case KEY_TAB: // go to associated object
		  _current = index(y);
		  t = follow_link(_current);
		  if (t != _current)
		    {
		      _current = t;
		      redraw = true;
		      resync = true;
		    }
		  break;
		case KEY_RETURN:
		  _current = index(y);
		  if (!enter_item(_current))
		    return;
		  show_header();
		  redraw = 1;
		  break;
		case KEY_ESC:
		  Jdb::abort_command();
		  return;
		default:
		  _current = index(y);
		  if (!handle_key(_current, c) && Jdb::is_toplevel_cmd(c))
		    return;

		  show_header();
		  redraw = 1;
		  break;
		}
	    }
	}
    }
}
