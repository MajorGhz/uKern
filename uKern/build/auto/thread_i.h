// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef thread_i_h
#define thread_i_h
#line 169 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"

#include <cassert>
#line 171 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"
#include <cstdlib>		// panic()
#line 172 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"
#include <cstring>
#line 173 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"
#include "atomic.h"
#line 174 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"
#include "entry_frame.h"
#line 175 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"
#include "fpu_alloc.h"
#line 176 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"
#include "globals.h"
#line 178 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"
#include "kdb_ke.h"
#line 179 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"
#include "kernel_task.h"
#line 180 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"
#include "kmem_alloc.h"
#line 181 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"
#include "logdefs.h"
#line 182 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"
#include "map_util.h"
#line 183 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"
#include "ram_quota.h"
#line 184 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"
#include "sched_context.h"
#line 186 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"
#include "std_macros.h"
#line 187 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"
#include "task.h"
#line 188 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"
#include "thread_state.h"
#line 825 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"

#include "fpu.h"
#line 827 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"
#include "fpu_alloc.h"
#line 828 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"
#include "fpu_state.h"
#line 38 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

#include "config.h"
#line 40 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "cpu.h"
#line 41 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "cpu_lock.h"
#line 42 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "gdt.h"
#line 43 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "idt.h"
#line 44 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "ipi.h"
#line 45 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "mem_layout.h"
#line 46 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "logdefs.h"
#line 47 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "paging.h"
#line 48 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "processor.h"		// for cli/sti
#line 49 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "regdefs.h"
#line 50 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "std_macros.h"
#line 51 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "thread.h"
#line 52 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "timer.h"
#line 53 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "trap_state.h"
#line 525 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "globalconfig.h"
#line 526 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "idt.h"
#line 527 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "simpleio.h"
#line 528 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "static_init.h"
#line 529 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "terminate.h"
#line 246 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"

#include <feature.h>
#line 128 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-ipc.cpp"

#include <cstdlib>		// panic()
#line 130 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-ipc.cpp"

#include "l4_types.h"
#line 132 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-ipc.cpp"
#include "l4_msg_item.h"
#line 133 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-ipc.cpp"

#include "config.h"
#line 135 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-ipc.cpp"
#include "cpu_lock.h"
#line 136 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-ipc.cpp"
#include "ipc_timeout.h"
#line 137 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-ipc.cpp"
#include "lock_guard.h"
#line 138 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-ipc.cpp"
#include "logdefs.h"
#line 139 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-ipc.cpp"
#include "map_util.h"
#line 140 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-ipc.cpp"
#include "processor.h"
#line 142 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-ipc.cpp"
#include "kdb_ke.h"
#line 143 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-ipc.cpp"
#include "warn.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-pagefault.cpp"

#include <cstdio>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-pagefault.cpp"

#include "config.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-pagefault.cpp"
#include "cpu.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-pagefault.cpp"
#include "kmem.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-pagefault.cpp"
#include "logdefs.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-pagefault.cpp"
#include "processor.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-pagefault.cpp"
#include "thread.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-log.cpp"

#include <cstring>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-log.cpp"
#include "config.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-log.cpp"
#include "jdb_tbuf.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-log.cpp"
#include "types.h"
#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-debug.cpp"

#include <cstdio>
#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-debug.cpp"
#include "kmem.h"
#line 21 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-debug.cpp"
#include "mem_layout.h"
#line 22 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-debug.cpp"
#include "simpleio.h"
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/thread-dbf.cpp"
#include "cpu.h"
#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/thread-dbf.cpp"
#include "kernel_console.h"
#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/thread-dbf.cpp"
#include "reset.h"
#line 21 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/thread-dbf.cpp"
#include "tss.h"
#line 22 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/thread-dbf.cpp"
#include "watchdog.h"
#line 325 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"


// IPC-gate deletion stuff ------------------------------------

/**
 * Fake IRQ Chip class for IPC-gate-delete notifications.
 * This chip uses the IRQ number as thread pointer and implements
 * the bind and unbind functionality.
 */
class Del_irq_chip : public Irq_chip_soft
{
public:
  static Del_irq_chip chip;

public:  
#line 343 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"
  static inline Thread *thread(Mword pin);
  
#line 347 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"
  static inline Mword pin(Thread *t);
  
#line 351 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"
  inline void
  unbind(Irq_base *irq);
};

//
// IMPLEMENTATION of inline functions follows
//


#line 474 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"


