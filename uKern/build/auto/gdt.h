// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef gdt_h
#define gdt_h
#line 3 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/gdt.cpp"

#include "config_gdt.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/gdt.cpp"
#include "l4_types.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/gdt.cpp"
#include "x86desc.h"

//
// INTERFACE definition follows 
//

#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/gdt.cpp"

class Gdt
{
public:
   /** Segment numbers. */
  enum 
  {
    gdt_tss             = GDT_TSS,
    gdt_code_kernel     = GDT_CODE_KERNEL,
    gdt_data_kernel     = GDT_DATA_KERNEL,
    gdt_code_user       = GDT_CODE_USER,
    gdt_data_user       = GDT_DATA_USER,
    gdt_tss_dbf         = GDT_TSS_DBF,
    gdt_utcb            = GDT_UTCB,
    gdt_ldt             = GDT_LDT,
    gdt_user_entry1     = GDT_USER_ENTRY1,
    gdt_user_entry2     = GDT_USER_ENTRY2,
    gdt_user_entry3     = GDT_USER_ENTRY3,
    gdt_max             = GDT_MAX,
  };

  enum
  {
    Selector_user       = 0x03,
    Selector_kernel     = 0x00,
  };

private:
  Gdt_entry _entries[0];

public:  
#line 60 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/gdt.cpp"
  inline void
  set_entry_byte(int nr, Address base, Unsigned32 limit,
  		    Unsigned8 access, Unsigned8 szbits);
  
#line 68 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/gdt.cpp"
  inline void
  set_entry_4k(int nr, Address base, Unsigned32 limit,
  		  Unsigned8 access, Unsigned8 szbits);
  
#line 76 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/gdt.cpp"
  inline void
  clear_entry(int nr);
  
#line 83 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/gdt.cpp"
  inline Gdt_entry*
  entries();
  
#line 90 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/gdt.cpp"
  inline Gdt_entry &
  operator[](unsigned idx);
  
#line 95 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/gdt.cpp"
  inline Gdt_entry const &
  operator[](unsigned idx) const;
  
#line 103 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/gdt.cpp"
  static inline void
  set(Pseudo_descriptor *desc);
  
#line 110 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/gdt.cpp"
  static inline void
  get(Pseudo_descriptor *desc);
  
#line 117 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/gdt.cpp"
  static inline int
  data_segment();
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 57 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/gdt.cpp"



inline void
Gdt::set_entry_byte(int nr, Address base, Unsigned32 limit,
		    Unsigned8 access, Unsigned8 szbits)
{
  _entries[nr] = Gdt_entry(base, limit, access, szbits);
}

#line 66 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/gdt.cpp"


inline void
Gdt::set_entry_4k(int nr, Address base, Unsigned32 limit,
		  Unsigned8 access, Unsigned8 szbits)
{
  _entries[nr] = Gdt_entry(base, limit >> 12, access, szbits | 0x08);
}

#line 74 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/gdt.cpp"


inline void
Gdt::clear_entry(int nr)
{
  _entries[nr].clear();
}

#line 81 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/gdt.cpp"


inline Gdt_entry*
Gdt::entries()
{
  return _entries;
}

#line 88 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/gdt.cpp"


inline Gdt_entry &
Gdt::operator[](unsigned idx)
{ return _entries[idx]; }

#line 93 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/gdt.cpp"


inline Gdt_entry const &
Gdt::operator[](unsigned idx) const
{ return _entries[idx]; }

#line 101 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/gdt.cpp"


inline void
Gdt::set(Pseudo_descriptor *desc)
{
  asm volatile ("lgdt %0" : : "m" (*desc));
}

#line 108 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/gdt.cpp"


inline void
Gdt::get(Pseudo_descriptor *desc)
{
  asm volatile ("sgdt %0" : "=m" (*desc) : : "memory");
}

#line 115 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/gdt.cpp"


inline int
Gdt::data_segment()
{ return gdt_data_user | Selector_user; }

#endif // gdt_h
