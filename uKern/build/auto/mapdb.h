// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef mapdb_h
#define mapdb_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"

#include "slab_cache.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
#include "l4_types.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
#include "types.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
#include "mapping.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
#include "auto_quota.h"

//
// INTERFACE definition follows 
//

#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"

struct Mapping_tree;		// forward decls
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
class Physframe;
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
class Treemap;
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
class Space;
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"

/** A mapping database.
 */
class Mapdb
{
  friend class Jdb_mapdb;

public:
  typedef ::Mapping Mapping;
  typedef Mapping::Pfn Pfn;
  typedef Mapping::Pcnt Pcnt;
  typedef Mdb_types::Order Order;

  class Frame;

  /** Iterator for mapping trees.  This iterator knows how to descend
    into Treemap nodes.
   */
  class Iterator
  {
    typedef Mapping::Page Page;
    Mapping_tree* _mapping_tree;
    Mapping* _parent;
    Mapping* _cursor;
    Order  _page_shift;
    Treemap *_submap;
    Physframe *_subframe;
    Page _submap_index;
    Pcnt _offs_begin, _offs_end;

  public:
    inline Mapping* operator->() const { return _cursor; }
    inline operator Mapping*() const { return _cursor; }
    inline Iterator() : _submap (0), _submap_index(Page(0)) {}
    inline Iterator(const Mapdb::Frame& f, Mapping* parent,
                    Pfn va_begin, Pfn va_end);
    inline ~Iterator();
    inline void neutralize();
    inline Order order() const { return _page_shift; }
    inline Pfn page() const
    { return Pfn(cxx::int_value<Page>(_cursor->page())) << order(); }

    inline Iterator &operator++ ();
  };

  // TYPES
  class Frame
  {
    friend class Mapdb;
    friend class Mapdb::Iterator;
    Treemap* treemap;
    Physframe* frame;

  public:
    inline Pfn vaddr(Mapping* m) const;
    inline Order page_shift() const;
  };

private:
  // DATA
  Treemap* const _treemap;

public:  
#line 928 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  // 
  // class Mapdb
  // 
  
  /** Constructor.
      @param End physical end address of RAM.  (Used only if 
             Config::Mapdb_ram_only is true.) 
   */
  
  Mapdb(Space *owner, Mapping::Page end_frame, size_t const *page_shifts,
               unsigned page_shifts_max);
  
#line 948 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  /** Destructor. */
  
  ~Mapdb();
  
#line 955 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  /** Insert a new mapping entry with the given values as child of
      "parent".
      We assume that there is at least one free entry at the end of the
      array so that at least one insert() operation can succeed between a
      lookup()/free() pair of calls.  This is guaranteed by the free()
      operation which allocates a larger tree if the current one becomes
      to small.
      @param parent Parent mapping of the new mapping.
      @param space  Number of the address space into which the mapping is entered
      @param va     Virtual address of the mapped page.
      @param size   Size of the mapping.  For memory mappings, 4K or 4M.
      @return If successful, new mapping.  If out of memory or mapping 
             tree full, 0.
      @post  All Mapping* pointers pointing into this mapping tree,
             except "parent" and its parents, will be invalidated.
   */
  
  Mapping *
  insert(const Mapdb::Frame& frame, Mapping* parent, Space *space,
                Pfn va, Pfn phys, Pcnt size);
  
#line 981 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  /** 
   * Lookup a mapping and lock the corresponding mapping tree.  The returned
   * mapping pointer, and all other mapping pointers derived from it, remain
   * valid until free() is called on one of them.  We guarantee that at most 
   * one insert() operation succeeds between one lookup()/free() pair of calls 
   * (it succeeds unless the mapping tree is fu68,ll).
   * @param space Number of virtual address space in which the mapping 
   *              was entered
   * @param va    Virtual address of the mapping
   * @param phys  Physical address of the mapped pag frame
   * @return mapping, if found; otherwise, 0
   */
  
  bool
  lookup(Space *space, Pfn va, Pfn phys,
               Mapping** out_mapping, Mapdb::Frame* out_lock);
  
#line 1002 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  /** Unlock the mapping tree to which the mapping belongs.  Once a tree
      has been unlocked, all Mapping instances pointing into it become
      invalid.
  
