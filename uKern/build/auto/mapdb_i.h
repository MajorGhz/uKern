// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef mapdb_i_h
#define mapdb_i_h
#line 78 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"

/* The mapping database.

 * This implementation encodes mapping trees in very compact arrays of
 * fixed sizes, prefixed by a tree header (Mapping_tree).  Array
 * sizes can vary from 4 mappings to 4<<15 mappings.  For each size,
 * we set up a slab allocator.  To grow or shrink the size of an
 * array, we have to allocate a larger or smaller tree from the
 * corresponding allocator and then copy the array elements.
 * 
 * The array elements (Mapping) contain a tree depth element.  This
 * depth and the relative position in the array is all information we
 * need to derive tree structure information.  Here is an example:
 * 
 * array
 * element   depth
 * number    value    comment
 * --------------------------
 * 0         0        Sigma0 mapping
 * 1         1        child of element #0 with depth 0
 * 2         2        child of element #1 with depth 1
 * 3         2        child of element #1 with depth 1
 * 4         3        child of element #3 with depth 2
 * 5         2        child of element #1 with depth 1
 * 6         3        child of element #5 with depth 2
 * 7         1        child of element #0 with depth 0
 * 
 * This array is a pre-order encoding of the following tree:
 * 
 *                   0
 * 	          /     \ 
 *               1       7
 *            /  |  \                   
 *           2   3   5
 *               |   |
 *        	 4   6
       	       	   
 * The mapping database (Mapdb) is organized in a hierarchy of
 * frame-number-keyed maps of Mapping_trees (Treemap).  The top-level
 * Treemap contains mapping trees for superpages.  These mapping trees
 * may contain references to Treemaps for subpages.  (Original credits
 * for this idea: Christan Szmajda.)
 *
 *        Treemap
 *        -------------------------------
 *     	  | | | | | | | | | | | | | | | | array of ptr to 4M Mapping_tree's
 *        ---|---------------------------
 *           |
 *           v a Mapping_tree
 *           ---------------
 *           |             | tree header
 *           |-------------|
 *           |             | 4M Mapping *or* ptr to nested Treemap
 *           |             | e.g.
 *           |      ----------------| Treemap
 *           |             |        v array of ptr to 4K Mapping_tree's
 *           ---------------        -------------------------------
 *                                  | | | | | | | | | | | | | | | |
 *                                  ---|---------------------------
 *                                     |
 *                                     v a Mapping_tree
 *                             	       ---------------
 *                                     |             | tree header
 *                                     |-------------|
 *                                     |             | 4K Mapping
 *                                     |             |
 *                                     |             |
 *                                     |             |
 *                                     ---------------

 * IDEAS for enhancing this implementation: 

 * We often have to find a tree header corresponding to a mapping.
 * Currently, we do this by iterating backwards over the array
 * containing the mappings until we find the Sigma0 mapping, from
 * whose address we can compute the address of the tree header.  If
 * this becomes a problem, we could add one more byte to the mappings
 * with a hint (negative array offset) where to find the sigma0
 * mapping.  (If the hint value overflows, just iterate using the hint
 * value of the mapping we find with the first hint value.)  Another
 * idea (from Adam) would be to just look up the tree header by using
 * the physical address from the page-table lookup, but we would need
 * to change the interface of the mapping database for that (pass in
 * the physical address at all times), or we would have to include the
 * physical address (or just the address of the tree header) in the
 * Mapdb-user-visible Mapping (which could be different from the
 * internal tree representation).  (XXX: Implementing one of these
 * ideas is probably worthwile doing!)

 * Instead of copying whole trees around when they grow or shrink a
 * lot, or copying parts of trees when inserting an element, we could
 * give up the array representation and add a "next" pointer to the
 * elements -- that is, keep the tree of mappings in a
 * pre-order-encoded singly-linked list (credits to: Christan Szmajda
 * and Adam Wiggins).  24 bits would probably be enough to encode that
 * pointer.  Disadvantages: Mapping entries would be larger, and the
 * cache-friendly space-locality of tree entries would be lost.
 */

#include <cassert>
#line 178 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
#include <cstring>
#line 179 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"

#include "config.h"
#line 181 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
#include "globals.h"
#line 183 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
#include "kmem_alloc.h"
#line 185 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
#include "kmem_slab.h"
#line 186 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
#include "ram_quota.h"
#line 187 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
#include "std_macros.h"
#line 188 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
#include <new>
#line 299 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"

//
// class Treemap_ops
//
// Helper operations for Treemaps (used in Mapping_tree::flush)

class Treemap_ops
{
  typedef Treemap::Order Order;
  typedef Treemap::Page Page;
  typedef Treemap::Pfn Pfn;
  typedef Treemap::Pcnt Pcnt;
  Order _page_shift;

public:  
#line 315 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Treemap_ops(Order page_shift);
  
#line 320 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Treemap::Pfn
  to_vaddr(Page v) const;
  
#line 325 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Treemap::Pcnt
  page_size() const;
  
#line 330 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  unsigned long
  mem_size(Treemap const *submap) const;
  
#line 349 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  void
  grant(Treemap *submap, Space *new_space, Page page) const;
  
#line 370 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Space *
  owner(Treemap const *submap) const;
  
#line 375 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline bool
  is_partial(Treemap const *submap, Treemap::Pcnt offs_begin,
                          Treemap::Pcnt offs_end) const;
  
#line 384 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline void 
  del(Treemap *submap) const;
  
#line 389 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline void
  flush(Treemap *submap,
                     Treemap::Pcnt offs_begin, Treemap::Pcnt offs_end) const;
};

