/*
** trace_function.c for trace_function in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Mon May  1 19:16:32 2017 David Zeng
** Last update Fri May  5 18:58:29 2017 Bertrand Buffat
*/

#include "ftrace.h"

void			trace_ret(t_proc *proc, long opcode,
				  t_stack_address **stack)
{
  t_stack_address	*ret;
  char			*name;

  if (!((unsigned char)opcode == RET))
    return ;
  ret = stack_get(stack);
  if (!ret)
    return ;
  name = get_function_name(proc->pid, ret->callee_address);
#ifdef BONUS
  if (!rindex(name, '@'))
    fprintf(stderr, "%sLeaving function%s %s%s\n", RED, BLUE, name, WHITE);
#else
  fprintf(stderr, "Leaving function %s\n", name);
#endif
  stack_pop(stack);
}
