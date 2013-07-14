// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef timeout_h
#define timeout_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"

#include <cxx/hlist>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"
#include "l4_types.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"
#include "per_cpu_data.h"

//
// INTERFACE definition follows 
//

#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"

/** A timeout basic object. It contains the necessary queues and handles
    enqueuing, dequeuing and handling of timeouts. Real timeout classes
    should overwrite expired(), which will do the real work, if an
    timeout hits.
 */
class Timeout : public cxx::H_list_item
{
  friend class Jdb_timeout_list;
  friend class Jdb_list_timeouts;
  friend class Timeout_q;

public:
  typedef cxx::H_list<Timeout> To_list;

protected:
  /**
   * Absolute system time we want to be woken up at.
   */
  Unsigned64 _wakeup;

private:
  /**
   * Default copy constructor (is undefined).
   */
  Timeout(const Timeout&);

  /**
   * Overwritten timeout handler function.
   * @return true if a reschedule is necessary, false otherwise.
   */
  virtual bool expired();

  struct
  {
    bool     hit  : 1;
    unsigned res  : 6; // performance optimization
  } _flags;

public:  
#line 135 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"
  /**
   * Timeout constructor.
   */
  
  inline Timeout();
  
#line 146 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"
  /**
   * Initializes an timeout object.
   */
  
  inline void
  init();
  
#line 166 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"
  /**
   * Check if timeout is set.
   */
  
  inline bool
  is_set();
  
#line 176 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"
  /**
   * Check if timeout has hit.
   */
  
  inline bool
  has_hit();
  
#line 188 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"
  inline void
  set(Unsigned64 clock, Cpu_number cpu);
  
#line 201 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"
  /**
   * Return remaining time of timeout.
   */
  
  inline Signed64
  get_timeout(Unsigned64 clock);
  
#line 212 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"
  inline void
  set_again(Cpu_number cpu);
  
#line 227 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"
  inline void
  reset();
  
#line 261 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"
  /**
   * Dequeue an expired timeout.
   * @return true if a reschedule is necessary, false otherwise.
   */
  
  inline bool
  dequeue(bool is_expired = true);

private:  
#line 238 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"
  /**
   * Dequeue an expired timeout.
   * @return true if a reschedule is necessary, false otherwise.
   */
  
  inline bool
  expire();
};
#line 45 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"


class Timeout_q
{
private:
  /**
   * Timeout queue count (2^n) and  distance between two queues in 2^n.
   */
  enum
  {
    Wakeup_queue_count	  = 8,
    Wakeup_queue_distance = 12 // i.e. (1<<12)us
  };

  typedef Timeout::To_list To_list;
  typedef To_list::Iterator Iterator;
  typedef To_list::Const_iterator Const_iterator;

  /**
   * The timeout queues.
   */
  To_list _q[Wakeup_queue_count];

  /**
   * The current programmed timeout.
   */
  Unsigned64 _current;
  Unsigned64 _old_clock;

public:
  static Per_cpu<Timeout_q> timeout_queue;

public:  
#line 96 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"
  inline Timeout_q::To_list &
  first(int index);
  
#line 101 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"
  inline Timeout_q::To_list const &
  first(int index) const;
  
#line 106 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"
  inline unsigned
  queues() const;
  
#line 110 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"
  /**
   * Enqueue a new timeout.
   */
  
