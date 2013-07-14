// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef prio_list_h
#define prio_list_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"

#include <cassert>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"
#include <cxx/dlist>
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"
#include <cxx/hlist>
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"
#include "member_offs.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"
#include "spin_lock.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"
#include "types.h"

//
// INTERFACE definition follows 
//

#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"

/**
 * Priority sorted list with insert complexity O(n) n = number of available
 * priorities (256 in Fiasco).
 */


class Prio_list_elem;
#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"

/**
 * Priority sorted list.
 *
 * The list is organized in a way that the highest priority member can be
 * found with O(1). Ever dequeue operation is also O(1).
 *
 * There is a forward iteratable list with at most one element per priority.
 * Elements with the same priority are handled in a double-linked circular
 * list for each priority. This double-linked list implements FIFO policy for
 * finding the next element.
 */
class Prio_list : private cxx::H_list<Prio_list_elem>
{
  MEMBER_OFFSET();
  friend class Jdb_sender_list;
public:
  typedef cxx::H_list<Prio_list_elem> P_list;
  typedef cxx::D_list_cyclic<Prio_list_elem> S_list;

  using P_list::front;
  using P_list::empty;

  Prio_list_elem *first() const { return front(); }

public:  
#line 96 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"
  inline Prio_list_elem *
  next(Prio_list_elem *e) const;
  
#line 105 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"
  /**
   * Insert a new element into the priority list.
   * @param e the element to insert
   * @param prio the priority for the element
   */
  
  inline void
  insert(Prio_list_elem *e, unsigned short prio);
  
#line 138 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"
  /**
   * Dequeue a given element from the list.
   * @param e the element to dequeue
   */
  
  inline void
  dequeue(Prio_list_elem *e, Prio_list_elem **next = 0);
};
#line 42 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"

class Iteratable_prio_list : public Prio_list
{
public:
  Spin_lock<> *lock() { return &_lock; }

private:
  Prio_list_elem *_cursor;
  Spin_lock<> _lock;

public:  
#line 175 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"
  inline Iteratable_prio_list();
  
#line 177 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"
  /**
   * Dequeue a given element from the list.
   * @param e the element to dequeue
   */
  
  inline void
  dequeue(Prio_list_elem *e);
  
#line 193 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"
  inline void
  cursor(Prio_list_elem *e);
  
#line 198 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"
  inline Prio_list_elem *
  cursor() const;
};
#line 52 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"

typedef Iteratable_prio_list Locked_prio_list;
#line 54 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"


/**
 * Single element of a priority sorted list.
 */
class Prio_list_elem : public cxx::H_list_item, public cxx::D_list_item
{
  MEMBER_OFFSET();
private:
  friend class Prio_list;
  friend class Jdb_sender_list;
  typedef cxx::D_list_cyclic<Prio_list_elem> S_list;

  /**
   * Priority, the higher the better.
   */
  unsigned short _prio;

public:  
#line 87 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"
  /**
   * Get the priority.
   */
  
  inline unsigned short
  prio() const;
  
#line 131 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"
  /**
   * Is the element actually enqueued?
   * @return true if the element is actaully enqueued in a list.
   */
  
  inline bool in_list() const;

private:  
#line 77 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"
  /**
   * Setup pointers for enqueue.
   */
  
  inline void
  init(unsigned short p);
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 94 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"


inline Prio_list_elem *
Prio_list::next(Prio_list_elem *e) const
{
  S_list::Iterator i = ++S_list::iter(e);
  if (P_list::in_list(*i))
    return *++P_list::iter(*i);
  return *i;
}

#line 76 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"

/**
 * Setup pointers for enqueue.
 */

inline void
Prio_list_elem::init(unsigned short p)
{
  _prio = p;
}

#line 104 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"

/**
 * Insert a new element into the priority list.
 * @param e the element to insert
 * @param prio the priority for the element
 */

inline void
Prio_list::insert(Prio_list_elem *e, unsigned short prio)
{
  assert (e);
  e->init(prio);

  Iterator pos = begin();

  while (pos != end() && pos->prio() > prio)
    ++pos;

  if (pos != end() && pos->prio() == prio)
    S_list::insert_before(e, S_list::iter(*pos));
  else
    {
      S_list::self_insert(e);
      insert_before(e, pos);
    }
}

#line 137 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"

/**
 * Dequeue a given element from the list.
 * @param e the element to dequeue
 */

inline void
Prio_list::dequeue(Prio_list_elem *e, Prio_list_elem **next)
{
  if (P_list::in_list(e))
    {
      assert (S_list::in_list(e));
      // yes we are the head of our priority
      if (S_list::has_sibling(e))
	{
	  P_list::replace(e, *++S_list::iter(e));
	  if (next) *next = *++S_list::iter(e);
	}
      else
	{
	  if (next) *next = *++P_list::iter(e);
	  P_list::remove(e);
	}
    }
  else
    {
      if (next)
	{
	  if (P_list::in_list(*++S_list::iter(e))) // actually we are the last on our priority
	    *next = *++P_list::iter(e);
	  else
	    *next = *++S_list::iter(e);
	}
    }
  S_list::remove(e);
}

#line 173 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"


inline Iteratable_prio_list::Iteratable_prio_list() : _cursor(0), _lock(Spin_lock<>::Unlocked) {}

#line 176 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"

/**
 * Dequeue a given element from the list.
 * @param e the element to dequeue
 */

inline void
Iteratable_prio_list::dequeue(Prio_list_elem *e)
{
  Prio_list_elem **c = 0;
  if (EXPECT_FALSE(_cursor != 0) && EXPECT_FALSE(_cursor == e))
    c = &_cursor;

  Prio_list::dequeue(e, c);
}

#line 191 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"


inline void
Iteratable_prio_list::cursor(Prio_list_elem *e)
{ _cursor = e; }

#line 196 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"


inline Prio_list_elem *
Iteratable_prio_list::cursor() const
{ return _cursor; }

#line 86 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"

/**
 * Get the priority.
 */

inline unsigned short
Prio_list_elem::prio() const
{ return _prio; }

#line 130 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/prio_list.cpp"

/**
 * Is the element actually enqueued?
 * @return true if the element is actaully enqueued in a list.
 */

inline bool Prio_list_elem::in_list() const { return S_list::in_list(this); }

#endif // prio_list_h
