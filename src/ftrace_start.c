/*
** EPITECH PROJECT, 2022
** ftrace
** File description:
** ftrace_init
*/

#include "ftrace_start.h"
#include "ftrace_error_handling.h"

/**
*@brief start the ftrace process
*
*@param ac
*@param av
*@return int
*/
int ftrace_start(int ac, char **av)
{
    switch (ftrace_error_handling(ac, av)) {
    case WRONG_ARGUMENTS_NUMBERS:
        return -84;
    case USAGE:
        return 0;
    default:
        break;
    }
    return 0;
}
