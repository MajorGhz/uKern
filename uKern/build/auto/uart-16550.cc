// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "uart.h"
#include "uart_i.h"

#line 324 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"


// ------------------------------------------------------------------------


#line 78 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"



Uart::Uart() : port(~0U), _irq(-1)
{}

#line 83 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"


Uart::~Uart()
{}

#line 173 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"


bool Uart::valid()
{
  Unsigned8 scratch, scratch2, scratch3;

  scratch = ier();
  ier(0x00);

  Io::iodelay();

  scratch2 = ier();
  ier(0x0f);
  Io::iodelay();

  scratch3 = ier();
  ier(scratch);

  return scratch2 == 0x00 && scratch3 == 0x0f;
}

#line 193 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"


bool Uart::startup(Address _port, int __irq)
{
  port = _port;
  _irq  = __irq;

  Proc::Status o = Proc::cli_save();

  if (!valid())
    {
      Proc::sti_restore(o);
      fail();
      return false;
    }

  ier(Base_ier_bits);/* disable all rs-232 interrupts */
  mcr(0x0b);         /* out2, rts, and dtr enabled */
  fcr(7);            /* enable and clear rcv+xmit fifo */
  lcr(0);            /* clear line control register */

  /* clearall interrupts */
  /*read*/ msr(); /* IRQID 0*/
  /*read*/ iir(); /* IRQID 1*/
  /*read*/ trb(); /* IRQID 2*/
  /*read*/ lsr(); /* IRQID 3*/

  while(lsr() & 1/*DATA READY*/) /*read*/ trb();
  Proc::sti_restore(o);
  return true;
}

#line 224 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"



void Uart::shutdown()
{
  Proc::Status o = Proc::cli_save();
  mcr(0x06);
  fcr(0);
  lcr(0);
  ier(0);
  Proc::sti_restore(o);
}

#line 236 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"


bool Uart::change_mode(TransferMode m, BaudRate r)
{
  Proc::Status o = Proc::cli_save();
  Unsigned8 old_lcr = lcr();
  if(r != BAUD_NC) {
    lcr(old_lcr | 0x80/*DLAB*/);
    Unsigned16 divisor = Base_rate/r;
    trb( divisor & 0x0ff );        /* BRD_LOW  */
    ier( (divisor >> 8) & 0x0ff ); /* BRD_HIGH */
    lcr(old_lcr);
  }
  if( m != MODE_NC ) {
    lcr( m & 0x07f );
  }

  Proc::sti_restore(o);
  return true;
}

#line 256 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"


Uart::TransferMode Uart::get_mode()
{
  return lcr() & 0x7f;
}

#line 262 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"


int Uart::write(char const *s, size_t count)
{
  /* disable uart irqs */
  Unsigned8 old_ier;
  old_ier = ier();
  ier(old_ier & ~0x0f);

  /* transmission */
  for (unsigned i = 0; i < count; i++)
    {
      while (!(lsr() & 0x20 /* THRE */))
	;
      trb(s[i]);
    }

  /* wait till everything is transmitted */
  while (!(lsr() & 0x40 /* TSRE */))
    ;

  ier(old_ier);
  return count;
}

#line 286 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"


int Uart::getchar(bool blocking)
{
  if (!blocking && !(lsr() & 1 /* DATA READY */))
    return -1;

  Unsigned8 old_ier, ch;
  old_ier = ier();
  ier(old_ier & ~0x0f);
  while (!(lsr() & 1 /* DATA READY */))
    ;
  ch = trb();
  ier(old_ier);
  return ch;
}

#line 302 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/uart-16550.cpp"


int Uart::char_avail() const
{
  if (lsr() & 1 /* DATA READY */)
    return 1;

  return 0;
}
