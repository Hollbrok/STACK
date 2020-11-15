#include "stack.h"

int main()
{
    START_ACTIONS

    stack_construct(5, &Stack);
    stack_dump(&Stack);



    push_stack(&Stack, 111);
    stack_dump(&Stack);

    //printf("1");

    push_stack(&Stack, 13);
    push_stack(&Stack, 1213);
    push_stack(&Stack, 1374);
    push_stack(&Stack, 19441);
    push_stack(&Stack, 13412);
    push_stack(&Stack, 617);

    /*FILE* res = fopen("log_stack2.txt", "w");
    fprintf(res, "\nAAAAAAAAAAAAA\n");
    fclose(res); */

    stack_dump(&Stack);



    pop_stack(&Stack);
    pop_stack(&Stack);



    stack_dump(&Stack);
    //stack_destruct(&Stack);

    pop_stack(&Stack);
    pop_stack(&Stack);
    stack_dump(&Stack);

    FILE* finish = fopen("GOOD.txt", "w");
    fprintf(finish, "GOOD");
    fclose(finish);

    return 1337;
}
