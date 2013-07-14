// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef context_h
#define context_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

#include <csetjmp>             // typedef jmp_buf
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "types.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "clock.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "config.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "continuation.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "fpu_state.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "globals.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "l4_types.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "member_offs.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "per_cpu_data.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "queue.h"
#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "queue_item.h"
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "rcupdate.h"
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "sched_context.h"
#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "space.h"
#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "spin_lock.h"
#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "timeout.h"
#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include <fiasco_defs.h>
#line 343 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

#include "tb_entry.h"
#line 2133 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

#include "tb_entry.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/context-ia32-32.cpp"

#include "x86desc.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context-vcpu.cpp"

#include "vcpu.h"

//
// INTERFACE definition follows 
//

#line 21 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

class Entry_frame;
#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
class Thread_lock;
#line 24 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
class Context;
#line 25 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
class Kobject_iface;
#line 26 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

class Context_ptr
{
public:
  explicit Context_ptr(Cap_index id) : _t(id) {}
  Context_ptr() {}
  Context_ptr(Context_ptr const &o) : _t(o._t) {}
  Context_ptr const &operator = (Context_ptr const &o)
  { _t = o._t; return *this; }

  Kobject_iface *ptr(Space *, L4_fpage::Rights *) const;

  bool is_kernel() const { return false; }
  bool is_valid() const { return _t != Cap_index(~0UL); }

  // only for debugging use
  Cap_index raw() const { return _t; }

private:
  Cap_index _t;

};
#line 48 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

template< typename T >
class Context_ptr_base : public Context_ptr
{
public:
  enum Invalid_type { Invalid };
  enum Null_type { Null };
  explicit Context_ptr_base(Invalid_type) : Context_ptr(Cap_index(~0UL)) {}
  explicit Context_ptr_base(Null_type) : Context_ptr(Cap_index(0)) {}
  explicit Context_ptr_base(Cap_index id) : Context_ptr(id) {}
  Context_ptr_base() {}
  Context_ptr_base(Context_ptr_base<T> const &o) : Context_ptr(o) {}
  template< typename X >
  Context_ptr_base(Context_ptr_base<X> const &o) : Context_ptr(o)
  { X*x = 0; T*t = x; (void)t; }

  Context_ptr_base<T> const &operator = (Context_ptr_base<T> const &o)
  { Context_ptr::operator = (o); return *this; }

  template< typename X >
  Context_ptr_base<T> const &operator = (Context_ptr_base<X> const &o)
  { X*x=0; T*t=x; (void)t; Context_ptr::operator = (o); return *this; }

  //T *ptr(Space *s) const { return static_cast<T*>(Context_ptr::ptr(s)); }
};
#line 73 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

class Context_space_ref
{
public:
  typedef Spin_lock_coloc<Space *> Space_n_lock;

private:
  Space_n_lock _s;
  Address _v;

public:
  Space *space() const { return _s.get_unused(); }
  Space_n_lock *lock() { return &_s; }
  Address user_mode() const { return _v & 1; }
  Space *vcpu_user() const { return reinterpret_cast<Space*>(_v & ~3); }
  Space *vcpu_aware() const { return user_mode() ? vcpu_user() : space(); }

  void space(Space *s) { _s.set_unused(s); }
  void vcpu_user(Space *s) { _v = (Address)s; }
  void user_mode(bool enable)
  {
    if (enable)
      _v |= (Address)1;
    else
      _v &= (Address)(~1);
  }
};
#line 100 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/** An execution context.  A context is a runnable, schedulable activity.
    It carries along some state used by other subsystems: A lock count,
    and stack-element forward/next pointers.
 */
