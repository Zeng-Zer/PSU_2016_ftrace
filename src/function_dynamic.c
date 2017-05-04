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

static char	*get_name(Elf64_Sym *sym, int symsize, char *strtab,
			  unsigned int addr)
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

static char	*parse_dynamic_lib(char *file, unsigned long addr)
{
  char		*content;
  int		i;
  t_elf		elf;
  char		*name;

  content = read_file(file, false);
  elf.symsize = 0;
  elf.elf = (Elf64_Ehdr *)content;
  elf.shdr = (Elf64_Shdr *)(content + elf.elf->e_shoff);
  elf.ststrtab = content + elf.shdr[elf.elf->e_shstrndx].sh_offset;
  i = -1;
  while (++i < elf.elf->e_shnum)
    {
      if (elf.shdr[i].sh_type == SHT_SYMTAB)
	{
	  elf.sym = (Elf64_Sym *)(content + elf.shdr[i].sh_offset);
	  elf.symsize = elf.shdr[i].sh_size / sizeof(Elf64_Sym);
	}
      if (elf.shdr[i].sh_type == SHT_STRTAB &&
	  strncmp(&elf.ststrtab[elf.shdr[i].sh_name], ".strtab", 7) == 0)
	elf.strtab = content + elf.shdr[i].sh_offset;
    }
  name = get_name(elf.sym, elf.symsize, elf.strtab, addr);
  read_file(NULL, true);
  return (name);
}

static int	parse_interval(char *line, unsigned long *start,
			       unsigned long *end)
{
  char		*buf;
  char		*c;

  c = strchr(line, ' ');
  if (!c)
    return (1);
  buf = strndup(line, c - line);
  c = strchr(buf, '-');
  if (!c)
    {
      free(buf);
      return (1);
    }
  *c = '\0';
  *start = strtol(buf, NULL, 16);
  *end = strtol(c + 1, NULL, 16);
  free(buf);
  return (0);
}

static char	*get_dynamic_name(char *line, unsigned long addr)
{
  unsigned long	start;
  unsigned long	end;
  char		*file;
  char		*name;

  if (parse_interval(line, &start, &end) != 0 || addr < start || addr > end)
    return (NULL);
  line[strlen(line) - 1] = '\0';
  if (!(file = strchr(line, '/')) || !!strcmp(file + strlen(file) - 3, ".so"))
    return (NULL);
  name = parse_dynamic_lib(file, addr - start);
  return (name);
}

char		*function_dynamic(pid_t pid, unsigned long addr)
{
  char		*maps;
  size_t	size;
  char		path[256];
  FILE		*fd;
  char		*name;

  size = 0;
  maps = NULL;
  sprintf(path, "/proc/%d/maps", pid);
  if (!(fd = fopen(path, "r")))
    return (NULL);
  while (getline(&maps, &size, fd) != -1 &&
	 !(name = get_dynamic_name(maps, addr)));
  fclose(fd);
  return (name);
}
