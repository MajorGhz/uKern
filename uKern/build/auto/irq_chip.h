// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef irq_chip_h
#define irq_chip_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"

#include <cxx/bitfield>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"

#include "types.h"
#line 308 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"

#include "tb_entry.h"

//
// INTERFACE definition follows 
//

#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"

class Irq_base;
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"
class Irq_chip;
#line 115 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"


class Kobject_iface;
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"

class Upstream_irq
{
private:
  Irq_chip *const _c;
  Mword const _p;
  Upstream_irq const *const _prev;


public:  
#line 221 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"
  explicit inline Upstream_irq(Irq_base const *b, Upstream_irq const *prev);
  
#line 226 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"
  inline void
  ack() const;
};
#line 18 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"

/**
 * Abstraction for an IRQ controller chip.
 */
class Irq_chip
{
public:
  struct Mode
  {
    Mode() = default;
    explicit Mode(unsigned m) : raw(m) {}

    enum Flow_type
    {
      Set_irq_mode  = 0x1,
      Trigger_edge  = 0x0,
      Trigger_level = 0x2,
      Trigger_mask  = 0x2,

      Polarity_high = 0x0,
      Polarity_low  = 0x4,
      Polarity_both = 0x8,
      Polarity_mask = 0xc,

      F_level_high   = Set_irq_mode | Trigger_level | Polarity_high,
      F_level_low    = Set_irq_mode | Trigger_level | Polarity_low,
      F_raising_edge = Set_irq_mode | Trigger_edge  | Polarity_high,
      F_falling_edge = Set_irq_mode | Trigger_edge  | Polarity_low,
      F_both_edges   = Set_irq_mode | Trigger_edge  | Polarity_both
    };

    Mode(Flow_type ft) : raw(ft) {}

    unsigned raw;
    CXX_BITFIELD_MEMBER(0, 0, set_mode, raw);
    CXX_BITFIELD_MEMBER_UNSHIFTED(1, 3, flow_type, raw);
    CXX_BITFIELD_MEMBER_UNSHIFTED(1, 1, level_triggered, raw);
    CXX_BITFIELD_MEMBER_UNSHIFTED(2, 3, polarity, raw);
    CXX_BITFIELD_MEMBER(4, 5, wakeup, raw);
    CXX_BITFIELD_MEMBER(4, 4, set_wakeup, raw);
    CXX_BITFIELD_MEMBER(5, 5, clear_wakeup, raw);
  };

  virtual void mask(Mword pin) = 0;
  virtual void unmask(Mword pin) = 0;
  virtual void ack(Mword pin) = 0;
  virtual void mask_and_ack(Mword pin) = 0;

  /**
   * Set the trigger mode and polarity.
   */
  virtual int set_mode(Mword pin, Mode) = 0;
  virtual bool is_edge_triggered(Mword pin) const = 0;

  /**
   * Set the target CPU.
   * \param pin the pin to configure
   * \param cpu the logical CPU number.
   */
  virtual void set_cpu(Mword pin, Cpu_number cpu) = 0;
  virtual void unbind(Irq_base *irq);
  virtual ~Irq_chip() = 0;

#line 197 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"
private:

public:
  virtual char const *chip_type() const = 0;

public:  
#line 235 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"
  inline void
  bind(Irq_base *irq, Mword pin, bool ctor = false);
  
#line 260 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"
  /**
   * \param CHIP must be the dynamic type of the object.
   */
  
  
  template<typename CHIP> inline void
  handle_irq(Mword pin, Upstream_irq const *ui);
  
#line 277 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"
  template<typename CHIP> inline void
  handle_multi_pending(Upstream_irq const *ui);
};
#line 81 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"

/**
 * Artificial IRQ chip, used for SW IRQs.
 */
class Irq_chip_soft : public Irq_chip
{
public:
  void mask(Mword) {}
  void unmask(Mword) {}
  void mask_and_ack(Mword) {}
  void ack(Mword) {}

  void set_cpu(Mword, Cpu_number) {}
  int set_mode(Mword, Mode) { return 0; }
  bool is_edge_triggered(Mword) const { return true; }

  char const *chip_type() const { return "Soft"; }

  static Irq_chip_soft sw_chip;
};
#line 101 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"

/**
 * Abstract IRQ controller chip that is visble as part of the
 * Icu to the user.
 */
class Irq_chip_icu : public Irq_chip
{
public:
  virtual bool reserve(Mword pin) = 0;
  virtual bool alloc(Irq_base *irq, Mword pin) = 0;
  virtual Irq_base *irq(Mword pin) const = 0;
  virtual unsigned nr_irqs() const = 0;
  virtual ~Irq_chip_icu() = 0;
};
#line 118 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"


/**
 * Base class for all kinds of IRQ consuming objects.
 */
class Irq_base
{
  friend class Irq_chip;

public:

