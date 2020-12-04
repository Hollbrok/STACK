#include "for_user.h"


int main()
{
    setlocale(LC_ALL, "russian");

    FILE* res = fopen("log_stack.txt", "w");
    fclose(res);
    char* name = "";

    START_ACTIONS(Stack);

    Construct(&Stack, 1);
    stack_dump(&Stack);

    push_stack(&Stack, "faa");
    stack_dump(&Stack);

    push_stack(&Stack, "gaa");
    stack_dump(&Stack);

    pop_stack(&Stack);
    pop_stack(&Stack);
    pop_stack(&Stack);
    pop_stack(&Stack);
    stack_dump(&Stack);

    stack_destruct(&Stack);

    START_ACTIONS(Stack2);
    Construct(&Stack2, 5);

    stack_dump(&Stack2);

    push_stack(&Stack2, "jksbz");
    stack_dump(&Stack2);

    //printf("FUCKING INSANE");

    return 0;
}
