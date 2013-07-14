// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_attach_irq_i_h
#define jdb_attach_irq_i_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"

#include <cstdio>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"

#include "irq_chip.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
#include "irq.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
#include "irq_mgr.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
#include "jdb_module.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
#include "kernel_console.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
#include "static_init.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
#include "thread.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
#include "types.h"
#line 92 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"

#include "jdb_kobject.h"
#line 94 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
#include "irq.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"


//===================
// Std JDB modules
//===================

/**
 * 'IRQ' module.
 *
 * This module handles the 'R' command that
 * provides IRQ attachment and listing functions.
 */
class Jdb_attach_irq : public Jdb_module
{
public:
  Jdb_attach_irq() FIASCO_INIT;
private:
  static char     subcmd;

public:  
#line 42 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
  Jdb_module::Action_code
  action( int cmd, void *&args, char const *&, int & );
  
#line 72 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
  int
  num_cmds() const;
  
#line 79 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
  Jdb_module::Cmd const *
  cmds() const;
};
#line 95 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"

class Jdb_kobject_irq : public Jdb_kobject_handler
{

public:  
#line 119 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
  static Irq_sender *
  dcast_h(Irq_sender *i);
  
#line 126 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
  static Irq_muxer *
  dcast_h(Irq_muxer *i);
  
#line 134 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
  template<typename T> static T
  dcast(Kobject_common *o);
  
#line 145 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
  inline Jdb_kobject_irq();
  
#line 152 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
  char const *
  kobject_type() const;
  
#line 160 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
  bool
  handle_key(Kobject_common *o, int key);
  
#line 170 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
  Kobject_common *
  follow_link(Kobject_common *o);
  
#line 179 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
  bool
  show_kobject(Kobject_common *, int);
  
#line 184 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
  int
  show_kobject_short(char *buf, int max, Kobject_common *o);
};

//
// IMPLEMENTATION of inline functions follows
//


#line 143 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"


inline Jdb_kobject_irq::Jdb_kobject_irq()
  : Jdb_kobject_handler(Irq::static_kobj_type)
{
  Jdb_kobject::module()->register_handler(this);
}

//
// IMPLEMENTATION of function templates
//


#line 131 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"



template<typename T> T
Jdb_kobject_irq::dcast(Kobject_common *o)
{
  Irq *i = Kobject::dcast<Irq*>(o);
  if (!i)
    return 0;

  return dcast_h(static_cast<T>(i));
}

#endif // jdb_attach_irq_i_h
