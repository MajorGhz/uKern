// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef task_h
#define task_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"

#include "context.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
#include "kobject.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
#include "l4_types.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
#include "rcupdate.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
#include "space.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
#include "spin_lock.h"
#line 585 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"

#include "tb_entry.h"

//
// INTERFACE definition follows 
//

#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"

/**
 * \brief A task is a protection domain.
 *
 * A is derived from Space, which aggregates a set of address spaces.
 * Additionally to a space, a task provides initialization and
 * destruction functionality for a protection domain.
 * Task is also derived from Rcu_item to provide RCU shutdown of tasks.
 */
class Task :
  public Kobject,
  public Space
{
  FIASCO_DECLARE_KOBJ();

  friend class Jdb_space;

private:
  /// \brief Do host (platform) specific initialization.
  void ux_init();

public:
  enum Operation
  {
    Map         = 0,
    Unmap       = 1,
    Cap_info    = 2,
    Add_ku_mem  = 3,
    Ldt_set_x86 = 0x11,
  };

private:
  /// map the global utcb pointer page into this task
  void map_utcb_ptr_page();

#line 587 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
private:

private:
  struct Log_unmap : public Tb_entry
  {
    Mword id;
    Mword mask;
    Mword fpage;
    unsigned print(int max, char *buf) const;
  } __attribute__((packed));


public:  
#line 75 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
  virtual int
  resume_vcpu(Context *ctxt, Vcpu_state *vcpu, bool user_mode);
  
#line 100 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
  virtual bool
  put();
  
#line 241 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
  /** Allocate space for the UTCBs of all threads in this task.
   *  @ return true on success, false if not enough memory for the UTCBs
   */
  
  bool
  initialize();
  
#line 257 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
  /**
   * \brief Create a normal Task.
   * \pre \a parent must be valid and exist.
   */
  
  explicit Task(Ram_quota *q, Caps c);
  
#line 297 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
  //inline
  void
  operator delete(void *ptr);
  
#line 314 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
  template< typename TARGET > static Task *
  create(Ram_quota *quota, L4_fpage const &utcb_area);
  
#line 338 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
  /**
   * \brief Shutdown the task.
   *
   * Currently:
   * -# Unbind and delete all contexts bound to this task.
   * -# Unmap everything from all spaces.
   * -# Delete child tasks.
   */
  
  void
  destroy(Kobject ***reap_list);
  
#line 538 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
  void
  invoke(L4_obj_ref, L4_fpage::Rights rights, Syscall_frame *f, Utcb *utcb);
  
#line 579 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
  inline ~Task();

protected:  
#line 271 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
  Task(Ram_quota *q, Mem_space::Dir_type* pdir, Caps c);
  
#line 282 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
  static Slab_cache*
  allocator();
  
#line 288 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
  inline void *
  operator new(size_t size, void *p) throw();

private:  
#line 105 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
  int
  alloc_ku_mem_chunk(User<void>::Ptr u_addr, unsigned size, void **k_addr);
  
#line 168 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
  int
  alloc_ku_mem(L4_fpage ku_area);
  
#line 200 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
  inline void
  free_ku_mem(Ku_mem *m);
  
#line 208 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
  void
  free_ku_mem_chunk(void *k_addr, User<void>::Ptr u_addr, unsigned size,
                          unsigned mapped_size);
  
#line 233 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
  void
  free_ku_mem();
  
#line 356 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
  inline L4_msg_tag
  sys_map(L4_fpage::Rights rights, Syscall_frame *f, Utcb *utcb);
  
#line 423 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
  inline L4_msg_tag
  sys_unmap(Syscall_frame *f, Utcb *utcb);
  
#line 464 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
  inline L4_msg_tag
  sys_cap_valid(Syscall_frame *, Utcb *utcb);
  
#line 485 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
  inline L4_msg_tag
  sys_caps_equal(Syscall_frame *, Utcb *utcb);
  
#line 504 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
  inline L4_msg_tag
  sys_add_ku_mem(Syscall_frame *f, Utcb *utcb);
  
#line 523 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
  inline L4_msg_tag
  sys_cap_info(Syscall_frame *f, Utcb *utcb);
  
#line 617 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
  inline L4_msg_tag
  sys_vm_run(Syscall_frame *, Utcb *);
  
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/task-ia32-amd64.cpp"
  inline bool
  invoke_arch(L4_msg_tag &tag, Utcb *utcb);
};
#line 581 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"


// ---------------------------------------------------------------------------

#line 603 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 48 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"

#include "atomic.h"
#line 50 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
#include "unique_ptr.h"
#line 51 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
#include "config.h"
#line 52 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
#include "entry_frame.h"
#line 53 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
#include "globals.h"
#line 54 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
#include "kdb_ke.h"
#line 55 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
#include "kmem.h"
#line 56 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
#include "kmem_slab.h"
#line 57 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
#include "l4_types.h"
#line 58 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
#include "l4_buf_iter.h"
#line 59 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
#include "logdefs.h"
#line 60 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
#include "map_util.h"
#line 61 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
#include "mem_layout.h"
#line 62 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
#include "ram_quota.h"
#line 63 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
#include "thread_state.h"
#line 64 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
#include "paging.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/task-ia32-amd64.cpp"

#include "gdt.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/task-ia32-amd64.cpp"
#include "std_macros.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/task-ia32-amd64.cpp"
#include "x86desc.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 577 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"


inline Task::~Task()
{ free_ku_mem(); }

#line 285 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"



inline void *
Task::operator new(size_t size, void *p) throw()
{
  (void)size;
  assert (size == sizeof (Task));
  return p;
}

#line 574 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"

inline void Task::map_utcb_ptr_page() {}

#line 576 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"
inline void Task::ux_init() {}

//
// IMPLEMENTATION of function templates
//


#line 310 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/task.cpp"




template< typename TARGET > Task *
Task::create(Ram_quota *quota, L4_fpage const &utcb_area)
{
  void *t = allocator()->q_alloc(quota);
  if (!t)
    return 0;

  cxx::unique_ptr<Task> a(new (t) TARGET(quota, Caps::mem() | Caps::io() | Caps::obj()));

  if (!a->initialize())
    return 0;

  a->sync_kernel();

  if (utcb_area.is_valid())
    {
      int e = a->alloc_ku_mem(utcb_area);
      if (e < 0)
        return 0;
    }

  return a.release();
}

#endif // task_h
