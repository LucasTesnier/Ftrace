/*
** EPITECH PROJECT, 2022
** ftrace
** File description:
** ftrace_prepare_path
*/

#ifndef FTRACE_PREPARE_PATH_H_
    #define FTRACE_PREPARE_PATH_H_

    #include <stdlib.h>
    #include <string.h>

char **get_paths(char **env);
void free_paths(char **paths);

#endif /* !FTRACE_PREPARE_PATH_H_ */