//
// IMPLEMENTATION of inline functions follows
//


#line 451 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Treemap::Page
Treemap::trunc_to_page(Pcnt v) const
{ return Page(cxx::int_value<Pcnt>(v >> _page_shift)); }

#line 456 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Treemap::Page
Treemap::trunc_to_page(Pfn v) const
{ return Page(cxx::int_value<Pfn>(v >> _page_shift)); }

#line 466 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Treemap::Pcnt
Treemap::page_size() const
{ return Pcnt(1) << _page_shift; }

#line 504 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"




 //::Iterator::neutralize]
inline Treemap::~Treemap()
{
  Physframe::free(_physframe, cxx::int_value<Page>(_key_end));

  // Make sure that _unwind.~Mapdb_iterator is harmless: Reinitialize it.
  _unwind.neutralize();
}

#line 523 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"




inline void
Treemap::operator delete(void *block)
{
  Treemap *t = reinterpret_cast<Treemap*>(block);
  Space *id = t->_owner_id;
  allocator()->free(block);
  Mapping_tree::quota(id)->free(Treemap::quota_size(t->_key_end));
}

#line 542 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Space *
Treemap::owner() const
{
  return _owner_id;
}

#line 571 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


inline void
Treemap::set_vaddr(Mapping* m, Pfn address) const
{
  m->set_page(trunc_to_page(address));
}

#line 422 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


//
// Treemap members
//


inline Treemap::Treemap(Page key_end, Space *owner_id,
                 Pfn page_offset, Order page_shift,
                 const size_t* sub_shifts, unsigned sub_shifts_max,
                 Physframe *physframe)
  : _key_end(key_end),
    _owner_id(owner_id),
    _page_offset(page_offset),
    _page_shift(page_shift),
    _physframe(physframe),
    _sub_shifts(sub_shifts),
    _sub_shifts_max(sub_shifts_max)
{
  assert (_physframe);
}

#line 471 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


inline unsigned long
Treemap::quota_size(Page key_end)
{ return Physframe::mem_size(cxx::int_value<Page>(key_end)) + sizeof(Treemap); }

#line 213 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


inline unsigned long
Physframe::mem_size(size_t size)
{
  return (size*sizeof(Physframe) + 1023) & ~1023;
}

#line 220 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Physframe *
Physframe::alloc(size_t size)
{
  Physframe* block
    = (Physframe*)Kmem_alloc::allocator()->unaligned_alloc(mem_size(size));

#if 1				// Optimization: See constructor
  if (block) 
    memset(block, 0, size * sizeof(Physframe));
#else
  assert (block);
  for (unsigned i = 0; i < size; ++i)
    new (block + i) Physframe();
#endif

  return block;
}

#line 313 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Treemap_ops::Treemap_ops(Order page_shift)
: _page_shift(page_shift)
{}

#line 318 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Treemap::Pfn
Treemap_ops::to_vaddr(Page v) const
{ return Pfn(cxx::int_value<Page>(v << _page_shift)); }

#line 323 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Treemap::Pcnt
Treemap_ops::page_size() const
{ return Pcnt(1) << _page_shift; }

#line 368 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Space *
Treemap_ops::owner(Treemap const *submap) const
{ return submap->owner(); }

#line 373 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


inline bool
Treemap_ops::is_partial(Treemap const *submap, Treemap::Pcnt offs_begin,
                        Treemap::Pcnt offs_end) const
{
  return offs_begin > Treemap::Pcnt(0)
         || offs_end < submap->size();
}

#line 382 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


inline void 
Treemap_ops::del(Treemap *submap) const
{ delete submap; }

#line 387 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


inline void
Treemap_ops::flush(Treemap *submap,
                   Treemap::Pcnt offs_begin, Treemap::Pcnt offs_end) const
{
  typedef Treemap::Pcnt Pcnt;
  typedef Treemap::Pfn Pfn;

  for (Treemap::Page i = submap->trunc_to_page(offs_begin);
      i < submap->round_to_page(offs_end);
      i++)
    {
      Pcnt page_offs_begin = submap->to_vaddr(i) - Pfn(0);
      Pcnt page_offs_end = page_offs_begin;
      page_offs_end += submap->page_size();

      Physframe* subframe = submap->frame(i);

      auto guard = lock_guard(subframe->lock);

      if (offs_begin <= page_offs_begin && offs_end >= page_offs_end)
	subframe->tree.reset();
      else
	{
          // FIXME: do we have to check for subframe->tree != 0 here ?
	  submap->flush(subframe, subframe->tree->mappings(), false,
	    page_offs_begin > offs_begin
	    ? Pcnt(0) : cxx::get_lsb(offs_begin, _page_shift),
	    page_offs_end < offs_end
	    ? page_size()
	    : cxx::get_lsb(offs_end - Pcnt(1), _page_shift) + Pcnt(1));
	}
    }
}

#endif // mapdb_i_h
