/*
** get_function_name.c for get_function_name in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Tue May  2 16:07:19 2017 David Zeng
** Last update Tue May  2 16:07:19 2017 David Zeng
*/

#define _GNU_SOURCE
#include "ftrace.h"

static char	*alternative_name(unsigned int addr)
{
  char		*name;

  asprintf(&name, "func_0x%X@%s", addr,
	   rindex(g_prog, '/') ? rindex(g_prog, '/') + 1 : g_prog);
  return (name);
}

char		*get_function_name(pid_t pid, unsigned long addr)
{
  char		*function;

  if (!(function = function_binary(addr)) &&
      !(function = function_dynamic(pid, addr)))
    function = alternative_name(addr);
  return (function);
}
