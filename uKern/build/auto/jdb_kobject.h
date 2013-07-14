// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_kobject_h
#define jdb_kobject_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"

#include "jdb_module.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
#include "jdb_list.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
#include "kobject.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
#include <cxx/slist>

//
// INTERFACE definition follows 
//

#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"

class Kobject;
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
class Jdb_kobject_handler;
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"

class Jdb_kobject : public Jdb_module
{
public:
  typedef cxx::S_list_tail<Jdb_kobject_handler> Handler_list;
  typedef Handler_list::Const_iterator Handler_iter;

  Jdb_kobject();

  Handler_list handlers;
  Handler_list global_handlers;

private:
  static void *kobjp;

public:  
#line 353 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  void
  register_handler(Jdb_kobject_handler *h);
  
#line 363 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  Jdb_kobject_handler *
  find_handler(Kobject_common *o);
  
#line 374 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  bool
  handle_obj(Kobject *o, int lvl);
  
#line 384 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  static char const *
  kobject_type(Kobject_common *o);
  
#line 395 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  static int
  obj_description(char *buffer, int max, bool dense, Kobject_dbg *o);
  
#line 420 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&, char const *&, int &);
  
#line 448 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 461 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  int
  num_cmds() const;
  
#line 528 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  static void
  init();
  
#line 542 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  static Jdb_kobject *
  module();
  
#line 549 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  // Be robust if this object is invalid
  
  static void
  print_uid(Kobject_common *o, int task_format = 0);

private:  
#line 413 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  static void
  print_kobj(Kobject *o);
  
#line 468 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  static int
  fmt_handler(char /*fmt*/, int *size, char const *cmd_str, void *arg);
};
#line 25 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"


class Jdb_kobject_handler : public cxx::S_list_item
{
  friend class Jdb_kobject;

public:
  Jdb_kobject_handler(char const *type) : kobj_type(type) {}
  char const *kobj_type;
  virtual bool show_kobject(Kobject_common *o, int level) = 0;
  virtual int show_kobject_short(char *, int, Kobject_common *) { return 0; }
  virtual Kobject_common *follow_link(Kobject_common *o) { return o; }
  virtual ~Jdb_kobject_handler() {}
  virtual bool invoke(Kobject_common *o, Syscall_frame *f, Utcb *utcb);
  virtual bool handle_key(Kobject_common *, int /*keycode*/) { return false; }
  virtual Kobject *parent(Kobject_common *) { return 0; }
  virtual char const *kobject_type() const { return kobj_type; }

  bool is_global() const { return !kobj_type; }

protected:
  enum {
    Op_set_name         = 0,
    Op_global_id        = 1,
    Op_kobj_to_id       = 2,
    Op_query_log_typeid = 3,
    Op_switch_log       = 4,
    Op_get_name         = 5,
    Op_query_log_name   = 6,
  };
};
#line 56 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"

class Jdb_kobject_extension : public Kobject_dbg::Dbg_extension
{
public:
  virtual ~Jdb_kobject_extension() {}
  virtual char const *type() const = 0;

public:  
#line 597 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  template< typename T > static T *
  find_extension(Kobject_common const *o);
};
#line 63 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"

class Jdb_kobject_list : public Jdb_list
{
public:
  typedef bool Filter_func(Kobject_common const *);

  struct Mode : cxx::S_list_item
  {
    char const *name;
    Filter_func *filter;
    typedef cxx::S_list_bss<Mode> Mode_list;
    static Mode_list modes;

    Mode(char const *name, Filter_func *filter)
    : name(name), filter(filter)
    {
      // make sure that non-filtered mode is first in the list so that we
      // get this one displayed initially
      if (!filter)
        modes.push_front(this);
      else
        {
          Mode_list::Iterator i = modes.begin();
          if (i != modes.end())
            ++i;
          modes.insert_before(this, i);
        }
    }
  };

  void *get_head() const
  { return Kobject::from_dbg(Kobject_dbg::begin()); }

private:
  Mode::Mode_list::Const_iterator _current_mode;
  Filter_func *_filter;

public:  
#line 160 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  explicit Jdb_kobject_list(Filter_func *filt);
  
#line 165 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  Jdb_kobject_list();
  
#line 175 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  int
  show_item(char *buffer, int max, void *item) const;
  
#line 182 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  bool
  enter_item(void *item) const;
  
#line 190 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  void *
  follow_link(void *item);
  
#line 201 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  bool
  handle_key(void *item, int keycode);
  
#line 255 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  int
  seek(int cnt, void **item);
  
#line 293 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  char const *
  show_head() const;
  
#line 301 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  char const *
  get_mode_str() const;
  
#line 312 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  void
  next_mode();
  
#line 325 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  /* When the mode changes the current object may get invisible,
   * get a new visible one */
  
  void *
  get_valid(void *o);

private:  
#line 150 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  void *
  get_first();
  
#line 217 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  inline Kobject *
  next(Kobject *obj);
  
#line 236 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  inline Kobject *
  prev(Kobject *obj);
};

#line 571 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
extern "C" void
sys_invoke_debug(Kobject_iface *o, Syscall_frame *f);

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 103 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"

#include <climits>
#line 105 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
#include <cstring>
#line 106 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
#include <cstdio>
#line 107 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
#include <cstdlib>
#line 108 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"

#include "entry_frame.h"
#line 110 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
#include "jdb.h"
#line 111 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
#include "jdb_core.h"
#line 112 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
#include "jdb_module.h"
#line 113 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
#include "jdb_screen.h"
#line 114 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
#include "kernel_console.h"
#line 115 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
#include "kobject.h"
#line 116 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
#include "keycodes.h"
#line 117 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
#include "ram_quota.h"
#line 118 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
#include "simpleio.h"
#line 119 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
#include "space.h"
#line 120 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
#include "static_init.h"

//
// IMPLEMENTATION of function templates
//


#line 593 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"




template< typename T > T *
Jdb_kobject_extension::find_extension(Kobject_common const *o)
{
  typedef Kobject_dbg::Dbg_ext_list::Iterator Iterator;
  for (Iterator ex = o->dbg_info()->_jdb_data.begin();
       ex != o->dbg_info()->_jdb_data.end(); ++ex)
    {
      Jdb_kobject_extension *je = static_cast<Jdb_kobject_extension*>(*ex);
      if (je->type() == T::static_type)
	return static_cast<T*>(je);
    }

  return 0;
}

#endif // jdb_kobject_h