class Context :
  public Context_base,
  protected Rcu_item
{
  MEMBER_OFFSET();
  friend class Jdb_thread_list;
  friend class Context_ptr;
  friend class Jdb_utcb;

protected:
  virtual void finish_migration() = 0;
  virtual bool initiate_migration() = 0;

  struct State_request
  {
    Mword add;
    Mword del;
  };

public:
  /**
   * \brief Encapsulate an aggregate of Context.
   *
   * Allow to get a back reference to the aggregating Context object.
   */
  class Context_member
  {
  private:
    Context_member(Context_member const &);

  public:
    Context_member() {}
    /**
     * \brief Get the aggregating Context object.
     */
    Context *context() const;
  };

  /**
   * \brief Deffered Request.
   *
   * Represents a request that can be queued for each Context
   * and is executed by the target context just after switching to the
   * target context.
   */
  class Drq : public Queue_item, public Context_member
  {
  public:
    typedef unsigned (Request_func)(Drq *, Context *target, void *);
    enum { Need_resched = 1, No_answer = 2 };
    enum Wait_mode { No_wait = 0, Wait = 1 };
    enum Exec_mode { Target_ctxt = 0, Any_ctxt = 1 };
    // enum State { Idle = 0, Handled = 1, Reply_handled = 2 };

    Request_func *func;
    Request_func *reply;
    void *arg;
    // State state;
  };

  /**
   * \brief Queue for deffered requests (Drq).
   *
   * A FIFO queue each Context aggregates to queue incomming Drq's
   * that have to be executed directly after switching to a context.
   */
  class Drq_q : public Queue, public Context_member
  {
  public:
    enum Drop_mode { Drop = true, No_drop = false };
    void enq(Drq *rq);
    bool dequeue(Drq *drq, Queue_item::Status reason);
    bool handle_requests(Drop_mode drop = No_drop);
    bool execute_request(Drq *r, Drop_mode drop, bool local);
  };

  struct Migration
  {
    Cpu_number cpu;
    L4_sched_param const *sp;
    bool in_progress;

    Migration() : in_progress(false) {}
  };

  template<typename T>
  class Ku_mem_ptr : public Context_member
  {
    MEMBER_OFFSET();

  private:
    typename User<T>::Ptr _u;
    T *_k;

  public:
    Ku_mem_ptr() : _u(0), _k(0) {}
    Ku_mem_ptr(typename User<T>::Ptr const &u, T *k) : _u(u), _k(k) {}

    void set(typename User<T>::Ptr const &u, T *k)
    { _u = u; _k = k; }

    T *access(bool is_current = false) const
    {
      // assert_kdb (!is_current || current() == context());
      if (is_current
          && (int)Config::Access_user_mem == Config::Access_user_mem_direct)
        return _u.get();

      Cpu_number const cpu = current_cpu();
      if ((int)Config::Access_user_mem == Config::Must_access_user_mem_direct
          && cpu == context()->cpu()
          && Mem_space::current_mem_space(cpu) == context()->space())
        return _u.get();
      return _k;
    }

    typename User<T>::Ptr usr() const { return _u; }
    T* kern() const { return _k; }
  };

public:
  /**
   * Definition of different scheduling modes
   */
  enum Sched_mode
  {
    Periodic	= 0x1,	///< 0 = Conventional, 1 = Periodic
    Nonstrict	= 0x2,	///< 0 = Strictly Periodic, 1 = Non-strictly periodic
  };

  /**
   * Definition of different helping modes
   */
  enum Helping_mode
  {
    Helping,
    Not_Helping,
    Ignore_Helping
  };

  /**
   * Return consumed CPU time.
   * @return Consumed CPU time in usecs
   */
  Cpu_time consumed_time();

  virtual bool kill() = 0;

  void spill_user_state();
  void fill_user_state();

  Space * FIASCO_PURE space() const { return _space.space(); }
  Mem_space * FIASCO_PURE mem_space() const { return static_cast<Mem_space*>(space()); }

protected:
  /**
   * Update consumed CPU time during each context switch and when
   *        reading out the current thread's consumed CPU time.
   */
  void update_consumed_time();

  Mword *_kernel_sp;
  void *_utcb_handler;
  Ku_mem_ptr<Utcb> _utcb;

private:
  friend class Jdb;
  friend class Jdb_tcb;

  /// low level page table switching stuff
  void switchin_context(Context *) asm ("switchin_context_label") FIASCO_FASTCALL;

  /// low level fpu switching stuff
  void switch_fpu(Context *t);

  /// low level cpu switching stuff
  void switch_cpu(Context *t);

protected:
  Context_space_ref _space;

private:
  Context *_donatee;
  Context *_helper;

  // Lock state
  // how many locks does this thread hold on other threads
  // incremented in Thread::lock, decremented in Thread::clear
  // Thread::kill needs to know
  int _lock_cnt;


  // The scheduling parameters.  We would only need to keep an
  // anonymous reference to them as we do not need them ourselves, but
  // we aggregate them for performance reasons.
  Sched_context _sched_context;
  Sched_context *_sched;
  Unsigned64 _period;
  Sched_mode _mode;

  // Pointer to floating point register state
  Fpu_state _fpu_state;
  // Implementation-specific consumed CPU time (TSC ticks or usecs)
  Clock::Time _consumed_time;

  Drq _drq;
  Drq_q _drq_q;

protected:
  // for trigger_exception
  Continuation _exc_cont;

  jmp_buf *_recover_jmpbuf;     // setjmp buffer for page-fault recovery

  Migration *_migration;
  bool _need_to_finish_migration;

public:
  void arch_load_vcpu_kern_state(Vcpu_state *vcpu, bool do_load);

protected:
  void arch_load_vcpu_user_state(Vcpu_state *vcpu, bool do_load);
  void arch_update_vcpu_state(Vcpu_state *vcpu);

  // XXX Timeout for both, sender and receiver! In normal case we would have
  // to define own timeouts in Receiver and Sender but because only one
  // timeout can be set at one time we use the same timeout. The timeout
  // has to be defined here because Dirq::hit has to be able to reset the
  // timeout (Irq::_irq_thread is of type Receiver).
  Timeout *_timeout;

private:
  static Per_cpu<Clock> _clock;
  static Per_cpu<Context *> _kernel_ctxt;

#line 345 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
private:

public:
  struct Drq_log : public Tb_entry
  {
    void *func;
    void *reply;
    Context *thread;
    Drq const *rq;
    Cpu_number target_cpu;
    enum class Type { Send, Do_request, Do_reply, Done } type;
    bool wait;
    unsigned print(int max, char *buf) const;
    Group_order has_partner() const
    {
      switch (type)
        {
        case Type::Send: return Group_order::first();
        case Type::Done: return Group_order::last();
        case Type::Do_request: return Group_order(1);
        case Type::Do_reply: return Group_order(2);
        }
      return Group_order::none();
    }

    Group_order is_partner(Drq_log const *o) const
    {
      if (rq != o->rq || func != o->func || reply != o->reply)
        return Group_order::none();

      return o->has_partner();
    }
  };


  struct Vcpu_log : public Tb_entry
  {
    Mword state;
    Mword ip;
    Mword sp;
    Mword space;
    Mword err;
    unsigned char type;
    unsigned char trap;
    unsigned print(int max, char *buf) const;
  };

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/context-ia32-32.cpp"
private:

protected:
  enum { Gdt_user_entries = 4 };
  Gdt_entry	_gdt_user_entries[Gdt_user_entries+1];
  Unsigned32	_es, _fs, _gs;

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context-vcpu.cpp"
private:

protected:
  Ku_mem_ptr<Vcpu_state> _vcpu_state;

#line 136 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context-vcpu.cpp"
private:

  static unsigned vcpu_log_fmt(Tb_entry *, int, char *)
  asm ("__context_vcpu_log_fmt");

public:  
#line 432 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /** Initialize a context.  After setup, a switch_exec to this context results
      in a return to user code using the return registers at regs().  The
      return registers are not initialized however; neither is the space_context
      to be used in thread switching (use set_space_context() for that).
      @pre (_kernel_sp == 0)  &&  (* (stack end) == 0)
      @param thread_lock pointer to lock used to lock this context
      @param space_context the space context
   */
  
  inline Context();
  
#line 463 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  inline void
  reset_kernel_sp();
  
#line 470 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  inline void
  spill_fpu_if_owner();
  
#line 488 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  inline void
  do_kill();
  
#line 500 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /** Destroy context.
   */
  
  virtual ~Context();
  
#line 507 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  inline bool
  check_for_current_cpu() const;
  
#line 520 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  inline Mword
  state(bool check = true) const;
  
#line 529 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  static inline Context*
  kernel_context(Cpu_number cpu);
  
#line 544 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * Does the context exist? .
   * @return true if this context has been initialized.
   */
  
  inline Mword
  exists() const;
  
#line 555 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * Is the context about to be deleted.
   * @return true if this context is in deletion.
   */
  
  inline bool
  is_invalid() const;
  
#line 564 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * Atomically add bits to state flags.
   * @param bits bits to be added to state flags
   * @return 1 if none of the bits that were added had been set before
   */
  
  inline void
  state_add(Mword bits);
  
#line 577 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * Add bits in state flags. Unsafe (non-atomic) and
   *        fast version -- you must hold the kernel lock when you use it.
   * @pre cpu_lock.test() == true
   * @param bits bits to be added to state flags
   */ 
  
  inline void
  state_add_dirty(Mword bits, bool check = true);
  
#line 592 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * Atomically delete bits from state flags.
   * @param bits bits to be removed from state flags
   * @return 1 if all of the bits that were removed had previously been set
   */
  
  inline void
  state_del(Mword bits);
  
#line 605 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * Delete bits in state flags. Unsafe (non-atomic) and
   *        fast version -- you must hold the kernel lock when you use it.
   * @pre cpu_lock.test() == true
   * @param bits bits to be removed from state flags
   */
  
  inline void
  state_del_dirty(Mword bits, bool check = true);
  
#line 620 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * Atomically delete and add bits in state flags, provided the
   *        following rules apply (otherwise state is not changed at all):
   *        - Bits that are to be set must be clear in state or clear in mask
   *        - Bits that are to be cleared must be set in state
   * @param mask Bits not set in mask shall be deleted from state flags
   * @param bits Bits to be added to state flags
   * @return 1 if state was changed, 0 otherwise
   */
  
  inline Mword
  state_change_safely(Mword mask, Mword bits);
  
#line 647 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * Atomically delete and add bits in state flags.
   * @param mask bits not set in mask shall be deleted from state flags
   * @param bits bits to be added to state flags
   */
  
  inline Mword
  state_change(Mword mask, Mword bits);
  
#line 660 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * Delete and add bits in state flags. Unsafe (non-atomic) and
   *        fast version -- you must hold the kernel lock when you use it.
   * @pre cpu_lock.test() == true
   * @param mask Bits not set in mask shall be deleted from state flags
   * @param bits Bits to be added to state flags
   */
  
  inline void
  state_change_dirty(Mword mask, Mword bits, bool check = true);
  
#line 682 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  inline Context_space_ref *
  space_ref();
  
#line 687 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  inline Space *
  vcpu_aware_space() const;
  
#line 691 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /** Registers used when iret'ing to user mode.
      @return return registers
   */
  
  inline Entry_frame *
  regs() const;
  
#line 709 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /** Increment lock count.
      @post lock_cnt() > 0 */
  
  inline void
  inc_lock_cnt();
  
#line 718 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /** Decrement lock count.
      @pre lock_cnt() > 0
   */
  
  inline void
  dec_lock_cnt();
  
#line 728 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /** Lock count.
      @return lock count
   */
  
  inline int
  lock_cnt() const;
  
#line 738 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  //@}
  
  /**
   * Switch active timeslice of this Context.
   * @param next Sched_context to switch to
   */
  
  void
  switch_sched(Sched_context *next, Sched_context::Ready_queue *queue);
  
#line 752 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * Select a different context for running and activate it.
   */
  
  void
  schedule();
  
#line 828 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  inline void
  schedule_if(bool s);
  
#line 838 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * Return Context's Sched_context with id 'id'; return time slice 0 as default.
   * @return Sched_context with id 'id' or 0
   */
  
  inline Sched_context *
  sched_context(unsigned short const id = 0) const;
  
#line 857 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * Return Context's currently active Sched_context.
   * @return Active Sched_context
   */
  
  inline Sched_context *
  sched() const;
  
#line 879 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * Return Context's real-time period length.
   * @return Period length in usecs
   */
  
  inline Unsigned64
  period() const;
  
#line 901 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * Return Context's scheduling mode.
   * @return Scheduling mode
   */
  
  inline Context::Sched_mode
  mode() const;
  
#line 912 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * Set Context's scheduling mode.
   * @param mode New scheduling mode
   */
  
  inline void
  set_mode(Context::Sched_mode const mode);
  
#line 941 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * Check if Context is in ready-list.
   * @return 1 if thread is in ready-list, 0 otherwise
   */
  
  inline Mword
  in_ready_list() const;
  
#line 953 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * \brief Activate a newly created thread.
   *
   * This function sets a new thread onto the ready list and switches to
   * the thread if it can preempt the currently running thread.
   */
  
  bool
  activate();
  
#line 980 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /** Helper.  Context that helps us by donating its time to us. It is
      set by switch_exec() if the calling thread says so.
      @return context that helps us and should be activated after freeing a lock.
  */
  
  inline Context *
  helper() const;
  
#line 993 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  inline void
  set_helper(Helping_mode const mode);
  
#line 1010 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /** Donatee.  Context that receives our time slices, for example
      because it has locked us.
      @return context that should be activated instead of us when we're
              switch_exec()'ed.
  */
  
  inline Context *
  donatee() const;
  
#line 1023 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  inline void
  set_donatee(Context * const donatee);
  
#line 1030 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  inline Mword *
  get_kernel_sp() const;
  
#line 1037 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  inline void
  set_kernel_sp(Mword * const esp);
  
#line 1044 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  inline Fpu_state *
  fpu_state();
  
#line 1050 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * Add to consumed CPU time.
   * @param quantum Implementation-specific time quantum (TSC ticks or usecs)
   */
  
  inline void
  consume_time(Clock::Time quantum);
  
#line 1083 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * Switch to scheduling context and execution context while not running under
   * CPU lock.
   */
  
  inline void
  switch_to(Context *t);
  
#line 1127 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  inline void
  switch_to_locked(Context *t);
  
#line 1135 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * Switch execution context while not running under CPU lock.
   */
  
  inline bool FIASCO_WARN_RESULT
  switch_exec(Context *t, enum Helping_mode mode);
  
#line 1181 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * Switch to a specific different execution context.
   *        If that context is currently locked, switch to its locker instead
   *        (except if current() is the locker)
   * @pre current() == this  &&  current() != t
   * @param t thread that shall be activated.
   * @param mode helping mode; we either help, don't help or leave the
   *             helping state unchanged
   */
  
  bool  FIASCO_WARN_RESULT //L4_IPC_CODE
  switch_exec_locked(Context *t, enum Helping_mode mode);
  
#line 1241 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  inline void
  switch_exec_schedule_locked(Context *t, enum Helping_mode mode);
  
#line 1249 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  inline Context::Ku_mem_ptr<Utcb> const &
  utcb() const;
  
#line 1410 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * \brief Check for pending DRQs.
   * \return true if there are DRQs pending, false if not.
   */
  
  inline bool
  drq_pending() const;
  
#line 1420 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  inline void
  try_finish_migration();
  
#line 1431 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * \brief Handle all pending DRQs.
   * \pre cpu_lock.test() (The CPU lock must be held).
   * \pre current() == this (only the currently running context is allowed to
   *      call this function).
   * \return true if re-scheduling is needed (ready queue has changed),
   *         false if not.
   */
  //inline
  bool
  handle_drq();
  
#line 1472 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * \brief Get the queue item of the context.
   * \pre The context must currently not be in any queue.
   * \return The queue item of the context.
   *
   * The queue item can be used to enqueue the context to a Queue.
   * a context must be in at most one queue at a time.
   * To figure out the context corresponding to a queue item
   * context_of() can be used.
   */
  
  inline Queue_item *
  queue_item();
  
#line 1505 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * \brief Queue a DRQ for changing the contexts state.
   * \param mask bit mask for the state (state &= mask).
   * \param add bits to add to the state (state |= add).
   * \note This function is a preemption point.
   *
   * This function must be used to change the state of contexts that are
   * potentially running on a different CPU.
   */
  
  inline void
  drq_state_change(Mword mask, Mword add);
  
#line 1531 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * \brief Initiate a DRQ for the context.
   * \pre \a src must be the currently running context.
   * \param src the source of the DRQ (the context who initiates the DRQ).
   * \param func the DRQ handler.
   * \param arg the argument for the DRQ handler.
   * \param reply the reply handler (called in the context of \a src immediately
   *        after receiving a successful reply).
   *
   * DRQs are requests that any context can queue to any other context. DRQs are
   * the basic mechanism to initiate actions on remote CPUs in an MP system,
   * however, are also allowed locally.
   * DRQ handlers of pending DRQs are executed by Context::handle_drq() in the
   * context of the target context. Context::handle_drq() is basically called
   * after switching to a context in Context::switch_exec_locked().
   *
   * This function enqueues a DRQ and blocks the current context for a reply DRQ.
   */
  
  inline void
  drq(Drq *drq, Drq::Request_func *func, void *arg,
               Drq::Request_func *reply = 0,
               Drq::Exec_mode exec = Drq::Target_ctxt,
               Drq::Wait_mode wait = Drq::Wait);
  
#line 1618 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  inline void
  drq(Drq::Request_func *func, void *arg,
               Drq::Request_func *reply = 0,
               Drq::Exec_mode exec = Drq::Target_ctxt,
               Drq::Wait_mode wait = Drq::Wait);
  
#line 1637 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  inline void
  recover_jmp_buf(jmp_buf *b);
  
#line 1642 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  static void
  xcpu_tlb_flush(...);
  
#line 1671 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  inline Cpu_number
  cpu(bool running = false) const;
  
#line 1681 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  static inline void
  enable_tlb(Cpu_number);
  
#line 1686 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  static inline void
  disable_tlb(Cpu_number);
  
#line 1700 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  bool
  enqueue_drq(Drq *rq, Drq::Exec_mode /*exec*/);
  
#line 1739 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  inline void
  rcu_wait();
  
#line 1747 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  static inline void
  xcpu_tlb_flush(bool, Mem_space *, Mem_space *);
  
#line 2087 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  inline void
  spill_fpu();
  
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context-vcpu.cpp"
  inline Context::Ku_mem_ptr<Vcpu_state> const &
  vcpu_state() const;
  
#line 21 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context-vcpu.cpp"
  inline Mword
  vcpu_disable_irqs();
  
#line 35 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context-vcpu.cpp"
  inline void
  vcpu_restore_irqs(Mword irqs);
  
#line 44 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context-vcpu.cpp"
  inline void
  vcpu_save_state_and_upcall();
  
#line 52 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context-vcpu.cpp"
  inline bool
  vcpu_enter_kernel_mode(Vcpu_state *vcpu);
  
#line 93 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context-vcpu.cpp"
  inline bool
  vcpu_irqs_enabled(Vcpu_state *vcpu) const;
  
#line 101 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context-vcpu.cpp"
  inline bool
  vcpu_pagefaults_enabled(Vcpu_state *vcpu) const;
  
#line 109 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context-vcpu.cpp"
  inline bool
  vcpu_exceptions_enabled(Vcpu_state *vcpu) const;
  
#line 117 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context-vcpu.cpp"
  inline void
  vcpu_set_irq_pending();
  
#line 124 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context-vcpu.cpp"
  /** Return the space context.
      @return space context used for this execution context.
              Set with set_space_context().
   */
  
  inline Space *
  vcpu_user_space() const;

protected:  
#line 534 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  static inline void
  kernel_context(Cpu_number cpu, Context *ctxt);
  
#line 868 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * Set Context's currently active Sched_context.
   * @param sched Sched_context to be activated
   */
  
  inline void
  set_sched(Sched_context * const sched);
  
#line 890 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * Set Context's real-time period length.
   * @param period New period length in usecs
   */
  
  inline void
  set_period(Unsigned64 const period);
  
#line 1398 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * \brief Dequeue from lock and DRQ queues, abort pending DRQs
   */
  
  void
  shutdown_queues();
  
#line 1599 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  inline void
  kernel_context_drq(Drq::Request_func *func, void *arg,
                              Drq::Request_func *reply = 0);
  
#line 1692 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  void
  remote_ready_enqueue();
  
#line 52 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/context-ia32.cpp"
  inline void
  load_segments();
  
#line 61 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/context-ia32.cpp"
  inline void
  store_segments();
  
#line 21 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/context-ia32-32.cpp"
  inline void
  switch_gdt_user_entries(Context *to);
  
#line 32 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/context-ia32-32.cpp"
  inline void
  arch_setup_utcb_ptr();

private:  
#line 928 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * Enqueue current() if ready to fix up ready-list invariant.
   */
  
  inline void
  update_ready_list();
  
#line 1100 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * Switch scheduling context and execution context.
   * @param t Destination thread whose scheduling context and execution context
   *          should be activated.
   */
  
  inline bool FIASCO_WARN_RESULT
  schedule_switch_to_locked(Context *t);
  
#line 1153 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  inline Context *
  handle_helping(Context *t);
  
#line 1268 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  inline bool
  do_drq_reply(Drq *r, Drq_q::Drop_mode drop);
  
#line 1369 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * \brief Forced dequeue from lock wait queue, or DRQ queue.
   */
  
  void
  force_dequeue();
  
#line 1489 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  /**
   * \brief DRQ handler for state_change.
   *
   * This function basically wraps Context::state_change().
   */
  
  static unsigned
  handle_drq_state_change(Drq * /*src*/, Context *self, void * _rq);
  
#line 1626 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  static bool
  rcu_unblock(Rcu_item *i);
  
#line 1733 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
  inline void
  shutdown_drqs();
};
#line 1252 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#line 1257 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#line 2135 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/** logged context switch. */
class Tb_entry_ctx_sw : public Tb_entry
{
public:
  using Tb_entry::_ip;

