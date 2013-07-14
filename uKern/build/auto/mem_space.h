// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef mem_space_h
#define mem_space_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"

#include "auto_quota.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"
#include "paging.h"		// for page attributes
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"
#include "mem_layout.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"
#include "member_offs.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"
#include "per_cpu_data.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"
#include "ram_quota.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"
#include "types.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"
#include "mapdb_types.h"

//
// INTERFACE definition follows 
//

#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"

class Space;
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"

/**
 * An address space.
 *
 * Insertion and lookup functions.
 */
class Mem_space
{
  MEMBER_OFFSET();

  // Space reverse lookup
  friend inline Mem_space* current_mem_space();

public:
  typedef int Status;
  static char const *const name;

  typedef Page::Attr Attr;
  typedef Pdir::Va Vaddr;
  typedef Pdir::Vs Vsize;

  typedef Addr::Addr<Config::PAGE_SHIFT> Phys_addr;
  typedef Addr::Diff<Config::PAGE_SHIFT> Phys_diff;
  typedef Addr::Order<Config::PAGE_SHIFT> Page_order;

  typedef void Reap_list;

  // for map_util
  typedef Page_number V_pfn;
  typedef Page_count V_pfc;
  typedef Addr::Order<0> V_order;

  // Each architecture must provide these members:
  void switchin_context(Mem_space *from);

  /** Insert a page-table entry, or upgrade an existing entry with new
   *  attributes.
   *
   * @param phys Physical address (page-aligned).
   * @param virt Virtual address for which an entry should be created.
   * @param size Size of the page frame -- 4KB or 4MB.
   * @param page_attribs Attributes for the mapping (see
   *                     Mem_space::Page_attrib).
   * @return Insert_ok if a new mapping was created;
   *         Insert_warn_exists if the mapping already exists;
   *         Insert_warn_attrib_upgrade if the mapping already existed but
   *                                    attributes could be upgraded;
   *         Insert_err_nomem if the mapping could not be inserted because
   *                          the kernel is out of memory;
   *         Insert_err_exists if the mapping could not be inserted because
   *                           another mapping occupies the virtual-address
   *                           range
   * @pre phys and virt need to be size-aligned according to the size argument.
   */
  FIASCO_SPACE_VIRTUAL
  Status v_insert(Phys_addr phys, Vaddr virt, Page_order size,
                  Attr page_attribs);

  /** Look up a page-table entry.
   *
   * @param virt Virtual address for which we try the look up.
   * @param phys Meaningful only if we find something (and return true).
   *             If not 0, we fill in the physical address of the found page
   *             frame.
   * @param page_attribs Meaningful only if we find something (and return
   *             true). If not 0, we fill in the page attributes for the
   *             found page frame (see Mem_space::Page_attrib).
   * @param size If not 0, we fill in the size of the page-table slot.  If an
   *             entry was found (and we return true), this is the size
   *             of the page frame.  If no entry was found (and we
   *             return false), this is the size of the free slot.  In
   *             either case, it is either 4KB or 4MB.
   * @return True if an entry was found, false otherwise.
   */
  FIASCO_SPACE_VIRTUAL
  bool v_lookup(Vaddr virt, Phys_addr *phys = 0, Page_order *order = 0,
                Attr *page_attribs = 0);

  /** Delete page-table entries, or some of the entries' attributes.
   *
   * This function works for one or multiple mappings (in contrast to
   * v_insert!).
   *
   * @param virt Virtual address of the memory region that should be changed.
   * @param size Size of the memory region that should be changed.
   * @param page_attribs If nonzero, delete only the given page attributes.
   *                     Otherwise, delete the whole entries.
   * @return Combined (bit-ORed) page attributes that were removed.  In
   *         case of errors, ~Page_all_attribs is additionally bit-ORed in.
   */
  FIASCO_SPACE_VIRTUAL
  L4_fpage::Rights v_delete(Vaddr virt, Page_order size,
                            L4_fpage::Rights page_attribs);

  FIASCO_SPACE_VIRTUAL
  void v_set_access_flags(Vaddr virt, L4_fpage::Rights access_flags);

  /** Set this memory space as the current on on this CPU. */
  void make_current();

  static Mem_space *kernel_space()
  { return _kernel_space; }

  static inline Mem_space *current_mem_space(Cpu_number cpu);


  virtual
  Page_number mem_space_map_max_address() const
  { return Virt_addr(Map_max_address); }

  Page_number map_max_address() const
  { return mem_space_map_max_address(); }

  static Phys_addr page_address(Phys_addr o, Page_order s)
  { return cxx::mask_lsb(o, s); }

