// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef tb_entry_h
#define tb_entry_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"

#include "initcalls.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
#include "l4_error.h"
#line 24 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"

#include "l4_types.h"

//
// INTERFACE definition follows 
//

#line 26 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"

class Tb_entry;
#line 28 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
class Context;
#line 29 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
class Space;
#line 30 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
class Sched_context;
#line 31 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
class Syscall_frame;
#line 32 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
class Trap_state;
#line 33 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
class Tb_entry_formatter;
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"

enum {
  Tbuf_unused             = 0,
  Tbuf_pf,
  Tbuf_ipc,
  Tbuf_ipc_res,
  Tbuf_ipc_trace,
  Tbuf_ke,
  Tbuf_ke_reg,
  Tbuf_exregs,
  Tbuf_breakpoint,
  Tbuf_pf_res,
  Tbuf_preemption,
  Tbuf_ke_bin,
  Tbuf_dynentries,

  Tbuf_max                = 0x80,
  Tbuf_hidden             = 0x80,
};
#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"

struct Tb_log_table_entry
{
  char const *name;
  unsigned char *patch;
  Tb_entry_formatter *fmt;
};
#line 41 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"

extern Tb_log_table_entry _log_table[];
#line 43 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
extern Tb_log_table_entry _log_table_end;
#line 44 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"



class Tb_entry
{
protected:
  Mword		_number;	///< event number
  Address	_ip;		///< instruction pointer
  Context const *_ctx;		///< Context
  Unsigned64	_tsc;		///< time stamp counter
  Unsigned32	_pmc1;		///< performance counter value 1
  Unsigned32	_pmc2;		///< performance counter value 2
  Unsigned32	_kclock;	///< lower 32 bits of kernel clock
  Unsigned8	_type;		///< type of entry
  Unsigned8     _cpu;           ///< CPU

  static Mword (*rdcnt1)();
  static Mword (*rdcnt2)();

public:
  class Group_order
  {
  public:
    Group_order() : _o(0) {} // not grouped
    Group_order(unsigned v) : _o(2 + v) {}
    static Group_order none() { return Group_order(); }
    static Group_order last() { return Group_order(255, true); }
    static Group_order first() { return Group_order(0); }
    static Group_order direct() { return Group_order(1, true); }

    bool not_grouped() const { return _o == 0; }
    bool is_direct() const { return _o == 1; }
    bool is_first() const { return _o == 2; }
    bool is_last() const { return _o == 255; }
    bool grouped() const { return _o >= 2; }
    unsigned char depth() const { return _o - 2; }

  private:
    Group_order(unsigned char v, bool) : _o(v) {}
    unsigned char _o;
  };

  Group_order has_partner() const { return Group_order::none(); }
  Group_order is_partner(Tb_entry const *) const { return Group_order::none(); }
  Mword partner() const { return 0; }


#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"
private:

public:
  enum
  {
    Tb_entry_size = 64,
  };

public:  
#line 322 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  static void
  set_rdcnt(int num, Mword (*f)());
  
#line 336 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  clear();
  
#line 341 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  set_global(char type, Context const *ctx, Address ip);
  
#line 352 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  hide();
  
#line 357 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  unhide();
  
#line 362 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Address
  ip() const;
  
#line 367 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Context const *
  ctx() const;
  
#line 372 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Unsigned8
  type() const;
  
#line 377 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline int
  hidden() const;
  
#line 382 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Mword
  number() const;
  
#line 387 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  number(Mword number);
  
#line 392 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  rdpmc1();
  
#line 397 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  rdpmc2();
  
#line 402 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Unsigned32
  kclock() const;
  
#line 407 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Unsigned8
  cpu() const;
  
#line 412 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Unsigned64
  tsc() const;
  
#line 417 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Unsigned32
  pmc1() const;
  
#line 422 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Unsigned32
  pmc2() const;
  
#line 29 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"
  inline void
  rdtsc();

protected:  
#line 303 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  static Mword dummy_read_pmc();
} __attribute__((__packed__, __aligned__(8)));
#line 91 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


class Tb_entry_union : public Tb_entry
{
private:
  char _padding[Tb_entry_size - sizeof(Tb_entry)];
};
#line 98 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"

