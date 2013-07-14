// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "kip.h"
#include "kip_i.h"

#line 50 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"

//============================================================================

#line 141 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"

Kip *Kip::global_kip;
#line 164 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"

asm(".section .initkip.version, \"a\", %progbits        \n"	\
    ".string \"" CONFIG_KERNEL_VERSION_STRING "\"       \n"	\
    ".previous                                          \n");
#line 168 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"

asm(".section .initkip.features.fini, \"a\", %progbits  \n"	\
    ".string \"\"                                       \n"	\
    ".previous                                          \n");

#line 121 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"


Mem_desc *Kip::add_mem_region(Mem_desc const &md)
{
  Mem_desc *m = mem_descs();
  Mem_desc *end = m + num_mem_descs();
  for (;m<end;++m)
    {
      if (m->type() == Mem_desc::Undefined)
	{
	  *m = md;
	  return m;
	}
    }

  // Add mem region failed -- must be a Fiasco startup problem.  Bail out.
  panic("Too few memory descriptors in KIP");

  return 0;
}

#line 143 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"


void Kip::init_global_kip(Kip *kip)
{
  global_kip = kip;

  kip->platform_info.is_mp = Config::Max_num_cpus > 1;

  // check that the KIP has actually been set up
  //assert(kip->sigma0_ip && kip->root_ip && kip->user_ptr);
}

#line 156 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/abi/kip.cpp"


char const *Kip::version_string() const
{
  static_assert((sizeof(Kip) & 0xf) == 0, "Invalid KIP structure size");

  return reinterpret_cast <char const *> (this) + (offset_version_strings << 4);
}
