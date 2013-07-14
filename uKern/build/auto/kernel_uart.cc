// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "kernel_uart.h"
#include "kernel_uart_i.h"

#line 33 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart.cpp"

//---------------------------------------------------------------------------

#line 52 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart.cpp"

static Static_object<Filter_console> _fcon;
#line 54 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart.cpp"
static Static_object<Kernel_uart> _kernel_uart;

#line 55 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart.cpp"

FIASCO_CONST
Uart *
Kernel_uart::uart()
{ return _kernel_uart; }

#line 60 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart.cpp"


bool
Kernel_uart::init(Init_mode init_mode)
{
  if ((int)init_mode != Bsp_init_mode)
    return false;

  if (Koptions::o()->opt(Koptions::F_noserial)) // do not use serial uart
    return true;

  _kernel_uart.construct();
  _fcon.construct(_kernel_uart);

  Kconsole::console()->register_console(_fcon, 0);
  return true;
}

#line 77 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart.cpp"


Kernel_uart::Kernel_uart()
{
  unsigned           n = Config::default_console_uart_baudrate;
  Uart::TransferMode m = Uart::MODE_8N1;
  unsigned long long p = Config::default_console_uart;
  int                i = -1;

  if (Koptions::o()->opt(Koptions::F_uart_baud))
    n = Koptions::o()->uart.baud;

  if (Koptions::o()->opt(Koptions::F_uart_base))
    p = Koptions::o()->uart.base_address;

  if (Koptions::o()->opt(Koptions::F_uart_irq))
    i = Koptions::o()->uart.irqno;

  if (!startup(p, i))
    printf("Comport/base 0x%04llx is not accepted by the uart driver!\n", p);
  else if (!change_mode(m, n))
    panic("Somthing is wrong with the baud rate (%d)!\n", n);
}

#line 116 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart.cpp"



void
Kernel_uart::enable_rcv_irq()
{
  static Kuart_irq uart_irq;
  if (Irq_mgr::mgr->alloc(&uart_irq, uart()->irq()))
    {
      uart_irq.unmask();
      uart()->enable_rcv_irq();
    }
}
