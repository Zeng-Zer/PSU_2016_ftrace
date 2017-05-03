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

void	trace_function(t_proc *proc, long opcode)
{
  unsigned int	address;

  if ((unsigned char)opcode == RELCALL)
    {
      address = opcode >> 8; // call args
      address = (proc->regs.rip + address + 5); // jump to address
      fprintf(stderr, "Entering function ' ' at 0x%x\n", address);
    }
}
