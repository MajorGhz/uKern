// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_list_h
#define jdb_list_h

//
// INTERFACE definition follows 
//

#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"

class Jdb_list
{
public:
  virtual char const *get_mode_str() const { return "[std mode]"; }
  virtual void next_mode() {}
  virtual void next_sort() {}
  virtual void *get_head() const = 0;
  virtual int show_item(char *buffer, int max, void *item) const = 0;
  virtual char const *show_head() const = 0;
  virtual int seek(int cnt, void **item) = 0;
  virtual bool enter_item(void * /*item*/) const { return true; }
  virtual void *follow_link(void *a) { return a; }
  virtual bool handle_key(void * /*item*/, int /*keycode*/) { return false; }
  virtual void *parent(void * /*item*/) { return 0; }
  virtual void *get_valid(void *a) { return a; }

private:
  void *_start, *_last;
  void *_current;


public:  
#line 44 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  Jdb_list();
  
#line 48 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  // set _t_start element of list
  
  void
  set_start(void *start);
  
#line 56 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  // _t_start-- if possible
  
  inline bool
  line_back();
  
#line 62 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  // _t_start++ if possible
  
  inline bool
  line_forw();
  
#line 80 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  // _t_start -= 24 if possible
  
  bool
  page_back();
  
#line 86 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  // _t_start += 24 if possible
  
  bool
  page_forw();
  
#line 105 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  // _t_start = first element of list
  
  bool
  goto_home();
  
#line 111 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  // _t_start = last element of list
  
  bool
  goto_end();
  
#line 124 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  // search index of t_search starting from _t_start
  
  int
  lookup_in_visible_area(void *search);
  
#line 143 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  // get y'th element of thread list starting from _t_start
  
  void *
  index(int y);
  
#line 156 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  void
  show_line(void *i);
  
#line 174 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  // show complete page using show callback function
  
  int
  page_show();
  
#line 197 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  // show complete list using show callback function
  
  int
  complete_show();
  
#line 276 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  void
  show_header();
  
#line 285 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  void
  do_list();
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 55 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"

// _t_start-- if possible

inline bool
Jdb_list::line_back()
{ return seek(-1, &_start); }

#line 61 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_list.cpp"

// _t_start++ if possible

inline bool
Jdb_list::line_forw()
{
  if (seek(1, &_last))
    return seek(1, &_start);
  else
    return false;
}

#endif // jdb_list_h
