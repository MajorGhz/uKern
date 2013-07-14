// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_ptab.h"
#include "jdb_ptab_i.h"

#line 48 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"

char Jdb_ptab_m::first_char;
#line 81 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"


// available from the jdb_dump module
int jdb_dump_addr_task(Address addr, Space *task, int level)
  __attribute__((weak));
#line 352 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"

static Jdb_ptab_m jdb_ptab_m INIT_PRIORITY(JDB_MODULE_INIT_PRIO);

#line 52 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"
					// arch-dependent type


Jdb_ptab::Jdb_ptab(void *pt_base, Space *task,
                   unsigned char pt_level, unsigned entries,
                   Address virt_base, int level)
: base((Address)pt_base), virt_base(virt_base), _level(level),
  _task(task), entries(entries), cur_pt_level(pt_level), dump_raw(0)
{
  if (entries == 0)
    this->entries = Pdir::entries_at_level(pt_level);
}

#line 64 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"


unsigned
Jdb_ptab::col_width(unsigned column) const
{
  if (column == 0)
    return Jdb_screen::Col_head_size;
  else
    return Jdb_screen::Mword_size_bmode;
}

#line 74 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"


unsigned long
Jdb_ptab::cols() const
{
  return Jdb_screen::cols();
}

#line 86 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"



void
Jdb_ptab::draw_entry(unsigned long row, unsigned long col)
{
  int idx;
  if (col == 0)
    {
      idx = index(row, 1);
      if (idx >= 0)
        print_head(pte(idx));
      else
        putstr("        ");
    }
  else if ((idx = index(row, col)) >= 0)
    print_entry(Pdir::Pte_ptr(pte(idx), cur_pt_level));
  else
    putstr("   ###  ");
}

#line 106 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"


Address
Jdb_ptab::entry_phys(Pdir::Pte_ptr const &entry)
{
  if (!entry.is_leaf())
    return entry.next_level();

  return entry.page_addr();
}

#line 136 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"


unsigned
Jdb_ptab::entry_is_pt_ptr(Pdir::Pte_ptr const &entry,
                          unsigned *entries, unsigned *next_level)
{
  if (!entry.is_valid() || entry.is_leaf())
    return 0;

  *entries = Pdir::entries_at_level(entry.level+1);
  *next_level = entry.level+1;
  return 1;
}

#line 149 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"



void
Jdb_ptab::print_head(void *entry)
{
  printf(L4_PTR_FMT, (Address)entry);
}

#line 157 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"


bool
Jdb_ptab_m::handle_key(Kobject_common *o, int code)
{
  if (code != 'p')
    return false;

  Space *t = Kobject::dcast<Task*>(o);
  if (!t)
    {
      Thread *th = Kobject::dcast<Thread_object*>(o);
      if (!th || !th->space())
        return false;

      t = th->space();
    }

  Jdb_ptab pt_view(static_cast<Mem_space*>(t)->dir(), t, 0, 0, 0, 1);
  pt_view.show(0,0);

  return true;
}

#line 180 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"


unsigned 
Jdb_ptab::key_pressed(int c, unsigned long &row, unsigned long &col)
{
  switch (c)
    {
    default:
      return Nothing;

    case KEY_CURSOR_HOME: // return to previous or go home
      if (_level == 0)
	return Nothing;
      return Back;

    case ' ':
      dump_raw ^= 1;
      return Redraw;

    case KEY_RETURN:	// goto ptab/address under cursor
      if (_level<=7)
	{
          int idx = index(row, col);
          if (idx < 0)
            break;

          Pdir::Pte_ptr pt_entry(pte(idx), cur_pt_level);
	  if (!pt_entry.is_valid())
	    break;

	  void *pd_virt = (void*)Mem_layout::phys_to_pmem(entry_phys(pt_entry));

	  unsigned next_level, entries;

	  if (cur_pt_level < Pdir::Depth
	      && entry_is_pt_ptr(pt_entry, &entries, &next_level))
	    {
	      Jdb_ptab pt_view(pd_virt, _task, next_level, entries,
		               disp_virt(idx), _level+1);
	      if (!pt_view.show(0,1))
		return Exit;
	      return Redraw;
	    }
	  else if (jdb_dump_addr_task != 0)
	    {
	      if (!jdb_dump_addr_task(disp_virt(idx), _task, _level+1))
		return Exit;
	      return Redraw;
	    }
	}
      break;
    }

  return Handled;
}

#line 235 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"


Address
Jdb_ptab::disp_virt(int idx)
{
  Pdir::Va e((Mword)idx << Pdir::lsb_for_level(cur_pt_level));
  return Virt_addr::val(e) + virt_base;
}

#line 243 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"


unsigned long
Jdb_ptab::rows() const
{
  if (cols() > 1)
    return (entries + cols() - 2) / (cols()-1);
  return 0;
}

#line 252 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"


void
Jdb_ptab::print_statline(unsigned long row, unsigned long col)
{
  unsigned long sid = Kobject_dbg::pointer_to_id(_task);

  Address va;
  int idx = index(row, col);
  if (idx >= 0)
    va = disp_virt(idx);
  else
    va = -1;

  Jdb::printf_statline("p:", "<Space>=mode <CR>=goto page/next level",
                       "<level=%1d> <" L4_PTR_FMT "> task D:%lx", cur_pt_level, va, sid);
}

#line 269 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"


Jdb_module::Action_code
Jdb_ptab_m::action(int cmd, void *&args, char const *&fmt, int &next_char)
{
  if (cmd == 0)
    {
      if (args == &first_char)
	{
	  if (first_char != KEY_RETURN && first_char != ' ')
	    {
	      fmt       = "%q";
	      args      = &task;
	      next_char = first_char;
	      return EXTRA_INPUT_WITH_NEXTCHAR;
	    }
	  else
	    {
	      task = 0; //Jdb::get_current_task();
	    }
	}
      else if (args == &task)
	{
#if 0
	  if (!Jdb::is_valid_task(task))
	    {
	      puts(" invalid task");
	      return NOTHING;
	    }
#endif
	}
      else
	return NOTHING;

      Space *s;
      if (task)
        {
          s = Kobject::dcast<Task*>(reinterpret_cast<Kobject*>(task));
          if (!s)
	    return Jdb_module::NOTHING;
        }
      else
        s = Kernel_task::kernel_task();

      void *ptab_base;
      if (!(ptab_base = ((void*)static_cast<Mem_space*>(s)->dir())))
	return Jdb_module::NOTHING;

      Jdb::clear_screen();
      Jdb_ptab pt_view(ptab_base, s);
      pt_view.show(0,1);

    }

  return NOTHING;
}

#line 325 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"


Jdb_module::Cmd const *
Jdb_ptab_m::cmds() const
{
  static Cmd cs[] =
    {
	{ 0, "p", "ptab", "%C",
	  "p[<taskno>]\tshow pagetable of current/given task",
	  &first_char },
    };
  return cs;
}

#line 338 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"


int
Jdb_ptab_m::num_cmds() const
{
  return 1;
}

#line 345 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_ptab.cpp"


Jdb_ptab_m::Jdb_ptab_m()
  : Jdb_module("INFO"), Jdb_kobject_handler(0)
{
  Jdb_kobject::module()->register_handler(this);
}
