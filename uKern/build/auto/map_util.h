// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef map_util_h
#define map_util_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"

#include "assert_opt.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"
#include "l4_types.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"
#include "space.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util-mem.cpp"

#include "mapdb.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util-mem.cpp"
#include "types.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/map_util-io.cpp"

#include "mapdb.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/map_util-io.cpp"
#include "types.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util-objs.cpp"

#include "kobject_mapdb.h"

//
// INTERFACE definition follows 
//

#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"

class Mapdb;
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"

namespace Mu {

struct Mapping_type_t;
typedef cxx::int_type<unsigned, Mapping_type_t> Mapping_type;

template< typename SPACE, typename M >
inline
L4_fpage::Rights
v_delete(M &m, L4_fpage::Rights flush_rights, bool full_flush)
{
  SPACE* child_space = m->space();
  assert_opt (child_space);
  L4_fpage::Rights res = child_space->v_delete(SPACE::to_virt(m.page()),
                                               SPACE::to_order(m.order()),
                                               flush_rights);
  (void) full_flush;
  assert_kdb (full_flush != child_space->v_lookup(SPACE::to_virt(m.page())));
  return res;
}

template<>
inline
L4_fpage::Rights
v_delete<Obj_space>(Kobject_mapdb::Iterator &m, L4_fpage::Rights flush_rights, bool /*full_flush*/)
{
  Obj_space::Entry *c = static_cast<Obj_space::Entry*>(*m);

  if (c->valid())
    {
      if (flush_rights & L4_fpage::Rights::R())
        c->invalidate();
      else
        c->del_rights(flush_rights & L4_fpage::Rights::WX());
    }
  return L4_fpage::Rights(0);
}

template< typename SIZE_TYPE >
static typename SIZE_TYPE::Order_type
get_order_from_fp(L4_fpage const &fp, int base_order = 0)
{
  typedef typename cxx::underlying_type<SIZE_TYPE>::type Value;
  typedef typename SIZE_TYPE::Order_type Order;

  enum : int {
    Bits = sizeof(Value) * 8 - 1,
    Max  = cxx::is_signed<Value>::value ? Bits - 1 : Bits
  };

  int shift = fp.order() - base_order;

  if (shift <= Max)
    return Order(shift);
  else
    return Order(Max);
}

template<typename Addr, typename Size>
static inline
void free_constraint(Addr &snd_addr, Size &snd_size,
                     Addr &rcv_addr, Size rcv_size,
                     Addr const &hot_spot)
{
  if (rcv_size >= snd_size)
    rcv_addr += cxx::mask_lsb(cxx::get_lsb(hot_spot, rcv_size), snd_size);
  else
    {
      snd_addr += cxx::mask_lsb(cxx::get_lsb(hot_spot, snd_size), rcv_size);
      snd_size = rcv_size;
      // reduce size of address range
    }
}

}
#line 83 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"

template< typename SPACE >
class Map_traits
{
public:
  static bool match(L4_fpage const &from, L4_fpage const &to);
  static bool free_object(typename SPACE::Phys_addr o,
                          typename SPACE::Reap_list **reap_list);

public:  
#line 133 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"
  static inline typename SPACE::Attr
  apply_attribs(typename SPACE::Attr attribs,
                                   typename SPACE::Phys_addr &,
                                   typename SPACE::Attr set_attr);
};
#line 92 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"


class Reap_list
{
private:
  Kobject *_h;
  Kobject **_t;

public:
  Reap_list() : _h(0), _t(&_h) {}
  Kobject ***list() { return &_t; }

public:  
#line 267 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"
  void
  del();
  
#line 291 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"
  inline ~Reap_list();
};
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util-mem.cpp"

extern Static_object<Mapdb> mapdb_mem;
#line 137 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/map_util-io.cpp"


/*
 * Fiasco-ia32
 * Specific code for I/O port protection
 */

#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/map_util-io.cpp"

extern Static_object<Mapdb> mapdb_io;

#line 198 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"
/** Flexpage mapping.
    divert to mem_map (for memory fpages) or io_map (for IO fpages)
    @param from source address space
    @param fp_from flexpage descriptor for virtual-address space range
	in source address space
    @param to destination address space
    @param fp_to flexpage descriptor for virtual-address space range
	in destination address space
    @param offs sender-specified offset into destination flexpage
    @param grant if set, grant the fpage, otherwise map
    @pre page_aligned(offs)
    @return IPC error
    L4_fpage from_fp, to_fp;
    Mword control;code that describes the status of the operation
*/
// Don't inline -- it eats too much stack.
// inline NEEDS ["config.h", io_map]
L4_error
fpage_map(Space *from, L4_fpage fp_from, Space *to,
          L4_fpage fp_to, L4_msg_item control, Reap_list *r);

