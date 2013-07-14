// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "mapdb.h"
#include "mapdb_i.h"

#line 516 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"

static Kmem_slab_t<Treemap> _treemap_allocator("Treemap");

#line 239 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


       
inline Physframe::~Physframe()
{
  if (tree)
    {
      auto guard = lock_guard(lock);

      // Find next-level trees.
      for (Mapping* m = tree->mappings();
	   m && !m->is_end_tag();
	   m = tree->next(m))
	{
	  if (m->submap())
	    delete m->submap();
	}

      tree.reset();
    }
}

#line 260 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"

// inline NEEDS[Physframe::~Physframe]
void 
Physframe::free(Physframe *block, size_t size)
{
  for (unsigned i = 0; i < size; ++i)
    block[i].~Physframe();

  Kmem_alloc::allocator()->unaligned_free(Physframe::mem_size(size), block);
}

#line 328 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


unsigned long
Treemap_ops::mem_size(Treemap const *submap) const
{
  unsigned long quota
    = cxx::int_value<Page>(submap->_key_end) * sizeof(Physframe) + sizeof(Treemap);

  for (Page key = Page(0);
      key < submap->_key_end;
      ++key)
    {
      Physframe* subframe = submap->frame(key);
      if (subframe->tree)
	quota += sizeof(Mapping);
    }

  return quota;
}

#line 347 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


void
Treemap_ops::grant(Treemap *submap, Space *new_space, Page page) const
{
  submap->_owner_id = new_space;
  submap->_page_offset = to_vaddr(page);

  for (Page key = Page(0);
      key < submap->_key_end;
      ++key)
    {
      Physframe* subframe = submap->frame(key);
      if (Mapping_tree* tree = subframe->tree.get())
	{
	  auto guard = lock_guard(subframe->lock);
	  tree->mappings()->set_space(new_space);
	  tree->mappings()->set_page(page + (key >> (_page_shift - submap->_page_shift)));
	}
    }
}

#line 476 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


Treemap *
Treemap::create(Page key_end, Space *owner_id,
                Pfn page_offset, Order page_shift,
                const size_t* sub_shifts, unsigned sub_shifts_max)
{
  Auto_quota<Ram_quota> quota(Mapping_tree::quota(owner_id), quota_size(key_end));

  if (EXPECT_FALSE(!quota))
    return 0;

  Physframe *pf = Physframe::alloc(cxx::int_value<Page>(key_end));

  if (EXPECT_FALSE(!pf))
    return 0;

  void *m = allocator()->alloc();
  if (EXPECT_FALSE(!m))
    {
      Physframe::free(pf, cxx::int_value<Page>(key_end));
      return 0;
    }

  quota.release();
  return new (m) Treemap(key_end, owner_id, page_offset, page_shift, sub_shifts,
                         sub_shifts_max, pf);
}

#line 518 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


Slab_cache *
Treemap::allocator()
{ return &_treemap_allocator; }

#line 578 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


Physframe*
Treemap::tree(Page key)
{
  assert (key < _key_end);

  Physframe *f = &_physframe[cxx::int_value<Page>(key)];

  f->lock.lock();

  if (! f->tree)
    {
      Auto_quota<Ram_quota> q(Mapping_tree::quota(_owner_id), sizeof(Mapping));
      if (EXPECT_FALSE(!q))
        {
          f->lock.clear();
          return 0;
        }

      cxx::unique_ptr<Mapping_tree> new_tree
	(new (Mapping_tree::Size_id_min) Mapping_tree(Mapping_tree::Size_id_min, key + trunc_to_page(_page_offset),
	                      _owner_id));

      if (EXPECT_FALSE(!new_tree))
        {
          f->lock.clear();
          return 0;
        }

      q.release();
      f->tree = cxx::move(new_tree);
    }

  return f;
}

#line 614 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


Physframe*
Treemap::frame(Page key) const
{
  assert (key < _key_end);

  return &_physframe[cxx::int_value<Page>(key)];
}

#line 623 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


