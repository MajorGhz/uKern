// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "keyb.h"
#include "keyb_i.h"

#line 103 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/keyb-pc.cpp"

enum {
  SHIFT = 0xff,
};
#line 107 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/keyb-pc.cpp"

static unsigned char keymap[][2] = {
  {0       },		/* 0 */
  {27,	27 },		/* 1 - ESC */
  {'1',	'!'},		/* 2 */
  {'2',	'@'},
  {'3',	'#'},
  {'4',	'$'},
  {'5',	'%'},
  {'6',	'^'},
  {'7',	'&'},
  {'8',	'*'},
  {'9',	'('},
  {'0',	')'},
  {'-',	'_'},
  {'=',	'+'},
  {8,	8  },		/* 14 - Backspace */
  {'\t','\t'},		/* 15 */
  {'q',	'Q'},
  {'w',	'W'},
  {'e',	'E'},
  {'r',	'R'},
  {'t',	'T'},
  {'y',	'Y'},
  {'u',	'U'},
  {'i',	'I'},
  {'o',	'O'},
  {'p',	'P'},
  {'[',	'{'},
  {']', '}'},		/* 27 */
  {'\r','\r'},		/* 28 - Enter */
  {0,	0  },		/* 29 - Ctrl */
  {'a',	'A'},		/* 30 */
  {'s',	'S'},
  {'d',	'D'},
  {'f',	'F'},
  {'g',	'G'},
  {'h',	'H'},
  {'j',	'J'},
  {'k',	'K'},
  {'l',	'L'},
  {';',	':'},
  {'\'','"'},		/* 40 */
  {'`',	'~'},		/* 41 */
  {SHIFT, SHIFT},	/* 42 - Left Shift */
  {'\\','|'},		/* 43 */
  {'z',	'Z'},		/* 44 */
  {'x',	'X'},
  {'c',	'C'},
  {'v',	'V'},
  {'b',	'B'},
  {'n',	'N'},
  {'m',	'M'},
  {',',	'<'},
  {'.',	'>'},
  {'/', '?'},		/* 53 */
  {SHIFT, SHIFT},	/* 54 - Right Shift */
  {0,	 0},		/* 55 - Print Screen */
  {0,	 0},		/* 56 - Alt */
  {' ',' '},		/* 57 - Space bar */
  {0,	 0},		/* 58 - Caps Lock */
  {0,	 0},		/* 59 - F1 */
  {0,	 0},		/* 60 - F2 */
  {0,	 0},		/* 61 - F3 */
  {0,	 0},		/* 62 - F4 */
  {0,	 0},		/* 63 - F5 */
  {0,	 0},		/* 64 - F6 */
  {0,	 0},		/* 65 - F7 */
  {0,	 0},		/* 66 - F8 */
  {0,	 0},		/* 67 - F9 */
  {0,	 0},		/* 68 - F10 */
  {0,	 0},		/* 69 - Num Lock */
  {0,	 0},		/* 70 - Scroll Lock */
  {0xb7,0xb7},		/* 71 - Numeric keypad 7 */
  {0xb8,0xb8},		/* 72 - Numeric keypad 8 */
  {0xb9,0xb9},		/* 73 - Numeric keypad 9 */
  {'-',	'-'},		/* 74 - Numeric keypad '-' */
  {0xb4,0xb4},		/* 75 - Numeric keypad 4 */
  {0xb5,0xb5},		/* 76 - Numeric keypad 5 */
  {0xb6,0xb6},		/* 77 - Numeric keypad 6 */
  {'+',	'+'},		/* 78 - Numeric keypad '+' */
  {0xb1,0xb1},		/* 79 - Numeric keypad 1 */
  {0xb2,0xb2},		/* 80 - Numeric keypad 2 */
  {0xb3,0xb3},		/* 81 - Numeric keypad 3 */
  {0xb0,0xb0},		/* 82 - Numeric keypad 0 */
  {0xae,0xae},		/* 83 - Numeric keypad '.' */
};

#line 194 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/keyb-pc.cpp"


void
Keyb::set_keymap(Keyb::Keymap km)
{
  // This is a one-time switch over only.
  if (km == Keymap_de)
    {
      // Simple patch to german layout
      keymap[ 3][1] = '"';
      keymap[ 7][1] = '&';
      keymap[ 8][1] = '/';
      keymap[ 9][1] = '(';
      keymap[10][1] = ')';
      keymap[11][1] = '=';
      keymap[12][1] = '?';
      keymap[13][1] = '`';
      keymap[21][0] = 'z';
      keymap[21][1] = 'Z';
      keymap[27][0] = '+';
      keymap[27][1] = '*';
      keymap[41][0] = '^';
      keymap[43][0] = '#';
      keymap[43][1] = '\'';
      keymap[44][0] = 'y';
      keymap[44][1] = 'Y';
      keymap[51][1] = ';';
      keymap[52][1] = ':';
      keymap[53][0] = '-';
      keymap[53][1] = '_';
    }
}

#line 226 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/keyb-pc.cpp"


int Keyb::getchar(bool wait)
{
  static unsigned shift_state;
  unsigned status, scan_code, ch;
  Proc::Status old_s = Proc::cli_save();

  for (;;)
    {
      /* Wait until a scan code is ready and read it. */
      status = Io::in8(0x64);
      if ((status & K_OBUF_FUL) == 0)
	{
	  if (wait)
	    continue;
          Proc::sti_restore(old_s);
	  return -1;
	}
      scan_code = Io::in8(0x60);

      /* Drop mouse events */
      if ((status & K_AUX_OBUF_FUL) != 0)
	{
	  if (wait)
	    continue;
	  Proc::sti_restore(old_s);
          return -1;
	}

      if ((scan_code & 0x7f) >= sizeof(keymap)/sizeof(keymap[0]))
	continue;

      /* Handle key releases - only release of SHIFT is important. */
      if (scan_code & 0x80)
	{
	  scan_code &= 0x7f;
	  if (keymap[scan_code][0] == SHIFT)
	    shift_state = 0;
	  continue;
	}

      /* Translate the character through the keymap. */
      ch = keymap[scan_code][shift_state];
      if (ch == (unsigned)SHIFT)
	{
	  shift_state = 1;
	  continue;
	}
      if (ch == 0)
	continue;

      Proc::sti_restore(old_s);
      return ch;
    }
}
