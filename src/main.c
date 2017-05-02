/*
** main.c for main in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Mon Jan 23 17:57:49 2017 David Zeng
** Last update Mon Jan 23 17:57:49 2017 David Zeng
*/

#include "ftrace.h"

int	main(int argc, char *argv[])
{
  pid_t pid;

  if (argc < 2)
    {
      fprintf(stderr, "Usage: %s <commande>\n", argv[0]);
      return 1;
    }
  pid = fork_process(argv + 1);
  trace_process(pid);
  return (0);
}
