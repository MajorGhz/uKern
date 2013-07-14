// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef vga_console_i_h
#define vga_console_i_h
#line 109 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/vga_console.cpp"

#include <cstring>
#line 111 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/vga_console.cpp"
#include <cctype>
#line 112 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/vga_console.cpp"

#include "io.h"
#line 114 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/vga_console.cpp"
#include "mem_layout.h"

//
// IMPLEMENTATION of inline functions follows
//


#line 200 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/vga_console.cpp"




inline int Vga_console::seq_6( char const *str, size_t len, unsigned &pos )
{
  if( pos+2 >= len ) return 0;
  _y = str[pos+1];
  _x = str[pos+2];
  if( _y >= _height ) _y = _height -1;
  if( _x >= _width  ) _x = _width -1;
  pos += 2;
  return 1;
}

#line 214 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/vga_console.cpp"


inline int Vga_console::seq_1( char const *, size_t, unsigned & )
{
  _x = 0; _y = 0; return 1;
}

#line 220 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/vga_console.cpp"


inline int Vga_console::seq_5( char const *, size_t , unsigned & )
{
  for( unsigned i = 0; i<_width-_x; ++i)
    set(_x+(_y*_width)+i, 0x20, _attribute);

  return 1;
}

#line 229 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/vga_console.cpp"



inline void Vga_console::ansi_attrib( int a )
{
  char const colors[] = { 0, 4, 2, 6, 1, 5, 3, 7 };

  if(!_use_color && a>=30 && a <=47)
    return;

  switch(a) {
  case 0:
    if(_light_white)
      _attribute = 0x0f;
    else
      _attribute = 0x07;
    break;
  case 1:
    _attribute |= 0x0808;
    break;
  case 22:
    _attribute &= ~0x0808;
    break;
  case 5:
    _attribute |= 0x8080;
  default:
    if (30 <= a && a <= 37) 
      _attribute = (_attribute & 0x0f0) | colors[a-30] | ((_attribute >> 8) & 0x08);
    else if (40 <= a && a <= 47)
      _attribute = (_attribute & 0x0f) | (colors[a-40] << 4) | ((_attribute >> 8) & 0x80);
    break;
  };

}

#endif // vga_console_i_h
