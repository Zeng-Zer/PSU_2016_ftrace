/*
** trace_function.c for trace_function in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Mon May  1 19:01:59 2017 David Zeng
** Last update Mon May  1 19:01:59 2017 David Zeng
*/

#include "ftrace.h"

void		trace_process(pid_t pid)
{
  t_proc	proc;
  long		opcode;
  
  proc.pid = pid;
  while (waitpid(pid, &proc.status, 0) && !WIFEXITED(proc.status))
    {
      ptrace(PTRACE_GETREGS, pid, NULL, &proc.regs);
      opcode = ptrace(PTRACE_PEEKTEXT, pid, proc.regs.rip, NULL);
      
      if ((short)opcode == SYSCALL)
	trace_syscall(&proc);

      else if ((unsigned char)opcode == RELCALL)
	trace_function(&proc, opcode);

      ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
    }

}
