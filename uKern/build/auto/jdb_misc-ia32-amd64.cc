// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_misc.h"
#include "jdb_misc_i.h"

#line 22 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"

char Jdb_misc_general::first_char;
#line 72 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"

static Jdb_misc_general jdb_misc_general INIT_PRIORITY(JDB_MODULE_INIT_PRIO);
#line 86 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"

char     Jdb_misc_debug::first_char;
#line 88 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
Mword    Jdb_misc_debug::task;
#line 233 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"

static Jdb_misc_debug jdb_misc_debug INIT_PRIORITY(JDB_MODULE_INIT_PRIO);
#line 282 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"

char       Jdb_misc_info::first_char;
#line 284 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
Address    Jdb_misc_info::addr;
#line 285 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
Mword      Jdb_misc_info::value;
#line 286 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
Unsigned64 Jdb_misc_info::value64;
#line 401 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"

static Jdb_misc_info jdb_misc_info INIT_PRIORITY(JDB_MODULE_INIT_PRIO);

#line 24 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"



Jdb_module::Action_code
Jdb_misc_general::action(int cmd, void *&, char const *&, int &)
{
  switch (cmd)
    {
    case 0:
      // escape key
      if (first_char == '+' || first_char == '-')
	{
	  putchar(first_char);
	  Config::esc_hack = (first_char == '+');
	  putchar('\n');
	  return NOTHING;
	}
      return ERROR;
    }

  return NOTHING;
}

#line 46 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"


Jdb_module::Cmd const *
Jdb_misc_general::cmds() const
{
  static Cmd cs[] =
    {
	{ 0, "E", "esckey", "%C",
	  "E{+|-}\ton/off enter jdb by pressing <ESC>",
	  &first_char },
    };
  return cs;
}

#line 59 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"


int
Jdb_misc_general::num_cmds() const
{
  return 1;
}

#line 66 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"


Jdb_misc_general::Jdb_misc_general()
  : Jdb_module("GENERAL")
{
}

#line 89 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"

void
Jdb_misc_debug::show_lbr_entry(const char *str, Address addr)
{
  char symbol[60];

  printf("%s " L4_PTR_FMT " ", str, addr);
  if (Jdb_symbol::match_addr_to_symbol_fuzzy(&addr, 0, symbol, sizeof(symbol)))
    printf("(%s)", symbol);
}

#line 99 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"


Jdb_module::Action_code
Jdb_misc_debug::action(int cmd, void *&args, char const *&fmt, int &)
{
  switch (cmd)
    {
    case 0:
      // single step
      if (first_char == '+' || first_char == '-')
	{
	  putchar(first_char);
	  Jdb::set_single_step(Jdb::current_cpu, first_char == '+');
	  putchar('\n');
	}
      break;
    case 1:
      // ldt
      if (args == &task)
	{
	  show_ldt();
	  putchar('\n');
	  return NOTHING;
	}

      // lbr/ldt
      if (first_char == '+' || first_char == '-')
	{
	  Cpu::boot_cpu()->lbr_enable(first_char == '+');
	  putchar(first_char);
	  putchar('\n');
	}
      else if (first_char == 'd')
	{
	  printf("d task=");
	  fmt   = "%q";
	  args  = &task;
	  return EXTRA_INPUT;
	}
      else
	{
	  Jdb::msr_test = Jdb::Msr_test_fail_warn;
	  if (Cpu::boot_cpu()->lbr_type() == Cpu::Lbr_pentium_4 || 
	      Cpu::boot_cpu()->lbr_type() == Cpu::Lbr_pentium_4_ext)
	    {
	      Unsigned64 msr;
	      Unsigned32 branch_tos;

	      msr = Cpu::rdmsr(MSR_LER_FROM_LIP);
	      show_lbr_entry("\nbefore exc:", (Address)msr);
	      msr = Cpu::rdmsr(MSR_LER_TO_LIP);
	      show_lbr_entry(" =>", (Address)msr);

	      msr = Cpu::rdmsr(MSR_LASTBRANCH_TOS);
	      branch_tos = (Unsigned32)msr;

	      if (Cpu::boot_cpu()->lbr_type() == Cpu::Lbr_pentium_4)
		{
		  // older P4 models provide a stack of 4 MSRs
		  for (int i=0, j=branch_tos & 3; i<4; i++)
		    {
		      j = (j+1) & 3;
		      msr = Cpu::rdmsr(MSR_LASTBRANCH_0+j);
		      show_lbr_entry("\nbranch/exc:", (Address)(msr >> 32));
		      show_lbr_entry(" =>", (Address)msr);
		    }
		}
	      else
		{
		  // newer P4 models provide a stack of 16 MSR pairs
		  for (int i=0, j=branch_tos & 15; i<16; i++)
		    {
		      j = (j+1) & 15;
		      msr = Cpu::rdmsr(0x680+j);
		      show_lbr_entry("\nbranch/exc:", (Address)msr);
		      msr = Cpu::rdmsr(0x6c0+j);
		      show_lbr_entry(" =>", (Address)msr);
		    }
		}
	    }
	  else if (Cpu::boot_cpu()->lbr_type() == Cpu::Lbr_pentium_6)
	    {
	      Unsigned64 msr;

	      msr = Cpu::rdmsr(MSR_LASTBRANCHFROMIP);
	      show_lbr_entry("\nbranch:", (Address)msr);
	      msr = Cpu::rdmsr(MSR_LASTBRANCHTOIP);
	      show_lbr_entry(" =>", (Address)msr);
	      msr = Cpu::rdmsr(MSR_LASTINTFROMIP);
	      show_lbr_entry("\n   int:", (Address)msr);
	      msr = Cpu::rdmsr(MSR_LASTINTTOIP);
	      show_lbr_entry(" =>", (Address)msr);
	    }
	  else
	    printf("Last branch recording feature not available");

	  Jdb::msr_test = Jdb::Msr_test_default;
	  putchar('\n');
	  break;
	}
    }

  return NOTHING;
}

