/*
** trace_function.c for trace_function in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Mon May  1 19:16:32 2017 David Zeng
** Last update Mon May  1 19:16:32 2017 David Zeng
*/

#include "ftrace.h"

// TODO trace function call/leave
void trace_function(t_proc *proc, long opcode)
{
  int	address;
  long	label;

  address = (int)(opcode >> 8);
  label = ptrace(PTRACE_PEEKTEXT, proc->pid, (unsigned long int)(proc->regs.rip + address + 5), NULL);
  
  fprintf(stderr, "Entering function 0x%x at 0x%x\n",
	  (unsigned int)label, (unsigned int)(proc->regs.rip + address + 5));
}
