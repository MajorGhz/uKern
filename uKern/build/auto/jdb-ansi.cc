// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb.h"
#include "jdb_i.h"


#line 38 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"



void
Jdb::cursor(unsigned int row, unsigned int col)
{
  if (row || col)
    printf ("\033[%u;%uH", row, col);
  else
    printf ("\033[%u;%uH", 1, 1);
}

#line 77 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"


void
Jdb::screen_scroll(unsigned int start, unsigned int end)
{
  if (start || end)
    printf ("\033[%u;%ur", start, end);
  else
    printf ("\033[r");
}

#line 94 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"

// preserve the history of the serial console if fancy != 0

void
Jdb::clear_screen(int fancy)
{
  if (fancy == FANCY)
    {
      cursor(Jdb_screen::height(), 1);
      for (unsigned i=0; i<Jdb_screen::height(); i++)
	{
	  putchar('\n');
	  clear_to_eol();
	}
    }
  else
    {
      cursor();
      for (unsigned i=0; i<Jdb_screen::height()-1; i++)
	{
	  clear_to_eol();
	  putchar('\n');
	}
    }
  cursor();
}
