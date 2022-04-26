/*
** EPITECH PROJECT, 2022
** Project
** File description:
** utils
*/

#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

/**
*@brief convert hex number to decimal
*
*@param adress
*@return int
*/
int hex_to_dec(char *adress)
{
    return ((int)strtol(adress, NULL, 16));
}

char *dec_to_hex(long long int adress)
{
    char *new = malloc(sizeof(char) * 18);

    new[0] = '\0';
    sprintf(new, "%llx", adress);
    return new;
}