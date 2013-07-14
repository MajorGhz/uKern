// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb.h"
#include "jdb_i.h"

#line 138 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

char Jdb::_connected;			// Jdb::init() was done
#line 140 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
// explicit single_step command
DEFINE_PER_CPU Per_cpu<char> Jdb::permanent_single_step;
#line 142 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
volatile char Jdb::msr_test;		// = 1: trying to access an msr
#line 143 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
volatile char Jdb::msr_fail;		// = 1: MSR access failed
#line 144 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
DEFINE_PER_CPU Per_cpu<char> Jdb::code_ret; // current instruction is ret/iret
#line 145 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
DEFINE_PER_CPU Per_cpu<char> Jdb::code_call;// current instruction is call
#line 146 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
DEFINE_PER_CPU Per_cpu<char> Jdb::code_bra; // current instruction is jmp/jxx
#line 147 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
DEFINE_PER_CPU Per_cpu<char> Jdb::code_int; // current instruction is int x
#line 148 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

// special single step state
DEFINE_PER_CPU Per_cpu<Jdb::Step_state> Jdb::ss_state;
#line 151 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
DEFINE_PER_CPU Per_cpu<int> Jdb::ss_level;  // current call level
#line 152 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

const Unsigned8*Jdb::debug_ctrl_str;	// string+length for remote control of
#line 154 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
int             Jdb::debug_ctrl_len;	// Jdb via enter_kdebugger("*#");
#line 155 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

Pic::Status Jdb::pic_status;
#line 157 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
DEFINE_PER_CPU Per_cpu<unsigned> Jdb::apic_tpr;
#line 158 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
DEFINE_PER_CPU Per_cpu<int> Jdb::jdb_irqs_disabled;
#line 159 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

int  (*Jdb::bp_test_log_only)();
#line 161 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
int  (*Jdb::bp_test_sstep)();
#line 162 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
int  (*Jdb::bp_test_break)(char *errbuf, size_t bufsize);
#line 163 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
int  (*Jdb::bp_test_other)(char *errbuf, size_t bufsize);
#line 164 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

// available from the jdb_dump module
int jdb_dump_addr_task (Address addr, Space *task, int level)
  __attribute__((weak));
#line 168 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"


STATIC_INITIALIZE_P(Jdb,JDB_INIT_PRIO);
#line 236 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"


DEFINE_PER_CPU static Per_cpu<Proc::Status> jdb_saved_flags;
#line 479 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

#define WEAK __attribute__((weak))
#line 481 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
extern "C" char in_slowtrap, in_page_fault, in_handle_fputrap;
#line 482 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
extern "C" char in_interrupt, in_timer_interrupt, in_timer_interrupt_slow;
#line 483 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
extern "C" char i30_ret_switch WEAK, se_ret_switch WEAK, in_slow_ipc1 WEAK;
#line 484 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
extern "C" char in_slow_ipc2 WEAK, in_slow_ipc4;
#line 485 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
extern "C" char in_slow_ipc5, in_sc_ipc1 WEAK;
#line 486 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
extern "C" char in_sc_ipc2 WEAK, in_syscall WEAK;
#line 487 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#undef WEAK

#line 655 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

