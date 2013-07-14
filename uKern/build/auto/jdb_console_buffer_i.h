// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_console_buffer_i_h
#define jdb_console_buffer_i_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"

#include <cstdio>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"
#include <cstring>
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"
#include <cstdlib>
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"

#include "config.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"
#include "jdb_module.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"
#include "jdb.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"
#include "kernel_console.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"
#include "keycodes.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"
#include "kmem_alloc.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"
#include "koptions.h"
#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"
#include "static_init.h"
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"

/**
 * A output console that stores the output in a buffer.
 *
 * This buffer can be useful for accessing older the debugging
 * output without a serial console.
 */
class Console_buffer : public Console
{
private:
  static bool _enabled;
  static size_t out_buf_size;
  static size_t out_buf_len;
  static char *out_buf;
  static char *out_buf_w;

public:  
#line 53 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"
  Console_buffer();
  
#line 69 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"
  /**
   * Allocates a buffer of the given size.
   * @param size the buffer size in bytes.
   */
  
  static void
  alloc(size_t size);
  
#line 91 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"
  ~Console_buffer();
  
#line 100 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"
  int
  write( char const *str, size_t len );
  
#line 142 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"
  int
  getchar(bool);
  
#line 148 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"
  /**
   * Prints the buffer to the standard I/O.
   * @param lines the number of lines to skip.
   * This method prints the buffer contents to the normal I/O.
   * Before doing this the buffer is disabled, that no recursion 
   * appers even if the buffer is part of the muxed I/O.
   */
  
  static int
  print_buffer(unsigned lines);
  
#line 246 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"
  /**
   * Prints the buffer to the standard I/O.
   * @param str the string the output should be filtered for
   * This method prints the buffer contents to the normal I/O.
   * Before doing this the buffer is disabled, that no recursion
   * appers even if the buffer is part of the muxed I/O.
   */
  
  static int
  print_buffer(const char *str);
  
#line 333 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"
  Mword get_attributes() const;
  
#line 339 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"
  static FIASCO_INIT
  void
  init();

private:  
#line 39 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"
  static void
  at_jdb_enter();
  
#line 46 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"
  static void
  at_jdb_leave();
  
#line 126 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"
  static inline void
  inc_ptr(char **c);
  
#line 134 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"
  static inline void
  dec_out_ptr(char **c);
  
#line 233 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"
  static int
  strncmp(char *start, const char *search, size_t len);
};
#line 348 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"



/// Jdb module

class Jdb_cb : public Jdb_module
{
public:
  Jdb_cb() FIASCO_INIT;
private:
  static char  first_char;
  static char  search_str[30];
  static Mword output_lines;

public:  
#line 368 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&args, char const *&fmt, int &next_char);
  
#line 406 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 419 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"
  int
  num_cmds() const;
};

//
// IMPLEMENTATION of inline functions follows
//


#line 124 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"


inline void
Console_buffer::inc_ptr(char **c)
{
  if (++*c >= out_buf + out_buf_size)
    *c = out_buf;
}

#line 132 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_console_buffer.cpp"


inline void
Console_buffer::dec_out_ptr(char **c)
{
  if (--*c < out_buf)
    *c += out_buf_size;
}

#endif // jdb_console_buffer_i_h
