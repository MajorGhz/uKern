// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_tcb.h"
#include "jdb_tcb_i.h"

#line 6 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


//-----------------------------------------------------------------

#line 38 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
#define ADDR_FMT "%08lx"
#line 144 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"



Kobject *Jdb_tcb::threadid;
#line 148 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
Address Jdb_tcb::address;
#line 149 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
char    Jdb_tcb::first_char;
#line 150 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
char    Jdb_tcb::auto_tcb;
#line 151 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
Jdb_disasm_view Jdb_tcb::_disasm_view(Jdb_tcb::Disasm_x, Jdb_tcb::Disasm_y);
#line 152 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"
Jdb_stack_view  Jdb_tcb::_stack_view (Jdb_tcb::Stack_y);
#line 153 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


// available from jdb_dump module
extern int jdb_dump_addr_task (Address addr, Space *task, int level)
  __attribute__((weak));
#line 913 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"

static Jdb_tcb jdb_tcb INIT_PRIORITY(JDB_MODULE_INIT_PRIO);
#line 991 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"

static Jdb_thread_name_ext jdb_thread_name_ext INIT_PRIORITY(JDB_MODULE_INIT_PRIO);

#line 158 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


Jdb_stack_view::Jdb_stack_view(unsigned y)
: start_y(y), absy(0), memdump_is_colored(true)
{}

#line 175 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


void
Jdb_stack_view::init(Address ksp, Jdb_entry_frame *_ef, bool _is_current)
{
  current = Jdb_tcb_ptr(ksp);

  absy = current.offs() / bytes_per_line();
  addx = (current.offs() % bytes_per_line()) / sizeof(Mword);
  addy = 0;
  ef = _ef;
  is_current = _is_current;
}

#line 188 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


void
Jdb_stack_view::print_value(Jdb_tcb_ptr const &p, bool highl)
{
  if (!p.valid() || !Jdb_util::is_mapped((void const*)p.addr()))
    {
      printf(" %.*s", Jdb_screen::Mword_size_bmode, Jdb_screen::Mword_not_mapped);
      return;
    }

  const char *s1="", *s2="";
  if (highl)
    {
      s1 = Jdb::esc_emph;
      s2 = JDB_ANSI_END;
    }
  else if (p.is_user_value())
    {
      s1 = Jdb::esc_iret;
      s2 = JDB_ANSI_END;
    }
  else if (memdump_is_colored)
    {
      if (p.is_kern_code())
        {
          s1 = JDB_ANSI_COLOR(lightblue);
          s2 = JDB_ANSI_END;
        }
      else if (p.is_kobject())
        {
          s1 = JDB_ANSI_COLOR(lightgreen);
          s2 = JDB_ANSI_END;
        }
      /* else if (p.in_backtrace(...
         {
         s1 = Jdb::esc_bt;
         s2 = "\033[m";
         } */
    }

  printf(" %s" ADDR_FMT "%s", s1, p.value(), s2);
}

#line 231 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"



void
Jdb_stack_view::dump()//Jdb_tcb_ptr const &current)
{
  Jdb_tcb_ptr p = current;
  p.offs(absy * bytes_per_line());

  Jdb::cursor(start_y, 1);

  for (unsigned y = 0; y < Jdb_screen::height() - start_y; ++y)
    {
      Kconsole::console()->getchar_chance();

      if (p.valid())
        {
          printf("    %03lx ", p.addr() & 0xfff);
          for (unsigned x = 0; x < cols(); ++x, p+=1)
            print_value(p);
          putchar('\n');
        }
      else
        puts("\033[K");
    }
}

#line 267 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


