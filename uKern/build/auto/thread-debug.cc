// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "thread.h"
#include "thread_i.h"

#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-debug.cpp"

//--------------------------------------------------------------------------

#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-debug.cpp"


//---------------------------------------------------------------------------


#line 27 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/thread-debug.cpp"


unsigned
Thread::Log_thread_exregs::print(int max, char *buf) const
{
  return snprintf(buf, max, "D=%lx ip=%lx sp=%lx op=%s%s%s",
                  id, ip, sp,
                  op & Exr_cancel ? "Cancel" : "",
                  ((op & (Exr_cancel | Exr_trigger_exception))
                   == (Exr_cancel | Exr_trigger_exception))
                   ? ","
                   : ((op & (Exr_cancel | Exr_trigger_exception))
                      == 0 ? "0" : "") ,
                  op & Exr_trigger_exception ? "TrExc" : "");
}
