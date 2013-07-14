// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "terminate.h"
#include "terminate_i.h"


#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/terminate.cpp"
/**
 * The exit handler as long as exit_question() is not installed.
 */

static void
raw_exit();
#line 29 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/terminate.cpp"


static void (*exit_question)(void) = &raw_exit;
#line 37 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/terminate.cpp"


extern "C" void FIASCO_NORETURN _exit(int);

#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/terminate.cpp"

/**
 * The exit handler as long as exit_question() is not installed.
 */

static void
raw_exit()
{
  // make sure that we don't acknowledg the exit question automatically
  Kconsole::console()->change_state(Console::PUSH, 0,
                                    ~Console::INENABLED, 0);
  puts("\nPress any key to reboot.");
  Kconsole::console()->getchar();
  puts("\033[1mRebooting.\033[m");
  //  Cpu::busy_wait_ns(10000000);
  platform_reset();
}

#line 32 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/terminate.cpp"

void set_exit_question(void (*eq)(void))
{
  exit_question = eq;
}

#line 40 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/terminate.cpp"

FIASCO_NORETURN
void
terminate(int exit_value)
{
  Helping_lock::threading_system_active = false;

  if (exit_question)
    exit_question();

  puts("\nShutting down...");

  _exit(exit_value);
}