bool
Treemap::lookup(Pcnt key, Space *search_space, Pfn search_va,
                Mapping** out_mapping, Treemap** out_treemap,
                Physframe** out_frame)
{
  // get and lock the tree.
  assert (trunc_to_page(key) < _key_end);
  Physframe *f = tree(trunc_to_page(key)); // returns locked frame
  assert (f);

  Mapping_tree *t = f->tree.get();
  Order const psz = _page_shift;

  assert (t);
  assert (t->mappings()[0].space() == _owner_id);
  assert (vaddr(t->mappings()) == cxx::mask_lsb(key, psz) + _page_offset);

  Mapping *m;
  bool ret = false;

  for (m = t->mappings(); m; m = t->next (m))
    {
      if (Treemap *sub = m->submap())
	{
	  // XXX Recursion.  The max. recursion depth should better be
	  // limited!
	  if ((ret = sub->lookup(cxx::get_lsb(key, psz),
	                         search_space, search_va,
	                         out_mapping, out_treemap, out_frame)))
	    break;
	}
      else if (m->space() == search_space
	       && vaddr(m) == cxx::mask_lsb(search_va, psz))
	{
	  *out_mapping = m;
	  *out_treemap = this;
	  *out_frame = f;
	  return true;		// found! -- return locked
	}
    }

  // not found, or found in submap -- unlock tree
  f->lock.clear();

  return ret;
}

#line 671 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


Mapping *
Treemap::insert(Physframe* frame, Mapping* parent, Space *space,
                Pfn va, Pcnt phys, Pcnt size)
{
  Mapping_tree* t = frame->tree.get();
  Treemap* submap = 0;
  Ram_quota *payer;
  Order const psz = _page_shift;
  bool insert_submap = page_size() != size;

  // Inserting subpage mapping?  See if we can find a submap.  If so,
  // we don't have to allocate a new Mapping entry.
  if (insert_submap)
    submap = t->find_submap(parent);

  if (! submap) // Need allocation of new entry -- for submap or
		// normal mapping
    {
      // first check quota! In case of a new submap the parent pays for 
      // the node...
      payer = Mapping_tree::quota(insert_submap ? parent->space() : space);

      Mapping *free = t->allocate(payer, parent, insert_submap);
      if (EXPECT_FALSE(!free))
	return 0; 
      
      // Check for submap entry.
      if (! insert_submap)	// Not a submap entry
	{
	  free->set_space(space);
	  set_vaddr(free, va);

	  t->check_integrity(_owner_id);
	  return free;
	}

      assert (_sub_shifts_max > 0);

      submap
        = Treemap::create(Page(1) << (_page_shift - Order(_sub_shifts[0])),
            parent->space(), vaddr(parent), Order(_sub_shifts[0]),
            _sub_shifts + 1, _sub_shifts_max - 1);
      if (! submap)
	{
	  // free the mapping got with allocate
	  t->free_mapping(payer, free); 
	  return 0;
	}

      free->set_submap(submap);
    }

  Physframe* subframe = submap->tree(submap->trunc_to_page(cxx::get_lsb(phys, psz)));
  if (! subframe)
    return 0;

  Mapping_tree* subtree = subframe->tree.get();

  if (! subtree)
    return 0;

  // XXX recurse.
  Mapping* ret = submap->insert(subframe, subtree->mappings(), space, va,
                                cxx::get_lsb(phys, psz), size);
  submap->free(subframe);

  return ret;
} // Treemap::insert()

#line 741 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


void 
Treemap::free(Physframe* f)
{
  f->pack();
  f->tree->check_integrity(_owner_id);

  // Unlock tree.
  f->lock.clear();
} // Treemap::free()

#line 752 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"



void
Treemap::flush(Physframe* f, Mapping* parent, bool me_too,
               Pcnt offs_begin, Pcnt offs_end)
{
  assert (! parent->unused());

  // This is easy to do: We just have to iterate over the array
  // encoding the tree.
  Mapping_tree *t = f->tree.get();
  t->flush(parent, me_too, offs_begin, offs_end, Treemap_ops(_page_shift));

  t->check_integrity(_owner_id);
  return;
} // Treemap::flush()

#line 769 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


bool
Treemap::grant(Physframe* f, Mapping* m, Space *new_space, Pfn va)
{
  return f->tree->grant(m, new_space, trunc_to_page(va),
                        Treemap_ops(_page_shift));
}

#line 926 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


// 
// class Mapdb
// 

/** Constructor.
    @param End physical end address of RAM.  (Used only if 
           Config::Mapdb_ram_only is true.) 
 */

