// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_bp.h"
#include "jdb_bp_i.h"

#line 114 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"

Breakpoint Jdb_bp::bps[4];
#line 116 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"

char const * const Breakpoint::mode_names[4] =
{
  "instruction", "write access", "i/o access", "r/w access"
};
#line 121 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"

char     Jdb_set_bp::breakpoint_cmd;
#line 123 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
char     Jdb_set_bp::breakpoint_restrict_cmd;
#line 124 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
Mword    Jdb_set_bp::breakpoint_number;
#line 125 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
Mword    Jdb_set_bp::breakpoint_length;
#line 126 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
Mword    Jdb_set_bp::breakpoint_restrict_task;
#line 127 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
Mword    Jdb_set_bp::breakpoint_restrict_thread;
#line 128 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
Jdb_set_bp::Restrict_reg  Jdb_set_bp::breakpoint_restrict_reg;
#line 129 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
Jdb_set_bp::Restrict_addr Jdb_set_bp::breakpoint_restrict_addr;
#line 130 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
int      Jdb_set_bp::state;
#line 413 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


STATIC_INITIALIZE_P(Jdb_bp, JDB_MODULE_INIT_PRIO);
#line 837 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"

static Jdb_set_bp jdb_set_bp INIT_PRIORITY(JDB_MODULE_INIT_PRIO);

#line 138 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


inline void
Breakpoint::kill()
{
  addr = 0;
}

#line 145 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


inline int
Breakpoint::unused()
{
  return addr == 0;
}

#line 152 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


inline int
Breakpoint::break_at_instruction()
{
  return mode == INSTRUCTION;
}

#line 159 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


inline int
Breakpoint::match_addr(Address virt, Mode m)
{
  return !unused() && addr == virt && mode == m;
}

#line 166 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


inline void
Breakpoint::set_logmode(char m)
{
  log = (m == '*') ? LOG : BREAK;
}

#line 173 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


inline int
Breakpoint::is_break()
{
  return !unused() && log == BREAK;
}

#line 188 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


inline void
Breakpoint::restrict_thread(int other, Mword thread)
{
  restrict.thread.other  = other;
  restrict.thread.thread = thread;
}

#line 196 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


inline void
Breakpoint::restrict_register(char reg, Mword y, Mword z)
{
  restrict.reg.reg = reg;
  restrict.reg.y   = y;
  restrict.reg.z   = z;
}

#line 205 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


inline void
Breakpoint::restrict_memory(Mword addr, Mword len, Mword y, Mword z)
{
  restrict.mem.addr = addr;
  restrict.mem.len  = len;
  restrict.mem.y    = y;
  restrict.mem.z    = z;
}

#line 215 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


inline void 
Breakpoint::clear_restriction()
{
  restrict.thread.thread = 0;
  restrict.task.task     = 0;
  restrict.reg.reg       = 0;
  restrict.mem.len       = 0;
}

#line 471 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


inline void
Jdb_bp::logmode_breakpoint(int num, char mode)
{
  bps[num].set_logmode(mode);
}

#line 551 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"



inline void
Jdb_bp::restrict_task(int num, int other, Mword task)
{
  bps[num].restrict_task(other, task);
}

#line 559 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


inline void
Jdb_bp::restrict_thread(int num, int other, Mword thread)
{
  bps[num].restrict_thread(other, thread);
}

#line 566 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


inline void
Jdb_bp::restrict_register(int num, char reg, Mword y, Mword z)
{
  bps[num].restrict_register(reg, y, z);
}

#line 573 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


inline void
Jdb_bp::restrict_memory(int num, Mword addr, Mword len, Mword y, Mword z)
{
  bps[num].restrict_memory(addr, len, y, z);
}

#line 580 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


inline void
Jdb_bp::clear_restriction(int num)
{
  bps[num].clear_restriction();
}

#line 131 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


Breakpoint::Breakpoint()
{
  restrict.thread.thread = 0;
  restrict.task.task     = 0;
}

#line 225 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


