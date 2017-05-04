/*
** wait_signals.c for wait_signals in /home/zeng_d/rendu/PSU/PSU_2016_ftrace
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Thu May  4 23:21:38 2017 David Zeng
** Last update Thu May  4 23:21:38 2017 David Zeng
*/

#include <signal.h>
#include "ftrace.h"

static t_pair const g_signals[] = {
  {SIGHUP, "SIGHUP"},
  {SIGINT, "SIGINT"},
  {SIGQUIT, "SIGQUIT"},
  {SIGILL, "SIGILL"},
  {SIGTRAP, "SIGTRAP"},
  {SIGABRT, "SIGABRT"},
  {SIGIOT, "SIGIOT"},
  {SIGBUS, "SIGBUS"},
  {SIGFPE, "SIGFPE"},
  {SIGKILL, "SIGKILL"},
  {SIGUSR1, "SIGUSR1"},
  {SIGSEGV, "SIGSEGV"},
  {SIGUSR2, "SIGUSR2"},
  {SIGPIPE, "SIGPIPE"},
  {SIGALRM, "SIGALRM"},
  {SIGTERM, "SIGTERM"},
  {SIGSTKFLT, "SIGSTKFLT"},
  {SIGCHLD, "SIGCHLD"},
  {SIGCONT, "SIGCONT"},
  {SIGSTOP, "SIGSTOP"},
  {SIGTSTP, "SIGTSTP"},
  {SIGTTIN, "SIGTTIN"},
  {SIGTTOU, "SIGTTOU"},
  {SIGURG, "SIGURG"},
  {SIGXCPU, "SIGXCPU"},
  {SIGXFSZ, "SIGXFSZ"},
  {SIGVTALRM, "SIGVTALRM"},
  {SIGPROF, "SIGPROF"},
  {SIGWINCH, "SIGWINCH"},
  {SIGIO, "SIGIO"},
  {SIGPWR, "SIGPWR"},
  {SIGSYS, "SIGSYS"}
};

static void	print_signals(int sig)
{
  int		i;

  i = -1;
  while (++i < (int)(sizeof(g_signals) / sizeof(t_pair)))
    {
      if (g_signals[i].fst == sig)
	{
	  fprintf(stderr, "Received signal %s\n", g_signals[i].snd);
	  break;
	}
    }
}

bool	wait_signals(int status)
{
  int	sig;

  sig = -1;
  if (WIFEXITED(status))
    return (false);
  else if (WIFSIGNALED(status))
    sig = WTERMSIG(status);
  else if (WIFSTOPPED(status))
    sig = WSTOPSIG(status);
  else
    return (true);
  if (sig == SIGTRAP)
    return (true);
  print_signals(sig);
  if (sig == SIGWINCH || sig == SIGURG || sig == SIGTTOU || sig == SIGTTIN ||
      sig == SIGTSTP || sig == SIGSTOP || sig == SIGCHLD)
    return (true);
  return (false);
}
