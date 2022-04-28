/*
** EPITECH PROJECT, 2022
** ftrace
** File description:
** ftrace_received_signals
*/

#include "ftrace_received_signals.h"
#include <signal.h>
#include <wait.h>

const static char *get_signal_value(int sig_value)
{
    const char *tab[65] = {"SIGHUP", "SIGINT", "SIGQUIT", "SIGILL", "SIGTRAP",
        "SIGABRT", "SIGBUS", "SIGFPE", "SIGKILL", "SIGUSR1", "SIGSEGV",
        "SIGUSR2", "SIGPIPE", "SIGALRM", "SIGTERM", "SIGSTKFLT", "SIGCHLD",
        "SIGCONT", "SIGSTOP", "SIGTSTP", "SIGTTIN", "SIGTTOU", "SIGURG",
        "SIGXCPU", "SIGXFSZ", "SIGVTALRM", "SIGPROF", "SIGWINCH", "SIGIO",
        "SIGPWR", "SIGSYS", "SIGRTMIN", "SIGRTMIN+1", "SIGRTMIN+2",
        "SIGRTMIN+3", "SIGRTMIN+4", "SIGRTMIN+5", "SIGRTMIN+6", "SIGRTMIN+7",
        "SIGRTMIN+8", "SIGRTMIN+9", "SIGRTMIN+10", "SIGRTMIN+11", "SIGRTMIN+12",
        "SIGRTMIN+13", "SIGRTMIN+14", "SIGRTMIN+15", "SIGRTMAX-14",
        "SIGRTMAX-13", "SIGRTMAX-12", "SIGRTMAX-11", "SIGRTMAX-10",
        "SIGRTMAX-9", "SIGRTMAX-8", "SIGRTMAX-7", "SIGRTMAX-6", "SIGRTMAX-5",
        "SIGRTMAX-4", "SIGRTMAX-3", "SIGRTMAX-2", "SIGRTMAX-1", "SIGRTMAX",
        NULL};

    return tab[sig_value - 1];
}

/**
*@brief Check if the traced program has received a signal
*
*@param ptr
*@param trace_data
*@param status
*/
void ftrace_received_a_signal(trace_data_t *trace_data, int status)
{
    siginfo_t sig;

    if (ptrace(PTRACE_GETSIGINFO, trace_data->pid, 0, &sig) == -1)
        return;
    if (sig.si_code == 0)
        fprintf(stderr, "Received signal %s\n", get_signal_value(sig.si_signo));
}