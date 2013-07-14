// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_screen_h
#define jdb_screen_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_screen.cpp"

#include "types.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_screen.cpp"

class Jdb_screen
{
public:
  static const unsigned Mword_size_bmode = sizeof(Mword)*2;
  static const unsigned Mword_size_cmode = sizeof(Mword);
  static const unsigned Col_head_size = sizeof(Mword)*2;

  static const char *Mword_adapter;
  static const char *Mword_not_mapped;
  static const char *Mword_blank;

  static const char* const Reg_names[];
  static const char Reg_prefix;
  static const char *Line;

  static const char* Root_page_table;

private:
  static unsigned int _height;
  static unsigned int _width;
  static bool         _direct_enabled;

public:  
#line 41 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_screen.cpp"
  static void
  set_height(unsigned int h);
  
#line 46 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_screen.cpp"
  static void
  set_width(unsigned int w);
  
#line 51 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_screen.cpp"
  static inline unsigned int
  width();
  
#line 56 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_screen.cpp"
  static inline unsigned int
  height();
  
#line 61 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_screen.cpp"
  static inline unsigned long
  cols();
  
#line 66 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_screen.cpp"
  static inline unsigned long
  rows();
  
#line 71 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_screen.cpp"
  static inline void
  enable_direct(bool enable);
  
#line 76 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_screen.cpp"
  static inline bool
  direct_enabled();
  
#line 28 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_screen-ia32.cpp"
  static int
  num_regs();
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 49 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_screen.cpp"


inline unsigned int
Jdb_screen::width()
{ return _width; }

#line 54 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_screen.cpp"


inline unsigned int
Jdb_screen::height()
{ return _height; }

#line 59 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_screen.cpp"


inline unsigned long
Jdb_screen::cols()
{ return (width()-Col_head_size)/(Mword_size_bmode + 1) + 1; }

#line 64 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_screen.cpp"


inline unsigned long
Jdb_screen::rows()
{ return ((unsigned long)-1)/ ((cols()-1)*4) + 1; }

#line 69 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_screen.cpp"


inline void
Jdb_screen::enable_direct(bool enable)
{ _direct_enabled = enable; }

#line 74 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_screen.cpp"


inline bool
Jdb_screen::direct_enabled()
{ return _direct_enabled; }

#endif // jdb_screen_h