static_assert(sizeof(Tb_entry_union) == Tb_entry::Tb_entry_size,
              "Tb_entry_union has the wrong size");
#line 101 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"

struct Tb_entry_empty : public Tb_entry
{
  unsigned print(int, char *) const { return 0; }
};
#line 106 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"

class Tb_entry_formatter
{
public:
  typedef Tb_entry::Group_order Group_order;

  virtual unsigned print(Tb_entry const *e, int max, char *buf) const = 0;
  virtual Group_order has_partner(Tb_entry const *e) const = 0;
  virtual Group_order is_pair(Tb_entry const *e, Tb_entry const *n) const = 0;
  virtual Mword partner(Tb_entry const *e) const = 0;

  static Tb_entry_formatter const *get_fmt(Tb_entry const *e)
  {
    if (e->type() >= Tbuf_dynentries)
      return _log_table[e->type() - Tbuf_dynentries].fmt;

    return _fixed[e->type()];
  }

private:
  static Tb_entry_formatter const *_fixed[];

public:  
#line 311 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  static void
  set_fixed(unsigned type, Tb_entry_formatter const *f);
};
#line 128 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


template< typename T >
class Tb_entry_formatter_t : public Tb_entry_formatter
{
public:
  typedef T const *Const_ptr;
  typedef T *Ptr;

  unsigned print(Tb_entry const *e, int max, char *buf) const
  { return static_cast<Const_ptr>(e)->print(max, buf); }

  Group_order has_partner(Tb_entry const *e) const
  { return static_cast<Const_ptr>(e)->has_partner(); }

  Group_order is_pair(Tb_entry const *e, Tb_entry const *n) const
  {
    //assert (get_fmt(e) == &singleton);

    if (&singleton == get_fmt(n))
      return static_cast<Const_ptr>(e)->is_partner(static_cast<Const_ptr>(n));
    return Tb_entry::Group_order::none();
  }

  Mword partner(Tb_entry const *e) const
  { return static_cast<Const_ptr>(e)->partner(); }

  static Tb_entry_formatter_t const singleton;
};
#line 157 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"

template<typename T>
Tb_entry_formatter_t<T> const Tb_entry_formatter_t<T>::singleton;
#line 160 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


/** logged ipc. */
class Tb_entry_ipc : public Tb_entry
{
private:
  L4_msg_tag	_tag;           ///< message tag
  Mword	_dword[2];	///< first two message words
  L4_obj_ref	_dst;		///< destination id
  Mword       _dbg_id;
  Mword       _label;
  L4_timeout_pair _timeout;	///< timeout
public:
  Tb_entry_ipc() : _timeout(0) {}
  unsigned print(int max, char *buf) const;

public:  
#line 428 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  set(Context const *ctx, Mword ip, Syscall_frame *ipc_regs, Utcb *utcb,
  		  Mword dbg_id, Unsigned64 left);
  
#line 457 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Mword
  ipc_type() const;
  
#line 462 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Mword
  dbg_id() const;
  
#line 467 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline L4_obj_ref
  dst() const;
  
#line 472 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline L4_timeout_pair
  timeout() const;
  
#line 477 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline L4_msg_tag
  tag() const;
  
#line 482 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Mword
  label() const;
  
#line 487 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Mword
  dword(unsigned index) const;
};
#line 176 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"

/** logged ipc result. */
class Tb_entry_ipc_res : public Tb_entry
{
private:
  L4_msg_tag	_tag;		///< message tag
  Mword	_dword[2];	///< first two dwords
  L4_error	_result;	///< result
  Mword	_from;		///< receive descriptor
  Mword	_pair_event;	///< referred event
  Unsigned8	_have_snd;	///< ipc had send part
  Unsigned8	_is_np;		///< next period bit set
public:
  unsigned print(int max, char *buf) const;

public:  
#line 493 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  set(Context const *ctx, Mword ip, Syscall_frame *ipc_regs,
                        Utcb *utcb,
  		      Mword result, Mword pair_event, Unsigned8 have_snd,
  		      Unsigned8 is_np);
  
#line 514 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline int
  have_snd() const;
  
#line 519 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline int
  is_np() const;
  
#line 524 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Mword
  from() const;
  
#line 529 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline L4_error
  result() const;
  
