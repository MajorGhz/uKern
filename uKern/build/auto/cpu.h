// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef cpu_h
#define cpu_h
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/cpu.cpp"

#include "cpu_mask.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/cpu.cpp"
#include "member_offs.h"
#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

#include "types.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
#include "initcalls.h"
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
#include "regdefs.h"
#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
#include "per_cpu_data.h"
#line 216 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

#include "l4_types.h"
#line 218 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
#include "initcalls.h"
#line 219 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
#include "per_cpu_data.h"
#line 220 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
#include "gdt.h"

//
// INTERFACE definition follows 
//

#line 221 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

class Gdt;
#line 223 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
class Tss;
#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/cpu.cpp"

class Cpu
{
  MEMBER_OFFSET();

public:
  struct By_phys_id
  {
    Cpu_phys_id _p;
    By_phys_id(Cpu_phys_id p) : _p(p) {}
    template<typename CPU>
    bool operator () (CPU const &c) const { return _p == c.phys_id(); }
  };
  // we actually use a mask that has one CPU more that we can physically,
  // have, to avoid lots of special cases for an invalid CPU number
  typedef Cpu_mask_t<Config::Max_num_cpus + 1> Online_cpu_mask;

  enum { Invalid = Config::Max_num_cpus };
  static Cpu_number invalid() { return Cpu_number(Invalid); }

  /** Get the logical ID of this CPU */
  Cpu_number id() const;


  /**
   * Set this CPU to online state.
   * NOTE: This does not activate an inactive CPU, Just set the given state.
   */
  void set_online(bool o);

  /** Convienience for Cpu::cpus.cpu(cpu).online() */
  static bool online(Cpu_number cpu);

  static Online_cpu_mask const &online_mask();

private:
  /** Is this CPU online ? */
  bool online() const;

  static Online_cpu_mask _online_mask;

#line 61 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/cpu.cpp"
private:

private:
  void set_id(Cpu_number) {}

#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
private:

public:

  enum Vendor
  {
    Vendor_unknown = 0,
    Vendor_intel,
    Vendor_amd,
    Vendor_cyrix,
    Vendor_via,
    Vendor_umc,
    Vendor_nexgen,
    Vendor_rise,
    Vendor_transmeta,
    Vendor_sis,
    Vendor_nsc
  };

  enum CacheTLB
  {
    Cache_unknown = 0,
    Cache_l1_data,
    Cache_l1_inst,
    Cache_l1_trace,
    Cache_l2,
    Cache_l3,
    Tlb_data_4k,
    Tlb_inst_4k,
    Tlb_data_4M,
    Tlb_inst_4M,
    Tlb_data_4k_4M,
    Tlb_inst_4k_4M,
    Tlb_data_2M_4M,
  };

  enum
  {
    Ldt_entry_size = 8,
  };

  enum Local_features
  {
    Lf_rdpmc		= 0x00000001,
    Lf_rdpmc32		= 0x00000002,
  };

  Unsigned64 time_us() const;
  int can_wrmsr() const;

private:
  void init();
  Unsigned64 _frequency;
  Unsigned32 _version;
  Unsigned32 _brand;
  Unsigned32 _features;
  Unsigned32 _ext_features;
  Unsigned32 _ext_8000_0001_ecx;
  Unsigned32 _ext_8000_0001_edx;
  Unsigned32 _local_features;

  Unsigned16 _inst_tlb_4k_entries;
  Unsigned16 _data_tlb_4k_entries;
  Unsigned16 _inst_tlb_4m_entries;
  Unsigned16 _data_tlb_4m_entries;
  Unsigned16 _inst_tlb_4k_4m_entries;
  Unsigned16 _data_tlb_4k_4m_entries;
  Unsigned16 _l2_inst_tlb_4k_entries;
  Unsigned16 _l2_data_tlb_4k_entries;
  Unsigned16 _l2_inst_tlb_4m_entries;
  Unsigned16 _l2_data_tlb_4m_entries;

  Unsigned16 _l1_trace_cache_size;
  Unsigned16 _l1_trace_cache_asso;

  Unsigned16 _l1_data_cache_size;
  Unsigned16 _l1_data_cache_asso;
  Unsigned16 _l1_data_cache_line_size;

  Unsigned16 _l1_inst_cache_size;
  Unsigned16 _l1_inst_cache_asso;
  Unsigned16 _l1_inst_cache_line_size;