  typedef void (*Hit_func)(Irq_base *, Upstream_irq const *);
  enum Flags
  {
    F_enabled = 1,
  };

  Irq_base() : _flags(0), _next(0)
  {
    Irq_chip_soft::sw_chip.bind(this, 0, true);
    mask();
  }

  void hit(Upstream_irq const *ui) { hit_func(this, ui); }

  Mword pin() const { return _pin; }
  Irq_chip *chip() const { return _chip; }

  void mask() { if (!__mask()) _chip->mask(_pin); }
  void mask_and_ack()
  {
    if (!__mask())
      _chip->mask_and_ack(_pin);
    else
      _chip->ack(_pin);
  }

  void unmask() { if (__unmask()) _chip->unmask(_pin); }
  void ack() { _chip->ack(_pin); }

  void set_cpu(Cpu_number cpu) { _chip->set_cpu(_pin, cpu); }

  unsigned get_mode() const
  { return _flags & 0xe; }

  bool masked() const { return !(_flags & F_enabled); }
  Mword flags() const { return _flags; }

  void unbind() { _chip->unbind(this); }

  bool __mask() { bool o = masked(); _flags &= ~F_enabled; return o; }
  bool __unmask() { bool o = masked(); _flags |= F_enabled; return o; }

  void set_hit(Hit_func f) { hit_func = f; }
  virtual void switch_mode(bool is_edge_triggered) = 0;
  virtual ~Irq_base() = 0;

protected:
  Hit_func hit_func;

  Irq_chip *_chip;
  Mword _pin;
  unsigned _flags;

  template<typename T>
  static void handler_wrapper(Irq_base *irq, Upstream_irq const *ui)
  { nonull_static_cast<T*>(irq)->handle(ui); }

public:
  Irq_base *_next;

  static Irq_base *(*dcast)(Kobject_iface *);

#line 310 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"
private:

public:
  struct Irq_log : public Tb_entry
  {
    Irq_base *obj;
    Irq_chip *chip;
    Mword pin;
    unsigned print(int max, char *buf) const;
  };

public:  
#line 293 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"
  inline void
  destroy();
  
#line 349 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"
  inline void
  log();
};
#line 191 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"




//----------------------------------------------------------------------------

#line 331 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 209 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"
#include "cpu_lock.h"
#line 210 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"
#include "lock_guard.h"
#line 328 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"

#include "logdefs.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 219 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"


inline Upstream_irq::Upstream_irq(Irq_base const *b, Upstream_irq const *prev)
: _c(b->chip()), _p(b->pin()), _prev(prev)
{}

#line 224 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"


inline void
Upstream_irq::ack() const
{
  for (Upstream_irq const *c = this; c; c = c->_prev)
    c->_c->ack(c->_p);
}

#line 232 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"



inline void
Irq_chip::bind(Irq_base *irq, Mword pin, bool ctor)
{
  irq->_pin = pin;
  irq->_chip = this;

  if (ctor)
    return;

  irq->switch_mode(is_edge_triggered(pin));

  if (irq->masked())
    mask(pin);
  else
    unmask(pin);
}

#line 258 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"


/**
 * \param CHIP must be the dynamic type of the object.
 */


template<typename CHIP> inline void
Irq_chip::handle_irq(Mword pin, Upstream_irq const *ui)
{
  // call the irq function of the chip avoiding the
  // virtual function call overhead.
  Irq_base *irq = nonull_static_cast<CHIP*>(this)->CHIP::irq(pin);
  irq->log();
  irq->hit(ui);
}

#line 274 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"



template<typename CHIP> inline void
Irq_chip::handle_multi_pending(Upstream_irq const *ui)
{
  while (Mword pend = nonull_static_cast<CHIP*>(this)->CHIP::pending())
    {
      for (unsigned i = 0; i < sizeof(Mword)*8; ++i, pend >>= 1)
	if (pend & 1)
	  {
	    handle_irq<CHIP>(i, ui);
	    break; // read the pending ints again
	  }
    }
}

#line 215 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"

inline Irq_chip::~Irq_chip() {}

#line 251 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"


inline void
Irq_chip::unbind(Irq_base *irq)
{
  Irq_chip_soft::sw_chip.bind(irq, 0, true);
}

#line 217 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"
inline Irq_chip_icu::~Irq_chip_icu() {}

#line 290 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"



inline void
Irq_base::destroy()
{
  auto g = lock_guard(cpu_lock);
  unbind();
}

#line 347 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"


inline void
Irq_base::log()
{
  Context *c = current();
  LOG_TRACE("IRQ-Object triggers", "irq", c, Irq_log,
      l->obj = this;
      l->chip = chip();
      l->pin = pin();
  );
}

#line 218 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/irq_chip.cpp"
inline Irq_base::~Irq_base() {}

#endif // irq_chip_h