// entered debugger because of single step trap
inline int
Jdb::handle_single_step(Cpu_number cpu)
{
  int really_break = 1;

  analyze_code(cpu);

  Cpu const &ccpu = Cpu::cpus.cpu(cpu);

  // special single_step ('j' command): go until branch/return
  if (ss_state.cpu(cpu) != SS_NONE)
    {
      if (ccpu.lbr_type() != Cpu::Lbr_unsupported)
	{
	  // don't worry, the CPU always knows what she is doing :-)
	}
      else
	{
	  // we have to emulate lbr looking at the code ...
	  switch (ss_state.cpu(cpu))
	    {
	    case SS_RETURN:
	      // go until function return
	      really_break = 0;
	      if (code_call.cpu(cpu))
		{
		  // increase call level
		  ss_level.cpu(cpu)++;
		}
	      else if (code_ret.cpu(cpu))
		{
		  // decrease call level
		  really_break = (ss_level.cpu(cpu)-- == 0);
		}
	      break;
	    case SS_BRANCH:
	    default:
	      // go until next branch
	      really_break = (code_ret.cpu(cpu) || code_call.cpu(cpu) || code_bra.cpu(cpu) || code_int.cpu(cpu));
	      break;
	    }
	}

      if (really_break)
	{
	  // condition met
	  ss_state.cpu(cpu) = SS_NONE;
	  snprintf(error_buffer.cpu(cpu), sizeof(error_buffer.cpu(Cpu_number::boot_cpu())), "%s", "Branch/Call");
	}
    }
  else // (ss_state == SS_NONE)
    // regular single_step
    snprintf(error_buffer.cpu(cpu), sizeof(error_buffer.cpu(Cpu_number::boot_cpu())), "%s", "Singlestep");

  return really_break;
}

#line 713 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

// entered debugger due to debug exception
inline int
Jdb::handle_trap1(Cpu_number cpu)
{
  // FIXME: currently only on bot cpu
  if (cpu != Cpu_number::boot_cpu())
    return 0;

  if (bp_test_sstep && bp_test_sstep())
    return handle_single_step(cpu);

  if (bp_test_break
      && bp_test_break(error_buffer.cpu(cpu), sizeof(error_buffer.cpu(Cpu_number::boot_cpu()))))
    return 1;

  if (bp_test_other
      && bp_test_other(error_buffer.cpu(cpu), sizeof(error_buffer.cpu(Cpu_number::boot_cpu()))))
    return 1;

  return 0;
}

#line 735 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

// entered debugger due to software breakpoint
inline int
Jdb::handle_trap3(Cpu_number cpu)
{
  Jdb_entry_frame *entry_frame = Jdb::entry_frame.cpu(cpu);
  Space *task = get_task(cpu);
  Unsigned8 op;
  Unsigned8 len;

  snprintf(error_buffer.cpu(cpu), sizeof(error_buffer.cpu(Cpu_number::boot_cpu())), "%s", "INT 3");
  if (   !peek((Unsigned8*)entry_frame->ip(), task, op)
      || !peek((Unsigned8*)(entry_frame->ip()+1), task, len)
      || op != 0xeb)
    return 1;

  char const *msg = (char const*)(entry_frame->ip()+2);
  char buffer[3];
  if (!peek(msg, task, buffer[0]))
    return 1;

  if (len > 1 && !peek(msg+1, task, buffer[1]))
    return 1;

  // we are entering here because enter_kdebugger("*#..."); failed
  if (len > 1 && buffer[0] == '*' && buffer[1] == '#')
    {
      unsigned i;
      char ctrl[29];

      len-=2;
      msg+=2;
      if (len && peek(msg, task, buffer[2]))
	{
	  char tmp;
	  if (buffer[2] == '#')
	    {
	      // the ``-jdb_cmd='' sequence
	      msg = (char const*)entry_frame->value();
	      for (i=0; i<sizeof(ctrl)-1 && peek(msg, task, tmp) && tmp; i++, msg++)
		ctrl[i] = tmp;
	    }
	  else
	    {
	      // a ``enter_kdebug("*#")'' sequence
	      for (i=0; i<sizeof(ctrl)-1 && i<len && peek(msg, task, tmp); i++, msg++)
		ctrl[i] = tmp;
	    }
	  ctrl[i] = '\0';
	  snprintf(error_buffer.cpu(cpu), sizeof(error_buffer.cpu(Cpu_number::boot_cpu())),
	      "invalid ctrl sequence \"%s\"", ctrl);
	}
    }
  // enter_kdebugger("...");
  else if (len > 0)
    {
      unsigned i;
      len = len < 47 ? len : 47;
      len =   len < sizeof(error_buffer.cpu(Cpu_number::boot_cpu()))-1
            ? len
            : sizeof(error_buffer.cpu(Cpu_number::boot_cpu()))-1;

      for(i=0; i<len && peek(msg+i, task, buffer[0]); i++)
	error_buffer.cpu(cpu)[i] = buffer[0];
      error_buffer.cpu(cpu)[i]='\0';
    }

  return 1;
}

