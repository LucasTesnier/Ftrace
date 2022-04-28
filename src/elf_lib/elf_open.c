/*
** EPITECH PROJECT, 2022
** Project
** File description:
** elf_open
*/

#include "elf_open.h"
#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sysexits.h>
#include <stdio.h>

/**
*@brief init the ELF info structure
*
*@param path
*@return elf_info_t*
*/
elf_info_t *elf_info_init(char *path)
{
    elf_info_t *elf_info = malloc(sizeof(elf_info_t) * 1);

    if (elf_info == NULL)
        return NULL;
    elf_info->fd = open(path, O_RDONLY);
    if (elf_info->fd == OPEN_ERROR) {
        free(elf_info);
        return NULL;
    }
    fstat(elf_info->fd, &(elf_info->size));
    elf_info->buf = mmap(NULL, elf_info->size.st_size, PROT_READ,
    MAP_PRIVATE, elf_info->fd, 0);
    if (elf_info->buf == (void *)-1)
        return NULL;
    elf_info->elf_file = elf_open_file(elf_info->fd, path);
    if (elf_info->elf_file == NULL)
        return NULL;
    return elf_info;
}

/**
*@brief open the file and load into an ELF file
*
*@param fd
*@param path
*@return Elf*
*/
Elf *elf_open_file(file_descriptor_t fd, char *path)
{
    Elf *elf_file = NULL;

    if (elf_version(EV_CURRENT) == EV_NONE) {
        errx(EX_SOFTWARE, "ELF library initialization failed: %s.",
        elf_errmsg(-1));
        return NULL;
    }
    elf_file = elf_begin(fd, ELF_C_READ, NULL);
    if (elf_file == NULL) {
        errx(EX_SOFTWARE, "elf_begin() failed: %s.", elf_errmsg(-1));
        return NULL;
    }
    if (elf_kind(elf_file) != ELF_K_ELF) {
        errx(EX_DATAERR, "%s is not an ELF object.", path);
        return NULL;
    }
    return elf_file;
}

/**
*@brief destroy the elf_info structure
*
*@param elf_info
*/
void elf_info_destroy(elf_info_t *elf_info)
{
    munmap(elf_info->buf, elf_info->size.st_size);
    elf_end(elf_info->elf_file);
    close(elf_info->fd);
    free(elf_info);
}