#line 534 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline L4_msg_tag
  tag() const;
  
#line 539 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Mword
  dword(unsigned index) const;
  
#line 544 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Mword
  pair_event() const;
};
#line 191 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"

/** logged ipc for user level tracing with Vampir. */
class Tb_entry_ipc_trace : public Tb_entry
{
private:
  Unsigned64	_snd_tsc;	///< entry tsc
  L4_msg_tag	_result;	///< result
  L4_obj_ref	_snd_dst;	///< send destination
  Mword	_rcv_dst;	///< rcv partner
  Unsigned8	_snd_desc;
  Unsigned8	_rcv_desc;
public:
  unsigned print(int max, char *buf) const;

public:  
#line 550 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  set(Context const *ctx, Mword ip, Unsigned64 snd_tsc,
  			L4_obj_ref const &snd_dst, Mword rcv_dst,
  			L4_msg_tag result, Unsigned8 snd_desc,
  			Unsigned8 rcv_desc);
};
#line 217 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"

/** logged pagefault. */
class Tb_entry_pf : public Tb_entry
{
private:
  Address	_pfa;		///< pagefault address
  Mword	_error;		///< pagefault error code
  Space	*_space;
public:
  unsigned print(int max, char *buf) const;

public:  
#line 566 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  set(Context const *ctx, Address ip, Address pfa,
  		 Mword error, Space *spc);
  
#line 577 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Mword
  error() const;
  
#line 582 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Address
  pfa() const;
  
#line 587 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Space*
  space() const;
};
#line 228 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"

/** pagefault result. */
class Tb_entry_pf_res : public Tb_entry
{
private:
  Address	_pfa;
  L4_error	_err;
  L4_error	_ret;
public:
  unsigned print(int max, char *buf) const;

public:  
#line 593 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  set(Context const *ctx, Address ip, Address pfa, 
  		     L4_error err, L4_error ret);
  
#line 604 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Address
  pfa() const;
  
#line 609 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline L4_error
  err() const;
  
#line 614 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline L4_error
  ret() const;
};
#line 239 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


/** logged kernel event. */
template<typename BASE, unsigned TAG>
class Tb_entry_ke_t : public BASE
{
protected:
  union Msg
  {
    char msg[BASE::Tb_entry_size - sizeof(BASE)];
    struct Ptr
    {
      char tag[2];
      char const *ptr;
    } mptr;
  } _msg;

public:  
#line 656 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  set(Context const *ctx, Address ip);
  
#line 661 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  set_const(Context const *ctx, Address ip, char const *msg);
  
#line 671 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  set_buf(unsigned i, char c);
  
#line 679 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  term_buf(unsigned i);
  
#line 686 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline char const *
  msg() const;
} __attribute__((__packed__));
#line 256 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"

typedef Tb_entry_ke_t<Tb_entry, Tbuf_ke> Tb_entry_ke;
#line 258 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"

class Tb_entry_ke_reg_b : public Tb_entry
{
public:
  Mword v[3];
} __attribute__((__packed__));
#line 264 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"

class Tb_entry_ke_reg : public Tb_entry_ke_t<Tb_entry_ke_reg_b, Tbuf_ke_reg>
{

public:  
#line 706 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  set_const(Context const *ctx, Mword eip,
                             const char *msg,
                             Mword v1, Mword v2, Mword v3);
};
#line 268 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"

/** logged breakpoint. */
class Tb_entry_bp : public Tb_entry
{
private:
  Address	_address;	///< breakpoint address
  int		_len;		///< breakpoint length
  Mword	_value;		///< value at address
  int		_mode;		///< breakpoint mode
public:
  unsigned print(int max, char *buf) const;

public:  
#line 620 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  set(Context const *ctx, Address ip,
  		 int mode, int len, Mword value, Address address);
  
#line 634 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline int
  mode() const;
  
#line 639 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline int
  len() const;
  
#line 644 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Mword
  value() const;
  
#line 649 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Address
  addr() const;
};
#line 280 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"

/** logged binary kernel event. */
class Tb_entry_ke_bin : public Tb_entry
{
public:
  char _msg[Tb_entry_size - sizeof(Tb_entry)];
  enum { SIZE = 30 };

public:  
#line 693 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  set(Context const *ctx, Address ip);
  
#line 698 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  set_buf(unsigned i, char c);
};
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"