  Unsigned16 _l2_cache_size;
  Unsigned16 _l2_cache_asso;
  Unsigned16 _l2_cache_line_size;

  Unsigned32 _l3_cache_size;
  Unsigned16 _l3_cache_asso;
  Unsigned16 _l3_cache_line_size;

  Unsigned8 _phys_bits;
  Unsigned8 _virt_bits;

  Vendor _vendor;
  char _model_str[52];

  Unsigned32 _arch_perfmon_info_eax;
  Unsigned32 _arch_perfmon_info_ebx;
  Unsigned32 _arch_perfmon_info_ecx;

  Unsigned32 _monitor_mwait_eax;
  Unsigned32 _monitor_mwait_ebx;
  Unsigned32 _monitor_mwait_ecx;
  Unsigned32 _monitor_mwait_edx;

  Unsigned32 scaler_tsc_to_ns;
  Unsigned32 scaler_tsc_to_us;
  Unsigned32 scaler_ns_to_tsc;

public:

  void disable(Cpu_number cpu, char const *reason);

  char const *model_str() const { return _model_str; }
  Vendor vendor() const { return _vendor; }

  unsigned family() const
  { return (_version >> 8 & 0xf) + (_version >> 20 & 0xff); }

  char const *vendor_str() const
  { return _vendor == Vendor_unknown ? "Unknown" : vendor_ident[_vendor]; }

  unsigned model() const
  { return (_version >> 4 & 0xf) + (_version >> 12 & 0xf0); }

  unsigned stepping() const { return _version & 0xF; }
  unsigned type() const { return (_version >> 12) & 0x3; }
  Unsigned64 frequency() const { return _frequency; }
  unsigned brand() const { return _brand & 0xFF; }
  unsigned features() const { return _features; }
  unsigned ext_features() const { return _ext_features; }
  bool has_monitor_mwait() const { return _ext_features & (1 << 3); }
  bool has_monitor_mwait_irq() const { return _monitor_mwait_ecx & 3; }
  unsigned ext_8000_0001_ecx() const { return _ext_8000_0001_ecx; }
  unsigned ext_8000_0001_edx() const { return _ext_8000_0001_edx; }
  unsigned local_features() const { return _local_features; }
  bool superpages() const { return features() & FEAT_PSE; }
  bool tsc() const { return features() & FEAT_TSC; }
  bool sysenter() const { return features() & FEAT_SEP; }
  bool syscall() const { return ext_8000_0001_edx() & FEATA_SYSCALL; }
  bool vmx() { return boot_cpu()->ext_features() & FEATX_VMX; }
  bool svm() { return boot_cpu()->ext_8000_0001_ecx() & FEATA_SVM; }
  bool has_amd_osvw() { return  boot_cpu()->ext_8000_0001_ecx() & (1<<9); }
  unsigned virt_bits() const { return _virt_bits; }
  unsigned phys_bits() const { return _phys_bits; }
  Unsigned32 get_scaler_tsc_to_ns() const { return scaler_tsc_to_ns; }
  Unsigned32 get_scaler_tsc_to_us() const { return scaler_tsc_to_us; }
  Unsigned32 get_scaler_ns_to_tsc() const { return scaler_ns_to_tsc; }

  Address volatile &kernel_sp() const;

public:
  static Per_cpu<Cpu> cpus;
  static Cpu *boot_cpu() { return _boot_cpu; }

  static bool have_superpages() { return boot_cpu()->superpages(); }
  static bool have_sysenter() { return boot_cpu()->sysenter(); }
  static bool have_syscall() { return boot_cpu()->syscall(); }
  static bool have_fxsr() { return boot_cpu()->features() & FEAT_FXSR; }
  static bool have_pge() { return boot_cpu()->features() & FEAT_PGE; }

private:

  static Cpu *_boot_cpu;

  struct Vendor_table {
    Unsigned32 vendor_mask;
    Unsigned32 vendor_code;
    Unsigned16 l2_cache;
    char       vendor_string[32];
  } __attribute__((packed));

  struct Cache_table {
    Unsigned8  desc;
    Unsigned8  level;
    Unsigned16 size;
    Unsigned8  asso;
    Unsigned8  line_size;
  };

  static Vendor_table const intel_table[];
  static Vendor_table const amd_table[];
  static Vendor_table const cyrix_table[];
  static Vendor_table const via_table[];
  static Vendor_table const umc_table[];
  static Vendor_table const nexgen_table[];
  static Vendor_table const rise_table[];
  static Vendor_table const transmeta_table[];
  static Vendor_table const sis_table[];
  static Vendor_table const nsc_table[];

