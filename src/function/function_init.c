/*
** EPITECH PROJECT, 2022
** Project
** File description:
** function_init
*/

#include "function_init.h"
#include "function_dynamic.h"
#include "elf_adress.h"
#include <string.h>
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/reg.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/user.h>

char *get_project_name(char *path)
{
    char *new_name = malloc(sizeof(char) * strlen(path));
    int pos = 0;

    for (int i = 0; i < strlen(path); i++)
        if (path[i] == '/')
            pos = i;
    new_name[0] = '\0';
    strcat(new_name, path + pos + 1);
    return new_name;
}

char *create_unknown_name(trace_data_t *trace_data, char *address)
{
    char *new_name = malloc(sizeof(char) * (6 + strlen(address) +
    strlen(trace_data->raw_command)));
    char *project_name = get_project_name(trace_data->raw_command);

    if (new_name == ERROR_MALLOC)
        return ERROR_MALLOC;
    if (project_name == ERROR_MALLOC) {
        free(new_name);
        return ERROR_MALLOC;
    }
    new_name[0] = '\0';
    strcat(new_name, "func_");
    strcat(new_name, address);
    strcat(new_name, "@");
    strcat(new_name, project_name);
    free(project_name);
    return new_name;
}

function_t *init_function(elf_info_t *elf_info, trace_data_t *trace_data,
char *address)
{
    function_t *new_function = malloc(sizeof(function_t) * 1);
    long offset = ptrace(PTRACE_PEEKTEXT, trace_data->pid,
    hex_to_dec(address) + 2);

    if (new_function == ERROR_MALLOC)
        return ERROR_MALLOC;
    new_function->address = strdup(address);
    new_function->name = elf_get_name_from_adress(elf_info, address,
    (offset & 0xFFFFFFFF) + hex_to_dec(address) + 6);
    if (new_function->name == ELF_ADRESS_ERROR)
        new_function->name = create_unknown_name(trace_data, address);
    if (new_function->name == ERROR_MALLOC) {
        free(new_function->address);
        free(new_function);
        return ERROR_MALLOC;
    }
    return new_function;
}

void destroy_function(function_t *function)
{
    free(function->address);
    free(function);
}