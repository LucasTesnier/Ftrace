/*
** EPITECH PROJECT, 2022
** ftrace
** File description:
** ftrace_init
*/

#include "ftrace_init.h"
#include "elf_open.h"
#include <stddef.h>

/**
*@brief start the ftrace process
*
*@param ac
*@param av
*@return int
*/
int ftrace_start(int ac, char **av)
{
    elf_info_t *elf_info = elf_info_init(av[1]);

    (void)ac;
    if (elf_info == NULL)
        return 84;
    elf_info_destroy(elf_info);
    return 0;
}