/*
** EPITECH PROJECT, 2022
** Project
** File description:
** function_dynamic
*/

#include "function_dynamic.h"
#include "elf_adress.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

char *elf_match_address(char *address, char *path, char *file)
{
    char *new_path = malloc(sizeof(char) * (strlen(path) + strlen(file) + 2));
    elf_info_t *elf_info = NULL;
    char *name = NULL;

    if (new_path == NULL)
        return NULL;
    new_path[0] = '\0';
    sprintf(new_path, "%s/%s", path, file);
    elf_info = elf_info_init(new_path);
    if (elf_info != NULL) {
        name = elf_get_name_from_adress(elf_info, address);
        elf_info_destroy(elf_info);
        free(new_path);
    } else {
        free(new_path);
    }
    return name;
}

char *get_path_from_pid(trace_data_t *trace_data)
{
    char *path = malloc(sizeof(char) * (strlen("/proc") +
    strlen("/map_files") + 15));

    if (path == NULL)
        return NULL;
    path[0] = '\0';
    sprintf(path, "/proc/%i/map_files", trace_data->pid);
    return path;
}

char *elf_get_dynamic_name(trace_data_t *trace_data, char *address)
{
    DIR* dir;
    char *path = get_path_from_pid(trace_data);
    struct dirent* in_file;
    char *name = NULL;

    if ((dir = opendir(path)) == NULL) {
        free(path);
        return name;
    }
    while ((in_file = readdir(dir))) {
        if (!strcmp(in_file->d_name, "."))
            continue;
        if (!strcmp(in_file->d_name, "..") || in_file->d_name[0] == '7')
            continue;
        if ((name = elf_match_address(address, path, in_file->d_name)) != NULL)
            break;
    }
    closedir(dir);
    free(path);
    return name;
}