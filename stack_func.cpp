#include "stack.h"

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