#line 235 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"
/** Flexpage unmapping.
    divert to mem_fpage_unmap (for memory fpages) or
    io_fpage_unmap (for IO fpages)
    @param space address space that should be flushed
    @param fp    flexpage descriptor of address-space range that should
                 be flushed
    @param me_too If false, only flush recursive mappings.  If true,
                 additionally flush the region in the given address space.
    @param flush_mode determines which access privileges to remove.
    @return combined (bit-ORed) access status of unmapped physical pages
*/
// Don't inline -- it eats too much stack.
// inline NEEDS ["config.h", io_fpage_unmap]
L4_fpage::Rights
fpage_unmap(Space *space, L4_fpage fp, L4_map_mask mask, Kobject ***rl);

#line 294 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"
//////////////////////////////////////////////////////////////////////
//
// Utility functions for all address-space types
//



template <typename SPACE, typename MAPDB> inline L4_error
map(MAPDB* mapdb,
    SPACE* from, Space *from_id,
    typename SPACE::V_pfn snd_addr,
    typename SPACE::V_pfc snd_size,
    SPACE* to, Space *to_id,
    typename SPACE::V_pfn rcv_addr,
    bool grant, typename SPACE::Attr attribs,
    typename SPACE::Reap_list **reap_list = 0);

#line 593 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"
// save access rights for Mem_space

template<typename MAPDB> void
save_access_flags(Mem_space *space, typename Mem_space::V_pfn page_address, bool me_too,
                  typename MAPDB::Mapping *mapping,
                  typename MAPDB::Frame const &mapdb_frame,
                  L4_fpage::Rights page_rights);

#line 616 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"
// do nothing for IO and OBJs

template<typename MAPDB, typename SPACE,
         typename = typename cxx::enable_if<!cxx::is_same<SPACE, Mem_space>::value>::type> void
save_access_flags(SPACE *, typename SPACE::V_pfn, bool,
                  typename MAPDB::Mapping *,
                  typename MAPDB::Frame const &,
                  L4_fpage::Rights);

#line 628 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"
template <typename SPACE, typename MAPDB> L4_fpage::Rights
unmap(MAPDB* mapdb, SPACE* space, Space *space_id,
      typename SPACE::V_pfn start,
      typename SPACE::V_pfc size,
      L4_fpage::Rights rights,
      L4_map_mask mask, typename SPACE::Reap_list **reap_list);

#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util-mem.cpp"
/** Map the region described by "fp_from" of address space "from" into
    region "fp_to" at offset "offs" of address space "to", updating the
    mapping database as we do so.
    @param from source address space
    @param fp_from_{page, size, write, grant} flexpage description for
	virtual-address space range in source address space
    @param to destination address space
    @param fp_to_{page, size} flexpage descripton for virtual-address
	space range in destination address space
    @param offs sender-specified offset into destination flexpage
    @return IPC error code that describes the status of the operation
 */
L4_error __attribute__((nonnull(1, 3)))
mem_map(Space *from, L4_fpage const &fp_from,
        Space *to, L4_fpage const &fp_to, L4_msg_item control);

#line 66 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util-mem.cpp"
/** Unmap the mappings in the region described by "fp" from the address
    space "space" and/or the address spaces the mappings have been
    mapped into.
    @param space address space that should be flushed
    @param fp    flexpage descriptor of address-space range that should
                 be flushed
    @param me_too If false, only flush recursive mappings.  If true,
                 additionally flush the region in the given address space.
    @param restriction Only flush specific task ID.
    @param flush_mode determines which access privileges to remove.
    @return combined (bit-ORed) access status of unmapped physical pages
*/
L4_fpage::Rights __attribute__((nonnull(1)))
mem_fpage_unmap(Space *space, L4_fpage fp, L4_map_mask mask);

#line 98 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util-mem.cpp"
/** The mapping database.
    This is the system's instance of the mapping database.
 */
void
init_mapdb_mem(Space *sigma0);

#line 21 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/map_util-io.cpp"
void init_mapdb_io(Space *sigma0);

