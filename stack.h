#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include <iostream>
#include <conio.h>

struct node
{
    double data;
    struct node* p;
};

void push(node **pptop, double date);

double pop(node **pptop);

void print(node **pptop);


#endif // STACK_H_INCLUDED
