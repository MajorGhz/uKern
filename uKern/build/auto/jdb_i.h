// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_i_h
#define jdb_i_h
#line 363 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


class Cmd_buffer
{
private:
  unsigned  _l;
  char _b[256];

public:
  Cmd_buffer() {}
  char *buffer() { return _b; }
  int len() const { return _l; }
  void flush() { _l = 0; _b[0] = 0; }
  void cut(int l) 
  {
    if (l < 0)
      l = _l + l;

    if (l >= 0 && (unsigned)l < _l)
      {
	_l = l;
	_b[l] = 0;
      }
  }

  void append(int c) { if (_l + 1 < sizeof(_b)) { _b[_l++] = c; _b[_l] = 0; } }
  void append(char const *str, int len)
  {
    if (_l + len >= sizeof(_b))
      len = sizeof(_b) - _l - 1;

    memcpy(_b + _l, str, len);
    _l += len;
    _b[_l] = 0;
  }

  void overlay(char const *str, unsigned len)
  {
    if (len + 1 > sizeof(_b))
      len = sizeof(_b) - 1;

    if (len < _l)
      return;

    str += _l;
    len -= _l;

    memcpy(_b + _l, str, len);
    _l = len + _l;
  }

};
#line 923 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


class Jdb_base_cmds : public Jdb_module
{
public:
  Jdb_base_cmds() FIASCO_INIT;

public:  
#line 934 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&, char const *&, int &);
  
#line 948 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  int
  num_cmds() const;
  
#line 955 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"
  Jdb_module::Cmd const *
  cmds() const;
};
#line 305 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"


struct On_dbg_stack
{
  Mword sp;
  On_dbg_stack(Mword sp) : sp(sp) {}
  bool operator () (Cpu_number cpu) const
  {
    Thread::Dbg_stack const &st = Thread::dbg_stack.cpu(cpu);
    return sp <= Mword(st.stack_top) 
       && sp >= Mword(st.stack_top) - Thread::Dbg_stack::Stack_size;
  }
};
#line 21 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb-thread.cpp"

class Jdb_tid_ext : public Jdb_prompt_ext
{
public:
  void ext();
  void update();
};

//
// IMPLEMENTATION of inline functions follows
//


#line 980 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


inline void
Jdb::rcv_uart_enable()
{
  if (Config::serial_esc == Config::SERIAL_ESC_IRQ)
    Kernel_uart::enable_rcv_irq();
}

#line 1158 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb.cpp"


inline int
Jdb::remote_work_ipi_process(Cpu_number)
{ return 1; }

#line 228 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"



inline void
Jdb::backspace()
{
  putstr("\b \b");
}

#endif // jdb_i_h
