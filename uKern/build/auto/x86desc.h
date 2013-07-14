// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef x86desc_h
#define x86desc_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"

#include "l4_types.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"

class X86desc
{
public:
  enum
  {
    Accessed            = 0x01,
    Access_kernel       = 0x00,
    Access_user         = 0x60,
    Access_present      = 0x80,

    Access_tss          = 0x09,
    Access_intr_gate    = 0x0e,
    Access_trap_gate    = 0x0f,

    Long_mode           = 0x02, // XXX for code segments
  };

public:  
#line 183 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  const char*
  type_str() const;
  
#line 252 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  void
  show() const;
  
#line 274 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline X86desc();
  
#line 278 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline unsigned access() const;
  
#line 282 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline int
  present() const;
  
#line 289 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline Unsigned8
  type() const;
  
#line 296 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline Unsigned8
  dpl() const;
  
#line 303 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline bool
  unsafe() const;
};
#line 22 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


class Gdt_entry : public X86desc
{
public:
  enum
  {
    Access_type_user    = 0x10,
    Access_code_read    = 0x1a,
    Access_data_write   = 0x12,
    Size_32             = 0x04,
  };

  Unsigned16   limit_low;
  Unsigned16   base_low;
  Unsigned8    base_med;
  Unsigned8    access;
  Unsigned8    limit_high;
  Unsigned8    base_high;



public:  
#line 115 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline Address
  base() const;
  
#line 212 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  void
  show() const;
  
#line 339 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline Gdt_entry(Address base, Unsigned32 limit,
  		     Unsigned8 _access, Unsigned8 szbits);
  
#line 352 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline Gdt_entry();
  
#line 357 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline Mword
  limit() const;
  
#line 362 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline Mword
  size() const;
  
#line 370 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline bool
  avl() const;
  
#line 377 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline bool
  seg64() const;
  
#line 384 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline bool
  seg32() const;
  
#line 391 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline unsigned
  mode() const;
  
#line 396 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline bool
  granularity() const;
  
#line 403 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline bool
  writable() const;
  
#line 410 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline int
  contents() const;
  
#line 417 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline void
  clear();
} __attribute__((packed));
#line 44 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


class Idt_entry : public X86desc
{
private:
  Unsigned16 _offset_low;
  Unsigned16 _selector;
  Unsigned8  _ist;
  Unsigned8  _access;
  Unsigned16 _offset_high;

public:  
#line 70 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline Address offset() const;
  
#line 74 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline Idt_entry();
  
#line 77 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  // interrupt gate
  
  inline Idt_entry(Address entry, Unsigned16 selector, Unsigned8 access, unsigned = 0);
  
#line 88 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  // task gate
  
  inline Idt_entry(Unsigned16 selector, Unsigned8 access);
  
#line 100 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  static inline Idt_entry
  free(Unsigned16 val);
  
#line 110 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline Unsigned16
  get_free_val() const;
  
#line 226 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline unsigned
  selector() const;
  
#line 231 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  void
  show() const;
  
#line 324 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline unsigned
  ist() const;
  
#line 334 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline void
  clear();
} __attribute__((packed));
#line 55 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"



class Pseudo_descriptor
{
  Unsigned16 _limit;
  Mword _base;

public:  
#line 308 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline Pseudo_descriptor();
  
#line 312 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline Pseudo_descriptor(Address base, Unsigned16 limit);
  
#line 317 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline Address
  base() const;
  
#line 329 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline Unsigned16
  limit() const;
} __attribute__((packed));

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 270 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"

#include <cstring>

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 272 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline X86desc::X86desc()
{}

#line 276 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline unsigned X86desc::access() const
{ return ((Unsigned8 const *)this)[5]; }

#line 280 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline int
X86desc::present() const
{
  return (access() & 0x80) >> 7;
}

#line 287 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline Unsigned8
X86desc::type() const
{
  return access() & 0x1f;
}

