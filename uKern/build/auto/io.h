// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef io_h
#define io_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/io.cpp"

#include "types.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/io.cpp"

/**
 * I/O API.
 */
class Io
{
public:

  /// Delay for slow I/O operations.
  static void iodelay();

  /**
   * Read the value of type T at address.
   */
  template< typename T >
  static T read(Address address);

  /**
   * Write the value of type T at address.
   */
  template< typename T >
  static void write(T value, Address address);

  /**
   * Write (read<T>(address) & maskbits) of type T at address.
   */
  template< typename T >
  static void mask(T mask, Address address);

  /**
   * Write (read<T>(address) & ~clearbits) of type T at address.
   */
  template< typename T >
  static void clear(T clearbits, Address address);

  /**
   * Write (read<T>(address) | setbits) of type T at address.
   */
  template< typename T >
  static void set(T setbits, Address address);

  /**
   * Write ((read<T>(address) & ~disable) | enable) of type T at address.
   */
  template< typename T >
  static void modify(T enable, T disable, Address address);

  /**
   * Read byte port.
   */
  static Unsigned8 in8(unsigned long port);

  /**
   * Read 16-bit port.
   */
  static Unsigned16 in16(unsigned long port);

  /**
   * Read 32-bit port.
   */
  static Unsigned32 in32(unsigned long port);

  /**
   * Write byte port.
   */
  static void out8(Unsigned8 val, unsigned long port);

  /**
   * Write 16-bit port.
   */
  static void out16(Unsigned16 val, unsigned long port);

  /**
   * Write 32-bit port.
   */
  static void out32(Unsigned32 val, unsigned long port);

  /// @name Delayed versions.
  //@{

  /**
   * Read 8-bit port.
   */
  static Unsigned8 in8_p(unsigned long port);

  /**
   * Read 16-bit port.
   */
  static Unsigned16 in16_p(unsigned long port);

  /**
   * Read 32-bit port.
   */
  static Unsigned32 in32_p(unsigned long port);

  /**
   * Write 8-bit port.
   */
  static void out8_p(Unsigned8 val, unsigned long port);

  /**
   * Write 16-bit port.
   */
  static void out16_p(Unsigned16 val, unsigned long port);

  /**
   * Write 32-bit port.
   */
  static void out32_p(Unsigned32 val, unsigned long port);
  //@}
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 118 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/io.cpp"



template< typename T > inline T Io::read(Address address)
{ return *(volatile T *)address; }

#line 123 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/io.cpp"



template< typename T> inline void Io::write(T value, Address address)
{ *(volatile T *)address = value; }

#line 131 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/io.cpp"



template< typename T> inline void Io::mask(T mask, Address address)
{ write<T>(read<T>(address) & mask, address); }

#line 136 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/io.cpp"



template< typename T> inline void Io::clear(T clearbits, Address address)
{ write<T>(read<T>(address) & ~clearbits, address); }

#line 141 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/io.cpp"



template< typename T> inline void Io::set(T setbits, Address address)
{ write<T>(read<T>(address) | setbits, address); }

#line 146 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/io.cpp"



template< typename T> inline void Io::modify(T enable, T disable, Address address)
{
  write<T>((read<T>(address) & ~disable) | enable, address);
}

#line 153 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/io.cpp"




inline Unsigned8 Io::in8_p(unsigned long port)
{
  Unsigned8 tmp = in8(port);
  iodelay();
  return tmp;
}

#line 163 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/io.cpp"


inline Unsigned16 Io::in16_p(unsigned long port)
{
  Unsigned16 tmp = in16(port);
  iodelay();
  return tmp;
}

#line 171 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/io.cpp"


inline Unsigned32 Io::in32_p(unsigned long port)
{
  Unsigned32 tmp = in32(port);
  iodelay();
  return tmp;
}

#line 179 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/io.cpp"


inline void Io::out8_p(Unsigned8 val, unsigned long port)
{
  out8(val, port);
  iodelay();
}

#line 186 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/io.cpp"


inline void Io::out16_p(Unsigned16 val, unsigned long port)
{
  out16(val, port);
  iodelay();
}

#line 193 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/io.cpp"


inline void Io::out32_p(Unsigned32 val, unsigned long port)
{
  out32(val, port);
  iodelay();
}

#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/ia32/io-ia32.cpp"


/* This is a more reliable delay than a few short jmps. */

inline void Io::iodelay() 
{
  asm("inb $0x80,%%al; inb $0x80,%%al" : : : "eax");
}

#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/ia32/io-ia32.cpp"


inline Unsigned8  Io::in8( unsigned long port )
{
  Unsigned8 tmp;
  asm volatile ("inb %w1, %b0": "=a"(tmp) : "Nd"(port) );
  return tmp;
}

#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/ia32/io-ia32.cpp"


inline Unsigned16 Io::in16( unsigned long port )
{
  Unsigned16 tmp;
  asm volatile ("inw %w1, %w0": "=a"(tmp) : "Nd"(port) );
  return tmp;
}

#line 26 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/ia32/io-ia32.cpp"


inline Unsigned32 Io::in32( unsigned long port )
{
  Unsigned32 tmp;
  asm volatile ("in %w1, %0": "=a"(tmp) : "Nd"(port) );
  return tmp;
}

#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/ia32/io-ia32.cpp"


inline void Io::out8( Unsigned8  val, unsigned long port )
{
  asm volatile ("outb %b0, %w1": : "a"(val), "Nd"(port) );
}

#line 40 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/ia32/io-ia32.cpp"


inline void Io::out16( Unsigned16 val, unsigned long port )
{
  asm volatile ("outw %w0, %w1": : "a"(val), "Nd"(port) );
}

#line 46 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/ia32/io-ia32.cpp"


inline void Io::out32( Unsigned32 val, unsigned long port )
{
  asm volatile ("out %0, %w1": : "a"(val), "Nd"(port) );
}

#endif // io_h