#line 29 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/map_util-io.cpp"
/** Map the IO port region described by "fp_from" of address space "from"
    into address space "to". IO ports can only be mapped idempotently,
    therefore there is no offset for fp_from and only those ports are mapped
    that lay in the intersection of fp_from and fp_to
    @param from source address space
    @param fp_from... IO flexpage descripton for IO space range
	in source IO space
    @param to destination address space
    @param fp_to... IO flexpage description for IO space range
	in destination IO space
    @return IPC error code that describes the status of the operation
 */
L4_error __attribute__((nonnull(1, 3)))
io_map(Space *from, L4_fpage const &fp_from,
       Space *to, L4_fpage const &fp_to, L4_msg_item control);

#line 90 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/map_util-io.cpp"
/** Unmap IO mappings.
    Unmap the region described by "fp" from the IO
    space "space" and/or the IO spaces the mappings have been
    mapped into.
    XXX not implemented yet
    @param space address space that should be flushed
    @param fp    IO flexpage descriptor of IO-space range that should
                 be flushed
    @param me_too If false, only flush recursive mappings. If true,
                 additionally flush the region in the given address space.
    @return true if successful
*/
L4_fpage::Rights __attribute__((nonnull(1)))
io_fpage_unmap(Space *space, L4_fpage fp, L4_map_mask mask);

#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util-objs.cpp"
L4_error
obj_map(Space *from, L4_fpage const &fp_from,
        Space *to, L4_fpage const &fp_to, L4_msg_item control,
        Kobject ***reap_list);

#line 48 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util-objs.cpp"
L4_fpage::Rights __attribute__((nonnull(1)))
obj_fpage_unmap(Space * space, L4_fpage fp, L4_map_mask mask,
                Kobject ***reap_list);

#line 65 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util-objs.cpp"
L4_error
obj_map(Space *from, Cap_index snd_addr, unsigned long snd_size,
        Space *to, Cap_index rcv_addr,
        Kobject ***reap_list, bool grant = false,
        Obj_space::Attr attribs = Obj_space::Attr::Full());

#line 81 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util-objs.cpp"
bool
map(Kobject_iface *o, Obj_space* to, Space *to_id, Cap_index rcv_addr,
    Kobject ***reap_list);

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 107 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"

#include <cassert>
#line 109 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"

#include "config.h"
#line 111 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"
#include "context.h"
#line 112 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"
#include "kobject.h"
#line 113 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"
#include "paging.h"
#line 114 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"
#include "warn.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util-mem.cpp"

#include "config.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util-mem.cpp"
#include "mapdb.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util-mem.cpp"
#include "mem_space.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util-mem.cpp"
#include <minmax.h>
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/map_util-io.cpp"

#include "l4_types.h"
#line 15 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/map_util-io.cpp"
#include "assert.h"
#line 16 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/map_util-io.cpp"
#include "space.h"
#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/map_util-io.cpp"
#include "io_space.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util-objs.cpp"

#include "assert.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util-objs.cpp"
#include "assert_opt.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util-objs.cpp"

#include "obj_space.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util-objs.cpp"
#include "l4_types.h"
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util-objs.cpp"
#include "mappable.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 129 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"




template< typename SPACE > inline typename SPACE::Attr
Map_traits<SPACE>::apply_attribs(typename SPACE::Attr attribs,
                                 typename SPACE::Phys_addr &,
                                 typename SPACE::Attr set_attr)
{ return attribs.apply(set_attr); }

#line 115 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"




template<typename SPACE> inline bool
Map_traits<SPACE>::match(L4_fpage const &, L4_fpage const &)
{ return false; }

#line 122 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"



template<typename SPACE> inline bool
Map_traits<SPACE>::free_object(typename SPACE::Phys_addr,
                               typename SPACE::Reap_list **)
{ return false; }

#line 142 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"



template<> inline bool
Map_traits<Io_space>::match(L4_fpage const &from, L4_fpage const &to)
{ return from.is_iopage() && (to.is_iopage() || to.is_all_spaces()); }

#line 152 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"



template<> inline bool
Map_traits<Mem_space>::match(L4_fpage const &from, L4_fpage const &to)
{
  return from.is_mempage() && (to.is_all_spaces() || to.is_mempage());
}

#line 160 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"




template<> inline bool
Map_traits<Obj_space>::match(L4_fpage const &from, L4_fpage const &to)
{ return from.is_objpage() && (to.is_objpage() || to.is_all_spaces()); }