void
Jdb_stack_view::highlight(bool highl)
{
  current.offs(absy*bytes_per_line() + addy*bytes_per_line() + addx * sizeof(Mword));
  Jdb_tcb_ptr first_col = current;
  first_col.offs(absy*bytes_per_line() + addy*bytes_per_line());

  if (!current.valid())
    return;

  Jdb::cursor(posy(), 1);
  if (highl)
    printf("%08lx", current.addr() & 0xffffffff);
  else
    printf("    %03lx ", first_col.addr() & 0xfff);
  Jdb::cursor(posy(), posx());
  print_value(current, highl);

  char kobj_desc[120];
  kobj_desc[0] = 0;
  Kobject_dbg::Iterator o;

  if (current.is_kern_code())
    strcpy(kobj_desc, "Kernel code"); // todo: print kernel function name
  else if (current.is_user_value())
    snprintf(kobj_desc, sizeof(kobj_desc), "Return frame: %s",
             current.user_value_desc());
  else
    if ((o = Kobject_dbg::pointer_to_obj(reinterpret_cast<void *>(current.value()))) != Kobject_dbg::end())
      {
        Jdb_kobject::obj_description(kobj_desc, sizeof(kobj_desc), true, *o);
        kobj_desc[sizeof(kobj_desc) - 1] = 0;
      }

  Jdb::printf_statline("tcb", "<CR>=dump <Space>=Disas",
                       "%s", kobj_desc);
}

#line 306 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


bool
Jdb_stack_view::handle_key(int key, bool *redraw)
{
  Mword   lines    = Jdb_screen::height() - start_y;
  Mword   max_lines = (Context::Size + bytes_per_line() - 1)/bytes_per_line();
  Address max_absy = max_lines - lines;

  if (lines > max_lines)
    max_absy = 0;

  if (lines > max_lines - absy)
    lines = max_lines - absy;

  if (key == 'e')
    edit_stack(redraw);
  else
    return Jdb::std_cursor_key(key, this->cols(), lines, max_absy,
      &absy, &addy, &addx, redraw);

  return true;
}

#line 329 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


void
Jdb_stack_view::edit_stack(bool *redraw)
{
  if (current.valid())
    {
      Mword value;
      int c;

      Jdb::cursor(posy(), posx());
      printf(" %.*s", Jdb_screen::Mword_size_bmode, Jdb_screen::Mword_blank);
      Jdb::printf_statline("tcb",
          is_current ? "<Space>=edit registers" : 0,
          "edit <" ADDR_FMT "> = " ADDR_FMT,
          current.addr(), current.value());

      Jdb::cursor(posy(), posx() + 1);
      c = Jdb_core::getchar();

      if (c==KEY_ESC)
        {
          *redraw = true;
          return;
        }

      if (c != ' ' || !is_current)
        {
          // edit memory
          putchar(c);
          Jdb::printf_statline("tcb", 0, "edit <" ADDR_FMT "> = " ADDR_FMT,
              current.addr(), current.value());
          Jdb::cursor(posy(), posx() + 1);
          if (!Jdb_input::get_mword(&value, c, 16))
            {
              Jdb::cursor(posy(), posx());
              print_value(current);
              return;
            }
          else
            current.value(value);
        }
      else
        {
          // edit registers
          Jdb::cursor(posy(), posx());
          print_value(current);
          edit_registers();
          return;
        }
      *redraw = true;
    }
}

#line 382 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


Jdb_disasm_view::Jdb_disasm_view(unsigned x, unsigned y)
: _x(x), _y(y)
{}

#line 387 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


void
Jdb_disasm_view::show(Jdb_tcb_ptr const &p, Space *s)
{
  if (!Jdb_disasm::avail())
    return;

  Address disass_addr = p.top_value(-5);
  Jdb::cursor(_y, _x);
  putstr(Jdb::esc_emph);
  Jdb_disasm::show_disasm_line(-40, disass_addr, 0, s);
  putstr("\033[m");
  Jdb::cursor(_y + 1, _x);
  Jdb_disasm::show_disasm_line(-40, disass_addr, 0, s);
}

#line 403 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"



Jdb_tcb::Jdb_tcb()
  : Jdb_module("INFO"), Jdb_kobject_handler(Thread_object::static_kobj_type)
{
  static Jdb_handler enter(at_jdb_enter);

  Jdb::jdb_enter.add(&enter);
  Jdb_kobject::module()->register_handler(this);
}

#line 414 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"

void
Jdb_tcb::at_jdb_enter()
{
  if (auto_tcb)
    {
      // clear any keystrokes in queue
      Jdb::set_next_cmd(0);
      Jdb::push_cons()->push('t');
      Jdb::push_cons()->push(' ');
    }
}

