#include "stack.h"

int main()
{
    setlocale(LC_ALL, "russian");
    FILE* res = fopen("log_stack.txt", "w");
    fclose(res);
    char* name = "";

    START_ACTIONS(Stack);

    Construct(&Stack, 5);

    stack_dump(&Stack);

    push_stack(&Stack, 5464);
    stack_dump(&Stack);


    push_stack(&Stack, 111);
    push_stack(&Stack, 2);
    push_stack(&Stack, 1);
    stack_dump(&Stack);

    push_stack(&Stack, 1);
    stack_dump(&Stack);

    push_stack(&Stack, 1);
    push_stack(&Stack, 2);
    stack_dump(&Stack);

    stack_destruct(&Stack);

//-----------------------------------------------------------------------------

    START_ACTIONS(Stack2);
    Construct(&Stack2, 4);

    stack_dump(&Stack2);

    push_stack(&Stack2, 44);
    stack_dump(&Stack2);

    return 0;
}