/** logged trap. */
class Tb_entry_trap : public Tb_entry
{
private:
  Unsigned8	_trapno;
  Unsigned16	_error;
  Mword	_ebp, _cr2, _eax, _eflags, _esp;
  Unsigned16	_cs,  _ds;
public:
  unsigned print(int max, char *buf) const;

public:  
#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"
  inline void
  set(Mword eip, Trap_state *ts);
  
#line 49 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"
  inline void
  set(Mword eip, Mword trapno);
  
#line 58 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"
  inline Unsigned8
  trapno() const;
  
#line 63 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"
  inline Unsigned16
  error() const;
  
#line 68 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"
  inline Mword
  eax() const;
  
#line 73 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"
  inline Mword
  cr2() const;
  
#line 78 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"
  inline Mword
  ebp() const;
  
#line 83 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"
  inline Unsigned16
  cs() const;
  
#line 88 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"
  inline Unsigned16
  ds() const;
  
#line 93 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"
  inline Mword
  sp() const;
  
#line 98 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"
  inline Mword
  flags() const;
} __attribute__((packed));

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 295 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"

#include "entry_frame.h"
#line 297 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
#include "globals.h"
#line 298 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
#include "kip.h"
#line 300 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"
#include "trap_state.h"
#line 25 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"

#include "cpu.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 334 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline void
Tb_entry::clear()
{ _type = Tbuf_unused; }

#line 339 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline void
Tb_entry::set_global(char type, Context const *ctx, Address ip)
{
  _type   = type;
  _ctx    = ctx;
  _ip     = ip;
  _kclock = (Unsigned32)Kip::k()->clock;
  _cpu    = cxx::int_value<Cpu_number>(current_cpu());
}

#line 350 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline void
Tb_entry::hide()
{ _type |= Tbuf_hidden; }

#line 355 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline void
Tb_entry::unhide()
{ _type &= ~Tbuf_hidden; }

#line 360 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Address
Tb_entry::ip() const
{ return _ip; }

#line 365 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Context const *
Tb_entry::ctx() const
{ return _ctx; }

#line 370 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Unsigned8
Tb_entry::type() const
{ return _type & (Tbuf_max-1); }

#line 375 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline int
Tb_entry::hidden() const
{ return _type & Tbuf_hidden; }

#line 380 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Mword
Tb_entry::number() const
{ return _number; }

#line 385 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline void
Tb_entry::number(Mword number)
{ _number = number; }

#line 390 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline void
Tb_entry::rdpmc1()
{ _pmc1 = rdcnt1(); }

#line 395 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline void
Tb_entry::rdpmc2()
{ _pmc2 = rdcnt2(); }

#line 400 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Unsigned32
Tb_entry::kclock() const
{ return _kclock; }

#line 405 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Unsigned8
Tb_entry::cpu() const
{ return _cpu; }

#line 410 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Unsigned64
Tb_entry::tsc() const
{ return _tsc; }

#line 415 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Unsigned32
Tb_entry::pmc1() const
{ return _pmc1; }

#line 420 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Unsigned32
Tb_entry::pmc2() const
{ return _pmc2; }

#line 27 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"


inline void
Tb_entry::rdtsc()
{ _tsc = Cpu::rdtsc(); }

#line 425 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"



inline void
Tb_entry_ipc::set(Context const *ctx, Mword ip, Syscall_frame *ipc_regs, Utcb *utcb,
		  Mword dbg_id, Unsigned64 left)
{
  set_global(Tbuf_ipc, ctx, ip);
  _dst       = ipc_regs->ref();
  _label     = ipc_regs->from_spec();


  _dbg_id = dbg_id;

  _timeout   = ipc_regs->timeout();
  _tag       = ipc_regs->tag();
  if (ipc_regs->next_period())
    {
      _dword[0]  = (Unsigned32)(left & 0xffffffff);
      _dword[1]  = (Unsigned32)(left >> 32);
    }
  else
    {
      // hint for gcc
      register Mword tmp0 = utcb->values[0];
      register Mword tmp1 = utcb->values[1];
      _dword[0]  = tmp0;
      _dword[1]  = tmp1;
    }
}

