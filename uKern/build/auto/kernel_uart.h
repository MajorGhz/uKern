// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kernel_uart_h
#define kernel_uart_h
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart.cpp"

#include "uart.h"
#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart.cpp"
#include "std_macros.h"

//
// INTERFACE definition follows 
//

#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart.cpp"

class Kernel_uart

: public Uart
{
public:
  enum Init_mode
  {
    Init_before_mmu,
    Init_after_mmu
  };
  Kernel_uart();
  static void enable_rcv_irq();

#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart.cpp"
private:

private:
  /**
   * Prototype for the UART specific startup implementation.
   * @param uart, the instantiation to start.
   * @param port, the com port number.
   */
  bool startup(unsigned port, int irq=-1);

#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart-16550.cpp"
private:
 enum { Bsp_init_mode = Init_before_mmu }; 
public:  
#line 56 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart.cpp"
  static FIASCO_CONST
  Uart *
  uart();
  
#line 62 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart.cpp"
  static bool
  init(Init_mode init_mode = Init_before_mmu);
};

#endif // kernel_uart_h
