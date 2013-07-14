// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "boot_console.h"
#include "boot_console_i.h"

#line 24 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/boot_console-ia32-amd64.cpp"

static Static_object<Vga_console> vga;
#line 26 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/boot_console-ia32-amd64.cpp"
static Static_object<Keyb> keyb;

#line 27 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/boot_console-ia32-amd64.cpp"

FIASCO_INIT
void Boot_console::init()
{
  keyb.construct();
  if (Koptions::o()->opt(Koptions::F_keymap_de))
    keyb->set_keymap(Keyb::Keymap_de);
  Kconsole::console()->register_console(keyb);

  if (Koptions::o()->opt(Koptions::F_noscreen))
    return;

#if defined(CONFIG_IRQ_SPINNER)
  vga.construct((unsigned long)Mem_layout::Adap_vram_cga_beg,80,20,true,true);
#else
  vga.construct((unsigned long)Mem_layout::Adap_vram_cga_beg,80,25,true,true);
#endif

  if (vga->is_working())
    Kconsole::console()->register_console(vga);

#if defined(CONFIG_IRQ_SPINNER)
  for (int y = 20; y < 25; ++y)
    for (int x = 0; x < 80; ++x)
      vga->printchar(x, y, ' ', 8);
#endif
};
