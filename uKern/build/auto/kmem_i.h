// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kmem_i_h
#define kmem_i_h

//
// IMPLEMENTATION of inline functions follows
//


#line 530 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


inline Address FIASCO_INIT_CPU
Kmem::__alloc(void **p, unsigned long size)
{
  Address r = ((unsigned long)*p + 0xf) & ~0xf;
  *p = (void*)(r + size);
  return r;
}

#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/kmem-ia32-32.cpp"

inline FIASCO_INIT_CPU
void
Kmem::init_cpu_arch(Cpu &cpu, void **cpu_mem)
{
  // allocate the task segment for the double fault handler
  cpu.init_tss_dbf (__alloc(cpu_mem, sizeof(Tss)),
      Mem_layout::pmem_to_phys(Kmem::dir()));

  cpu.init_sysenter();
}

#endif // kmem_i_h
