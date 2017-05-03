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

void	trace_function(t_proc *proc, unsigned long opcode,
		       t_stack_address **stack)
{
  unsigned int	value;
  unsigned long	address;

  if ((unsigned char)opcode == RELCALL)
    {
      value = opcode >> 8; // call args
      address = (proc->regs.rip + value + 5); // jump to address
      address &= 0xffffffff; //recast to uns int

      fprintf(stderr, "Entering function %s at 0x%lx\n",
	      get_function_name(proc->pid, address), address);
      stack_push(stack, address, proc->regs.rip);
    }

  else if ((opcode & 0xFF) == 0xFF	//first == FF
	   && ((opcode >> 8) & 0x38) == 0x10) // second == __010___
    {
      fprintf(stderr, "INDIRECT CALL %lx, register nb: %d\n",
	      opcode & 0xFFFF, (unsigned char)((opcode >> 8) & 0x3));
      stack_push(stack, 0, proc->regs.rip);
    }
}
