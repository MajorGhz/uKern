// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kmem_h
#define kmem_h
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

#include "globalconfig.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "initcalls.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "kip.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "mem_layout.h"

//
// INTERFACE definition follows 
//

#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

class Cpu;
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
class Pdir;
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
class Tss;
#line 1 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
// our own implementation of C++ memory management: disallow dynamic
// allocation (except where class-specific new/delete functions exist)
//
// more specialized memory allocation/deallocation functions follow
// below in the "Kmem" namespace


#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

class Device_map
{
public:
  enum
  {
    Max = 16,
    Virt_base = 0x20000000,
  };

private:
  Address _map[Max];


public:  
#line 108 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  void
  init();
  
#line 130 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  template< typename T > T *
  lookup(T *phys);
  
#line 172 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  template< typename T > T *
  map(T *phys, bool cache = true);
  
#line 177 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  void
  unmap(void const *phys);

private:  
#line 116 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  unsigned
  lookup_idx(Address phys);
  
#line 142 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  Address
  map(Address phys, bool /*cache*/);
};
#line 31 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

/**
 * The system's base facilities for kernel-memory management.
 * The kernel memory is a singleton object.  We access it through a
 * static class interface.
 */
class Kmem : public Mem_layout
{
  friend class Device_map;
  friend class Jdb;
  friend class Jdb_dbinfo;
  friend class Jdb_kern_info_misc;
  friend class Kdb;
  friend class Profile;
  friend class Vmem_alloc;

private:
  Kmem();			// default constructors are undefined
  Kmem (const Kmem&);
  static unsigned long pmem_cpu_page, cpu_page_vm;

public:
  static Device_map dev_map;

  enum
  {
    mem_user_max = Mem_layout::User_max,
  };

  static void init_pageing(Cpu const &boot_cpu);
  static void init_boot_cpu(Cpu const &boot_cpu);
  static void init_app_cpu(Cpu const &cpu);
  static Mword is_kmem_page_fault(Address pfa, Mword error);
  static Mword is_ipc_page_fault(Address pfa, Mword error);
  static Mword is_io_bitmap_page_fault(Address pfa);
  static Address kcode_start();
  static Address kcode_end();
  static Address virt_to_phys(const void *addr);


#line 77 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
private:

  friend class Kernel_task;

public:
  static Address     user_max();

private:
  static Unsigned8   *io_bitmap_delimiter;
  static Address kphys_start, kphys_end;
  static Pdir *kdir; ///< Kernel page directory

public:  
#line 197 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  static inline Address
  io_bitmap_delimiter_page();
  
#line 226 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  // Only used for initialization and kernel debugger
  
  static Address
  map_phys_page_tmp(Address phys, Mword idx);
  
#line 255 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  static inline Address kernel_image_start();
  
#line 268 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  /** Return number of IPC slots to copy */
  
  static inline unsigned
  ipc_slots();
  
#line 290 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  //
  // helper functions
  //
  
  // Establish a 4k-mapping
  
  static void
  map_phys_page(Address phys, Address virt,
                      bool cached, bool global, Address *offs = 0);
  
#line 316 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  static FIASCO_INIT
  void
  init_mmu();
  
#line 454 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  static FIASCO_INIT_CPU
  void
  init_cpu(Cpu &cpu);
  
#line 540 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  /**
   * Compute a kernel-virtual address for a physical address.
   * This function always returns virtual addresses within the
   * physical-memory region.
   * @pre addr <= highest kernel-accessible RAM address
   * @param addr a physical address
   * @return kernel-virtual address.
   */
  
  static inline void *
  phys_to_virt(Address addr);
  
#line 555 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  /** Allocate some bytes from a memory page */
  
  static inline Address
  alloc_tss(Address size);
  
#line 566 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  /**
   * Return Global page directory.
   * This is the master copy of the kernel's page directory. Kernel-memory
   * allocations are kept here and copied to task page directories lazily
   * upon page fault.
   * @return kernel's global page directory
   */
  static inline const Pdir* dir();

private:  
#line 532 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  static inline Address FIASCO_INIT_CPU
  __alloc(void **p, unsigned long size);
  
#line 3 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/kmem-ia32-32.cpp"
  static inline FIASCO_INIT_CPU
  void
  init_cpu_arch(Cpu &cpu, void **cpu_mem);
};
#line 71 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

typedef Kmem Kmem_space;
#line 73 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


