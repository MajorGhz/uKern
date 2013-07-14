// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kern_cnt_h
#define kern_cnt_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kern_cnt.cpp"

#include "types.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kern_cnt.cpp"

class Kern_cnt
{
private:
  enum {
    Max_slot = 2,
  };

  static Mword *kcnt[Max_slot];
  static Mword (*read_kcnt_fn[Max_slot])();

public:  
#line 30 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kern_cnt.cpp"
  static Mword*
  get_ctr(int num);
  
#line 40 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kern_cnt.cpp"
  static const char *
  get_str(Mword num);
  
#line 62 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kern_cnt.cpp"
  static int
  mode(Mword slot, const char **mode, const char **name, Mword *event);
  
#line 89 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kern_cnt.cpp"
  static int
  setup_pmc(Mword slot, Mword event);

private:  
#line 26 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kern_cnt.cpp"
  static Mword read_kcnt1();
  
#line 27 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kern_cnt.cpp"
  static Mword read_kcnt2();
};

#endif // kern_cnt_h
