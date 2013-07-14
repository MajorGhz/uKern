// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_lines_h
#define jdb_lines_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_lines.cpp"

#include "l4_types.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_lines.cpp"
class Space;
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_lines.cpp"

class Jdb_lines_line
{
public:
  unsigned long  addr;
  unsigned short line;
} __attribute__((packed));
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_lines.cpp"

class Jdb_lines_info
{
private:
  Address  _virt;
  size_t   _size;
  Address  _beg_line;
  Address  _end_line;

public:  
#line 57 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_lines.cpp"
  inline Jdb_lines_line*
  lin();
  
#line 64 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_lines.cpp"
  inline const char*
  str();
  
#line 71 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_lines.cpp"
  inline void
  get(Address &virt, size_t &size);
  
#line 79 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_lines.cpp"
  inline void
  reset();
  
#line 86 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_lines.cpp"
  inline bool
  in_range(Address addr);
  
#line 92 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_lines.cpp"
  // register lines for a specific task (called by user mode application)
  
  bool
  set(Address virt, size_t size);
};
#line 21 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_lines.cpp"

class Jdb_lines
{
public:
  enum
  {
    // don't allow more than 2048 tasks to register their lines to save space
    Max_tasks = 2048,
  };

private:
  static Jdb_lines_info *_task_lines;

public:  
#line 46 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_lines.cpp"
  static void
  init(void *mem, Mword pages);
  
#line 123 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_lines.cpp"
  static Jdb_lines_info*
  lookup(Space * task);
  
#line 142 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_lines.cpp"
  // search line name that matches for a specific address
  
  static bool
  match_addr_to_line(Address addr, Space * task,
  			      char *line, unsigned line_size,
  			      int show_header_files);
  
#line 191 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_lines.cpp"
  // search line name that matches for a specific address
  
  static bool
  match_addr_to_line_fuzzy(Address *addr_ptr, Space * task,
  				    char *line, unsigned line_size,
  				    int show_header_files);

private:  
#line 252 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_lines.cpp"
  // truncate string if its length exceeds strsize and create line
  
  static void
  sprint_line(const char *dir, const char *fname, unsigned line,
  		       char *str, size_t strsize);
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 69 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_lines.cpp"


inline void
Jdb_lines_info::get(Address &virt, size_t &size)
{
  virt = _virt;
  size = _size;
}

#line 77 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_lines.cpp"


inline void
Jdb_lines_info::reset()
{
  _virt = 0;
}

#endif // jdb_lines_h
