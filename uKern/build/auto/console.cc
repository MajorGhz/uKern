// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "console.h"
#include "console_i.h"

#line 104 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/console.cpp"

Console *Console::stdout;
#line 106 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/console.cpp"
Console *Console::stderr;
#line 107 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/console.cpp"
Console *Console::stdin;

#line 108 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/console.cpp"

Console::~Console()
{}

#line 121 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/console.cpp"


void Console::state(Mword new_state)
{
  _state = new_state;
}

#line 141 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/console.cpp"


void Console::disable_all()
{
  stdout = 0;
  stderr = 0;
  stdin  = 0;
}

#line 149 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/console.cpp"


int Console::write(char const *, size_t len)
{
  return len;
}

#line 155 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/console.cpp"


int Console::getchar(bool /* blocking */)
{
  return -1; /* no input */
}

#line 161 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/console.cpp"


int Console::char_avail() const
{
  return -1; /* unknown */
}

#line 167 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/console.cpp"


Mword Console::get_attributes() const
{
  return 0;
}

#line 175 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/console.cpp"


const char*
Console::str_mode() const
{
  static char const * const mode_str[] =
    { "      ", "Output", "Input ", "InOut " };
  return mode_str[get_attributes() & (OUT|IN)];
}

#line 184 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/console.cpp"


const char*
Console::str_state() const
{
  static char const * const state_str[] =
    { "Disabled       ", "Output disabled",
      "Input disabled ", "Enabled        " };
  return state_str[state() & (INENABLED|OUTENABLED)];
}

#line 194 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/console.cpp"


const char*
Console::str_attr(Mword bit) const
{
  static char const * const attr_str[] =
    { "Direct", "Uart", "UX", "Push", "Gzip", "Buffer", "Kdb", "FAILED!" };

  return (bit < 2 || bit >= (sizeof(attr_str)/sizeof(attr_str[0]))+2)
    ? "???"
    : attr_str[bit-2];
}
