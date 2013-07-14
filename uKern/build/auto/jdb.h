// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_h
#define jdb_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"

#include "l4_types.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "jdb_core.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "jdb_handler_queue.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "per_cpu_data.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

#include "l4_types.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "pic.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"

#include "jdb_core.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"
#include "jdb_handler_queue.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"
#include "jdb_entry_frame.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"
#include "trap_state.h"

//
// INTERFACE definition follows 
//

#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"

class Context;
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
class Thread;
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
class Push_console;
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"

class Jdb_entry_frame;
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

class Trap_state;
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
class Thread;
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
class Console_buffer;
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
class Jdb_entry_frame;
#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
class Push_console;
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"

class Space;
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"
class Thread;
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-thread.cpp"

class Space;
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"

class Jdb : public Jdb_core
{
public:
  static Per_cpu<Jdb_entry_frame*> entry_frame;
  static Cpu_number current_cpu;
  static Per_cpu<void (*)(Cpu_number, void *)> remote_func;
  static Per_cpu<void *> remote_func_data;
  static Per_cpu<bool> remote_func_running;

  static int FIASCO_FASTCALL enter_jdb(Jdb_entry_frame *e, Cpu_number cpu);
  static void cursor_end_of_screen();
  static void cursor_home();
  static void printf_statline(const char *prompt, const char *help,
                              const char *format, ...)
  __attribute__((format(printf, 3, 4)));
  static void save_disable_irqs(Cpu_number cpu);
  static void restore_irqs(Cpu_number cpu);

private:
  Jdb();			// default constructors are undefined
  Jdb(const Jdb&);

  static char hide_statline;
  static char last_cmd;
  static char next_cmd;
  static Per_cpu<char[81]> error_buffer;
  static bool was_input_error;

  static Thread  *current_active;

  static const char *toplevel_cmds;
  static const char *non_interactive_cmds;

  // state for traps in JDB itself
  static Per_cpu<bool> running;
  static bool in_service;
  static bool leave_barrier;
  static unsigned long cpus_in_debugger;
  static bool never_break;
  static bool jdb_active;

  static void enter_trap_handler(Cpu_number cpu);
  static void leave_trap_handler(Cpu_number cpu);
  static bool handle_conditional_breakpoint(Cpu_number cpu);
  static void handle_nested_trap(Jdb_entry_frame *e);
  static bool handle_user_request(Cpu_number cpu);
  static bool handle_debug_traps(Cpu_number cpu);
  static bool test_checksums();

public:
  static Jdb_handler_queue jdb_enter;
  static Jdb_handler_queue jdb_leave;

  // esc sequences for highligthing
  static char  esc_iret[];
  static char  esc_bt[];
  static char  esc_emph[];
  static char  esc_emph2[];
  static char  esc_mark[];
  static char  esc_line[];
  static char  esc_symbol[];


#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
private:

public:
  enum
  {
    Msr_test_default     = 0,
    Msr_test_fail_warn   = 1,
    Msr_test_fail_ignore = 2,
  };

  static void init();

  static Per_cpu<unsigned> apic_tpr;
  static Pic::Status pic_status;
  static volatile char msr_test;
  static volatile char msr_fail;

  typedef enum
    {
      s_unknown, s_ipc, s_syscall, s_pagefault, s_fputrap,
      s_interrupt, s_timer_interrupt, s_slowtrap, s_user_invoke,
    } Guessed_thread_state;


  static int (*bp_test_log_only)();
  static int (*bp_test_sstep)();
  static int (*bp_test_break)(char *errbuf, size_t bufsize);
  static int (*bp_test_other)(char *errbuf, size_t bufsize);

private:

  static char _connected;
  static Per_cpu<char> permanent_single_step;
  static Per_cpu<char> code_ret, code_call, code_bra, code_int;

  typedef enum
    {
      SS_NONE=0, SS_BRANCH, SS_RETURN
    } Step_state;

  static Per_cpu<Step_state> ss_state;
  static Per_cpu<int> ss_level;

  static const Unsigned8 *debug_ctrl_str;
  static int              debug_ctrl_len;

  static Per_cpu<int> jdb_irqs_disabled;

#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"
private:

public:
  enum
  {
    NOFANCY=0,
    FANCY=1
  };

  enum Direction
  {
    Cursor_up = 'A',
    Cursor_down = 'B',
    Cursor_right = 'C',
    Cursor_left = 'D'
  };

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-thread.cpp"
private:

public:
  /**
   * Deliver Thread object which was active at entry of kernel debugger.
   * If we came from the kernel itself, return Thread with id 0.0
   */
  static Thread *get_thread(Cpu_number cpu);

public:  
#line 132 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  static bool
  cpu_in_jdb(Cpu_number cpu);
  
#line 139 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  template< typename Func > static void
  foreach_cpu(Func const &f);
  
#line 152 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  template< typename Func > static bool
  foreach_cpu(Func const &f, bool positive);
  
#line 173 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  static inline void
  set_next_cmd(char cmd);
  
#line 178 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  static inline int
  was_last_cmd();
  
#line 183 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  static inline int
  get_next_cmd();
  
#line 187 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  /** Command aborted. If we are interpreting a debug command like
   *  enter_kdebugger("*#...") this is an error
   */
  
