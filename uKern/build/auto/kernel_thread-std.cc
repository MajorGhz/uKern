// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "kernel_thread.h"
#include "kernel_thread_i.h"

#line 17 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread-std.cpp"

static Cap_index const C_task      = Cap_index(1);
#line 19 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread-std.cpp"
static Cap_index const C_factory   = Cap_index(2);
#line 20 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread-std.cpp"
static Cap_index const C_thread    = Cap_index(3);
#line 21 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread-std.cpp"
static Cap_index const C_pager     = Cap_index(4);
#line 22 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread-std.cpp"
static Cap_index const C_log       = Cap_index(5);
#line 23 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread-std.cpp"
static Cap_index const C_icu       = Cap_index(6);
#line 24 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread-std.cpp"
static Cap_index const C_scheduler = Cap_index(7);

#line 25 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/kernel_thread-std.cpp"



void
Kernel_thread::init_workload()
{
  auto g = lock_guard(cpu_lock);

  if (Config::Jdb &&
      !Koptions::o()->opt(Koptions::F_nojdb) &&
      Koptions::o()->opt(Koptions::F_jdb_cmd))
    {
      // extract the control sequence from the command line
      char ctrl[128];
      char const *s = Koptions::o()->jdb_cmd;
      char *d;

      for (d=ctrl; d < ctrl+sizeof(ctrl)-1 && *s && *s != ' '; *d++ = *s++)
	;
      *d = '\0';

      kdb_ke_sequence(ctrl);
    }

  // kernel debugger rendezvous
  if (Koptions::o()->opt(Koptions::F_wait))
    kdb_ke("Wait");

  //
  // create sigma0
  //

  Task *sigma0 = Task::create<Sigma0_task>(Ram_quota::root,
      L4_fpage::mem(Mem_layout::Utcb_addr, Config::PAGE_SHIFT));

  assert_opt (sigma0);
  // prevent deletion of this thing
  sigma0->inc_ref();

  init_mapdb_mem(sigma0);
  init_mapdb_io(sigma0);

  check (map(sigma0,          sigma0, sigma0, C_task, 0));
  check (map(Factory::root(), sigma0, sigma0, C_factory, 0));

  for (Cap_index c = Initial_kobjects::first(); c < Initial_kobjects::end(); ++c)
    {
      Kobject_iface *o = initial_kobjects.obj(c);
      if (o)
	check(map(o, sigma0, sigma0, c, 0));
    }

  Thread_object *sigma0_thread = new (Ram_quota::root) Thread_object();

  assert_kdb(sigma0_thread);

  // prevent deletion of this thing
  sigma0_thread->inc_ref();
  check (map(sigma0_thread, sigma0, sigma0, C_thread, 0));

  Address sp = init_workload_s0_stack();
  check (sigma0_thread->control(Thread_ptr(Thread_ptr::Null), Thread_ptr(Thread_ptr::Null)) == 0);
  check (sigma0_thread->bind(sigma0, User<Utcb>::Ptr((Utcb*)Mem_layout::Utcb_addr)));
  check (sigma0_thread->ex_regs(Kip::k()->sigma0_ip, sp));

  //
  // create the boot task
  //

  Task *boot_task = Task::create<Task>(Ram_quota::root,
      L4_fpage::mem(Mem_layout::Utcb_addr, Config::PAGE_SHIFT+2));

  assert_opt (boot_task);

  // prevent deletion of this thing
  boot_task->inc_ref();

  Thread_object *boot_thread = new (Ram_quota::root) Thread_object();

  assert_kdb (boot_thread);

  // prevent deletion of this thing
  boot_thread->inc_ref();

  check (map(boot_task,   boot_task, boot_task, C_task, 0));
  check (map(boot_thread, boot_task, boot_task, C_thread, 0));

  check (boot_thread->control(Thread_ptr(C_pager), Thread_ptr(Thread_ptr::Null)) == 0);
  check (boot_thread->bind(boot_task, User<Utcb>::Ptr((Utcb*)Mem_layout::Utcb_addr)));
  check (boot_thread->ex_regs(Kip::k()->root_ip, Kip::k()->root_sp));

  Ipc_gate *s0_b_gate = Ipc_gate::create(Ram_quota::root, sigma0_thread, 4 << 4);

  check (s0_b_gate);
  check (map(s0_b_gate, boot_task, boot_task, C_pager, 0));

  set_cpu_of(sigma0_thread, Cpu_number::boot_cpu());
  set_cpu_of(boot_thread, Cpu_number::boot_cpu());

  sigma0_thread->activate();
  check (obj_map(sigma0, C_factory, 1, boot_task, C_factory, 0).error() == 0);
  for (Cap_index c = Initial_kobjects::first(); c < Initial_kobjects::end(); ++c)
    {
      Kobject_iface *o = initial_kobjects.obj(c);
      if (o)
	check(obj_map(sigma0, c, 1, boot_task, c, 0).error() == 0);
    }

  boot_thread->activate();
}
