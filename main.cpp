#include "stack.h"

int main()
{
    FILE* res = fopen("log.txt", "wb");
    node *ptop = NULL;

    push(&ptop, 40);
    push(&ptop, 0.012);
    //push(&ptop, 222/0);

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


    fclose(res);

    return 0;
}