  static Cache_table const intel_cache_table[];

  static char const * const vendor_ident[];
  static Vendor_table const * const vendor_table[];

  static char const * const exception_strings[];

#line 224 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
private:

public:
  enum Lbr
  {
    Lbr_uninitialized = 0,
    Lbr_unsupported,
    Lbr_pentium_6,
    Lbr_pentium_4,
    Lbr_pentium_4_ext,
  };

  enum Bts
  {
    Bts_uninitialized = 0,
    Bts_unsupported,
    Bts_pentium_m,
    Bts_pentium_4,
  };

private:
  /** Flags if lbr or bts facilities are activated, used by double-fault
   *  handler to reset the debugging facilities
   */
  Unsigned32 debugctl_busy;

  /** debugctl value for activating lbr or bts */
  Unsigned32 debugctl_set;

  /** debugctl value to reset activated lr/bts facilities in the double-faukt
   *  handler
   */
  Unsigned32 debugctl_reset;

  /** supported lbr type */
  Lbr _lbr;

  /** supported bts type */
  Bts _bts;

  /** is lbr active ? */
  char lbr_active;

  /** is btf active ? */
  char btf_active;

  /** is bts active ? */
  char bts_active;

  Gdt *gdt;
  Tss *tss;
  Tss *tss_dbf;

public:
  Lbr lbr_type() const { return _lbr; }
  Bts bts_type() const { return _bts; }
  bool lbr_status() const { return lbr_active; }
  bool bts_status() const { return bts_active; }
  bool btf_status() const { return btf_active; }

  Gdt* get_gdt() const { return gdt; }
  Tss* get_tss() const { return tss; }
  void set_gdt() const
  {
    Pseudo_descriptor desc((Address)gdt, Gdt::gdt_max-1);
    Gdt::set (&desc);
  }

  static void set_tss() { set_tr(Gdt::gdt_tss); }

private:
  void init_lbr_type();
  void init_bts_type();


public:  
#line 664 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  explicit FIASCO_INIT_CPU
  Cpu(Cpu_number cpu);
  
#line 679 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static void
  init_global_features();
  
#line 684 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static char const *
  exception_string(Mword trapno);
  
#line 692 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline FIASCO_INIT_CPU
  void
  cpuid(Unsigned32 const mode,
             Unsigned32 *const eax, Unsigned32 *const ebx,
             Unsigned32 *const ecx, Unsigned32 *const edx);
  
#line 702 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline FIASCO_INIT_CPU
  void
  cpuid_0xd(Unsigned32 const ecx_val,
                 Unsigned32 *const eax, Unsigned32 *const ebx,
                 Unsigned32 *const ecx, Unsigned32 *const edx);
  
#line 713 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  void
  update_features_info();
  
#line 861 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static unsigned
  amd_cpuid_mnc();
  
#line 894 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  inline FIASCO_INIT_CPU
  void
  arch_perfmon_info(Unsigned32 *eax, Unsigned32 *ebx, Unsigned32 *ecx) const;
  
#line 904 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static unsigned long
  get_features();
  
#line 935 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  /** Identify the CPU features.
      Attention: This function may be called more than once. The reason is
      that enabling a Local APIC that was previously disabled by the BIOS
      may change the processor features. Therefore, this function has to
      be called again after the Local APIC was enabled.
   */
  FIASCO_INIT_CPU
  void
  identify();
  
#line 1084 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  inline void
  busy_wait_ns(Unsigned64 ns);
  
#line 1094 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  bool
  if_show_infos() const;
  
#line 1106 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  void
  show_cache_tlb_info(const char *indent) const;
  
#line 1174 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  // Function used for calculating apic scaler
  
