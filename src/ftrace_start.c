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
    elf_info_t *elf_info = NULL;

    switch (ftrace_error_handling(ac, av)) {
    case WRONG_ARGUMENTS_NUMBERS:
        return 84;
    case USAGE:
        return 0;
    default:
        break;
    }
    elf_info = elf_info_init(av[1]);
    if (elf_info == NULL)
        return 84;
    printf("Adress name is : %s\n", elf_get_name_from_adress(elf_info, "401126"));
    elf_info_destroy(elf_info);
    return 0;
}
