// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_tbuf_h
#define jdb_tbuf_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

#include "jdb_ktrace.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
#include "l4_types.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
#include "std_macros.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
#include "tb_entry.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
#include "spin_lock.h"

//
// INTERFACE definition follows 
//

#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

class Context;
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
class Log_event;
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
struct Tracebuffer_status;
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

class Jdb_tbuf
{
public:
  static void (*direct_log_entry)(Tb_entry*, const char*);

  enum
  {
    Event  = 1,
    Result = 2
  };

protected:
  static Tb_entry_union *_tbuf_act;	// current entry
  static Tb_entry_union *_tbuf_max;
  static Mword		_entries;	// number of occupied entries
  static Mword		_max_entries;	// maximum number of entries
  static Mword          _filter_enabled;// !=0 if filter is active
  static Mword		_number;	// current event number
  static Mword		_count_mask1;
  static Mword		_count_mask2;
  static Address        _size;		// size of memory area for tbuffer
  static Spin_lock<>    _lock;

public:  
#line 177 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  static inline Tracebuffer_status *
  status();
  
#line 191 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  static inline Address
  size();
  
#line 197 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Clear tracebuffer. */
  
  static void
  clear_tbuf();
  
#line 211 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Return pointer to new tracebuffer entry. */
  
  static Tb_entry*
  new_entry();
  
#line 241 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  template<typename T> static inline T*
  new_entry();
  
#line 248 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Commit tracebuffer entry. */
  
  static void
  commit_entry();
  
#line 271 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Return number of entries currently allocated in tracebuffer.
   * @return number of entries */
  
  static inline Mword
  unfiltered_entries();
  
#line 281 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  static Mword
  entries();
  
#line 296 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Return maximum number of entries in tracebuffer.
   * @return number of entries */
  
  static inline Mword
  max_entries();
  
#line 305 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Set maximum number of entries in tracebuffer. */
  
  static inline void
  max_entries(Mword num);
  
#line 313 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Check if event is valid.
   * @param idx position of event in tracebuffer
   * @return 0 if not valid, 1 if valid */
  
  static inline int
  event_valid(Mword idx);
  
#line 323 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Return pointer to tracebuffer event.
   * @param  position of event in tracebuffer:
   *         0 is last event, 1 the event before and so on
   * @return pointer to tracebuffer event
   *
   * event with idx == 0 is the last event queued in
   * event with idx == 1 is the event before */
  
  static Tb_entry*
  unfiltered_lookup(Mword idx);
  
#line 345 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Return pointer to tracebuffer event.
   * Don't count hidden events.
   * @param  position of event in tracebuffer:
   *         0 is last event, 1 the event before and so on
   * @return pointer to tracebuffer event
   *
   * event with idx == 0 is the last event queued in
   * event with idx == 1 is the event before */
  
  static Tb_entry*
  lookup(Mword look_idx);
  
#line 374 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  static Mword
  unfiltered_idx(Tb_entry const *e);
  
#line 386 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Tb_entry => tracebuffer index. */
  
  static Mword
  idx(Tb_entry const *e);
  
#line 411 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Event number => Tb_entry. */
  
  static inline Tb_entry*
  search(Mword nr);
  
#line 425 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Event number => tracebuffer index.
   * @param  nr  number of event
   * @return tracebuffer index of event which has the number nr or
   *         -1 if there is no event with this number or
   *         -2 if the event is currently hidden. */
  
  static Mword
  search_to_idx(Mword nr);
  
#line 459 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Return some information about log event.
   * @param idx number of event to determine the info
   * @retval number event number
   * @retval tsc event value of CPU cycles
   * @retval pmc event value of perf counter cycles
   * @return 0 if something wrong, 1 if everything ok */
  
  static int
  event(Mword idx, Mword *number, Unsigned32 *kclock,
  		Unsigned64 *tsc, Unsigned32 *pmc1, Unsigned32 *pmc2);
  
#line 487 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Get difference CPU cycles between event idx and event idx+1.
   * @param idx position of first event in tracebuffer
   * @retval difference in CPU cycles
   * @return 0 if something wrong, 1 if everything ok */
  
