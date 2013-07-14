// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef mem_layout_h
#define mem_layout_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_layout.cpp"

#include "l4_types.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/mem_layout-ia32-32.cpp"

#include "types.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/mem_layout-ia32-32.cpp"
#include "config.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/mem_layout-ia32-32.cpp"
#include "linking.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/mem_layout-ia32-32.cpp"
#include "template_math.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_layout.cpp"

class Mem_layout
{
public:
  /// reflect symbols in linker script
  static const char load            asm ("_load");
  static const char image_start     asm ("_kernel_image_start");
  static const char start           asm ("_start");
  static const char end             asm ("_end");
  static const char ecode           asm ("_ecode");
  static const char etext           asm ("_etext");
  static const char data_start      asm ("_kernel_data_start");
  static const char edata           asm ("_edata");
  static const char initcall_start  asm ("_initcall_start");
  static const char initcall_end    asm ("_initcall_end");

  static Mword in_tcbs (Address a); // FIXME
  static Mword in_kernel (Address a); // XXX: not right for UX

#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_layout-ia32.cpp"
private:

public:
  enum { Io_port_max = (1UL << 16) };

  static Address _io_map_ptr;

#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/mem_layout-ia32-32.cpp"
private:

public:
  enum Flags
  {
    /// Is the adapter memory in the kernel image super page?
    Adap_in_kernel_image = FIASCO_IMAGE_PHYS_START < Config::SUPERPAGE_SIZE,
  };

  enum
  {
    Utcb_addr         = 0xbff00000,    ///< % 4KB   UTCB map address
    Kip_auto_map      = 0xbfff2000,    ///< % 4KB
    User_max          = 0xc0000000,
    Service_page      = 0xeac00000,    ///< % 4MB   global mappings
    Local_apic_page   = Service_page + 0x0000,   ///< % 4KB
    Kmem_tmp_page_1   = Service_page + 0x2000,   ///< % 4KB size 8KB
    Kmem_tmp_page_2   = Service_page + 0x4000,   ///< % 4KB size 8KB
    Tbuf_status_page  = Service_page + 0x6000,   ///< % 4KB
    Tbuf_ustatus_page = Tbuf_status_page,
    Jdb_bench_page    = Service_page + 0x8000,   ///< % 4KB
    Jdb_bts_area      = Service_page + 0xf000,   ///< % 4KB size 0x81000
    utcb_ptr_align    = Tl_math::Ld<64>::Res,    // 64byte cachelines
    Idt               = Service_page + 0xfe000,  ///< % 4KB
    Syscalls          = Service_page + 0xff000,  ///< % 4KB syscall page
    Tbuf_buffer_area  = Service_page + 0x200000, ///< % 2MB
    Tbuf_ubuffer_area = Tbuf_buffer_area,
    // 0xeb800000-0xec000000 (8MB) free
    Io_map_area_start = 0xec000000,
    Io_map_area_end   = 0xec800000,
    __free_4          = 0xec880000,    ///< % 4MB
    Jdb_debug_start   = 0xecc00000,    ///< % 4MB   JDB symbols/lines
    Jdb_debug_end     = 0xee000000,    ///< % 4MB
    // 0xee000000-0xef800000 (24MB) free
    Kstatic           = 0xef800000,    ///< Io_bitmap - 4MB
    Io_bitmap         = 0xefc00000,    ///< % 4MB
    Vmem_end          = 0xf0000000,

    Kernel_image        = FIASCO_IMAGE_VIRT_START, // usually 0xf0000000
    Kernel_image_end    = Kernel_image + Config::SUPERPAGE_SIZE,

    Adap_image           = Adap_in_kernel_image
                           ? Kernel_image
                           : Kernel_image + Config::SUPERPAGE_SIZE,

    Adap_vram_mda_beg = Adap_image + 0xb0000, ///< % 8KB video RAM MDA memory
    Adap_vram_mda_end = Adap_image + 0xb8000,
    Adap_vram_cga_beg = Adap_image + 0xb8000, ///< % 8KB video RAM CGA memory
    Adap_vram_cga_end = Adap_image + 0xc0000,

    Caps_start        = 0xf0800000,    ///< % 4MB
    Caps_end          = 0xf3000000,    ///< % 4MB == Caps_start + (1<<20) * 4
    Physmem           = 0xfc400000,    ///< % 4MB   kernel memory
  };

  enum Offsets
  {
    Kernel_image_offset = FIASCO_IMAGE_PHYS_OFFSET,
  };

  enum Phys_addrs
  {
    Kernel_image_phys = FIASCO_IMAGE_PHYS_START & Config::SUPERPAGE_MASK,
    Adap_image_phys   = 0,
  };

  template < typename T > static T* boot_data (T const *addr);