      A mapping tree is locked during lookup().  When the tree is
      locked, the tree may be traversed (using member functions of
      Mapping, which serves as an iterator over the tree) or
      manipulated (using insert(), free(), flush(), grant()).  Note that
      only one insert() is allowed during each locking cycle.
  
      @param mapping_of_tree Any mapping belonging to a mapping tree.
   */
  
  static void
  free(const Mapdb::Frame& f);
  
#line 1021 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  /** Delete mappings from a tree.  This function deletes mappings
      recusively.
      @param m Mapping that denotes the subtree that should be deleted.
      @param me_too If true, delete m as well; otherwise, delete only 
             submappings.
   */
  
  static void
  flush(const Mapdb::Frame& f, Mapping *m, L4_map_mask mask,
               Pfn va_start, Pfn va_end);
  
#line 1043 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  /** Change ownership of a mapping.
      @param m Mapping to be modified.
      @param new_space Number of address space the mapping should be 
                       transferred to
      @param va Virtual address of the mapping in the new address space
   */
  
  bool
  grant(const Mapdb::Frame& f, Mapping *m, Space *new_space,
               Pfn va);
  
#line 1057 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  /** Return page size of given mapping and frame. */
  
  static inline Mapdb::Order
  shift(const Mapdb::Frame& f, Mapping * /*m*/);
  
#line 1067 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  static inline Mapdb::Pfn
  vaddr(const Mapdb::Frame& f, Mapping* m);
  
#line 1088 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline bool
  valid_address(Pfn phys);
  
#line 1098 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Mapdb::Mapping *
  check_for_upgrade(Pfn phys,
                           Space *from_id, Pfn snd_addr,
                           Space *to_id, Pfn rcv_addr,
                           Frame *mapdb_frame);
  
#line 1176 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  bool
  find_space(Space *s);
};
#line 777 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
#line 1072 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 182 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
#include "helping_lock.h"
#line 184 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
#include "mapping_tree.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//

#line 270 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"

// 
// class Treemap
// 

class Treemap
{
public:
  typedef Mapping_tree::Page Page;
  typedef Mapdb::Pfn Pfn;
  typedef Mapdb::Pcnt Pcnt;
  typedef Mapdb::Order Order;

private:
  friend class Jdb_mapdb;
  friend class Treemap_ops;

  // DATA
  Page _key_end;		///< Number of Physframe entries
  Space *_owner_id;	///< ID of owner of mapping trees 
  Pfn _page_offset;	///< Virt. page address in owner's addr space
  Order _page_shift;		///< Page size of mapping trees
  Physframe* _physframe;	///< Pointer to Physframe array
  const size_t* const _sub_shifts; ///< Pointer to array of sub-page sizes
  const unsigned _sub_shifts_max;  ///< Number of valid _page_sizes entries

  friend class Mapdb::Iterator;
  Mapdb::Iterator _unwind;	///< Chaining information for Mapdb_iterator

public:  
#line 445 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Treemap::Page
  round_to_page(Pcnt v) const;
  
#line 453 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Treemap::Page
  trunc_to_page(Pcnt v) const;
  
#line 458 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Treemap::Page
  trunc_to_page(Pfn v) const;
  
#line 463 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Treemap::Pfn
  to_vaddr(Page v) const;
  
#line 468 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Treemap::Pcnt
  page_size() const;
  
#line 478 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  static Treemap *
  create(Page key_end, Space *owner_id,
                  Pfn page_offset, Order page_shift,
                  const size_t* sub_shifts, unsigned sub_shifts_max);
  
#line 508 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  //::Iterator::neutralize]
  inline ~Treemap();
  
#line 527 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline void
  operator delete(void *block);
  
#line 537 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Treemap::Order
  page_shift() const;
  
#line 544 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Space *
  owner() const;
  
#line 552 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Treemap::Pcnt
  size() const;
  
#line 559 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Treemap::Pfn
  end_addr() const;
  
#line 566 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Treemap::Pfn
  vaddr(Mapping* m) const;
  
#line 573 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline void
  set_vaddr(Mapping* m, Pfn address) const;
  
#line 580 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  Physframe*
  tree(Page key);
  
#line 616 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  Physframe*
  frame(Page key) const;
  
#line 625 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  bool
  lookup(Pcnt key, Space *search_space, Pfn search_va,
                  Mapping** out_mapping, Treemap** out_treemap,
                  Physframe** out_frame);
  
#line 673 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  Mapping *
  insert(Physframe* frame, Mapping* parent, Space *space,
                  Pfn va, Pcnt phys, Pcnt size);
  
#line 743 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  void 
  free(Physframe* f);
  
#line 755 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  void
  flush(Physframe* f, Mapping* parent, bool me_too,
                 Pcnt offs_begin, Pcnt offs_end);
  
#line 771 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  bool
  grant(Physframe* f, Mapping* m, Space *new_space, Pfn va);
  
#line 1124 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  bool
  find_space(Space *s);

private:  
#line 424 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  //
  // Treemap members
  //
  
  
  inline Treemap(Page key_end, Space *owner_id,
                   Pfn page_offset, Order page_shift,
                   const size_t* sub_shifts, unsigned sub_shifts_max,
                   Physframe *physframe);
  
#line 473 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  static inline unsigned long
  quota_size(Page key_end);
  
#line 520 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  static Slab_cache *
  allocator();
};
#line 189 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"