  inline void
  enqueue(Timeout *to);
  
#line 265 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"
  /**
   * Handles the timeouts, i.e. call expired() for the expired timeouts
   * and programs the "oneshot timer" to the next timeout.
   * @return true if a reschedule is necessary, false otherwise.
   */
  
  
  inline bool
  do_timeouts();
  
#line 351 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"
  inline Timeout_q();
  
#line 356 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"
  inline bool
  have_timeouts(Timeout const *ignore) const;
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 80 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"

#include <cassert>
#line 82 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"
#include "cpu_lock.h"
#line 83 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"
#include "kip.h"
#line 84 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"
#include "lock_guard.h"
#line 85 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"
#include "timer.h"
#line 87 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"
#include <climits>
#line 88 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"
#include "config.h"
#line 89 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"
#include "kdb_ke.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 133 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"


/**
 * Timeout constructor.
 */

inline Timeout::Timeout()
{
  _flags.hit = 0;
  _flags.res = 0;
}

#line 144 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"


/**
 * Initializes an timeout object.
 */

inline void
Timeout::init()
{
  _wakeup = ULONG_LONG_MAX;
}

#line 165 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"

/**
 * Check if timeout is set.
 */

inline bool
Timeout::is_set()
{
  return To_list::in_list(this);
}

#line 175 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"

/**
 * Check if timeout has hit.
 */

inline bool
Timeout::has_hit()
{
  return _flags.hit;
}

#line 108 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"


/**
 * Enqueue a new timeout.
 */

inline void
Timeout_q::enqueue(Timeout *to)
{
  int queue = (to->_wakeup >> Wakeup_queue_distance) & (Wakeup_queue_count-1);

  To_list &q = first(queue);
  Iterator tmp = q.begin();

  while (tmp != q.end() && tmp->_wakeup < to->_wakeup)
    ++tmp;

  q.insert_before(to, tmp);

  if (Config::Scheduler_one_shot && (to->_wakeup <= _current))
    {
      _current = to->_wakeup;
      Timer::update_timer(_current);
    }
}

#line 185 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"




inline void
Timeout::set(Unsigned64 clock, Cpu_number cpu)
{
  // XXX uses global kernel lock
  auto guard = lock_guard(cpu_lock);

  assert (!is_set());

  _wakeup = clock;
  Timeout_q::timeout_queue.cpu(cpu).enqueue(this);
}

#line 200 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"

/**
 * Return remaining time of timeout.
 */

inline Signed64
Timeout::get_timeout(Unsigned64 clock)
{
  return _wakeup - clock;
}

#line 210 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"



inline void
Timeout::set_again(Cpu_number cpu)
{
  // XXX uses global kernel lock
  auto guard = lock_guard(cpu_lock);

  assert(! is_set());
  if (has_hit())
    return;

  Timeout_q::timeout_queue.cpu(cpu).enqueue(this);
}

#line 225 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"



inline void
Timeout::reset()
{
  assert_kdb (cpu_lock.test());
  To_list::remove(this);

  // Normaly we should reprogramm the timer in one shot mode
  // But we let the timer interrupt handler to do this "lazily", to save cycles
}

#line 249 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"
/**
 * Dequeue an expired timeout.
 * @return true if a reschedule is necessary, false otherwise.
 */

inline bool
Timeout::dequeue(bool is_expired)
{
  To_list::remove(this);

  if (is_expired)
    return expire();
  else
    return false;
}

#line 93 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"



inline Timeout_q::To_list &
Timeout_q::first(int index)
{ return _q[index & (Wakeup_queue_count-1)]; }

#line 99 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"


inline Timeout_q::To_list const &
Timeout_q::first(int index) const
{ return _q[index & (Wakeup_queue_count-1)]; }

#line 104 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"


inline unsigned
Timeout_q::queues() const { return Wakeup_queue_count; }

#line 237 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"

/**
 * Dequeue an expired timeout.
 * @return true if a reschedule is necessary, false otherwise.
 */

inline bool
Timeout::expire()
{
  _flags.hit = 1;
  return expired();
}

#line 264 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"

/**
 * Handles the timeouts, i.e. call expired() for the expired timeouts
 * and programs the "oneshot timer" to the next timeout.
 * @return true if a reschedule is necessary, false otherwise.
 */


inline bool
Timeout_q::do_timeouts()
{
  bool reschedule = false;

  // We test if the time between 2 activiations of this function is greater
  // than the distance between two timeout queues.
  // To avoid to lose timeouts, we calculating the missed queues and
  // scan them too.
  // This can only happen, if we dont enter the timer interrupt for a long
  // time, usual with one shot timer.
  // Because we initalize old_dequeue_time with zero,
  // we can get an "miss" on the first timerinterrupt.
  // But this is booting the system, which is uncritical.

  // Calculate which timeout queues needs to be checked.
  int start = (_old_clock >> Wakeup_queue_distance);
  int diff  = (Kip::k()->clock >> Wakeup_queue_distance) - start;
  int end   = (start + diff + 1) & (Wakeup_queue_count - 1);

  // wrap around
  start = start & (Wakeup_queue_count - 1);

  // test if an complete miss
  if (diff >= Wakeup_queue_count)
    start = end = 0; // scan all queues

  // update old_clock for the next run
  _old_clock = Kip::k()->clock;

  // ensure we always terminate
  assert((end >= 0) && (end < Wakeup_queue_count));

  for (;;)
    {
      To_list &q = first(start);
      Iterator timeout = q.begin();

      // now scan this queue for timeouts below current clock
      while (timeout != q.end() && timeout->_wakeup <= (Kip::k()->clock))
        {
          reschedule |= timeout->expire();
          timeout = q.erase(timeout);
        }

      // next queue
      start = (start + 1) & (Wakeup_queue_count - 1);

      if (start == end)
	break;
    }

  if (Config::Scheduler_one_shot)
    {
      // scan all queues for the next minimum
      //_current = (Unsigned64) ULONG_LONG_MAX;
      _current = Kip::k()->clock + 10000; //ms
      bool update_timer = true;

      for (int i = 0; i < Wakeup_queue_count; i++)
	{
	  // make sure that something enqueued other than the dummy element
	  if (first(i).empty())
	    continue;

	  update_timer = true;

	  if (first(i).front()->_wakeup < _current)
	    _current =  first(i).front()->_wakeup;
	}

      if (update_timer)
	Timer::update_timer(_current);

    }
  return reschedule;
}

#line 349 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"


inline Timeout_q::Timeout_q()
: _current(ULONG_LONG_MAX), _old_clock(0)
{}

#line 354 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/timeout.cpp"


inline bool
Timeout_q::have_timeouts(Timeout const *ignore) const
{
  for (unsigned i = 0; i < Wakeup_queue_count; ++i)
    {
      To_list const &t = first(i);
      if (!t.empty())
        {
          To_list::Const_iterator f = t.begin();
          if (*f == ignore && (++f) == t.end())
            continue;

          return true;
        }
    }

  return false;
}

#endif // timeout_h
