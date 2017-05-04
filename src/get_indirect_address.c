#include "ftrace.h"

unsigned long	get_indirect_address(t_proc *proc, unsigned long opcode)
{
  unsigned char	reg;
  unsigned long	tab[9];

  tab[0] = proc->regs.rax;
  tab[1] = proc->regs.rcx;
  tab[2] = proc->regs.rbx;
  tab[3] = proc->regs.rsp;
  tab[4] = proc->regs.rax;
  tab[5] = proc->regs.rbp;
  tab[6] = proc->regs.rsi;
  tab[7] = proc->regs.rdi;

  reg = (opcode & 0xFF00) >> 8;

  return (tab[reg & 0x07]);
}
