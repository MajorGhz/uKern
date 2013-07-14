// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "thread.h"
#include "thread_i.h"


#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-log.cpp"


/** Page-fault logging.
 */
void
Thread::page_fault_log(Address pfa, unsigned error_code, unsigned long eip)
{
  if (Jdb_pf_trace::check_restriction(current_thread()->dbg_id(), pfa))
    {
      auto guard = lock_guard(cpu_lock);

      Tb_entry_pf _local;
      Tb_entry_pf *tb = static_cast<Tb_entry_pf*>
	(EXPECT_TRUE(Jdb_pf_trace::log_buf()) ? Jdb_tbuf::new_entry()
				    : &_local);
      tb->set(this, eip, pfa, error_code, current()->space());

      if (EXPECT_TRUE(Jdb_pf_trace::log_buf()))
	Jdb_tbuf::commit_entry();
      else
	Jdb_tbuf::direct_log_entry(tb, "PF");
    }
}