#line 455 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Mword
Tb_entry_ipc::ipc_type() const
{ return _dst.op(); }

#line 460 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Mword
Tb_entry_ipc::dbg_id() const
{ return _dbg_id; }

#line 465 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline L4_obj_ref
Tb_entry_ipc::dst() const
{ return _dst; }

#line 470 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline L4_timeout_pair
Tb_entry_ipc::timeout() const
{ return _timeout; }

#line 475 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline L4_msg_tag
Tb_entry_ipc::tag() const
{ return _tag; }

#line 480 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Mword
Tb_entry_ipc::label() const
{ return _label; }

#line 485 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Mword
Tb_entry_ipc::dword(unsigned index) const
{ return _dword[index]; }

#line 490 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"



inline void
Tb_entry_ipc_res::set(Context const *ctx, Mword ip, Syscall_frame *ipc_regs,
                      Utcb *utcb,
		      Mword result, Mword pair_event, Unsigned8 have_snd,
		      Unsigned8 is_np)
{
  set_global(Tbuf_ipc_res, ctx, ip);
  // hint for gcc
  register Mword tmp0 = utcb->values[0];
  register Mword tmp1 = utcb->values[1];
  _dword[0]   = tmp0;
  _dword[1]   = tmp1;
  _tag        = ipc_regs->tag();
  _pair_event = pair_event;
  _result     = L4_error::from_raw(result);
  _from       = ipc_regs->from_spec();
  _have_snd   = have_snd;
  _is_np      = is_np;
}

#line 512 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline int
Tb_entry_ipc_res::have_snd() const
{ return _have_snd; }

#line 517 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline int
Tb_entry_ipc_res::is_np() const
{ return _is_np; }

#line 522 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Mword
Tb_entry_ipc_res::from() const
{ return _from; }

#line 527 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline L4_error
Tb_entry_ipc_res::result() const
{ return _result; }

#line 532 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline L4_msg_tag
Tb_entry_ipc_res::tag() const
{ return _tag; }

#line 537 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Mword
Tb_entry_ipc_res::dword(unsigned index) const
{ return _dword[index]; }

#line 542 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Mword
Tb_entry_ipc_res::pair_event() const
{ return _pair_event; }

#line 547 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"



inline void
Tb_entry_ipc_trace::set(Context const *ctx, Mword ip, Unsigned64 snd_tsc,
			L4_obj_ref const &snd_dst, Mword rcv_dst,
			L4_msg_tag result, Unsigned8 snd_desc,
			Unsigned8 rcv_desc)
{
  set_global(Tbuf_ipc_trace, ctx, ip);
  _snd_tsc  = snd_tsc;
  _snd_dst  = snd_dst;
  _rcv_dst  = rcv_dst;
  _result   = result;
  _snd_desc = snd_desc;
  _rcv_desc = rcv_desc;
}

#line 564 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline void
Tb_entry_pf::set(Context const *ctx, Address ip, Address pfa,
		 Mword error, Space *spc)
{
  set_global(Tbuf_pf, ctx, ip);
  _pfa   = pfa;
  _error = error;
  _space = spc;
}

#line 575 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Mword
Tb_entry_pf::error() const
{ return _error; }

#line 580 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Address
Tb_entry_pf::pfa() const
{ return _pfa; }

#line 585 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Space*
Tb_entry_pf::space() const
{ return _space; }

#line 590 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"



inline void
Tb_entry_pf_res::set(Context const *ctx, Address ip, Address pfa, 
		     L4_error err, L4_error ret)
{
  set_global(Tbuf_pf_res, ctx, ip);
  _pfa = pfa;
  _err = err;
  _ret = ret;
}

#line 602 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Address
Tb_entry_pf_res::pfa() const
{ return _pfa; }

#line 607 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline L4_error
Tb_entry_pf_res::err() const
{ return _err; }

#line 612 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline L4_error
Tb_entry_pf_res::ret() const
{ return _ret; }

#line 652 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"



 
template<typename BASE, unsigned TAG> inline void
Tb_entry_ke_t<BASE, TAG>::set(Context const *ctx, Address ip)
{ this->set_global(TAG, ctx, ip); }

