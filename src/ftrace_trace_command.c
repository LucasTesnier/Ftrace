/*
** EPITECH PROJECT, 2022
** ftrace
** File description:
** trace_command
*/

#include "ftrace_trace_command.h"
#include "ftrace_prepare_command.h"
#include "ftrace_syscall.h"
#include "ftrace_signals.h"
#include <string.h>
#include <sys/ptrace.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/reg.h>
#include <sys/wait.h>
#include <sys/user.h>

/**
*@brief Free the trace_data structure
*
*@param trace_data
*/
void trace_data_destroy(trace_data_t *trace_data)
{
    if (trace_data->raw_command)
        free(trace_data->raw_command);
    if (trace_data->complete_command)
        free(trace_data->complete_command);
    if (trace_data)
        free(trace_data);
}

/**
*@brief Create the trace_data structure
*
*@param command
*@return trace_data_t*
*/
trace_data_t *trace_data_create(char *command, char **env)
{
    trace_data_t *trace_data = malloc(sizeof(trace_data_t));

    if (!trace_data)
        return NULL;
    trace_data->raw_command = strdup(command);
    if (!trace_data->raw_command)
        return NULL;
    trace_data->complete_command = prepare_command(command, env);
    if (!trace_data->complete_command) {
        free(trace_data->raw_command);
        free(trace_data);
        return NULL;
    }
    return trace_data;
}

/**
*@brief display the syscall traced command
*
*@param trace_data
*@return int
*/
int ftrace_display_command(trace_data_t *trace_data)
{
    struct user_regs_struct regs;
    syscall_t actual_signal;
    int status = 0;

    waitpid(trace_data->pid, &status, 0);
    while (true) {
        next_signal(&status, trace_data->pid, &regs);
        int temp = ptrace(PTRACE_PEEKTEXT, trace_data->pid, regs.rip, NULL);
        if ((temp & 0xffff) == 0x050F) {
            next_signal(&status, trace_data->pid, &regs);
            fill_actual_signal_with_regs_value(regs, &actual_signal);
            matching_actual_signal_with_signal_table(&actual_signal);
            display_actual_signal(actual_signal);
        }
        if (WIFEXITED(status) || WIFSIGNALED(status))
            break;
    }
    return WEXITSTATUS(status);
}

/**
*@brief trace the command
*
*@param trace_data
*@return int
*/
int ftrace_trace_command(trace_data_t *trace_data)
{
    trace_data->pid = fork();
    if (trace_data->pid == -1)
        return -1;
    if (trace_data->pid == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        kill(getpid(), SIGSTOP);
        execvp(trace_data->raw_command, NULL);
        return 0;
    } else {
        ftrace_display_command(trace_data);
    }
    return 0;
}