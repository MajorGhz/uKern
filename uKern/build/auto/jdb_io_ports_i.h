// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_io_ports_i_h
#define jdb_io_ports_i_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_io_ports.cpp"

#include <cstdio>
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_io_ports.cpp"
#include "simpleio.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_io_ports.cpp"

#include "io.h"
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_io_ports.cpp"
#include "jdb_module.h"
#line 8 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_io_ports.cpp"
#include "jdb.h"
#line 9 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_io_ports.cpp"
#include "pci.h"
#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_io_ports.cpp"
#include "pic.h"
#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_io_ports.cpp"
#include "static_init.h"
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_io_ports.cpp"

/**
 * Private IA32-I/O module.
 */
class Io_m : public Jdb_module
{
public:
  Io_m() FIASCO_INIT;

private:
  static char porttype;

  struct Port_io_buf {
    unsigned adr;
    unsigned val;
  };

  struct Pci_port_buf {
    unsigned bus;
    unsigned dev;
    unsigned subdev;
    unsigned reg;
    unsigned val;
  };
  
  struct Irq_buf {
    unsigned irq;
  };

  union Input_buffer {
    Port_io_buf io;
    Pci_port_buf pci;
    Irq_buf irq;
  };

  static Input_buffer buf;

public:  
#line 57 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_io_ports.cpp"
  Jdb_module::Action_code
  action( int cmd, void *&args, char const *&fmt, int &);
  
#line 211 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_io_ports.cpp"
  int num_cmds() const;
  
#line 217 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/ia32/jdb_io_ports.cpp"
  Jdb_module::Cmd const * cmds() const;
};

#endif // jdb_io_ports_i_h
