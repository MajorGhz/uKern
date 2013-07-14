// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "map_util.h"
#include "map_util_i.h"


#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util-objs.cpp"

L4_error
obj_map(Space *from, L4_fpage const &fp_from,
        Space *to, L4_fpage const &fp_to, L4_msg_item control,
        Kobject ***reap_list)
{
  assert_opt (from);
  assert_opt (to);

  Cap_index rcv_addr = fp_to.obj_index();
  Cap_index snd_addr = fp_from.obj_index();
  Order so = Mu::get_order_from_fp<Cap_diff>(fp_from);
  Order ro = Mu::get_order_from_fp<Cap_diff>(fp_to);
  Cap_index offs = Cap_index((Mword)control.index());

  snd_addr = cxx::mask_lsb(snd_addr, so);
  rcv_addr = cxx::mask_lsb(rcv_addr, ro);

  Mu::free_constraint(snd_addr, so, rcv_addr, ro, offs);
  Cap_diff snd_size = Cap_diff(1) << so;

  if (snd_size == Cap_diff(0))
    return L4_error::None;

  Obj_space::Attr attribs(fp_from.rights(), L4_msg_item::C_weak_ref ^ control.attr());

  return map<Obj_space>((Kobject_mapdb*)0,
                        from, from, Obj_space::V_pfn(snd_addr),
                        snd_size,
                        to, to, Obj_space::V_pfn(rcv_addr),
                        control.is_grant(), attribs,
                        reap_list);
}

#line 47 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util-objs.cpp"

L4_fpage::Rights __attribute__((nonnull(1)))
obj_fpage_unmap(Space * space, L4_fpage fp, L4_map_mask mask,
                Kobject ***reap_list)
{
  assert_opt (space);
  Order size = Mu::get_order_from_fp<Cap_diff>(fp);
  Cap_index addr = fp.obj_index();
  addr = cxx::mask_lsb(addr, size);

  // XXX prevent unmaps when a task has no caps enabled

  return unmap<Obj_space>((Kobject_mapdb*)0, space, space,
               Obj_space::V_pfn(addr), Obj_space::V_pfc(1) << size,
               fp.rights(), mask, reap_list);
}

#line 63 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util-objs.cpp"


L4_error
obj_map(Space *from, Cap_index snd_addr, unsigned long snd_size,
        Space *to, Cap_index rcv_addr,
        Kobject ***reap_list, bool grant,
        Obj_space::Attr attribs)
{
  assert_opt (from);
  assert_opt (to);

  return map<Obj_space>((Kobject_mapdb*)0,
	     from, from, Obj_space::V_pfn(snd_addr),
	     Cap_diff(snd_size),
	     to, to, Obj_space::V_pfn(rcv_addr),
	     grant, attribs, reap_list);
}

#line 80 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/map_util-objs.cpp"

bool
map(Kobject_iface *o, Obj_space* to, Space *to_id, Cap_index rcv_addr,
    Kobject ***reap_list)
{
  assert_opt (o);
  assert_opt (to);
  assert_opt (to_id);

  typedef Obj_space SPACE;
  typedef Obj_space::V_pfn Addr;
  typedef Obj_space::Page_order Size;

  if (EXPECT_FALSE(rcv_addr >= to->map_max_address()))
    return 0;

  // Receiver lookup.
  Obj_space::Phys_addr r_phys;
  Size r_size;
  Obj_space::Attr r_attribs;

  Addr ra(rcv_addr);
  if (to->v_lookup(ra, &r_phys, &r_size, &r_attribs))
    unmap((Kobject_mapdb*)0, to, to_id, ra, Obj_space::V_pfc(1) << r_size,
          L4_fpage::Rights::FULL(), L4_map_mask::full(), reap_list);

  // Do the actual insertion.
  Obj_space::Status status = to->v_insert(o, ra, Size(0), Obj_space::Attr::Full());

  switch (status)
    {
    case SPACE::Insert_warn_exists:
    case SPACE::Insert_warn_attrib_upgrade:
    case SPACE::Insert_ok:

      if (status == SPACE::Insert_ok)
	{
	  if (! o->map_root()->insert(0, to_id, ra))
	    {
	      to->v_delete(Obj_space::V_pfn(rcv_addr), Size(0), L4_fpage::Rights::FULL());
	      return 0;
	    }
	}
      break;

    case SPACE::Insert_err_nomem:
      return 0;

    case SPACE::Insert_err_exists:
      // Do not flag an error here -- because according to L4
      // semantics, it isn't.
      break;
    }

  return 1;
}