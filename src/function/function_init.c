/*
** EPITECH PROJECT, 2022
** Project
** File description:
** function_init
*/

#include "function_init.h"
#include "elf_adress.h"
#include <string.h>
#include <stdlib.h>

char *create_unknown_name(trace_data_t *trace_data, char *address)
{
    char *new_name = malloc(sizeof(char) * (6 + strlen(address) +
    strlen(trace_data->raw_command)));

    if (new_name == ERROR_MALLOC)
        return ERROR_MALLOC;
    new_name[0] = '\0';
    strcat(new_name, "func_");
    strcat(new_name, address);
    strcat(new_name, "@");
    strcat(new_name, trace_data->raw_command);
    return new_name;
}

function_t *init_function(elf_info_t *elf_info, trace_data_t *trace_data,
char *address)
{
    function_t *new_function = malloc(sizeof(function_t) * 1);

    if (new_function == ERROR_MALLOC)
        return ERROR_MALLOC;
    new_function->address = strdup(address);
    new_function->name = elf_get_name_from_adress(elf_info, address);
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
    free(function->name);
    free(function->address);
    free(function);
}