#line 804 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

// entered debugger due to other exception
inline int
Jdb::handle_trapX(Cpu_number cpu)
{
  unsigned pos = snprintf(error_buffer.cpu(cpu), sizeof(error_buffer.cpu(Cpu_number::boot_cpu())), "%s",
			  Cpu::exception_string(entry_frame.cpu(cpu)->_trapno)) + 1;
  if (   pos < sizeof(error_buffer.cpu(Cpu_number::boot_cpu()))
      && entry_frame.cpu(cpu)->_trapno >= 10
      && entry_frame.cpu(cpu)->_trapno <= 14)
    snprintf(error_buffer.cpu(cpu)+pos, sizeof(error_buffer.cpu(Cpu_number::boot_cpu()))-pos,
             "(ERR=" L4_PTR_FMT ")", entry_frame.cpu(cpu)->_err);

  return 1;
}

#line 75 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"


void Jdb::init_serial_console()
{
  if (Config::serial_esc == Config::SERIAL_ESC_IRQ &&
      !Kernel_uart::uart()->failed())
    {
      int irq;

      if ((irq = Kernel_uart::uart()->irq()) == -1)
	{
	  Config::serial_esc = Config::SERIAL_ESC_NOIRQ;
	  puts("SERIAL ESC: Using serial hack in slow timer handler.");
	}
      else
	{
	  Kernel_uart::enable_rcv_irq();
	  printf("SERIAL ESC: allocated IRQ %d for serial uart\n", irq);
	}
    }
}

#line 171 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"


FIASCO_INIT FIASCO_NOINLINE
void Jdb::init()
{
  if (Koptions::o()->opt(Koptions::F_nojdb))
    return;

  if (Koptions::o()->opt(Koptions::F_jdb_never_stop))
    never_break = 1;

  init_serial_console();

  Trap_state::base_handler = (Trap_state::Handler)enter_jdb;

  // if esc_hack, serial_esc or watchdog enabled, set slow timer handler
  Idt::set_vectors_run();

  // disable lbr feature per default since it eats cycles on AMD Athlon boxes
  Cpu::boot_cpu()->lbr_enable(false);

  Kconsole::console()->register_console(push_cons());

  Thread::set_int3_handler(handle_int3_threadctx);

  _connected = true;
  Thread::may_enter_jdb = true;
}

#line 239 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

// disable interrupts before entering the kernel debugger

void
Jdb::save_disable_irqs(Cpu_number cpu)
{
  if (!jdb_irqs_disabled.cpu(cpu)++)
    {
      // save interrupt flags
      jdb_saved_flags.cpu(cpu) = Proc::cli_save();

      if (cpu == Cpu_number::boot_cpu())
	{
	  Watchdog::disable();
	  pic_status = Pic::disable_all_save();
          if (Config::getchar_does_hlt_works_ok)
            Timer_tick::disable(Cpu_number::boot_cpu());
	}
      if (Io_apic::active() && Apic::is_present())
	{
	  apic_tpr.cpu(cpu) = Apic::tpr();
	  Apic::tpr(APIC_IRQ_BASE - 0x10);
	}

      if (cpu == Cpu_number::boot_cpu() && Config::getchar_does_hlt_works_ok)
	{
	  // set timer interrupt does nothing than wakeup from hlt
	  Timer_tick::set_vectors_stop();
	  Timer_tick::enable(Cpu_number::boot_cpu());
	}

    }

  if (cpu == Cpu_number::boot_cpu() && Config::getchar_does_hlt_works_ok)
    // explicit enable interrupts because the timer interrupt is
    // needed to wakeup from "hlt" state in getchar(). All other
    // interrupts are disabled at the pic.
    Proc::sti();
}

#line 278 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

// restore interrupts after leaving the kernel debugger

