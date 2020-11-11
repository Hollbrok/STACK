#include "stack.h"

int main()
{
    setlocale(LC_ALL, "russian");
    stack_t Stack= {};

    double zero = 0;

    stack_construct(5, &Stack);
    //stack_construct(5, &Stack);

    push_stack(&Stack, 1);
    stack_dump(&Stack);

    push_stack(&Stack, 4);
    stack_dump(&Stack);

    push_stack(&Stack, 0/zero);
    push_stack(&Stack, 2.444);
    push_stack(&Stack, NAN);
    push_stack(&Stack, 666);

    stack_dump(&Stack);

    pop_stack(&Stack);
    pop_stack(&Stack);

    stack_dump(&Stack);

    stack_destruct(&Stack);

    /*FILE* finish = fopen("GOOD.txt", "a");
    fprintf(finish, "GOOD");
    fclose(finish);*/

    stack_dump(&Stack);

    FILE* finish = fopen("GOOD.txt", "w");
    fprintf(finish, "GOOD");
    fclose(finish);

    return 1337;
}