void
Breakpoint::show()
{
  if (addr)
    {
      printf("%5s on %12s at " L4_PTR_FMT,
	     log ? "LOG" : "BREAK", mode_names[mode & 3], addr);
      if (mode != INSTRUCTION)
	printf(" len %d", len);
      else
	putstr("      ");

      if (   restrict.thread.thread == 0
	  && restrict.task.task == 0
	  && restrict.reg.reg == 0
	  && restrict.mem.len == 0)
	puts(" (not restricted)");
      else
	{
	  int j = 0;
#if 0
	  printf("\n%32s", "restricted to ");
	  if (restrict.thread.thread != (GThread_num)-1)
	    {
	      j++;
	      printf("thread%s %x.%x\n",
		     restrict.thread.other ? " !=" : "",
		     L4_uid::task_from_gthread (restrict.thread.thread),
		     L4_uid::lthread_from_gthread (restrict.thread.thread));
	    }
	  if (restrict.task.task)
	    {
	      if (j++)
		printf("%32s", "and ");
	      printf("task%s %p\n",
		     restrict.task.other ? " !=" : "",
		     restrict.task.task);
	    }
#endif
	  if (restrict.reg.reg != 0)
	    {
	      if (j++)
		printf("%32s", "and ");
	      printf("register %s in [" L4_PTR_FMT ", " L4_PTR_FMT "]\n",
		  (restrict.reg.reg > 0) && (restrict.reg.reg < 10) 
		      ? Jdb_screen::Reg_names[restrict.reg.reg-1] 
		      : "???",
		   restrict.reg.y, restrict.reg.z);
	    }
	  if (restrict.mem.len != 0)
	    {
	      if (j++)
		printf("%32s", "and ");
	      printf("%d-byte var at " L4_PTR_FMT " in [" L4_PTR_FMT ", "
		     L4_PTR_FMT "]\n", 
		  restrict.mem.len, restrict.mem.addr, 
		  restrict.mem.y,   restrict.mem.z);
	    }
	}
    }
  else
    puts("disabled");
}

#line 290 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"

// return TRUE  if the breakpoint does NOT match
// return FALSE if all restrictions do match

int
Breakpoint::restricted(Thread *t)
{
  Jdb_entry_frame *e = Jdb::get_entry_frame(Jdb::current_cpu);

  Space *task = t->space();
#if 0
  // investigate for thread restriction
  if (restrict.thread.thread != (GThread_num)-1)
    {
      if (restrict.thread.other ^ (restrict.thread.thread != t->id().gthread()))
	return 1;
    }

  // investigate for task restriction
  if (restrict.task.task)
    {
      if (restrict.task.other ^ (restrict.task.task != task))
	return 1;
    }
#endif
  // investigate for register restriction
  if (restrict.reg.reg)
    {
      Mword val = e->get_reg(restrict.reg.reg);
      Mword y   = restrict.reg.y;
      Mword z   = restrict.reg.z;

      // return true if rules do NOT match
      if (  (y <= z && (val <  y || val >  z))
	  ||(y >  z && (val >= z || val <= y)))
	return 1;
    }

  // investigate for variable restriction
  if (restrict.mem.len)
    {
      Mword val = 0;
      Mword y   = restrict.mem.y;
      Mword z   = restrict.mem.z;

      if (Jdb::peek_task(restrict.mem.addr, task, &val, restrict.mem.len) != 0)
	return 0;

      // return true if rules do NOT match
      if (  (y <= z && (val <  y || val >  z))
	  ||(y >  z && (val >= z || val <= y)))
	return 1;
    }

  return 0;
}

#line 346 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


int
Breakpoint::test_break(Thread *t, char *errbuf, size_t bufsize)
{
  if (restricted(t))
    return 0;

  Space *task = t->space();

  snprintf(errbuf, bufsize, "break on %s at " L4_PTR_FMT,
           mode_names[mode], addr);
  if (mode==WRITE || mode==ACCESS)
    {
      // If it's a write or access (read) breakpoint, we look at the
      // appropriate place and print the bytes we find there. We do
      // not need to look if the page is present because the x86 CPU
      // enters the debug exception immediately _after_ the memory
      // access was performed.
      size_t size = strlen(errbuf);
      errbuf  += size;
      bufsize -= size;
      Mword val = 0;
      if (len > sizeof(Mword))
	return 0;

      if (Jdb::peek_task(addr, task, &val, len) != 0)
	return 0;

      snprintf(errbuf, bufsize, " [%08lx]", val);
    }
  return 1;
}

