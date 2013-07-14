// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "uart_console.h"
#include "uart_console_i.h"


#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/uart_console.cpp"
static void uart_console_init_stage2();
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/uart_console.cpp"

STATIC_INITIALIZER  (uart_console_init_stage2);

#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/uart_console.cpp"

static void uart_console_init_stage2()
{
  if ((Kernel_uart::uart()->failed()))
    return;

  int irq = -1;
  if (Config::serial_esc == Config::SERIAL_ESC_IRQ
      && (irq = Kernel_uart::uart()->irq()) == -1)
    {
      puts("SERIAL ESC: not supported");
      Config::serial_esc = Config::SERIAL_ESC_NOIRQ;
    }

  switch (Config::serial_esc)
    {
    case Config::SERIAL_ESC_NOIRQ:
      puts("SERIAL ESC: No IRQ for specified uart port.");
      puts("Using serial hack in slow timer handler.");
      break;

    case Config::SERIAL_ESC_IRQ:
      Kernel_uart::enable_rcv_irq();
      printf("SERIAL ESC: allocated IRQ %d for serial uart\n", irq);
      puts("Not using serial hack in slow timer handler.");
      break;
    }
}
