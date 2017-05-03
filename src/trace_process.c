/*
** trace_function.c for trace_function in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Mon May  1 19:01:59 2017 David Zeng
** Last update Mon May  1 19:01:59 2017 David Zeng
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "ftrace.h"

void			trace_process(pid_t pid)
{
  t_proc		proc;
  long			opcode;
  t_stack_address	*stack;

  proc.pid = pid;
  stack = NULL;
  while (waitpid(pid, &proc.status, 0) && !WIFEXITED(proc.status))
    {
      ptrace(PTRACE_GETREGS, pid, NULL, &proc.regs);
      opcode = ptrace(PTRACE_PEEKTEXT, pid, proc.regs.rip, NULL);
      //      trace_syscall(&proc, opcode);
      trace_function(&proc, opcode, &stack);
      trace_ret(&proc, opcode, &stack);
      ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
    }
}