#line 426 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"



Kobject *
Jdb_tcb::parent(Kobject *o)
{
  Thread *t = Kobject::dcast<Thread_object*>(o);
  if (!t)
    return 0;

  return static_cast<Task*>(t->space());
}

#line 453 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


Jdb_module::Action_code
Jdb_tcb::show(Thread *t, int level)
{
  Thread *t_current      = Jdb::get_current_active();
  bool is_current_thread;
  bool redraw_screen     = true;
  Jdb_entry_frame *ef    = Jdb::get_entry_frame(Jdb::current_cpu);
#if 0
  Address bt_start       = 0;
#endif

  if (!t && !t_current)
    {
#if 0
      const Mword mask
        = (Context::Size * Mem_layout::max_threads()) - 1;
      const Mword tsksz = Context::Size*L4_uid::threads_per_task();
      LThread_num task = ((Address)Jdb::get_thread() & mask) / tsksz;
#endif
#if 0
      putchar('\n');
      print_entry_frame_regs(0);
#endif
      return NOTHING;
    }

  if (!t)
    t = t_current;

  is_current_thread = t == t_current;

#if 0
  if (!t->is_valid())
    {
      puts(" Invalid thread");
      return NOTHING;
    }
#endif

  if (level==0)
    {
      Jdb::clear_screen(Jdb::FANCY);
      redraw_screen = false;
    }

whole_screen:

  if (redraw_screen)
    {
      Jdb::clear_screen(Jdb::NOFANCY);
      redraw_screen = false;
    }

  char time_str[12];

  putstr("thread  : ");
  Jdb_kobject::print_uid(t, 3);
  print_thread_uid_raw(t);
  printf("\tCPU: %u ", cxx::int_value<Cpu_number>(t->cpu()));

  printf("\tprio: %02x  mode: %s\n",
         t->sched()->prio(),
         t->mode() & Context::Periodic  ?
         t->mode() & Context::Nonstrict ? "Per (IRT)" : "Per (SP)" : "Con");

  printf("state   : %03lx ", t->state(false));
  Jdb_thread::print_state_long(t);

  putstr("\nwait for: ");
  if (!t->partner())
    putstr("---  ");
  else
    Jdb_thread::print_partner(t, 4);

  putstr("\tpolling: ");
  Jdb_thread::print_snd_partner(t, 3);

  putstr("\trcv descr: ");

  if ((t->state(false) & Thread_ipc_mask) == Thread_receive_wait)
    printf("%08lx", t->rcv_regs()->from_spec());
  else
    putstr("        ");

  putstr("\n"
         "lcked by: ");
  if (t->thread_lock()->lock_owner())
    Jdb_kobject::print_uid(static_cast<Thread*>(t->thread_lock()->lock_owner()), 3);

  putstr("\t\t\ttimeout  : ");
  if (t->_timeout && t->_timeout->is_set())
    {
      Signed64 diff = (t->_timeout->get_timeout(Kip::k()->clock)) * 1000;
      if (diff < 0)
        strcpy(time_str, "over");
      else
        Jdb::write_ll_ns(diff, time_str,
                         11 < sizeof(time_str)-1 ? 11 : sizeof(time_str)-1,
                         false);
      printf("%-13s", time_str);
    }

  putstr("\ncpu time: ");
  Jdb::write_ll_ns(t->consumed_time()*1000, time_str,
                   11 < sizeof(time_str) ? 11 : sizeof(time_str), false);
  printf("%-13s", time_str);

  printf("\t\ttimeslice: %llu/%lld %cs\n"
         "pager\t: ",
         t->sched()->left(), ~0ULL/*t->sched()->quantum()*/, Config::char_micro);
  print_kobject(t, t->_pager.raw());

  putstr("\ttask     : ");
  if (t->space() == Kernel_task::kernel_task())
    putstr(" kernel        ");
  else
    print_kobject(static_cast<Task*>(t->space()));

  putstr("\nexc-hndl: ");
  print_kobject(t, t->_exc_handler.raw());

  printf("\tUTCB     : %08lx/%08lx",
         (Mword)t->utcb().kern(), (Mword)t->utcb().usr().get());

#if 0
  putstr("\tready  lnk: ");
  if (t->state(false) & Thread_ready)
    {
      if (t->_ready_next)
        Jdb_kobject::print_uid(Thread::lookup(t->_ready_next), 3);
      else if (is_current_thread)
        putstr(" ???.??");
      else
        putstr("\033[31;1m???.??\033[m");
      if (t->_ready_prev)
        Jdb_kobject::print_uid(Thread::lookup(t->_ready_prev), 4);
      else if (is_current_thread)
        putstr(" ???.??");
      else
        putstr(" \033[31;1m???.??\033[m");
      putchar('\n');
    }
  else
    puts("--- ---");
#endif

  putchar('\n');

  putstr("vCPU    : ");
  if (t->state(false) & Thread_vcpu_enabled)
    {
      char st1[7];
      char st2[7];
      Vcpu_state *v = t->vcpu_state().kern();
      printf("%08lx/%08lx S=", (Mword)v, (Mword)t->vcpu_state().usr().get());
      print_kobject(static_cast<Task*>(t->vcpu_user_space()));
      putchar('\n');
      printf("vCPU    : c=%s s=%s sf=%c e-ip=%08lx e-sp=%08lx\n",
             vcpu_state_str(v->state, st1, sizeof(st1)),
             vcpu_state_str(v->_saved_state, st2, sizeof(st2)),
             (v->sticky_flags & Vcpu_state::Sf_irq_pending) ? 'P' : '-',
             v->_entry_ip, v->_entry_sp);
    }
  else
    putstr("---\nvCPU    : ---\n");

  Address ksp  = is_current_thread ? ef->ksp()
                                   : (Address)t->get_kernel_sp();

#if 0
  Address tcb  = (Address)context_of((void*)ksp);
#endif
  _stack_view.init(ksp, ef, is_current_thread);

  if (is_current_thread)
    print_entry_frame_regs(t);

  else if (t->space() != Kernel_task::kernel_task())
    {
      Jdb::cursor(11, 1);
      info_thread_state(t);
      putchar('\n');
      print_return_frame_regs(_stack_view.current, ksp);

      _disasm_view.show(_stack_view.current, t->space());
    }
  else
    {
      // kernel thread
      Jdb::cursor(15, 1);
      printf("kernel SP=" ADDR_FMT, ksp);
    }

dump_stack:

  // dump the stack from ksp bottom right to tcb_top
  _stack_view.dump();

  for (bool redraw=false; ; )
    {
      _stack_view.highlight(true);
      int c=Jdb_core::getchar();
      _stack_view.highlight(false);
      Jdb::cursor(Jdb_screen::height(), 6);

      if (c == KEY_CURSOR_HOME && level > 0)
        return GO_BACK;

      if (!_stack_view.handle_key(c, &redraw))
        {
          switch (c)
            {
            case KEY_RETURN:
              if (jdb_dump_addr_task && _stack_view.current.valid())
                {
                  if (!jdb_dump_addr_task(_stack_view.current.value(),
                        _stack_view.current.is_user_value() ? t->space() : 0, level+1))
                    return NOTHING;
                  redraw_screen = true;
                }
              break;
            case KEY_TAB:
              //bt_start = search_bt_start(tcb, (Mword*)ksp, is_current_thread);
              redraw = true;
              break;
            case ' ':
              if (Jdb_disasm::avail() && _stack_view.current.valid())
                {
                  printf("V %lx\n", _stack_view.current.value());
                  if (!Jdb_disasm::show(_stack_view.current.value(),
                        _stack_view.current.is_user_value() ? t->space() : 0, level+1, true))
                    return NOTHING;
                  redraw_screen = true;
                }
              break;
            case 'u':
              if (Jdb_disasm::avail() && _stack_view.current.valid())
                {
                  Jdb::printf_statline("tcb", "<CR>=disassemble here",
                                        "u[address=%08lx task=%lx] ",
                                        _stack_view.current.value(),
                                        Kobject_dbg::pointer_to_id(t->space()));
                  int c1 = Jdb_core::getchar();
                  if ((c1 != KEY_RETURN) && (c1 != ' '))
                    {
                      Jdb::printf_statline("tcb", 0, "u");
                      Jdb::execute_command("u", c1);
                      return NOTHING;
                    }

                  if (!Jdb_disasm::show(_stack_view.current.value(),
                        _stack_view.current.is_user_value() ? t->space() : 0, level+1, true))
                    return NOTHING;
                  redraw_screen = true;
                }
              break;
#if 0
            case 'r': // ready-list
              putstr("[n]ext/[p]revious in ready list?");
              switch (Jdb_core::getchar())
                {
                case 'n':
                  if (t->_ready_next)
                    {
                      t = static_cast<Thread*>(t->_ready_next);
                      goto new_tcb;
                    }
                  break;
                case 'p':
                  if (t->_ready_prev)
                    {
                      t = static_cast<Thread*>(t->_ready_prev);
                      goto new_tcb;
                    }
                  break;
                }
              break;
#endif
            case 'C':
              _stack_view.memdump_is_colored = !_stack_view.memdump_is_colored;
              redraw = true;
              break;
            case KEY_ESC:
              Jdb::abort_command();
              return NOTHING;
            default:
              if (Jdb::is_toplevel_cmd(c))
                return NOTHING;
              break;
            }
        }
      if (redraw_screen)
        goto whole_screen;
      if (redraw)
        goto dump_stack;
    }
} 