#line 167 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"



template<> inline bool
Map_traits<Obj_space>::free_object(Obj_space::Phys_addr o,
                                   Obj_space::Reap_list **reap_list)
{
  if (o->map_root()->no_mappings())
    {
      o->initiate_deletion(reap_list);
      return true;
    }

  return false;
}

#line 182 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"



template<> inline Obj_space::Attr
Map_traits<Obj_space>::apply_attribs(Obj_space::Attr attribs,
                                     Obj_space::Phys_addr &a,
                                     Obj_space::Attr set_attr)
{
  if (attribs.extra() & ~set_attr.extra())
    a = a->downgrade(~set_attr.extra());

  attribs &= set_attr;
  return attribs;
}

#line 289 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"


inline Reap_list::~Reap_list()
{ del(); }

#line 293 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"

//////////////////////////////////////////////////////////////////////
//
// Utility functions for all address-space types
//



template <typename SPACE, typename MAPDB> inline L4_error
map(MAPDB* mapdb,
    SPACE* from, Space *from_id,
    typename SPACE::V_pfn snd_addr,
    typename SPACE::V_pfc snd_size,
    SPACE* to, Space *to_id,
    typename SPACE::V_pfn rcv_addr,
    bool grant, typename SPACE::Attr attribs,
    typename SPACE::Reap_list **reap_list)
{
  using namespace Mu;

  typedef typename SPACE::Attr Attr;
  typedef typename SPACE::Page_order Page_order;

  typedef typename SPACE::V_pfn V_pfn;
  typedef typename SPACE::V_pfc V_pfc;

  typedef typename MAPDB::Mapping Mapping;
  typedef typename MAPDB::Frame Frame;
  typedef Map_traits<SPACE> Mt;


  L4_error condition = L4_error::None;

  // FIXME: make this debugging code optional
  bool no_page_mapped = true;

  V_pfn const rcv_start = rcv_addr;
  V_pfc const rcv_size = snd_size;

  auto const to_fit_size = to->fitting_sizes();

  // We now loop through all the pages we want to send from the
  // sender's address space, looking up appropriate parent mappings in
  // the mapping data base, and entering a child mapping and a page
  // table entry for the receiver.

  // Special care is taken for 4MB page table entries we find in the
  // sender's address space: If what we will create in the receiver is
  // not a 4MB-mapping, too, we have to find the correct parent
  // mapping for the new mapping database entry: This is the sigma0
  // mapping for all addresses != the 4MB page base address.

  // When overmapping an existing page, flush the interfering
  // physical page in the receiver, even if it is larger than the
  // mapped page.

  // verify sender and receiver virtual addresses are still within
  // bounds; if not, bail out.  Sigma0 may send from any address (even
  // from an out-of-bound one)

  // increment variable for our map loop
  V_pfc size;

  bool from_needs_tlb_flush = false;
  bool to_needs_tlb_flush = false;
  bool need_xcpu_tlb_flush = false;
  V_pfn const to_max = to->map_max_address();
  V_pfn const from_max = from->map_max_address();

  for (;
       snd_size != V_pfc(0)       // pages left for sending?
       && rcv_addr < to_max
       && snd_addr < from_max;

       rcv_addr += size,
       snd_addr += size,
       snd_size -= size)
    {
      // First, look up the page table entries in the sender and
      // receiver address spaces.

      // Sender lookup.
      // make gcc happy, initialized later anyway
      typename SPACE::Phys_addr s_phys;
      Page_order s_order;
      Attr s_attribs;

      // Sigma0 special case: Sigma0 doesn't need to have a
      // fully-constructed page table, and it can fabricate mappings
      // for all physical addresses.
      if (EXPECT_FALSE(! from->v_fabricate(snd_addr, &s_phys,
                                           &s_order, &s_attribs)))
        {
          size = SPACE::to_size(s_order) - SPACE::subpage_offset(snd_addr, s_order);
          if (size >= snd_size)
            break;
          continue;
        }

      // We have a mapping in the sender's address space.
      // FIXME: make this debugging code optional
      no_page_mapped = false;

      // Receiver lookup.

      // The may be used uninitialized warning for this variable is bogus
      // the v_lookup function must initialize the value if it returns true.
      typename SPACE::Phys_addr r_phys;
      Page_order r_order;
      Attr r_attribs;

      // Compute attributes for to-be-inserted frame
      V_pfc page_offset = SPACE::subpage_offset(snd_addr, s_order);
      typename SPACE::Phys_addr i_phys = SPACE::subpage_address(s_phys, page_offset);
      Page_order i_order = to_fit_size(s_order);

      V_pfc i_size = SPACE::to_size(i_order);
      bool const rcv_page_mapped = to->v_lookup(rcv_addr, &r_phys, &r_order, &r_attribs);

      while (i_size > snd_size
          // want to send less than a superpage?
          || i_order > r_order         // not enough space for superpage map?
          || SPACE::subpage_offset(snd_addr, i_order) != V_pfc(0) // snd page not aligned?
          || SPACE::subpage_offset(rcv_addr, i_order) != V_pfc(0) // rcv page not aligned?
          || (rcv_addr + i_size > rcv_start + rcv_size))
        // rcv area to small?
        {
          i_order = to_fit_size(--i_order);
          i_size = SPACE::to_size(i_order);
          if (grant)
            {
              WARN("XXX Can't GRANT page from superpage (%p: " L4_PTR_FMT
                  " -> %p: " L4_PTR_FMT "), demoting to MAP\n",
                  from_id,
                  (unsigned long)cxx::int_value<V_pfn>(snd_addr), to_id,
                  (unsigned long)cxx::int_value<V_pfn>(rcv_addr));
              grant = 0;
            }
        }

      // Also, look up mapping database entry.  Depending on whether
      // we can overmap, either look up the destination mapping first
      // (and compute the sender mapping from it) or look up the
      // sender mapping directly.
      Mapping* sender_mapping = 0;
      // mapdb_frame will be initialized by the mapdb lookup function when
      // it returns true, so don't care about "may be use uninitialized..."
      Frame mapdb_frame;

      if (rcv_page_mapped)
        {
          // We have something mapped.

          // Check if we can upgrade mapping.  Otherwise, flush target
          // mapping.
          if (! grant                         // Grant currently always flushes
              && r_order <= i_order             // Rcv frame in snd frame
              && SPACE::page_address(r_phys, i_order) == i_phys)
            sender_mapping = mapdb->check_for_upgrade(SPACE::to_pfn(r_phys), from_id,
                                                      SPACE::to_pfn(snd_addr), to_id,
                                                      SPACE::to_pfn(rcv_addr), &mapdb_frame);

          if (! sender_mapping)	// Need flush
            unmap(mapdb, to, to_id, SPACE::page_address(rcv_addr, r_order), SPACE::to_size(r_order),
                  L4_fpage::Rights::FULL(), L4_map_mask::full(), reap_list);
        }

      // Loop increment is size of insertion
      size = i_size;

      if (! sender_mapping && mapdb->valid_address(SPACE::to_pfn(s_phys))
          && EXPECT_FALSE(! mapdb->lookup(from_id,
                                          SPACE::to_pfn(SPACE::page_address(snd_addr, s_order)),
                                          SPACE::to_pfn(s_phys),
                                          &sender_mapping, &mapdb_frame)))
        continue;		// someone deleted this mapping in the meantime

      // from here mapdb_frame is always initialized, so ignore the warning
      // in grant / insert

      // At this point, we have a lookup for the sender frame (s_phys,
      // s_size, s_attribs), the max. size of the receiver frame
      // (r_phys), the sender_mapping, and whether a receiver mapping
      // already exists (doing_upgrade).

      Attr i_attribs = Mt::apply_attribs(s_attribs, i_phys, attribs);

      // Do the actual insertion.
      typename SPACE::Status status
        = to->v_insert(i_phys, rcv_addr, i_order, i_attribs);

      switch (status)
        {
        case SPACE::Insert_warn_exists:
        case SPACE::Insert_warn_attrib_upgrade:
        case SPACE::Insert_ok:

          assert_kdb (mapdb->valid_address(SPACE::to_pfn(s_phys)) || status == SPACE::Insert_ok);
          // Never doing upgrades for mapdb-unmanaged memory

          if (grant)
            {
              if (mapdb->valid_address(SPACE::to_pfn(s_phys))
                  && EXPECT_FALSE(!mapdb->grant(mapdb_frame, sender_mapping,
                                                to_id, SPACE::to_pfn(rcv_addr))))
                {
                  // Error -- remove mapping again.
                  to->v_delete(rcv_addr, i_order, L4_fpage::Rights::FULL());
                  to_needs_tlb_flush = true;

                  // may fail due to quota limits
                  condition = L4_error::Map_failed;
                  break;
                }

              from->v_delete(SPACE::page_address(snd_addr, s_order), s_order, L4_fpage::Rights::FULL());
              from_needs_tlb_flush = true;
            }
          else if (status == SPACE::Insert_ok)
            {
              if (mapdb->valid_address(SPACE::to_pfn(s_phys))
                  && !mapdb->insert(mapdb_frame, sender_mapping,
                                    to_id, SPACE::to_pfn(rcv_addr),
                                    SPACE::to_pfn(i_phys), SPACE::to_pcnt(i_order)))
                {
                  // Error -- remove mapping again.
                  to->v_delete(rcv_addr, i_order, L4_fpage::Rights::FULL());
                  to_needs_tlb_flush = true;

                  // XXX This is not race-free as the mapping could have
                  // been used in the mean-time, but we do not care.
                  condition = L4_error::Map_failed;
                  break;
                }
            }

          if (SPACE::Need_xcpu_tlb_flush && SPACE::Need_insert_tlb_flush)
            need_xcpu_tlb_flush = true;

            {
              V_pfc super_offset = SPACE::subpage_offset(snd_addr, i_order);
              if (super_offset != V_pfc(0))
                // Just use OR here because i_phys may already contain
                // the offset. (As is on ARM)
                i_phys = SPACE::subpage_address(i_phys, super_offset);
            }

          break;

        case SPACE::Insert_err_nomem:
          condition = L4_error::Map_failed;
          break;

        case SPACE::Insert_err_exists:
          WARN("map (%s) skipping area (%p/%lx): " L4_PTR_FMT
               " -> %p/%lx: " L4_PTR_FMT "(%lx)", SPACE::name,
               from_id, Kobject_dbg::pointer_to_id(from_id),
               (unsigned long)cxx::int_value<V_pfn>(snd_addr),
               to_id, Kobject_dbg::pointer_to_id(to_id),
               (unsigned long)cxx::int_value<V_pfn>(rcv_addr),
               (unsigned long)cxx::int_value<V_pfc>(i_size));
          // Do not flag an error here -- because according to L4
          // semantics, it isn't.
          break;
        }

      if (sender_mapping)
        mapdb->free(mapdb_frame);

      if (!condition.ok())
        break;
    }

  if (from_needs_tlb_flush || to_needs_tlb_flush)
    {
      SPACE *f = from_needs_tlb_flush ? from : 0;
      SPACE *t = to_needs_tlb_flush   ? to   : 0;
      SPACE::tlb_flush_spaces(false, t, f);
      if (SPACE::Need_xcpu_tlb_flush)
        {
          need_xcpu_tlb_flush = false;
          Context::xcpu_tlb_flush(false, t, f);
        }
    }

  if (need_xcpu_tlb_flush)
    Context::xcpu_tlb_flush(false, to, from);

  // FIXME: make this debugging code optional
  if (EXPECT_FALSE(no_page_mapped))
    WARN("nothing mapped: (%s) from [%p/%lx]: " L4_PTR_FMT
         " size: " L4_PTR_FMT " to [%p/%lx]\n", SPACE::name,
         from_id, Kobject_dbg::pointer_to_id(from_id),
         (unsigned long)cxx::int_value<V_pfn>(snd_addr),
         (unsigned long)cxx::int_value<V_pfc>(rcv_size),
         to_id, Kobject_dbg::pointer_to_id(to_id));

  return condition;
}