  static Address pmem_size;
private:
  static Address physmem_offs asm ("PHYSMEM_OFFS");

public:  
#line 27 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_layout.cpp"
  static inline bool
  is_caps_area(Address a);
  
#line 50 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_layout.cpp"
  static inline Mword
  in_kernel_code(Address a);
  
#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_layout-ia32.cpp"
  static inline Address
  alloc_io_vmem(unsigned long bytes);
  
#line 31 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_layout-ia32.cpp"
  template< typename V > static inline bool
  read_special_safe(V const *address, V &v);
  
#line 47 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_layout-ia32.cpp"
  template< typename T > static inline T
  read_special_safe(T const *a);
  
#line 59 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_layout-ia32.cpp"
  static inline bool
  is_special_mapped(void const *a);
  
#line 91 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/mem_layout-ia32-32.cpp"
  static inline void
  kphys_base(Address base);
  
#line 98 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/mem_layout-ia32-32.cpp"
  static inline Address
  pmem_to_phys(Address addr);
  
#line 106 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/mem_layout-ia32-32.cpp"
  static inline Address
  pmem_to_phys(const void *ptr);
  
#line 116 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/mem_layout-ia32-32.cpp"
  static inline Address
  phys_to_pmem(Address addr);
  
#line 123 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/mem_layout-ia32-32.cpp"
  static inline Mword
  in_kernel_image(Address addr);
  
#line 130 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/mem_layout-ia32-32.cpp"
  static inline Mword
  in_pmem(Address addr);
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_layout-ia32.cpp"

#include "static_assert.h"
#line 82 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/mem_layout-ia32-32.cpp"

#include <cassert>
#line 84 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/mem_layout-ia32-32.cpp"
#include <kdb_ke.h>

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 25 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_layout.cpp"


inline bool
Mem_layout::is_caps_area(Address a)
{ return (a >= Caps_start) && (a < Caps_end); }

#line 48 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_layout.cpp"


inline Mword
Mem_layout::in_kernel_code(Address a)
{
  return a >= (Address)&start && a < (Address)&ecode;
}

#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_layout-ia32.cpp"


inline Address
Mem_layout::alloc_io_vmem(unsigned long bytes)
{
  bytes = (bytes + Config::PAGE_SIZE - 1) & ~(Config::PAGE_SIZE - 1);
  if (_io_map_ptr - bytes < Io_map_area_start)
    return 0;

  _io_map_ptr -= bytes;
  return _io_map_ptr;
}

#line 28 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_layout-ia32.cpp"



template< typename V > inline bool
Mem_layout::read_special_safe(V const *address, V &v)
{
  static_assert(sizeof(v) <= sizeof(Mword), "wrong sized argument");
  Mword value;
  bool res;
  asm volatile ("clc; mov (%[adr]), %[val]; setnc %b[ex] \n"
      : [val] "=acd" (value), [ex] "=r" (res)
      : [adr] "acdbSD" (address)
      : "cc");
  v = V(value);
  return res;
}

#line 44 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_layout-ia32.cpp"



template< typename T > inline T
Mem_layout::read_special_safe(T const *a)
{
  static_assert(sizeof(T) <= sizeof(Mword), "wrong sized return type");
  Mword res;
  asm volatile ("mov (%1), %0 \n\t"
      : "=acd" (res) : "acdbSD" (a) : "cc");
  return T(res);

}

#line 57 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_layout-ia32.cpp"


inline bool
Mem_layout::is_special_mapped(void const *a)
{
  // Touch the state to page in the TCB. If we get a pagefault here,
  // the handler doesn't handle it but returns immediatly after
  // setting eax to 0xffffffff
  Mword pagefault_if_0;
  asm volatile (
      "clc; mov (%2), %0 \n\t"
      "setnc %b0         \n\t"
      : "=acd" (pagefault_if_0)
      : "0"(0UL), "acdbSD"(a)
      : "cc");
  return pagefault_if_0;
}

#line 88 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/mem_layout-ia32-32.cpp"



inline void
Mem_layout::kphys_base(Address base)
{
  physmem_offs = (Address)Physmem - base;
}

#line 96 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/mem_layout-ia32-32.cpp"


inline Address
Mem_layout::pmem_to_phys(Address addr)
{
  assert (in_pmem(addr));
  return addr - physmem_offs;
}

#line 104 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/mem_layout-ia32-32.cpp"


inline Address
Mem_layout::pmem_to_phys(const void *ptr)
{
  Address addr = reinterpret_cast<Address>(ptr);

  assert_kdb (in_pmem(addr));
  return addr - physmem_offs;
}

#line 114 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/mem_layout-ia32-32.cpp"


inline Address
Mem_layout::phys_to_pmem(Address addr)
{
  return addr + physmem_offs;
}

#line 121 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/mem_layout-ia32-32.cpp"


inline Mword
Mem_layout::in_kernel_image(Address addr)
{
  return addr >= Kernel_image && addr < Kernel_image_end;
}

#line 128 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/mem_layout-ia32-32.cpp"


inline Mword
Mem_layout::in_pmem(Address addr)
{
  return addr >= Physmem;
}

#line 41 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_layout.cpp"


inline Mword
Mem_layout::in_kernel(Address a)
{
  return a >= User_max;
}

#endif // mem_layout_h
