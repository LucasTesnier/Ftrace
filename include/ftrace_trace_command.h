/*
** EPITECH PROJECT, 2022
** ftrace
** File description:
** trace_command
*/

#ifndef TRACE_COMMAND_H_
    #define TRACE_COMMAND_H_

    #include <sys/types.h>
    #include <stdlib.h>

typedef struct trace_data_s {
    char *raw_command;
    char *complete_command;
    pid_t pid;
} trace_data_t;

void trace_data_destroy(trace_data_t *trace_data);
trace_data_t *trace_data_create(char *command);

#endif /* !TRACE_COMMAND_H_ */
