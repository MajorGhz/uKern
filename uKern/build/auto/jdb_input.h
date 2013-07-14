// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_input_h
#define jdb_input_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_input.cpp"

#include "jdb_module.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_input.cpp"
#include "types.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_input.cpp"
#include "l4_types.h"

//
// INTERFACE definition follows 
//

#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_input.cpp"

class Task;
#line 12 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_input.cpp"
class Space;
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_input.cpp"
class Kobject;
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_input.cpp"

class Jdb_input
{

public:  
#line 172 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_input.cpp"
  static int
  get_mword(Mword *mword, int digits, int base, int first_char = 0);
};
#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_input.cpp"

class Jdb_input_task_addr
{
public:
  static char     first_char;
  static char     first_char_have_task;
private:
  static Kobject *_task;
  static Space   *_space;
  static Address  _addr;
public:
  typedef struct
    {
      char str[32];
      Jdb_module::Gotkey *gotkey;
    } Symbol;
  static Symbol   symbol;

public:  
#line 65 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_input.cpp"
  static Task *
  task();
  
#line 70 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_input.cpp"
  static Space *
  space();
  
#line 75 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_input.cpp"
  static Address
  addr();
  
#line 80 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_input.cpp"
  static Jdb_module::Action_code
  action(void *&args, char const *&fmt, int &next_char);

private:  
#line 57 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_input.cpp"
  static void
  gotkey_complete_symbol(char *&str, int maxlen, int c);
};

#endif // jdb_input_h