  static inline Unsigned32
  muldiv(Unsigned32 val, Unsigned32 mul, Unsigned32 div);
  
#line 1189 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline Unsigned32
  get_cs();
  
#line 1198 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline Unsigned32
  get_ds();
  
#line 1207 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline Unsigned32
  get_es();
  
#line 1216 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline Unsigned32
  get_ss();
  
#line 1225 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline void
  set_ds(Unsigned32 val);
  
#line 1230 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline void
  set_es(Unsigned32 val);
  
#line 1251 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline void
  set_cr0(unsigned long val);
  
#line 1256 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline void
  set_pdbr(unsigned long addr);
  
#line 1261 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline void
  set_cr4(unsigned long val);
  
#line 1266 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline void
  set_ldt(Unsigned16 val);
  
#line 1272 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline void
  set_ss(Unsigned32 val);
  
#line 1277 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline void
  set_tr(Unsigned16 val);
  
#line 1282 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline Mword
  get_cr0();
  
#line 1291 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline Address
  get_pdbr();
  
#line 1296 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline Mword
  get_cr4();
  
#line 1301 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline Unsigned16
  get_ldt();
  
#line 1306 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline Unsigned16
  get_tr();
  
#line 1316 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline Unsigned64
  rdmsr(Unsigned32 reg);
  
#line 1326 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline Unsigned64
  rdpmc(Unsigned32 idx, Unsigned32);
  
#line 1336 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline void
  wrmsr(Unsigned32 low, Unsigned32 high, Unsigned32 reg);
  
#line 1341 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline void
  wrmsr(Unsigned64 msr, Unsigned32 reg);
  
#line 1346 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline void
  enable_rdpmc();
  
#line 1396 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  inline void
  lbr_enable(bool on);
  
#line 1419 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  inline void
  btf_enable(bool on);
  
#line 1443 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  void
  bts_enable(bool on);
  
#line 1474 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  inline void
  debugctl_enable();
  
#line 1482 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  inline void
  debugctl_disable();
  
#line 1489 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  /*
   * AMD OS-Visible Workaround Information
   * print a warning if a CPU is affected by any known erratum
   */
  
  void
  print_errata();
  
#line 1554 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  void
  print() const;
  
#line 1566 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  void
  set_sysenter(void (*func)(void));
  
#line 1576 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  void
  set_fast_entry(void (*func)(void));
  
#line 1585 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  FIASCO_INIT_CPU
  void
  init_sysenter();
  
#line 1677 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  inline void
  enable_ldt(Address addr, int size);
  
#line 1694 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline Unsigned32
  get_fs();
  
#line 1699 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline Unsigned32
  get_gs();
  
#line 1704 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline void
  set_fs(Unsigned32 val);
  
#line 1709 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline void
  set_gs(Unsigned32 val);
  
#line 7 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
  static inline Mword
  stack_align(Mword stack);
  
#line 13 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
  inline Unsigned64
  ns_to_tsc(Unsigned64 ns) const;
  
#line 35 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
  inline Unsigned64
  tsc_to_ns(Unsigned64 tsc) const;
  
#line 57 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
  inline Unsigned64
  tsc_to_us(Unsigned64 tsc) const;
  
#line 78 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
  inline void
  tsc_to_s_and_ns(Unsigned64 tsc, Unsigned32 *s, Unsigned32 *ns) const;
  
#line 102 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
  static inline Unsigned64
  rdtsc();
  
#line 111 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
  static inline Unsigned32
  get_flags();
  
#line 116 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
  static inline void
  set_flags(Unsigned32 efl);
  
#line 129 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
  static inline void
  set_cs();
  
#line 139 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
  FIASCO_INIT_CPU
  void
  init_tss_dbf(Address tss_dbf_mem, Address kdir);
  
#line 164 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
  FIASCO_INIT_CPU
  void
  init_tss(Address tss_mem, size_t tss_size);
  
#line 178 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
  FIASCO_INIT_CPU
  void
  init_gdt(Address gdt_mem, Address user_max);

private:  
#line 719 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  FIASCO_INIT_CPU
  void
  cache_tlb_intel();
  
#line 799 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  FIASCO_INIT_CPU
  void
  cache_tlb_l1();
  
#line 820 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  FIASCO_INIT_CPU
  void
  cache_tlb_l2_l3();
  
#line 849 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  FIASCO_INIT_CPU
  void
  addr_size_info();
  
#line 873 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  FIASCO_INIT_CPU
  void
  set_model_str();
  
#line 1599 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  // Return 2^32 / (tsc clocks per usec)
  FIASCO_INIT_CPU
  void
  calibrate_tsc();
};
#line 208 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


//-----------------------------------------------------------------------------
/*
 * Fiasco ia32-native
 * Architecture specific cpu init code
 */


//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 1245 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
#include "processor.h"
#line 4 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
#include "tss.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 691 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

