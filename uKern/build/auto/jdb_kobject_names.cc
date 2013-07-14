// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_kobject_names.h"
#include "jdb_kobject_names_i.h"

#line 27 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"

//-----------------------------------------------------------------------

#line 41 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"



enum
{
  Name_buffer_size = 8192,
  Name_entries = Name_buffer_size / sizeof(Jdb_kobject_name),
};
#line 49 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"


char const *const Jdb_kobject_name::static_type = "Jdb_kobject_names";
#line 52 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
Jdb_kobject_name *Jdb_kobject_name::_names;
#line 70 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"

static Spin_lock<> allocator_lock;
#line 209 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"


STATIC_INITIALIZE(Jdb_kobject_name);

#line 53 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"



unsigned
Jdb_kobject_name::max_len()
{ return sizeof(_name); }

#line 59 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"


void
Jdb_kobject_name::name(char const *name)
{
  strncpy(_name, name, sizeof(_name));
}

#line 66 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"


Jdb_kobject_name::Jdb_kobject_name()
{ _name[0] = 0; }

#line 72 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"


void *
Jdb_kobject_name::operator new(size_t) throw()
{
  Jdb_kobject_name *n = _names;
  while (1)
    {
      void **o = reinterpret_cast<void**>(n);
      if (!*o)
	{
	  auto g = lock_guard(allocator_lock);
	  if (!*o)
	    {
	      *o = (void*)10;
	      return n;
	    }
	}

      ++n;

      if ((n - _names) >= Name_entries)
	return 0;
    }
}

#line 97 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"


void
Jdb_kobject_name::operator delete(void *p)
{
  auto g = lock_guard(allocator_lock);
  void **o = reinterpret_cast<void**>(p);
  *o = 0;
}

#line 106 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"


void
Jdb_kobject_name::clear_name()
{
  for (unsigned i = 0; i < max_len(); ++i)
    _name[i] = 0;
}

#line 132 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"


int
Jdb_name_hdl::show_kobject_short(char *buf, int max, Kobject_common *o)
{
  Jdb_kobject_name *ex
    = Jdb_kobject_extension::find_extension<Jdb_kobject_name>(o);

  if (ex)
    return snprintf(buf, max, " {%-*.*s}", ex->max_len(), ex->max_len(), ex->name());

  return 0;
}

#line 145 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"


bool
Jdb_name_hdl::invoke(Kobject_common *o, Syscall_frame *f, Utcb *utcb)
{
  switch (utcb->values[0])
    {
    case Op_set_name:
        {
          Jdb_kobject_name *ne = new Jdb_kobject_name();
          if (!ne)
            {
              f->tag(Kobject_iface::commit_result(-L4_err::ENomem));
              return true;
            }

          char const *name = reinterpret_cast<char const*>(&utcb->values[1]);
          ne->clear_name();
          strncpy(ne->name(), name, ne->max_len());
          o->dbg_info()->_jdb_data.add(ne);
          f->tag(Kobject_iface::commit_result(0));
          return true;
        }
    case Op_get_name:
        {
          Kobject_dbg::Iterator o = Kobject_dbg::id_to_obj(utcb->values[1]);
          if (o == Kobject_dbg::end())
            {
              f->tag(Kobject_iface::commit_result(-L4_err::ENoent));
              return true;
            }
          Jdb_kobject_name *n = Jdb_kobject_extension::find_extension<Jdb_kobject_name>(Kobject::from_dbg(o));
          if (!n)
            {
              f->tag(Kobject_iface::commit_result(-L4_err::ENoent));
              return true;
            }

          unsigned l = min<unsigned>(n->max_len(), sizeof(utcb->values));
          char *dst = reinterpret_cast<char *>(utcb->values);
          strncpy(dst, n->name(), l);
          dst[l - 1] = 0;

          f->tag(Kobject_iface::commit_result(0));
          return true;
        }
    }
  return false;
}

#line 194 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"

FIASCO_INIT
void
Jdb_kobject_name::init()
{
  _names = (Jdb_kobject_name*)Kmem_alloc::allocator()->unaligned_alloc(Name_buffer_size);
  if (!_names)
    panic("No memory for thread names");

  for (int i=0; i<Name_entries; i++)
    *reinterpret_cast<unsigned long*>(_names + i) = 0;

  static Jdb_name_hdl hdl;
  Jdb_kobject::module()->register_handler(&hdl);
}