#line 752 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"

/* --- original L4 screen ------------------------------------------------------
thread: 0081 (001.01) <00020401 00080000>                               prio: 10
state : 85, ready                            lists: 81                   mcp: ff

wait for: --                             rcv descr: 00000000   partner: 00000000
sndq    : 0081 0081                       timeouts: 00000000   waddr0/1: 000/000
cpu time: 0000000000 timeslice: 01/0a

pager   : --                            prsent lnk: 0080 0080
ipreempt: --                            ready link : 0080 0080
xpreempt: --
                                        soon wakeup lnk: 
EAX=00202dfe  ESI=00020401  DS=0008     late wakeup lnk: 
EBX=00000028  EDI=00080000  ES=0008
ECX=00000003  EBP=e0020400
EDX=00000001  ESP=e00207b4

700:
720:
740:
760:
780:
7a0:                                                  0000897b 00000020 00240082
7c0:  00000000 00000000 00000000 00000000    00000000 00000000 00000000 00000000
7e0:  00000000 00000000 ffffff80 00000000    0000001b 00003200 00000000 00000013
L4KD: 
------------------------------------------------------------------------------*/


Jdb_module::Action_code
Jdb_tcb::action(int cmd, void *&args, char const *&fmt, int &next_char)
{
  static Address tcb_addr = 0;
  if (cmd == 0)
    {
      if (args == &first_char)
        {
          switch (first_char)
            {
              case '+':
              case '-':
                printf("%c\n", first_char);
                auto_tcb = first_char == '+';
                break;
              case '?':
                args      = &address;
                fmt       = " addr=" ADDR_FMT " => ";
                putchar(first_char);
                return Jdb_module::EXTRA_INPUT;
              case 'a':
                args      = &tcb_addr;
                fmt       = " tcb=%x => ";
                putchar(first_char);
                return Jdb_module::EXTRA_INPUT;
              case KEY_RETURN:
                show(0, 0);
                return NOTHING;
              default:
                args      = &threadid;
                fmt       = "%q";
                next_char = first_char;
                return Jdb_module::EXTRA_INPUT_WITH_NEXTCHAR;
            }
        }
      else if (args == &address)
        {
          address &= ~(Context::Size-1);
          Jdb_kobject::print_uid(reinterpret_cast<Thread*>(address), 3);
          putchar('\n');
        }
      else if (args == &tcb_addr)
        show((Thread*)tcb_addr, 0);
      else
        {
          Thread *t = Kobject::dcast<Thread_object *>(threadid);
          if (t)
            show(t, 0);
          else
            printf("\nNot a thread\n");
        }
    }

  return NOTHING;
}