inline FIASCO_INIT_CPU
void
Cpu::cpuid(Unsigned32 const mode,
           Unsigned32 *const eax, Unsigned32 *const ebx,
           Unsigned32 *const ecx, Unsigned32 *const edx)
{
  asm volatile ("cpuid" : "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx)
                        : "a" (mode));
}

#line 701 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

inline FIASCO_INIT_CPU
void
Cpu::cpuid_0xd(Unsigned32 const ecx_val,
               Unsigned32 *const eax, Unsigned32 *const ebx,
               Unsigned32 *const ecx, Unsigned32 *const edx)
{
  asm volatile ("cpuid" : "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx)
                        : "a" (0xd), "c" (ecx_val));
}

#line 893 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

inline FIASCO_INIT_CPU
void
Cpu::arch_perfmon_info(Unsigned32 *eax, Unsigned32 *ebx, Unsigned32 *ecx) const
{
  *eax = _arch_perfmon_info_eax;
  *ebx = _arch_perfmon_info_ebx;
  *ecx = _arch_perfmon_info_ecx;
}

#line 1082 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::busy_wait_ns(Unsigned64 ns)
{
  Unsigned64 stop = rdtsc () + ns_to_tsc(ns);

  while (rdtsc() < stop)
    Proc::pause();
}

#line 1173 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

// Function used for calculating apic scaler

inline Unsigned32
Cpu::muldiv(Unsigned32 val, Unsigned32 mul, Unsigned32 div)
{
  Unsigned32 dummy;

  asm volatile ("mull %3 ; divl %4\n\t"
               :"=a" (val), "=d" (dummy)
               : "0" (val),  "d" (mul),  "c" (div));
  return val;
}

#line 1186 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"



inline Unsigned32
Cpu::get_cs()
{
  Unsigned32 val;
  asm volatile ("mov %%cs, %0" : "=rm" (val));
  return val;
}

#line 1196 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline Unsigned32
Cpu::get_ds()
{
  Unsigned32 val;
  asm volatile ("mov %%ds, %0" : "=rm" (val));
  return val;
}

#line 1205 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline Unsigned32
Cpu::get_es()
{
  Unsigned32 val;
  asm volatile ("mov %%es, %0" : "=rm" (val));
  return val;
}

#line 1214 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline Unsigned32
Cpu::get_ss()
{
  Unsigned32 val;
  asm volatile ("mov %%ss, %0" : "=rm" (val));
  return val;
}

#line 1223 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::set_ds(Unsigned32 val)
{ asm volatile ("mov %0, %%ds" : : "rm" (val)); }

#line 1228 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::set_es(Unsigned32 val)
{ asm volatile ("mov %0, %%es" : : "rm" (val)); }

#line 1248 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"



inline void
Cpu::set_cr0(unsigned long val)
{ asm volatile ("mov %0, %%cr0" : : "r" (val)); }

#line 1254 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::set_pdbr(unsigned long addr)
{ asm volatile ("mov %0, %%cr3" : : "r" (addr)); }

#line 1259 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::set_cr4(unsigned long val)
{ asm volatile ("mov %0, %%cr4" : : "r" (val)); }

#line 1264 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::set_ldt(Unsigned16 val)
{ asm volatile ("lldt %0" : : "rm" (val)); }

#line 1269 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"



inline void
Cpu::set_ss(Unsigned32 val)
{ asm volatile ("mov %0, %%ss" : : "r" (val)); }

#line 1275 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::set_tr(Unsigned16 val)
{ asm volatile ("ltr %0" : : "rm" (val)); }

#line 1280 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline Mword
Cpu::get_cr0()
{
  Mword val;
  asm volatile ("mov %%cr0, %0" : "=r" (val));
  return val;
}

#line 1289 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline Address
Cpu::get_pdbr()
{ Address addr; asm volatile ("mov %%cr3, %0" : "=r" (addr)); return addr; }

#line 1294 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline Mword
Cpu::get_cr4()
{ Mword val; asm volatile ("mov %%cr4, %0" : "=r" (val)); return val; }

#line 1299 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline Unsigned16
Cpu::get_ldt()
{ Unsigned16 val; asm volatile ("sldt %0" : "=rm" (val)); return val; }

#line 1304 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline Unsigned16
Cpu::get_tr()
{ Unsigned16 val; asm volatile ("str %0" : "=rm" (val)); return val; }

