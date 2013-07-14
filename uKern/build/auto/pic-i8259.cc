// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "pic.h"
#include "pic_i.h"

#line 144 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/pic-i8259.cpp"

int Pic::special_fully_nested_mode = 1; // be compatible with Jochen's L4

#line 146 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/pic-i8259.cpp"

FIASCO_INIT
void
Pic::init()
{
  pic_init(0x20,0x28);
}

#line 158 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/pic-i8259.cpp"


//
// this version of pic_init() overrides the OSKIT's.
//
// differences to standard AT initialization: 
// . we use the "special fully nested mode" to let irq sources on the
//   slave irq raise nested
// . we give irq 2 (= slave pic) the highest prio on the master pic; this
//   results in the following sequence of prios: 8-15,3-7,0,1
//   this way, the timer interrupt on irq 8 always gets thru (even if 
//   some user irq handler doesn't acknowledge its irq!)
//
FIASCO_INIT
void
Pic::pic_init(unsigned char master_base, unsigned char slave_base)
{
  // disallow all interrupts before we selectively enable them 
  Pic::disable_all_save();
  /*
   * Set the LINTEN bit in the HyperTransport Transaction
   * Control Register.
   *
   * This will cause EXTINT and NMI interrupts routed over the
   * hypertransport bus to be fed into the LAPIC LINT0/LINT1.  If
   * the bit isn't set, the interrupts will go to the general cpu
   * INTR/NMI pins.  On a dual-core cpu the interrupt winds up
   * going to BOTH cpus.  The first cpu that does the interrupt ack
   * cycle will get the correct interrupt.  The second cpu that does
   * it will get a spurious interrupt vector (typically IRQ 7).
   */
#if 0
  if ((cpu_id & 0xff0) == 0xf30) 
#endif
    {
#if 0
      Unsigned32 tcr;
      Io::out32(0x0cf8,
	  (1 << 31) | /* enable */
	  (0 << 16) | /* bus */
	  (24 << 11) |        /* dev (cpu + 24) */
	  (0 << 8) |  /* func */
	  0x68                /* reg */
	  );
      tcr = Io::in32(0xcfc);
      if ((tcr & 0x00010000) == 0) {
	  Io::out32(0xcfc, tcr|0x00010000);
	  printf("AMD: Rerouting HyperTransport "
	      "EXTINT/NMI to APIC\n");
      }
      Io::out32(0x0cf8, 0);
#endif
  }
  // VMware isn't able to deal with the special fully nested mode
  // correctly so we simply don't use it while running under
  // VMware. Otherwise VMware will barf with 
  // *** VMware Workstation internal monitor error ***
  // BUG F(152):393 bugNr=4388

  if (Koptions::o()->opt(Koptions::F_nosfn))
    special_fully_nested_mode = 0;

  if (special_fully_nested_mode)
    {
      puts ("Enabling special fully nested mode for PIC");
      /* Initialize the master. */

      Io::out8_p(PICM_ICW1, MASTER_ICW);
      Io::out8_p(master_base, MASTER_OCW);
      Io::out8_p(PICM_ICW3, MASTER_OCW);
      Io::out8_p(SNF_MODE_ENA | PICM_ICW4, MASTER_OCW);

      /* Initialize the slave. */
      Io::out8_p(PICS_ICW1, SLAVES_ICW);
      Io::out8_p(slave_base, SLAVES_OCW);
      Io::out8_p(PICS_ICW3, SLAVES_OCW);
      Io::out8_p(SNF_MODE_ENA | PICS_ICW4, SLAVES_OCW);

      // the timer interrupt should have the highest priority so that it
      // always gets through
      if (Config::Pic_prio_modify
	  && (int)Config::Scheduler_mode == Config::SCHED_RTC)
	{
	  // setting specific rotation (specific priority) 
	  // -- see Intel 8259A reference manual
	  // irq 1 on master hast lowest prio
	  // => irq 2 (cascade) = irqs 8..15 have highest prio
	  Io::out8_p(SET_PRIORITY | 1, MASTER_ICW);
	  // irq 7 on slave has lowest prio
	  // => irq 0 on slave (= irq 8) has highest prio
	  Io::out8_p(SET_PRIORITY | 7, SLAVES_ICW);
	}
    }
  else
    {
      printf("%sUsing (normal) fully nested PIC mode\n",
	  Config::found_vmware ? "Found VMware: " : "");

      /* Initialize the master. */
      Io::out8_p(PICM_ICW1, MASTER_ICW);
      Io::out8_p(master_base, MASTER_OCW);
      Io::out8_p(PICM_ICW3, MASTER_OCW);
      Io::out8_p(PICM_ICW4, MASTER_OCW);

      /* Initialize the slave. */
      Io::out8_p(PICS_ICW1, SLAVES_ICW);
      Io::out8_p(slave_base, SLAVES_OCW);
      Io::out8_p(PICS_ICW3, SLAVES_OCW);
      Io::out8_p(PICS_ICW4, SLAVES_OCW);
    }

  // set initial masks
  Io::out8_p(0xfb, MASTER_OCW);	// unmask irq2
  Io::out8_p(0xff, SLAVES_OCW);	// mask everything

  /* Ack any bogus intrs by setting the End Of Interrupt bit. */
  Io::out8_p(NON_SPEC_EOI, MASTER_ICW);
  Io::out8_p(NON_SPEC_EOI, SLAVES_ICW);

  // disallow all interrupts before we selectively enable them 
  Pic::disable_all_save();

}