  Context const *dst;		///< switcher target
  Context const *dst_orig;
  Address kernel_ip;
  Mword lock_cnt;
  Space const *from_space;
  Sched_context const *from_sched;
  Mword from_prio;
  unsigned print(int max, char *buf) const;
} __attribute__((packed));
#line 2158 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#line 132 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context-vcpu.cpp"


// --------------------------------------------------------------------------

#line 148 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context-vcpu.cpp"

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 398 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "atomic.h"
#line 401 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "entry_frame.h"
#line 406 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "logdefs.h"
#line 407 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "mem.h"
#line 1668 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"
#include "kdb_ke.h"
#line 2083 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

#include "fpu.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/context-ia32.cpp"

#include <cassert>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/context-ia32.cpp"
#include <cstdio>
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/context-ia32.cpp"
#include "globals.h"		// current()
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/context-ia32.cpp"
#include "lock_guard.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/context-ia32.cpp"
#include "space.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/context-ia32.cpp"
#include "thread_state.h"
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/context-ia32-32.cpp"

#include "cpu.h"
#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/context-ia32-32.cpp"
#include "gdt.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 431 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/** Initialize a context.  After setup, a switch_exec to this context results
    in a return to user code using the return registers at regs().  The
    return registers are not initialized however; neither is the space_context
    to be used in thread switching (use set_space_context() for that).
    @pre (_kernel_sp == 0)  &&  (* (stack end) == 0)
    @param thread_lock pointer to lock used to lock this context
    @param space_context the space context
 */