#line 837 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


Kobject_common *
Jdb_tcb::follow_link(Kobject_common *o)
{
  Thread *t = Kobject::dcast<Thread_object *>(Kobject::from_dbg(o->dbg_info()));
  if (t->space() == Kernel_task::kernel_task())
    return o;
  return static_cast<Kobject*>(static_cast<Task*>(t->space()));
}

#line 847 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


bool
Jdb_tcb::show_kobject(Kobject_common *o, int level)
{
  Thread *t = Kobject::dcast<Thread_object *>(Kobject::from_dbg(o->dbg_info()));
  return show(t, level);
}

#line 855 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


bool
Jdb_tcb::is_current(Thread *t)
{
  return t == Jdb::get_thread(t->cpu());
}

#line 862 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


int
Jdb_tcb::show_kobject_short(char *buf, int max, Kobject_common *o)
{
  Thread *t = Kobject::dcast<Thread_object *>(Kobject::from_dbg(o->dbg_info()));
  bool is_current = Jdb_tcb::is_current(t);
  int cnt = 0;
  if (t == Context::kernel_context(t->cpu()))
    {
      cnt = snprintf(buf, max, " {KERNEL} C=%u",
                     cxx::int_value<Cpu_number>(t->cpu()));
      max -= cnt;
      buf += cnt;
    }
  if (t->space() == Kernel_task::kernel_task())
    return cnt + snprintf(buf, max, " R=%ld%s", t->ref_cnt(),
                          is_current ? " " JDB_ANSI_COLOR(green) "current" JDB_ANSI_END : "");

  return cnt + snprintf(buf, max, " C=%u S=D:%lx R=%ld %s",
                        cxx::int_value<Cpu_number>(t->cpu()),
                        Kobject_dbg::pointer_to_id(t->space()),
                        t->ref_cnt(),
                        is_current ? " " JDB_ANSI_COLOR(green) "current" JDB_ANSI_END : "");
}

