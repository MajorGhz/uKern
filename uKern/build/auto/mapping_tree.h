// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef mapping_tree_h
#define mapping_tree_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"

#include "config.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
#include "l4_types.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
#include "lock.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
#include "mapping.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
#include "types.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"

#include <unique_ptr.h>

//
// INTERFACE definition follows 
//

#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"

class Ram_quota;
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"

class Simple_tree_submap_ops
{

public:  
#line 202 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  // Helpers
  
  
  inline unsigned long
  mem_size(Treemap const *) const;
  
#line 210 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  inline void
  grant(Treemap *, Space *, Page_number) const;
  
#line 215 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  inline Space *
  owner(Treemap const *) const;
  
#line 220 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  inline bool
  is_partial(Treemap const *, Page_number, Page_number) const;
  
#line 225 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  inline void
  del(Treemap *) const;
  
#line 230 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  inline void
  flush(Treemap *, Page_number, Page_number) const;
};
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"

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
 *                /     \
 *               1       7
 *            /  |  \
 *           2   3   5
 *               |   |
 *               4   6

 * The mapping database (Mapdb) is organized in a hierarchy of
 * frame-number-keyed maps of Mapping_trees (Treemap).  The top-level
 * Treemap contains mapping trees for superpages.  These mapping trees
 * may contain references to Treemaps for subpages.  (Original credits
 * for this idea: Christan Szmajda.)
 *
 *        Treemap
 *        -------------------------------
 *        | | | | | | | | | | | | | | | | array of ptr to 4M Mapping_tree's
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
 *                                     ---------------
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



#line 117 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
//
// Mapping_tree
// FIXME: do we need this depending on endianess ?
struct Mapping_tree
{
  typedef Mapping::Page Page;
  typedef Mapping::Pfn Pfn;
  typedef Mapping::Pcnt Pcnt;

  enum Size_id
  {
    Size_id_min = 0,
    Size_id_max = 9		// can be up to 15 (4 bits)
  };
  // DATA
  unsigned _count: 16;		///< Number of live entries in this tree.
  unsigned _size_id: 4;		///< Tree size -- see number_of_entries().
  unsigned _empty_count: 11;	///< Number of dead entries in this tree.
                                //   XXX currently never read, except in
                                //   sanity checks

  unsigned _unused: 1;		// (make this 32 bits to avoid a compiler bug)

  Mapping _mappings[0];


public:  
#line 245 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  inline Mapping_tree::Size_id
  shrink();
  
#line 256 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  inline Mapping_tree::Size_id
  bigger();
  
#line 305 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  //
  // class Mapping_tree
  //
  
  
  
  static inline Ram_quota *
  quota(Space *space);
  
#line 318 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  void*
  operator new(size_t, Mapping_tree::Size_id size_id) throw();
  
#line 323 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  void
  operator delete(void* block);
  
#line 337 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  //inline NEEDS[Mapping_depth, Mapping_tree::last]
  Mapping_tree(Size_id size_id, Page page,
                             Space *owner);
  
#line 359 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  ~Mapping_tree();
  
#line 369 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  //inline NEEDS[Mapping_depth, Mapping_tree::last]
  Mapping_tree(Size_id size_id, Mapping_tree* from_tree);
  
#line 378 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  // public routines with inline implementations
  
  inline unsigned
  number_of_entries() const;
  
#line 387 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  inline Mapping *
  mappings();
  
#line 394 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  inline bool
  is_empty() const;
  
#line 401 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  inline Mapping *
  end();
  
#line 408 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  inline Mapping *
  last();
  
#line 414 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  // A utility function to find the tree header belonging to a mapping. 
  
  /** Our Mapping_tree.
      @return the Mapping_tree we are in.
   */
  
  static Mapping_tree *
  head_of(Mapping *m);
  
#line 445 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  /** Next mapping in the mapping tree.
      @param t head of mapping tree, if available
      @return the next mapping in the mapping tree.  If the mapping has
      children, it is the first child.  Otherwise, if the mapping has a
      sibling, it's the next sibling.  Otherwise, if the mapping is the
      last sibling or only child, it's the mapping's parent.
   */
  
  inline Mapping *
  next(Mapping *m);
  
#line 463 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  /** Next child mapping of a given parent mapping.  This
      function traverses the mapping tree like next(); however, it
      stops (and returns 0) if the next mapping is outside the subtree
      starting with parent.
      @param parent Parent mapping
      @return the next child mapping of a given parent mapping
   */
  
  inline Mapping *
  next_child(Mapping *parent, Mapping *current_child);
  
#line 485 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  // This function copies the elements of mapping tree src to mapping
  // tree dst, ignoring empty elements (that is, compressing the
  // source tree.  In-place compression is supported.
  