inline Context::Context()
: _kernel_sp(reinterpret_cast<Mword*>(regs())),
  _utcb_handler(0),
  _helper(this),
  _sched_context(),
  _sched(&_sched_context),
  _mode(Sched_mode(0)),
  _migration(0),
  _need_to_finish_migration(false)

{
  // NOTE: We do not have to synchronize the initialization of
  // _space_context because it is constant for all concurrent
  // invocations of this constructor.  When two threads concurrently
  // try to create a new task, they already synchronize in
  // sys_task_new() and avoid calling us twice with different
  // space_context arguments.

  set_cpu_of(this, Cpu::invalid());
}

#line 461 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline void
Context::reset_kernel_sp()
{
  _kernel_sp = reinterpret_cast<Mword*>(regs());
}

#line 468 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline void
Context::spill_fpu_if_owner()
{
  // spill FPU state into memory before migration
  if (state() & Thread_fpu_owner)
    {
      Fpu &f = Fpu::fpu.current();
      if (current() != this)
        f.enable();

      spill_fpu();
      f.set_owner(0);
      f.disable();
    }
}

#line 485 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"



inline void
Context::do_kill()
{
  // If this context owned the FPU, noone owns it now
  Fpu &f = Fpu::fpu.current();
  if (f.is_owner(this))
    {
      f.set_owner(0);
      f.disable();
    }
}