// 
// class Physframe
// 

/** Array elements for holding frame-specific data. */
class Physframe : public Base_mappable
{
  friend class Mapdb;
  friend class Mapdb::Iterator;
  friend class Treemap;
  friend class Jdb_mapdb;

public:  
#line 215 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  static inline unsigned long
  mem_size(size_t size);

private:  
#line 222 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  static inline Physframe *
  alloc(size_t size);
  
#line 242 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline ~Physframe();
  
#line 261 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  // inline NEEDS[Physframe::~Physframe]
  static void 
  free(Physframe *block, size_t size);
}; // struct Physframe

#line 535 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Treemap::Order
Treemap::page_shift() const
{
  return _page_shift;
}

#line 1056 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"

/** Return page size of given mapping and frame. */

inline Mapdb::Order
Mapdb::shift(const Mapdb::Frame& f, Mapping * /*m*/)
{
  // XXX add special case for _mappings[0]: Return superpage size.
  return f.treemap->page_shift();
}

#line 461 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Treemap::Pfn
Treemap::to_vaddr(Page v) const
{ return Pfn(cxx::int_value<Page>(v << _page_shift)); }

#line 564 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Treemap::Pfn
Treemap::vaddr(Mapping* m) const
{
  return to_vaddr(m->page());
}

#line 1065 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Mapdb::Pfn
Mapdb::vaddr(const Mapdb::Frame& f, Mapping* m)
{
  return f.treemap->vaddr(m);
}

#line 549 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"



inline Treemap::Pcnt
Treemap::size() const
{
  return to_vaddr(_key_end) - Pfn(0);
}

#line 557 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Treemap::Pfn
Treemap::end_addr() const
{
  return _page_offset + size();
}

#line 1086 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


inline bool
Mapdb::valid_address(Pfn phys)
{
  // on the root level physical and virtual frame numbers
  // are the same
  return phys < _treemap->end_addr();
}

#line 1095 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"



inline Mapdb::Mapping *
Mapdb::check_for_upgrade(Pfn phys,
                         Space *from_id, Pfn snd_addr,
                         Space *to_id, Pfn rcv_addr,
                         Frame *mapdb_frame)
{
  // Check if we can upgrade mapping.  Otherwise, flush target
  // mapping.
  Mapping* receiver_mapping;
  if (valid_address(phys) // Can lookup in mapdb
      && lookup(to_id, rcv_addr, phys, &receiver_mapping, mapdb_frame))
    {
      Mapping* receiver_parent = receiver_mapping->parent();
      if (receiver_parent->space() == from_id
	  && vaddr(*mapdb_frame, receiver_parent) == snd_addr)
	return receiver_parent;
      else		// Not my child -- cannot upgrade
	free(*mapdb_frame);
    }
  return 0;
}

#line 777 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"



//
// class Mapdb_iterator
//

/** Create a new mapping-tree iterator.  If parent is the result of a
    fresh lookup (and not the result of an insert operation), you can
    pass the corresponding Mapdb::Frame for optimization.
 */