#line 203 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"


Jdb_module::Cmd const *
Jdb_misc_debug::cmds() const
{
  static Cmd cs[] =
    {
	{ 0, "S", "singlestep", "%C",
	  "S{+|-}\ton/off permanent single step mode",
	  &first_char },
	{ 1, "L", "lbr", "%C",
	  "L\tshow last branch recording information\n"
	  "Ld<taskno>\tshow LDT of specific task",
	  &first_char },
    };
  return cs;
}

#line 220 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"


int
Jdb_misc_debug::num_cmds() const
{
  return 2;
}

#line 227 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"


Jdb_misc_debug::Jdb_misc_debug()
  : Jdb_module("DEBUGGING")
{
}

#line 235 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"


void
Jdb_misc_debug::show_ldt()
{
  Space *s = Kobject::dcast<Task*>(reinterpret_cast<Kobject*>(task));
  Address addr, size;

  if (!s)
    {
      printf(" -- invalid task number '%lx'", task);
      return;
    }

  addr = s->_ldt.addr();
  size = s->_ldt.size();

  if (!size)
    {
      printf(" -- no LDT active");
      return;
    }

  printf("\nLDT of space %lx at " L4_PTR_FMT "-" L4_PTR_FMT "\n", task, addr, addr+size-1);

  Gdt_entry *desc = reinterpret_cast<Gdt_entry *>(addr);

  for (; size>=Cpu::Ldt_entry_size; size-=Cpu::Ldt_entry_size, desc++)
    {
      if (desc->present())
        {
          printf(" %5lx: ", (Mword)desc - addr);
          desc->show();
        }
    }
}

#line 287 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"


Jdb_module::Action_code
Jdb_misc_info::action(int cmd, void *&args, char const *&fmt, int &)
{
  switch (cmd)
    {
    case 0:
      // read/write physical memory
      if (args == &first_char)
	{
	  if (first_char == 'r' || first_char == 'w')
	    {
	      putchar(first_char);
	      fmt  = "%8x";
	      args = &addr;
	      return EXTRA_INPUT;
	    }
	}
      else if (args == &addr || args == &value)
	{
	  addr &= ~(sizeof(Mword)-1);
	  if (args == &value)
	    Jdb::poke_phys(addr, &value, sizeof(value));
	  if (first_char == 'w' && args == &addr)
	    putstr(" (");
	  else
	    putstr(" => ");
	  Jdb::peek_phys(addr, &value, sizeof(value));
	  printf(L4_MWORD_FMT, value);
	  if (first_char == 'w' && args == &addr)
	    {
	      putstr(") new value=");
	      fmt  = L4_MWORD_FMT;
	      args = &value;
	      return EXTRA_INPUT;
	    }
	  putchar('\n');
	}
      break;

    case 1:
      // read/write machine status register
      if (!Cpu::boot_cpu()->can_wrmsr())
	{
	  puts("MSR not supported");
	  return NOTHING;
	}

      if (args == &first_char)
	{
	  if (first_char == 'r' || first_char == 'w')
	    {
	      putchar(first_char);
	      fmt  = L4_ADDR_INPUT_FMT;
	      args = &addr;
	      return EXTRA_INPUT;
	    }
	}
      else if (args == &addr || args == &value64)
	{
	  Jdb::msr_test = Jdb::Msr_test_fail_warn;
	  if (args == &value64)
	    Cpu::wrmsr(value64, addr);
	  if (first_char == 'w' && (args == &addr))
	    putstr(" (");
	  else
	    putstr(" => ");
	  value64 = Cpu::rdmsr(addr);
	  printf(L4_X64_FMT, value64);
	  if (first_char == 'w' && (args == &addr))
	    {
	      putstr(") new value=");
	      fmt  = L4_X64_FMT;
	      args = &value64;
	      return EXTRA_INPUT;
	    }
	  putchar('\n');
	  Jdb::msr_test = Jdb::Msr_test_default;
	}
      break;
    }

  return NOTHING;
}

#line 372 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"


Jdb_module::Cmd const *
Jdb_misc_info::cmds() const
{
  static Cmd cs[] =
    {
	{ 0, "A", "adapter", "%C",
	  "A{r|w}<addr>\tread/write any physical address",
	  &first_char },
        { 1, "M", "msr", "%C",
	  "M{r|w}<addr>\tread/write machine status register",
	  &first_char },
    };
  return cs;
}

#line 388 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"


int
Jdb_misc_info::num_cmds() const
{
  return 2;
}

#line 395 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"


Jdb_misc_info::Jdb_misc_info()
  : Jdb_module("INFO")
{
}