#line 505 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline bool
Context::check_for_current_cpu() const
{
  bool r = cpu() == current_cpu() || !Cpu::online(cpu());
  if (0 && EXPECT_FALSE(!r)) // debug output disabled
    printf("FAIL: cpu=%u (current=%u)\n",
           cxx::int_value<Cpu_number>(cpu()),
           cxx::int_value<Cpu_number>(current_cpu()));
  return r;
}

#line 517 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"



inline Mword
Context::state(bool check) const
{
  (void)check;
  assert_kdb(!check || check_for_current_cpu());
  return _state;
}

#line 527 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline Context*
Context::kernel_context(Cpu_number cpu)
{ return _kernel_ctxt.cpu(cpu); }

#line 542 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


/**
 * Does the context exist? .
 * @return true if this context has been initialized.
 */

inline Mword
Context::exists() const
{
  return state() != Thread_invalid;
}

#line 554 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/**
 * Is the context about to be deleted.
 * @return true if this context is in deletion.
 */

inline bool
Context::is_invalid() const
{ return state() == Thread_invalid; }

#line 563 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/**
 * Atomically add bits to state flags.
 * @param bits bits to be added to state flags
 * @return 1 if none of the bits that were added had been set before
 */

inline void
Context::state_add(Mword bits)
{
  assert_kdb(check_for_current_cpu());
  atomic_or(&_state, bits);
}

#line 576 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/**
 * Add bits in state flags. Unsafe (non-atomic) and
 *        fast version -- you must hold the kernel lock when you use it.
 * @pre cpu_lock.test() == true
 * @param bits bits to be added to state flags
 */ 

inline void
Context::state_add_dirty(Mword bits, bool check)
{
  (void)check;
  assert_kdb(!check || check_for_current_cpu());
  _state |= bits;
}

#line 591 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/**
 * Atomically delete bits from state flags.
 * @param bits bits to be removed from state flags
 * @return 1 if all of the bits that were removed had previously been set
 */

inline void
Context::state_del(Mword bits)
{
  assert_kdb (check_for_current_cpu());
  atomic_and(&_state, ~bits);
}

#line 604 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/**
 * Delete bits in state flags. Unsafe (non-atomic) and
 *        fast version -- you must hold the kernel lock when you use it.
 * @pre cpu_lock.test() == true
 * @param bits bits to be removed from state flags
 */

inline void
Context::state_del_dirty(Mword bits, bool check)
{
  (void)check;
  assert_kdb(!check || check_for_current_cpu());
  _state &= ~bits;
}

#line 619 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/**
 * Atomically delete and add bits in state flags, provided the
 *        following rules apply (otherwise state is not changed at all):
 *        - Bits that are to be set must be clear in state or clear in mask
 *        - Bits that are to be cleared must be set in state
 * @param mask Bits not set in mask shall be deleted from state flags
 * @param bits Bits to be added to state flags
 * @return 1 if state was changed, 0 otherwise
 */

inline Mword
Context::state_change_safely(Mword mask, Mword bits)
{
  assert_kdb (check_for_current_cpu());
  Mword old;

  do
    {
      old = _state;
      if (old & bits & mask | ~old & ~mask)
        return 0;
    }
  while (!cas(&_state, old, old & mask | bits));

  return 1;
}

#line 646 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/**
 * Atomically delete and add bits in state flags.
 * @param mask bits not set in mask shall be deleted from state flags
 * @param bits bits to be added to state flags
 */

inline Mword
Context::state_change(Mword mask, Mword bits)
{
  assert_kdb (check_for_current_cpu());
  return atomic_change(&_state, mask, bits);
}

#line 659 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/**
 * Delete and add bits in state flags. Unsafe (non-atomic) and
 *        fast version -- you must hold the kernel lock when you use it.
 * @pre cpu_lock.test() == true
 * @param mask Bits not set in mask shall be deleted from state flags
 * @param bits Bits to be added to state flags
 */

inline void
Context::state_change_dirty(Mword mask, Mword bits, bool check)
{
  (void)check;
  assert_kdb(!check || check_for_current_cpu());
  _state &= mask;
  _state |= bits;
}

#line 679 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"



inline Context_space_ref *
Context::space_ref()
{ return &_space; }

#line 685 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline Space *
Context::vcpu_aware_space() const
{ return _space.vcpu_aware(); }

#line 690 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/** Registers used when iret'ing to user mode.
    @return return registers
 */

inline Entry_frame *
Context::regs() const
{
  return reinterpret_cast<Entry_frame *>
    (Cpu::stack_align(reinterpret_cast<Mword>(this) + Size)) - 1;
}

#line 708 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/** Increment lock count.
    @post lock_cnt() > 0 */

inline void
Context::inc_lock_cnt()
{
  _lock_cnt++;
}

#line 717 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/** Decrement lock count.
    @pre lock_cnt() > 0
 */

inline void
Context::dec_lock_cnt()
{
  _lock_cnt--;
}

#line 727 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/** Lock count.
    @return lock count
 */

inline int
Context::lock_cnt() const
{
  return _lock_cnt;
}

#line 825 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"



inline void
Context::schedule_if(bool s)
{
  if (!s || Sched_context::rq.current().schedule_in_progress)
    return;

  schedule();
}

#line 836 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


/**
 * Return Context's Sched_context with id 'id'; return time slice 0 as default.
 * @return Sched_context with id 'id' or 0
 */

inline Sched_context *
Context::sched_context(unsigned short const id) const
{
  if (EXPECT_TRUE (!id))
    return const_cast<Sched_context*>(&_sched_context);
#if 0
  for (Sched_context *tmp = _sched_context.next();
      tmp != &_sched_context; tmp = tmp->next())
    if (tmp->id() == id)
      return tmp;
#endif
  return 0;
}

#line 856 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/**
 * Return Context's currently active Sched_context.
 * @return Active Sched_context
 */

inline Sched_context *
Context::sched() const
{
  return _sched;
}

#line 878 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/**
 * Return Context's real-time period length.
 * @return Period length in usecs
 */

inline Unsigned64
Context::period() const
{
  return _period;
}

#line 900 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/**
 * Return Context's scheduling mode.
 * @return Scheduling mode
 */

inline Context::Sched_mode
Context::mode() const
{
  return _mode;
}

#line 911 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/**
 * Set Context's scheduling mode.
 * @param mode New scheduling mode
 */

inline void
Context::set_mode(Context::Sched_mode const mode)
{
  _mode = mode;
}

#line 940 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/**
 * Check if Context is in ready-list.
 * @return 1 if thread is in ready-list, 0 otherwise
 */

inline Mword
Context::in_ready_list() const
{
  return sched()->in_ready_list();
}

#line 978 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


/** Helper.  Context that helps us by donating its time to us. It is
    set by switch_exec() if the calling thread says so.
    @return context that helps us and should be activated after freeing a lock.
*/

inline Context *
Context::helper() const
{
  return _helper;
}

#line 990 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"



inline void
Context::set_helper(Helping_mode const mode)
{
  switch (mode)
    {
    case Helping:
      _helper = current();
      break;
    case Not_Helping:
      _helper = this;
      break;
    case Ignore_Helping:
      // don't change _helper value
      break;
    }
}

#line 1009 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/** Donatee.  Context that receives our time slices, for example
    because it has locked us.
    @return context that should be activated instead of us when we're
            switch_exec()'ed.
