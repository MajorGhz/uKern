// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef pic_h
#define pic_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/pic.cpp"

#include <types.h>
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/pic-i8259.cpp"

#include "initcalls.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/pic.cpp"

/**
 * Encapsulation of the platforms interrupt controller
 */
class Pic
{
public:
  /**
   * The type holding the saved Pic state.
   */
  typedef unsigned Status;

  /**
   * Static initalization of the interrupt controller
   */
  static void init();

  /**
   * Disable the given irq (without lock protection).
   * @pre The Cpu_lock must be locked (cli'ed)
   *
   * This function must be implemented in the
   * architecture specific part (e.g. pic-i8259.cpp).
   */
  static void disable_locked( unsigned irqnum );

  /**
   * Enable the given irq (without lock protection).
   * @pre The Cpu_lock must be locked (cli'ed)
   *
   * This function must be implemented in the
   * architecture specific part (e.g. pic-i8259.cpp).
   */
  static void enable_locked(unsigned irqnum, unsigned prio = 0);

  /**
   * Temporarily block the IRQ til the next ACK.
   * @pre The Cpu_lock must be locked (cli'ed)
   *
   * This function must be implemented in the
   * architecture specific part (e.g. pic-i8259.cpp).
   */
  static void block_locked(unsigned irqnum);

  /**
   * Disable all IRQ's and and return the old Pic state.
   * @pre Must be done with disabled interrupts.
   */
  static Status disable_all_save();

  /**
   * Restore the IRQ's to the saved state s.
   * @pre Must be done with disabled interrupts.
   * @param s, the saved state.
   */
  static void restore_all( Status s );

  /**
   * Acknowledge the given IRQ.
   * @pre The Cpu_lock must be locked (cli'ed).
   * @param irq, the irq to acknowledge.
   *
   * This function must be implemented in the
   * architecture specific part (e.g. pic-i8259.cpp).
   */
  static void acknowledge_locked( unsigned irq );

  /**
   * Set CPU affinity of IRQ.
   * @param irq IRQ.
   * @param cpu Logical CPU.
   */
  static void set_cpu(unsigned irq, Cpu_number cpu);

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/pic-i8259.cpp"
private:

public:
  enum
  {
    MASTER_PIC_BASE = 0x20,
    SLAVES_PIC_BASE = 0xa0,
    OFF_ICW	    = 0x00,
    OFF_OCW	    = 0x01,

    MASTER_ICW	    = MASTER_PIC_BASE + OFF_ICW,
    MASTER_OCW	    = MASTER_PIC_BASE + OFF_OCW,
    SLAVES_ICW	    = SLAVES_PIC_BASE + OFF_ICW,
    SLAVES_OCW	    = SLAVES_PIC_BASE + OFF_OCW,


    /*
    **	ICW1				
    */

    ICW_TEMPLATE    = 0x10,
    
    LEVL_TRIGGER    = 0x08,
    EDGE_TRIGGER    = 0x00,
    ADDR_INTRVL4    = 0x04,
    ADDR_INTRVL8    = 0x00,
    SINGLE__MODE    = 0x02,
    CASCADE_MODE    = 0x00,
    ICW4__NEEDED    = 0x01,
    NO_ICW4_NEED    = 0x00,

    /*
    **	ICW3				
    */

    SLAVE_ON_IR0    = 0x01,
    SLAVE_ON_IR1    = 0x02,
    SLAVE_ON_IR2    = 0x04,
    SLAVE_ON_IR3    = 0x08,
    SLAVE_ON_IR4    = 0x10,
    SLAVE_ON_IR5    = 0x20,
    SLAVE_ON_IR6    = 0x40,
    SLAVE_ON_IR7    = 0x80,
    
    I_AM_SLAVE_0    = 0x00,
    I_AM_SLAVE_1    = 0x01,
    I_AM_SLAVE_2    = 0x02,
    I_AM_SLAVE_3    = 0x03,
    I_AM_SLAVE_4    = 0x04,
    I_AM_SLAVE_5    = 0x05,
    I_AM_SLAVE_6    = 0x06,
    I_AM_SLAVE_7    = 0x07,

    /*
    **	ICW4				
    */
    
    SNF_MODE_ENA    = 0x10,
    SNF_MODE_DIS    = 0x00,
    BUFFERD_MODE    = 0x08,
    NONBUFD_MODE    = 0x00,
    AUTO_EOI_MOD    = 0x02,
    NRML_EOI_MOD    = 0x00,
    I8086_EMM_MOD   = 0x01,
    SET_MCS_MODE    = 0x00,

    /*
    **	OCW1				
    */
    
    PICM_MASK	    = 0xFF,
    PICS_MASK	    = 0xFF,
    
    /*
    **	OCW2				
    */
    
    NON_SPEC_EOI    = 0x20,
    SPECIFIC_EOI    = 0x60,
    ROT_NON_SPEC    = 0xa0,
    SET_ROT_AEOI    = 0x80,
    RSET_ROTAEOI    = 0x00,
    ROT_SPEC_EOI    = 0xe0,
    SET_PRIORITY    = 0xc0,
    NO_OPERATION    = 0x40,
    
