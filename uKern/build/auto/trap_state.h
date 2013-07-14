// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef trap_state_h
#define trap_state_h
#line 3 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"

#include "l4_types.h"

//
// INTERFACE definition follows 
//

#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"

class Trap_state
{
  friend class Jdb_tcb;
  friend class Jdb_stack_view;

public:
  typedef FIASCO_FASTCALL int (*Handler)(Trap_state*, unsigned cpu);
  static Handler base_handler asm ("BASE_TRAP_HANDLER");

  // Saved segment registers
  Mword  _es;
  Mword  _ds;
  Mword  _gs;                                     // => utcb->values[ 0]
  Mword  _fs;                                     // => utcb->values[ 1]

  // PUSHA register state frame
  Mword  _di;                                     // => utcb->values[ 2]
  Mword  _si;                                     // => utcb->values[ 3]
  Mword  _bp;                                     // => utcb->values[ 4]
  Mword  _cr2; // we save cr2 over esp for PFs    // => utcb->values[ 5]
  Mword  _bx;                                     // => utcb->values[ 6]
  Mword  _dx;                                     // => utcb->values[ 7]
  Mword  _cx;                                     // => utcb->values[ 8]
  Mword  _ax;                                     // => utcb->values[ 9]

  // Processor trap number, 0-31
  Mword  _trapno;                                 // => utcb->values[10]

  // Error code pushed by the processor, 0 if none
  Mword  _err;                                    // => utcb->values[11]

protected:
  // Processor state frame
  Mword  _ip;                                     // => utcb->values[12]
  Mword  _cs;                                     // => utcb->values[13]
  Mword  _flags;                                  // => utcb->values[14]
  Mword  _sp;                                     // => utcb->values[15]
  Mword  _ss;

public:  
#line 54 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline void
  sanitize_user_state();
  
#line 88 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline void
  set_ipc_upcall();
  
#line 96 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline void
  set_pagefault(Mword pfa, Mword error);
  
#line 105 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline Mword
  trapno() const;
  
#line 110 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline Mword
  error() const;
  
#line 115 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline Mword
  ip() const;
  
#line 120 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline Mword
  cs() const;
  
#line 125 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline Mword
  flags() const;
  
#line 130 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline Mword
  sp() const;
  
#line 135 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline Mword
  ss() const;
  
#line 140 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline Mword
  value() const;
  
#line 145 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline Mword
  value2() const;
  
#line 150 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline Mword
  dx() const;
  
#line 155 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline Mword
  value3() const;
  
#line 160 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline Mword
  value4() const;
  
#line 165 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline void
  ip(Mword ip);
  
#line 170 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline void
  cs(Mword cs);
  
#line 175 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline void
  flags(Mword flags);
  
#line 180 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline void
  sp(Mword sp);
  
#line 185 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline void
  ss(Mword ss);
  
#line 190 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline void
  value(Mword value);
  
#line 195 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline void
  value3(Mword value);
  
#line 200 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline void
  consume_instruction(unsigned count);
  
#line 205 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline bool
  is_debug_exception() const;
  
#line 210 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  void
  dump();
  
#line 252 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline bool
  exclude_logging();
};

#line 243 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
extern "C" FIASCO_FASTCALL
void
trap_dump_panic(Trap_state *ts);

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 49 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"

#include "regdefs.h"
#line 51 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
#include "gdt.h"
#line 83 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
#include "atomic.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 52 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline void
Trap_state::sanitize_user_state()
{
  _cs = Gdt::gdt_code_user | Gdt::Selector_user;
  _ss = Gdt::gdt_data_user | Gdt::Selector_user;
  _flags = (_flags & ~(EFLAGS_IOPL | EFLAGS_NT)) | EFLAGS_IF;
}

#line 86 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline void
Trap_state::set_ipc_upcall()
{
  _err = 0;
  _trapno = 0xfe;
}

#line 94 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline void
Trap_state::set_pagefault(Mword pfa, Mword error)
{
  _cr2 = pfa;
  _trapno = 0xe;
  _err = error;
}

#line 103 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline Mword
Trap_state::trapno() const
{ return _trapno; }

#line 108 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline Mword
Trap_state::error() const
{ return _err; }

#line 113 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline Mword
Trap_state::ip() const
{ return _ip; }

#line 118 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline Mword
Trap_state::cs() const
{ return _cs; }

#line 123 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline Mword
Trap_state::flags() const
{ return _flags; }

#line 128 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline Mword
Trap_state::sp() const
{ return _sp; }

#line 133 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline Mword
Trap_state::ss() const
{ return _ss; }

#line 138 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline Mword
Trap_state::value() const
{ return _ax; }

#line 143 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline Mword
Trap_state::value2() const
{ return _cx; }

#line 148 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline Mword
Trap_state::dx() const
{ return _dx; }

#line 153 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline Mword
Trap_state::value3() const
{ return _dx; }

#line 158 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline Mword
Trap_state::value4() const
{ return _bx; }

#line 163 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline void
Trap_state::ip(Mword ip)
{ _ip = ip; }

#line 168 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline void
Trap_state::cs(Mword cs)
{ _cs = cs; }

#line 173 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline void
Trap_state::flags(Mword flags)
{ _flags = flags; }

#line 178 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline void
Trap_state::sp(Mword sp)
{ _sp = sp; }

#line 183 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline void
Trap_state::ss(Mword ss)
{ _ss = ss; }

#line 188 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline void
Trap_state::value(Mword value)
{ _ax = value; }

#line 193 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline void
Trap_state::value3(Mword value)
{ _dx = value; }

#line 198 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"

 
inline void
Trap_state::consume_instruction(unsigned count)
{ cas ((Address*)(&_ip), _ip, _ip + count); }

#line 203 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline bool
Trap_state::is_debug_exception() const
{ return _trapno == 1 || _trapno == 3; }

#line 250 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline bool
Trap_state::exclude_logging()
{ return _trapno == 1 || _trapno == 3; }

#endif // trap_state_h
