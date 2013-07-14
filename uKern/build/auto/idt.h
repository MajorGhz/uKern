// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef idt_h
#define idt_h
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"

#include "initcalls.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"
#include "kmem.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"
#include "mem_layout.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"
#include "types.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"
#include "x86desc.h"

//
// INTERFACE definition follows 
//

#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"

class Idt_init_entry;
#line 1 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"
/*
 * Fiasco Interrupt Descriptor Table (IDT) Code
 */


#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"

class Idt
{
  friend class Jdb_kern_info_bench;
public:
  // idt entries for 0x20 CPU exceptions, 0x10 IRQs, 7 syscalls,
  // 0x3e/0x3f for APIC exceptions
  static const unsigned _idt_max = 0xa0;
private:
  static const Address  _idt = Mem_layout::Idt;

public:  
#line 58 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"
  static FIASCO_INIT
  void
  init_table(Idt_init_entry *src);
  
#line 74 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"
  /**
   * IDT initialization function. Sets up initial interrupt vectors.
   * It also write-protects the IDT because of the infamous Pentium F00F bug.
   */
  static FIASCO_INIT
  void
  init();
  
#line 93 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"
  static void
  load();
  
#line 101 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"
  static void
  set_entry(unsigned vector, Idt_entry entry);
  
#line 114 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"
  static Idt_entry const &
  get(unsigned vector);
  
#line 122 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"
  /**
   * IDT patching function.
   * Allows to change interrupt gate vectors at runtime.
   * It makes the IDT writable for the duration of this operation.
   * @param vector interrupt vector to be modified
   * @param func new handler function for this interrupt vector
   * @param user true if user mode can use this vector, false otherwise
   */
  
  static void
  set_entry(unsigned vector, Address entry, bool user);
  
#line 151 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"
  static Address
  get_entry(unsigned vector);
  
#line 160 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"
  static inline Address
  idt();
  
#line 172 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"
  /**
   * IDT loading function.
   * Loads IDT base and limit into the CPU.
    * @param desc IDT descriptor (base address, limit)
    */  
  
  static inline void
  set(Pseudo_descriptor *desc);
  
#line 185 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"
  static inline void
  get(Pseudo_descriptor *desc);
  
#line 197 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"
  /**
   * Set IDT vector to the normal timer interrupt handler.
   */
  
  static void
  set_vectors_run();

private:  
#line 37 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"
  /**
   * IDT write-protect/write-unprotect function.
   * @param writable true if IDT should be made writable, false otherwise
   */
  
  static void
  set_writable(bool writable);
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 158 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"


inline Address
Idt::idt()
{
  return _idt;
}

#line 171 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"

/**
 * IDT loading function.
 * Loads IDT base and limit into the CPU.
  * @param desc IDT descriptor (base address, limit)
  */  

inline void
Idt::set(Pseudo_descriptor *desc)
{
  asm volatile ("lidt %0" : : "m" (*desc));
}

#line 183 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"


inline void
Idt::get(Pseudo_descriptor *desc)
{
  asm volatile ("sidt %0" : "=m" (*desc) : : "memory");
}

#endif // idt_h
