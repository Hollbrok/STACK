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
#include <typeinfo>
#include <ctype.h>
#include "stack_config.h"
//#include "def_type.h"

//#define STRING_T

#ifdef DOUBLE_T
    typedef double type_data;
    const type_data POISON             = NAN;
    const type_data CANARY_LEFT_DATA   = 0x1BF3334A;
    const type_data CANARY_RIGHT_DATA  = 0xFDF4223A;
    const int CANARY_L_STACK           = 0x1A3C3D7C;
    const int CANARY_R_STACK           = 0xADF44A23;
    #define FORMAT "lg"
    //const char* TYPE = "DOUBLE";
#endif


#ifdef INT_T
    typedef int type_data;
    const type_data POISON             = INT_MAX;
    const type_data CANARY_LEFT_DATA   = 0x1BF3334A;
    const type_data CANARY_RIGHT_DATA  = 0xFDF4223A;
    const int CANARY_L_STACK           = 0x1A3C3D7C;
    const int CANARY_R_STACK           = 0xADF44A23;
    #define FORMAT "d"
    //const char* TYPE = "INT";
#endif


#ifdef FLOAT_T
    typedef float type_data;
    const type_data POISON             = NAN;
    const type_data CANARY_LEFT_DATA   = 0x1BF3334A;
    const type_data CANARY_RIGHT_DATA  = 0xFDF4223A;
    const int CANARY_LEFT_STACK        = 0x1A3C3D7C;
    const int CANARY_RIGHT_STACK       = 0xADF44A23;
    #define FORMAT "f"
    //const char* TYPE = "FLOAT";
#endif

#ifdef STRING_T
    typedef char* type_data;
    const type_data POISON             = "LLLLLLLLLLL";
    const type_data CANARY_LEFT_DATA   = "glavz";
    const type_data CANARY_RIGHT_DATA  = "amoqc";
    const int CANARY_L_STACK           = 0x1A3C3D7C;
    const int CANARY_R_STACK           = 0xADF44A23;
    #define FORMAT "s"
    //const char* TYPE = "char*";
#endif

#ifdef CHAR_T
    typedef char type_data;
    const type_data POISON             = 'z';
    const type_data CANARY_LEFT_DATA   = 's';
    const type_data CANARY_RIGHT_DATA  = 'm';
    const int CANARY_L_STACK           = 0x1A3C3D7C;
    const int CANARY_R_STACK           = 0xADF44A23;
    #define FORMAT "c"
    //const char* TYPE = "char";
#endif

#ifdef LOW_SECURE // только проверка на Stack == nullptr, stack_construct
    const int low_sec   = 1;
    const int med_sec   = 0;
    const int high_sec  = 0;
    //const char* sec_lvl = "LOW";
#endif LOW_SECURE

#ifdef MEDIUM_SECURE // все проверки, кроме хэширования и канареек
    const int low_sec   = 0;
    const int med_sec   = 1;
    const int high_sec  = 0;
   // const char* sec_lvl = "MEDIUM";
#endif MEDIUM_SECURE

#ifdef HIGH_SECURE // все проверки
    const int low_sec   = 0;
    const int med_sec   = 0;
    const int high_sec  = 1;
    //const char* sec_lvl = "HIGH";
#endif HIGH_SECURE


struct stack_t
{
    int canary_left_stack;

    type_data* data       = nullptr;
    char* name            = nullptr;
    int capacity          ;//max size
    int cur_size          ;//size now
    int hash_stack        ;

    int canary_right_stack;

};


#define ASSERT_OK                                       \
    if (stack_verify(Stack))                            \
    {                                                   \
        stack_dump(Stack);                              \
        return;                                         \
    }

#define START_ACTIONS(a)                                \
    stack_t a = {};

#define Construct(a,b)                                  \
        name = #a;                                      \
        name++;                                         \
        stack_construct(a, b, name);

#define ASSERT_POP_OK                                   \
    if (stack_verify(Stack))                            \
    {                                                   \
        stack_dump(Stack);                              \
        return POISON;                                  \
    }


void stack_construct(stack_t* Stack, int max_c, char* name);

void stack_destruct(stack_t* Stack);

void push_stack(stack_t* Stack, type_data push_num);

void stack_dump(stack_t* Stack);

void add_memory(stack_t* Stack);

type_data pop_stack(stack_t* Stack);

int stack_verify(stack_t* Stack);

int hash_stack(stack_t* Stack);

char* error_print();

char* define_lvl();

#endif // STACK_H_INCLUDED