  static V_pfn page_address(V_pfn a, Page_order o)
  { return cxx::mask_lsb(a, o); }

  static Phys_addr subpage_address(Phys_addr addr, V_pfc offset)
  { return addr | Phys_diff(offset); }

  struct Fit_size
  {
    typedef cxx::array<Page_order, Page_order, 65> Size_array;
    Size_array const &o;
    Page_order operator () (Page_order i) const { return o[i]; }

    explicit Fit_size(Size_array const &o) :o(o) {}
  };

  FIASCO_SPACE_VIRTUAL
  Fit_size mem_space_fitting_sizes() const __attribute__((pure));

  Fit_size fitting_sizes() const
  { return mem_space_fitting_sizes(); }

  static Mdb_types::Pfn to_pfn(Phys_addr p)
  { return Mdb_types::Pfn(cxx::int_value<Page_number>(p)); }

  static Mdb_types::Pfn to_pfn(V_pfn p)
  { return Mdb_types::Pfn(cxx::int_value<Page_number>(p)); }

  static Mdb_types::Pcnt to_pcnt(Page_order s)
  { return Mdb_types::Pcnt(1) << Mdb_types::Order(cxx::int_value<Page_order>(s) - Config::PAGE_SHIFT); }

  static V_pfn to_virt(Mdb_types::Pfn p)
  { return Page_number(cxx::int_value<Mdb_types::Pfn>(p)); }

  static Page_order to_order(Mdb_types::Order p)
  { return Page_order(cxx::int_value<Mdb_types::Order>(p) + Config::PAGE_SHIFT); }

  static V_pfc to_size(Page_order p)
  { return V_pfc(1) << p; }

  static V_pfc subpage_offset(V_pfn a, Page_order o)
  { return cxx::get_lsb(a, o); }

  Page_order largest_page_size() const
  { return mem_space_fitting_sizes()(Page_order(64)); }

  enum
  {
    Max_num_global_page_sizes = 5
  };

  static Page_order const *get_global_page_sizes(bool finalize = true)
  {
    if (finalize)
      _glbl_page_sizes_finished = true;
    return _glbl_page_sizes;
  }

private:
  Mem_space(const Mem_space &) = delete;

  Ram_quota *_quota;

  static Per_cpu<Mem_space *> _current;
  static Mem_space *_kernel_space;
  static Page_order _glbl_page_sizes[Max_num_global_page_sizes];
  static unsigned _num_glbl_page_sizes;
  static bool _glbl_page_sizes_finished;

#line 214 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"
private:

public:
  enum { Need_xcpu_tlb_flush = false };

#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space-user.cpp"
private:

public:
  /**
   * Read integral type at any virtual address.
   * @param addr Virtual address in user or kernel address space.
   * @param user_space Location of virtual address (user or kernel space).
   * @return Integral value read from address.
   */
  template< typename T >
  T peek(T const *addr, bool user_space);

  /**
   * Read integral type at virtual address in user space.
   * @param addr Virtual address in user address space.
   * @return Integral value read from address.
   */
  template< typename T >
  T peek_user(T const *addr);

  /**
   * Set integral type at virtual address in user space to value.
   * @param addr Virtual address in user address space.
   * @param value New value to be set.
   */
  template< typename T >
  void poke_user(T *addr, T value);

#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
private:

public:
  typedef Pdir Dir_type;

  /** Return status of v_insert. */
  enum // Status
  {
    Insert_ok = 0,		///< Mapping was added successfully.
    Insert_warn_exists,		///< Mapping already existed
    Insert_warn_attrib_upgrade,	///< Mapping already existed, attribs upgrade
    Insert_err_nomem,		///< Couldn't alloc new page table
    Insert_err_exists		///< A mapping already exists at the target addr
  };

  /** Attribute masks for page mappings. */
  enum Page_attrib
  {
    Page_no_attribs = 0,
    /// Page is writable.
    Page_writable = Pt_entry::Writable,
    Page_cacheable = 0,
    /// Page is noncacheable.
    Page_noncacheable = Pt_entry::Noncacheable | Pt_entry::Write_through,
    /// it's a user page.
    Page_user_accessible = Pt_entry::User,
    /// Page has been referenced
    Page_referenced = Pt_entry::Referenced,
    /// Page is dirty
    Page_dirty = Pt_entry::Dirty,
    Page_references = Page_referenced | Page_dirty,
    /// A mask which contains all mask bits
    Page_all_attribs = Page_writable | Page_noncacheable |
                       Page_user_accessible | Page_referenced | Page_dirty,
  };

  // Mapping utilities

