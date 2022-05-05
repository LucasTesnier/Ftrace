/*
** EPITECH PROJECT, 2022
** Project
** File description:
** elf_adress
*/

#ifndef ELF_ADRESS_H_
    #define ELF_ADRESS_H_

    #include "elf_open.h"
    #include <stdlib.h>

    #define ELF_ADRESS_ERROR NULL
    #define ELF_ADRESS_SUCCESS 0
    #define ELF_ADRESS_FAIL 1

typedef struct elf_adress_s {
    GElf_Shdr symtab;
    GElf_Shdr strtab;
    Elf64_Sym *sym;
    char *str;
    Elf_Data *data_rel;
    Elf_Data *data_sym;
    GElf_Shdr scn_sym;
} elf_adress_t;

elf_adress_t *init_elf_adress(elf_info_t *elf_info);
int fill_elf_adress(elf_info_t *elf_info, elf_adress_t *elf_adress,
size_t shstrndx);
char *elf_get_name_from_adress(elf_info_t *elf_info,
char *adress, unsigned long rip);

#endif /* !ELF_ADRESS_H_ */
