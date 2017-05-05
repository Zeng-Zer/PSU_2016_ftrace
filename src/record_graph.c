/*
** record_graph.c for  in /home/buffat_b
** 
** Made by Bertrand Buffat
** Login   <buffat_b@epitech.net>
** 
** Started on  Fri May  5 18:52:47 2017 Bertrand Buffat
** Last update Fri May  5 19:00:10 2017 Bertrand Buffat
*/

#include <ftrace.h>

static FILE	*init_record(FILE *fd)
{
  if (fd == NULL)
    {
      fd = fopen("graph.opt", "wa");
      fprintf(fd, "digraph ftrace {\n");
    }
  else
    {
      fprintf(fd, "}\n");
      fclose(fd);
    }
  return (fd);
}

static void		add_line(t_proc *proc, char *callee,
				 t_stack_address **stack, FILE *fd)
{
  t_stack_address	*ret;
  char			*caller;

  if (rindex(callee, '@') || !*callee)
    return ;
  ret = stack_get(stack);
  while (ret &&
	 rindex(get_function_name(proc->pid, ret->callee_address), '@'))
    ret = stack_prev(&ret);
  if (!ret)
    return ;
  caller = get_function_name(proc->pid, ret->callee_address);
  if (!*caller)
    return ;
  fprintf(fd, "\"%s\" -> \"%s\"\n", caller, callee);
}

void			record_graph(t_proc *proc, char *name,
				     t_stack_address **stack, int flag)
{
  static FILE		*fd = NULL;

  if (!flag)
    fd = init_record(fd);
  else
    add_line(proc, name, stack, fd);
}
