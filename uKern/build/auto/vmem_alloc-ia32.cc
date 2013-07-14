// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "vmem_alloc.h"
#include "vmem_alloc_i.h"

#line 56 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/vmem_alloc-ia32.cpp"


//----------------------------------------------------------------------------


#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/vmem_alloc-ia32.cpp"


void*
Vmem_alloc::page_alloc(void *address, Zero_fill zf, unsigned mode)
{
  void *vpage = 0;
  Address page;

  vpage = Kmem_alloc::allocator()->alloc(Config::PAGE_SHIFT);

  if (EXPECT_FALSE(!vpage))
    return 0;

  // insert page into master page table
  auto e = Kmem::kdir->walk(Virt_addr(address), Pdir::Depth,
                            false, pdir_alloc(Kmem_alloc::allocator()));
  if (EXPECT_FALSE(e.is_valid()))
    {
      kdb_ke("page_alloc: address already mapped");
      goto error;
    }

  if (e.level != Pdir::Depth)
    goto error;

  if (zf == ZERO_FILL)
    memset(vpage, 0, Config::PAGE_SIZE);

  page = Mem_layout::pmem_to_phys((Address)vpage);

  e.set_page(page, Pt_entry::Writable | Pt_entry::Dirty
                   | Pt_entry::Referenced
                   | Pt_entry::global() | (mode & User ? (unsigned)Pt_entry::User : 0));
  page_map (address, 0, zf, page);
  return address;

error:
  Kmem_alloc::allocator()->free(Config::PAGE_SHIFT, vpage); // 2^0 = 1 page
  return 0;
}
