// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef vm_factory_h
#define vm_factory_h

//
// INTERFACE definition follows 
//

#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vm_factory.cpp"

class Vm;
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vm_factory.cpp"
class Ram_quota;
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/vm_factory.cpp"

class Vm_factory
{
public:
  static Vm *create(Ram_quota *quota, int *err);
};

#endif // vm_factory_h
