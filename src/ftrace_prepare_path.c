/*
** EPITECH PROJECT, 2022
** ftrace
** File description:
** ftrace_prepare_path
*/

#include "ftrace_prepare_command.h"

/**
*@brief calc length of the given tab
*
*@param tab
*@return tablen
*/
static int my_tablen(char **tab)
{
    int len = 0;

    while (tab[len] != NULL)
        len++;
    return len;
}

/**
*@brief calc nb paths form env variable PATH
*
*@param paths
*@return paths
*/
static int calc_nb_paths(char *paths)
{
    int nb_paths = 1;

    for (int i = 0; paths[i] != '\0'; i++) {
        if (paths[i] == ':')
            nb_paths++;
    }
    return nb_paths;
}

/**
*@brief put env paths in tab paths
*
*@param env
*@param paths
*@return paths
*/
static char **put_paths_in_tab(char **paths, char *env)
{
    int start = 0;
    int end = 0;
    int x = 0;

    for (int i = 0; env[i] != '\0'; i++) {
        if (env[i + 1] == ':' || env[i + 1] == '\0') {
            end = i;
            paths[x] = malloc(sizeof(char) * (end - start + 2));
            strncpy(paths[x], &env[start], end - start + 1);
            x++;
            start = i + 2;
        }
    }
    if (!paths)
        return NULL;
    return paths;
}

/**
*@brief form the environment, get all paths
*
*@param env
*@return paths
*/
char **get_paths(char **env)
{
    char **paths = NULL;
    int nb_paths = 0;
    int p_line = 0;
    int tab_len = my_tablen(env);

    while (p_line < tab_len && strncmp(env[p_line], "PATH", 4) != 0)
        p_line++;
    nb_paths = calc_nb_paths(env[p_line]);
    paths = malloc(sizeof(char *) * (nb_paths +1));
    if (!paths)
        return NULL;
    paths[nb_paths] = NULL;
    paths = put_paths_in_tab(paths, env[p_line]);
    if (!paths)
        return NULL;
    return paths;
}

/**
*@brief free the given paths
*
*@param paths
*/
void free_paths(char **paths)
{
    for (int x = 0; paths[x]; x++)
        free(paths[x]);
    free(paths);
}