void
Jdb::restore_irqs(Cpu_number cpu)
{
  if (!--jdb_irqs_disabled.cpu(cpu))
    {
      Proc::cli();

      if (Io_apic::active() && Apic::is_present())
	Apic::tpr(apic_tpr.cpu(cpu));

      if (cpu == Cpu_number::boot_cpu())
	{
	  Pic::restore_all(Jdb::pic_status);
	  Watchdog::enable();
	}

      // reset timer interrupt vector
      if (cpu == Cpu_number::boot_cpu() && Config::getchar_does_hlt_works_ok)
      	Idt::set_vectors_run();

      // reset interrupt flags
      Proc::sti_restore(jdb_saved_flags.cpu(cpu));
    }
}

#line 318 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

// Do thread lookup using Trap_state. In contrast to Thread::current_thread()
// this function can also handle cases where we entered from kernel stack
// context. We _never_ return 0!

Thread*
Jdb::get_thread(Cpu_number cpu)
{
  Jdb_entry_frame *entry_frame = Jdb::entry_frame.cpu(cpu);
  Address sp = (Address) entry_frame;

  // special case since we come from the double fault handler stack
  if (entry_frame->_trapno == 8 && !(entry_frame->cs() & 3))
    sp = entry_frame->sp(); // we can trust esp since it comes from main_tss

  if (foreach_cpu(On_dbg_stack(sp), false))
    return 0;

  if (!Helping_lock::threading_system_active)
    return 0;

  return static_cast<Thread*>(context_of((const void*)sp));
}

#line 341 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"


Space *
Jdb::translate_task(Address addr, Space *task)
{
  return (Kmem::is_kmem_page_fault(addr, 0)) ? 0 : task;
}

#line 348 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"


void
Jdb::peek_phys(Address phys, void *value, int width)
{
  assert(!(phys & (width-1)));

  Address virt = Kmem::map_phys_page_tmp(phys, 0);

  memcpy(value, (void*)virt, width);
}

#line 359 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"


void
Jdb::poke_phys(Address phys, void const *value, int width)
{
  assert(!(phys & (width-1)));

  Address virt = Kmem::map_phys_page_tmp(phys, 0);

  memcpy((void*)virt, value, width);
}

#line 370 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"



int
Jdb::peek_task(Address addr, Space *task, void *value, int width)
{
  Address phys;

  if (!task && Kmem::is_kmem_page_fault(addr, 0))
    {
      // address of kernel directory
      Address pdbr;
      asm volatile ("mov %%cr3, %0" : "=r" (pdbr));
      Pdir *kdir = (Pdir*)Mem_layout::phys_to_pmem(pdbr);
      auto i = kdir->walk(Virt_addr(addr));
      if (i.is_valid())
	{
          memcpy(value, (void*)addr, width);
          return 0;
	}
    }
  // specific address space, use temporary mapping
  if (!task)
    phys = addr;
  else
    {
      // user address, use temporary mapping
      phys = Address(task->virt_to_phys (addr));

      if (phys == ~0UL)
	phys = task->virt_to_phys_s0((void*)addr);

      if (phys == ~0UL)
	return -1;
    }

  peek_phys(phys, value, width);
  return 0;
}

#line 409 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"


int
Jdb::poke_task(Address addr, Space *task, void const *value, int width)
{
  Address phys;

  if (task && Kmem::is_kmem_page_fault(addr, 0))
    {
      Address pdbr;
      asm volatile ("mov %%cr3, %0" : "=r" (pdbr));
      Pdir *kdir = (Pdir*)Mem_layout::phys_to_pmem(pdbr);
      auto i = kdir->walk(Virt_addr(addr));
      if (i.is_valid())
	{
          memcpy((void*)addr, value, width);
          return 0;
	}
    }

  if (!task)
    phys = addr;
  else
    {
      // user address, use temporary mapping
      phys = Address(task->virt_to_phys(addr));

      if (phys == ~0UL)
	phys = task->virt_to_phys_s0((void*)addr);

      if (phys == ~0UL)
	return -1;
    }

  poke_phys(phys, value, width);
  return 0;
}

#line 446 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

