// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kernel_uart_i_h
#define kernel_uart_i_h
#line 36 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart.cpp"

#include <cstring>
#line 38 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart.cpp"
#include <cstdlib>
#line 39 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart.cpp"
#include <cstdio>
#line 40 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart.cpp"

#include "filter_console.h"
#line 42 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart.cpp"
#include "irq_chip.h"
#line 43 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart.cpp"
#include "irq_mgr.h"
#line 44 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart.cpp"
#include "kdb_ke.h"
#line 45 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart.cpp"
#include "kernel_console.h"
#line 46 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart.cpp"
#include "uart.h"
#line 47 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart.cpp"
#include "config.h"
#line 48 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart.cpp"
#include "kip.h"
#line 49 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart.cpp"
#include "koptions.h"
#line 50 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart.cpp"
#include "panic.h"
#line 51 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart.cpp"
#include "vkey.h"
#line 100 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_uart.cpp"


class Kuart_irq : public Irq_base
{
public:
  Kuart_irq() { hit_func = &handler_wrapper<Kuart_irq>; }
  void switch_mode(bool) {}
  void handle(Upstream_irq const *ui)
  {
    mask_and_ack();
    ui->ack();
    unmask();
    if (!Vkey::check_())
      kdb_ke("IRQ ENTRY");
  }
};

#endif // kernel_uart_i_h
