/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ftrace_process_rip
*/

#ifndef FTRACE_PROCESS_RIP_H_
    #define FTRACE_PROCESS_RIP_H_

void ftrace_is_a_signal(int ptr, trace_data_t *trace_data, int *status);
void ftrace_is_leave(int ptr, f_stack_t *stack);
void ftrace_is_call(int ptr, trace_data_t *trace_data, elf_info_t *elf_info,
f_stack_t *stack);

#endif /* !FTRACE_PROCESS_RIP_H_ */
