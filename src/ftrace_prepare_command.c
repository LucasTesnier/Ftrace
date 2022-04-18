/*
** EPITECH PROJECT, 2022
** ftrace
** File description:
** ftrace_prepare_command
*/

#include "ftrace_prepare_command.h"
#include "ftrace_prepare_path.h"

/**
*@brief check if fike
*
*@param buffer
*@return true if file exist, false otherwise
*/
static bool file_exist(char *buffer)
{
    struct stat sb;
    int value = stat(buffer, &sb);

    if (value < 0) {
        return false;
    } else {
        return true;
    }
}

/**
*@brief form the environment, get all paths
*
*@param command
*@return command if exist, otherwise NULL
*/
static char *prepare_dir_command(char *raw_command)
{
    struct stat sb;
    char *res = NULL;

    stat(raw_command, &sb);
    if (access(raw_command, F_OK) == 0) {
        if (access(raw_command, X_OK) == 0 && !(sb.st_mode & __S_IFDIR))
            res = strdup(raw_command);
        else
            printf("%s%s", raw_command, ": Permission denied.\n");
    } else {
        printf("%s%s", raw_command, ": Command not found.\n");
    }
    return res;
}

/**
*@brief concat the raw command and the path
*
*@param path
*@param raw_command
*@param new_command
*/
static void concat_command(char *path, char *raw_command, char *new_command)
{
    strcpy(new_command, path);
    strcat(new_command, "/");
    strcat(new_command, raw_command);
}

/**
*@brief form the environment, get all paths
*
*@param env
*@param raw_command
*@return command
*/
static char *prepare_path_command(char *raw_command, char **env)
{
    char **paths = get_paths(env);
    char *command = NULL;

    if (!paths)
        return NULL;
    for (int i = 0; paths[i]; i++) {
        command = malloc(sizeof(char) * (strlen(raw_command) +
        strlen(paths[i]) + 2));
        if (!command)
            return NULL;
        concat_command(paths[i], raw_command, command);
        if (access(command, X_OK) == 0)
            break;
        free(command);
        command = NULL;
    }
    free_paths(paths);
    return command;
}

/**
*@brief form the environment, get all paths
*
*@param env
*@param raw_command
*@return command
*/
char *prepare_command(char *raw_command, char **env)
{
    if (file_exist(raw_command)) {
        return prepare_dir_command(raw_command);
    } else {
        return prepare_path_command(raw_command, env);
    }
}
