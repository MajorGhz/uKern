// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef sched_context_h
#define sched_context_h
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context-fixed_prio.cpp"

#include <cxx/dlist>
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context-fixed_prio.cpp"
#include "member_offs.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context-fixed_prio.cpp"
#include "types.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context-fixed_prio.cpp"
#include "globals.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context-fixed_prio.cpp"
#include "ready_queue_fp.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context.cpp"
#include "per_cpu_data.h"
#line 151 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context.cpp"

#include "tb_entry.h"

//
// INTERFACE definition follows 
//

#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context-fixed_prio.cpp"


class Sched_context : public cxx::D_list_item
{
  MEMBER_OFFSET();
  friend class Jdb_list_timeouts;
  friend class Jdb_thread_list;

  template<typename T>
  friend struct Jdb_thread_list_policy;

  union Sp
  {
    L4_sched_param p;
    L4_sched_param_legacy legacy_fixed_prio;
    L4_sched_param_fixed_prio fixed_prio;
  };

public:
  typedef cxx::Sd_list<Sched_context> Fp_list;

  class Ready_queue_base : public Ready_queue_fp<Sched_context>
  {
  public:
    void activate(Sched_context *s)
    { _current_sched = s; }
    Sched_context *current_sched() const { return _current_sched; }
    void ready_enqueue(Sched_context *sc)
    {
      assert_kdb(cpu_lock.test());

      // Don't enqueue threads which are already enqueued
      if (EXPECT_FALSE (sc->in_ready_list()))
        return;

      enqueue(sc, sc == current_sched());
    }

  private:
    Sched_context *_current_sched;
  };

  Context *context() const { return context_of(this); }

private:
  unsigned short _prio;
  Unsigned64 _quantum;
  Unsigned64 _left;

  friend class Ready_queue_fp<Sched_context>;

#line 3 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context.cpp"
private:

public:
  class Ready_queue : public Ready_queue_base
  {
  public:
    void set_current_sched(Sched_context *sched);
    void invalidate_sched() { activate(0); }
    bool deblock(Sched_context *sc, Sched_context *crs, bool lazy_q = false);
    void deblock(Sched_context *sc);
    void ready_enqueue(Sched_context *sc)
    {
      assert_kdb(cpu_lock.test());

      // Don't enqueue threads which are already enqueued
      if (EXPECT_FALSE (sc->in_ready_list()))
        return;

      enqueue(sc, sc == current_sched());
    }

    void ready_dequeue(Sched_context *sc)
    {
      assert_kdb (cpu_lock.test());

      // Don't dequeue threads which aren't enqueued
      if (EXPECT_FALSE (!sc->in_ready_list()))
        return;

      dequeue(sc);
    }

    void switch_sched(Sched_context *from, Sched_context *to)
    {
      assert_kdb (cpu_lock.test());

      // If we're leaving the global timeslice, invalidate it This causes
      // schedule() to select a new timeslice via set_current_sched()
      if (from == current_sched())
        invalidate_sched();

      if (from->in_ready_list())
        dequeue(from);

      enqueue(to, false);
    }

    Context *schedule_in_progress;
  };

  static Per_cpu<Ready_queue> rq;

public:  
#line 75 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context-fixed_prio.cpp"
  /**
   * Constructor
   */
  
  Sched_context();
  
#line 86 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context-fixed_prio.cpp"
  /**
   * Return priority of Sched_context
   */
  
  inline unsigned short
  prio() const;
  
#line 97 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context-fixed_prio.cpp"
  int
  set(L4_sched_param const *_p);
  
#line 132 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context-fixed_prio.cpp"
  /**
   * Return remaining time quantum of Sched_context
   */
  
  inline Unsigned64
  left() const;
  
#line 143 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context-fixed_prio.cpp"
  inline void
  replenish();
  
#line 147 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context-fixed_prio.cpp"
  /**
   * Set remaining time quantum of Sched_context
   */
  
  inline void
  set_left(Unsigned64 left);
  
#line 158 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context-fixed_prio.cpp"
  /**
   * Check if Context is in ready-list.
   * @return 1 if thread is in ready-list, 0 otherwise
   */
  
  inline Mword
  in_ready_list() const;
  
#line 170 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context-fixed_prio.cpp"
  inline bool
  dominates(Sched_context *sc);
};
#line 66 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context.cpp"
#line 153 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context.cpp"

/** logged scheduling event. */
class Tb_entry_sched : public Tb_entry
{
public:
  unsigned short mode;
  Context const *owner;
  unsigned short id;
  unsigned short prio;
  signed long left;
  unsigned long quantum;

  unsigned print(int max, char *buf) const;
} __attribute__((packed));

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 58 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context.cpp"

#include "kdb_ke.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 84 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context-fixed_prio.cpp"


/**
 * Return priority of Sched_context
 */

inline unsigned short
Sched_context::prio() const
{
  return _prio;
}

#line 131 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context-fixed_prio.cpp"

/**
 * Return remaining time quantum of Sched_context
 */

inline Unsigned64
Sched_context::left() const
{
  return _left;
}

#line 146 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context-fixed_prio.cpp"

/**
 * Set remaining time quantum of Sched_context
 */

inline void
Sched_context::set_left(Unsigned64 left)
{
  _left = left;
}

#line 141 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context-fixed_prio.cpp"


inline void
Sched_context::replenish()
{ set_left(_quantum); }

#line 156 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context-fixed_prio.cpp"


/**
 * Check if Context is in ready-list.
 * @return 1 if thread is in ready-list, 0 otherwise
 */

inline Mword
Sched_context::in_ready_list() const
{
  return Fp_list::in_list(this);
}

#line 168 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context-fixed_prio.cpp"


inline bool
Sched_context::dominates(Sched_context *sc)
{ return prio() > sc->prio(); }

#line 99 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context.cpp"


/**
 * \param cpu must be current_cpu()
 */

inline void
Sched_context::Ready_queue::deblock(Sched_context *sc)
{
  assert_kdb(cpu_lock.test());

  Sched_context *cs = current_sched();
  if (sc != cs)
      deblock_refill(sc);

  ready_enqueue(sc);
}

#line 116 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sched_context.cpp"

/**
 * \param cpu must be current_cpu()
 * \param crs the Sched_context of the current context
 * \param lazy_q queue lazily if applicable
 */

inline bool
Sched_context::Ready_queue::deblock(Sched_context *sc, Sched_context *crs, bool lazy_q)
{
  assert_kdb(cpu_lock.test());

  Sched_context *cs = current_sched();
  bool res = true;
  if (sc == cs)
    {
      if (crs->dominates(sc))
	res = false;
    }
  else
    {
      deblock_refill(sc);

      if ((EXPECT_TRUE(cs != 0) && cs->dominates(sc)) || crs->dominates(sc))
	res = false;
    }

  if (res && lazy_q)
    return true;

  ready_enqueue(sc);
  return res;
}

#endif // sched_context_h
