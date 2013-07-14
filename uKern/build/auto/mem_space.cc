// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "mem_space.h"
#include "mem_space_i.h"

#line 220 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"


//---------------------------------------------------------------------------

#line 236 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"

DEFINE_PER_CPU Per_cpu<Mem_space *> Mem_space::_current;
#line 238 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"


char const * const Mem_space::name = "Mem_space";
#line 241 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"
Mem_space *Mem_space::_kernel_space;
#line 242 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"

static Mem_space::Fit_size::Size_array __mfs;
#line 244 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"
Mem_space::Page_order Mem_space::_glbl_page_sizes[Max_num_global_page_sizes];
#line 245 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"
unsigned Mem_space::_num_glbl_page_sizes;
#line 246 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"
bool Mem_space::_glbl_page_sizes_finished;

#line 247 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"


void
Mem_space::add_global_page_size(Page_order o)
{
  assert_kdb (!_glbl_page_sizes_finished);
  unsigned i;
  for (i = 0; i < _num_glbl_page_sizes; ++i)
    {
      if (_glbl_page_sizes[i] == o)
        return;

      if (_glbl_page_sizes[i] < o)
        break;
    }

  assert (_num_glbl_page_sizes + 1 < Max_num_global_page_sizes);

  for (unsigned x = _num_glbl_page_sizes; x > i; --x)
    _glbl_page_sizes[x] = _glbl_page_sizes[x - 1];

  _glbl_page_sizes[i] = o;
  assert (_glbl_page_sizes[_num_glbl_page_sizes] <= Page_order(Config::PAGE_SHIFT));

  ++_num_glbl_page_sizes;
}

#line 273 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"


void
Mem_space::add_page_size(Page_order o)
{
  add_global_page_size(o);
  for (Page_order c = o; c < __mfs.size(); ++c)
    __mfs[c] = o;
}

#line 282 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"


Mem_space::Fit_size
Mem_space::mem_space_fitting_sizes() const
{
  return Fit_size(__mfs);
}

#line 294 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"


/// Avoid deallocation of page table upon Mem_space destruction.

void
Mem_space::reset_dirty()
{ _dir = 0; }

#line 311 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"


bool
Mem_space::v_fabricate(Vaddr address, Phys_addr *phys, Page_order *order,
                       Attr *attribs)
{
  return v_lookup(cxx::mask_lsb(address, Page_order(Config::PAGE_SHIFT)),
      phys, order, attribs);
}

#line 320 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/mem_space.cpp"


bool
Mem_space::is_sigma0() const
{ return false; }
