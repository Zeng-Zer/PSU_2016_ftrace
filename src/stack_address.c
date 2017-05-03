#include "ftrace.h"

t_stack_address	*stack_get(t_stack_address **stack)
{
  return (*stack);
}

void	stack_push(t_stack_address **stack, unsigned long callee, unsigned long caller)
{
  t_stack_address	*elem;

  elem = malloc(sizeof(t_stack_address));
  elem->callee_address = callee;
  elem->caller_address = caller;

  elem->next = *stack;
  *stack = elem;
}

void	stack_pop(t_stack_address **stack)
{
  t_stack_address	*curr;

  curr = *stack;
  if (!curr)
    return ;

  *stack = curr->next;
  free(curr);
}