inline void
Thread::user_invoke_generic()
{
  Context *const c = current();
  assert_kdb (c->state() & Thread_ready_mask);

  if (c->handle_drq())
    c->schedule();

  // release CPU lock explicitly, because
  // * the context that switched to us holds the CPU lock
  // * we run on a newly-created stack without a CPU lock guard
  cpu_lock.clear();
}

#line 749 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"


inline Thread::Migration *
Thread::start_migration()
{
  assert_kdb(cpu_lock.test());
  Migration *m = _migration;

  assert (!((Mword)m & 0x3)); // ensure alignment

  if (!m || !mp_cas(&_migration, m, (Migration*)0))
    return reinterpret_cast<Migration*>(0x2); // bit one == 0 --> no need to reschedule

  if (m->cpu == cpu())
    {
      set_sched_params(m->sp);
      Mem::mp_mb();
      write_now(&m->in_progress, true);
      return reinterpret_cast<Migration*>(0x1); // bit one == 1 --> need to reschedule
    }

  return m; // need to do real migration
}

#line 951 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"



inline void
Thread::migrate_away(Migration *inf, bool /*remote*/)
{
  assert_kdb (current() != this);
  assert_kdb (cpu_lock.test());

  Cpu_number cpu = inf->cpu;
  //  LOG_MSG_3VAL(this, "MGi ", Mword(current()), (current_cpu() << 16) | cpu(), Context::current_sched());
  if (_timeout)
    _timeout->reset();

  auto &rq = Sched_context::rq.current();

  // if we are in the middle of the scheduler, leave it now
  if (rq.schedule_in_progress == this)
    rq.schedule_in_progress = 0;

  rq.ready_dequeue(sched());

    {
      // Not sure if this can ever happen
      Sched_context *csc = rq.current_sched();
      if (!csc || csc->context() == this)
	rq.set_current_sched(current()->sched());
    }

  Sched_context *sc = sched_context();
  sc->set(inf->sp);
  sc->replenish();
  set_sched(sc);

  set_cpu_of(this, cpu);
  inf->in_progress = true;
  _need_to_finish_migration = true;
}

#line 989 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"


inline bool
Thread::migrate_to(Cpu_number target_cpu, bool)
{
  if (!Cpu::online(target_cpu))
    {
      handle_drq();
      return false;
    }

  auto &rq = Sched_context::rq.current();
  if (state() & Thread_ready_mask && !in_ready_list())
    rq.ready_enqueue(sched());

  enqueue_timeout_again();

  return false;
}

#line 549 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

/**
 * The ia32 specific part of the thread constructor.
 */

inline void
Thread::arch_init()
{
  // clear out user regs that can be returned from the thread_ex_regs
  // system call to prevent covert channel
  Entry_frame *r = regs();
  r->flags(EFLAGS_IOPL_K | EFLAGS_IF | 2);	// ei
  r->cs(Gdt::gdt_code_user | Gdt::Selector_user);
  r->ss(Gdt::gdt_data_user | Gdt::Selector_user);

  r->sp(0);
  // after cs initialisation as ip() requires proper cs
  r->ip(0);
}

#line 711 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"



inline void
Thread::check_f00f_bug(Trap_state *ts)
{
  // If we page fault on the IDT, it must be because of the F00F bug.
  // Figure out exception slot and raise the corresponding exception.
  // XXX: Should we also modify the error code?
  if (ts->_trapno == 14		// page fault?
      && ts->_cr2 >= Idt::idt()
      && ts->_cr2 <  Idt::idt() + Idt::_idt_max * 8)
    ts->_trapno = (ts->_cr2 - Idt::idt()) / 8;
}

#line 725 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"



inline unsigned
Thread::check_io_bitmap_delimiter_fault(Trap_state *ts)
{
  // check for page fault at the byte following the IO bitmap
  if (ts->_trapno == 14           // page fault?
      && (ts->_err & 4) == 0         // in supervisor mode?
      && ts->ip() < Kmem::mem_user_max   // delimiter byte accessed?
      && (ts->_cr2 == Mem_layout::Io_bitmap + Mem_layout::Io_port_max / 8))
    {
      // page fault in the first byte following the IO bitmap
      // map in the cpu_page read_only at the place
      Mem_space::Status result =
	mem_space()->v_insert(
	    Mem_space::Phys_addr(mem_space()->virt_to_phys_s0((void*)Kmem::io_bitmap_delimiter_page())),
	    Virt_addr(Mem_layout::Io_bitmap + Mem_layout::Io_port_max / 8),
	    Mem_space::Page_order(Config::PAGE_SHIFT),
	    Page::Attr(Page::Rights::R(), Page::Type::Normal(), Page::Kern::Global()));

      switch (result)
	{
	case Mem_space::Insert_ok:
	  return 1; // success
	case Mem_space::Insert_err_nomem:
	  // kernel failure, translate this into a general protection
	  // violation and hope that somebody handles it
	  ts->_trapno = 13;
	  ts->_err    =  0;
	  return 0; // fail
	default:
	  // no other error code possible
	  assert (false);
	}
    }

  return 1;
}

