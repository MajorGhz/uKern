// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef apic_i_h
#define apic_i_h
#line 102 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "cpu.h"
#line 168 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

#include <cassert>
#line 170 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include <cstdio>
#line 171 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include <cstdlib>
#line 172 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include <cstring>
#line 173 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

#include "config.h"
#line 176 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "cpu_lock.h"
#line 177 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "entry_frame.h"
#line 178 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "globals.h"
#line 179 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "io.h"
#line 180 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "kmem.h"
#line 181 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "kip.h"
#line 182 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "lock_guard.h"
#line 183 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "panic.h"
#line 184 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "processor.h"
#line 185 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "regdefs.h"
#line 186 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "pic.h"
#line 187 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "pit.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/apic-debug.cpp"

#include <cstdio>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/apic-debug.cpp"
#include "simpleio.h"

//
// IMPLEMENTATION of inline functions follows
//


#line 210 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline Unsigned32
Apic::get_version()
{
  return reg_read(APIC_lvr) & 0xFF;
}

#line 349 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

// test if APIC present

inline int
Apic::test_present()
{
  return cpu().features() & FEAT_APIC;
}

#endif // apic_i_h