#line 659 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"

 
template<typename BASE, unsigned TAG> inline void
Tb_entry_ke_t<BASE, TAG>::set_const(Context const *ctx, Address ip, char const *msg)
{
  this->set_global(TAG, ctx, ip);
  _msg.mptr.tag[0] = 0;
  _msg.mptr.tag[1] = 1;
  _msg.mptr.ptr = msg;
}

#line 669 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"

 
template<typename BASE, unsigned TAG> inline void
Tb_entry_ke_t<BASE, TAG>::set_buf(unsigned i, char c)
{
  if (i < sizeof(_msg.msg)-1)
    _msg.msg[i] = c >= ' ' ? c : '.';
}

#line 677 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"

 
template<typename BASE, unsigned TAG> inline void
Tb_entry_ke_t<BASE, TAG>::term_buf(unsigned i)
{
  _msg.msg[i < sizeof(_msg.msg)-1 ? i : sizeof(_msg.msg)-1] = '\0';
}

#line 684 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"

 
template<typename BASE, unsigned TAG> inline char const *
Tb_entry_ke_t<BASE, TAG>::msg() const
{
  return _msg.mptr.tag[0] == 0 && _msg.mptr.tag[1] == 1 ? _msg.mptr.ptr : _msg.msg;
}

#line 704 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline void
Tb_entry_ke_reg::set_const(Context const *ctx, Mword eip,
                           const char *msg,
                           Mword v1, Mword v2, Mword v3)
{
  Tb_entry_ke_t<Tb_entry_ke_reg_b, Tbuf_ke_reg>::set_const(ctx, eip, msg);
  v[0] = v1;
  v[1] = v2;
  v[2] = v3;
}

#line 617 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"



inline void
Tb_entry_bp::set(Context const *ctx, Address ip,
		 int mode, int len, Mword value, Address address)
{
  set_global(Tbuf_breakpoint, ctx, ip);
  _mode    = mode;
  _len     = len;
  _value   = value;
  _address = address;
}

#line 630 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"




inline int
Tb_entry_bp::mode() const
{ return _mode; }

#line 637 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline int
Tb_entry_bp::len() const
{ return _len; }

#line 642 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Mword
Tb_entry_bp::value() const
{ return _value; }

#line 647 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Address
Tb_entry_bp::addr() const
{ return _address; }

#line 691 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline void
Tb_entry_ke_bin::set(Context const *ctx, Address ip)
{ set_global(Tbuf_ke_bin, ctx, ip); }

#line 696 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline void
Tb_entry_ke_bin::set_buf(unsigned i, char c)
{
  if (i < sizeof(_msg)-1)
    _msg[i] = c;
}

#line 32 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"


inline void
Tb_entry_trap::set(Mword eip, Trap_state *ts)
{
  _ip     = eip;
  _trapno = ts->_trapno;
  _error  = ts->_err;
  _cr2    = ts->_cr2;
  _eax    = ts->_ax;
  _cs     = (Unsigned16)ts->cs();
  _ds     = (Unsigned16)ts->_ds;
  _esp    = ts->sp();
  _eflags = ts->flags();
}

#line 47 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"


inline void
Tb_entry_trap::set(Mword eip, Mword trapno)
{
  _ip     = eip;
  _trapno = trapno;
  _cs     = 0;
}

#line 56 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"


inline Unsigned8
Tb_entry_trap::trapno() const
{ return _trapno; }

#line 61 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"


inline Unsigned16
Tb_entry_trap::error() const
{ return _error; }

#line 66 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"


inline Mword
Tb_entry_trap::eax() const
{ return _eax; }

#line 71 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"


inline Mword
Tb_entry_trap::cr2() const
{ return _cr2; }

#line 76 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"


inline Mword
Tb_entry_trap::ebp() const
{ return _ebp; }

#line 81 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"


inline Unsigned16
Tb_entry_trap::cs() const
{ return _cs; }

#line 86 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"


inline Unsigned16
Tb_entry_trap::ds() const
{ return _ds; }

#line 91 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"


inline Mword
Tb_entry_trap::sp() const
{ return _esp; }

#line 96 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"


inline Mword
Tb_entry_trap::flags() const
{ return _eflags; }

#endif // tb_entry_h
