// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "context.h"
#include "context_i.h"

#line 142 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context-vcpu.cpp"


// --------------------------------------------------------------------------


#line 148 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/context-vcpu.cpp"


unsigned
Context::Vcpu_log::print(int maxlen, char *buf) const
{
  switch (type)
    {
    case 0:
    case 4:
      return snprintf(buf, maxlen, "%sret pc=%lx sp=%lx state=%lx task=D:%lx",
	  type == 4 ? "f" : "", ip, sp, state, space);
    case 1:
      return snprintf(buf, maxlen, "ipc from D:%lx task=D:%lx sp=%lx",
	  Kobject_dbg::pointer_to_id((Kobject*)ip), state, sp);
    case 2:
      return snprintf(buf, maxlen, "exc #%x err=%lx pc=%lx sp=%lx state=%lx task=D:%lx",
	  (unsigned)trap, err, ip, sp, state, space);
    case 3:
      return snprintf(buf, maxlen, "pf  pc=%lx pfa=%lx state=%lx task=D:%lx",
	  ip, sp, state, space);
    default:
      return snprintf(buf, maxlen, "unknown");
    }
}
