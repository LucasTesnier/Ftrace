/*
** EPITECH PROJECT, 2022
** ftrace
** File description:
** ftrace_prepare_command
*/

#ifndef FTRACE_PREPARE_COMMAND_H_
    #define FTRACE_PREPARE_COMMAND_H_

    #include <sys/stat.h>
    #include <stdbool.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

char *prepare_command(char *raw_command, char **env);

#endif /* !FTRACE_PREPARE_COMMAND_H_ */
