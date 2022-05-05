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