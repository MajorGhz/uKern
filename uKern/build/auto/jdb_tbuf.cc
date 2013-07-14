// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_tbuf.h"
#include "jdb_tbuf_i.h"


#line 171 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
static void direct_log_dummy(Tb_entry*, const char*);
#line 159 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

Tb_entry_union *Jdb_tbuf::_tbuf_act;
#line 161 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
Tb_entry_union *Jdb_tbuf::_tbuf_max;
#line 162 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
Mword Jdb_tbuf::_entries;
#line 163 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
Mword Jdb_tbuf::_max_entries;
#line 164 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
Mword Jdb_tbuf::_filter_enabled;
#line 165 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
Mword Jdb_tbuf::_number;
#line 166 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
Mword Jdb_tbuf::_count_mask1;
#line 167 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
Mword Jdb_tbuf::_count_mask2;
#line 168 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
Address Jdb_tbuf::_size;
#line 169 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
Spin_lock<> Jdb_tbuf::_lock;
#line 173 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

void (*Jdb_tbuf::direct_log_entry)(Tb_entry*, const char*) = &direct_log_dummy;

#line 170 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

static void direct_log_dummy(Tb_entry*, const char*)
{}

#line 196 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

/** Clear tracebuffer. */

void
Jdb_tbuf::clear_tbuf()
{
  Mword i;

  for (i = 0; i < _max_entries; i++)
    buffer()[i].clear();

  _tbuf_act = buffer();
  _entries = 0;
}

#line 210 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

/** Return pointer to new tracebuffer entry. */

Tb_entry*
Jdb_tbuf::new_entry()
{
  Tb_entry *tb;
  {
    auto guard = lock_guard(_lock);

    tb = _tbuf_act;

    status()->current = (Address)tb;

    if (++_tbuf_act >= _tbuf_max)
      _tbuf_act = buffer();

    if (_entries < _max_entries)
      _entries++;

    tb->number(++_number);
  }

  tb->rdtsc();
  tb->rdpmc1();
  tb->rdpmc2();

  return tb;
}

#line 247 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

/** Commit tracebuffer entry. */

void
Jdb_tbuf::commit_entry()
{
  if (EXPECT_FALSE((_number & _count_mask2) == 0))
    {
      if (_number & _count_mask1)
	status()->window[0].version++; // 64-bit value!
      else
	status()->window[1].version++; // 64-bit value!

#if 0 // disbale Tbuf vIRQ for the time beeing (see bug #357)
      // fire the virtual 'buffer full' irq
      if (_observer)
        {
          auto guard = lock_guard(cpu_lock);
	  _observer->notify();
	}
#endif
    }
}

#line 279 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"


Mword
Jdb_tbuf::entries()
{
  if (!_filter_enabled)
    return unfiltered_entries();

  Mword cnt = 0;

  for (Mword idx = 0; idx<unfiltered_entries(); idx++)
    if (!buffer()[idx].hidden())
      cnt++;

  return cnt;
}

#line 322 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

/** Return pointer to tracebuffer event.
 * @param  position of event in tracebuffer:
 *         0 is last event, 1 the event before and so on
 * @return pointer to tracebuffer event
 *
 * event with idx == 0 is the last event queued in
 * event with idx == 1 is the event before */

Tb_entry*
Jdb_tbuf::unfiltered_lookup(Mword idx)
{
  if (!event_valid(idx))
    return 0;

  Tb_entry_union *e = _tbuf_act - idx - 1;

  if (e < buffer())
    e += _max_entries;

  return e;
}

#line 344 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

/** Return pointer to tracebuffer event.
 * Don't count hidden events.
 * @param  position of event in tracebuffer:
 *         0 is last event, 1 the event before and so on
 * @return pointer to tracebuffer event
 *
 * event with idx == 0 is the last event queued in
 * event with idx == 1 is the event before */

Tb_entry*
Jdb_tbuf::lookup(Mword look_idx)
{
  if (!_filter_enabled)
    return unfiltered_lookup(look_idx);

  for (Mword idx = 0;; idx++)
    {
      Tb_entry *e = unfiltered_lookup(idx);

      if (!e)
	return 0;
      if (e->hidden())
	continue;
      if (!look_idx--)
	return e;
    }
}

