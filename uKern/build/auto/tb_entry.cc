// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "tb_entry.h"
#include "tb_entry_i.h"

#line 304 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"

Mword (*Tb_entry::rdcnt1)() = dummy_read_pmc;
#line 306 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
Mword (*Tb_entry::rdcnt2)() = dummy_read_pmc;
#line 307 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
Tb_entry_formatter const *Tb_entry_formatter::_fixed[Tbuf_dynentries];

#line 301 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


Mword Tb_entry::dummy_read_pmc() { return 0; }

#line 308 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"



void
Tb_entry_formatter::set_fixed(unsigned type, Tb_entry_formatter const *f)
{
  if (type >= Tbuf_dynentries)
    return;

  _fixed[type] = f;
}

#line 319 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"



void
Tb_entry::set_rdcnt(int num, Mword (*f)())
{
  if (!f)
    f = dummy_read_pmc;

  switch (num)
    {
    case 0: rdcnt1 = f; break;
    case 1: rdcnt2 = f; break;
    }
}
