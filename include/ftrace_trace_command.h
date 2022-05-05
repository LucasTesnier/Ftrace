/*
** EPITECH PROJECT, 2022
** ftrace
** File description:
** trace_command
*/

#ifndef TRACE_COMMAND_H_
    #define TRACE_COMMAND_H_

    #include "elf_open.h"

    #include <sys/types.h>
    #include <stdlib.h>
    #include <stdbool.h>

typedef struct trace_data_s {
    char *raw_command;
    char *complete_command;
    pid_t pid;
    bool have_main;
} trace_data_t;

void trace_data_destroy(trace_data_t *trace_data);
trace_data_t *trace_data_create(char *command, char **env);
int ftrace_trace_command(trace_data_t *trace_data, elf_info_t *elf_info);

#endif /* !TRACE_COMMAND_H_ */
