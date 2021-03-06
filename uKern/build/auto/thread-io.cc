// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "thread.h"
#include "thread_i.h"


#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/thread-io.cpp"

//
// disassamble IO statements to compute the port address and
// the number of ports accessed
//

/** Compute port number and size for an IO instruction.
    @param eip address of the instruction
    @param ts thread state with registers
    @param port return port address
    @param size return number of ports accessed
    @return true if the instruction was handled successfully
      false otherwise
*/
bool
Thread::get_ioport(Address eip, Trap_state *ts, unsigned *port, unsigned *size)
{
  int from_user = ts->cs() & 3;

  // handle 1 Byte IO
  switch (mem_space()->peek((Unsigned8*)eip, from_user))
    {
    case 0xec:			// in dx, al
    case 0x6c:			// insb
    case 0xee:			// out dx, al
    case 0x6e:			// outb
      *size = 0;
      *port = ts->dx() & 0xffff;
      return true;
    case 0xed:			// in dx, eax
    case 0x6d:			// insd
    case 0xef:			// out eax, dx
    case 0x6f:			// outd
      *size = 2;
      *port = ts->dx() & 0xffff;
      if (*port + 4 <= Mem_layout::Io_port_max)
	return true;
      else		   // Access beyond L4_IOPORT_MAX
	return false;
    case 0xfa:			// cli
    case 0xfb:			// sti
      *size = 16; /* 16bit IO space */
      *port = 0;
      return true;
    }

  // handle 2 Byte IO
  if (!(eip < Kmem::mem_user_max - 1))
    return false;

  switch (mem_space()->peek((Unsigned8 *)eip, from_user))
    {
    case 0xe4:			// in imm8, al
    case 0xe6:			// out al, imm8
      *size = 0;
      *port = mem_space()->peek((Unsigned8 *)(eip + 1), from_user);
      return true;
    case 0xe5:			// in imm8, eax
    case 0xe7:			// out eax, imm8
      *size = 2;
      *port = mem_space()->peek((Unsigned8 *)(eip + 1), from_user);
      return *port + 4 <= Mem_layout::Io_port_max ? true : false;

    case 0x66:			// operand size override
      switch (mem_space()->peek((Unsigned8 *)(eip + 1), from_user))
	{
	case 0xed:			// in dx, ax
	case 0xef:			// out ax, dx
	case 0x6d:			// insw
	case 0x6f:			// outw
	  *size = 1;
	  *port = ts->dx() & 0xffff;
	  if (*port + 2 <= Mem_layout::Io_port_max)
	    return true;
	  else		   // Access beyond L4_IOPORT_MAX
	    return false;
	case 0xe5:			// in imm8, ax
	case 0xe7:			// out ax,imm8
	  *size = 1;
	  *port = mem_space()->peek((Unsigned8 *)(eip + 2), from_user);
	  if (*port + 2 <= Mem_layout::Io_port_max)
	    return true;
	  else
	    return false;
	}

    case 0xf3:			// REP
      switch (mem_space()->peek((Unsigned8*)(eip + 1), from_user))
	{
	case 0x6c:			// REP insb
	case 0x6e:			// REP outb
	  *size = 0;
	  *port = ts->dx() & 0xffff;
	  return true;
	case 0x6d:			// REP insd
	case 0x6f:			// REP outd
	  *size = 2;
	  *port = ts->dx() & 0xffff;
	  if (*port + 4 <= Mem_layout::Io_port_max)
	    return true;
	  else		   // Access beyond L4_IOPORT_MAX
	    return false;
	}
    }

  // handle 3 Byte IO
  if (!(eip < Kmem::mem_user_max - 2))
    return false;

  Unsigned16 w = mem_space()->peek((Unsigned16 *)eip, from_user);
  if (w == 0x66f3 || // sizeoverride REP
      w == 0xf366)   // REP sizeoverride
    {
      switch (mem_space()->peek((Unsigned8 *)(eip + 2), from_user))
	{
	case 0x6d:			// REP insw
	case 0x6f:			// REP outw
	  *size = 1;
	  *port = ts->dx() & 0xffff;
	  if (*port + 2 <= Mem_layout::Io_port_max)
	    return true;
	  else		   // Access beyond L4_IOPORT_MAX
	    return false;
	}
    }

  // nothing appropriate found
  return false;
}