  static void
  copy_compact_tree(Mapping_tree *dst, Mapping_tree *src);
  
#line 525 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  // Don't inline this function -- it eats a lot of stack space!
  // inline NEEDS[Mapping::data, Mapping::unused, Mapping::is_end_tag,
         //              Mapping_tree::end, Mapping_tree::number_of_entries]
  void
  check_integrity(Space *owner = (Space*)-1);
  
#line 573 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  /**
   * Use this function to reset a the tree to empty.
   *
   * In the case where a tree was copied to a new one you have to use 
   * this function to prevent the node iteration in the destructor.
   */
  
  inline void
  reset();
  
#line 589 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  inline Treemap *
  find_submap(Mapping* parent);
  
#line 605 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  inline Mapping *
  allocate(Ram_quota *payer, Mapping *parent,
                         bool insert_submap = false);
  
#line 729 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  inline void
  free_mapping(Ram_quota *q, Mapping *m);
  
#line 738 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  template< typename SUBMAP_OPS > void
  flush(Mapping *parent, bool me_too,
                      Pcnt offs_begin, Pcnt offs_end, 
                      SUBMAP_OPS const &submap_ops = SUBMAP_OPS());
  
#line 831 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  template< typename SUBMAP_OPS > bool
  grant(Mapping* m, Space *new_space, Page page,
                      SUBMAP_OPS const &submap_ops = SUBMAP_OPS());
  
#line 856 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  inline Mapping *
  lookup(Space *space, Page page);
};
#line 172 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
//
// class Physframe
//

/** Array elements for holding frame-specific data. */
class Base_mappable
{
public:
  typedef Mapping_tree::Page Page;
  // DATA
  cxx::unique_ptr<Mapping_tree> tree;
  typedef ::Lock Lock;
  Lock lock;

public:  
#line 874 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  Mapping *
  lookup(Space *space, Page page);
  
#line 890 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  inline Mapping *
  insert(Mapping* parent, Space *space, Page page);
  
#line 926 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
  void 
  pack();
}; // struct Physframe

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 190 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"

#include <cassert>
#line 192 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
#include <cstring>
#line 193 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"

#include "config.h"
#line 195 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
#include "globals.h"
#line 196 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
#include "kmem_slab.h"
#line 197 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
#include "ram_quota.h"
#line 198 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
#include "space.h"
#line 199 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"
#include "std_macros.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//

#line 233 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"

//
// Mapping-tree allocators
//

enum Mapping_tree_size
{
  Size_factor = 4,
  Size_id_max = 9		// can be up to 15 (4 bits)
};

#line 200 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"


// Helpers


inline unsigned long
Simple_tree_submap_ops::mem_size(Treemap const *) const
{ return 0; }

#line 208 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"


inline void
Simple_tree_submap_ops::grant(Treemap *, Space *, Page_number) const
{}

#line 213 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"


inline Space *
Simple_tree_submap_ops::owner(Treemap const *) const
{ return 0; }

#line 218 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"


inline bool
Simple_tree_submap_ops::is_partial(Treemap const *, Page_number, Page_number) const
{ return false; }

#line 223 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"


inline void
Simple_tree_submap_ops::del(Treemap *) const
{}

#line 228 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"


inline void
Simple_tree_submap_ops::flush(Treemap *, Page_number, Page_number) const
{}

#line 243 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"


inline Mapping_tree::Size_id
Mapping_tree::shrink()
{
  unsigned sid = _size_id - 1;
  while (sid > 0 && ((static_cast<unsigned>(_count) << 2) < ((unsigned)Size_factor << sid)))
    --sid;

  return Size_id(sid);
}

#line 254 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"


inline Mapping_tree::Size_id
Mapping_tree::bigger()
{ return Mapping_tree::Size_id(_size_id + 1); }

#line 304 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"

//
// class Mapping_tree
//



inline Ram_quota *
Mapping_tree::quota(Space *space)
{
  return space->ram_quota();
}

#line 377 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"

// public routines with inline implementations

inline unsigned
Mapping_tree::number_of_entries() const
{
  return Size_factor << (unsigned long)_size_id;
}

#line 385 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"


inline Mapping *
Mapping_tree::mappings()
{
  return & _mappings[0];
}

#line 392 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"


inline bool
Mapping_tree::is_empty() const
{
  return _count == 0;
}

#line 399 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"


inline Mapping *
Mapping_tree::end()
{
  return mappings() + number_of_entries();
}

#line 406 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"


inline Mapping *
Mapping_tree::last()
{
  return end() - 1;
}

#line 444 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"

/** Next mapping in the mapping tree.
    @param t head of mapping tree, if available
    @return the next mapping in the mapping tree.  If the mapping has
    children, it is the first child.  Otherwise, if the mapping has a
    sibling, it's the next sibling.  Otherwise, if the mapping is the
    last sibling or only child, it's the mapping's parent.
 */

