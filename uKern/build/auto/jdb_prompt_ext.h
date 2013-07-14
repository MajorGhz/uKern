// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_prompt_ext_h
#define jdb_prompt_ext_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_ext.cpp"

#include <cxx/hlist>

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_ext.cpp"

class Jdb_prompt_ext : public cxx::H_list_item
{
public:
  Jdb_prompt_ext();
  virtual void ext() = 0;
  virtual void update();
  virtual ~Jdb_prompt_ext() = 0;

  static void do_all();
  static void update_all();

private:
  typedef cxx::H_list_bss<Jdb_prompt_ext> List;
  typedef List::Const_iterator Iter;
  static List exts;
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 31 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_prompt_ext.cpp"

inline Jdb_prompt_ext::~Jdb_prompt_ext() {}

#endif // jdb_prompt_ext_h
