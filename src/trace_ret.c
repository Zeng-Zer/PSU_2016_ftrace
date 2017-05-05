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

void			trace_ret(t_proc *proc, long opcode,
				  t_stack_address **stack)
{
  t_stack_address	*ret;
  char			*name;

  if ((unsigned char)opcode == RET)
    {
      ret = stack_get(stack);
      if (ret) {
	name = get_function_name(proc->pid, ret->callee_address);
	//	if (!rindex(name, '@')) {
	  fprintf(stderr, "Leaving function %s\n", name);
        //	}
      }
      stack_pop(stack);
    }
}