*/

inline Context *
Context::donatee() const
{
  return _donatee;
}

#line 1021 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline void
Context::set_donatee(Context * const donatee)
{
  _donatee = donatee;
}

#line 1028 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline Mword *
Context::get_kernel_sp() const
{
  return _kernel_sp;
}

#line 1035 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline void
Context::set_kernel_sp(Mword * const esp)
{
  _kernel_sp = esp;
}

#line 1042 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline Fpu_state *
Context::fpu_state()
{
  return &_fpu_state;
}

#line 1049 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/**
 * Add to consumed CPU time.
 * @param quantum Implementation-specific time quantum (TSC ticks or usecs)
 */

inline void
Context::consume_time(Clock::Time quantum)
{
  _consumed_time += quantum;
}

#line 1082 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/**
 * Switch to scheduling context and execution context while not running under
 * CPU lock.
 */

inline void
Context::switch_to(Context *t)
{
  // Call switch_to_locked if CPU lock is already held
  assert (!cpu_lock.test());

  // Grab the CPU lock
  auto guard = lock_guard(cpu_lock);

  switch_to_locked(t);
}

#line 1099 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/**
 * Switch scheduling context and execution context.
 * @param t Destination thread whose scheduling context and execution context
 *          should be activated.
 */

inline bool FIASCO_WARN_RESULT
Context::schedule_switch_to_locked(Context *t)
{
   // Must be called with CPU lock held
  assert_kdb (cpu_lock.test());

  Sched_context::Ready_queue &rq = Sched_context::rq.current();
  // Switch to destination thread's scheduling context
  if (rq.current_sched() != t->sched())
    rq.set_current_sched(t->sched());

  // XXX: IPC dependency tracking belongs here.

  // Switch to destination thread's execution context, no helping involved
  if (t != this)
    return switch_exec_locked(t, Not_Helping);

  return handle_drq();
}

#line 1125 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline void
Context::switch_to_locked(Context *t)
{
  if (EXPECT_FALSE(schedule_switch_to_locked(t)))
    schedule();
}

#line 1133 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


/**
 * Switch execution context while not running under CPU lock.
 */

inline bool FIASCO_WARN_RESULT
Context::switch_exec(Context *t, enum Helping_mode mode)
{
  // Call switch_exec_locked if CPU lock is already held
  assert_kdb (!cpu_lock.test());

  // Grab the CPU lock
  auto guard = lock_guard(cpu_lock);

  return switch_exec_locked(t, mode);
}

#line 1239 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline void
Context::switch_exec_schedule_locked(Context *t, enum Helping_mode mode)
{
  if (EXPECT_FALSE(switch_exec_locked(t, mode)))
    schedule();
}

#line 1247 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline Context::Ku_mem_ptr<Utcb> const &
Context::utcb() const
{ return _utcb; }

#line 1408 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


/**
 * \brief Check for pending DRQs.
 * \return true if there are DRQs pending, false if not.
 */

inline bool
Context::drq_pending() const
{ return _drq_q.first(); }

#line 1418 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline void
Context::try_finish_migration()
{
  if (EXPECT_FALSE(_need_to_finish_migration))
    {
      _need_to_finish_migration = false;
      finish_migration();
    }
}

#line 1470 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


/**
 * \brief Get the queue item of the context.
 * \pre The context must currently not be in any queue.
 * \return The queue item of the context.
 *
 * The queue item can be used to enqueue the context to a Queue.
 * a context must be in at most one queue at a time.
 * To figure out the context corresponding to a queue item
 * context_of() can be used.
 */

inline Queue_item *
Context::queue_item()
{
  return &_drq;
}

#line 1529 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


/**
 * \brief Initiate a DRQ for the context.
 * \pre \a src must be the currently running context.
 * \param src the source of the DRQ (the context who initiates the DRQ).
 * \param func the DRQ handler.
 * \param arg the argument for the DRQ handler.
 * \param reply the reply handler (called in the context of \a src immediately
 *        after receiving a successful reply).
 *
 * DRQs are requests that any context can queue to any other context. DRQs are
 * the basic mechanism to initiate actions on remote CPUs in an MP system,
 * however, are also allowed locally.
 * DRQ handlers of pending DRQs are executed by Context::handle_drq() in the
 * context of the target context. Context::handle_drq() is basically called
 * after switching to a context in Context::switch_exec_locked().
 *
 * This function enqueues a DRQ and blocks the current context for a reply DRQ.
 */

inline void
Context::drq(Drq *drq, Drq::Request_func *func, void *arg,
             Drq::Request_func *reply,
             Drq::Exec_mode exec,
             Drq::Wait_mode wait)
{
  // printf("CPU[%2u:%p]: > Context::drq(this=%p, src=%p, func=%p, arg=%p)\n", current_cpu(), current(), this, src, func,arg);
  Context *cur = current();
  LOG_TRACE("DRQ Stuff", "drq", cur, Drq_log,
      l->type = Drq_log::Type::Send;
      l->rq = drq;
      l->func = (void*)func;
      l->reply = (void*)reply;
      l->thread = this;
      l->target_cpu = cpu();
      l->wait = wait;
  );
  //assert_kdb (current() == src);
  assert_kdb (!(wait == Drq::Wait && (cur->state() & Thread_drq_ready)) || cur->cpu() == cpu());
  assert_kdb (!((wait == Drq::Wait || drq == &_drq) && cur->state() & Thread_drq_wait));
  assert_kdb (!drq->queued());

  drq->func  = func;
  drq->reply = reply;
  drq->arg   = arg;
  cur->state_add(wait == Drq::Wait ? Thread_drq_wait : 0);


  enqueue_drq(drq, exec);

  //LOG_MSG_3VAL(src, "<drq", src->state(), Mword(this), 0);
  while (wait == Drq::Wait && cur->state() & Thread_drq_wait)
    {
      cur->state_del(Thread_ready_mask);
      cur->schedule();
    }

  LOG_TRACE("DRQ Stuff", "drq", cur, Drq_log,
      l->type = Drq_log::Type::Done;
      l->rq = drq;
      l->func = (void*)func;
      l->reply = (void*)reply;
      l->thread = this;
      l->target_cpu = cpu();
  );
  //LOG_MSG_3VAL(src, "drq>", src->state(), Mword(this), 0);
}

#line 1616 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline void
Context::drq(Drq::Request_func *func, void *arg,
             Drq::Request_func *reply,
             Drq::Exec_mode exec,
             Drq::Wait_mode wait)
{ return drq(&current()->_drq, func, arg, reply, exec, wait); }

#line 1503 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


/**
 * \brief Queue a DRQ for changing the contexts state.
 * \param mask bit mask for the state (state &= mask).
 * \param add bits to add to the state (state |= add).
 * \note This function is a preemption point.
 *
 * This function must be used to change the state of contexts that are
 * potentially running on a different CPU.
 */

inline void
Context::drq_state_change(Mword mask, Mword add)
{
  if (current() == this)
    {
      state_change_dirty(mask, add);
      return;
    }

  State_request rq;
  rq.del = mask;
  rq.add = add;
  drq(handle_drq_state_change, &rq);
}

