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

void		trace_function(t_proc *proc, unsigned long opcode,
			       t_stack_address **stack)
{
  char		*name;
  unsigned int	value;
  unsigned long	address;
  
  if ((opcode & 0xFF) == 0xe8) //REL CALL
    {
      value = opcode >> 8; // call args
      address = (proc->regs.rip + value + 5); // jump to address
      name = get_function_name(proc->pid, address);
      //      if (!rindex(name, '@')) {
	fprintf(stderr, "Entering function %s at 0x%lx\n", name, address & 0xFFFFFFFF);
	//      }
      stack_push(stack, address, proc->regs.rip);
    }
  else if ((opcode & 0xFF) == 0xFF	//first == FF
	   && ((opcode >> 8) & 0x38) == 0x10) // second == __010___
    {
      address = get_indirect_address(proc, opcode);
      name = get_function_name(proc->pid, address);
      //      if (!rindex(name, '@')) {
	fprintf(stderr, "INDIRECT Entering function %s at 0x%lx\n", name, address & 0xFFFFFFFF);
	//      }
      stack_push(stack, address, proc->regs.rbp);
    }
}
