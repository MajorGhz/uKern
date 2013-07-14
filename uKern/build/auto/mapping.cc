// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "mapping.h"
#include "mapping_i.h"


#line 163 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping.cpp"

/** Parent.
    @return parent mapping of this mapping.
 */
Mapping *
Mapping::parent()
{
  if (depth() <= Depth_root)
    return 0;			// Sigma0 mappings don't have a parent.

  // Iterate over mapping entries of this tree backwards until we find
  // an entry with a depth smaller than ours.  (We assume here that
  // "special" depths (empty, end) are larger than Depth_max.)
  Mapping *m = this - 1;

  // NOTE: Depth_unused / Depth_submap are high, so no need to test
  // for them
  while (m->depth() >= depth())
    m--;

  return m;
}
