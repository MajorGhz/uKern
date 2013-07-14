// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef mem_region_h
#define mem_region_h

//
// INTERFACE definition follows 
//

#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/mem_region.cpp"

class Mem_region
{
public:
  unsigned long start, end;

  Mem_region() : start(0), end(0) {}

  Mem_region(unsigned long start, unsigned long end) : start(start), end(end) {}

  bool valid() const { return start < end; }

  bool operator < (Mem_region const &o) const
  { return end < o.start; }

  bool overlaps(Mem_region const &o) const
  { return !(o < *this || *this < o); }

  bool contains(Mem_region const &o) const
  { return start <= o.start && end >= o.end; }

  void merge(Mem_region const &r)
  {
    start = start < r.start ? start : r.start;
    end   = end > r.end     ? end   : r.end;
  }

  unsigned long size() const
  { return end - start + 1; }

};
#line 33 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/mem_region.cpp"


class Mem_region_map_base
{
private:
  unsigned _s;
  unsigned _l;
  Mem_region _r[0];

public:
  Mem_region_map_base(unsigned size) : _s(size), _l(0) {}

public:  
#line 73 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/mem_region.cpp"
  inline bool
  add(Mem_region const &r);
  
#line 109 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/mem_region.cpp"
  inline bool
  sub(Mem_region const &r);
  
#line 147 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/mem_region.cpp"
  inline unsigned 
  length() const;
  
#line 153 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/mem_region.cpp"
  inline unsigned 
  capacity() const;
  
#line 158 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/mem_region.cpp"
  inline Mem_region const &
  operator[](unsigned idx) const;
  
#line 163 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/mem_region.cpp"
  inline Mem_region &
  operator[](unsigned idx);

private:  
#line 62 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/mem_region.cpp"
  inline void
  del(unsigned start, unsigned end);
};
#line 45 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/mem_region.cpp"

template< unsigned E >
class Mem_region_map : public Mem_region_map_base
{
public:
  enum { Entries = E };
  Mem_region_map() : Mem_region_map_base(Entries) {}

private:
  Mem_region _r[Entries];
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 60 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/mem_region.cpp"


inline void
Mem_region_map_base::del(unsigned start, unsigned end)
{
  register unsigned delta = end - start;
  for (unsigned p = start; p < end; ++p)
    _r[p] = _r[p + delta];

  _l -= delta;
}

#line 71 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/mem_region.cpp"


inline bool
Mem_region_map_base::add(Mem_region const &r)
{
  if (!r.valid())
    return true;

  unsigned pos = 0;
  for (;pos < _l && _r[pos] < r; ++pos) ;
  if (_l > pos && !(r < _r[pos]))
    { // overlap -> merge
      _r[pos].merge(r);
      for (unsigned p = pos + 1; p < _l; ++p)
	{
	  if (!(_r[pos] < _r[p]))
	    _r[pos].merge(_r[p]);
	  else
	    {
	      del(pos + 1, p);
	      return true;
	    }
	}
      _l = pos + 1;
      return true;
    }

  if (_l >= _s)
    return false;

  for (unsigned p = _l; p > pos; --p) _r[p] = _r[p-1];
  ++_l;
  _r[pos] = r;
  return true;
}

#line 106 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/mem_region.cpp"



inline bool
Mem_region_map_base::sub(Mem_region const &r)
{
  if (!r.valid())
    return true;

  unsigned pos;
  for (pos = 0; pos < _l; ++pos)
    {
      if (_r[pos].overlaps(r))
	{
	  if (r.contains(_r[pos]))
	    {
	      del(pos, pos+1);
	      --pos; // ensure we do not skip the next element
	    }
	  else if (r.start <= _r[pos].start)
	    _r[pos].start = r.end + 1;
	  else if (r.end >= _r[pos].end)
	    _r[pos].end = r.start - 1;
	  else
	    {
	      if (_l >= _s)
		return false;

	      for (unsigned p = _l; p > pos; --p) _r[p] = _r[p-1];
	      ++_l;
	      _r[pos+1].start = r.end + 1;
	      _r[pos+1].end = _r[pos].end;
	      _r[pos].end = r.start - 1;
	    }
	}
    }
  return true;
}

#line 144 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/mem_region.cpp"



inline unsigned 
Mem_region_map_base::length() const
{ return _l; }

#line 150 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/mem_region.cpp"



inline unsigned 
Mem_region_map_base::capacity() const
{ return _s; }

#line 156 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/mem_region.cpp"


inline Mem_region const &
Mem_region_map_base::operator[](unsigned idx) const
{ return _r[idx]; }

#line 161 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/lib/libk/mem_region.cpp"


inline Mem_region &
Mem_region_map_base::operator[](unsigned idx)
{ return _r[idx]; }

#endif // mem_region_h
