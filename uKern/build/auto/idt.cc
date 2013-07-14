// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "idt.h"
#include "idt_i.h"

#line 165 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"


//---------------------------------------------------------------------------

#line 190 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"

extern "C" void entry_int_timer();
#line 192 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"
extern "C" void entry_int_timer_slow();
#line 193 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"
extern "C" void entry_int7();
#line 194 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"
extern "C" void entry_intf();
#line 195 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"
extern "C" void entry_int_pic_ignore();

#line 36 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"

/**
 * IDT write-protect/write-unprotect function.
 * @param writable true if IDT should be made writable, false otherwise
 */

void
Idt::set_writable(bool writable)
{
  auto e = Kmem::dir()->walk(Virt_addr(_idt));

  // Make sure page directory entry is valid and not a 4MB page
  assert (e.is_valid() && e.level == Pdir::Depth);

  if (writable)
    e.add_attribs(Pt_entry::Writable); // Make read-write
  else
    e.del_attribs(Pt_entry::Writable); // Make read-only

  Mem_unit::tlb_flush (_idt);
}

#line 57 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"

FIASCO_INIT
void
Idt::init_table(Idt_init_entry *src)
{
  Idt_entry *entries = (Idt_entry*)_idt;

  while (src->entry)
    {
      entries[src->vector] = 
	((src->type & 0x1f) == 0x05) // task gate?
	  ? Idt_entry(src->entry, src->type)
	  : Idt_entry(src->entry, Gdt::gdt_code_kernel, src->type);
      src++;
    }
}

#line 73 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"

/**
 * IDT initialization function. Sets up initial interrupt vectors.
 * It also write-protects the IDT because of the infamous Pentium F00F bug.
 */
FIASCO_INIT
void
Idt::init()
{
  if (!Vmem_alloc::page_alloc((void *) _idt, Vmem_alloc::ZERO_FILL))
    panic("IDT allocation failure");

  init_table((Idt_init_entry*)&idt_init_table);
  load();

  set_writable(false);
}

#line 90 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"



void
Idt::load()
{
  Pseudo_descriptor desc(_idt, _idt_max*sizeof(Idt_entry)-1);
  set(&desc);
}

#line 99 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"


void
Idt::set_entry(unsigned vector, Idt_entry entry)
{
  assert (vector < _idt_max);

  set_writable(true);

  Idt_entry *entries = (Idt_entry*)_idt;
  entries[vector] = entry;
  set_writable(false);
}

#line 112 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"


Idt_entry const &
Idt::get(unsigned vector)
{
  assert (vector < _idt_max);

  return ((Idt_entry*)_idt)[vector];
}

#line 121 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"

/**
 * IDT patching function.
 * Allows to change interrupt gate vectors at runtime.
 * It makes the IDT writable for the duration of this operation.
 * @param vector interrupt vector to be modified
 * @param func new handler function for this interrupt vector
 * @param user true if user mode can use this vector, false otherwise
 */

void
Idt::set_entry(unsigned vector, Address entry, bool user)
{
  assert (vector < _idt_max);

  set_writable(true);

  Idt_entry *entries = (Idt_entry*)_idt;
  if (entry)
    entries[vector] = Idt_entry(entry, Gdt::gdt_code_kernel,
			        Idt_entry::Access_intr_gate |
			        (user ? Idt_entry::Access_user 
			              : Idt_entry::Access_kernel));
  else
    entries[vector].clear();

  set_writable(false);
}

#line 149 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"


Address
Idt::get_entry(unsigned vector)
{
  assert (vector < _idt_max);
  Idt_entry *entries = (Idt_entry*)_idt;
  return entries[vector].offset();
}

#line 196 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/idt.cpp"

/**
 * Set IDT vector to the normal timer interrupt handler.
 */

void
Idt::set_vectors_run()
{
  Address func = (Config::esc_hack || Config::watchdog ||
		  Config::serial_esc==Config::SERIAL_ESC_NOIRQ)
		    ? (Address)entry_int_timer_slow // slower for debugging
		    : (Address)entry_int_timer;     // non-debugging

  set_entry(Config::scheduler_irq_vector, func, false);
#if 0
  if (!Irq_chip::hw_chip->is_free(0x7))
    Irq_chip::hw_chip->reset(0x07);

  if (!Irq_chip::hw_chip->is_free(0xf))
    Irq_chip::hw_chip->reset(0x0f);
#endif
}