// The content of apdapter memory is not shown by default because reading
// memory-mapped I/O registers may confuse the hardware. We assume that all
// memory above the end of the RAM is adapter memory.

int
Jdb::is_adapter_memory(Address virt, Space *task)
{
  Address phys;

  if (!task)
    // phys requested
    phys = virt;
  else if (   !Kmem::is_io_bitmap_page_fault(virt)
           &&  Kmem::is_kmem_page_fault(virt, 0))
    // kernel address
    phys = Kmem::virt_to_phys((const void*)virt);
  else
    // user address
    phys = task->virt_to_phys_s0((void*)virt);

  if (phys == ~0UL)
    return false;

  Mem_desc *m = Kip::k()->mem_descs();
  Mem_desc *e = m + Kip::k()->num_mem_descs();
  for (; m != e; ++m)
    if (m->type() == Mem_desc::Conventional && !m->is_virtual()
	&& m->start() <= phys && m->end() >= phys)
      return false;

  return true;
}

#line 488 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

// Try to guess the thread state of t by walking down the kernel stack and
// locking at the first return address we find.

Jdb::Guessed_thread_state
Jdb::guess_thread_state(Thread *t)
{
  Guessed_thread_state state = s_unknown;
  Mword *ktop = (Mword*)((Mword)context_of(t->get_kernel_sp()) +
			  Context::Size);

  for (int i=-1; i>-26; i--)
    {
      if (ktop[i] != 0)
	{
	  if (ktop[i] == (Mword)&in_page_fault)
	    state = s_pagefault;
	  if ((ktop[i] == (Mword)&i30_ret_switch) ||// shortcut.S, int 0x30
	      (ktop[i] == (Mword)&in_slow_ipc1) ||  // shortcut.S, int 0x30
	      (ktop[i] == (Mword)&se_ret_switch) || // shortcut.S, sysenter
	      (ktop[i] == (Mword)&in_slow_ipc2) ||  // shortcut.S, sysenter
	      (ktop[i] == (Mword)&in_slow_ipc4) ||  // entry.S, int 0x30 log
	      (ktop[i] == (Mword)&in_slow_ipc5) ||  // entry.S, sysenter log
#if defined (CONFIG_JDB_LOGGING) || !defined(CONFIG_ASSEMBLER_IPC_SHORTCUT)
	      (ktop[i] == (Mword)&in_sc_ipc1)   ||  // entry.S, int 0x30
	      (ktop[i] == (Mword)&in_sc_ipc2)   ||  // entry.S, sysenter
#endif
	     0)
	    state = s_ipc;
	  else if (ktop[i] == (Mword)&in_syscall)
	    state = s_syscall;
	  else if (ktop[i] == (Mword)&Thread::user_invoke)
	    state = s_user_invoke;
	  else if (ktop[i] == (Mword)&in_handle_fputrap)
	    state = s_fputrap;
	  else if (ktop[i] == (Mword)&in_interrupt)
	    state = s_interrupt;
	  else if ((ktop[i] == (Mword)&in_timer_interrupt) ||
		   (ktop[i] == (Mword)&in_timer_interrupt_slow))
	    state = s_timer_interrupt;
	  else if (ktop[i] == (Mword)&in_slowtrap)
	    state = s_slowtrap;
	  if (state != s_unknown)
	    break;
	}
    }

  if (state == s_unknown && (t->state(false) & Thread_ipc_mask))
    state = s_ipc;

  return state;
}

#line 540 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"


void
Jdb::set_single_step(Cpu_number cpu, int on)
{
  if (on)
    entry_frame.cpu(cpu)->flags(entry_frame.cpu(cpu)->flags() | EFLAGS_TF);
  else
    entry_frame.cpu(cpu)->flags(entry_frame.cpu(cpu)->flags() & ~EFLAGS_TF);

  permanent_single_step.cpu(cpu) = on;
}

#line 552 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"


