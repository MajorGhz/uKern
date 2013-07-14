// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "thread.h"
#include "thread_i.h"


#line 537 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
static void
int3_handler_init();
#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"


//----------------------------------------------------------------------------

#line 54 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

Trap_state::Handler Thread::nested_trap_handler FIASCO_FASTCALL;
#line 530 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

int (*Thread::int3_handler)(Trap_state*);
#line 532 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
DEFINE_PER_CPU Per_cpu<Thread::Dbg_stack> Thread::dbg_stack;
#line 533 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

STATIC_INITIALIZER_P (int3_handler_init, KDB_INIT_PRIO);
#line 819 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

//---------------------------------------------------------------------------


#line 56 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"


Thread::Thread()
: Receiver(),
  Sender(0),   // select optimized version of constructor
  _pager(Thread_ptr::Invalid),
  _exc_handler(Thread_ptr::Invalid),
  _del_observer(0)
{
  assert (state(false) == Thread_invalid);

  inc_ref();
  _space.space(Kernel_task::kernel_task());

  if (Config::Stack_depth)
    std::memset((char*)this + sizeof(Thread), '5',
		Thread::Size-sizeof(Thread)-64);

  _magic          = magic;
  _recover_jmpbuf = 0;
  _timeout        = 0;

  *reinterpret_cast<void(**)()> (--_kernel_sp) = user_invoke;

  arch_init();

  state_add_dirty(Thread_dead, false);

  // ok, we're ready to go!
}

#line 152 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"


extern "C" FIASCO_FASTCALL
void
thread_restore_exc_state()
{
  current_thread()->restore_exc_state();
}

#line 160 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"


void
Thread::print_page_fault_error(Mword e)
{
  printf("%lx", e);
}

#line 167 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

/**
 * The global trap handler switch.
 * This function handles CPU-exception reflection, emulation of CPU 
 * instructions (LIDT, WRMSR, RDMSR), int3 debug messages, 
 * kernel-debugger invocation, and thread crashes (if a trap cannot be 
 * handled).
 * @param state trap state
 * @return 0 if trap has been consumed by handler;
 *          -1 if trap could not be handled.
 */

int
Thread::handle_slow_trap(Trap_state *ts)
{
  Address ip;
  int from_user = ts->cs() & 3;

  if (EXPECT_FALSE(ts->_trapno == 0xee)) //debug IPI
    {
      Ipi::eoi(Ipi::Debug, cpu());
      goto generic_debug;
    }

  if (from_user && _space.user_mode())
    {
      if (ts->_trapno == 14 && Kmem::is_io_bitmap_page_fault(ts->_cr2))
        {
	  ts->_trapno = 13;
	  ts->_err    = 0;
        }

      if (send_exception(ts))
	goto success;
    }

  // XXX We might be forced to raise an excepton. In this case, our return
  // CS:IP points to leave_by_trigger_exception() which will trigger the
  // exception just before returning to userland. But if we were inside an
  // IPC while we was ex-regs'd, we will generate the 'exception after the
  // syscall' _before_ we leave the kernel.
  if (ts->_trapno == 13 && (ts->_err & 6) == 6)
    goto check_exception;

  LOG_TRAP;

  if (!check_trap13_kernel (ts))
    return 0;

  if (EXPECT_FALSE(!from_user))
    {
      // get also here if a pagefault was not handled by the user level pager
      if (ts->_trapno == 14)
	goto check_exception;

      goto generic_debug;      // we were in kernel mode -- nothing to emulate
    }

  if (EXPECT_FALSE(ts->_trapno == 2))
    goto generic_debug;        // NMI always enters kernel debugger

  if (EXPECT_FALSE(ts->_trapno == 0xffffffff))
    goto generic_debug;        // debugger interrupt

  check_f00f_bug(ts);

  // so we were in user mode -- look for something to emulate

  // We continue running with interrupts off -- no sti() here. But
  // interrupts may be enabled by the pagefault handler if we get a
  // pagefault in peek_user().

  // Set up exception handling.  If we suffer an un-handled user-space
  // page fault, kill the thread.
  jmp_buf pf_recovery;
  unsigned error;
  if (EXPECT_FALSE ((error = setjmp(pf_recovery)) != 0) )
    {
      WARN("%p killed:\n"
           "\033[1mUnhandled page fault, code=%08x\033[m\n", this, error);
      goto fail_nomsg;
    }

  _recover_jmpbuf = &pf_recovery;

  switch (handle_io_page_fault(ts))
    {
    case 1: goto success;
    case 2: goto fail;
    default: break;
    }

  ip = ts->ip();

  // just print out some warning, we do the normal exception handling
  handle_sysenter_trap(ts, ip, from_user);
  _recover_jmpbuf = 0;

check_exception:

  // send exception IPC if requested
  if (send_exception(ts))
    goto success;

  // backward compatibility cruft: check for those insane "int3" debug
  // messaging command sequences
  if (ts->_trapno == 3)
    {
      if (int3_handler && int3_handler(ts))
	goto success;

      goto generic_debug;
    }

  // privileged tasks also may invoke the kernel debugger with a debug
  // exception
  if (ts->_trapno == 1)
    goto generic_debug;


fail:
  // can't handle trap -- kill the thread
  WARN("%p killed:\n"
       "\033[1mUnhandled trap \033[m\n", this);

fail_nomsg:
  if ((int)Config::Warn_level >= Warning)
    ts->dump();

  halt();

success:
  _recover_jmpbuf = 0;
  return 0;

generic_debug:
  _recover_jmpbuf = 0;

  if (!nested_trap_handler)
    return handle_not_nested_trap(ts);

  return call_nested_trap_handler(ts);
}