  static int
  diff_tsc(Mword idx, Signed64 *delta);
  
#line 505 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Get difference perfcnt cycles between event idx and event idx+1.
   * @param idx position of first event in tracebuffer
   * @param nr  number of perfcounter (0=first, 1=second)
   * @retval difference in perfcnt cycles
   * @return 0 if something wrong, 1 if everything ok */
  
  static int
  diff_pmc(Mword idx, Mword nr, Signed32 *delta);
  
#line 530 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  static inline void
  enable_filter();
  
#line 537 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  static inline void
  disable_filter();

protected:  
#line 184 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  static inline Tb_entry_union *
  buffer();
};
#line 36 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

#ifdef CONFIG_JDB_LOGGING
#line 38 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

#ifdef CONFIG_PF_UX
#line 40 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

// We don't want to patch the text segment of Fiasco-UX.

#define BEGIN_LOG_EVENT(name, sc, fmt)				\
  do								\
    {								\
      register Unsigned8 __do_log__;				\
      asm volatile (".pushsection \".data\"	\n\t"		\
		    "1:  .byte   0		\n\t"		\
		    ".section \".debug.jdb.log_table\" \n\t"	\
		    ".long 2f			\n\t"		\
		    ".long 1b			\n\t"		\
		    ".long %c[xfmt]		\n\t"		\
		    ".section \".rodata.log.str\" \n\t"		\
		    "2: .asciz "#name"		\n\t"		\
		    "   .asciz "#sc"		\n\t"		\
		    ".popsection		\n\t"		\
		    "movb    1b,%0		\n\t"		\
		    : "=q"(__do_log__) 			\
                    : [xfmt] "i" (&Tb_entry_formatter_t<fmt>::singleton));  \
      if (EXPECT_FALSE( __do_log__ ))				\
	{
#line 62 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

#elif defined(CONFIG_ARM)
#line 64 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

#define BEGIN_LOG_EVENT(name, sc, fmt)				\
  do								\
    {								\
      register Mword __do_log__;				\
      asm volatile ("1:  mov    %0, #0		\n\t"		\
		    ".pushsection \".debug.jdb.log_table\" \n\t"	\
		    "3: .long 2f		\n\t"		\
		    "   .long 1b		\n\t"		\
		    "   .long %c[xfmt]		\n\t"		\
		    ".section \".rodata.log.str\" \n\t"		\
		    "2: .asciz "#name"		\n\t"           \
		    "   .asciz "#sc"		\n\t"		\
		    ".popsection		\n\t"		\
		    : "=r"(__do_log__)                          \
                    : [xfmt] "i" (&Tb_entry_formatter_t<fmt>::singleton));  \
      if (EXPECT_FALSE( __do_log__ ))				\
	{
#line 82 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

#elif defined(CONFIG_IA32) // IA32
#line 84 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

#define BEGIN_LOG_EVENT(name, sc, fmt)				\
  do								\
    {								\
      register Unsigned8 __do_log__;				\
      asm volatile ("1:   movb $0,%0			\n\t"	\
		    ".pushsection \".debug.jdb.log_table\"	\n\t"	\
		    "3:  .long 2f			\n\t"	\
		    "    .long 1b + 1			\n\t"	\
		    "    .long %a[xfmt]			\n\t"	\
		    ".section \".rodata.log.str\"	\n\t"	\
		    "2:  .asciz "#name"			\n\t"	\
		    "    .asciz "#sc"			\n\t"	\
		    ".popsection			\n\t"	\
		    : "=b"(__do_log__)                          \
                    : [xfmt] "i" (&Tb_entry_formatter_t<fmt>::singleton));  \
      if (EXPECT_FALSE( __do_log__ ))				\
	{
#line 102 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

#elif defined(CONFIG_AMD64)
#line 104 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
#define BEGIN_LOG_EVENT(name, sc, fmt)				\
  do								\
    {								\
      register Unsigned8 __do_log__;				\
      asm volatile ("1:   movb $0,%0			\n\t"	\
		    ".pushsection \".debug.jdb.log_table\"	\n\t"	\
		    "3:  .quad 2f			\n\t"	\
		    "    .quad 1b + 1			\n\t"	\
		    "    .quad %c[xfmt]			\n\t"	\
		    ".section \".rodata.log.str\"	\n\t"	\
		    "2:  .asciz "#name"			\n\t"	\
		    "    .asciz "#sc"			\n\t"	\
		    ".popsection			\n\t"	\
		    : "=b"(__do_log__)                          \
                    : [xfmt] "i"(&Tb_entry_formatter_t<fmt>::singleton) );   \
      if (EXPECT_FALSE( __do_log__ ))				\
	{
#line 121 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

#elif defined(CONFIG_PPC32)
#line 123 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
//#warning TODO: Dummy implementation for PPC32
#define BEGIN_LOG_EVENT(name, sc, fmt)				\
  do								\
    {								\
      register Unsigned8 __do_log__ = 0;			\
      if (EXPECT_FALSE( __do_log__ ))				\
	{
#line 130 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

#else
#line 132 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
#error Unknown Arch for LOG macros
#line 133 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
#endif
#line 134 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

#define END_LOG_EVENT						\
	}							\
    } while (0)
#line 138 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

#else // ! CONFIG_JDB_LOGGING
#line 140 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

#define BEGIN_LOG_EVENT(name, sc, fmt)				\
  if (0)							\
    { char __do_log__ = 0; (void)__do_log__;
#line 144 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

#define END_LOG_EVENT						\
    }
#line 147 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

#endif // ! CONFIG_JDB_LOGGING

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 157 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
#include "mem_layout.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 175 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"


inline Tracebuffer_status *
Jdb_tbuf::status()
{
  return (Tracebuffer_status *)Mem_layout::Tbuf_status_page;
}

#line 189 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"


inline Address
Jdb_tbuf::size()
{
  return _size;
}

#line 239 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

 
template<typename T> inline T*
Jdb_tbuf::new_entry()
{
  static_assert(sizeof(T) <= sizeof(Tb_entry_union), "tb entry T too big");
  return static_cast<T*>(new_entry());
}

#line 270 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

/** Return number of entries currently allocated in tracebuffer.
 * @return number of entries */

inline Mword
Jdb_tbuf::unfiltered_entries()
{
  return _entries;
}

#line 295 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

/** Return maximum number of entries in tracebuffer.
 * @return number of entries */

inline Mword
Jdb_tbuf::max_entries()
{
  return _max_entries;
}

#line 304 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

/** Set maximum number of entries in tracebuffer. */

inline void
Jdb_tbuf::max_entries(Mword num)
{
  _max_entries = num;
}

#line 312 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

/** Check if event is valid.
 * @param idx position of event in tracebuffer
 * @return 0 if not valid, 1 if valid */

inline int
Jdb_tbuf::event_valid(Mword idx)
{
  return idx < _entries;
}

#line 410 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

/** Event number => Tb_entry. */

inline Tb_entry*
Jdb_tbuf::search(Mword nr)
{
  Tb_entry *e;

  for (Mword idx = 0; (e = unfiltered_lookup(idx)); idx++)
    if (e->number() == nr)
      return e;

  return 0;
}

#line 528 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"


inline void
Jdb_tbuf::enable_filter()
{
  _filter_enabled = 1;
}

#line 535 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"


inline void
Jdb_tbuf::disable_filter()
{
  _filter_enabled = 0;
}

#line 182 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"


inline Tb_entry_union *
Jdb_tbuf::buffer()
{
  return (Tb_entry_union *)Mem_layout::Tbuf_buffer_area;
}

#endif // jdb_tbuf_h
