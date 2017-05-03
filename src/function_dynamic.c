/*
** function_dynamic.c for function_dynamic in /home/zeng_d/rendu/PSU/PSU_2016_ftrace
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Wed May  3 17:11:50 2017 David Zeng
** Last update Wed May  3 17:11:50 2017 David Zeng
*/

#include "ftrace.h"

static char	*library_proc_map(pid_t pid, unsigned long addr)
{
  static char	*maps = NULL;
  char		path[256];
  int		fd;

  if (!maps)
    {
      sprintf(path, "/proc/%d/maps", pid);
      if ((fd = open(path, O_RDONLY)) != 0 ||
	  !(maps = mmap(NULL, lseek(fd, 0, SEEK_END), PROT_READ, MAP_SHARED,
			fd, 0)))
	return (NULL);
    }
  printf("LOL%s\n", maps);
  return (NULL);
}

char	*function_dynamic(pid_t pid, unsigned long addr)
{
  return (library_proc_map(pid, addr));
}
