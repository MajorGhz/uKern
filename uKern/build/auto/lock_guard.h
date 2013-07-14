// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef lock_guard_h
#define lock_guard_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"
#include <cxx/type_traits>

//
// INTERFACE definition follows 
//

#line 3 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"

//
// Regular lock-guard policy, lock on ctor, unlock/reset in dtor
//
template< typename LOCK >
struct Lock_guard_regular_policy
{
  typedef typename LOCK::Status Status;
  static Status test_and_set(LOCK *l) { return l->test_and_set(); }
  static void set(LOCK *l, Status s) { l->set(s); }
};
#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"

//
// Inverse lock-guard policy, unlock in ctor, lock in dtor
// NOTE: this is applicable only to some locks (e.g., the cpu lock)
//
template<typename LOCK>
struct Lock_guard_inverse_policy : private LOCK
{
  typedef typename LOCK::Status Status;
  static Status test_and_set(LOCK *l) { l->clear(); return LOCK::Locked; }
  static void set(LOCK *l, Status s) { l->set(s); }
};
#line 26 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"


//
// Lock_guard: a guard object using a lock such as helping_lock_t
//
template<
  typename LOCK,
  template< typename L > class POLICY = Lock_guard_regular_policy >
class Lock_guard
{
  typedef typename cxx::remove_pointer<typename cxx::remove_reference<LOCK>::type>::type Lock;
  typedef POLICY<Lock> Policy;

  Lock *_lock;
  typename Policy::Status _state;

  Lock_guard(Lock_guard &) = delete;
  Lock_guard &operator = (Lock_guard &) = delete;

public:  
#line 58 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"
  inline Lock_guard();
  
#line 64 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"
  explicit inline Lock_guard(Lock *l);
  
#line 72 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"
  inline Lock_guard(Lock_guard &&l);
  
#line 80 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"
  inline Lock_guard<LOCK, POLICY>
  operator=(Lock_guard &&l);
  
#line 100 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"
  inline void
  lock(Lock *l);
  
#line 109 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"
  inline bool
  check_and_lock(Lock *l);
  
#line 119 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"
  inline bool
  try_lock(Lock *l);
  
#line 137 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"
  inline void
  release();
  
#line 145 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"
  inline void
  reset();
  
#line 157 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"
  inline ~Lock_guard();
  
#line 165 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"
  inline bool
  was_set(void);
};
#line 45 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"

template< typename LOCK>
class Lock_guard_2
{
  LOCK *_l1, *_l2;
  typename LOCK::Status _state1, _state2;

public:  
#line 173 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"
  inline Lock_guard_2();
  
#line 179 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"
  inline Lock_guard_2(LOCK *l1, LOCK *l2);
  
#line 192 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"
  inline void
  lock(LOCK *l1, LOCK *l2);
  
#line 206 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"
  inline bool
  check_and_lock(LOCK *l1, LOCK *l2);
  
#line 230 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"
  inline ~Lock_guard_2();
};

#line 91 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"
template<typename LOCK> inline Lock_guard<LOCK> lock_guard(LOCK &lock);

#line 95 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"
template<typename LOCK> inline Lock_guard<LOCK> lock_guard(LOCK *lock);

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 54 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"




template<typename LOCK, template< typename L > class POLICY> inline Lock_guard<LOCK, POLICY>::Lock_guard()
  : _lock(0)
{}

#line 61 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"



template<typename LOCK, template< typename L > class POLICY> inline Lock_guard<LOCK, POLICY>::Lock_guard(Lock *l)
  : _lock(l)
{
  _state = Policy::test_and_set(_lock);
}

#line 69 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"



template<typename LOCK, template< typename L > class POLICY> inline Lock_guard<LOCK, POLICY>::Lock_guard(Lock_guard &&l)
  : _lock(l._lock), _state(l._state)
{
  l.release();
}

#line 77 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"



template<typename LOCK, template< typename L > class POLICY> inline Lock_guard<LOCK, POLICY>
Lock_guard<LOCK, POLICY>::operator=(Lock_guard &&l)
{
  reset();
  _lock = l._lock;
  _state = l._state;
  l.release();
}

