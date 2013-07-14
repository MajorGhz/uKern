// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_handler_queue_h
#define jdb_handler_queue_h

//
// INTERFACE definition follows 
//

#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_handler_queue.cpp"

// XXX If there is a constructor needed for this class make sure that it is
//     called with a priority higher than JDB_MODULE_INIT_PRIO!

class Jdb_handler
{
  friend class Jdb_handler_queue;
  
public:
  Jdb_handler( void (*handler)() ) : handler(handler), next(0) {}
  void execute() { handler(); }

private:
  void (*handler)();
  Jdb_handler *next;
};
#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_handler_queue.cpp"

class Jdb_handler_queue
{
private:
  Jdb_handler *first;

public:  
#line 28 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_handler_queue.cpp"
  inline void
  add(Jdb_handler *handler);
  
#line 36 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_handler_queue.cpp"
  void
  execute() const;
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 26 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_handler_queue.cpp"


inline void
Jdb_handler_queue::add(Jdb_handler *handler)
{
  handler->next = first;
  first = handler;
}

#endif // jdb_handler_queue_h
