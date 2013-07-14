// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef vga_console_h
#define vga_console_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/vga_console.cpp"

#include "types.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/vga_console.cpp"
#include "console.h"

//
// INTERFACE definition follows 
//

#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/vga_console.cpp"

/**
 * Console implementation for VGA.
 *
 * This console is a output only console for VGA.
 * It implements an ANSI ESC capable output device.
 */
class Vga_console : public Console
{
public:

  /**
   * Clear the screen,
   */
  void clear();

  /**
   * Scroll the screen n lines up.
   * @param n number of lines to scroll.
   */
  void scroll( unsigned n );

  /**
   * Get the base address for the VGA memory.
   * @return The base address of the VGA memory.
   */
  Address video_base() const;

  /**
   * Set the base address of the VGA memory.
   * @param base the base address of the VGA memory.
   */
  void video_base( Address base );

  /**
   * Create a new instance of a VGA console.
   * @param base the base address of the VGA memory.
   * @param width the width of the screen.
   * @param height the height of the screen.
   * @param light_white if set to true the color 
   *        grey is replaced with white.
   * @param use_color says whether ANSI ESC colors should be 
   *        passed (=true) to the video memory or not (=false).
   */
  Vga_console( Address base, unsigned width = 80, unsigned height = 25, 
	       bool light_white = false, bool use_color = false );

  /**
   * dtor.
   */
  ~Vga_console();

  /**
   * Output method.
   */
  int write( char const *str, size_t len );

  /**
   * Empty implementation.
   */
  int getchar( bool blocking = true );

  inline bool is_working();

  /**
   * Output a character.
   */
  inline void printchar(unsigned x, unsigned y, unsigned char c, unsigned char a);

private:

  /// Type of a on screen character.
  struct VChar {
    char c;
    char a;
  } __attribute__((packed));

  VChar   *_video_base;
  Address  _crtc;
  unsigned _width, _height;
  unsigned _x, _y;
  unsigned _attribute;
  enum {
    MAX_ANSI_ESC_ARGS = 5,
  };

  int ansi_esc_args[MAX_ANSI_ESC_ARGS];
  unsigned num_ansi_esc_args;

  void (Vga_console::*wr)(char const *, size_t, unsigned & );

  bool const _light_white;
  bool const _use_color;
  bool _is_working;

  /**
   * Set blinking screen cursor
   */
  void blink_cursor( unsigned x, unsigned y );

public:  
#line 484 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/vga_console.cpp"
  Mword get_attributes() const;

private:  
#line 155 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/vga_console.cpp"
  inline void set(unsigned i, char c, char a);
  
#line 204 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/vga_console.cpp"
  inline int seq_6( char const *str, size_t len, unsigned &pos );
  
#line 216 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/vga_console.cpp"
  inline int seq_1( char const *, size_t, unsigned & );
  
#line 222 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/vga_console.cpp"
  inline int seq_5( char const *, size_t , unsigned & );
  
#line 232 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/vga_console.cpp"
  inline void ansi_attrib( int a );
  
#line 267 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/vga_console.cpp"
  void esc_write( char const *str, size_t len, unsigned &i );
  
#line 283 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/vga_console.cpp"
  void ansi_esc_write( char const *str, size_t len, unsigned &i );
  
#line 378 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/vga_console.cpp"
  void normal_write( char const *str, size_t len, unsigned &i );
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 153 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/vga_console.cpp"


inline void Vga_console::set(unsigned i, char c, char a)
{
  _video_base[i].c = c;
  _video_base[i].a = a;
}

#line 176 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/vga_console.cpp"


inline void
Vga_console::printchar(unsigned x, unsigned y,
                       unsigned char c, unsigned char a)
{
  set(x + y * _width, c, a);
}

#line 475 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/vga_console.cpp"



inline bool Vga_console::is_working()
{
  return _is_working;
}

#endif // vga_console_h
