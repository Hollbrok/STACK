#ifndef STACK_CONFIG_H_INCLUDED
#define STACK_CONFIG_H_INCLUDED

enum
{
    POISON              = -1,
    NULL_STACK_PTR      = 1,
    NULL_DATA_PTR       = 2,
    CUR_BIGGER_CAPACITY = 3,
    CUR_LESS_ZERO       = 4,
    CAPCITY_LESS_ZERO   = 5,
    CLASSIFY_CAPACITY   = 6,
    CLASSIFY_CUR        = 7,
    ERROR_STATE         = 0,
};


#endif // STACK_CONFIG_H_INCLUDED
