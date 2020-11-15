#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <assert.h>

#include "stack_config.h"

#define ASSERT_OK                                       \
    if (stack_verify(Stack))                            \
    {                                                   \
        stack_dump(Stack);                              \
        return;                                         \
    }

#define START_ACTIONS                                   \
    setlocale(LC_ALL, "russian");                       \
    stack_t Stack= {};                                  \
    FILE* res = fopen("log_stack.txt", "w");            \
    fclose(res);                                        \
    double zero = 0;

struct stack_t
{
    int canary_left_stack;
    double* data;
    int capacity;//max size
    int cur_size;//size now
    int canary_right_stack;

};

void stack_construct(int max_c, stack_t* Stack);

void stack_destruct(stack_t* Stack);

void push_stack(stack_t* Stack, double push_num);

double pop_stack(stack_t* Stack);

void stack_dump(stack_t* Stack);

int stack_verify(stack_t* Stack);

char* error_print(int ERROR_STATE);

void add_memory(stack_t* Stack);

#endif // STACK_H_INCLUDED
