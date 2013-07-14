// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_core_h
#define jdb_core_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"

#include "static_init.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#include "jdb_module.h"

//
// INTERFACE definition follows 
//

#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"

/**
 * The core of the modularized Jdb.
 * @see Jdb_module
 * @see Jdb_category
 *
 * This class provides the core functions for handling
 * Jdb_modules and providing them with the right input.
 *
 */
class Jdb_core
{
public:

  /**
   * The command structure for Jdb_core.
   *
   * This structure consists of a pointer to the Jdb_module
   * and a Jdb_module::Cmd structure. It is used in exec_cmd()
   * and returned from has_cmd().
   */
  struct Cmd
  {
    /**
     * Pointer to the module providing this command.
     */
    Jdb_module            *mod;

    /**
     * The Jdb_module::Cmd structure, describing the command.
     *
     * If this is a null pointer the command is invalid.
     * @see Jdb_module
     * @see Jdb_module::Cmd
     */
    Jdb_module::Cmd const *cmd;

    /**
     * Create a Jdb_core::Cmd.
     * @param _mod the Jdb_module providing the command.
     * @param _cmd the command structure (see Jdb_module::Cmd).
     */
    Cmd(Jdb_module *_mod, Jdb_module::Cmd const *_cmd = 0)
      : mod(_mod), cmd(_cmd)
    {}
  };

  /**
   * Get the command structure accoring to the given name.
   * @param cmd the command to look for.
   * @return A valid Cmd structure if cmd was found, or a
   *         Cmd structure where Cmd::cmd is a null pointer if
   *         no module provides such a command.
   */
  static Cmd has_cmd(char const *cmd);

  /**
   * Execute the command according to cmd.
   * @param cmd the command structure (see Jdb_core::Cmd), which
   *        describes the command to execute.
   * @return 0 if Jdb_module::action() returned LEAVE
   *         1 if Jdb_module::action() returned NOTHING
   *         2 if Jdb_module::action() returned GO_BACK (KEY_HOME entered)
   *         3 if the input was aborted (KEY_ESC entered) or was invalid
   *
   * This method is actually responsible for reading the input
   * with respect to the commands format string and calling
   * the Jdb_module::action() method after that.
   *
   */
  static int exec_cmd(Cmd const cmd, char const *str, int push_next_char = -1);

  /**
   * Overwritten getchar() to be able to handle next_char.
   */
  static int getchar(void);

  /**
   * Call this function every time a `\n' is written to the
   *        console and it stops output when the screen is full.
   * @return 0 if user wants to abort the output (escape or 'q' pressed)
   */
  static int new_line(unsigned &line);

  static void prompt_start();
  static void prompt_end();
  static void prompt();
  static int  prompt_len();
  static void update_prompt();
  static int set_prompt_color(char v);

  /**
   * Like strlen but do not count ESC sequences.
   */
  static unsigned print_len(const char *s);

  static char esc_prompt[];


public:
  static bool short_mode;
  typedef int (Input_fmt)(char fmt, int *size, char const *cmd_str, void *buf);

private:
  static int  next_char;
  static Input_fmt *_fmt_list[26];

public:  
#line 158 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
  static bool
  add_fmt_handler(char fmt, Input_fmt* hdlr);
  
#line 172 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
  static void
  print_prompt();
  
#line 234 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
  static int
  get_ansi_color(char c);
  
#line 297 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
  static unsigned
  print_alternatives(char const *prefix);
  
#line 326 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
  static Jdb_core::Cmd
  complete_cmd(char const *prefix, bool &multi_match);
  
#line 365 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
  static int
  cmd_getchar(char const *&str);

private:  
#line 285 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
  static unsigned
  match_len(char const *a, char const *b, unsigned l);
  
#line 388 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
  static inline void
  cmd_putchar(int c);
};
#line 112 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"

#define JDB_ANSI_black        "30"
#line 114 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#define JDB_ANSI_gray         "30;1"
#line 115 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#define JDB_ANSI_red          "31"
#line 116 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#define JDB_ANSI_lightred     "31;1"
#line 117 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#define JDB_ANSI_green        "32"
#line 118 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#define JDB_ANSI_lightgreen   "32;1"
#line 119 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#define JDB_ANSI_brown        "33"
#line 120 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#define JDB_ANSI_yellow       "33;1"
#line 121 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#define JDB_ANSI_blue         "34"
#line 122 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#define JDB_ANSI_lightblue    "34;1"
#line 123 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#define JDB_ANSI_magenta      "35"
#line 124 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#define JDB_ANSI_lightmagenta "35;1"
#line 125 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#define JDB_ANSI_cyan         "36"
#line 126 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#define JDB_ANSI_lightcyan    "36;1"
#line 127 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#define JDB_ANSI_white        "37"
#line 128 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#define JDB_ANSI_brightwhite  "37;1"
#line 129 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#define JDB_ANSI_default      ""
#line 130 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"

#define JDB_ANSI_COLOR(color)   "\033[" JDB_ANSI_##color "m"
#line 132 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_core.cpp"

#define JDB_ANSI_END          "\033[m"

#endif // jdb_core_h
