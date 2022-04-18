/*
** EPITECH PROJECT, 2022
** ftrace
** File description:
** trace_command
*/

#include "ftrace_trace_command.h"
#include "ftrace_prepare_command.h"
#include <string.h>

/**
*@brief Free the trace_data structure
*
*@param trace_data
*/
void trace_data_destroy(trace_data_t *trace_data)
{
    free(trace_data->raw_command);
    free(trace_data->complete_command);
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
    //trace_data->complete_command = prepare_command(command, env);
    if (!trace_data->raw_command || !trace_data->complete_command) {
        free(trace_data);
        return NULL;
    }
    return trace_data;
}