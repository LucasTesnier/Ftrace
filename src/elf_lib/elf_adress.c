/*
** EPITECH PROJECT, 2022
** Project
** File description:
** elf_adress
*/

#include "elf_open.h"
#include "elf_adress.h"
#include "utils.h"
#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sysexits.h>
#include <string.h>
#include <stdio.h>

/**
*@brief init the elf_adress structure
*
*@param elf_info
*@return elf_adress_t*
*/
elf_adress_t *init_elf_adress(elf_info_t *elf_info)
{
    elf_adress_t *elf_adress = malloc(sizeof(elf_adress_t) * 1);
    size_t shstrndx = 0;

    if (elf_adress == NULL)
        return ELF_ADRESS_ERROR;
    if (elf_getshdrstrndx(elf_info->elf_file, &shstrndx) != 0) {
        errx(EX_SOFTWARE, "elf_getshdrstrndx() failed : %s.", elf_errmsg(-1));
        return ELF_ADRESS_ERROR;
    }
    if (fill_elf_adress(elf_info, elf_adress, shstrndx)) {
        free(elf_adress);
        return ELF_ADRESS_ERROR;
    }
    return elf_adress;
}

/**
*@brief fill the elf adress structure (match the str and sym tab)
*
*@param elf_info
*@param elf_adress
*@param shstrndx
*@return int
*/
int fill_elf_adress(elf_info_t *elf_info, elf_adress_t *elf_adress,
size_t shstrndx)
{
    Elf_Scn *scn = NULL;
    GElf_Shdr shdr;
    char *name = NULL;

    while ((scn = elf_nextscn(elf_info->elf_file, scn)) != NULL) {
        if (gelf_getshdr(scn, &shdr) != &shdr) {
            errx(EX_SOFTWARE, "getshdr() failed: %s.", elf_errmsg(-1));
            return ELF_ADRESS_FAIL;
        }
        if ((name = elf_strptr(elf_info->elf_file,
        shstrndx, shdr.sh_name)) == NULL) {
            errx(EX_SOFTWARE, "elf_strptr() failed: %s.", elf_errmsg(-1));
            return ELF_ADRESS_FAIL;
        }
        if (strcmp(name, ".symtab") == 0)
            elf_adress->symtab = shdr;
        if (strcmp(name, ".strtab") == 0)
            elf_adress->strtab = shdr;
        if (shdr.sh_type == SHT_RELA && strcmp(name, ".rela.plt") == 0)
            elf_adress->data_rel = elf_getdata(scn, NULL);
        if (shdr.sh_type == SHT_DYNSYM)
            elf_adress->data_sym = elf_getdata(scn, NULL);
            
    }
    return ELF_ADRESS_SUCCESS;
}

char *elf_get_name_dynamic(elf_info_t *elf_info, elf_adress_t *elf_adress, int pos, char *adress)
{
    GElf_Rela rela;
    GElf_Sym sym;
    char *name = NULL;

    gelf_getrela(elf_adress->data_rel, pos, &rela);
    if (rela.r_offset == 0)
        return name;
    gelf_getsym(elf_adress->data_sym, GELF_R_SYM(rela.r_info), &sym);
    /*if (sym.st_info != STT_SECTION &&
            sym.st_info != STT_FILE && hex_to_dec(adress) ==
            sym.st_value &&
            ((char *)(elf_adress->str + sym.st_name))[0] != '.')
            name = elf_adress->str + sym.st_name;*/
    if (sym.st_value != 0)
        printf("Adresse : %li, offset : %li\n", sym.st_value, rela.r_offset);
    return name;
}

/**
*@brief return the matching name for the given adress in an ELF file
*
*@param elf_info
*@param adress
*@return char*
*/
char *elf_get_name_from_adress(elf_info_t *elf_info, char *adress)
{
    elf_adress_t *elf_adress = init_elf_adress(elf_info);
    char *name = NULL;

    if (elf_adress == ELF_ADRESS_ERROR)
        return ELF_ADRESS_ERROR;
    if (!elf_adress->symtab.sh_size || !elf_adress->strtab.sh_size)
        return ELF_ADRESS_ERROR;
    elf_adress->sym = (Elf64_Sym *) (elf_info->buf +
    elf_adress->symtab.sh_offset);
    elf_adress->str = (char *) (elf_info->buf + elf_adress->strtab.sh_offset);
    for (size_t i = 1; i < elf_adress->symtab.sh_size /
    elf_adress->symtab.sh_entsize; i++) {
        name = elf_get_name_dynamic(elf_info, elf_adress, i, adress);
        if (elf_adress->sym[i].st_info != STT_SECTION &&
            elf_adress->sym[i].st_info != STT_FILE && hex_to_dec(adress) ==
            elf_adress->sym[i].st_value &&
            ((char *)(elf_adress->str + elf_adress->sym[i].st_name))[0] != '.')
            name = elf_adress->str + elf_adress->sym[i].st_name;
        if (name != NULL)
            break;
    }
    return name;
}