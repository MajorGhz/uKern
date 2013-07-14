// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "context.h"
#include "context_i.h"

#line 47 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/context-ia32.cpp"

//---------------------------------------------------------------------------


#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/context-ia32.cpp"

/** Thread context switchin.  Called on every re-activation of a thread
    (switch_exec()).  This method is public only because it is called from
    from assembly code in switch_cpu().
 */

void
Context::switchin_context(Context *from)
{
  assert_kdb (this == current());
  assert_kdb (state() & Thread_ready_mask);

  // Set kernel-esp in case we want to return to the user.
  // kmem::kernel_sp() returns a pointer to the kernel SP (in the
  // TSS) the CPU uses when next switching from user to kernel mode.
  // regs() + 1 returns a pointer to the end of our kernel stack.
  Cpu::cpus.cpu(cpu()).kernel_sp() = reinterpret_cast<Address>(regs() + 1);

  // switch to our page directory if necessary
  vcpu_aware_space()->switchin_context(from->vcpu_aware_space());

  // load new segment selectors
  load_segments();
}
