// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef boot_info_h
#define boot_info_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/boot_info.cpp"

#include "initcalls.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"

#include "types.h"

//
// INTERFACE definition follows 
//

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/boot_info.cpp"

class Boot_info
{
public:
  static void init() FIASCO_INIT;

#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"
private:

private:
  static unsigned _flag;
  static unsigned _checksum_ro;
  static unsigned _checksum_rw;

public:  
#line 29 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"
  /// \defgroup pre init setup
  /**
   * The Boot_info object must be set up with these functions
   * before Boot_info::init() is called!
   * This can be done either in __main, if booted on hardware
   * or in an initializer with a higher priority than BOOT_INFO_INIT_PRIO
   * (e.g UX_STARTUP1_INIT_PRIO) if the kernel runs on software (FIASCO-UX)
   */
  //@{
  
  
  static inline void set_flags(unsigned aflags);
  
#line 44 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"
  static inline void set_checksum_ro(unsigned ro_cs);
  
#line 48 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"
  static inline void set_checksum_rw(unsigned rw_cs);
  
#line 59 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"
  static inline unsigned
  get_flags(void);
  
#line 66 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"
  static inline unsigned
  get_checksum_ro(void);
  
#line 73 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"
  static inline unsigned
  get_checksum_rw(void);
  
#line 80 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"
  static void
  reset_checksum_ro(void);
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 27 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"


/// \defgroup pre init setup
/**
 * The Boot_info object must be set up with these functions
 * before Boot_info::init() is called!
 * This can be done either in __main, if booted on hardware
 * or in an initializer with a higher priority than BOOT_INFO_INIT_PRIO
 * (e.g UX_STARTUP1_INIT_PRIO) if the kernel runs on software (FIASCO-UX)
 */
//@{


inline void Boot_info::set_flags(unsigned aflags)
{  _flag = aflags; }

#line 42 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"


inline void Boot_info::set_checksum_ro(unsigned ro_cs)
{  _checksum_ro = ro_cs; }

#line 46 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"


inline void Boot_info::set_checksum_rw(unsigned rw_cs)
{  _checksum_rw = rw_cs; }

#line 57 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"


inline unsigned
Boot_info::get_flags(void)
{
  return _flag;
}

#line 64 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"


inline unsigned
Boot_info::get_checksum_ro(void)
{
  return _checksum_ro;
}

#line 71 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"


inline unsigned
Boot_info::get_checksum_rw(void)
{
  return _checksum_rw;
}

#endif // boot_info_h