inline Mapping *
Mapping_tree::next(Mapping *m)
{
  for (m++; m < end() && ! m->is_end_tag(); m++)
    if (! m->unused())
      return m;

  return 0;
}

#line 462 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"

/** Next child mapping of a given parent mapping.  This
    function traverses the mapping tree like next(); however, it
    stops (and returns 0) if the next mapping is outside the subtree
    starting with parent.
    @param parent Parent mapping
    @return the next child mapping of a given parent mapping
 */

inline Mapping *
Mapping_tree::next_child(Mapping *parent, Mapping *current_child)
{
  // Find the next valid entry in the tree structure.
  Mapping *m = next(current_child);

  // If we didn't find an entry, or if the entry cannot be a child of
  // "parent", return 0
  if (m == 0 || m->depth() <= parent->depth())
    return 0;

  return m;			// Found!
}

#line 571 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"


/**
 * Use this function to reset a the tree to empty.
 *
 * In the case where a tree was copied to a new one you have to use 
 * this function to prevent the node iteration in the destructor.
 */

inline void
Mapping_tree::reset()
{
  _count = 0;
  _empty_count = 0;
  _mappings[0].set_depth(Mapping::Depth_end);
}

#line 587 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"


inline Treemap *
Mapping_tree::find_submap(Mapping* parent)
{
  assert (! parent->submap());

  // We need just one step to find a possible submap, because they are
  // always a parent's first child.
  Mapping* m = next(parent);

  if (m && m->submap())
    return m->submap();

  return 0;
}

#line 603 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"


inline Mapping *
Mapping_tree::allocate(Ram_quota *payer, Mapping *parent,
                       bool insert_submap)
{
  Auto_quota<Ram_quota> q(payer, sizeof(Mapping));
  if (EXPECT_FALSE(!q))
    return 0;

  // After locating the right place for the new entry, it will be
  // stored there (if this place is empty) or the following entries
  // moved by one entry.

  // We cannot continue if the last array entry is not free.  This
  // only happens if an earlier call to free() with this mapping tree
  // couldn't allocate a bigger array.  In this case, signal an
  // out-of-memory condition.
  if (EXPECT_FALSE (! last()->unused()))
    return 0;

  // If the parent mapping already has the maximum depth, we cannot
  // insert a child.
  if (EXPECT_FALSE (parent->depth() == Mapping::Depth_max))
    return 0;

  //allocation is done, so...
  q.release();

  Mapping *insert = 0, *free = 0;
  // - Find an insertion point for the new entry. Acceptable insertion
  //   points are either before a sibling (same depth) or at the end
  //   of the subtree; for submap insertions, it's always before
  //   the first sibling.  "insert" keeps track of the last
  //   acceptable insertion point.
  // - Find a free entry in the array encoding the subtree ("free").
  //   There might be none; in this case, we stop at the end of the
  //   subtree.

  for (Mapping* m = parent + 1; m < end(); m++)
    {
      // End of subtree?  If we reach this point, this is our insert spot.
      if (m->is_end_tag()
          || m->depth() <= (insert_submap
             ? parent->depth() + 1
             : parent->depth()))
        {
          insert = m;
          break;
        }

      if (m->unused())
        free = m;
      else if (free		// Only look for insert spots after free
               && m->depth() <= parent->depth() + 1)
        {
          insert = m;
          break;
        }
    }

  assert (insert);
  assert (free == 0 || (free->unused() && free < insert));

  // We now update "free" to point to a free spot that is acceptable
  // as well.

  if (free)
    {
      // "free" will be the latest free spot before the "insert" spot.
      // If there is anything between "free" and "insert", move it
      // upward to make space just before insert.
      while (free + 1 != insert)
        {
          *free = *(free + 1);
          free++;
        }

#ifndef NDEBUG
      // Tree-header maintenance
      _empty_count -= 1;	// Allocated dead entry
#endif
    }
  else				// free == 0
    {
      // There was no free spot in the subtree.  Move everything
      // downward until we have free space.  This is guaranteed to
      // succeed, because we ensured earlier that the last entry of
      // the array is free.

      free = insert;		// This will be the free spot

      // Find empty spot
      while (! insert->unused())
        insert++;

      // Tree maintenance: handle end tag, empty count
      if (insert->is_end_tag())
        {
          // Need to move end tag.
          if (insert + 1 < end())
            insert++;           // Arrange for copying end tag as well
        }
#ifndef NDEBUG
      else
        _empty_count -= 1;      // Allocated dead entry
#endif

      // Move mappings
      while (insert > free)
        {
          *insert = *(insert - 1);
          --insert;
        }
    }

  _count += 1;		// Adding an alive entry

  // found a place to insert new child (free).
  free->set_depth(insert_submap ? (unsigned)Mapping::Depth_submap 
                                : parent->depth() + 1);

  return free;
}