#line 379 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"

// Create log entry if breakpoint matches

void
Breakpoint::test_log(Thread *t)
{
  Jdb_entry_frame *e = Jdb::get_entry_frame(Jdb::current_cpu);

  if (log && !restricted(t))
    {
      Space *task = t->space();
      // log breakpoint
      Mword value = 0;

      if (mode == WRITE || mode == ACCESS)
	{
	  // If it's a write or access (read) breakpoint, we look at the
	  // appropriate place and print the bytes we find there. We do
	  // not need to look if the page is present because the x86 CPU
	  // enters the debug exception immediately _after_ the memory
	  // access was performed.
	  if (len > sizeof(Mword))
	    return;

	  if (Jdb::peek_task(addr, task, &value, len) != 0)
	    return;
	}

      // is called with disabled interrupts
      Tb_entry_bp *tb = static_cast<Tb_entry_bp*>(Jdb_tbuf::new_entry());
      tb->set(t, e->ip(), mode, len, value, addr);
      Jdb_tbuf::commit_entry();
    }
}

#line 416 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"

FIASCO_INIT
void
Jdb_bp::init()
{
  static Jdb_handler enter(at_jdb_enter);
  static Jdb_handler leave(at_jdb_leave);

  Jdb::jdb_enter.add(&enter);
  Jdb::jdb_leave.add(&leave);

  init_arch();
}

#line 448 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


int
Jdb_bp::set_breakpoint(int num, Address addr, Mword len,
		       Breakpoint::Mode mode, Breakpoint::Log log,
		       Task *task)
{
  if (set_debug_address_register(num, addr, len, mode, task))
    {
      bps[num].set(addr, len, mode, log);
      return 1;
    }

  return 0;
}

#line 463 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


void 
Jdb_bp::clr_breakpoint(int num)
{
  clr_debug_address_register(num);
  bps[num].kill();
}

#line 478 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


int
Jdb_bp::first_unused()
{
  int i;

  for (i=0; i<4 && !bps[i].unused(); i++)
    ;

  return i;
}

#line 490 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"

// Return 1 if a breakpoint hits

int
Jdb_bp::test_break(Mword dr6, char *errbuf, size_t bufsize)
{
  Thread *t = Jdb::get_thread(Cpu_number::boot_cpu());
  Jdb_entry_frame *e = Jdb::get_entry_frame(Cpu_number::boot_cpu());

  for (int i=0; i<4; i++)
    if (dr6 & (1<<i))
      {
	if (bps[i].break_at_instruction())
      	  e->flags(e->flags() | EFLAGS_RF);
	if (bps[i].test_break(t, errbuf, bufsize))
	  return 1;
      }

  return 0;
}

#line 510 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"

// Create log entry if breakpoint matches.
// Return 1 if debugger should stop

void
Jdb_bp::test_log(Mword &dr6)
{
  Thread *t = Jdb::get_thread(Cpu_number::boot_cpu());
  Jdb_entry_frame *e = Jdb::get_entry_frame(Cpu_number::boot_cpu());

  for (int i=0; i<4; i++)
    if (dr6 & (1<<i))
      {
	if (!bps[i].is_break())
	  {
	    // create log entry
	    bps[i].test_log(t);
	    // consider instruction breakpoints
	    if (bps[i].break_at_instruction())
	      e->flags(e->flags() | EFLAGS_RF);
	    // clear condition
	    dr6 &= ~(1<<i);
	  }
      }
}

#line 535 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


Mword
Jdb_bp::test_match(Address addr, Breakpoint::Mode mode)
{
  for (int i=0; i<4; i++)
    if (bps[i].match_addr(addr, mode))
      return i+1;

  return 0;
}

