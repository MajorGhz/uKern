// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_kobject_names_h
#define jdb_kobject_names_h
#line 3 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"

#include "config.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
#include "jdb_kobject.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
#include "l4_types.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
#include "initcalls.h"

//
// INTERFACE definition follows 
//

#line 1 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
//-----------------------------------------------------------------------

#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"


class Jdb_kobject_name : public Jdb_kobject_extension
{
public:
  static char const *const static_type;
  virtual char const *type() const { return static_type; }

  ~Jdb_kobject_name() {}

  void *operator new (size_t) throw();
  void operator delete (void *);

private:

  char _name[16];

  static Jdb_kobject_name *_names;

public:  
#line 56 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
  unsigned
  max_len();
  
#line 61 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
  void
  name(char const *name);
  
#line 68 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
  Jdb_kobject_name();
  
#line 108 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
  void
  clear_name();
  
#line 116 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
  inline char const *
  name() const;
  
#line 121 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
  inline char *
  name();
  
#line 195 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
  static FIASCO_INIT
  void
  init();
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 114 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"


inline char const *
Jdb_kobject_name::name() const
{ return _name; }

#line 119 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"


inline char *
Jdb_kobject_name::name()
{ return _name; }

#endif // jdb_kobject_names_h
