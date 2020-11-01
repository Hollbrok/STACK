#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include <iostream>

struct node
{
    double data;
    struct node* p;
};

void push(node **pptop, double date);
double pop(node **pptop);
void print(node **pptop);

int main()
{
    struct node *ptop = NULL;

    push(&ptop, 40);
    push(&ptop, 0.012);
    push(&ptop, 222/0);




    print(&ptop);
    print(&ptop);
    print(&ptop);
    print(&ptop);
    print(&ptop);
    print(&ptop);
    print(&ptop);
    print(&ptop);
    print(&ptop);
    print(&ptop);
    //printf("%.2lf \n", pop(&ptop));

    return 0;
}

double pop(node **pptop)
{
    struct node *temp;
    double x;

    if(*pptop == NULL)
    {
        printf("STACK IS EMPTY");
        exit(0);
    }

    temp = *pptop;
    x = temp->data;



    *pptop = temp -> p;
    free(temp);

    /*if(x == 0)
    {
        return 0;
    }*/

    if(x == EOF)
    {
        printf("Trying of hacking stack if failed, returned ");
        return 0;
    }

    /*if(isnan(x))
    {
        printf("Trying of hacking stack if failed, returned ");
        return 0;
    }*/

    if(fpclassify (x) != FP_NORMAL)
    {
        printf("Trying of hacking stack if failed, returned ");
        return 0;
    }

    return x;
}

void push(node **pptop,double date)
{



    node *temp;
    temp = (struct node*) calloc(1, sizeof( node));
    if(temp == NULL)
    {
        printf("STACK IS FULL");
        exit(0);
    }

    temp->data = date;
    temp->p    = *pptop;
    *pptop     = temp;

}

void print(node **pptop)
{
    printf("%.2lf \n", pop(pptop));
}
