// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef keyb_h
#define keyb_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/keyb.cpp"

#include "console.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/keyb.cpp"

/**
 * Platform independent keyboard stub.
 *
 * Provides an empty implentation for write(...).
 */
class Keyb : public Console
{
public:
  // must be implemented in platform part.
  int getchar(bool blocking = true);

  // implemented empty
  int write(char const *str, size_t len);

  enum Keymap { Keymap_en, Keymap_de };
  void set_keymap(Keymap);

#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/keyb-pc.cpp"
private:

private:

  enum {
    /*
     * Keyboard I/O ports.
     */
    K_RDWR	    = 0x60, /* keyboard data & cmds (read/write) */
    K_STATUS        = 0x64, /* keybd status (read-only) */
    K_CMD	    = 0x64, /* keybd ctlr command (write-only) */

    /*
     * Bit definitions for K_STATUS port.
     */
    K_OBUF_FUL      = 0x01, /* output (from keybd) buffer full */
    K_IBUF_FUL      = 0x02, /* input (to keybd) buffer full */
    K_SYSFLAG	    = 0x04, /* "System Flag" */
    K_CMD_DATA	    = 0x08, /* 1 = input buf has cmd, 0 = data */
    K_KBD_INHIBIT   = 0x10, /* 0 if keyboard inhibited */
    K_AUX_OBUF_FUL  = 0x20, /* 1 = obuf holds aux device data */
    K_TIMEOUT	    = 0x40, /* timout error flag */
    K_PARITY_ERROR  = 0x80, /* parity error flag */

    /*
     * Keyboard controller commands (sent to K_CMD port).
     */
    KC_CMD_READ	    = 0x20, /* read controller command byte */
    KC_CMD_WRITE    = 0x60, /* write controller command byte */
    KC_CMD_DIS_AUX  = 0xa7, /* disable auxiliary device */
    KC_CMD_ENB_AUX  = 0xa8, /* enable auxiliary device */
    KC_CMD_TEST_AUX = 0xa9, /* test auxiliary device interface */
    KC_CMD_SELFTEST = 0xaa, /* keyboard controller self-test */
    KC_CMD_TEST	    = 0xab, /* test keyboard interface */
    KC_CMD_DUMP	    = 0xac, /* diagnostic dump */
    KC_CMD_DISABLE  = 0xad, /* disable keyboard */
    KC_CMD_ENABLE   = 0xae, /* enable keyboard */
    KC_CMD_RDKBD    = 0xc4, /* read keyboard ID */
    KC_CMD_WIN	    = 0xd0, /* read  output port */
    KC_CMD_WOUT	    = 0xd1, /* write output port */
    KC_CMD_ECHO	    = 0xee, /* used for diagnostic testing */
    KC_CMD_PULSE    = 0xff, /* pulse bits 3-0 based on low nybble */

    /*
     * Keyboard commands (send to K_RDWR).
     */
    K_CMD_LEDS	    = 0xed, /* set status LEDs (caps lock, etc.) */

    /*
     * Bit definitions for controller command byte (sent following
     * K_CMD_WRITE command).
     */
    K_CB_ENBLIRQ    = 0x01, /* enable data-ready intrpt */
    K_CB_SETSYSF    = 0x04, /* Set System Flag */
    K_CB_INHBOVR    = 0x08, /* Inhibit Override */
    K_CB_DISBLE	    = 0x10, /* disable keyboard */

    /*
     * Bit definitions for "Indicator Status Byte" (sent after a
     * K_CMD_LEDS command).  If the bit is on, the LED is on.  Undefined
     * bit positions must be 0.
     */
    K_LED_SCRLLK    = 0x1, /* scroll lock */
    K_LED_NUMLK	    = 0x2, /* num lock */
    K_LED_CAPSLK    = 0x4, /* caps lock */

    /*
     * Bit definitions for "Miscellaneous port B" (K_PORTB).
     */
    /* read/write */
    K_ENABLETMR2    = 0x01, /* enable output from timer 2 */
    K_SPKRDATA	    = 0x02, /* direct input to speaker */
    K_ENABLEPRTB    = 0x04, /* "enable" port B */
    K_EIOPRTB	    = 0x08, /* enable NMI on parity error */
    /* read-only */
    K_REFRESHB	    = 0x10, /* refresh flag from INLTCONT PAL */
    K_OUT2B	    = 0x20, /* timer 2 output */
    K_ICKB	    = 0x40, /* I/O channel check (parity error) */

    /*
     * Bit definitions for the keyboard controller's output port.
     */
    KO_SYSRESET	    = 0x01, /* processor reset */
    KO_GATE20	    = 0x02, /* A20 address line enable */
    KO_AUX_DATA_OUT = 0x04, /* output data to auxiliary device */
    KO_AUX_CLOCK    = 0x08, /* auxiliary device clock */
    KO_OBUF_FUL	    = 0x10, /* keyboard output buffer full */
    KO_AUX_OBUF_FUL = 0x20, /* aux device output buffer full */
    KO_CLOCK	    = 0x40, /* keyboard clock */
    KO_DATA_OUT	    = 0x80, /* output data to keyboard */
  };

public:  
#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/keyb.cpp"
  Mword
  get_attributes() const;
};

#endif // keyb_h