#line 310 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

/**
 * The low-level page fault handler called from entry.S.  We're invoked with
 * interrupts turned off.  Apart from turning on interrupts in almost
 * all cases (except for kernel page faults in TCB area), just forwards
 * the call to Thread::handle_page_fault().
 * @param pfa page-fault virtual address
 * @param error_code CPU error code
 * @return true if page fault could be resolved, false otherwise
 */
extern "C" FIASCO_FASTCALL
int
thread_page_fault(Address pfa, Mword error_code, Address ip, Mword flags,
		  Return_frame *regs)
{

  // XXX: need to do in a different way, if on debug stack e.g.
#if 0
  // If we're in the GDB stub -- let generic handler handle it
  if (EXPECT_FALSE (!in_context_area((void*)Proc::stack_pointer())))
    return false;
#endif

  // Pagefault in user mode or interrupts were enabled
  if (PF::is_usermode_error(error_code))
    {
      if (current_thread()->vcpu_pagefault(pfa, error_code, ip))
        return 1;

      Proc::sti();
    }
  else if(flags & EFLAGS_IF)
    Proc::sti();

  // Pagefault in kernel mode and interrupts were disabled
  else
    {
      // page fault in kernel memory region
      if (Kmem::is_kmem_page_fault(pfa, error_code))
	{
	  // We've interrupted a context in the kernel with disabled interrupts,
	  // the page fault address is in the kernel region, the error code is
	  // "not mapped" (as opposed to "access error"), and the region is
	  // actually valid (that is, mapped in Kmem's shared page directory,
	  // just not in the currently active page directory)
	  // Remain cli'd !!!
	}
      else if (!Kmem::is_kmem_page_fault(pfa, error_code))
	{
          // No error -- just enable interrupts.
	  Proc::sti();
	}
      else
	{
          // Error: We interrupted a cli'd kernel context touching kernel space
	  if (!Thread::log_page_fault())
	    printf("*P[%lx,%lx,%lx] ", pfa, error_code & 0xffff, ip);

	  kdb_ke ("page fault in cli mode");
	}
    }

  return current_thread()->handle_page_fault(pfa, error_code, ip, regs);
}

#line 374 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

/** The catch-all trap entry point.  Called by assembly code when a 
    CPU trap (that's not specially handled, such as system calls) occurs.
    Just forwards the call to Thread::handle_slow_trap().
    @param state trap state
    @return 0 if trap has been consumed by handler;
           -1 if trap could not be handled.
 */
