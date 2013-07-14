// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "acpi.h"
#include "acpi_i.h"


#line 140 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/acpi.cpp"
static void
print_acpi_id(char const *id, unsigned len);
#line 103 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/acpi.cpp"

Acpi_sdt Acpi::_sdt;
#line 105 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/acpi.cpp"
bool Acpi::_init_done;
#line 403 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/acpi.cpp"

// ------------------------------------------------------------------------


#line 138 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/acpi.cpp"


static void
print_acpi_id(char const *id, unsigned len)
{
  char ID[len];
  for (unsigned i = 0; i < len; ++i)
    ID[i] = isalnum(id[i]) ? id[i] : '.';
  printf("%.*s", len, ID);
}

#line 148 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/acpi.cpp"

void
Acpi_rsdp::print_info() const
{
  printf("ACPI: RSDP[%p]\tr%02x OEM:", this, rev);
  print_acpi_id(oem, 6);
  printf("\n");
}

#line 156 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/acpi.cpp"

void
Acpi_table_head::print_info() const
{
  printf("ACPI: ");
  print_acpi_id(signature, 4);
  printf("[%p]\tr%02x OEM:", this, rev);
  print_acpi_id(oem_id, 6);
  printf(" OEMTID:");
  print_acpi_id(oem_tid, 8);
  printf("\n");
}

#line 168 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/acpi.cpp"


void
Acpi_sdt::print_summary() const
{
  for (unsigned i = 0; i < _num_tables; ++i)
    if (_tables[i])
      _tables[i]->print_info();
}

#line 228 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/acpi.cpp"




void
Acpi::init_virt()
{
  if (_init_done)
    return;
  _init_done = 1;

  printf("ACPI-Init\n");

  Acpi_rsdp const *rsdp = Acpi_rsdp::locate();
  if (!rsdp)
    {
      printf("ACPI: Could not find RSDP, skip init\n");
      return;
    }

  rsdp->print_info();

  if (rsdp->rev && rsdp->xsdt_phys)
    {
      Acpi_xsdt_p const *x = Kmem::dev_map.map((const Acpi_xsdt_p *)rsdp->xsdt_phys);
      if (x == (Acpi_xsdt_p const *)~0UL)
        printf("ACPI: Could not map XSDT\n");
      else if (!x->checksum_ok())
        printf("ACPI: Checksum mismatch in XSDT\n");
      else
        {
          _sdt.init(x);
          x->print_info();
          _sdt.print_summary();
          return;
        }
    }

  if (rsdp->rsdt_phys)
    {
      Acpi_rsdt_p const *r = Kmem::dev_map.map((const Acpi_rsdt_p *)(unsigned long)rsdp->rsdt_phys);
      if (r == (Acpi_rsdt_p const *)~0UL)
        printf("ACPI: Could not map RSDT\n");
      else if (!r->checksum_ok())
        printf("ACPI: Checksum mismatch in RSDT\n");
      else
        {
          _sdt.init(r);
          r->print_info();
          _sdt.print_summary();
          return;
        }
    }
}

#line 291 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/acpi.cpp"


Acpi_rsdt_p const *
Acpi_rsdp::rsdt() const
{
  return (Acpi_rsdt_p const*)(unsigned long)rsdt_phys;
}

#line 298 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/acpi.cpp"


Acpi_xsdt_p const *
Acpi_rsdp::xsdt() const
{
  if (rev == 0)
    return 0;
  return (Acpi_xsdt_p const*)xsdt_phys;
}

#line 307 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/acpi.cpp"


bool
Acpi_rsdp::checksum_ok() const
{
  // ACPI 1.0 checksum
  Unsigned8 sum = 0;
  for (unsigned i = 0; i < 20; i++)
    sum += *((Unsigned8 *)this + i);

  if (sum)
    return false;

  if (rev == 0)
    return true;

  // Extended Checksum
  for (unsigned i = 0; i < len && i < 4096; ++i)
    sum += *((Unsigned8 *)this + i);

  return !sum;
}

#line 329 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/acpi.cpp"


bool
Acpi_table_head::checksum_ok() const
{
  Unsigned8 sum = 0;
  for (unsigned i = 0; i < len && i < 4096; ++i)
    sum += *((Unsigned8 *)this + i);

  return !sum;
}

#line 340 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/acpi.cpp"


Acpi_table_head const *
Acpi_sdt::find(char const sig[4]) const
{
  for (unsigned i = 0; i < _num_tables; ++i)
    {
      Acpi_table_head const *t = _tables[i];
      if (!t)
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

#line 383 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/acpi.cpp"


Acpi_madt::Apic_head const *
Acpi_madt::find(Unsigned8 type, int idx) const
{
  for (unsigned i = 0; i < len-sizeof(Acpi_madt);)
    {
      Apic_head const *a = (Apic_head const *)(data + i);
      //printf("a=%p, a->type=%u, a->len=%u\n", a, a->type, a->len);
      if (a->type == type)
	{
	  if (!idx)
	    return a;
	  --idx;
	}
      i += a->len;
    }

  return 0;
}

#line 406 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/acpi.cpp"


Acpi_rsdp const *
Acpi_rsdp::locate()
{
  enum
  {
    ACPI20_PC99_RSDP_START = 0x0e0000,
    ACPI20_PC99_RSDP_END =   0x100000
  };

  for (Address p = ACPI20_PC99_RSDP_START; p < ACPI20_PC99_RSDP_END; p += 16)
    {
      Acpi_rsdp const* r = (Acpi_rsdp const *)p;
      if (r->signature[0] == 'R' &&
	  r->signature[1] == 'S' &&
	  r->signature[2] == 'D' &&
	  r->signature[3] == ' ' &&
	  r->signature[4] == 'P' &&
	  r->signature[5] == 'T' &&
	  r->signature[6] == 'R' &&
	  r->signature[7] == ' ' &&
          r->checksum_ok())
	return r;
    }

  return 0;
}
