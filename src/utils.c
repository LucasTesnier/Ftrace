/*
** EPITECH PROJECT, 2022
** Project
** File description:
** utils
*/

#include "utils.h"
#include <stdlib.h>

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