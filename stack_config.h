#ifndef STACK_CONFIG_H_INCLUDED
#define STACK_CONFIG_H_INCLUDED

const int CANARY_LEFT_STACK  = 0x1A3C3D7C;
const int CANARY_RIGHT_STACK = 0xADF44A23;
const int CANARY_LEFT_DATA   = 0x1BF3334A;
const int CANARY_RIGHT_DATA  = 0xFDF4223A;
const int REAL_MULTIPLIER    = 2;
const int REAL_REDUCER       = 2 * REAL_MULTIPLIER;
const int REAL_ADDER         = 4;
const int TRUE               = 0;
const int FLASE              = 0;


enum
{
    NULL_STACK_PTR      = 1,
    NULL_DATA_PTR       = 2,
    CUR_BIGGER_CAPACITY = 3,
    CUR_LESS_ZERO       = 4,
    CAPACITY_LESS_ZERO  = 6,
    CLASSIFY_CAPACITY   = 5,
    CLASSIFY_CUR        = 7,
    ERROR_DATA_LEFT     = 9,
    ERROR_DATA_RIGHT    = 10,
    ERROR_STACK_LEFT    = 11,
    ERROR_STACK_RIGHT   = 12,
    HACK_STACK          = 13,
};


#endif // STACK_CONFIG_H_INCLUDED