#line 97 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"



template<typename LOCK, template< typename L > class POLICY> inline void
Lock_guard<LOCK, POLICY>::lock(Lock *l)
{
  _lock = l;
  _state = Policy::test_and_set(l);
}

#line 106 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"



template<typename LOCK, template< typename L > class POLICY> inline bool
Lock_guard<LOCK, POLICY>::check_and_lock(Lock *l)
{
  _lock = l;
  _state = Policy::test_and_set(l);
  return _state != Lock::Invalid;
}

#line 116 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"



template<typename LOCK, template< typename L > class POLICY> inline bool
Lock_guard<LOCK, POLICY>::try_lock(Lock *l)
{
  _state = Policy::test_and_set(l);
  switch (_state)
    {
    case Lock::Locked:
      return true;
    case Lock::Not_locked:
      _lock = l;			// Was not locked -- unlock.
      return true;
    default:
      return false; // Error case -- lock not existent
    }
}

#line 134 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"



template<typename LOCK, template< typename L > class POLICY> inline void
Lock_guard<LOCK, POLICY>::release()
{
  _lock = 0;
}

#line 142 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"



template<typename LOCK, template< typename L > class POLICY> inline void
Lock_guard<LOCK, POLICY>::reset()
{
  if (_lock)
    {
      Policy::set(_lock, _state);
      _lock = 0;
    }
}

#line 154 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"



template<typename LOCK, template< typename L > class POLICY> inline Lock_guard<LOCK, POLICY>::~Lock_guard()
{
  if (_lock)
    Policy::set(_lock, _state);
}

#line 162 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"



template<typename LOCK, template< typename L > class POLICY> inline bool
Lock_guard<LOCK, POLICY>::was_set(void)
{
  return _state; //!_lock;
}

#line 170 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"



template<typename LOCK> inline Lock_guard_2<LOCK>::Lock_guard_2()
  : _l1(0), _l2(0)
{}

#line 176 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"



template<typename LOCK> inline Lock_guard_2<LOCK>::Lock_guard_2(LOCK *l1, LOCK *l2)
  : _l1(l1 < l2 ? l1 : l2), _l2(l1 < l2 ? l2 : l1)
{
  _state1 = _l1->test_and_set();
  if (_l1 == _l2)
    _l2 = 0;
  else
    _state2 = _l2->test_and_set();
}

#line 188 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"




template<typename LOCK> inline void
Lock_guard_2<LOCK>::lock(LOCK *l1, LOCK *l2)
{
  _l1 = l1 < l2 ? l1 : l2;
  _l2 = l1 < l2 ? l2 : l1;
  _state1 = _l1->test_and_set();
  if (_l1 == _l2)
    _l2 = 0;
  else 
    _state2 = _l2->test_and_set();
}

#line 203 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"



template<typename LOCK> inline bool
Lock_guard_2<LOCK>::check_and_lock(LOCK *l1, LOCK *l2)
{
  _l1 = l1 < l2 ? l1 : l2;
  _l2 = l1 < l2 ? l2 : l1;
  if ((_state1 = _l1->test_and_set()) == LOCK::Invalid)
    {
      _l1 = _l2 = 0;
      return false;
    }

  if (_l1 == _l2)
    _l2 = 0;
  else if ((_state2 = _l2->test_and_set()) == LOCK::Invalid)
    {
      _l2 = 0;
      return false;
    }

  return true;
}

#line 227 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"



template<typename LOCK> inline Lock_guard_2<LOCK>::~Lock_guard_2()
{
  if (_l2)
    _l2->set(_state2);

  if (_l1)
    _l1->set(_state1);
}

#line 88 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"



template<typename LOCK> inline Lock_guard<LOCK> lock_guard(LOCK &lock)
{ return Lock_guard<LOCK>(&lock); }

#line 93 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/lock_guard.cpp"


template<typename LOCK> inline Lock_guard<LOCK> lock_guard(LOCK *lock)
{ return Lock_guard<LOCK>(lock); }

#endif // lock_guard_h
