#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include <iostream>
#include <conio.h>

#include "stack_config.h"


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

#endif // STACK_H_INCLUDED
