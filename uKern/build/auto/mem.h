// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef mem_h
#define mem_h

//
// INTERFACE definition follows 
//

#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/mem.cpp"

class Mem
{
public:
  /**
   * Memory barriers.
   */
  static void barrier() { __asm__ __volatile__ ("" : : : "memory"); }

  static void mb();
  static void rmb();
  static void wmb();

  static void mp_mb();
  static void mp_rmb();
  static void mp_wmb();


  /**
   * Memory operations.
   */
  static void memcpy_mwords(void *dst, void const *src, unsigned long nr_of_mwords);
  static void memcpy_bytes (void *dst, void const *src, unsigned long nr_of_bytes);
  static void memset_mwords(void *dst, const unsigned long val, unsigned long nr_of_mwords);

public:  
#line 46 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/ia32/mem-ia32.cpp"
  static inline void
  memcpy_bytes_fs(void *dst, void const *src, unsigned long n);
  
#line 61 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/ia32/mem-ia32.cpp"
  static inline void
  memcpy_mwords_fs(void *dst, void const *src, unsigned long n);
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 44 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/ia32/mem-ia32.cpp"


inline void
Mem::memcpy_bytes_fs(void *dst, void const *src, unsigned long n)
{
  unsigned dummy1, dummy2, dummy3;

  asm volatile ("cld					\n\t"
                "rep movsl %%fs:(%%esi), %%es:(%%edi)	\n\t"
                "mov %%edx, %%ecx			\n\t"
                "repz movsb %%fs:(%%esi), %%es:(%%edi)	\n\t"
                : "=c" (dummy1), "=S" (dummy2), "=D" (dummy3)
                : "c" (n >> 2), "d" (n & 3), "S" (src), "D" (dst)
                : "memory");
}

#line 59 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/ia32/mem-ia32.cpp"


inline void
Mem::memcpy_mwords_fs(void *dst, void const *src, unsigned long n)
{
  unsigned dummy1, dummy2, dummy3;

  asm volatile ("cld					\n\t"
                "rep movsl %%fs:(%%esi), %%es:(%%edi)	\n\t"
                : "=c" (dummy1), "=S" (dummy2), "=D" (dummy3)
                : "c" (n), "S" (src), "D" (dst)
                : "memory");
}

#line 30 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/mem.cpp"

inline void Mem::mb() { barrier(); }

#line 32 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/mem.cpp"
inline void Mem::rmb() { barrier(); }

#line 33 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/mem.cpp"
inline void Mem::wmb() { barrier(); }

#line 34 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/mem.cpp"

inline void Mem::mp_mb() { barrier(); }

#line 36 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/mem.cpp"
inline void Mem::mp_rmb() { barrier(); }

#line 37 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/mem.cpp"
inline void Mem::mp_wmb() { barrier(); }

#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/ia32/mem-ia32.cpp"


inline void
Mem::memset_mwords(void *dst, unsigned long value, unsigned long n)
{
  unsigned dummy1, dummy2;
  asm volatile ("cld					\n\t"
		"repz stosl               \n\t"
		: "=c"(dummy1), "=D"(dummy2)
		: "a"(value), "c"(n), "D"(dst)
		: "memory");
}

#line 14 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/ia32/mem-ia32.cpp"



inline void
Mem::memcpy_bytes(void *dst, void const *src, unsigned long n)
{
  unsigned dummy1, dummy2, dummy3;

  asm volatile ("cld					\n\t"
                "repz movsl %%ds:(%%esi), %%es:(%%edi)	\n\t"
                "mov %%edx, %%ecx			\n\t"
                "repz movsb %%ds:(%%esi), %%es:(%%edi)	\n\t"
                : "=c" (dummy1), "=S" (dummy2), "=D" (dummy3)
                : "c" (n >> 2), "d" (n & 3), "S" (src), "D" (dst)
                : "memory");
}

#line 30 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/drivers/ia32/mem-ia32.cpp"



inline void
Mem::memcpy_mwords(void *dst, void const *src, unsigned long n)
{
  unsigned dummy1, dummy2, dummy3;

  asm volatile ("cld					\n\t"
                "rep movsl %%ds:(%%esi), %%es:(%%edi)	\n\t"
                : "=c" (dummy1), "=S" (dummy2), "=D" (dummy3)
                : "c" (n), "S" (src), "D" (dst)
                : "memory");
}

#endif // mem_h
