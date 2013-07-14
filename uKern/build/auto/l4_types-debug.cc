// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "l4_types.h"
#include "l4_types_i.h"


#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/l4_types-debug.cpp"

void L4_timeout::print() const
{
  printf("m=%ld e=%ld", man(), exp());
}

#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/l4_types-debug.cpp"

void L4_timeout_pair::print() const
{
  printf("snd: ");
  snd.print();
  printf(" rcv: ");
  rcv.print();
}

#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/l4_types-debug.cpp"


void
Utcb::print() const
{
  puts("Values:");
  for (unsigned i = 0; i < Max_words; ++i)
    printf("%2d:%16lx%c", i, values[i], !((i+1) % 4) ? '\n' : ' ');
  if (Max_words % 4)
    puts("");
  printf("Reserved:   %16lx\n", utcb_addr);

  printf("Buffers:  desc=%16lx\n", buf_desc.raw());
  for (unsigned i = 0; i < sizeof(buffers) / sizeof(buffers[0]); ++i)
    printf("%2d:%16lx%c", i, buffers[i], !((i+1) % 4) ? '\n' : ' ');
  if ((sizeof(buffers) / sizeof(buffers[0])) % 4)
    puts("");

  printf("Xfer timeout: ");
  xfer.print();
  puts("");

  printf("Error:       %16lx\n", error.raw());
  printf("User values: %16lx %16lx %16lx\n", user[0], user[1], user[2]);
}