//
// IMPLEMENTATION of function templates
//


#line 592 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"

// save access rights for Mem_space

template<typename MAPDB> void
save_access_flags(Mem_space *space, typename Mem_space::V_pfn page_address, bool me_too,
                  typename MAPDB::Mapping *mapping,
                  typename MAPDB::Frame const &mapdb_frame,
                  L4_fpage::Rights page_rights)
{
  if (L4_fpage::Rights accessed = page_rights & (L4_fpage::Rights::RW()))
    {
      // When flushing access attributes from our space as well,
      // cache them in parent space, otherwise in our space.
      if (! me_too || !mapping->parent())
        space->v_set_access_flags(page_address, accessed);
      else
        {
          typename MAPDB::Mapping *parent = mapping->parent();
          typename Mem_space::V_pfn parent_address = Mem_space::to_virt(mapdb_frame.vaddr(parent));
          parent->space()->v_set_access_flags(parent_address, accessed);
        }
    }
}

#line 615 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"

// do nothing for IO and OBJs

template<typename MAPDB, typename SPACE,
         typename = typename cxx::enable_if<!cxx::is_same<SPACE, Mem_space>::value>::type> void
save_access_flags(SPACE *, typename SPACE::V_pfn, bool,
                  typename MAPDB::Mapping *,
                  typename MAPDB::Frame const &,
                  L4_fpage::Rights)
{}

