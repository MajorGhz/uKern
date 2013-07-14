// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_iomap.h"
#include "jdb_iomap_i.h"

#line 25 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_iomap.cpp"

char     Jdb_iomap::first_char;
#line 27 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_iomap.cpp"
Space   *Jdb_iomap::space;
#line 154 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_iomap.cpp"

static Jdb_iomap jdb_iomap INIT_PRIORITY(JDB_MODULE_INIT_PRIO);

#line 28 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_iomap.cpp"


void
Jdb_iomap::show()
{
  // base addresses of the two IO bitmap pages
  Address bitmap_1, bitmap_2;
  bitmap_1 = space->virt_to_phys(Mem_layout::Io_bitmap);
  bitmap_2 = space->virt_to_phys(Mem_layout::Io_bitmap + Config::PAGE_SIZE);

  Jdb::clear_screen();

  printf("\nIO bitmap for space %p ", space);
  if(bitmap_1 == ~0UL && bitmap_2 == ~0UL)
    { // no memory mapped for the IO bitmap
      puts("not mapped");
      return;
    }
  else
    {
      putstr("mapped to [");
      if (bitmap_1 != ~0UL)
	printf(L4_PTR_FMT " ", (Address)Kmem::phys_to_virt(bitmap_1));
      else
	putstr("   --    ");

      if (bitmap_2 != ~0UL)
	printf("/ " L4_PTR_FMT, (Address)Kmem::phys_to_virt(bitmap_2));
      else
	putstr("/    --   ");
    }

  puts("]\n\nPorts assigned:");

  bool mapped = false, any_mapped = false;
  unsigned count=0;

  for(unsigned i = 0; i < Mem_layout::Io_port_max; i++ )
    {
      if (space->io_lookup(i) != mapped)
	{
	  if(! mapped)
	    {
	      mapped = any_mapped = true;
	      printf("%04x-", i);
	    }
	  else
	    {
	      mapped = false;
	      printf("%04x ", i-1);
	    }
	}
      if(mapped)
	count++;
    }
  if(mapped)
    printf("%04x ", Mem_layout::Io_port_max -1);

  if (!any_mapped)
    putstr("<none>");

  printf("\n\nPort counter: %ld ", space->get_io_counter() );
  if(count == space->get_io_counter())
    puts("(correct)");
  else
    printf("%sshould be %d\033[m\n", Jdb::esc_emph, count);
}

#line 95 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_iomap.cpp"


Jdb_module::Action_code
Jdb_iomap::action(int cmd, void *&args, char const *&fmt, int &next_char)
{
  if (cmd == 0)
    {
      if (args == &first_char)
	{
	  if (isxdigit(first_char))
	    {
	      fmt       = "%q";
	      args      = &task;
	      next_char = first_char;
	      return EXTRA_INPUT_WITH_NEXTCHAR;
	    }
          else
            task = 0;
	}
      else if (args != &task)
        return NOTHING;

      if (!task)
        return NOTHING;

      space = Kobject::dcast<Task*>(reinterpret_cast<Kobject*>(task));
      if (!space)
        return NOTHING;

      show();
    }

  return NOTHING;
}

#line 129 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_iomap.cpp"


Jdb_module::Cmd const *
Jdb_iomap::cmds() const
{
  static Cmd cs[] =
    {
	{ 0, "r", "iomap", "%C",
	  "r[<taskno>]\tdisplay IO bitmap of current/given task",
	  &first_char },
    };
  return cs;
}

#line 142 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_iomap.cpp"


int
Jdb_iomap::num_cmds() const
{
  return 1;
}

#line 149 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_iomap.cpp"


Jdb_iomap::Jdb_iomap()
  : Jdb_module("INFO")
{}