extern "C" FIASCO_FASTCALL
int
thread_handle_trap(Trap_state *ts, unsigned)
{
  return current_thread()->handle_slow_trap(ts);
}

#line 535 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"


static void
int3_handler_init()
{
  Thread::set_int3_handler(Thread::handle_int3);
}

#line 568 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"


/** A C interface for Context::handle_fpu_trap, callable from assembly code.
    @relates Context
 */
// The "FPU not available" trap entry point
extern "C"
int
thread_handle_fputrap()
{
  LOG_TRAP_N(7);

  return current_thread()->switchin_fpu();
}

#line 589 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

/**
 * Default handle for int3 extensions if JDB is disabled. If the JDB is
 * available, Jdb::handle_int3_threadctx is called instead.
 * @return 0 not handled, wait for user response
 *         1 successfully handled
 */

int
Thread::handle_int3(Trap_state *ts)
{
  Mem_space *s   = current()->mem_space();
  int from_user  = ts->cs() & 3;
  Address   ip   = ts->ip();
  Unsigned8 todo = s->peek((Unsigned8*)ip, from_user);
  Unsigned8 *str;
  int len;
  char c;

  switch (todo)
    {
    case 0xeb: // jmp == enter_kdebug()
      len = s->peek((Unsigned8*)(ip+1), from_user);
      str = (Unsigned8*)(ip + 2);

      putstr("KDB: ");
      if (len > 0)
	{
	  for (; len; len--)
            putchar(s->peek(str++, from_user));
	}
      putchar('\n');
      return 0; // => Jdb

    case 0x90: // nop == l4kd_display()
      if (          s->peek((Unsigned8*)(ip+1), from_user)  != 0xeb /*jmp*/
	  || (len = s->peek((Unsigned8*)(ip+2), from_user)) <= 0)
	return 0; // => Jdb

      str = (Unsigned8*)(ip + 3);
      for (; len; len--)
	putchar(s->peek(str++, from_user));
      break;

    case 0x3c: // cmpb
      todo = s->peek((Unsigned8*)(ip+1), from_user);
      switch (todo)
	{
	case  0: // l4kd_outchar
	  putchar(ts->value() & 0xff);
	  break;
        case  1: // l4kd_outnstring
	  str = (Unsigned8*)ts->value();
          len = ts->value4();
	  for(; len > 0; len--)
	    putchar(s->peek(str++, from_user));
	  break;
	case  2: // l4kd_outstr
	  str = (Unsigned8*)ts->value();
	  for (; (c=s->peek(str++, from_user)); )
            putchar(c);
	  break;
	case  5: // l4kd_outhex32
	  printf("%08lx", ts->value() & 0xffffffff);
	  break;
	case  6: // l4kd_outhex20
	  printf("%05lx", ts->value() & 0xfffff);
	  break;
	case  7: // l4kd_outhex16
	  printf("%04lx", ts->value() & 0xffff);
	  break;
	case  8: // l4kd_outhex12
	  printf("%03lx", ts->value() & 0xfff);
	  break;
	case  9: // l4kd_outhex8
	  printf("%02lx", ts->value() & 0xff);
	  break;
	case 11: // l4kd_outdec
	  printf("%ld", ts->value());
	  break;
	case 31: // Watchdog
	  switch (ts->value2())
	    {
	    case 1:
	      // enable watchdog
	      Watchdog::user_enable();
	      break;
	    case 2:
	      // disable watchdog
	      Watchdog::user_disable();
	      break;
	    case 3:
	      // user takes over the control of watchdog and is from now on
	      // responsible for calling "I'm still alive" events (function 5)
	      Watchdog::user_takeover_control();
	      break;
	    case 4:
	      // user returns control of watchdog to kernel
	      Watchdog::user_giveback_control();
              break;
	    case 5:
	      // I'm still alive
	      Watchdog::touch();
	      break;
	    }
	  break;

	default: // ko
	  if (todo < ' ')
	    return 0; // => Jdb

	  putchar(todo);
	  break;
	}
      break;

    default:
      return 0; // => Jdb
    }

  return 1;
}
