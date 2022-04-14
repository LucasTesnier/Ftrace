/*
** EPITECH PROJECT, 2022
** ftrace
** File description:
** frace_error_handling
*/

#include "ftrace_error_handling.h"

/**
*@brief display the message for ftrace
*
*@param code code corresponding to the message
*/
static void display_messages(int code)
{
    if (code == USAGE_CODE)
        puts("USAGE:\tftrace\t<command>");
    else if (code == WRONG_ARGUMENTS_NUMBERS)
        fprintf(stderr, "Wrong numbers of arguments\nSee ./ftrace --help\n");
}

/**
*@brief handle the received arguments
*
*@param ac
*@param av
*@return 0 the argument is valid, corresponding code otherwise
*/
int ftrace_error_handling(int ac, char **av)
{
    if (ac != 2) {
        display_messages(WRONG_ARGUMENTS_NUMBERS);
        return WRONG_ARGUMENTS_NUMBERS;
    }
    if (!strcmp(USAGE_STRING, av[1])) {
        display_messages(USAGE_CODE);
        return USAGE_CODE;
    }
    return 0;
}