//----------------------------------------------------------------------------


//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 95 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

#include "cpu.h"
#line 97 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "l4_types.h"
#line 98 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "kmem_alloc.h"
#line 99 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "mem_unit.h"
#line 100 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "panic.h"
#line 101 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "paging.h"
#line 102 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "pic.h"
#line 103 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "std_macros.h"
#line 104 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

#include <cstdio>
#line 512 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

#include <cstdlib>
#line 514 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include <cstddef>		// size_t
#line 515 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include <cstring>		// memset
#line 516 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

#include "boot_info.h"
#line 518 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "config.h"
#line 519 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "cpu.h"
#line 520 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "gdt.h"
#line 521 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "globals.h"
#line 522 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "paging.h"
#line 523 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "regdefs.h"
#line 524 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "std_macros.h"
#line 525 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "tss.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 194 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"



inline Address
Kmem::io_bitmap_delimiter_page()
{
  return reinterpret_cast<Address>(io_bitmap_delimiter);
}

#line 253 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


inline Address Kmem::kernel_image_start()
{ return virt_to_phys(&Mem_layout::image_start) & Config::PAGE_MASK; }

#line 266 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


/** Return number of IPC slots to copy */

inline unsigned
Kmem::ipc_slots()
{ return (8 << 20) / Config::SUPERPAGE_SIZE; }

#line 539 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

/**
 * Compute a kernel-virtual address for a physical address.
 * This function always returns virtual addresses within the
 * physical-memory region.
 * @pre addr <= highest kernel-accessible RAM address
 * @param addr a physical address
 * @return kernel-virtual address.
 */

inline void *
Kmem::phys_to_virt(Address addr)
{
  return reinterpret_cast<void *>(Mem_layout::phys_to_pmem(addr));
}

#line 554 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

/** Allocate some bytes from a memory page */

inline Address
Kmem::alloc_tss(Address size)
{
  Address ret = cpu_page_vm;
  cpu_page_vm += (size + 0xf) & ~0xf;

  return ret;
}

#line 565 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

/**
 * Return Global page directory.
 * This is the master copy of the kernel's page directory. Kernel-memory
 * allocations are kept here and copied to task page directories lazily
 * upon page fault.
 * @return kernel's global page directory
 */
inline const Pdir* Kmem::dir() { return kdir; }

#line 202 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


/**
 * Compute physical address from a kernel-virtual address.
 * @param addr a virtual address
 * @return corresponding physical address if a mappings exists.
 *         -1 otherwise.
 */

inline Address
Kmem::virt_to_phys(const void *addr)
{
  Address a = reinterpret_cast<Address>(addr);

  if (EXPECT_TRUE(Mem_layout::in_pmem(a)))
    return Mem_layout::pmem_to_phys(a);

  if (EXPECT_TRUE(Mem_layout::in_kernel_image(a)))
    return a - Mem_layout::Kernel_image_offset;

  return kdir->virt_to_phys(a);
}

#line 257 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

inline Address Kmem::kcode_start()
{ return virt_to_phys(&Mem_layout::start) & Config::PAGE_MASK; }

#line 260 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

inline Address Kmem::kcode_end()
{
  return (virt_to_phys(&Mem_layout::end) + Config::PAGE_SIZE)
         & Config::PAGE_MASK;
}

#line 273 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


inline Mword
Kmem::is_io_bitmap_page_fault(Address addr)
{
  return addr >= Mem_layout::Io_bitmap &&
	 addr <= Mem_layout::Io_bitmap + Mem_layout::Io_port_max / 8;
}

#line 281 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


inline Mword
Kmem::is_kmem_page_fault(Address addr, Mword /*error*/)
{
  return addr >= mem_user_max;
}

#line 506 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

inline Address Kmem::user_max() { return ~0UL; }

//
// IMPLEMENTATION of function templates
//


#line 126 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"




template< typename T > T *
Device_map::lookup(T *phys)
{
  unsigned idx = lookup_idx((Address)phys);
  if (idx == ~0U)
    return (T*)~0UL;

  return (T*)((Virt_base + idx * Config::SUPERPAGE_SIZE)
      | ((Address)phys & ~(~0UL << Config::SUPERPAGE_SHIFT)));
}

#line 169 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"



template< typename T > T *
Device_map::map(T *phys, bool cache)
{ return (T*)map((Address)phys, cache); }

#endif // kmem_h
