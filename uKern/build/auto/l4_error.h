// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef l4_error_h
#define l4_error_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/l4_error.cpp"

#include "types.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/l4_error.cpp"

class L4_error
{
public:
  enum Error_code
  {
    None            = 0,
    Timeout         = 2,
    R_timeout       = 3,
    Not_existent    = 4,
    Canceled        = 6,
    R_canceled      = 7,
    Overflow        = 8,
    Snd_xfertimeout = 10,
    Rcv_xfertimeout = 12,
    Aborted         = 14,
    R_aborted       = 15,
    Map_failed      = 16,
  };

  enum Phase
  {
    Snd = 0,
    Rcv = 1
  };

  L4_error(Error_code ec = None, Phase p = Snd) : _raw(ec | p) {}
  L4_error(L4_error const &e, Phase p = Snd) : _raw(e._raw | p) {}

  bool ok() const { return _raw == 0; }

  Error_code error() const { return Error_code(_raw & 0x1e); }
  Mword raw() const { return _raw; }
  bool snd_phase() const { return !(_raw & Rcv); }

  static L4_error from_raw(Mword raw) { return L4_error(true, raw); }

private:
  L4_error(bool, Mword raw) : _raw(raw) {}
  Mword _raw;

public:  
#line 57 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/l4_error.cpp"
  char const *
  str_error();
};

#endif // l4_error_h
