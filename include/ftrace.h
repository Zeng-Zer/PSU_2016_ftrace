/*
** ftrace.h for ftrace in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Mon May  1 18:54:32 2017 David Zeng
** Last update Mon May  1 18:54:32 2017 David Zeng
*/

#ifndef FTRACE_H_
# define FTRACE_H_

# include <stdio.h>
# include <stdlib.h>
# include <sys/ptrace.h>
# include <sys/reg.h>
# include <stdbool.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/user.h>
# include <signal.h>
# include <elf.h>

# define SYSCALL 0x050f
# define RELCALL 0xe8
# define RET 0xc3

typedef struct			s_stack_address
{
  unsigned long			callee_address;
  unsigned long			caller_address;
  struct s_stack_address	*next;
}				t_stack_address;

typedef struct			s_elf
{
  Elf64_Ehdr			*elf;
  Elf64_Shdr			*shdr;
  Elf64_Sym			*sym;
  int				symsize;
  char				*strtab;
  char				*ststrtab;
}				t_elf;

typedef struct			s_proc
{
  pid_t				pid;
  struct user_regs_struct	regs;
  int				status;
}				t_proc;

typedef struct			s_syscall_proto
{
  unsigned int			argc;
  char				*name;
}				t_syscall_proto;

extern char			*g_prog;

pid_t		fork_process(char *argv[]);
void		trace_process(pid_t pid);
void		trace_syscall(t_proc *proc, long opcode);
void		trace_function(t_proc *proc, long rip, t_stack_address **stack);
void		trace_ret(t_proc *proc, long rip, t_stack_address **stack);
t_syscall_proto	get_syscall_proto(int num);
t_stack_address	*stack_get(t_stack_address **stack);
void		stack_push(t_stack_address **, unsigned long, unsigned long);
void		stack_pop(t_stack_address **stack);
char		*get_function_name(unsigned long addr);
char		*function_binary(unsigned long addr);

#endif /* !FTRACE_H_ */
