/*
** fork_process.c<PSU_2016_ftrace> for fork_process in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Mon May  1 18:54:09 2017 David Zeng
** Last update Mon May  1 18:54:09 2017 David Zeng
*/

#include "ftrace.h"

pid_t	fork_process(char *argv[])
{
  pid_t	pid;

  if ((pid = fork()) == 0)
    {
      ptrace(PTRACE_TRACEME, 0, NULL, NULL);
      exit(execvp(argv[0], argv));
    }
  else if (pid < 0)
    {
      fprintf(stderr, "fork error\n");
      exit(1);
    }
  return (pid);
}
