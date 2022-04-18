/*
** EPITECH PROJECT, 2022
** ftrace
** File description:
** ftrace_signals
*/

#ifndef FTRACE_SIGNALS_H_
    #define FTRACE_SIGNALS_H_

    #include <stdio.h>
    #include <sys/ptrace.h>
    #include <sys/wait.h>
    #include <sys/user.h>

void next_signal(int *status, pid_t pid, struct user_regs_struct *regs);
void fill_actual_signal_with_regs_value(struct user_regs_struct regs,
syscall_t *actual_signal);
void matching_actual_signal_with_signal_table(syscall_t *actual_signal);
void display_actual_signal(syscall_t actual_signal);

#endif /* !FTRACE_SIGNALS_H_ */
