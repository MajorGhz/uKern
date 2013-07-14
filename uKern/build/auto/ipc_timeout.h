// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef ipc_timeout_h
#define ipc_timeout_h
#line 3 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_timeout.cpp"

#include "timeout.h"

//
// INTERFACE definition follows 
//

#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_timeout.cpp"

class Receiver;
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_timeout.cpp"

class IPC_timeout : public Timeout
{
  friend class Jdb_list_timeouts;

public:  
#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_timeout.cpp"
  /**
   * IPC_timeout constructor
   */
  
  inline IPC_timeout();
  
#line 27 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_timeout.cpp"
  /**
   * IPC_timeout destructor
   */
  
  virtual inline ~IPC_timeout();

private:  
#line 37 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_timeout.cpp"
  inline Receiver *
  owner();
  
#line 48 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_timeout.cpp"
  /**
   * Timeout expiration callback function
   * @return true if reschedule is necessary, false otherwise
   */
  
  bool
  expired();
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_timeout.cpp"
#include "globals.h"
#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_timeout.cpp"
#include "receiver.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_timeout.cpp"

/**
 * IPC_timeout constructor
 */

inline IPC_timeout::IPC_timeout()
{}

#line 35 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_timeout.cpp"


inline Receiver *
IPC_timeout::owner()
{
  // We could have saved our context in our constructor, but computing
  // it this way is easier and saves space. We can do this as we know
  // that IPC_timeouts are always created on the kernel stack of the
  // owner context.

  return reinterpret_cast<Receiver *>(context_of (this));
}

#line 26 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ipc_timeout.cpp"

/**
 * IPC_timeout destructor
 */

inline IPC_timeout::~IPC_timeout()
{
  owner()->set_timeout (0);	// reset owner's timeout field
}

#endif // ipc_timeout_h