Mapdb::Mapdb(Space *owner, Mapping::Page end_frame, size_t const *page_shifts,
             unsigned page_shifts_max)
: _treemap(Treemap::create(end_frame, owner,
                           Pfn(0),
                           Order(page_shifts[0]), page_shifts + 1,
                           page_shifts_max - 1))
{
  // assert (boot_time);
  assert (_treemap);
} // Mapdb()

#line 947 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"

/** Destructor. */

Mapdb::~Mapdb()
{
  delete _treemap;
}

#line 954 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"

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
Mapdb::insert(const Mapdb::Frame& frame, Mapping* parent, Space *space,
              Pfn va, Pfn phys, Pcnt size)
{
  return frame.treemap->insert(frame.frame, parent, space, va, phys - Pfn(0),
                               size);
} // insert()

#line 979 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


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
Mapdb::lookup(Space *space, Pfn va, Pfn phys,
             Mapping** out_mapping, Mapdb::Frame* out_lock)
{
  return _treemap->lookup(phys - Pfn(0), space, va, out_mapping,
                          & out_lock->treemap, & out_lock->frame);
}

#line 1001 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"

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

void
Mapdb::free(const Mapdb::Frame& f)
{
  f.treemap->free(f.frame);
} // free()

#line 1020 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"

/** Delete mappings from a tree.  This function deletes mappings
    recusively.
    @param m Mapping that denotes the subtree that should be deleted.
    @param me_too If true, delete m as well; otherwise, delete only 
           submappings.
 */

void
Mapdb::flush(const Mapdb::Frame& f, Mapping *m, L4_map_mask mask,
             Pfn va_start, Pfn va_end)
{
  Pcnt size = f.treemap->page_size();
  Pcnt offs_begin = va_start > f.treemap->vaddr(m)
                  ? va_start - f.treemap->vaddr(m)
                  : Pcnt(0);
  Pcnt offs_end = va_end > f.treemap->vaddr(m) + size
                ? size
                : va_end - f.treemap->vaddr(m);

  f.treemap->flush(f.frame, m, mask.self_unmap(), offs_begin, offs_end);
} // flush()

#line 1042 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"

/** Change ownership of a mapping.
    @param m Mapping to be modified.
    @param new_space Number of address space the mapping should be 
                     transferred to
    @param va Virtual address of the mapping in the new address space
 */

bool
Mapdb::grant(const Mapdb::Frame& f, Mapping *m, Space *new_space,
             Pfn va)
{
  return f.treemap->grant(f.frame, m, new_space, va);
}

#line 1122 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


bool
Treemap::find_space(Space *s)
{
  bool bug = _owner_id == s;
  for (Page i = Page(0); i < _key_end; ++i)
    {
      bool tree_bug = false;
      Mapping_tree *t = _physframe[cxx::int_value<Page>(i)].tree.get();
      if (!t)
        continue;

      t->check_integrity();
      Mapping *m = t->mappings();
      for (unsigned mx = 0; mx < t->number_of_entries(); ++mx)
        {
          bool mapping_bug = false;
          Mapping *ma = m + mx;
          if (ma->is_end_tag())
            break;

          if (ma->unused())
            continue;

          if (ma->submap())
            mapping_bug = ma->submap()->find_space(s);
          else if (ma->space() == s)
            {
              mapping_bug = true;
              printf("MAPDB: found space %p in mapdb (idx=%d, mapping=%p, depth=%d, page=%lx)\n",
                     s, mx, ma, ma->depth(), cxx::int_value<Page>(ma->page()));
            }

          tree_bug |= mapping_bug;
        }

      if (tree_bug)
        printf("MAPDB: error in mapping tree: index=%ld\n",
               cxx::int_value<Page>(i));

      bug |= tree_bug;
    }

  if (bug)
    printf("MAPDB: error in treemap: owner(space)=%p, offset=%lx, size=%lx, pageshift=%d\n",
           _owner_id, cxx::int_value<Pfn>(_page_offset),
           cxx::int_value<Page>(_key_end),
           cxx::int_value<Order>(_page_shift));

  return bug;
}

#line 1174 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mapdb.cpp"


bool
Mapdb::find_space(Space *s)
{ return _treemap->find_space(s); }
