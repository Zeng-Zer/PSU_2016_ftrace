/*
** get_function_name.c for get_function_name in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Tue May  2 16:07:19 2017 David Zeng
** Last update Tue May  2 16:07:19 2017 David Zeng
*/

#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "ftrace.h"

static char	*read_file(char const *filename)
{
  int		fd;
  char		*file;

  if ((fd = open(filename, O_RDONLY)) == -1)
    {
      fprintf(stderr, "Couldn't open file %s\n", filename);
      exit(1);
    }

  file = mmap(NULL, lseek(fd, 0, SEEK_END), PROT_READ, MAP_SHARED, fd, 0);
  if (!file)
    {
      fprintf(stderr, "Couldn't read file %s\n", filename);
      exit(1);
    }
  return (file);
}

char		*get_function_name(char const *filename, long addr)
{
  static char	*file = NULL;

  if (!file)
    file = read_file(filename);

}
