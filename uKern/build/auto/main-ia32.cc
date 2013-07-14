// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "main.h"
#include "main_i.h"


#line 42 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/main-ia32.cpp"
static void
exit_question();
#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/main-ia32.cpp"

static int exit_question_active;

#line 25 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/main-ia32.cpp"


extern "C" void __attribute__ ((noreturn))
_exit(int)
{
  if (exit_question_active)
    platform_reset();

  while (1)
    {
      Proc::halt();
      Proc::pause();
    }
}

#line 39 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/main-ia32.cpp"



static void
exit_question()
{
  Proc::cli();
  exit_question_active = 1;

  Pic::Status irqs = Pic::disable_all_save();
  if (Config::getchar_does_hlt_works_ok)
    {
      Timer_tick::set_vectors_stop();
      Timer_tick::enable(Cpu_number::boot_cpu()); // hmexit alway on CPU 0
      Proc::sti();
    }

  // make sure that we don't acknowledg the exit question automatically
  Kconsole::console()->change_state(Console::PUSH, 0, ~Console::INENABLED, 0);
  puts("\nReturn reboots, \"k\" enters L4 kernel debugger...");

  char c = Kconsole::console()->getchar();

  if (c == 'k' || c == 'K') 
    {
      Pic::restore_all(irqs);
      kdb_ke("_exit");
    }
  else
    {
      // It may be better to not call all the destruction stuff because of
      // unresolved static destructor dependency problems. So just do the
      // reset at this point.
      puts("\033[1mRebooting.\033[m");
    }
}

#line 75 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/main-ia32.cpp"

void
main_arch()
{
  // console initialization
  set_exit_question(&exit_question);

  //Pic::disable_all_save();
}
