// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef uart_h
#define uart_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart.cpp"

#include "console.h"
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"

#include "types.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart.cpp"

/**
 * Platform independent UART stub.
 */
class Uart : public Console
{
public:
  /**
   * Type UART transfer mode (Bits, Stopbits etc.).
   */
  typedef unsigned TransferMode;

  /**
   * Type for baud rate.
   */
  typedef unsigned BaudRate;

  /* These constants must be defined in the 
     arch part of the uart. To define them there
     has the advantage of most efficent definition
     for the hardware.

  static unsigned const PAR_NONE = xxx;
  static unsigned const PAR_EVEN = xxx;
  static unsigned const PAR_ODD  = xxx;
  static unsigned const DAT_5    = xxx;
  static unsigned const DAT_6    = xxx;
  static unsigned const DAT_7    = xxx;
  static unsigned const DAT_8    = xxx;
  static unsigned const STOP_1   = xxx;
  static unsigned const STOP_2   = xxx;

  static unsigned const MODE_8N1 = PAR_NONE | DAT_8 | STOP_1;
  static unsigned const MODE_7E1 = PAR_EVEN | DAT_7 | STOP_1;

  // these two values are to leave either mode
  // or baud rate unchanged on a call to change_mode
  static unsigned const MODE_NC  = xxx;
  static unsigned const BAUD_NC  = xxx;

  */


public:
  /* Interface definition - implemented in the arch part */
  /// ctor
  Uart();

  /// dtor
  ~Uart();

  /**
   * (abstract) Shutdown the serial port.
   */
  void shutdown();

  /**
   * (abstract) Get the IRQ assigned to the port.
   */
  int irq() const;

  Address base() const;

  /**
   * (abstract) Enable rcv IRQ in UART.
   */
  void enable_rcv_irq();

  /**
   * (abstract) Disable rcv IRQ in UART.
   */
  void disable_rcv_irq();

  /**
   * (abstract) Change transfer mode or speed.
   * @param m the new mode for the transfer, or MODE_NC for no mode change.
   * @param r the new baud rate, or BAUD_NC, for no speed change.
   */
  bool change_mode(TransferMode m, BaudRate r);

  /**
   * (abstract) Get the current transfer mode.
   */
  TransferMode get_mode();

  /**
   * (abstract) Write str.
   */
  int write( char const *str, size_t len );

  /**
   * (abstract) Read a character.
   */
  int getchar( bool blocking = true );

  /**
   * (abstract) Is there anything to read?
   */
  int char_avail() const;
  
  Mword get_attributes() const;

#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"
private:

public:
  enum {
    Base_rate     = 115200,
    Base_ier_bits = 0,

    Access_shift  = 0,
  };

#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"
private:

public:

  /**
   * Start this serial port for I/O.
   * @param port the I/O port base address.
   * @param irq the IRQ assigned to this port, -1 if none.
   */
  bool startup(Address port, int irq);

  enum {
    PAR_NONE = 0x00,
    PAR_EVEN = 0x18,
    PAR_ODD  = 0x08,
    DAT_5    = 0x00,
    DAT_6    = 0x01,
    DAT_7    = 0x02,
    DAT_8    = 0x03,
    STOP_1   = 0x00,
    STOP_2   = 0x04,

    MODE_8N1 = PAR_NONE | DAT_8 | STOP_1,
    MODE_7E1 = PAR_EVEN | DAT_7 | STOP_1,

  // these two values are to leave either mode
  // or baud rate unchanged on a call to change_mode
    MODE_NC  = 0x1000000,
    BAUD_NC  = 0x1000000,
  };

private:

  enum Registers {
    TRB      = 0, // Transmit/Receive Buffer  (read/write)
    BRD_LOW  = 0, // Baud Rate Divisor LSB if bit 7 of LCR is set  (read/write)
    IER      = 1, // Interrupt Enable Register  (read/write)
    BRD_HIGH = 1, // Baud Rate Divisor MSB if bit 7 of LCR is set  (read/write)
    IIR      = 2, // Interrupt Identification Register  (read only)
    FCR      = 2, // 16550 FIFO Control Register  (write only)
    LCR      = 3, // Line Control Register  (read/write)
    MCR      = 4, // Modem Control Register  (read/write)
    LSR      = 5, // Line Status Register  (read only)
    MSR      = 6, // Modem Status Register  (read only)
    SPR      = 7, // Scratch Pad Register  (read/write)
  };

  Address port;
  int _irq;

private:  
#line 90 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"
  inline void outb( Unsigned8 b, Registers reg );
  
#line 96 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"
  inline Unsigned8 inb( Registers reg ) const;
  
#line 103 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"
  inline void mcr(Unsigned8 b);
  
#line 109 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"
  inline Unsigned8 mcr() const;
  
#line 115 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"
  inline void fcr(Unsigned8 b);
  
#line 121 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"
  inline void lcr(Unsigned8 b);
  
#line 127 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"
  inline Unsigned8 lcr() const;
  
#line 133 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"
  inline void ier(Unsigned8 b);
  
#line 139 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"
  inline Unsigned8 ier() const;
  
#line 145 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"
  inline Unsigned8 iir() const;
  
#line 151 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"
  inline Unsigned8 msr() const;
  
#line 157 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"
  inline Unsigned8 lsr() const;
  
#line 163 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"
  inline void trb(Unsigned8 b);
  
#line 169 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"
  inline Unsigned8 trb() const;
  
#line 175 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"
  bool valid();
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 75 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"

#include "io.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 311 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"



inline int Uart::irq() const
{
  return _irq;
}

#line 87 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"



inline void Uart::outb( Unsigned8 b, Registers reg )
{
  Io::out8(b, port + (reg << Access_shift));
}

#line 131 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"


inline void Uart::ier(Unsigned8 b)
{
  outb(b, IER);
}

#line 94 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"


inline Unsigned8 Uart::inb( Registers reg ) const
{
  return Io::in8(port + (reg << Access_shift));
}

#line 137 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"


inline Unsigned8 Uart::ier() const
{
  return inb(IER);
}

#line 318 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"


inline void Uart::disable_rcv_irq()
{
  ier(ier() & ~1);
}

#line 328 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"


inline void Uart::enable_rcv_irq()
{
  ier(ier() | 1);
}

#endif // uart_h
