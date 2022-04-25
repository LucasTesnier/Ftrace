/*
** EPITECH PROJECT, 2022
** Project
** File description:
** function_stack
*/

#ifndef FUNCTION_STACK_H_
    #define FUNCTION_STACK_H_

    #include "function_init.h"

typedef struct node_s {
    struct node_s *prev;
    function_t *function;
} node_t;

typedef struct f_stack_s {
    node_t *bottom;
} f_stack_t;

void destroy_function_stack(f_stack_t *stack);
void destroy_node(node_t *node);
char *pop_last_function(f_stack_t *stack);
void add_function_stack(f_stack_t *stack, function_t *function);
f_stack_t *init_function_stack(void);

#endif /* !FUNCTION_STACK_H_ */
