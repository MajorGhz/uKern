// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef vkey_h
#define vkey_h

//
// INTERFACE definition follows 
//

#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vkey.cpp"

class Irq_base;
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vkey.cpp"

class Vkey
{
public:
  enum Echo_type { Echo_off = 0, Echo_on = 1, Echo_crnl = 2 };

public:  
#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vkey.cpp"
  static void
  irq(Irq_base *i);
  
#line 42 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vkey.cpp"
  static void
  set_echo(Echo_type echo);
  
#line 92 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vkey.cpp"
  static void
  add_char(int v);
  
#line 100 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vkey.cpp"
  static int
  check_();
  
#line 160 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vkey.cpp"
  static int
  get();
  
#line 170 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vkey.cpp"
  static void
  clear();

private:  
#line 49 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vkey.cpp"
  static bool
  add(int c);
  
#line 74 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vkey.cpp"
  static bool
  add(const char *seq);
  
#line 84 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vkey.cpp"
  static void
  trigger();
};

#endif // vkey_h