#line 887 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


char const *
Jdb_tcb::kobject_type() const
{
  return JDB_ANSI_COLOR(green) "Thread" JDB_ANSI_COLOR(default);
}

#line 894 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


Jdb_module::Cmd const *
Jdb_tcb::cmds() const
{
  static Cmd cs[] =
    {
        { 0, "t", "tcb", "%C",
          "t[<threadid>]\tshow current/given thread control block (TCB)\n"
          "t{+|-}\tshow current thread control block at every JDB entry\n",
          &first_char },
    };
  return cs;
}

#line 908 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


int
Jdb_tcb::num_cmds() const
{ return 1; }

#line 915 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"

int
jdb_show_tcb(Thread *t, int level)
{ return Jdb_tcb::show(t, level); }

#line 926 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


void
Jdb_tcb::print_kobject(Cap_index n)
{
  printf("[C:%4lx]       ", cxx::int_value<Cap_index>(n));
}

#line 933 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


void
Jdb_tcb::print_kobject(Kobject *o)
{
  printf("D:%4lx         ", o ? o->dbg_info()->dbg_id() : 0);
}

#line 940 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


void
Jdb_tcb::print_kobject(Thread *t, Cap_index capidx)
{
  Space *space = t->space();
  if (!space)
    {
      print_kobject(capidx);
      return;
    }

  Obj_space::Capability *c = space->jdb_lookup_cap(capidx);
  if (!c || !c->valid())
    {
      print_kobject(capidx);
      return;
    }

  printf("[C:%4lx] D:%4lx", cxx::int_value<Cap_index>(capidx),
         c->obj()->dbg_info()->dbg_id());
}

#line 972 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


void
Jdb_thread_name_ext::ext()
{
  if (Jdb::get_current_active())
    {
      Jdb_kobject_name *nx = Jdb_kobject_extension::find_extension<Jdb_kobject_name>(Jdb::get_current_active());
      if (nx && nx->name()[0])
        printf("[%*.*s] ", nx->max_len(), nx->max_len(), nx->name());
    }
}

#line 984 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_tcb.cpp"


void
Jdb_thread_name_ext::update()
{
  Jdb::get_current(Jdb::current_cpu);
}
