// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef l4_buf_iter_h
#define l4_buf_iter_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/l4_buf_iter.cpp"

#include <types.h>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/l4_buf_iter.cpp"
#include <l4_msg_item.h>
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/l4_buf_iter.cpp"
#include <l4_fpage.h>
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/l4_buf_iter.cpp"
#include <l4_types.h>

//
// INTERFACE definition follows 
//

#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/l4_buf_iter.cpp"

class L4_buf_iter
{
public:
  struct Item
  {
    L4_msg_item b;
    Mword d;

    Item() : b(0)
#ifndef NDEBUG
	     , d(0)
#endif
    {}
  };

  explicit L4_buf_iter(Utcb const *utcb, unsigned start)
  : _buf(&utcb->buffers[start]), _max(&utcb->buffers[Utcb::Max_buffers])
  { next(); }
  bool more() const { return _buf < _max; }
  Item const *get() const { return &c; }
  bool next();

private:
  Mword const *_buf;
  Mword const *const _max;
  Item c;
};
#line 35 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/l4_buf_iter.cpp"

class L4_snd_item_iter
{
public:
  struct Item
  {
    L4_msg_item b;
    Mword d;

    Item()
    : b(0)
#ifndef NDEBUG
      , d(0)
#endif
    {}
  };

  explicit L4_snd_item_iter(Utcb const *utcb, unsigned offset)
  : _buf(&utcb->values[offset]),
    _max(&utcb->values[Utcb::Max_words]) {}
  bool more() const { return _buf < _max; }
  Item const *get() const { return &c; }
  bool next();

private:
  Mword const *_buf;
  Mword const *const _max;
  Item c;
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 67 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/l4_buf_iter.cpp"


inline bool
L4_buf_iter::next()
{
  c.b = L4_msg_item(_buf[0]);
  if (EXPECT_FALSE(c.b.is_void()))
    return false;

  if (c.b.type() == L4_msg_item::Map && c.b.is_small_obj())
    c.d = c.b.get_small_buf().raw();
  else
    {
      ++_buf;
      if (EXPECT_FALSE(_buf >= _max))
	{
	  c.b = L4_msg_item(0);
	  return false;
	}

      c.d = _buf[0];
    }
  ++_buf;
  return true;
}

#line 92 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/l4_buf_iter.cpp"



inline bool
L4_snd_item_iter::next()
{
  c.b = L4_msg_item(_buf[0]);

  ++_buf;

  if (EXPECT_FALSE(c.b.is_void()))
    return true;

  if (EXPECT_FALSE(_buf >= _max))
    return false;

  c.d = _buf[0];

  ++_buf;
  return true;
}

#endif // l4_buf_iter_h