#line 625 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util.cpp"



template <typename SPACE, typename MAPDB> L4_fpage::Rights
unmap(MAPDB* mapdb, SPACE* space, Space *space_id,
      typename SPACE::V_pfn start,
      typename SPACE::V_pfc size,
      L4_fpage::Rights rights,
      L4_map_mask mask, typename SPACE::Reap_list **reap_list)
{
  using namespace Mu;

  typedef typename MAPDB::Mapping Mapping;
  typedef typename MAPDB::Iterator Iterator;
  typedef typename MAPDB::Frame Frame;

  typedef typename SPACE::V_pfn V_pfn;
  typedef typename SPACE::V_pfc V_pfc;

  bool me_too = mask.self_unmap();

  L4_fpage::Rights flushed_rights(0);
  V_pfn end = start + size;
  V_pfn const map_max = space->map_max_address();

  // make gcc happy, initialized later anyway
  typename SPACE::Phys_addr phys;
  V_pfc phys_size;
  V_pfn page_address;

  bool const full_flush = SPACE::is_full_flush(rights);
  bool need_tlb_flush = false;
  bool need_xcpu_tlb_flush = false;

  // iterate over all pages in "space"'s page table that are mapped
  // into the specified region
  for (V_pfn address = start;
       address < end && address < map_max;
       address = page_address + phys_size)
    {
      // for amd64-mem_space's this will skip the hole in the address space
      address = SPACE::canonize(address);

      bool have_page;

      typename SPACE::Page_order phys_order;
      have_page = space->v_fabricate(address, &phys, &phys_order);

      phys_size = SPACE::to_size(phys_order);
      page_address = SPACE::page_address(address, phys_order);

      // phys_size and page_address have now been set up, allowing the
      // use of continue (which evaluates the for-loop's iteration
      // expression involving these to variables).

      if (! have_page)
        continue;

      if (me_too)
        {
          // Rewind flush address to page address.  We always flush
          // the whole page, even if it is larger than the specified
          // flush area.
          address = page_address;
          if (end < address + phys_size)
            end = address + phys_size;
        }

      // all pages shall be handled by our mapping data base
      assert_kdb (mapdb->valid_address(SPACE::to_pfn(phys)));

      Mapping *mapping;
      Frame mapdb_frame;

      if (! mapdb->lookup(space_id, SPACE::to_pfn(page_address), SPACE::to_pfn(phys),
                          &mapping, &mapdb_frame))
        // someone else unmapped faster
        continue;		// skip

      L4_fpage::Rights page_rights(0);

      // Delete from this address space
      if (me_too)
        {
          page_rights |=
            space->v_delete(address, phys_order, rights);

          // assert_kdb (full_flush != space->v_lookup(address));
          need_tlb_flush = true;
          need_xcpu_tlb_flush = true;
        }

      // now delete from the other address spaces
      for (Iterator m(mapdb_frame, mapping, SPACE::to_pfn(address), SPACE::to_pfn(end));
           m;
           ++m)
        {
          page_rights |= v_delete<SPACE>(m, rights, full_flush);
          need_xcpu_tlb_flush = true;
        }

      flushed_rights |= page_rights;

      // Store access attributes for later retrieval
      save_access_flags<MAPDB>(space, page_address, me_too, mapping, mapdb_frame, page_rights);

      if (full_flush)
        mapdb->flush(mapdb_frame, mapping, mask, SPACE::to_pfn(address), SPACE::to_pfn(end));

      if (full_flush)
        Map_traits<SPACE>::free_object(phys, reap_list);

      mapdb->free(mapdb_frame);
    }

  if (need_tlb_flush)
    space->tlb_flush();

  if (SPACE::Need_xcpu_tlb_flush && need_xcpu_tlb_flush)
    Context::xcpu_tlb_flush(true, space, 0);

  return flushed_rights;
}

#endif // map_util_h
