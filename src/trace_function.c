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

static void	trace_call(t_proc *proc, unsigned long address,
			   t_stack_address **stack)
{
  char		*name;
  
  name = get_function_name(proc->pid, address);
#ifdef BONUS
  if (!rindex(name, '@'))
    fprintf(stderr, "%sEntering function %s%s%s at %s0x%lx%s\n",
	    GREEN, BLUE, name, WHITE, YELLOW, address & 0xFFFFFFFF, WHITE);
  record_graph(proc, name, stack, 1);
#else
  fprintf(stderr, "Entering function %s at 0x%lx\n", name, address & 0xFFFFFFFF);
#endif
  stack_push(stack, address, proc->regs.rbp);
}

void		trace_function(t_proc *proc, unsigned long opcode,
			       t_stack_address **stack)
{
  unsigned int	value;
  unsigned long	address;

  if ((opcode & 0xFF) == 0xe8)
    {
      value = opcode >> 8;
      address = (proc->regs.rip + value + 5);
      trace_call(proc, address, stack);
    }
  else if ((opcode & 0xFF) == 0xFF
	   && ((opcode >> 8) & 0x38) == 0x10)
    {
      address = get_indirect_address(proc, opcode);
      trace_call(proc, address, stack);
    }
}
