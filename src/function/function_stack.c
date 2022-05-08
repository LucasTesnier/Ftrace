/*
** EPITECH PROJECT, 2022
** Project
** File description:
** function_stack
*/

#include "function_stack.h"
#include <string.h>
#include <stdio.h>

/**
*@brief init the function stack object
*
*@return f_stack_t*
*/
f_stack_t *init_function_stack(void)
{
    f_stack_t *new_stack = malloc(sizeof(f_stack_t) * 1);

    if (new_stack == ERROR_MALLOC)
        return ERROR_MALLOC;
    new_stack->bottom = NULL;
    return new_stack;
}

/**
*@brief add a function in the stack
*
*@param stack
*@param function
*/
void add_function_stack(f_stack_t *stack, function_t *function)
{
    node_t *new = malloc(sizeof(node_t) * 1);
    node_t *ptr = stack->bottom;

    if (new == ERROR_MALLOC)
        return;
    new->function = function;
    new->prev = NULL;
    if (ptr == NULL) {
        stack->bottom = new;
        return;
    }
    while (ptr->prev != NULL)
        ptr = ptr->prev;
    ptr->prev = new;
}

/**
*@brief pop the last function in the stack
*
*@param stack
*@return char*
*/
char *pop_last_function(f_stack_t *stack)
{
    node_t *ptr = stack->bottom;
    node_t *s = NULL;
    char *save = NULL;

    if (ptr == NULL)
        return NULL;
    if (ptr->prev == NULL) {
        save = strdup(ptr->function->name);
        destroy_node(ptr);
        stack->bottom = NULL;
        return save;
    }
    while (ptr->prev != NULL) {
        s = ptr;
        ptr = ptr->prev;
    }
    s->prev = NULL;
    save = strdup(ptr->function->name);
    destroy_node(ptr);
    return save;
}

/**
*@brief destroy a node
*
*@param node
*/
void destroy_node(node_t *node)
{
    destroy_function(node->function);
    if (node->prev != NULL)
        destroy_node(node->prev);
    free(node);
}

/**
*@brief destroy the stack object
*
*@param stack
*/
void destroy_function_stack(f_stack_t *stack)
{
    if (stack->bottom != NULL)
        destroy_node(stack->bottom);
    free(stack);
}