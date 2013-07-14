// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "startup.h"
#include "startup_i.h"


#line 35 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/startup-ia32.cpp"

FIASCO_INIT FIASCO_NOINLINE
void
Startup::stage1()
{
  Boot_info::init();
  Config::init();
  if (Kernel_uart::init(Kernel_uart::Init_before_mmu))
    Banner::init();
}

#line 45 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/startup-ia32.cpp"

FIASCO_INIT FIASCO_NOINLINE
void
Startup::stage2()
{
  // the logical ID of the boot CPU is always 0
  Kip_init::init();
  Kmem_alloc::init();

  Cpu::cpus.cpu(Cpu_number::boot_cpu()).identify();
  // initialize initial page tables (also used for other CPUs later)
  Mem_space::init_page_sizes();
  Kmem::init_mmu();

  if (Kernel_uart::init(Kernel_uart::Init_after_mmu))
    Banner::init();

  // Initialize cpu-local data management and run constructors for CPU 0
  Per_cpu_data::init_ctors();
  Per_cpu_data_alloc::alloc(Cpu_number::boot_cpu());
  Per_cpu_data::run_ctors(Cpu_number::boot_cpu());

  // set frequency in KIP to that of the boot CPU
  Kip_init::init_freq(Cpu::cpus.cpu(Cpu_number::boot_cpu()));

  bool use_io_apic = Io_apic::init(Cpu_number::boot_cpu());
  if (use_io_apic)
    {
      Config::apic = true;
      Pic::disable_all_save();
    }
  else
    {
      Pic::init();
      Irq_chip_ia32_pic::init();
    }

  Kernel_task::init(); // enables current_mem_space()

  // initialize initial TSS, GDT, IDT
  Kmem::init_cpu(Cpu::cpus.cpu(Cpu_number::boot_cpu()));
  Utcb_init::init();
  Idt::init();
  Fpu::init(Cpu_number::boot_cpu());
  Apic::init();
  Apic::apic.cpu(Cpu_number::boot_cpu()).construct();
  Ipi::init(Cpu_number::boot_cpu());
  Timer::init(Cpu_number::boot_cpu());
  int timer_irq = Timer::irq();
  if (use_io_apic)
    {
      // If we use the IOAPIC, we route our timer IRQ to
      // Config::Apic_timer_vector, even with PIT or RTC
      Config::scheduler_irq_vector = Config::Apic_timer_vector;

      if (timer_irq >= 0)
	{
	  Irq_mgr *const m = Irq_mgr::mgr;
	  Irq_mgr::Irq const irq = m->chip(m->legacy_override(timer_irq));
	  Io_apic *const apic = static_cast<Io_apic*>(irq.chip);

	  Io_apic_entry e = apic->read_entry(irq.pin);
	  e.vector() = Config::Apic_timer_vector;
	  apic->write_entry(irq.pin, e);
	}
    }
  else
    {
      if (timer_irq >= 0)
	Config::scheduler_irq_vector = 0x20 + timer_irq;
      else
	Config::scheduler_irq_vector = Config::Apic_timer_vector;
    }

  Idt::set_vectors_run();
  Timer::master_cpu(Cpu_number::boot_cpu());
  Apic::check_still_getting_interrupts();
//  Cpu::init_global_features();
}