  static void
  abort_command();
  
#line 242 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  static bool is_toplevel_cmd(char c);
  
#line 258 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  static int
  execute_command(const char *s, int first_char = -1);
  
#line 270 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  static Push_console *
  push_cons();
  
#line 578 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  static void
  remote_work(Cpu_number cpu, void (*func)(Cpu_number, void *), void *data,
                   bool sync = true);
  
#line 611 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  static int
  getchar(void);
  
#line 631 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  //-------- pretty print functions ------------------------------
  
  static void
  write_ll_ns(Signed64 ns, char *buf, int maxlen, bool sign);
  
#line 702 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  static void
  write_ll_hex(Signed64 x, char *buf, int maxlen, bool sign);
  
#line 718 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  static void
  write_ll_dec(Signed64 x, char *buf, int maxlen, bool sign);
  
#line 737 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  static inline Thread*
  get_current_active();
  
#line 744 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  static inline Jdb_entry_frame*
  get_entry_frame(Cpu_number cpu);
  
#line 750 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  /// handling of standard cursor keys (Up/Down/PgUp/PgDn)
  
  static int
  std_cursor_key(int c, Mword cols, Mword lines, Mword max_absy, Mword *absy,
                      Mword *addy, Mword *addx, bool *redraw);
  
#line 890 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  static inline Space *
  get_task(Cpu_number cpu);
  
#line 900 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  //
  // memory access wrappers
  //
  
  
  
  template< typename T > static bool
  peek(T const *addr, Space *task, T &value);
  
#line 920 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  template< typename T > static bool
  poke(T *addr, Space *task, T const &value);
  
#line 200 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  static inline bool
  connected();
  
#line 343 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  static Space *
  translate_task(Address addr, Space *task);
  
#line 350 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  static void
  peek_phys(Address phys, void *value, int width);
  
#line 361 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  static void
  poke_phys(Address phys, void const *value, int width);
  
#line 373 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  static int
  peek_task(Address addr, Space *task, void *value, int width);
  
#line 411 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  static int
  poke_task(Address addr, Space *task, void const *value, int width);
  
#line 447 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  // The content of apdapter memory is not shown by default because reading
  // memory-mapped I/O registers may confuse the hardware. We assume that all
  // memory above the end of the RAM is adapter memory.
  
  static int
  is_adapter_memory(Address virt, Space *task);
  
#line 489 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  // Try to guess the thread state of t by walking down the kernel stack and
  // locking at the first return address we find.
  
  static Jdb::Guessed_thread_state
  guess_thread_state(Thread *t);
  
#line 542 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  static void
  set_single_step(Cpu_number cpu, int on);
  
#line 990 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  static inline void
  enter_getchar();
  
#line 995 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  static inline void
  leave_getchar();
  
#line 33 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"
  static inline void
  cursor( Direction d, unsigned n = 1);
  
#line 41 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"
  static void
  cursor(unsigned int row=0, unsigned int col=0);
  
#line 51 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"
  static inline void
  blink_cursor(unsigned int row, unsigned int col);
  
#line 58 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"
  static inline void
  cursor_save();
  
#line 65 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"
  static inline void
  cursor_restore();
  
#line 72 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"
  static inline void
  screen_erase();
  
#line 79 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"
  static void
  screen_scroll(unsigned int start, unsigned int end);
  
#line 89 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"
  static inline void
  clear_to_eol();
  
#line 95 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"
  // preserve the history of the serial console if fancy != 0
  
  static void
  clear_screen(int fancy=FANCY);
  
#line 21 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"
  static void
  write_tsc_s(Signed64 tsc, char *buf, int maxlen, bool sign);
  
#line 82 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"
  static void
  write_tsc(Signed64 tsc, char *buf, int maxlen, bool sign);
  
#line 92 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"
  static int
  get_register(char *reg);
  
#line 67 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-thread.cpp"
  static void
  get_current(Cpu_number cpu);
  
#line 74 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-thread.cpp"
  static inline Space*
  get_current_space();

protected:  
#line 208 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  template< typename T > static inline void
  set_monitored_address(T *dest, T val);
  
#line 216 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  template< typename T > static inline T
  monitor_address(Cpu_number current_cpu, T *addr);

private:  
#line 277 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  // Interprete str as non interactive commands for Jdb. We allow mostly 
  // non-interactive commands here (e.g. we don't allow d, t, l, u commands)
  
