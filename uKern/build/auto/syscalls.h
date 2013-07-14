// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef syscalls_h
#define syscalls_h

//
// INTERFACE definition follows 
//

#line 62 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/syscalls.cpp"

extern void (*syscall_table[])();

#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/syscalls.cpp"
extern "C"
void  __attribute__((flatten))
sys_ipc_wrapper();

#line 41 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/syscalls.cpp"
extern "C" void  __attribute__((flatten)) sys_invoke_debug_wrapper();

#line 11 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/syscalls-log.cpp"
/** IPC logging.
    called from interrupt gate.
 */
extern "C" void sys_ipc_log_wrapper(void);

#line 100 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/syscalls-log.cpp"
/** IPC tracing.
 */
extern "C" void sys_ipc_trace_wrapper(void);

#endif // syscalls_h
