// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef mappable_h
#define mappable_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mappable.cpp"

#include "mapping_tree.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mappable.cpp"

class Mappable : public Base_mappable
{
public:
  bool no_mappings() const;
  virtual ~Mappable() = 0;
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mappable.cpp"

inline Mappable::~Mappable() {}

#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mappable.cpp"


inline bool
Mappable::no_mappings() const
{
  return !tree.get() || tree.get()->is_empty();
}

#endif // mappable_h
