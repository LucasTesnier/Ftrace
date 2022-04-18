/*
** EPITECH PROJECT, 2022
** ftrace
** File description:
** ftrace_error_handling
*/

#ifndef FTRACE_ERROR_HANDLING_H_
    #define FTRACE_ERROR_HANDLING_H_
    #define WRONG_ARGUMENTS_NUMBERS -1
    #define USAGE_CODE 1
    #define USAGE_STRING "--help"
    #include <string.h>
    #include <stdio.h>

int ftrace_error_handling(int ac, char **av);

#endif /* !FTRACE_ERROR_HANDLING_H_ */