#line 1314 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline Unsigned64
Cpu::rdmsr(Unsigned32 reg)
{
  Unsigned32 l,h;

  asm volatile ("rdmsr" : "=a" (l), "=d" (h) : "c" (reg));
  return ((Unsigned64)h << 32) + (Unsigned64)l;
}

#line 1324 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline Unsigned64
Cpu::rdpmc(Unsigned32 idx, Unsigned32)
{
  Unsigned32 l,h;

  asm volatile ("rdpmc" : "=a" (l), "=d" (h) : "c" (idx));
  return ((Unsigned64)h << 32) + (Unsigned64)l;
}

#line 1334 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::wrmsr(Unsigned32 low, Unsigned32 high, Unsigned32 reg)
{ asm volatile ("wrmsr" : : "a" (low), "d" (high), "c" (reg)); }

#line 1339 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::wrmsr(Unsigned64 msr, Unsigned32 reg)
{ asm volatile ("wrmsr" : : "a" ((Unsigned32)msr), "d" ((Unsigned32)(msr >> 32)), "c" (reg)); }

#line 1344 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::enable_rdpmc()
{ set_cr4(get_cr4() | CR4_PCE); }

#line 1393 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"



inline void
Cpu::lbr_enable(bool on)
{
  if (lbr_type() != Lbr_unsupported)
    {
      if (on)
	{
	  lbr_active    = true;
	  debugctl_set |= 1;
	  debugctl_busy = true;
	}
      else
	{
	  lbr_active    = false;
	  debugctl_set &= ~1;
	  debugctl_busy = lbr_active || bts_active;
	  wrmsr(debugctl_reset, MSR_DEBUGCTLA);
	}
    }
}

#line 1416 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"



inline void
Cpu::btf_enable(bool on)
{
  if (lbr_type() != Lbr_unsupported)
    {
      if (on)
	{
	  btf_active      = true;
	  debugctl_set   |= 2;
	  debugctl_reset |= 2; /* don't disable bit in kernel */
	  wrmsr(2, MSR_DEBUGCTLA);     /* activate _now_ */
	}
      else
	{
	  btf_active    = false;
	  debugctl_set &= ~2;
	  debugctl_busy = lbr_active || bts_active;
	  wrmsr(debugctl_reset, MSR_DEBUGCTLA);
	}
    }
}

#line 1472 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::debugctl_enable()
{
  if (debugctl_busy)
    wrmsr(debugctl_set, MSR_DEBUGCTLA);
}

#line 1480 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::debugctl_disable()
{
  if (debugctl_busy)
    wrmsr(debugctl_reset, MSR_DEBUGCTLA);
}

#line 1674 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"



inline void
Cpu::enable_ldt(Address addr, int size)
{
  if (!size)
    {
      get_gdt()->clear_entry (Gdt::gdt_ldt / 8);
      set_ldt(0);
    }
  else
    {
      get_gdt()->set_entry_byte(Gdt::gdt_ldt / 8, addr, size-1, 2/*=ldt*/, 0);
      set_ldt(Gdt::gdt_ldt);
    }
}

#line 1691 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"



inline Unsigned32
Cpu::get_fs()
{ Unsigned32 val; asm volatile ("mov %%fs, %0" : "=rm" (val)); return val; }

#line 1697 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline Unsigned32
Cpu::get_gs()
{ Unsigned32 val; asm volatile ("mov %%gs, %0" : "=rm" (val)); return val; }

#line 1702 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::set_fs(Unsigned32 val)
{ asm volatile ("mov %0, %%fs" : : "rm" (val)); }

#line 1707 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::set_gs(Unsigned32 val)
{ asm volatile ("mov %0, %%gs" : : "rm" (val)); }

#line 5 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"


inline Mword
Cpu::stack_align(Mword stack)
{ return stack & ~0x3; }

#line 10 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"



inline Unsigned64
Cpu::ns_to_tsc(Unsigned64 ns) const
{
  Unsigned32 dummy;
  Unsigned64 tsc;
  asm volatile
	("movl  %%edx, %%ecx		\n\t"
	 "mull	%3			\n\t"
	 "movl	%%ecx, %%eax		\n\t"
	 "movl	%%edx, %%ecx		\n\t"
	 "mull	%3			\n\t"
	 "addl	%%ecx, %%eax		\n\t"
	 "adcl	$0, %%edx		\n\t"
	 "shld	$5, %%eax, %%edx	\n\t"
	 "shll	$5, %%eax		\n\t"
	:"=A" (tsc), "=&c" (dummy)
	: "0" (ns),  "b" (scaler_ns_to_tsc)
	);
  return tsc;
}