#line 294 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline Unsigned8
X86desc::dpl() const
{
  return (access() & 0x60) >> 5;
}

#line 301 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline bool
X86desc::unsafe() const
{ return present() && (dpl() != 3); }

#line 113 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline Address
Gdt_entry::base() const
{
  return (Address)base_low | ((Address)base_med  << 16)
         | ((Address)base_high << 24);
}

#line 337 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline Gdt_entry::Gdt_entry(Address base, Unsigned32 limit,
		     Unsigned8 _access, Unsigned8 szbits)
{
  limit_low  =  limit & 0x0000ffff;
  base_low   =  base  & 0x0000ffff;
  base_med   = (base  & 0x00ff0000) >> 16;
  access     =  _access | Access_present;
  limit_high = ((limit & 0x000f0000) >> 16) |
			(((Unsigned16)szbits) << 4);
  base_high  = (base  & 0xff000000) >> 24;
}

#line 350 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline Gdt_entry::Gdt_entry()
{}

#line 354 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"



inline Mword
Gdt_entry::limit() const
{ return (Mword)limit_low | (((Mword)limit_high & 0x0f) << 16); }

#line 394 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline bool
Gdt_entry::granularity() const
{
  return (limit_high & 0x80);
}

#line 360 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline Mword
Gdt_entry::size() const
{
  Mword l = limit();
  return granularity() ? ((l+1) << 12)-1 : l;
}

#line 368 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline bool
Gdt_entry::avl() const
{
  return (limit_high & 0x10);
}

#line 375 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline bool
Gdt_entry::seg64() const
{
  return (limit_high & 0x20);
}

#line 382 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline bool
Gdt_entry::seg32() const
{
  return (limit_high & 0x40);
}

#line 389 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline unsigned
Gdt_entry::mode() const
{ return (limit_high >> 5) & 3; }

#line 401 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline bool
Gdt_entry::writable() const
{
  return (type() & 0x02);
}

#line 408 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline int
Gdt_entry::contents() const
{
  return (type() & 0x0c) >> 2;
}

#line 415 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline void
Gdt_entry::clear()
{
  *(Unsigned64*)this = 0;
}

#line 68 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline Address Idt_entry::offset() const
{ return (Address)_offset_low | ((Address)_offset_high << 16); }

#line 72 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline Idt_entry::Idt_entry()
{}

#line 76 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"

// interrupt gate

inline Idt_entry::Idt_entry(Address entry, Unsigned16 selector, Unsigned8 access, unsigned)
{
  _offset_low  = entry & 0x0000ffff;
  _selector    = selector;
  _ist         = 0;
  _access      = access | X86desc::Access_present;
  _offset_high = (entry & 0xffff0000) >> 16;
}

#line 87 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"

// task gate

inline Idt_entry::Idt_entry(Unsigned16 selector, Unsigned8 access)
{
  _offset_low  = 0;
  _selector    = selector;
  _ist         = 0;
  _access      = access | X86desc::Access_present;
  _offset_high = 0;
}

#line 98 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline Idt_entry
Idt_entry::free(Unsigned16 val)
{
  Idt_entry e;
  e._access = 0;
  e._offset_low = val;
  return e;
}

#line 108 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline Unsigned16
Idt_entry::get_free_val() const
{ return _offset_low; }

#line 224 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline unsigned
Idt_entry::selector() const
{ return _selector; }

#line 322 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline unsigned
Idt_entry::ist() const
{ return _ist; }

#line 332 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline void
Idt_entry::clear()
{ memset(this, 0, sizeof(*this)); }

#line 306 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline Pseudo_descriptor::Pseudo_descriptor()
{}

#line 310 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline Pseudo_descriptor::Pseudo_descriptor(Address base, Unsigned16 limit)
  : _limit(limit), _base(base)
{}

#line 315 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline Address
Pseudo_descriptor::base() const
{
  return _base;
}

#line 327 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline Unsigned16
Pseudo_descriptor::limit() const
{ return _limit; }

#endif // x86desc_h
