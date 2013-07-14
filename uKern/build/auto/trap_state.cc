// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "trap_state.h"
#include "trap_state_i.h"

#line 45 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


//---------------------------------------------------------------------------

#line 84 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"

Trap_state::Handler Trap_state::base_handler FIASCO_FASTCALL;

#line 208 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


void
Trap_state::dump()
{
  int from_user = _cs & 3;

  printf("EAX %08lx EBX %08lx ECX %08lx EDX %08lx\n"
         "ESI %08lx EDI %08lx EBP %08lx ESP %08lx\n"
         "EIP %08lx EFLAGS %08lx\n"
         "CS %04lx SS %04lx DS %04lx ES %04lx FS %04lx GS %04lx\n"
         "trap %ld (%s), error %08lx, from %s mode\n",
	 _ax, _bx, _cx, _dx,
	 _si, _di, _bp, from_user ? _sp : (Unsigned32)&_sp,
	 _ip, _flags,
	 _cs & 0xffff, from_user ? _ss & 0xffff : Cpu::get_ss() & 0xffff,
	 _ds & 0xffff, _es & 0xffff, _fs & 0xffff, _gs & 0xffff,
	 _trapno, Cpu::exception_string(_trapno), _err, from_user ? "user" : "kernel");

  if (_trapno == 13)
    {
      if (_err & 1)
	printf("(external event");
      else
	printf("(internal event");
      if (_err & 2)
	printf(" regarding IDT gate descriptor no. 0x%02lx)\n", _err >> 3);
      else
	printf(" regarding %s entry no. 0x%02lx)\n",
	      _err & 4 ? "LDT" : "GDT", _err >> 3);
    }
  else if (_trapno == 14)
    printf("page fault linear address %08lx\n", _cr2);
}

#line 242 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"

extern "C" FIASCO_FASTCALL
void
trap_dump_panic(Trap_state *ts)
{
  ts->dump();
  panic("terminated due to trap");
}