bool
Jdb::handle_special_cmds(int c)
{
  foreach_cpu(&analyze_code);

  switch (c)
    {
    case 'j': // do restricted "go"
      switch (putchar(c=getchar()))
	{
	case 'b': // go until next branch
	case 'r': // go until current function returns
	  ss_level.cpu(current_cpu) = 0;
	  if (code_call.cpu(current_cpu))
	    {
	      // increase call level because currently we
	      // stay on a call instruction
	      ss_level.cpu(current_cpu)++;
	    }
	  ss_state.cpu(current_cpu) = (c == 'b') ? SS_BRANCH : SS_RETURN;
	  // if we have lbr feature, the processor treats the single
	  // step flag as step on branches instead of step on instruction
	  Cpu::boot_cpu()->btf_enable(true);
	  // fall through
	case 's': // do one single step
	  entry_frame.cpu(current_cpu)->flags(entry_frame.cpu(current_cpu)->flags() | EFLAGS_TF);
	  hide_statline = false;
	  return 0;
	default:
	  abort_command();
	  break;
	}
      break;
    default:
      backspace();
      // ignore character and get next input
      break;
    }

  return 1;

}

#line 599 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

// take a look at the code of the current thread eip
// set global indicators code_call, code_ret, code_bra, code_int
// This can fail if the current page is still not mapped
void
Jdb::analyze_code(Cpu_number cpu)
{
  Jdb_entry_frame *entry_frame = Jdb::entry_frame.cpu(cpu);
  Space *task = get_task(cpu);
  // do nothing if page not mapped into this address space
  if (entry_frame->ip()+1 > Kmem::user_max())
    return;

  Unsigned8 op1, op2;

  if (   !peek((Unsigned8*)entry_frame->ip(), task, op1)
      || !peek((Unsigned8*)(entry_frame->ip()+1), task, op2))
    return;

  if (op1 != 0x0f && op1 != 0xff)
    op2 = 0;

  code_ret.cpu(cpu) =
	      (   ((op1 & 0xf6) == 0xc2)	// ret/lret /xxxx
	       || (op1 == 0xcf));		// iret

  code_call.cpu(cpu) =
	      (   (op1 == 0xe8)			// call near
	       || ((op1 == 0xff)
	           && ((op2 & 0x30) == 0x10))	// call/lcall *(...)
	       || (op1 == 0x9a));		// lcall xxxx:xxxx

  code_bra.cpu(cpu) =
	      (   ((op1 & 0xfc) == 0xe0)	// loop/jecxz
	       || ((op1 & 0xf0) == 0x70)	// jxx rel 8 bit
	       || (op1 == 0xeb)			// jmp rel 8 bit
	       || (op1 == 0xe9)			// jmp rel 16/32 bit
	       || ((op1 == 0x0f)
	           && ((op2 & 0xf0) == 0x80))	// jxx rel 16/32 bit
	       || ((op1 == 0xff)
	           && ((op2 & 0x30) == 0x20))	// jmp/ljmp *(...)
	       || (op1 == 0xea));		// ljmp xxxx:xxxx

  code_int.cpu(cpu) =
	      (   (op1 == 0xcc)			// int3
	       || (op1 == 0xcd)			// int xx
	       || (op1 == 0xce));		// into
}

#line 819 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

/** Int3 debugger interface. This function is called immediately
 * after entering the kernel debugger.
 * @return 1 if command was successfully interpreted
 */

