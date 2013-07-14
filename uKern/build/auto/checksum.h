// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef checksum_h
#define checksum_h

//
// INTERFACE definition follows 
//

#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/checksum.cpp"

class Checksum 
{

public:  
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/checksum.cpp"
  // calculate simple checksum over kernel text section and read-only data
  
  static unsigned get_checksum_ro();
  
#line 27 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/checksum.cpp"
  static bool
  check_ro();
  
#line 32 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/checksum.cpp"
  // calculate simple checksum over kernel data section
  
  static unsigned get_checksum_rw();
};

#endif // checksum_h
