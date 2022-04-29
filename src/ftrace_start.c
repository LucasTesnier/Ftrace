/*
** EPITECH PROJECT, 2022
** ftrace
** File description:
** ftrace_init
*/

#include "ftrace_start.h"
#include "ftrace_error_handling.h"
#include "elf_open.h"
#include "elf_adress.h"
#include "ftrace_trace_command.h"
#include <stddef.h>

/**
* @brief Init the provided structs with the given argument
*
* @param elf_info
* @param trace_data
* @param arg
* @return int
*/
static int init_structs(elf_info_t **elf_info, trace_data_t **trace_data,
char *arg, char **env)
{
    *trace_data = trace_data_create(arg, env);
    if (!trace_data)
        return -1;
    *elf_info = elf_info_init((*trace_data)->complete_command);
    if (*elf_info == NULL) {
        trace_data_destroy(*trace_data);
        return -1;
    }
    return 0;
}

/**
*@brief free the provided structures
*
*@param elf_info
*@param trace_data
*/
static void destroy_structs(elf_info_t *elf_info, trace_data_t *trace_data)
{
    elf_info_destroy(elf_info);
    trace_data_destroy(trace_data);
}

/**
*@brief start the ftrace process
*
*@param ac
*@param av
*@return int
*/
int ftrace_start(int ac, char **av, char **env)
{
    elf_info_t *elf_info = NULL;
    trace_data_t *trace_data = NULL;
    int res = 0;

    switch (ftrace_error_handling(ac, av)) {
    case WRONG_ARGUMENTS_NUMBERS:
        return 84;
    case USAGE:
        return 0;
    default:
        break;
    }
    if (init_structs(&elf_info, &trace_data, av[1], env))
        return 84;
    res = ftrace_trace_command(trace_data, elf_info);
    destroy_structs(elf_info, trace_data);
    return res;
}
