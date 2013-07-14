// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef console_h
#define console_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/console.cpp"

#include <cstddef>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/console.cpp"
#include "l4_types.h"

//
// INTERFACE definition follows 
//

#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/console.cpp"

/**
 * The abstract interface for a text I/O console.
 *
 * This abstract interface can be implemented for virtually every
 * text input or output device.
 */
class Console
{
public:
  enum Console_state
  {
    DISABLED    =     0,
    INENABLED   =     1, ///< output channel of console enabled
    OUTENABLED  =     2, ///< input channel of console enabled
    DISABLED_INIT =   4, ///< the console remains disabled during boot
  };

  enum Console_attr
  {
    // universal attributes
    INVALID     =     0,
    OUT         =   0x1, ///< output to console is possible
    IN          =   0x2, ///< input from console is possible
    // attributes to identify a specific console
    DIRECT      =   0x4, ///< output to screen or input from keyboard
    UART        =   0x8, ///< output to/input from serial serial line
    UX          =  0x10, ///< filtered input console for UX
    PUSH        =  0x20, ///< input console
    GZIP        =  0x40, ///< gzip+uuencode output and sent to uart console
    BUFFER      =  0x80, ///< ring buffer
    DEBUG       = 0x100, ///< kdb interface
    FAILED      = 0x200, ///< initialization failed
  };

  /**
   * modify console state
   */
  virtual void state(Mword new_state);

  /**
   * Write a string of len chacters to the output.
   * @param str the string to write (no zero termination is needed)
   * @param len the number of chacters to write.
   *
   * This method must be implemented in every implementation, but
   * can simply do nothing for input only consoles.
   */
  virtual int write(char const *str, size_t len);

  /**
   * read a charcater from the input.
   * @param blocking if true getchar blocks til a charcater is available.
   *
   * This method must be implemented in every implementation, but
   * can simply return -1 for output only consoles.
   */
  virtual int getchar(bool blocking = true);

  /**
   * Is input available?
   *
   * This method can be implemented.
   * It must return -1 if no information is available, 
   * 1 if at least one character is avialable, and 0 if
   * no charachter is available.
   */
  virtual int char_avail() const;

  /**
   * Console attributes.
   */
  virtual Mword get_attributes() const;

  virtual ~Console();

public:
  /**
   * Disables the stdout, stdin, and stderr console.
   */
  static void disable_all();

  /// stdout for libc glue.
  static Console *stdout;
  /// stderr for libc glue.
  static Console *stderr;
  /// stdin for libc glue.
  static Console *stdin;

protected:
  Mword  _state;

public:  
#line 112 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/console.cpp"
  /**
   * get current console state
   */
  
  inline Mword
  state() const;
  
#line 129 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/console.cpp"
  inline bool
  failed() const;
  
#line 136 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/console.cpp"
  inline void
  fail();
  
#line 177 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/console.cpp"
  const char*
  str_mode() const;
  
#line 186 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/console.cpp"
  const char*
  str_state() const;
  
#line 196 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/console.cpp"
  const char*
  str_attr(Mword bit) const;
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 111 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/console.cpp"

/**
 * get current console state
 */

inline Mword
Console::state() const
{
  return _state;
}

#line 127 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/console.cpp"


inline bool
Console::failed() const
{
  return _state & FAILED;
}

#line 134 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/console.cpp"


inline void
Console::fail()
{
  _state |= FAILED;
}

#endif // console_h
