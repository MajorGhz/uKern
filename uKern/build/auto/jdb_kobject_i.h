// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_kobject_i_h
#define jdb_kobject_i_h
#line 123 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"

class Jdb_kobject_id_hdl : public Jdb_kobject_handler
{
public:
  Jdb_kobject_id_hdl() : Jdb_kobject_handler(0) {}
  virtual bool show_kobject(Kobject_common *, int) { return false; }
  virtual ~Jdb_kobject_id_hdl() {}

public:  
#line 133 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  bool
  invoke(Kobject_common *o, Syscall_frame *f, Utcb *utcb);
};

#endif // jdb_kobject_i_h