  enum				// Definitions for map_util
  {
    Need_insert_tlb_flush = 0,
    Map_page_size = Config::PAGE_SIZE,
    Page_shift = Config::PAGE_SHIFT,
    Map_max_address = Mem_layout::User_max,
    Whole_space = MWORD_BITS,
    Identity_map = 0,
  };


  void	page_map	(Address phys, Address virt,
                         Address size, Attr);

  void	page_unmap	(Address virt, Address size);

  void	page_protect	(Address virt, Address size,
                         unsigned page_attribs);

protected:
  // DATA
  Dir_type *_dir;

public:  
#line 275 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"
  static void
  add_page_size(Page_order o);
  
#line 291 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"
  inline Ram_quota *
  ram_quota() const;
  
#line 296 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"
  /// Avoid deallocation of page table upon Mem_space destruction.
  
  void
  reset_dirty();
  
#line 303 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"
  inline Mem_space::Dir_type*
  dir();
  
#line 308 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"
  inline const Mem_space::Dir_type*
  dir() const;
  
#line 313 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"
  virtual bool
  v_fabricate(Vaddr address, Phys_addr *phys, Page_order *order,
                         Attr *attribs = 0);
  
#line 322 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"
  virtual bool
  is_sigma0() const;
  
#line 81 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  explicit inline Mem_space(Ram_quota *q);
  
#line 98 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  Mem_space(Ram_quota *q, Dir_type* pdir);
  
#line 106 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  static inline bool
  is_full_flush(L4_fpage::Rights rights);
  
#line 113 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  static inline bool
  has_superpages();
  
#line 121 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  static inline void
  tlb_flush(bool = false);
  
#line 128 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  static inline void
  tlb_flush_spaces(bool, Mem_space *, Mem_space *);
  
#line 143 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  inline bool
  set_attributes(Virt_addr virt, Attr page_attribs);
  
#line 249 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  /**
   * Simple page-table lookup.
   *
   * @param virt Virtual address.  This address does not need to be page-aligned.
   * @return Physical address corresponding to a.
   */
  
  inline Address
  virt_to_phys(Address virt) const;
  
#line 262 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  /**
   * Simple page-table lookup.
   *
   * @param virt Virtual address.  This address does not need to be page-aligned.
   * @return Physical address corresponding to a.
   */
  
  inline Address
  pmem_to_phys(Address virt) const;
  
#line 275 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  /**
   * Simple page-table lookup.
   *
   * This method is similar to Space_context's virt_to_phys().
   * The difference is that this version handles Sigma0's
   * address space with a special case:  For Sigma0, we do not
   * actually consult the page table -- it is meaningless because we
   * create new mappings for Sigma0 transparently; instead, we return the
   * logically-correct result of physical address == virtual address.
   *
   * @param a Virtual address.  This address does not need to be page-aligned.
   * @return Physical address corresponding to a.
   */
  
  virtual inline Address
  virt_to_phys_s0(void *a) const;
  
#line 344 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  /**
   * \brief Free all memory allocated for this Mem_space.
   * \pre Runs after the destructor!
   */
  
  ~Mem_space();
  
#line 384 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  inline Address
  phys_dir();
  
#line 473 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  static inline Page_number
  canonize(Page_number v);
  
#line 478 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  static void
  init_page_sizes();

protected:  
#line 249 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"
  static void
  add_global_page_size(Page_order o);
  
#line 84 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  inline bool
  initialize();
  
#line 157 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  inline void
  destroy();
  
#line 431 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  inline void
  sync_kernel();

private:  
#line 161 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  /**
   * Destructor.  Deletes the address space and unregisters it from
   * Space_index.
   */
  
