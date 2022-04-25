/*
** EPITECH PROJECT, 2022
** Project
** File description:
** function_init
*/

#ifndef FUNCTION_INIT_H_
    #define FUNCTION_INIT_H_

    #include <stddef.h>
    #include "ftrace_trace_command.h"
    #include "elf_open.h"

    #define ERROR_MALLOC NULL

typedef struct function_s {
    char *name;
    char *address;
} function_t;

function_t *init_function(elf_info_t *elf_info, trace_data_t *trace_data,
char *adress);
char *create_unknown_name(trace_data_t *trace_data, char *adress);
void destroy_function(function_t *function);

#endif /* !FUNCTION_INIT_H_ */
