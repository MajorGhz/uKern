// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kip_h
#define kip_h
#line 31 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"

#include "mem_region.h"
#line 33 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"
#include "types.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/ia32/kip-ia32.cpp"

#include "types.h"

//
// INTERFACE definition follows 
//

#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"

class Mem_desc
{
public:
  enum Mem_type
  {
    Undefined    = 0x0,
    Conventional = 0x1,
    Reserved     = 0x2,
    Dedicated    = 0x3,
    Shared       = 0x4,
    Kernel_tmp   = 0x7,

    Bootloader   = 0xe,
    Arch         = 0xf,
  };

private:
  Mword _l, _h;

public:  
#line 61 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"
  inline Mem_desc(Address start, Address end, Mem_type t, bool v = false,
                     unsigned st = 0);
  
#line 69 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"
  inline Address start() const;
  
#line 73 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"
  inline Address end() const;
  
#line 77 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"
  inline void
  type(Mem_type t);
  
#line 82 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"
  inline Mem_desc::Mem_type type() const;
  
#line 86 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"
  inline unsigned ext_type() const;
  
#line 90 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"
  inline unsigned is_virtual() const;
  
#line 94 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"
  inline bool contains(unsigned long addr);
  
#line 100 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"
  inline bool valid() const;
  
#line 35 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip-debug.cpp"
  void 
  dump() const;
};
#line 22 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"

//----------------------------------------------------------------------------

#line 25 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"

/* Empty class for VHW descriptor in KIP for native ia32 */
class Vhw_descriptor {};
#line 28 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"

//----------------------------------------------------------------------------

#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"

class Kip
{
public:
  void print() const;

  char const *version_string() const;

  // returns the 1st address beyond all available physical memory
  Address main_memory_high() const;

private:
  static Kip *global_kip asm ("GLOBAL_KIP");

#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip-debug.cpp"
private:

private:
  void debug_print_syscalls() const;

#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/ia32/kip-ia32.cpp"
private:

public:
  struct Platform_info
  {
    char name[16];
    Unsigned32 is_mp;
  };

  /* 0x00 */
  Mword      magic;
  Mword      version;
  Unsigned8  offset_version_strings;
  Unsigned8  fill0[3];
  Unsigned8  kip_sys_calls;
  Unsigned8  fill1[3];

  /* the following stuff is undocumented; we assume that the kernel
     info page is located at offset 0x1000 into the L4 kernel boot
     image so that these declarations are consistent with section 2.9
     of the L4 Reference Manual */

  /* 0x10 */
  Mword      sched_granularity;
  Mword      _res1[3];

  /* 0x20 */
  Mword      sigma0_sp, sigma0_ip;
  Mword      _res2[2];

  /* 0x30 */
  Mword      sigma1_sp, sigma1_ip;
  Mword      _res3[2];

  /* 0x40 */
  Mword      root_sp, root_ip;
  Mword      _res4[2];

  /* 0x50 */
  Mword      _res_50;
  Mword      _mem_info;
  Mword      _res_58[2];

  /* 0x60 */
  Mword      _res5[16];

  /* 0xA0 */
  volatile Cpu_time clock;
  Unsigned64 _res6;

  /* 0xB0 */
  Mword      frequency_cpu;
  Mword      frequency_bus;

  /* 0xB8 */
  Mword      _res7[10];

  /* 0xE0 */
  Mword      user_ptr;
  Mword      vhw_offset;
  Unsigned32 _res8[2];

  /* 0xF0 */
  Platform_info platform_info;
  Unsigned32 __reserved[3];

public:  
#line 104 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"
  inline Mem_desc *mem_descs();
  
#line 108 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"
  inline Mem_desc const *mem_descs() const;
  
#line 112 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"
  inline unsigned num_mem_descs() const;
  
#line 116 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"
  inline void num_mem_descs(unsigned n);
  
#line 123 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"
  Mem_desc *add_mem_region(Mem_desc const &md);
  
#line 145 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"
  static void init_global_kip(Kip *kip);
  
#line 155 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"
  static inline Kip *k();

private:  
#line 43 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip-debug.cpp"
  void
  debug_print_memory() const;
  
#line 61 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip-debug.cpp"
  void
  debug_print_features() const;
};
#line 48 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"

#define L4_KERNEL_INFO_MAGIC (0x4BE6344CL) /* "L4µK" */

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 59 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"


inline Mem_desc::Mem_desc(Address start, Address end, Mem_type t, bool v,
                   unsigned st)
: _l((start & ~0x3ffUL) | (t & 0x0f) | ((st << 4) & 0x0f0)
     | (v?0x0200:0x0)),
  _h(end)
{}

#line 67 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"


inline Address Mem_desc::start() const
{ return _l & ~0x3ffUL; }

#line 71 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"


inline Address Mem_desc::end() const
{ return _h | 0x3ffUL; }

#line 75 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"


inline void
Mem_desc::type(Mem_type t)
{ _l = (_l & ~0x0f) | (t & 0x0f); }

#line 80 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"


inline Mem_desc::Mem_type Mem_desc::type() const
{ return (Mem_type)(_l & 0x0f); }

#line 84 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"


inline unsigned Mem_desc::ext_type() const
{ return _l & 0x0f0; }

#line 88 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"


inline unsigned Mem_desc::is_virtual() const
{ return _l & 0x200; }

#line 92 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"


inline bool Mem_desc::contains(unsigned long addr)
{
  return start() <= addr && end() >= addr;
}

#line 98 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"


inline bool Mem_desc::valid() const
{ return type() && start() < end(); }

#line 102 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"


inline Mem_desc *Kip::mem_descs()
{ return (Mem_desc*)(((Address)this) + (_mem_info >> (MWORD_BITS/2))); }

#line 106 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"


inline Mem_desc const *Kip::mem_descs() const
{ return (Mem_desc const *)(((Address)this) + (_mem_info >> (MWORD_BITS/2))); }

#line 110 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"


inline unsigned Kip::num_mem_descs() const
{ return _mem_info & ((1UL << (MWORD_BITS/2))-1); }

#line 114 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"


inline void Kip::num_mem_descs(unsigned n)
{
  _mem_info = (_mem_info & ~((1UL << (MWORD_BITS/2))-1)
	       | (n & ((1UL << (MWORD_BITS/2))-1)));
}

#line 154 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"

inline Kip *Kip::k() { return global_kip; }

#endif // kip_h