#line 1635 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline void
Context::recover_jmp_buf(jmp_buf *b)
{ _recover_jmpbuf = b; }

#line 1669 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline Cpu_number
Context::cpu(bool running) const
{
  if (running)
    return Cpu_number::boot_cpu();

  return _cpu;
}

#line 1679 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline void
Context::enable_tlb(Cpu_number)
{}

#line 1684 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline void
Context::disable_tlb(Cpu_number)
{}

#line 1736 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"



inline void
Context::rcu_wait()
{
  // The UP case does not need to block for the next grace period, because
  // the CPU is always in a quiescent state when the interrupts where enabled
}

#line 1745 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline void
Context::xcpu_tlb_flush(bool, Mem_space *, Mem_space *)
{}

#line 2085 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline void
Context::spill_fpu()
{
  // If we own the FPU, we should never be getting an "FPU unavailable" trap
  assert_kdb (Fpu::fpu.current().owner() == this);
  assert_kdb (state() & Thread_fpu_owner);
  assert_kdb (fpu_state());

  // Save the FPU state of the previous FPU owner (lazy) if applicable
  Fpu::save_state(fpu_state());
  state_del_dirty(Thread_fpu_owner);
}

#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context-vcpu.cpp"


inline Context::Ku_mem_ptr<Vcpu_state> const &
Context::vcpu_state() const
{ return _vcpu_state; }

#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context-vcpu.cpp"



inline Mword
Context::vcpu_disable_irqs()
{
  if (EXPECT_FALSE(state() & Thread_vcpu_enabled))
    {
      Vcpu_state *vcpu = vcpu_state().access();
      Mword s = vcpu->state;
      vcpu->state = s & ~Vcpu_state::F_irqs;
      return s & Vcpu_state::F_irqs;
    }
  return 0;
}

#line 33 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context-vcpu.cpp"


inline void
Context::vcpu_restore_irqs(Mword irqs)
{
  if (EXPECT_FALSE((irqs & Vcpu_state::F_irqs)
                   && (state() & Thread_vcpu_enabled)))
    vcpu_state().access()->state |= Vcpu_state::F_irqs;
}

#line 42 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context-vcpu.cpp"


inline void
Context::vcpu_save_state_and_upcall()
{
  extern char leave_by_vcpu_upcall[];
  _exc_cont.activate(regs(), leave_by_vcpu_upcall);
}

#line 1648 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline void
Context::arch_load_vcpu_kern_state(Vcpu_state *, bool)
{}

#line 50 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context-vcpu.cpp"


inline bool
Context::vcpu_enter_kernel_mode(Vcpu_state *vcpu)
{
  if (EXPECT_FALSE(state() & Thread_vcpu_enabled))
    {
      state_del_dirty(Thread_vcpu_user);
      vcpu->_saved_state = vcpu->state;
      Mword flags = Vcpu_state::F_traps
	            | Vcpu_state::F_user_mode;
      vcpu->state &= ~flags;

      if (vcpu->_saved_state & Vcpu_state::F_user_mode)
	vcpu->_sp = vcpu->_entry_sp;
      else
	vcpu->_sp = regs()->sp();

      if (_space.user_mode())
	{
	  _space.user_mode(false);
	  state_del_dirty(Thread_vcpu_fpu_disabled);

          bool load_cpu_state = current() == this;

          arch_load_vcpu_kern_state(vcpu, load_cpu_state);

	  if (load_cpu_state)
	    {
	      if (state() & Thread_fpu_owner)
		Fpu::enable();

	      space()->switchin_context(vcpu_user_space());
	      return true;
	    }
	}
    }
  return false;
}

#line 89 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context-vcpu.cpp"




inline bool
Context::vcpu_irqs_enabled(Vcpu_state *vcpu) const
{
  return EXPECT_FALSE(state() & Thread_vcpu_enabled)
    && vcpu->state & Vcpu_state::F_irqs;
}

#line 99 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context-vcpu.cpp"


inline bool
Context::vcpu_pagefaults_enabled(Vcpu_state *vcpu) const
{
  return EXPECT_FALSE(state() & Thread_vcpu_enabled)
    && vcpu->state & Vcpu_state::F_page_faults;
}

#line 107 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context-vcpu.cpp"


inline bool
Context::vcpu_exceptions_enabled(Vcpu_state *vcpu) const
{
  return EXPECT_FALSE(state() & Thread_vcpu_enabled)
    && vcpu->state & Vcpu_state::F_exceptions;
}

#line 115 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context-vcpu.cpp"


inline void
Context::vcpu_set_irq_pending()
{
  if (EXPECT_FALSE(state() & Thread_vcpu_enabled))
    vcpu_state().access()->sticky_flags |= Vcpu_state::Sf_irq_pending;
}

#line 123 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context-vcpu.cpp"

/** Return the space context.
    @return space context used for this execution context.
            Set with set_space_context().
 */

inline Space *
Context::vcpu_user_space() const
{ return _space.vcpu_user(); }

#line 532 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline void
Context::kernel_context(Cpu_number cpu, Context *ctxt)
{ _kernel_ctxt.cpu(cpu) = ctxt; }

#line 867 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/**
 * Set Context's currently active Sched_context.
 * @param sched Sched_context to be activated
 */

inline void
Context::set_sched(Sched_context * const sched)
{
  _sched = sched;
}

#line 889 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/**
 * Set Context's real-time period length.
 * @param period New period length in usecs
 */

inline void
Context::set_period(Unsigned64 const period)
{
  _period = period;
}

#line 1597 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline void
Context::kernel_context_drq(Drq::Request_func *func, void *arg,
                            Drq::Request_func *reply)
{
  char align_buffer[2*sizeof(Drq)];
  Drq *mdrq = new ((void*)((Address)(align_buffer + __alignof__(Drq) - 1) & ~(__alignof__(Drq)-1))) Drq;


  mdrq->func  = func;
  mdrq->arg   = arg;
  mdrq->reply = reply;
  Context *kc = kernel_context(current_cpu());

  kc->_drq_q.enq(mdrq);
  bool resched = schedule_switch_to_locked(kc);
  (void)resched;
}

#line 50 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/context-ia32.cpp"


inline void
Context::load_segments()
{
  Cpu::set_es((Unsigned32)_es);
  Cpu::set_fs((Unsigned32)_fs);
  Cpu::set_gs((Unsigned32)_gs);
}

#line 59 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/context-ia32.cpp"


inline void
Context::store_segments()
{
  _es = Cpu::get_es();
  _fs = Cpu::get_fs();
  _gs = Cpu::get_gs();
}

#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/context-ia32-32.cpp"


inline void
Context::switch_gdt_user_entries(Context *to)
{
  Gdt &gdt = *Cpu::cpus.cpu(to->cpu()).get_gdt();
  for (unsigned i = 0; i < Gdt_user_entries; ++i)
    gdt[(Gdt::gdt_user_entry1 / 8) + i] = to->_gdt_user_entries[i];

  gdt[Gdt::gdt_utcb/8] = to->_gdt_user_entries[Gdt_user_entries];
}

#line 30 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/context-ia32-32.cpp"


