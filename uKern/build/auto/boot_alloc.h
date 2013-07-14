// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef boot_alloc_h
#define boot_alloc_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/boot_alloc.cpp"

#include <cstddef>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/boot_alloc.cpp"
#include <cxx/slist>
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/boot_alloc.cpp"
#include <cxx/type_traits>

//
// INTERFACE definition follows 
//

#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/boot_alloc.cpp"

class Boot_alloced
{
private:
  enum { Debug_boot_alloc };
  struct Block : cxx::S_list_item
  { size_t size; };

  typedef cxx::S_list_bss<Block> Block_list;

  static Block_list _free;

public:  
#line 40 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/boot_alloc.cpp"
  static void *
  alloc(size_t size);
  
#line 96 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/boot_alloc.cpp"
  inline void *
  operator new(size_t size) throw();
  
#line 100 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/boot_alloc.cpp"
  inline void *
  operator new[](size_t size) throw();
  
#line 104 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/boot_alloc.cpp"
  void
  operator delete(void *b);
  
#line 110 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/boot_alloc.cpp"
  void
  operator delete[](void *b);
};
#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/boot_alloc.cpp"

template< typename Base >
class Boot_object : public Base, public Boot_alloced
{
public:
  Boot_object()  = default;

  template< typename... A >
  Boot_object(A&&... args) : Base(cxx::forward<A>(args)...) {}
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 95 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/boot_alloc.cpp"

inline void *
Boot_alloced::operator new(size_t size) throw()
{ return alloc(size); }

#line 99 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/boot_alloc.cpp"

inline void *
Boot_alloced::operator new[](size_t size) throw()
{ return alloc(size); }

#endif // boot_alloc_h
