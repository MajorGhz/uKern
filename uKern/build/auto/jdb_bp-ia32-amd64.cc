// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_bp.h"
#include "jdb_bp_i.h"

#line 22 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"

Mword Jdb_bp::dr7;

#line 51 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"


int
Jdb_bp::global_breakpoints()
{
  return 1;
}

#line 58 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"


int
Jdb_bp::set_debug_address_register(int num, Mword addr, Mword len,
				   Breakpoint::Mode mode, Space *)
{
  clr_dr7(num, dr7);
  set_dr7(num, len, mode, dr7);
  switch (num)
    {
    case 0: write_debug_register(0, addr); break;
    case 1: write_debug_register(1, addr); break;
    case 2: write_debug_register(2, addr); break;
    case 3: write_debug_register(3, addr); break;
    default:;
    }
  return 1;
}

#line 76 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"


void
Jdb_bp::clr_debug_address_register(int num)
{
  clr_dr7(num, dr7);
}

#line 83 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"


void
Jdb_bp::at_jdb_enter()
{
  dr7 = read_debug_register(7);
  // disable breakpoints while we are in kernel debugger
  write_debug_register(7, dr7 & Val_enter);
}

#line 92 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"


void
Jdb_bp::at_jdb_leave()
{
  write_debug_register(6, Val_leave);
  write_debug_register(7, dr7);
}

#line 100 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"

/** @return 1 if single step occured */

int
Jdb_bp::test_sstep()
{
  Mword dr6 = read_debug_register(6);
  if (!(dr6 & Val_test_sstep))
    return 0;

  // single step has highest priority, don't consider other conditions
  write_debug_register(6, Val_leave);
  return 1;
}

#line 114 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"

/** @return 1 if breakpoint occured */

int
Jdb_bp::test_break(char *errbuf, size_t bufsize)
{
  Mword dr6 = read_debug_register(6);
  if (!(dr6 & Val_test))
    return 0;

  int ret = test_break(dr6, errbuf, bufsize);
  write_debug_register(6, dr6 & ~Val_test);
  return ret;
}

#line 128 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"

/** @return 1 if other debug exception occured */

int
Jdb_bp::test_other(char *errbuf, size_t bufsize)
{
  Mword dr6 = read_debug_register(6);
  if (!(dr6 & Val_test_other))
    return 0;

  snprintf(errbuf, bufsize, "unknown trap 1 (dr6=" L4_PTR_FMT ")", dr6);
  write_debug_register(6, Val_leave);
  return 1;
}

#line 142 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"

/** @return 0 if only breakpoints were logged and jdb should not be entered */

int
Jdb_bp::test_log_only()
{
  Mword dr6 = read_debug_register(6);

  if (dr6 & Val_test)
    {
      dr7 = read_debug_register(7);
      // disable breakpoints -- we might trigger a r/w breakpoint again
      write_debug_register(7, dr7 & Val_enter);
      test_log(dr6);
      write_debug_register(6, dr6);
      write_debug_register(7, dr7);
      if (!(dr6 & Val_test_other))
	// don't enter jdb, breakpoints only logged
	return 1;
    }
  // enter jdb
  return 0;
}

#line 165 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"


void
Jdb_bp::init_arch()
{
  Jdb::bp_test_log_only = test_log_only;
  Jdb::bp_test_break    = test_break;
  Jdb::bp_test_sstep    = test_sstep;
  Jdb::bp_test_other    = test_other;
}