#line 764 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"


inline bool
Thread::handle_sysenter_trap(Trap_state *ts, Address eip, bool from_user)
{
  if (EXPECT_FALSE
      ((ts->_trapno == 6 || ts->_trapno == 13)
       && (ts->_err & 0xffff) == 0
       && (eip < Kmem::mem_user_max - 2)
       && (mem_space()->peek((Unsigned16*) eip, from_user)) == 0x340f))
    {
      // somebody tried to do sysenter on a machine without support for it
      WARN("tcb=%p killed:\n"
	   "\033[1;31mSYSENTER not supported on this machine\033[0m",
	   this);

      if (Cpu::have_sysenter())
	// GP exception if sysenter is not correctly set up..
        WARN("MSR_SYSENTER_CS: %llx", Cpu::rdmsr(MSR_SYSENTER_CS));
      else
	// We get UD exception on processors without SYSENTER/SYSEXIT.
        WARN("SYSENTER/EXIT not available.");

      return false;
    }

  return true;
}

#line 792 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"


inline int
Thread::handle_not_nested_trap(Trap_state *ts)
{
  // no kernel debugger present
  printf(" %p IP=" L4_PTR_FMT " Trap=%02lx [Ret/Esc]\n",
	 this, ts->ip(), ts->_trapno);

  int r;
  // cannot use normal getchar because it may block with hlt and irq's
  // are off here
  while ((r = Kconsole::console()->getchar(false)) == -1)
    Proc::pause();

  if (r == '\033')
    terminate (1);

  return 0;
}

#line 822 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

inline Cpu_number Thread::dbg_find_cpu() { return Cpu_number::boot_cpu(); }

#line 161 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"



inline int
Thread::check_trap13_kernel(Trap_state *ts)
{
  if (EXPECT_FALSE(ts->_trapno == 13 && (ts->_err & 3) == 0))
    {
      // First check if user loaded a segment register with 0 because the
      // resulting exception #13 can be raised from user _and_ kernel. If
      // the user tried to load another segment selector, the thread gets
      // killed.
      // XXX Should we emulate this too? Michael Hohmuth: Yes, we should.
      if (EXPECT_FALSE(!(ts->_ds & 0xffff)))
	{
	  Cpu::set_ds(Gdt::data_segment());
	  return 0;
	}
      if (EXPECT_FALSE(!(ts->_es & 0xffff)))
	{
	  Cpu::set_es(Gdt::data_segment());
	  return 0;
	}
      if (EXPECT_FALSE(ts->_ds & 0xfff8) == Gdt::gdt_code_user)
	{
	  WARN("%p eip=%08lx: code selector ds=%04lx",
               this, ts->ip(), ts->_ds & 0xffff);
	  Cpu::set_ds(Gdt::data_segment());
	  return 0;
	}
      if (EXPECT_FALSE(ts->_es & 0xfff8) == Gdt::gdt_code_user)
	{
	  WARN("%p eip=%08lx: code selector es=%04lx",
               this, ts->ip(), ts->_es & 0xffff);
	  Cpu::set_es(Gdt::data_segment());
	  return 0;
	}
      if (EXPECT_FALSE(ts->_fs & 0xfff8) == Gdt::gdt_code_user)
	{
	  WARN("%p eip=%08lx: code selector fs=%04lx",
               this, ts->ip(), ts->_fs & 0xffff);
	  ts->_fs = 0;
	  return 0;
	}
      if (EXPECT_FALSE(ts->_gs & 0xfff8) == Gdt::gdt_code_user)
	{
	  WARN("%p eip=%08lx: code selector gs=%04lx",
               this, ts->ip(), ts->_gs & 0xffff);
	  ts->_gs = 0;
	  return 0;
	}
    }

  return 1;
}

#line 210 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-ipc.cpp"


inline void
Thread::snd_regs(Syscall_frame *r)
{ _snd_regs = r; }

#line 319 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-ipc.cpp"


