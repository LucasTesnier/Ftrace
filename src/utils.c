/*
** EPITECH PROJECT, 2022
** Project
** File description:
** utils
*/

#include "utils.h"
#include <stdlib.h>

int hex_to_dec(char *adress)
{
    return ((int)strtol(adress, NULL, 16));
}