  static int
  execute_command_ni(Space *task, char const *str, int len = 1000);
  
#line 324 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  static bool
  input_short_mode(Jdb::Cmd *cmd, char const **args, int &cmd_key);
  
#line 418 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  static bool
  input_long_mode(Jdb::Cmd *cmd, char const **args);
  
#line 501 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  static int
  execute_command();
  
#line 533 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  static bool
  open_debug_console(Cpu_number cpu);
  
#line 553 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  static void
  close_debug_console(Cpu_number cpu);
  
#line 982 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  static inline void
  rcv_uart_enable();
  
#line 1144 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  static bool
  stop_all_cpus(Cpu_number);
  
#line 1150 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  static void
  leave_wait_for_others();
  
#line 1155 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  static bool
  check_for_cpus(bool);
  
#line 1160 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  static inline int
  remote_work_ipi_process(Cpu_number);
  
#line 77 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  static void init_serial_console();
  
#line 231 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  static inline void
  backspace();
  
#line 554 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  static bool
  handle_special_cmds(int c);
  
#line 600 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  // take a look at the code of the current thread eip
  // set global indicators code_call, code_ret, code_bra, code_int
  // This can fail if the current page is still not mapped
  static void
  analyze_code(Cpu_number cpu);
  
#line 656 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  // entered debugger because of single step trap
  static inline int
  handle_single_step(Cpu_number cpu);
  
#line 714 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  // entered debugger due to debug exception
  static inline int
  handle_trap1(Cpu_number cpu);
  
#line 736 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  // entered debugger due to software breakpoint
  static inline int
  handle_trap3(Cpu_number cpu);
  
#line 805 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  // entered debugger due to other exception
  static inline int
  handle_trapX(Cpu_number cpu);
  
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-int3-ia32-amd64.cpp"
  /**
   * Handle int3 extensions in the current thread's context. All functions
   * for which we don't need/want to switch to the debugging stack.
   * \return 0 if this function should be handled in the context of Jdb
   *         1 successfully handled
   */
  
  static int
  handle_int3_threadctx(Trap_state *ts);
  
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-int3-ia32-ux.cpp"
  /**
   * Handle int3 extensions in the current thread's context. All functions
   * for which we don't need/want to switch to the debugging stack.
   * \return 0 if this function should be handled in the context of Jdb
   *         1 successfully handled
   */
  