#line 372 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"


Mword
Jdb_tbuf::unfiltered_idx(Tb_entry const *e)
{
  Tb_entry_union const *ef = static_cast<Tb_entry_union const *>(e);
  Mword idx = _tbuf_act - ef - 1;

  if (idx > _max_entries)
    idx += _max_entries;

  return idx;
}

#line 385 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

/** Tb_entry => tracebuffer index. */

Mword
Jdb_tbuf::idx(Tb_entry const *e)
{
  if (!_filter_enabled)
    return unfiltered_idx(e);

  Tb_entry_union const *ef = static_cast<Tb_entry_union const*>(e);
  Mword idx = (Mword) - 1;

  for (;;)
    {
      if (!ef->hidden())
	idx++;
      ef++;
      if (ef >= buffer() + _max_entries)
	ef -= _max_entries;
      if (ef == _tbuf_act)
	break;
    }

  return idx;
}

#line 424 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

/** Event number => tracebuffer index.
 * @param  nr  number of event
 * @return tracebuffer index of event which has the number nr or
 *         -1 if there is no event with this number or
 *         -2 if the event is currently hidden. */

Mword
Jdb_tbuf::search_to_idx(Mword nr)
{
  if (nr == (Mword) - 1)
    return (Mword) - 1;

  Tb_entry *e;

  if (!_filter_enabled)
    {
      e = search(nr);
      if (!e)
	return (Mword) - 1;
      return unfiltered_idx(e);
    }

  for (Mword idx_u = 0, idx_f = 0; (e = unfiltered_lookup(idx_u)); idx_u++)
    {
      if (e->number() == nr)
	return e->hidden() ? (Mword) - 2 : idx_f;

      if (!e->hidden())
	idx_f++;
    }

  return (Mword)-1;
}

#line 458 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

/** Return some information about log event.
 * @param idx number of event to determine the info
 * @retval number event number
 * @retval tsc event value of CPU cycles
 * @retval pmc event value of perf counter cycles
 * @return 0 if something wrong, 1 if everything ok */

int
Jdb_tbuf::event(Mword idx, Mword *number, Unsigned32 *kclock,
		Unsigned64 *tsc, Unsigned32 *pmc1, Unsigned32 *pmc2)
{
  Tb_entry *e = lookup(idx);

  if (!e)
    return false;

  *number = e->number();
  if (kclock)
    *kclock = e->kclock();
  if (tsc)
    *tsc = e->tsc();
  if (pmc1)
    *pmc1 = e->pmc1();
  if (pmc2)
    *pmc2 = e->pmc2();
  return true;
}

#line 486 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

/** Get difference CPU cycles between event idx and event idx+1.
 * @param idx position of first event in tracebuffer
 * @retval difference in CPU cycles
 * @return 0 if something wrong, 1 if everything ok */

int
Jdb_tbuf::diff_tsc(Mword idx, Signed64 *delta)
{
  Tb_entry *e      = lookup(idx);
  Tb_entry *e_prev = lookup(idx + 1);

  if (!e || !e_prev)
    return false;

  *delta = e->tsc() - e_prev->tsc();
  return true;
}

#line 504 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

/** Get difference perfcnt cycles between event idx and event idx+1.
 * @param idx position of first event in tracebuffer
 * @param nr  number of perfcounter (0=first, 1=second)
 * @retval difference in perfcnt cycles
 * @return 0 if something wrong, 1 if everything ok */

int
Jdb_tbuf::diff_pmc(Mword idx, Mword nr, Signed32 *delta)
{
  Tb_entry *e      = lookup(idx);
  Tb_entry *e_prev = lookup(idx + 1);

  if (!e || !e_prev)
    return false;

  switch (nr)
    {
    case 0: *delta = e->pmc1() - e_prev->pmc1(); break;
    case 1: *delta = e->pmc2() - e_prev->pmc2(); break;
    }

  return true;
}