  void
  dir_shutdown();
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 73 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
#include "mem_layout.h"
#line 361 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"

#include <cassert>
#line 365 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
#include "mem_unit.h"
#line 368 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
#include "logdefs.h"
#line 369 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
#include "paging.h"
#line 373 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
#include "kmem.h"
#line 469 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"

#include "cpu.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 289 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"


inline Ram_quota *
Mem_space::ram_quota() const
{ return _quota; }

#line 301 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"


inline Mem_space::Dir_type*
Mem_space::dir()
{ return _dir; }

#line 306 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"


inline const Mem_space::Dir_type*
Mem_space::dir() const
{ return _dir; }

#line 76 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"





inline Mem_space::Mem_space(Ram_quota *q) : _quota(q), _dir(0) {}

#line 104 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


inline bool
Mem_space::is_full_flush(L4_fpage::Rights rights)
{
  return rights & L4_fpage::Rights::R();
}

#line 111 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


inline bool
Mem_space::has_superpages()
{
  return Cpu::have_superpages();
}

#line 118 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"



inline void
Mem_space::tlb_flush(bool)
{
  Mem_unit::tlb_flush();
}

#line 126 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


inline void
Mem_space::tlb_flush_spaces(bool, Mem_space *, Mem_space *)
{
  tlb_flush();
}

#line 141 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


inline bool
Mem_space::set_attributes(Virt_addr virt, Attr page_attribs)
{
  auto i = _dir->walk(virt);

  if (!i.is_valid())
    return false;

  i.set_attribs(page_attribs);
  return true;
}

#line 248 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"

/**
 * Simple page-table lookup.
 *
 * @param virt Virtual address.  This address does not need to be page-aligned.
 * @return Physical address corresponding to a.
 */

inline Address
Mem_space::virt_to_phys(Address virt) const
{
  return dir()->virt_to_phys(virt);
}

#line 261 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"

/**
 * Simple page-table lookup.
 *
 * @param virt Virtual address.  This address does not need to be page-aligned.
 * @return Physical address corresponding to a.
 */

inline Address
Mem_space::pmem_to_phys(Address virt) const
{
  return Mem_layout::pmem_to_phys(virt);
}

#line 274 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"

/**
 * Simple page-table lookup.
 *
 * This method is similar to Space_context's virt_to_phys().
 * The difference is that this version handles Sigma0's
 * address space with a special case:  For Sigma0, we do not
 * actually consult the page table -- it is meaningless because we
 * create new mappings for Sigma0 transparently; instead, we return the
 * logically-correct result of physical address == virtual address.
 *
 * @param a Virtual address.  This address does not need to be page-aligned.
 * @return Physical address corresponding to a.
 */

inline Address
Mem_space::virt_to_phys_s0(void *a) const
{
  return dir()->virt_to_phys((Address)a);
}

#line 382 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


inline Address
Mem_space::phys_dir()
{
  return Mem_layout::pmem_to_phys(_dir);
}

#line 471 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


inline Page_number
Mem_space::canonize(Page_number v)
{ return v; }

#line 82 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


inline bool
Mem_space::initialize()
{
  void *b;
  if (EXPECT_FALSE(!(b = Kmem_alloc::allocator()
	  ->q_alloc(_quota, Config::PAGE_SHIFT))))
    return false;

  _dir = static_cast<Dir_type*>(b);
  _dir->clear(false);	// initialize to zero
  return true; // success
}

#line 154 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"



inline void
Mem_space::destroy()
{}

#line 429 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


inline void
Mem_space::sync_kernel()
{
  _dir->sync(Virt_addr(Mem_layout::User_max), Kmem::dir(),
             Virt_addr(Mem_layout::User_max),
             Virt_size(-Mem_layout::User_max), Pdir::Super_level,
             false,
             Kmem_alloc::q_allocator(_quota));
}

#line 41 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space-user.cpp"



template< typename T > inline T
Mem_space::peek(T const *addr, bool user_space)
{
  return user_space ? peek_user(addr) : *addr;
}

#line 52 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space-user.cpp"



template< typename T > inline T
Mem_space::peek_user(T const *addr)
{
  return *addr;
}

#line 60 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space-user.cpp"



template< typename T > inline void
Mem_space::poke_user(T *addr, T value)
{
  *addr = value;
}

#line 133 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"



inline Mem_space *
Mem_space::current_mem_space(Cpu_number cpu) /// XXX: do not fix, deprecated, remove!
{
  return _current.cpu(cpu);
}

#line 374 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


inline void
Mem_space::make_current()
{
  Cpu::set_pdbr((Mem_layout::pmem_to_phys(_dir)));
  _current.cpu(current_cpu()) = this;
}

#line 389 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"

/*
 * The following functions are all no-ops on native ia32.
 * Pages appear in an address space when the corresponding PTE is made
 * ... unlike Fiasco-UX which needs these special tricks
 */


inline void
Mem_space::page_map(Address, Address, Address, Attr)
{}

#line 400 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


inline void
Mem_space::page_protect(Address, Address, unsigned)
{}

#line 405 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


inline void
Mem_space::page_unmap(Address, Address)
{}

#line 410 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


inline void
Mem_space::switchin_context(Mem_space *from)
{
  // FIXME: this optimization breaks SMP task deletion, an idle thread
  // may run on an already deleted page table
#if 0
  // never switch to kernel space (context of the idle thread)
  if (dir() == Kmem::dir())
    return;
#endif

  if (from != this)
    {
      CNT_ADDR_SPACE_SWITCH;
      make_current();
    }
}

#endif // mem_space_h