    SND_EOI_IR0    = 0x00,
    SND_EOI_IR1    = 0x01,
    SND_EOI_IR2    = 0x02,
    SND_EOI_IR3    = 0x03,
    SND_EOI_IR4    = 0x04,
    SND_EOI_IR5    = 0x05,
    SND_EOI_IR6    = 0x06,
    SND_EOI_IR7    = 0x07,
 
    /*
    **	OCW3				
    */
    
    OCW_TEMPLATE    = 0x08,
    SPECIAL_MASK    = 0x40,
    MASK_MDE_SET    = 0x20,
    MASK_MDE_RST    = 0x00,
    POLL_COMMAND    = 0x04,
    NO_POLL_CMND    = 0x00,
    READ_NEXT_RD    = 0x02,
    READ_IR_ONRD    = 0x00,
    READ_IS_ONRD    = 0x01,
    
    /*
    **	Standard PIC initialization values for PCs.
    */
    PICM_ICW1	    = (ICW_TEMPLATE | EDGE_TRIGGER | ADDR_INTRVL8 
		       | CASCADE_MODE | ICW4__NEEDED),
    PICM_ICW3	    = SLAVE_ON_IR2,
    PICM_ICW4	    = (SNF_MODE_DIS | NONBUFD_MODE | NRML_EOI_MOD 
		       | I8086_EMM_MOD),

    PICS_ICW1	    = (ICW_TEMPLATE | EDGE_TRIGGER | ADDR_INTRVL8 
		       | CASCADE_MODE | ICW4__NEEDED),
    PICS_ICW3	    = I_AM_SLAVE_2,
    PICS_ICW4	    = (SNF_MODE_DIS | NONBUFD_MODE | NRML_EOI_MOD
		       | I8086_EMM_MOD),
  };

  static int special_fully_nested_mode;

public:  
#line 155 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/pic-i8259.cpp"
  static inline unsigned
  nr_irqs();

private:  
#line 160 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/pic-i8259.cpp"
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
  static FIASCO_INIT
  void
  pic_init(unsigned char master_base, unsigned char slave_base);
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 137 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/pic-i8259.cpp"
#include <cassert>
#line 138 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/pic-i8259.cpp"

#include "io.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 153 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/pic-i8259.cpp"


inline unsigned
Pic::nr_irqs()
{ return 16; }

#line 281 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/pic-i8259.cpp"


inline void
Pic::disable_locked(unsigned irq)
{
  if (irq < 8)
    Io::out8(Io::in8(MASTER_OCW) | (1 << irq), MASTER_OCW);
  else
    Io::out8(Io::in8(SLAVES_OCW) | (1 << (irq-8)), SLAVES_OCW);
}

#line 291 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/pic-i8259.cpp"


inline void
Pic::enable_locked(unsigned irq, unsigned /*prio*/)
{
  if (irq < 8)
    Io::out8(Io::in8(MASTER_OCW) & ~(1 << irq), MASTER_OCW);
  else
    {
      Io::out8(Io::in8(MASTER_OCW) & ~(1 << 2), MASTER_OCW);
      Io::out8(Io::in8(SLAVES_OCW) & ~(1 << (irq-8)), SLAVES_OCW);
    }
}

#line 304 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/pic-i8259.cpp"


inline void
Pic::acknowledge_locked(unsigned irq)
{
  if (irq >= 8)
    {
      Io::out8(NON_SPEC_EOI, SLAVES_ICW); // EOI slave
      if (special_fully_nested_mode)
	{
	  Io::out8(OCW_TEMPLATE | READ_NEXT_RD | READ_IS_ONRD, SLAVES_ICW);
	  if (Io::in8(SLAVES_ICW))      // slave still active?
	    return;                 // -- don't EOI master
	}
    }
  Io::out8(NON_SPEC_EOI, MASTER_ICW); // EOI master
}

#line 321 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/pic-i8259.cpp"


inline void
Pic::block_locked(unsigned)
{}

#line 326 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/pic-i8259.cpp"


inline Pic::Status
Pic::disable_all_save()
{
  Status s;
  s  = Io::in8(MASTER_OCW);
  s |= Io::in8(SLAVES_OCW) << 8;
  Io::out8( 0xff, MASTER_OCW );
  Io::out8( 0xff, SLAVES_OCW );
  
  return s;
}

#line 339 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/pic-i8259.cpp"


inline void
Pic::restore_all( Status s )
{
  Io::out8( s & 0x0ff, MASTER_OCW );
  Io::out8( (s >> 8) & 0x0ff, SLAVES_OCW );
}

#line 347 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/pic-i8259.cpp"



inline void
Pic::set_cpu(unsigned, Cpu_number cpu)
{
  (void)cpu;
  assert(cpu == Cpu_number::boot_cpu());
}

#endif // pic_h
