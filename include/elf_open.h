/*
** EPITECH PROJECT, 2022
** Project
** File description:
** elf_open
*/

#ifndef ELF_OPEN_H_
    #define ELF_OPEN_H_

    #define OPEN_ERROR -1

    #include <err.h>
    #include <fcntl.h>
    #include <libelf.h>
    #include <gelf.h>

typedef int file_descriptor_t;
typedef void * content_t;

typedef struct elf_info_s {
    file_descriptor_t fd;
    content_t buf;
    Elf *elf_file;
    struct stat size;
} elf_info_t;

elf_info_t *elf_info_init(char *path);
Elf *elf_open_file(file_descriptor_t fd, char *path);
void elf_info_destroy(elf_info_t *elf_info);

#endif /* !ELF_OPEN_H_ */