#line 33 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"


inline Unsigned64
Cpu::tsc_to_ns(Unsigned64 tsc) const
{
  Unsigned32 dummy;
  Unsigned64 ns;
  asm volatile
	("movl  %%edx, %%ecx		\n\t"
	 "mull	%3			\n\t"
	 "movl	%%ecx, %%eax		\n\t"
	 "movl	%%edx, %%ecx		\n\t"
	 "mull	%3			\n\t"
	 "addl	%%ecx, %%eax		\n\t"
	 "adcl	$0, %%edx		\n\t"
	 "shld	$5, %%eax, %%edx	\n\t"
	 "shll	$5, %%eax		\n\t"
	:"=A" (ns), "=&c" (dummy)
	: "0" (tsc), "b" (scaler_tsc_to_ns)
	);
  return ns;
}

#line 55 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"


inline Unsigned64
Cpu::tsc_to_us(Unsigned64 tsc) const
{
  Unsigned32 dummy;
  Unsigned64 us;
  asm volatile
	("movl  %%edx, %%ecx		\n\t"
	 "mull	%3			\n\t"
	 "movl	%%ecx, %%eax		\n\t"
	 "movl	%%edx, %%ecx		\n\t"
	 "mull	%3			\n\t"
	 "addl	%%ecx, %%eax		\n\t"
	 "adcl	$0, %%edx		\n\t"
	:"=A" (us), "=&c" (dummy)
	: "0" (tsc), "S" (scaler_tsc_to_us)
	);
  return us;
}

#line 75 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"



inline void
Cpu::tsc_to_s_and_ns(Unsigned64 tsc, Unsigned32 *s, Unsigned32 *ns) const
{
    Unsigned32 dummy;
    __asm__
	("				\n\t"
	 "movl  %%edx, %%ecx		\n\t"
	 "mull	%4			\n\t"
	 "movl	%%ecx, %%eax		\n\t"
	 "movl	%%edx, %%ecx		\n\t"
	 "mull	%4			\n\t"
	 "addl	%%ecx, %%eax		\n\t"
	 "adcl	$0, %%edx		\n\t"
	 "movl  $1000000000, %%ecx	\n\t"
	 "shld	$5, %%eax, %%edx	\n\t"
	 "shll	$5, %%eax		\n\t"
	 "divl  %%ecx			\n\t"
	:"=a" (*s), "=d" (*ns), "=&c" (dummy)
	: "A" (tsc), "g" (scaler_tsc_to_ns)
	);
}

#line 99 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"



inline Unsigned64
Cpu::rdtsc()
{
  Unsigned64 tsc;
  asm volatile ("rdtsc" : "=A" (tsc));
  return tsc;
}

#line 109 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"


inline Unsigned32
Cpu::get_flags()
{ Unsigned32 efl; asm volatile ("pushfl ; popl %0" : "=r"(efl)); return efl; }

#line 114 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"


inline void
Cpu::set_flags(Unsigned32 efl)
{ asm volatile ("pushl %0 ; popfl" : : "rm" (efl) : "memory"); }

#line 127 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"


inline void
Cpu::set_cs()
{
  asm volatile("ljmp %0, $1f ; 1:"
               : : "i"(Gdt::gdt_code_kernel | Gdt::Selector_kernel));
}

#line 73 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/cpu.cpp"


inline Cpu::Online_cpu_mask const &
Cpu::online_mask()
{ return _online_mask; }

#line 110 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/cpu.cpp"


inline Cpu_number
Cpu::id() const
{ return Cpu_number::boot_cpu(); }

#line 115 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/cpu.cpp"


inline bool
Cpu::online() const
{ return true; }

#line 120 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/cpu.cpp"


inline void
Cpu::set_online(bool)
{}

#line 125 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/cpu.cpp"


inline bool
Cpu::online(Cpu_number _cpu)
{ return _cpu == Cpu_number::boot_cpu(); }

#line 1309 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline int
Cpu::can_wrmsr() const
{ return features() & FEAT_MSR; }

#line 1667 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline Unsigned64
Cpu::time_us() const
{
  return tsc_to_us (rdtsc());
}

#line 119 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"


inline Address volatile &
Cpu::kernel_sp() const
{ return *reinterpret_cast<Address volatile *>(&get_tss()->_esp0); }

#endif // cpu_h
