// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef ref_obj_h
#define ref_obj_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ref_obj.cpp"

#include "types.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ref_obj.cpp"

class Ref_cnt_obj
{
public:
  Ref_cnt_obj() : _ref_cnt(0) {}
private:
  Smword _ref_cnt;

public:  
#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ref_obj.cpp"
  inline Smword
  ref_cnt() const;
  
#line 25 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ref_obj.cpp"
  inline bool
  inc_ref(bool from_zero = true);
  
#line 40 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ref_obj.cpp"
  inline Smword
  dec_ref();
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ref_obj.cpp"

#include "atomic.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ref_obj.cpp"


inline Smword
Ref_cnt_obj::ref_cnt() const
{ return _ref_cnt; }

#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ref_obj.cpp"


inline bool
Ref_cnt_obj::inc_ref(bool from_zero)
{
  Smword old;
  do
    {
      old = _ref_cnt;
      if (!from_zero && !old)
        return false;
    }
  while (!mp_cas(&_ref_cnt, old, old + 1));
  return true;
}

#line 38 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ref_obj.cpp"


inline Smword
Ref_cnt_obj::dec_ref()
{
  Smword old;
  do
    old = _ref_cnt;
  while (!mp_cas(&_ref_cnt, old, old - 1));

  return old - 1;
}

#endif // ref_obj_h