  static int
  handle_int3_threadctx_generic(Trap_state *ts);
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 80 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"

#include <cstdio>
#line 82 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
#include <cstring>
#line 83 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
#include <simpleio.h>
#line 84 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"

#include "config.h"
#line 86 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "delayloop.h"
#line 87 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "feature.h"
#line 88 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "jdb_core.h"
#line 89 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "jdb_entry_frame.h"
#line 90 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "jdb_screen.h"
#line 91 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "kernel_console.h"
#line 92 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "processor.h"
#line 93 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "push_console.h"
#line 94 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "static_init.h"
#line 95 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "keycodes.h"
#line 978 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"

#include "kernel_uart.h"
#line 991 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"

#include "ipi.h"
#line 993 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "logdefs.h"
#line 72 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

#include <cstdio>
#line 74 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "kernel_uart.h"
#line 98 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

#include <cstring>
#line 100 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include <csetjmp>
#line 101 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include <cstdarg>
#line 102 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include <climits>
#line 103 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include <cstdlib>
#line 104 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include <cstdio>
#line 105 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "simpleio.h"
#line 106 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

#include "apic.h"
#line 108 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "boot_info.h"
#line 109 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "checksum.h"
#line 110 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "config.h"
#line 111 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "cpu.h"
#line 112 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "initcalls.h"
#line 113 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "idt.h"
#line 114 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "io_apic.h"
#line 115 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "jdb_core.h"
#line 116 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "jdb_screen.h"
#line 117 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "kernel_console.h"
#line 118 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "keycodes.h"
#line 119 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "kernel_uart.h"
#line 120 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "kernel_task.h"
#line 121 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "kmem.h"
#line 122 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "koptions.h"
#line 123 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "logdefs.h"
#line 124 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "mem_layout.h"
#line 125 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "pic.h"
#line 126 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "push_console.h"
#line 127 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "processor.h"
#line 128 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "regdefs.h"
#line 129 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "static_init.h"
#line 130 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "terminate.h"
#line 131 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "thread.h"
#line 132 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "thread_state.h"
#line 133 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "timer.h"
#line 134 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "timer_tick.h"
#line 135 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "trap_state.h"
#line 136 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "vkey.h"
#line 137 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "watchdog.h"
#line 27 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"

#include <cstdio>
#line 29 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"
#include <simpleio.h>
#line 30 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"
#include "jdb_screen.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"

#include "config.h"
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"
#include "div32.h"
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"
#include "kernel_console.h"
#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"
#include "paging.h"
#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"
#include "jdb_screen.h"
#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-thread.cpp"

#include "jdb_prompt_ext.h"
#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-thread.cpp"
#include "jdb.h"
#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-thread.cpp"
#include "thread.h"
#line 62 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-thread.cpp"

#include "jdb.h"
#line 64 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-thread.cpp"
#include "thread.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-int3-ia32-amd64.cpp"

#include "thread.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-int3-ia32-ux.cpp"

#include "jdb_dbinfo.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-int3-ia32-ux.cpp"
#include "jdb_lines.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-int3-ia32-ux.cpp"
#include "jdb_symbol.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-int3-ia32-ux.cpp"
#include "jdb_tbuf.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-int3-ia32-ux.cpp"
#include "thread.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-int3-ia32-ux.cpp"
#include "timer.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 171 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


inline void
Jdb::set_next_cmd(char cmd)
{ next_cmd = cmd; }

#line 176 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


inline int
Jdb::was_last_cmd()
{ return last_cmd; }

#line 181 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


inline int
Jdb::get_next_cmd()
{ return next_cmd; }

#line 735 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


inline Thread*
Jdb::get_current_active()
{
  return current_active;
}

#line 742 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


inline Jdb_entry_frame*
Jdb::get_entry_frame(Cpu_number cpu)
{
  return entry_frame.cpu(cpu);
}

#line 888 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


inline Space *
Jdb::get_task(Cpu_number cpu)
{
  if (!get_thread(cpu))
    return 0;
  else
    return get_thread(cpu)->space();
}

#line 199 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

inline bool
Jdb::connected()
{
  return _connected;
}

#line 988 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"


inline void
Jdb::enter_getchar()
{}

#line 993 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"


inline void
Jdb::leave_getchar()
{}

#line 31 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"


inline void
Jdb::cursor( Direction d, unsigned n)
{
  printf("\033[%u%c", n, (char)d);
}

#line 49 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"


inline void
Jdb::blink_cursor(unsigned int row, unsigned int col)
{
  printf ("\033[%d;%df", row, col);
}

#line 56 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"


inline void
Jdb::cursor_save()
{
  putstr ("\0337");
}

#line 63 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"


inline void
Jdb::cursor_restore()
{
  putstr ("\0338");
}

#line 70 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"


inline void
Jdb::screen_erase()
{
  putstr ("\033[2J");
}   

#line 87 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"


inline void
Jdb::clear_to_eol()
{
  putstr("\033[K");
}

#line 72 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-thread.cpp"


inline Space*
Jdb::get_current_space()
{
  return current_active ? current_active->space() : 0;
}

#line 205 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"



template< typename T > inline void
Jdb::set_monitored_address(T *dest, T val)
{
  *dest = val;
}

#line 213 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"



template< typename T > inline T
Jdb::monitor_address(Cpu_number current_cpu, T *addr)
{
  if (!*addr && Cpu::cpus.cpu(current_cpu).has_monitor_mwait())
    {
      asm volatile ("monitor \n" : : "a"(addr), "c"(0), "d"(0) );
      Mword irq_sup = Cpu::cpus.cpu(current_cpu).has_monitor_mwait_irq() ? 1 : 0;
      asm volatile ("mwait   \n" : : "a"(0x00), "c"(irq_sup) );
    }

  return *addr;
}

//
// IMPLEMENTATION of function templates
//


#line 135 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"




template< typename Func > void
Jdb::foreach_cpu(Func const &f)
{
  for (Cpu_number i = Cpu_number::first(); i < Config::max_num_cpus(); ++i)
    {
      if (!Cpu::online(i) || !running.cpu(i))
	continue;
      f(i);
    }
}

#line 149 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"



template< typename Func > bool
Jdb::foreach_cpu(Func const &f, bool positive)
{
  bool r = positive;
  for (Cpu_number i = Cpu_number::first(); i < Config::max_num_cpus(); ++i)
    {
      if (!Cpu::online(i) || !running.cpu(i))
	continue;

      bool res = f(i);

      if (positive)
	r = r && res;
      else
	r = r || res;
    }

  return r;
}

#line 898 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


//
// memory access wrappers
//



template< typename T > bool
Jdb::peek(T const *addr, Space *task, T &value)
{
  // use an Mword here instead of T as some implementations of peek_task use
  // an Mword in their operation which is potentially bigger than T
  // XXX: should be fixed
  Mword tmp;
  bool ret = peek_task((Address)addr, task, &tmp, sizeof(T)) == 0;
  value = tmp;
  return ret;
}

#line 917 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"



template< typename T > bool
Jdb::poke(T *addr, Space *task, T const &value)
{ return poke_task((Address)addr, task, &value, sizeof(T)) == 0; }

#endif // jdb_h
