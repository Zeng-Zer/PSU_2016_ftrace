#include "ftrace.h"

unsigned long	get_reg_val(t_proc *proc, unsigned char number)
{
  unsigned long	tab[9];

  tab[0] = proc->regs.rax;
  tab[1] = proc->regs.rcx;
  tab[2] = proc->regs.rbx;
  tab[3] = proc->regs.rsp;
  tab[4] = proc->regs.rax;
  tab[5] = proc->regs.rbp;
  tab[6] = proc->regs.rsi;
  tab[7] = proc->regs.rdi;

  return (tab[number]);
}

unsigned long	indirect_register(t_proc *proc, unsigned long reg_value)
{
  return (ptrace(PTRACE_PEEKTEXT, proc->pid, reg_value));
}

unsigned long	indirect_register_16(t_proc *proc, unsigned long opcode, unsigned long reg_value)
{
  return (ptrace(PTRACE_PEEKTEXT, proc->pid, reg_value + ((opcode >> 16) & 0xFF)));
}

unsigned long	get_indirect_address(t_proc *proc, unsigned long opcode)
{
  unsigned char	mod;
  unsigned char	reg;

  // (opcode & 0xFF0000) >> 16
  // ptrace(PTRACE_PEEKTEXT, g_pid, call->regs.rax + (opcode & 0xFF0000) >> 16);
  // ca qu'il y a à Register + 2 bytes;

  mod = (opcode >> 8) & 0xC0;
  reg = (opcode & 0xFF00) >> 8;

  if (mod == 0x0) //00
    return (indirect_register(proc, get_reg_val(proc, reg & 0x07)));
  
  else if (mod == 0x40) //01
    return (indirect_register_16(proc, opcode, get_reg_val(proc, reg & 0x07)));
  
  else if (mod == 0x80) //10
    return (indirect_register_16(proc, opcode, get_reg_val(proc, reg & 0x07)));

  return (get_reg_val(proc, reg & 0x07));  //11
}