#line 546 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


int
Jdb_bp::instruction_bp_at_addr(Address addr)
{ return test_match(addr, Breakpoint::INSTRUCTION); }

#line 587 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


void 
Jdb_bp::list()
{
  putchar('\n');

  for(int i=0; i<4; i++)
    {
      printf("  #%d: ", i+1);
      bps[i].show();
    }

  putchar('\n');
}

#line 602 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


//---------------------------------------------------------------------------//


Jdb_set_bp::Jdb_set_bp()
  : Jdb_module("DEBUGGING")
{}

#line 610 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


Jdb_module::Action_code
Jdb_set_bp::action(int cmd, void *&args, char const *&fmt, int &next_char)
{
  Jdb_module::Action_code code;
  Breakpoint::Mode mode;

  if (cmd == 0)
    {
      if (args == &breakpoint_cmd)
	{
	  switch (breakpoint_cmd)
	    {
	    case 'p':
	      if (!(Cpu::boot_cpu()->features() & FEAT_DE))
		{
		  puts(" I/O breakpoints not supported by this CPU");
		  return NOTHING;
		}
	      // fall through
	    case 'a':
	    case 'i':
	    case 'w':
	      if ((breakpoint_number = Jdb_bp::first_unused()) < 4)
		{
		  fmt   = " addr=%C";
		  args  = &Jdb_input_task_addr::first_char;
		  state = 1; // breakpoints are global for all tasks
		  return EXTRA_INPUT;
		}
	      puts(" No breakpoints available");
	      return NOTHING;
	    case 'l':
	      // show all breakpoints
	      Jdb_bp::list();
	      return NOTHING;
	    case '-':
	      // delete breakpoint
	    case '+':
	      // set logmode of breakpoint to <STOP>
	    case '*':
	      // set logmode of breakpoint to <LOG>
	    case 'r':
	      // restrict breakpoint
	      fmt   = " bpn=%1x";
	      args  = &breakpoint_number;
	      state = 2;
	      return EXTRA_INPUT;
	    case 't':
	      Jdb::execute_command("bt");
	      break;
	    default:
	      return ERROR;
	    }
	}
      else switch (state)
	{
	case 1:
	  code = Jdb_input_task_addr::action(args, fmt, next_char);
	  if (code == ERROR)
	    return ERROR;
	  if (code == NOTHING)
	    // ok, continue
	    goto got_address;
	  // more input for Jdb_input_task_addr
	  return code;
	case 2:
	  if (breakpoint_number < 1 || breakpoint_number > 4)
	    return ERROR;
	  // input is 1..4 but numbers are 0..3
	  breakpoint_number -= 1;
	  // we know the breakpoint number
	  switch (breakpoint_cmd)
	    {
	    case '-':
	      Jdb_bp::clr_breakpoint(breakpoint_number);
	      putchar('\n');
	      return NOTHING;
	    case '+':
	    case '*':
	      Jdb_bp::logmode_breakpoint(breakpoint_number, breakpoint_cmd);
	      putchar('\n');
	      return NOTHING;
	    case 'r':
	      fmt   = " %C";
	      args  = &breakpoint_restrict_cmd;
	      state = 5;
	      return EXTRA_INPUT;
	    default:
	      return ERROR;
	    }
	  break;
	case 3:
got_address:
	  // address/task read
	  if (breakpoint_cmd != 'i')
	    {
	      fmt   = " len (1, 2, 4...)=%1x";
	      args  = &breakpoint_length;
	      state = 4;
	      return EXTRA_INPUT;
	    }
	  breakpoint_length = 1; // must be 1 for instruction breakpoints
	  // fall through
	case 4:
	  // length read
	  if (breakpoint_length & (breakpoint_length - 1))
	    break;
	  if (breakpoint_length > sizeof(Mword))
	    break;
          switch (breakpoint_cmd)
	    {
	    default : return ERROR;
	    case 'i': mode = Breakpoint::INSTRUCTION; break;
	    case 'w': mode = Breakpoint::WRITE;       break;
	    case 'p': mode = Breakpoint::PORTIO;      break;
	    case 'a': mode = Breakpoint::ACCESS;      break;
	    }
	  // abort if no address was given
	  if (Jdb_input_task_addr::addr() == (Address)-1)
	    return ERROR;
	  Jdb_bp::set_breakpoint(breakpoint_number, Jdb_input_task_addr::addr(),
				 breakpoint_length, mode, Breakpoint::BREAK,
				 Jdb_input_task_addr::task());
	  putchar('\n');
	  break;
	case 5:
	  // restrict command read
	  switch (breakpoint_restrict_cmd)
	    {
	    case 'a':
	    case 'A':
	      fmt   = (breakpoint_restrict_cmd=='A')
			? "task!=" L4_ADDR_INPUT_FMT "\n"
                        : "task==" L4_ADDR_INPUT_FMT "\n";
	      args  = &breakpoint_restrict_task;
	      state = 6;
	      return EXTRA_INPUT;
	    case 't':
	    case 'T':
	      fmt   = (breakpoint_restrict_cmd=='T')
			? "thread!=%t\n" : "thread==%t\n";
	      args  = &breakpoint_restrict_thread;
	      state = 7;
	      return EXTRA_INPUT;
	    case 'e':
	      if (!Jdb::get_register(&breakpoint_restrict_reg.reg))
		return NOTHING;
	      fmt  = " in [" L4_ADDR_INPUT_FMT "-" L4_ADDR_INPUT_FMT "]\n";
    	      args = &breakpoint_restrict_reg.low;
	      state = 8;
	      return EXTRA_INPUT;
	    case '1':
	    case '2':
	    case '4':
	      putchar(breakpoint_restrict_cmd);
	      fmt   = "-byte addr=" L4_ADDR_INPUT_FMT
		      " between[" L4_ADDR_INPUT_FMT "-" L4_ADDR_INPUT_FMT "]\n";
	      args  = &breakpoint_restrict_addr;
	      state = 9;
	      return EXTRA_INPUT;
	    case '-':
	      Jdb_bp::clear_restriction(breakpoint_number);
	      putchar('\n');
	      break;
	    default:
	      return ERROR;
	    }
	  break;
	case 6:
	  // breakpoint restrict task read
	  Jdb_bp::restrict_task(breakpoint_number,
				breakpoint_restrict_cmd == 'A',
				breakpoint_restrict_task);
	  break;
	case 7:
	  // breakpoint restrict thread read
	  Jdb_bp::restrict_thread(breakpoint_number,
				  breakpoint_restrict_cmd == 'T',
				  breakpoint_restrict_thread);
	  break;
	case 8:
	  // breakpoint restrict register in range
	  Jdb_bp::restrict_register(breakpoint_number,
				    breakpoint_restrict_reg.reg,
				    breakpoint_restrict_reg.low,
				    breakpoint_restrict_reg.high);
	  break;
	case 9:
	  // breakpoint restrict x-byte-value in range
	  Jdb_bp::restrict_memory(breakpoint_number,
				  breakpoint_restrict_addr.addr,
				  breakpoint_restrict_cmd - '0',
				  breakpoint_restrict_addr.low,
				  breakpoint_restrict_addr.high);
	  break;
	}
    }
  return NOTHING;
}

#line 811 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


Jdb_module::Cmd const *
Jdb_set_bp::cmds() const
{
  static Cmd cs[] = 
    {
	{ 0, "b", "bp", "%c",
	  "b{i|a|w|p}<addr>\tset breakpoint on instruction/access/write/io "
	  "access\n"
	  "b{-|+|*}<num>\tdisable/enable/log breakpoint\n"
	  "bl\tlist breakpoints\n"
	  "br<num>{t|T|a|A|e|1|2|4}\trestrict breakpoint to "
	  "(!)thread/(!)task/reg/mem",
	  &breakpoint_cmd },
    };

  return cs;
}

#line 830 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


int
Jdb_set_bp::num_cmds() const
{
  return 1;
}
