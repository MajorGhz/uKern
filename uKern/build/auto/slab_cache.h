// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef slab_cache_h
#define slab_cache_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"

#include <spin_lock.h>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"
#include <cxx/hlist>
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"
#include <cxx/slist>
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"
#include <auto_quota.h>

//
// INTERFACE definition follows 
//

#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"

// The anonymous slab allocator.  You can specialize this allocator by
// providing your own initialization functions and your own low-level
// allocation functions.

class Slab : public cxx::H_list_item
{
private:
  Slab(const Slab&);	// copy constructors remain undefined

  typedef cxx::S_list_item Slab_entry;
  typedef cxx::S_list<Slab_entry> Free_list;

  Free_list _free;
  unsigned short _elems;
  unsigned short _in_use;

public:  
#line 75 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"
  Slab(unsigned elems, unsigned entry_size, void *mem);
  
#line 92 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"
  void *
  alloc();
  
#line 105 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"
  void
  free(void *entry);
  
#line 115 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"
  inline bool
  is_empty() const;
  
#line 122 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"
  inline bool
  is_full() const;
  
#line 129 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"
  inline unsigned
  in_use() const;
  
#line 136 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"
  inline void *
  operator new(size_t, void *block) throw();

private:  
#line 66 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"
  // default deallocator must not be called -- must use explicit destruction
  
  inline void 
  operator delete(void* /*block*/);
};
#line 24 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"

class Slab_cache
{
protected:
  friend class Slab;

  // Low-level allocator functions:

  // Allocate/free a block.  "size" is always a multiple of PAGE_SIZE.
  virtual void *block_alloc(unsigned long size, unsigned long alignment) = 0;
  virtual void block_free(void *block, unsigned long size) = 0;

private:
  Slab_cache();
  Slab_cache(const Slab_cache&); // default constructor is undefined

  //
  // data declaration follows
  // 

  typedef cxx::H_list<Slab> Slab_list;
  Slab_list _full;    ///< List of full slabs
  Slab_list _partial; ///< List of partially filled slabs
  Slab_list _empty;   ///< List of empty slabs


  unsigned long _slab_size;
  unsigned _entry_size, _elem_num;
  unsigned _num_empty;
  typedef Spin_lock<> Lock;
  Lock lock;
  char const *_name;

public:  
#line 146 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"
  static inline unsigned
  entry_size(unsigned elem_size, unsigned alignment);
  
#line 150 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"
  // 
  // Slab_cache
  // 
  
  inline Slab_cache(unsigned elem_size, 
  				 unsigned alignment,
  				 char const * name, 
  				 unsigned long min_size,
  				 unsigned long max_size);
  
#line 173 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"
  //
  // Slab_cache
  //
  
  inline Slab_cache(unsigned long slab_size,
  				 unsigned elem_size,
  				 unsigned alignment,
  				 char const * name);
  
#line 190 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"
  virtual ~Slab_cache();
  
#line 222 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"
  void *
  alloc();	// request initialized member from cache
  
  
#line 278 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"
  template< typename Q > inline void *
  q_alloc(Q *quota);
  
#line 294 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"
  void
  free(void *cache_entry); // return initialized member to cache
  
  
#line 341 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"
  template< typename Q > inline void
  q_free(Q *quota, void *obj);
  
#line 349 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"
  unsigned long
  reap();		// request that cache returns memory to system
  
  
#line 383 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"
  void
  debug_dump();

protected:  
#line 197 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"
  inline void
  destroy();	// descendant should call this in destructor
  

private:  
#line 203 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"
  inline Slab *
  get_available_locked();
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 113 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"


inline bool
Slab::is_empty() const
{
  return _in_use == 0;
}

#line 120 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"


inline bool
Slab::is_full() const
{
  return _in_use == _elems;
}

#line 127 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"


inline unsigned
Slab::in_use() const
{
  return _in_use;
}

#line 134 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"


inline void *
Slab::operator new(size_t, void *block) throw()
{
  // slabs must be size-aligned so that we can compute their addresses
  // from element addresses
  return block;
}

#line 143 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"



inline unsigned
Slab_cache::entry_size(unsigned elem_size, unsigned alignment)
{ return (elem_size + alignment - 1) & ~(alignment - 1); }

#line 149 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"

// 
// Slab_cache
// 

inline Slab_cache::Slab_cache(unsigned elem_size, 
				 unsigned alignment,
				 char const * name, 
				 unsigned long min_size,
				 unsigned long max_size)
  : _entry_size(entry_size(elem_size, alignment)), _num_empty(0),
    _name (name)
{
  lock.init();

  for (
      _slab_size = min_size;
      (_slab_size - sizeof(Slab)) / _entry_size < 8
        && _slab_size < max_size;
      _slab_size <<= 1) ;

  _elem_num = (_slab_size - sizeof(Slab)) / _entry_size;
}

#line 172 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"

//
// Slab_cache
//

inline Slab_cache::Slab_cache(unsigned long slab_size,
				 unsigned elem_size,
				 unsigned alignment,
				 char const * name)
  : _slab_size(slab_size), _entry_size(entry_size(elem_size, alignment)),
    _num_empty(0), _name (name)
{
  lock.init();
  _elem_num = (_slab_size - sizeof(Slab)) / _entry_size;
}

#line 275 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"



template< typename Q > inline void *
Slab_cache::q_alloc(Q *quota)
{
  Auto_quota<Ram_quota> q(quota, _entry_size);
  if (EXPECT_FALSE(!q))
    return 0;

  void *r;
  if (EXPECT_FALSE(!(r=alloc())))
    return 0;

  q.release();
  return r;
}

#line 338 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"



template< typename Q > inline void
Slab_cache::q_free(Q *quota, void *obj)
{
  free(obj);
  quota->free(_entry_size);
}

#line 195 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/slab_cache.cpp"


inline void
Slab_cache::destroy()	// descendant should call this in destructor
{
}

#endif // slab_cache_h