#line 727 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"


inline void
Mapping_tree::free_mapping(Ram_quota *q, Mapping *m)
{
  assert (!m->unused() && !m->is_end_tag());
  q->free(sizeof(Mapping));
  m->set_unused();
}

#line 854 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"


inline Mapping *
Mapping_tree::lookup(Space *space, Page page)
{

  Mapping *m;

  for (m = mappings(); m; m = next(m))
    {
      assert (!m->submap());
      if (m->space() == space && m->page() == page)
        return m;
    }

  return 0;
}

#line 888 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"


inline Mapping *
Base_mappable::insert(Mapping* parent, Space *space, Page page)
{
  Mapping_tree* t = tree.get();
  if (!t)
    {
      assert (parent == 0);
      Auto_quota<Ram_quota> q(Mapping_tree::quota(space), sizeof(Mapping));
      if (EXPECT_FALSE(!q))
        return 0;

      Mapping_tree::Size_id min_size = Mapping_tree::Size_id_min;
      cxx::unique_ptr<Mapping_tree> new_tree(new (min_size) Mapping_tree (min_size, page, space));

      if (EXPECT_FALSE(!new_tree))
        return 0;

      tree = cxx::move(new_tree);
      q.release();
      return tree->mappings();
    }

  Mapping *free = t->allocate(Mapping_tree::quota(space), parent, false);

  if (EXPECT_FALSE(!free))
        return 0;

  free->set_space(space);
  free->set_page(page);

  t->check_integrity();
  return free;
}

//
// IMPLEMENTATION of function templates
//


#line 736 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"


template< typename SUBMAP_OPS > void
Mapping_tree::flush(Mapping *parent, bool me_too,
                    Pcnt offs_begin, Pcnt offs_end, 
                    SUBMAP_OPS const &submap_ops)
{
  assert (! parent->unused());

  // This is easy to do: We just have to iterate over the array
  // encoding the tree.
  Mapping *start_of_deletions = parent;
  unsigned p_depth = parent->depth();
  unsigned deleted = 0;
#ifndef NDEBUG
  unsigned empty_elems_passed = 0;
#endif

  if (me_too)
    {
      free_mapping(quota(parent->space()), parent);
      _count -= 1;
      deleted++;
    }
  else
    start_of_deletions++;

  unsigned m_depth = p_depth;

  for (Mapping* m = parent + 1;
       m < end() && ! m->is_end_tag();
       m++)
    {
      if (unsigned (m->depth()) <= p_depth)
        {
          // Found another data element -- stop deleting.  Since we
          // created holes in the tree representation, account for it.
#ifndef NDEBUG
          _empty_count += deleted;
#endif
          return;
        }

      if (m->unused())
        {
#ifndef NDEBUG
          empty_elems_passed++;
#endif
          continue;
        }

      Space *space;
      if (Treemap* submap = m->submap())
        {
          space = submap_ops.owner(submap);
          if (! me_too
              // Check for immediate child.  Note: It's a bad idea to
              // call m->parent() because that would iterate backwards
              // over already-deleted entries.
              && m_depth == p_depth
              && submap_ops.is_partial(submap, offs_begin, offs_end))
            {
              submap_ops.flush(submap, offs_begin, offs_end);

              start_of_deletions++;
              continue;
            }
          else
            submap_ops.del(submap);
        }
      else    // Found a real mapping
        {
          space = m->space();
          m_depth = m->depth();
        }

      // Delete the element.
      free_mapping(quota(space), m);
      _count -= 1;
      deleted++;
    }

  // We deleted stuff at the end of the array -- move end tag
  if (start_of_deletions < end())
    {
      start_of_deletions->set_depth(Mapping::Depth_end);

#ifndef NDEBUG
      // also, reduce number of free entries
      _empty_count -= empty_elems_passed;
#endif
    }
}

#line 829 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapping_tree.cpp"


template< typename SUBMAP_OPS > bool
Mapping_tree::grant(Mapping* m, Space *new_space, Page page,
                    SUBMAP_OPS const &submap_ops)
{
  unsigned long _quota = sizeof(Mapping);
  Treemap* submap = find_submap(m);
  if (submap)
    _quota += submap_ops.mem_size(submap);

  if (!quota(new_space)->alloc(_quota))
    return false;

  Space *old_space = m->space();

  m->set_space(new_space);
  m->set_page(page);

  if (submap)
    submap_ops.grant(submap, new_space, page);

  quota(old_space)->free(_quota);
  return true;
}

#endif // mapping_tree_h
