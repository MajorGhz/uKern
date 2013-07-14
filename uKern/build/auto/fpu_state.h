// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef fpu_state_h
#define fpu_state_h

//
// INTERFACE definition follows 
//

#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/fpu_state.cpp"

class Fpu_state
{
public:
#if 0
  void save_state();
  void restore_state();
#endif
  void *state_buffer();
  void state_buffer(void *b);

  Fpu_state();
  ~Fpu_state();

private:
  friend class Fpu_alloc;

  void *_state_buffer;
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/fpu_state.cpp"


inline Fpu_state::Fpu_state() : _state_buffer(0)
{}

#line 27 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/fpu_state.cpp"


inline Fpu_state::~Fpu_state()
{
  //free_state();
}

#line 33 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/fpu_state.cpp"


inline void *Fpu_state::state_buffer()
{
  return _state_buffer;
}

#line 39 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/fpu_state.cpp"


inline void Fpu_state::state_buffer(void *b)
{
  _state_buffer = b;
}

#endif // fpu_state_h
