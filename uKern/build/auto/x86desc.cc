// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "x86desc.h"
#include "x86desc_i.h"

#line 63 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"



//----------------------------------------------------------------------------


#line 180 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"



const char*
X86desc::type_str() const
{
  static char const * const desc_type[32] =
    {
      "reserved",          "16-bit tss (avail)",
      "ldt",               "16-bit tss (busy)",
      "16-bit call gate",  "task gate",
      "16-bit int gate",   "16-bit trap gate",
      "reserved",          "32-bit tss (avail)",
      "reserved",          "32-bit tss (busy)",
      "32-bit call gate",  "reserved",
      "32-bit int gate",   "32-bit trap gate",
      "data r/o",          "data r/o acc",
      "data r/w",          "data r/w acc",
      "data r/o exp-dn",   "data r/o exp-dn",
      "data r/w exp-dn",   "data r/w exp-dn acc",
      "code x/o",          "code x/o acc", 
      "code x/r",          "code x/r acc",
      "code x/r conf",     "code x/o conf acc",
      "code x/r conf",     "code x/r conf acc"
    };

  Unsigned8 const *t = (Unsigned8 const *)this;

  return desc_type[t[5] & 0x1f];
}

#line 210 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


void
Gdt_entry::show() const
{
  static char const modes[] = { 16, 64, 32, -1 };
  // segment descriptor
  Address b = base();
  printf("%016lx-%016lx dpl=%d %dbit %s %02X (\033[33;1m%s\033[m)\n",
         b, b + size(), (access & 0x60) >> 5,
         modes[mode()],
         access & 0x10 ? "code/data" : "system   ",
         access & 0x1f, type_str());
}

#line 229 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


void
Idt_entry::show() const
{
  if (type() == 0x5)
    {
      // Task gate

      printf("--------  sel=%04x dpl=%d %02X (\033[33;1m%s\033[m)\n",
             selector(), dpl(), type(), type_str());
    }
  else
    {
      Address o = offset();

      printf("%016lx  sel=%04x dpl=%d %02X (\033[33;1m%s\033[m)\n",
             o, selector(), dpl(), type(), type_str());
    }
}

#line 249 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"



void
X86desc::show() const
{
  if (present())
    {
      if ((access() & 0x16) == 0x06)
	static_cast<Idt_entry const*>(this)->show();
      else
	static_cast<Gdt_entry const*>(this)->show();
    }
  else
    {
      printf("--------  dpl=%d %02X (\033[33;1m%s\033[m)\n",
	  dpl(), type(), type_str());
    }
}