inline Mword
Thread::check_sender(Thread *sender, bool timeout)
{
  if (EXPECT_FALSE(is_invalid()))
    {
      sender->utcb().access()->error = L4_error::Not_existent;
      return Failed;
    }

  if (EXPECT_FALSE(!sender_ok(sender)))
    {
      if (!timeout)
	{
	  sender->utcb().access()->error = L4_error::Timeout;
	  return Failed;
	}

      sender->set_wait_queue(sender_list());
      sender->sender_enqueue(sender_list(), sender->sched_context()->prio());
      vcpu_set_irq_pending();
      return Queued;
    }

  return Ok;
}

#line 346 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-ipc.cpp"



inline void Thread::goto_sleep(L4_timeout const &t, Sender *sender, Utcb *utcb)
{
  IPC_timeout timeout;

  if (EXPECT_FALSE(t.is_finite() && !_timeout))
    {
      state_del_dirty(Thread_ready);

      Unsigned64 sysclock = Timer::system_clock();
      Unsigned64 tval = t.microsecs(sysclock, utcb);

      if (EXPECT_TRUE((tval > sysclock)))
	{
	  set_timeout(&timeout);
	  timeout.set(tval, cpu(true));
	}
      else // timeout already hit
	state_change_dirty(~Thread_ipc_mask, Thread_ready | Thread_timeout);
    }
  else
    {
      if (EXPECT_TRUE(t.is_never()))
	state_del_dirty(Thread_ready);
      else
	state_change_dirty(~Thread_ipc_mask, Thread_ready | Thread_timeout);
    }

  if (sender == this)
    switch_sched(sched(), &Sched_context::rq.current());

  schedule();

  if (EXPECT_FALSE((long)_timeout))
    {
      timeout.reset();
      set_timeout(0);
    }

  assert_kdb (state() & Thread_ready);
}

#line 389 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-ipc.cpp"



/**
 * @pre cpu_lock must be held
 */

inline unsigned
Thread::handshake_receiver(Thread *partner, L4_timeout snd_t)
{
  assert_kdb(cpu_lock.test());

  switch (__builtin_expect(partner->check_sender(this, !snd_t.is_zero()), Ok))
    {
    case Failed:
      return Failed;
    case Queued:
      state_add_dirty(Thread_send_wait);
      return Queued;
    default:
      partner->state_change_dirty(~(Thread_ipc_mask | Thread_ready), Thread_ipc_transfer);
      return Ok;
    }
}

#line 413 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-ipc.cpp"


inline void
Thread::set_ipc_error(L4_error const &e, Thread *rcv)
{
  utcb().access()->error = e;
  rcv->utcb().access()->error = L4_error(e, L4_error::Rcv);
}

#line 421 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-ipc.cpp"



inline Sender *
Thread::get_next_sender(Sender *sender)
{
  if (!sender_list()->empty())
    {
      if (sender) // closed wait
	{
	  if (sender->in_sender_list() && sender_list() == sender->wait_queue())
	    return sender;
	}
      else // open wait
	{
	  Sender *next = Sender::cast(sender_list()->first());
	  assert_kdb (next->in_sender_list());
	  set_partner(next);
	  return next;
	}
    }
  return 0;
}

#line 617 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-ipc.cpp"



inline bool
Thread::transfer_msg(L4_msg_tag tag, Thread *receiver,
                     Syscall_frame *sender_regs, L4_fpage::Rights rights)
{
  Syscall_frame* dst_regs = receiver->rcv_regs();

  bool success = copy_utcb_to(tag, receiver, rights);
  tag.set_error(!success);
  dst_regs->tag(tag);
  dst_regs->from(sender_regs->from_spec());

  // setup the reply capability in case of a call
  if (success && partner() == receiver)
    receiver->set_caller(this, rights);

  return success;
}

#line 1005 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-ipc.cpp"


/**
 * \pre Runs on the sender CPU
 */

inline bool
Thread::abort_send(L4_error const &e, Thread *partner)
{
  state_del_dirty(Thread_full_ipc_mask);

  if (_timeout && _timeout->is_set())
    _timeout->reset();

  set_timeout(0);
  Abort_state abt = Abt_ipc_done;

  if (partner->cpu() == current_cpu())
    {
      if (in_sender_list())
	{
	  sender_dequeue(partner->sender_list());
	  partner->vcpu_update_state();
	  abt = Abt_ipc_cancel;

	}
      else if (partner->in_ipc(this))
	abt = Abt_ipc_in_progress;
    }
  else
    abt = partner->Receiver::abort_send(this);

  switch (abt)
    {
    default:
    case Abt_ipc_done:
      return true;
    case Abt_ipc_cancel:
      utcb().access()->error = e;
      return false;
    case Abt_ipc_in_progress:
      state_add_dirty(Thread_ipc_transfer);
      while (state() & Thread_ipc_transfer)
	{
	  state_del_dirty(Thread_ready);
	  schedule();
	}
      return true;
    }
}

