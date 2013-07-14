// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "sys_call_page.h"
#include "sys_call_page_i.h"

#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/sys_call_page-abs-ia32.cpp"
/*
 * Fiasco Syscall-Page Code (absolute addressing)
 */


#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/sys_call_page-abs-ia32.cpp"

enum
{
  Offs_invoke            = 0x000,
  Offs_se_invoke         = 0x000,
  Offs_kip_invoke        = 0x800,
  Offs_kip_se_invoke     = 0x800,
  Offs_debugger          = 0x200,
  Offs_kip_debugger      = 0x900,
};
#line 28 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/sys_call_page-abs-ia32.cpp"


#define INV_SYSCALL(sysc) \
  *reinterpret_cast<Unsigned16*>(Mem_layout::Syscalls + Offs_##sysc) = 0x0b0f
#line 32 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/sys_call_page-abs-ia32.cpp"

#define SYSCALL_SYMS(sysc) \
extern char sys_call_##sysc, sys_call_##sysc##_end
#line 35 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/sys_call_page-abs-ia32.cpp"

#define COPY_SYSCALL(sysc) do { \
memcpy( (char*)Mem_layout::Syscalls + Offs_##sysc, &sys_call_##sysc, \
        &sys_call_##sysc##_end- &sys_call_##sysc ); \
memcpy( (char*)Kip::k() + Offs_kip_##sysc, &sys_call_##sysc, \
        &sys_call_##sysc##_end- &sys_call_##sysc ); } while (0)

#line 41 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/sys_call_page-abs-ia32.cpp"



void
Sys_call_page::init()
{
  SYSCALL_SYMS(invoke);
  SYSCALL_SYMS(se_invoke);
  SYSCALL_SYMS(debugger);

  if (!Vmem_alloc::page_alloc((void*)Mem_layout::Syscalls, 
	Vmem_alloc::ZERO_FILL, Vmem_alloc::User))
    panic("FIASCO: can't allocate system-call page.\n");

  printf ("Absolute KIP Syscalls using: %s\n",
          Cpu::have_sysenter() ? "Sysenter" : "int 0x30");

  Kip::k()->kip_sys_calls       = 2;

  if (Cpu::have_sysenter())
    COPY_SYSCALL(se_invoke);
  else
    COPY_SYSCALL(invoke);

  COPY_SYSCALL(debugger);

  Kernel_task::kernel_task()->set_attributes(
      Virt_addr(Mem_layout::Syscalls),
      Page::Attr(Page::Rights::UR(), Page::Type::Normal(),
                 Page::Kern::Global()));
}
