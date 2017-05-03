/*
** function_binary.c for function_binary in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Wed May  3 16:20:29 2017 David Zeng
** Last update Wed May  3 16:20:29 2017 David Zeng
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

static char	*get_name(Elf64_Sym *sym, int symsize, char *strtab,
			  unsigned long addr)
{
  int		i;

  i = -1;
  while (++i < symsize)
    {
      if (sym[i].st_value == addr)
	return (strdup(&strtab[sym[i].st_name]));
    }
  return (NULL);
}

char		*function_binary(unsigned long addr)
{
  static char	*file = NULL;
  int		i;
  t_elf		elf;

  if (!file)
    file = read_file(g_prog);
  elf.symsize = 0;
  elf.elf = (Elf64_Ehdr *)file;
  elf.shdr = (Elf64_Shdr *)(file + elf.elf->e_shoff);
  elf.ststrtab = file + elf.shdr[elf.elf->e_shstrndx].sh_offset;
  i = -1;
  while (++i < elf.elf->e_shnum)
    {
      if (elf.shdr[i].sh_type == SHT_SYMTAB)
	{
	  elf.sym = (Elf64_Sym *)(file + elf.shdr[i].sh_offset);
	  elf.symsize = elf.shdr[i].sh_size / sizeof(Elf64_Sym);
	}
      if (elf.shdr[i].sh_type == SHT_STRTAB &&
	  strncmp(&elf.ststrtab[elf.shdr[i].sh_name], ".strtab", 7) == 0)
	elf.strtab = file + elf.shdr[i].sh_offset;
    }
  return (get_name(elf.sym, elf.symsize, elf.strtab, addr));
}
