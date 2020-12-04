#include "for_user.h"


int main()
{
    setlocale(LC_ALL, "russian");

    FILE* res = fopen("log_stack.txt", "w");
    fclose(res);
    char* name = "";

    START_ACTIONS(Stack);

    Construct(&Stack, 2);
    //stack_dump(&Stack);

    push_stack(&Stack, "DAROVA");
    push_stack(&Stack, "this is ");
    stack_dump(&Stack);

    push_stack(&Stack, "my stack");
    stack_dump(&Stack);

    pop_stack(&Stack);
    pop_stack(&Stack);

    stack_dump(&Stack);

    stack_destruct(&Stack);

    START_ACTIONS(Stack2);
    Construct(&Stack2, 1);

    stack_dump(&Stack2);

    push_stack(&Stack2, "This is the 2nd stack");
    push_stack(&Stack2, "with the other name");
    push_stack(&Stack2, "ANIME");
    push_stack(&Stack2, "Goodbye");
    stack_dump(&Stack2);

    //printf("FUCKING INSANE");

    return 0;
}