#line 1055 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-ipc.cpp"



/**
 * \pre Runs on the sender CPU
 */

inline bool
Thread::do_send_wait(Thread *partner, L4_timeout snd_t)
{
  IPC_timeout timeout;

  if (EXPECT_FALSE(snd_t.is_finite()))
    {
      Unsigned64 tval = snd_t.microsecs(Timer::system_clock(), utcb().access(true));
      // Zero timeout or timeout expired already -- give up
      if (tval == 0)
	return abort_send(L4_error::Timeout, partner);

      set_timeout(&timeout);
      timeout.set(tval, cpu());
    }

  register Mword ipc_state;

  while (((ipc_state = state() & (Thread_send_wait | Thread_ipc_abort_mask))) == Thread_send_wait)
    {
      state_del_dirty(Thread_ready);
      schedule();
    }

  if (EXPECT_FALSE(ipc_state == (Thread_cancel | Thread_send_wait)))
    return abort_send(L4_error::Canceled, partner);

  if (EXPECT_FALSE(ipc_state == (Thread_timeout | Thread_send_wait)))
    return abort_send(L4_error::Timeout, partner);

  timeout.reset();
  set_timeout(0);

  return true;
}

#line 1097 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-ipc.cpp"


inline void
Thread::set_ipc_send_rights(L4_fpage::Rights c)
{
  _ipc_send_rights = c;
}

#line 131 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-io.cpp"


inline int
Thread::handle_io_page_fault(Trap_state *ts)
{
  Address eip = ts->ip();
  if (!check_io_bitmap_delimiter_fault(ts))
    return 0;

  // Check for IO page faults. If we got exception #14, the IO bitmap page is
  // not available. If we got exception #13, the IO bitmap is available but
  // the according bit is set. In both cases we have to dispatch the code at
  // the faulting eip to deterine the IO port and send an IO flexpage to our
  // pager. If it was a page fault, check the faulting address to prevent
  // touching userland.
  if (eip < Kmem::mem_user_max &&
      (ts->_trapno == 13 && (ts->_err & 7) == 0 ||
       ts->_trapno == 14 && Kmem::is_io_bitmap_page_fault(ts->_cr2)))
    {
      unsigned port, size;
      if (get_ioport(eip, ts, &port, &size))
        {
          Mword io_page = L4_fpage::io(port, size).raw();

          // set User mode flag to get correct IP in handle_page_fault_pager
          // pretend a write page fault
          static const unsigned io_error_code = PF_ERR_WRITE | PF_ERR_USERMODE;

	  CNT_IO_FAULT;

          if (EXPECT_FALSE (log_page_fault()))
	    page_fault_log(io_page, io_error_code, eip);

          // treat it as a page fault in the region above 0xf0000000,

	  // We could also reset the Thread_cancel at slowtraps entry but it
	  // could be harmful for debugging (see also comment at slowtraps:).
	  //
	  // This must be done while interrupts are off to prevent that an
	  // other thread sets the flag again.
          state_del(Thread_cancel);

	  // set cr2 in ts so that we also get the io_page value in an
	  // consecutive exception
	  ts->_cr2 = io_page;

	  if (EXPECT_FALSE(state() & Thread_alien))
	    {
	      // special case for alien tasks: Don't generate pagefault but
	      // send (pagefault) exception to pager.
	      ts->_trapno = 14;
	      if (send_exception(ts))
		return 1;
	      else
		return 2; // fail, don't send exception again
	    }

          bool ipc_code = handle_page_fault_pager(_pager, io_page,
                                                  io_error_code,
                                                  L4_msg_tag::Label_io_page_fault);

          if (ipc_code)
	    return 1;
        }
    }
  return 0; // fail
}

#line 341 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"


inline Thread *Del_irq_chip::thread(Mword pin)
{ return (Thread*)pin; }

#line 345 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"


inline Mword Del_irq_chip::pin(Thread *t)
{ return (Mword)t; }

#line 349 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread.cpp"


inline void
Del_irq_chip::unbind(Irq_base *irq)
{ thread(irq->pin())->remove_delete_irq(); }

#endif // thread_i_h
