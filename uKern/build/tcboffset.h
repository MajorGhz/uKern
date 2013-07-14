#define OFS__THREAD__STATE 0x4
#define OFS__THREAD__KERNEL_SP 0x14
#define OFS__THREAD__DONATEE 0x2c
#define OFS__THREAD__LOCK_CNT 0x34
#define OFS__THREAD__SCHED_CONTEXT 0x38
#define OFS__THREAD__SCHED 0x54
#define OFS__THREAD__PERIOD 0x58
#define OFS__THREAD__MODE 0x60
#define OFS__THREAD__FPU_STATE 0x64
#define OFS__THREAD__CONSUMED_TIME 0x68
#define OFS__THREAD__REPLY_CAP 0xf4
#define OFS__THREAD__PARTNER 0xec
#define OFS__THREAD__RCV_REGS 0xf0
#define OFS__THREAD__TIMEOUT 0xa8
#define OFS__THREAD__SPACE 0x24
#define OFS__THREAD__THREAD_LOCK 0x14c
#define OFS__THREAD__THREAD_LOCK__SWITCH_LOCK__LOCK_OWNER 0x14c
#define OFS__THREAD__THREAD_LOCK__SWITCH_HINT 0x150
#define OFS__THREAD__PAGER 0x154
#define OFS__THREAD__RECOVER_JMPBUF 0x9c
#define OFS__THREAD__MAGIC 0x164
#define OFS__THREAD__MAX 0x170
#define OFS__THREAD__USER_VCPU 0xe0
#define OFS__THREAD__VCPU_STATE 0xe4
#define OFS__SCHED_CONTEXT__MAX 0x1c
#define OFS__MEM_SPACE__PGTABLE 0x8
#define OFS__TBUF_STATUS__KERNCNTS 0x70
#define CAST__Thread_TO_Receiver 0x0
#define CAST__Thread_TO_Sender 0x104
#define VAL__SIZEOF_TRAP_STATE 0x4c
#define OFS__VCPU_STATE__ENTRY_IP 0x78
#define OFS__VCPU_STATE__ENTRY_SP 0x7c
#define VAL__MEM_LAYOUT__PHYSMEM 0xfc400000
#define VAL__MEM_LAYOUT__TBUF_STATUS_PAGE 0xeac06000
#define VAL__MEM_LAYOUT__LAPIC 0xeac00000
#define VAL__MEM_LAYOUT__IO_BITMAP 0xefc00000
#define VAL__MEM_LAYOUT__SYSCALLS 0xeacff000
#define OFS__CPU__TSS 0xd8
