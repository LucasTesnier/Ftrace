/*
** EPITECH PROJECT, 2022
** ftrace
** File description:
** ftrace_signals
*/

#include "ftrace_signals.h"
#include <string.h>
#include <sys/ptrace.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include "ftrace_syscall.h"

/**
*@brief move to the next signal
*
*@param status
*@param pid
*@param regs
*/
void next_signal(int *status, pid_t pid, struct user_regs_struct *regs)
{
    ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
    waitpid(pid, status, 0);
    ptrace(PTRACE_GETREGS, pid, NULL, regs);
}

/**
*@brief fill the actual_signal structure with the regs value
*
*@param regs
*@param actual_signal
*/
void fill_actual_signal_with_regs_value(struct user_regs_struct regs,
syscall_t *actual_signal)
{
    actual_signal->id = regs.orig_rax;
    actual_signal->rdi = regs.rdi;
    actual_signal->rsi = regs.rsi;
    actual_signal->rdx = regs.rdx;
    actual_signal->r10 = regs.r10;
    actual_signal->r8 = regs.r8;
    actual_signal->r9 = regs.r9;
    actual_signal->rax = regs.rax;
    (void)table;
}

/**
*@brief match the actual sigcall with the sigcall table
*
*@param actual_signal
*/
void matching_actual_signal_with_signal_table(syscall_t *actual_signal)
{
    for (int i = 0; table[i].id != -1; i++) {
        if (actual_signal->id == table[i].id) {
            actual_signal->name = table[i].name;
            actual_signal->nb_args = table[i].nb_args;
            return;
        }
    }
    actual_signal->name = "?";
    actual_signal->nb_args = 6;
}

/**
*@brief match the actual args with the correspondant reg
*
*@param actual_signal
*@param i
*@return int
*/
unsigned long long int get_matching_reg(syscall_t actual_signal, int i)
{
    if (i == 0)
        return actual_signal.rdi;
    if (i == 1)
        return actual_signal.rsi;
    if (i == 2)
        return actual_signal.rdx;
    if (i == 3)
        return actual_signal.r10;
    if (i == 4)
        return actual_signal.r8;
    if (i == 5)
        return actual_signal.r9;
    return 0;
}

/**
*@brief display the actual sygcall content
*
*@param actual_signal
*/
void display_actual_signal(syscall_t actual_signal)
{
    fprintf(stderr, "%s(", actual_signal.name);
    for (int i = 0; i < actual_signal.nb_args; i++) {
        fprintf(stderr, "%#llx", get_matching_reg(actual_signal, i));
        if (i + 1 < actual_signal.nb_args)
            fprintf(stderr, ", ");
    }
    fprintf(stderr, ") = %#llx\n", actual_signal.rax);
}