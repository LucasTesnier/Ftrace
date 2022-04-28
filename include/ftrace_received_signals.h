/*
** EPITECH PROJECT, 2022
** ftrace
** File description:
** ftrace_received_signals
*/

#ifndef FTRACE_RECEIVED_SIGNALS_H_
    #define FTRACE_RECEIVED_SIGNALS_H_

    #include "ftrace_trace_command.h"
    #include <sys/ptrace.h>
    #include <stdio.h>

void ftrace_received_a_signal(trace_data_t *trace_data, int status);

#endif /* !FTRACE_RECEIVED_SIGNALS_H_ */
