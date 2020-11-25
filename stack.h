#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <limits.h>

#include "stack_config.h"

#define DOUBLE_T

#ifdef DOUBLE_T
    typedef double type_data;
    const double POISON = NAN;
    #define FORMAT "lf"
#endif

#define INT_T

#ifdef INT_T
    typedef int type_data;
    const int POISON = INT_MAX;
    #define FORMAT "d"
#endif

#define FLOAT_T

#ifdef FLOAT_T
    typedef float type_data;
    const type_data POISON = NAN;
    #define FORMAT "f"
#endif

#define CHAR_T

#ifdef CHAR_T
    typedef char type_data;
    const type_data POISON = "я";
    #define FORMAT "c"
#endif

#define STRING_T

#ifdef STRING_T
    typedef char* type_data;
    const type_data POISON = nullptr;
    #define FORMAT "s"
#endif



#define ASSERT_OK                                       \
    if (stack_verify(Stack))                            \
    {                                                   \
        stack_dump(Stack);                              \
        return;                                         \
    }

#define START_ACTIONS(a)                                \
    stack_t a = {};                                     \

#define Construct(a,b)                                  \
        name = #a;                                      \
        name++;                                         \
        stack_construct(a, b, name);


struct stack_t
{
    int canary_left_stack;

    double* data;
    char* name;
    int capacity;//max size
    int cur_size;//size now
    int hash_stack;

    int canary_right_stack;

};

void stack_construct(stack_t* Stack, int max_c, char* name);

void stack_destruct(stack_t* Stack);

void push_stack(stack_t* Stack, double push_num);

void stack_dump(stack_t* Stack);

void add_memory(stack_t* Stack);

double pop_stack(stack_t* Stack);

int stack_verify(stack_t* Stack);

int hash_stack(stack_t* Stack);

char* error_print();

#endif // STACK_H_INCLUDED
