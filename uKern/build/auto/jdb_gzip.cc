// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_gzip.h"
#include "jdb_gzip_i.h"

#line 21 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"

Console *Jdb_gzip::uart;
#line 109 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"

STATIC_INITIALIZE(Jdb_gzip);

#line 40 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"


inline void
Jdb_gzip::enable()
{
  if (!init_done)
    {
      uart = Kconsole::console()->find_console(Console::UART);
      init_done = 1;
    }

  gz_open("jdb.gz");
  active = 1;
}

#line 54 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"


inline void
Jdb_gzip::disable()
{
  if (active)
    {
      gz_close();
      active = 0;
    }
}

#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"

Jdb_gzip::Jdb_gzip()
{
  _state = Console::DISABLED_INIT;
  char *heap = (char*)Kmem_alloc::allocator()->
    unaligned_alloc(heap_pages*Config::PAGE_SIZE);
  if (!heap)
    panic("No memory for gzip heap");
  gz_init(heap, heap_pages * Config::PAGE_SIZE, raw_write);
}

#line 33 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"

void
Jdb_gzip::raw_write(const char *s, size_t len)
{
  if (uart)
    uart->write(s, len);
}

#line 65 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"

void
Jdb_gzip::state(Mword new_state)
{
  if ((_state ^ new_state) & OUTENABLED)
    {
      if (new_state & OUTENABLED)
	enable();
      else
	disable();
    }

  _state = new_state;
}

#line 79 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"


int
Jdb_gzip::write(char const *str, size_t len)
{
  gz_write(str, len);
  return len;
}

#line 87 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"


Console*
Jdb_gzip::console()
{
  static Jdb_gzip c;
  return &c;
}

#line 95 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"


Mword
Jdb_gzip::get_attributes() const
{
  return GZIP | OUT;
}

#line 102 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"

FIASCO_INIT
void
Jdb_gzip::init()
{
  Kconsole::console()->register_console(console());
}