inline Mapdb::Iterator::Iterator(const Mapdb::Frame& f, Mapping* parent,
                          Pfn va_begin, Pfn va_end)
  : _mapping_tree(f.frame->tree.get()),
    _parent(parent),
    _cursor(parent),
    _page_shift(f.treemap->_page_shift),
    _submap(0),
    _subframe(0),
    _submap_index(Page(0))
{
  assert (_mapping_tree == Mapping_tree::head_of(parent));
  assert (! parent->submap());
  assert (va_begin <= va_end);

  if (va_begin <= f.treemap->vaddr(parent))
    _offs_begin = Pcnt(0);
  else
    _offs_begin = va_begin - f.treemap->vaddr(parent);

  if (va_end <= f.treemap->vaddr(parent))
    _offs_end = Pcnt(0);
  else
    _offs_end = va_end - f.treemap->vaddr(parent);

  ++*this;
}

#line 815 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Mapdb::Iterator::~Iterator()
{
  // unwind lock information
  while (_submap)
    {
      if (_subframe)
	_subframe->lock.clear();

      *this = _submap->_unwind;
    }
}

#line 828 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"

/** Make sure that the destructor does nothing.  Handy for scratch
    iterators such as Treemap::_unwind. */

inline void
Mapdb::Iterator::neutralize()
{
  _submap = 0;
}

#line 443 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Treemap::Page
Treemap::round_to_page(Pcnt v) const
{
  return Page(cxx::int_value<Pcnt>(v + ((Pcnt(1) << _page_shift) - Pcnt(1))
              >> _page_shift));
}

#line 837 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Mapdb::Iterator&
Mapdb::Iterator::operator++()
{
  for (;;)
    {
      _cursor = _mapping_tree->next_child(_parent, _cursor);
      
      if (_cursor && ! _cursor->submap())
	{			// Found a new regular child mapping.
	  if (_cursor)
	    return *this;
	}

      if (_cursor)		// _cursor is a submap
	{
	  Treemap* submap = _cursor->submap();
	  assert (submap);

	  // Before descending into array of subpages, save iterator
	  // state for later unwinding to this point.
	  submap->_unwind = *this;

	  // For subpages of original parent mapping, apply possible tag and
	  // virtual-address restrictions.  (Do not apply restrictions
	  // to other subpages because operations on a part of a
	  // superpage always affect *complete* child-superpages, as
	  // we do not support splitting out parts of superpages.
	  Pcnt parent_size = submap->size();


	  if (_cursor->parent() == _parent)
	    {			// Submap of iteration root
              assert (_offs_begin < parent_size);
              if (_offs_end > parent_size)
                _offs_end = parent_size;
	    }
	  else			// Submap of a child mapping
	    {
	      _offs_begin = Pcnt(0);
	      _offs_end = parent_size;
	    }

	  // Initialize rest of iterator for subframe iteration
	  _submap = submap;
	  _page_shift = _submap->_page_shift;
	  _subframe = 0;
	  _submap_index = Page(cxx::int_value<Pcnt>(_offs_begin >> _page_shift));
	  _mapping_tree = 0;
	  _parent = _cursor = 0;
	}

      else if (! _submap)	// End of iteration
	return *this;
	  
      // Clear previously acquired lock.
      if (_subframe)
	{
	  _subframe->lock.clear();
	  _subframe = 0;
	}

      // Find a new subframe.
      Physframe* f = 0;

      Page end_offs = _submap->round_to_page(_offs_end);
      assert (end_offs <= _submap->_key_end);

      for (; _submap_index < end_offs;)
	{
	  f = _submap->frame(_submap_index++);
	  if (f->tree.get())
	    break;
	}
      
      if (f && f->tree)	// Found a subframe
	{
	  _subframe = f;
	  f->lock.lock();	// Lock it
	  _mapping_tree = f->tree.get();
	  _parent = _cursor = _mapping_tree->mappings();
	  continue;
	}
      
      // No new subframes found -- unwind to superpage tree
      *this = _submap->_unwind;
    }
}

#line 1072 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"

// 
// class Mapdb::Frame
// 


inline Mapdb::Pfn
Mapdb::Frame::vaddr(Mapping* m) const
{ return treemap->vaddr(m); }

#line 1081 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Mapdb::Order
Mapdb::Frame::page_shift() const
{ return treemap->page_shift(); }

#endif // mapdb_h