inline void
Context::arch_setup_utcb_ptr()
{
  _utcb.access()->utcb_addr = (Mword)_utcb.usr().get();
  _gdt_user_entries[Gdt_user_entries] = Gdt_entry((Address)&_utcb.usr()->utcb_addr, 0xfffff, Gdt_entry::Access_user
                                                  | Gdt_entry::Access_data_write | Gdt_entry::Accessed, Gdt_entry::Size_32 | 0x80);
  _gs = _fs = Gdt::gdt_utcb | 3;
}

#line 1060 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"

/**
 * Update consumed CPU time during each context switch and when
 *        reading out the current thread's consumed CPU time.
 */

inline void
Context::update_consumed_time()
{
  if (Config::Fine_grained_cputime)
    consume_time (_clock.cpu(cpu()).delta());
}

#line 1072 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline Cpu_time
Context::consumed_time()
{
  if (Config::Fine_grained_cputime)
    return _clock.cpu(cpu()).us(_consumed_time);

  return _consumed_time;
}

#line 1653 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline void
Context::arch_load_vcpu_user_state(Vcpu_state *, bool)
{}

#line 1658 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline void
Context::arch_update_vcpu_state(Vcpu_state *)
{}

#line 2099 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


/**
 * When switching away from the FPU owner, disable the FPU to cause
 * the next FPU access to trap.
 * When switching back to the FPU owner, enable the FPU so we don't
 * get an FPU trap on FPU access.
 */

inline void
Context::switch_fpu(Context *t)
{
  Fpu &f = Fpu::fpu.current();
  if (f.is_owner(this))
    f.disable();
  else if (f.is_owner(t) && !(t->state() & Thread_vcpu_fpu_disabled))
    f.enable();
}

#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/context-ia32.cpp"



inline void
Context::spill_user_state()
{}

#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/context-ia32.cpp"


inline void
Context::fill_user_state()
{}

#line 43 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/context-ia32-32.cpp"




inline void
Context::switch_cpu(Context *t)
{
  Mword dummy1, dummy2, dummy3, dummy4;

  update_consumed_time();

  store_segments();

  switch_gdt_user_entries(t);

  asm volatile
    (
     "   pushl %%ebp			\n\t"	// save base ptr of old thread
     "   pushl $1f			\n\t"	// restart addr to old stack
     "   movl  %%esp, (%0)		\n\t"	// save stack pointer
     "   movl  (%1), %%esp		\n\t"	// load new stack pointer
     						// in new context now (cli'd)
     "   movl  %2, %%eax		\n\t"	// new thread's "this"
     "   call  switchin_context_label	\n\t"	// switch pagetable
     "   popl  %%eax			\n\t"	// don't do ret here -- we want
     "   jmp   *%%eax			\n\t"	// to preserve the return stack
						// restart code
     "  .p2align 4			\n\t"	// start code at new cache line
     "1: popl %%ebp			\n\t"	// restore base ptr

     : "=c" (dummy1), "=S" (dummy2), "=D" (dummy3), "=d" (dummy4)
     : "c" (&_kernel_sp), "S" (&t->_kernel_sp), "D" (t), "d" (this)
     : "eax", "ebx", "memory");
}

#line 1252 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline Context *
Context::Context_member::context() const
{ return context_of(this); }

#line 1257 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline void
Context::Drq_q::enq(Drq *rq)
{
  assert_kdb(cpu_lock.test());
  auto guard = lock_guard(q_lock());
  enqueue(rq);
}

#line 1266 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline bool
Context::do_drq_reply(Drq *r, Drq_q::Drop_mode drop)
{
  state_change_dirty(~Thread_drq_wait, Thread_ready);
  // r->state = Drq::Reply_handled;
  if (drop == Drq_q::No_drop && r->reply)
    return r->reply(r, this, r->arg) & Drq::Need_resched;

  return false;
}

#line 1278 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline bool
Context::Drq_q::execute_request(Drq *r, Drop_mode drop, bool local)
{
  bool need_resched = false;
  Context *const self = context();
  // printf("CPU[%2u:%p]: context=%p: handle request for %p (func=%p, arg=%p)\n", current_cpu(), current(), context(), r->context(), r->func, r->arg);
  if (r->context() == self)
    {
      LOG_TRACE("DRQ handling", "drq", current(), Drq_log,
	  l->type = Drq_log::Type::Do_reply;
          l->rq = r;
	  l->func = (void*)r->func;
	  l->reply = (void*)r->reply;
	  l->thread = r->context();
	  l->target_cpu = current_cpu();
	  l->wait = 0;
      );
      //LOG_MSG_3VAL(current(), "hrP", current_cpu() | (drop ? 0x100: 0), (Mword)r->context(), (Mword)r->func);
      return self->do_drq_reply(r, drop);
    }
  else
    {
      LOG_TRACE("DRQ handling", "drq", current(), Drq_log,
	  l->type = Drq_log::Type::Do_request;
          l->rq = r;
	  l->func = (void*)r->func;
	  l->reply = (void*)r->reply;
	  l->thread = r->context();
	  l->target_cpu = current_cpu();
	  l->wait = 0;
      );
      // r->state = Drq::Idle;
      unsigned answer = 0;
      //LOG_MSG_3VAL(current(), "hrq", current_cpu() | (drop ? 0x100: 0), (Mword)r->context(), (Mword)r->func);
      if (EXPECT_TRUE(drop == No_drop && r->func))
	answer = r->func(r, self, r->arg);
      else if (EXPECT_FALSE(drop == Drop))
	// flag DRQ abort for requester
	r->arg = (void*)-1;
       // LOG_MSG_3VAL(current(), "hrq-", answer, current()->state() /*(Mword)r->context()*/, (Mword)r->func);
      need_resched |= answer & Drq::Need_resched;
      //r->state = Drq::Handled;

      // enqueue answer
      if (!(answer & Drq::No_answer))
	{
	  if (local)
	    return r->context()->do_drq_reply(r, drop) || need_resched;
	  else
	    need_resched |= r->context()->enqueue_drq(r, Drq::Target_ctxt);
	}
    }
  return need_resched;
}

#line 1334 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline bool
Context::Drq_q::dequeue(Drq *drq, Queue_item::Status reason)
{
  auto guard = lock_guard(q_lock());
  if (!drq->queued())
    return false;
  return Queue::dequeue(drq, reason);
}

#line 1344 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline bool
Context::Drq_q::handle_requests(Drop_mode drop)
{
  // printf("CPU[%2u:%p]: > Context::Drq_q::handle_requests() context=%p\n", current_cpu(), current(), context());
  bool need_resched = false;
  while (1)
    {
      Queue_item *qi;
	{
	  auto guard = lock_guard(q_lock());
	  qi = first();
	  if (!qi)
	    return need_resched;

	  check_kdb (Queue::dequeue(qi, Queue_item::Ok));
	}

      Drq *r = static_cast<Drq*>(qi);
      // printf("CPU[%2u:%p]: context=%p: handle request for %p (func=%p, arg=%p)\n", current_cpu(), current(), context(), r->context(), r->func, r->arg);
      need_resched |= execute_request(r, drop, false);
    }
}

#line 418 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context.cpp"


inline Kobject_iface * __attribute__((nonnull(1, 2)))
Context_ptr::ptr(Space *s, L4_fpage::Rights *rights) const
{
  assert_kdb (cpu_lock.test());

  return static_cast<Obj_space*>(s)->lookup_local(_t, rights);
}

#endif // context_h
