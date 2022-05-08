/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ftrace_process_rip
*/

#include "ftrace_signals.h"
#include "function_init.h"
#include "function_stack.h"
#include "ftrace_process_rip.h"
#include "utils.h"
#include <string.h>
#include <sys/ptrace.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/reg.h>
#include <sys/wait.h>
#include <sys/user.h>

/**
*@brief hold the signal process
*
*@param ptr
*@param trace_data
*@param status
*/
void ftrace_is_a_signal(int ptr, trace_data_t *trace_data, int *status)
{
    struct user_regs_struct regs;
    syscall_t actual_signal;

    (void) table;
    if ((ptr & 0xffff) == 0x050F) {
        next_signal(status, trace_data->pid, &regs);
        fill_actual_signal_with_regs_value(regs, &actual_signal);
        matching_actual_signal_with_signal_table(&actual_signal);
        display_actual_signal(actual_signal);
    }
}

/**
*@brief hold the leave process
*
*@param ptr
*@param stack
*/
void ftrace_is_leave(int ptr, f_stack_t *stack)
{
    if ((ptr & 0xff) == 0xc3 || (ptr & 0xff) == 0xcb ||
    (ptr & 0xff) == 0xc2 || (ptr & 0xff) == 0xca) {
        if (stack->bottom != NULL) {
            printf("Leaving function %s\n", pop_last_function(stack));
        }
    }
}

/**
*@brief hold the call process
*
*@param ptr
*@param trace_data
*@param elf_info
*@param stack
*/
void ftrace_is_call(int ptr, trace_data_t *trace_data, elf_info_t *elf_info,
f_stack_t *stack)
{
    char *address = NULL;
    function_t *function = NULL;
    struct user_regs_struct regs;

    if ((ptr & 0xff) != 0xE8 || trace_data->have_main == false)
        return;
    ptrace(PTRACE_GETREGS, trace_data->pid, NULL, &regs);
    address = dec_to_hex(regs.rip + 5 + (ptr >> 8));
    if (strlen(address) == 6) {
        function = init_function(elf_info, trace_data, address);
        if (strncmp(function->name, "func_", 5))
            printf("Entering function %s at 0x%s\n", function->name,
            function->address);
        else
            printf("Entering function %s\n", function->name);
        add_function_stack(stack, function);
    }
}

/**
*@brief hold the main process
*
*@param ptr
*@param trace_data
*@param elf_info
*@param stack
*/
void ftrace_is_main(int ptr, trace_data_t *trace_data, elf_info_t *elf_info,
f_stack_t *stack)
{
    function_t *function = NULL;
    struct user_regs_struct regs;
    char *address = NULL;

    if (((ptr >> 3) & 0b111) != 2 || trace_data->have_main == true)
        return;
    ptrace(PTRACE_GETREGS, trace_data->pid, NULL, &regs);
    address = dec_to_hex(regs.rip);
    if (strlen(address) != 6)
        return;
    function = init_function(elf_info, trace_data, address);
    if (strncmp(function->name, "func_", 5)) {
        printf("Entering function %s at 0x%s\n", function->name,
        function->address);
        add_function_stack(stack, function);
        trace_data->have_main = true;
    }
}
