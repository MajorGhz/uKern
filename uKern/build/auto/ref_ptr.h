// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef ref_ptr_h
#define ref_ptr_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ref_ptr.cpp"

#include "kdb_ke.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ref_ptr.cpp"
#include "context.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ref_ptr.cpp"
#include "cpu_lock.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ref_ptr.cpp"
#include "globals.h"

//
// INTERFACE definition follows 
//

#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ref_ptr.cpp"


template<typename T>
class Ref_ptr
{
public:
  Ref_ptr(T *o = 0) : _p(o)
  { __take_ref(); }

  T *ptr() const
  {
    // assert_kdb (cpu_lock.test());
    return _p;
  }

  ~Ref_ptr()
  { __drop_ref(); }

  Ref_ptr(Ref_ptr<T> const &o)
  {
    __drop_ref();
    _p = o._p;
    __take_ref();
  }

  void operator = (Ref_ptr<T> const &o)
  {
    __drop_ref();
    _p = o._p;
    __take_ref();
  }
  
  void operator = (T *o)
  {
    __drop_ref();
    _p = o;
    __take_ref();
  }

  T *operator -> () const { return _p; }

  struct Null_type;

  operator Null_type const * () const
  { return reinterpret_cast<Null_type const *>(_p); }

private:
  void __drop_ref()
  {
    if (_p && (_p->dec_ref() == 0))
      {
	current()->rcu_wait();
        delete _p;
      }
  }

  void __take_ref()
  {
    if (_p)
      _p->inc_ref();
  }

  T *_p;
};

#endif // ref_ptr_h