bool
Jdb::handle_user_request(Cpu_number cpu)
{
  Jdb_entry_frame *entry_frame = Jdb::entry_frame.cpu(cpu);

  if (entry_frame->debug_ipi())
    return cpu != Cpu_number::boot_cpu();

  if (entry_frame->_trapno == 3)
    {
      Space *task = get_task(cpu);
      Unsigned8 todo;
      if (!peek((Unsigned8*)entry_frame->ip(), task, todo))
	return false;

      // jmp == enter_kdebug()
      if (todo == 0xeb)
	{
	  Unsigned8 len;
	  if (!peek((Unsigned8*)(entry_frame->ip()+1), task, len))
	    return false;

	  char const *str = (char const *)(entry_frame->ip()+2);
	  char tmp;

	  if (len <= 2)
	    return false;

	  if (!peek(str, task, tmp) || tmp !='*')
	    return false;

	  if (!peek(str+1, task, tmp) || tmp != '#')
	    return false;

	  int ret;

	  if (peek(str+2, task, tmp) && tmp == '#')
	    ret = execute_command_ni(task, (char const *)entry_frame->value());
	  else
	    ret = execute_command_ni(task, str+2, len-2);

	  if (ret)
	    return 1;
	}
      // cmpb
      else if (todo == 0x3c)
	{
	  if (!peek((Unsigned8*)(entry_frame->ip()+1), task, todo))
	    return false;

	  switch (todo)
	    {
	    case 29:
	      if (entry_frame->value() == 3)
		{
		  Watchdog::disable();
		  execute_command("Tgzip");
		  Watchdog::enable();
		  return 1;
		}
	      break;
	    }
	}
    }
  return 0;
}

#line 891 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"


void
Jdb::enter_trap_handler(Cpu_number cpu)
{ Cpu::cpus.cpu(cpu).debugctl_disable(); }

#line 896 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"


void
Jdb::leave_trap_handler(Cpu_number cpu)
{ Cpu::cpus.cpu(cpu).debugctl_enable(); }

#line 901 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"


bool
Jdb::handle_conditional_breakpoint(Cpu_number cpu)
{ return entry_frame.cpu(cpu)->_trapno == 1 && bp_test_log_only && bp_test_log_only(); }

#line 906 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"


void
Jdb::handle_nested_trap(Jdb_entry_frame *e)
{
  // re-enable interrupts if we need them because they are disabled
  if (Config::getchar_does_hlt_works_ok)
    Proc::sti();

  switch (e->_trapno)
    {
    case 2:
      cursor(Jdb_screen::height(), 1);
      printf("\nNMI occured\n");
      break;
    case 3:
      cursor(Jdb_screen::height(), 1);
      printf("\nSoftware breakpoint inside jdb at " L4_PTR_FMT "\n",
             e->ip()-1);
      break;
    case 13:
      switch (msr_test)
	{
	case Msr_test_fail_warn:
	  printf(" MSR does not exist or invalid value\n");
	  msr_test = Msr_test_default;
	  msr_fail = 1;
	  break;
	case Msr_test_fail_ignore:
	  msr_test = Msr_test_default;
	  msr_fail = 1;
	  break;
	default:
	  cursor(Jdb_screen::height(), 1);
	  printf("\nGeneral Protection (eip=" L4_PTR_FMT ","
	      " err=" L4_PTR_FMT ") -- jdb bug?\n",
	      e->ip(), e->_err);
	  break;
	}
      break;
    default:
      cursor(Jdb_screen::height(), 1);
      printf("\nInvalid access (trap=%02lx err=" L4_PTR_FMT
	  " pfa=" L4_PTR_FMT " eip=" L4_PTR_FMT ") "
	  "-- jdb bug?\n",
	  e->_trapno, e->_err, e->_cr2, e->ip());
      break;
    }
}

#line 955 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"


bool
Jdb::handle_debug_traps(Cpu_number cpu)
{
  bool really_break = true;

  if (entry_frame.cpu(cpu)->_trapno == 1)
    really_break = handle_trap1(cpu);
  else if (entry_frame.cpu(cpu)->_trapno == 3)
    really_break = handle_trap3(cpu);
  else
    really_break = handle_trapX(cpu);

  if (really_break)
    {
      for (Cpu_number i = Cpu_number::first(); i < Config::max_num_cpus(); ++i)
	{
	  if (!Cpu::online(i) || !running.cpu(i))
	    continue;
	  // else S+ mode
	  if (!permanent_single_step.cpu(i))
	    entry_frame.cpu(i)->flags(entry_frame.cpu(i)->flags() & ~EFLAGS_TF);
	}
    }

  return really_break;
}

#line 983 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"


bool
Jdb::test_checksums()
{ return Boot_info::get_checksum_ro() == Checksum::get_checksum_ro(); }
