// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef acpi_i_h
#define acpi_i_h
#line 106 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/acpi.cpp"

template< typename T >
class Acpi_sdt_p : public Acpi_table_head
{
public:
  T ptrs[0];


public:  
#line 179 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/acpi.cpp"
  unsigned
  entries() const;
  
#line 364 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/acpi.cpp"
  Acpi_table_head const *
  find(char const sig[4]) const;
} __attribute__((packed));
#line 114 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/acpi.cpp"

typedef Acpi_sdt_p<Unsigned32> Acpi_rsdt_p;
#line 116 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/acpi.cpp"
typedef Acpi_sdt_p<Unsigned64> Acpi_xsdt_p;
#line 117 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/acpi.cpp"

class Acpi_rsdp
{
public:
  char       signature[8];
  Unsigned8  chk_sum;
  char       oem[6];
  Unsigned8  rev;
  Unsigned32 rsdt_phys;
  Unsigned32 len;
  Unsigned64 xsdt_phys;
  Unsigned8  ext_chk_sum;
  char       reserved[3];

  Acpi_rsdt_p const *rsdt() const;
  Acpi_xsdt_p const *xsdt() const;

  bool checksum_ok() const;

  static Acpi_rsdp const *locate();

public:  
#line 149 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/acpi.cpp"
  void
  print_info() const;
} __attribute__((packed));

//
// IMPLEMENTATION of function templates
//


#line 177 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/acpi.cpp"


template< typename T > unsigned
Acpi_sdt_p<T>::entries() const
{ return (len - sizeof(Acpi_table_head)) / sizeof(ptrs[0]); }

#line 361 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/acpi.cpp"



template< typename T > Acpi_table_head const *
Acpi_sdt_p<T>::find(char const sig[4]) const
{
  for (unsigned i = 0; i < ((len-sizeof(Acpi_table_head))/sizeof(ptrs[0])); ++i)
    {
      Acpi_table_head const *t = Kmem::dev_map.map((Acpi_table_head const*)ptrs[i]);
      if (t == (Acpi_table_head const *)~0UL)
	continue;

      if (t->signature[0] == sig[0]
	  && t->signature[1] == sig[1]
	  && t->signature[2] == sig[2]
	  && t->signature[3] == sig[3]
          && t->checksum_ok())
	return t;
    }

  return 0;
}

#endif // acpi_i_h
