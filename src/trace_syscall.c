/*
** trace_syscall.c for trace_syscall in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Tue Apr 11 17:03:01 2017 David Zeng
** Last update Tue Apr 11 17:03:01 2017 David Zeng
*/

#include "ftrace.h"

static void		print_syscall(t_proc *proc, t_stack_address **stack)
{
  t_syscall_proto	sys;
  
  sys = get_syscall_proto(proc->regs.rax);
#ifdef BONUS
  fprintf(stderr, "%sSyscall %s%s", GREEN, BLUE, sys.name);
  record_graph(proc, sys.name, stack, 1);
#else
  fprintf(stderr, "Syscall %s", sys.name);
  (void)stack;
#endif
}

static void		print_param(t_proc *proc)
{
  t_syscall_proto	sys;
  int			i;

  sys = get_syscall_proto(proc->regs.rax);
  i = sys.argc;
  if (i == -1)
    return ;
  fprintf(stderr, "(");
  if (i-- > 0)
    fprintf(stderr, "0x%llx", proc->regs.rdi);
  if (i-- > 0)
    fprintf(stderr, ", 0x%llx", proc->regs.rsi);
  if (i-- > 0)
    fprintf(stderr, ", 0x%llx", proc->regs.rdx);
  if (i-- > 0)
    fprintf(stderr, ", 0x%llx", proc->regs.rcx);
  if (i-- > 0)
    fprintf(stderr, ", 0x%llx", proc->regs.r8);
  if (i-- > 0)
    fprintf(stderr, ", 0x%llx", proc->regs.r9);
  fprintf(stderr, ")");
}

static void	print_ret(t_proc *proc)
{
  bool		isExit;

  isExit = proc->regs.rax == 231;
  ptrace(PTRACE_SINGLESTEP, proc->pid, NULL, NULL);
  waitpid(proc->pid, &proc->status, 0);
  ptrace(PTRACE_GETREGS, proc->pid, NULL, &proc->regs);
#ifdef BONUS
  fprintf(stderr, "%s", YELLOW);
#endif
  if (isExit)
    fprintf(stderr, " = ?\n");
  else
    fprintf(stderr, " = 0x%llx\n", proc->regs.rax);
#ifdef BONUS
  fprintf(stderr, "%s", WHITE);
#endif
}

void	trace_syscall(t_proc *proc, long opcode,
		      t_stack_address **stack)
{
  if ((short)opcode == SYSCALL)
    {
      print_syscall(proc, stack);
      print_param(proc);
      print_ret(proc);
    }
}
