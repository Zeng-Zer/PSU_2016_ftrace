/*
** fork_process.c<PSU_2016_ftrace> for fork_process in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Mon May  1 18:54:09 2017 David Zeng
** Last update Mon May  1 18:54:09 2017 David Zeng
*/

#include <sys/stat.h>
#include <fcntl.h>
#include "ftrace.h"

static bool	can_access(char const *file)
{
  struct stat	statbuf;

  return (!(stat(file, &statbuf) != 0 ||
	    S_ISDIR(statbuf.st_mode) ||
	    access(file, F_OK | X_OK) != 0));
}

static bool	path_exist(char const *file)
{
  char		path[256];
  char		*p;
  char		buf[256];

  if (strchr(file, '/'))
    return (false);
  strcpy(path, getenv("PATH"));
  p = strtok(path, ":");
  while (p)
    {
      strcpy(buf, p);
      strcat(buf, "/");
      strcat(buf, file);
      if (can_access(buf))
	return (true);
      p = strtok(NULL, ":");
    }
  return (false);
}

pid_t	fork_process(char *argv[])
{
  pid_t	pid;

  if (!path_exist(argv[0]) && !can_access(argv[0]))
    {
      fprintf(stderr, "file '%s' could not be executed\n", argv[0]);
      exit(1);
    }
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
