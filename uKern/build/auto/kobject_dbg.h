// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kobject_dbg_h
#define kobject_dbg_h
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_dbg.cpp"

#include "spin_lock.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_dbg.cpp"
#include "lock_guard.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_dbg.cpp"
#include <cxx/dlist>
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_dbg.cpp"
#include <cxx/hlist>

//
// INTERFACE definition follows 
//

#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_dbg.cpp"

class Kobject;
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_dbg.cpp"

class Kobject_dbg

: public cxx::D_list_item
{

#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_dbg.cpp"
private:

  friend class Jdb_kobject;
  friend class Jdb_kobject_list;
  friend class Jdb_mapdb;

public:
  class Dbg_extension : public cxx::H_list_item
  {
  public:
    virtual ~Dbg_extension() = 0;
  };

public:
  typedef cxx::H_list<Dbg_extension> Dbg_ext_list;
  Dbg_ext_list _jdb_data;

private:
  Mword _dbg_id;

public:
  Mword dbg_id() const { return _dbg_id; }
  virtual Address kobject_start_addr() const = 0;
  virtual Mword kobject_size() const = 0;
  virtual ~Kobject_dbg() = 0;


  typedef cxx::D_list<Kobject_dbg> Kobject_list;
  typedef Kobject_list::Iterator Iterator;
  typedef Kobject_list::Const_iterator Const_iterator;

  static Spin_lock<> _kobjects_lock;
  static Kobject_list _kobjects;

  static Iterator begin() { return _kobjects.begin(); }
  static Iterator end() { return _kobjects.end(); }

private:
  static unsigned long _next_dbg_id;

public:  
#line 69 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_dbg.cpp"
  static Kobject_dbg::Iterator
  pointer_to_obj(void const *p);
  
#line 82 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_dbg.cpp"
  static unsigned long
  pointer_to_id(void const *p);
  
#line 92 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_dbg.cpp"
  static bool
  is_kobj(void const *o);
  
#line 99 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_dbg.cpp"
  static Kobject_dbg::Iterator
  id_to_obj(unsigned long id);
  
#line 111 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_dbg.cpp"
  static unsigned long
  obj_to_id(void const *o);

protected:  
#line 119 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_dbg.cpp"
  Kobject_dbg();
};
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_dbg.cpp"

//----------------------------------------------------------------------------

#line 65 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_dbg.cpp"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 126 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_dbg.cpp"


inline Kobject_dbg::~Kobject_dbg()
{
    {
      auto guard = lock_guard(_kobjects_lock);
      _kobjects.remove(this);
    }

  while (Dbg_extension *ex = _jdb_data.front())
    delete ex;
}

#line 65 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kobject_dbg.cpp"

inline Kobject_dbg::Dbg_extension::~Dbg_extension() {}

#endif // kobject_dbg_h
