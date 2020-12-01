#define CHAR_T
#include "stack.h"
#undef CHAR_T



int main()
{
    setlocale(LC_ALL, "russian");
    FILE* res = fopen("log_stack.txt", "w");
    fclose(res);
    char* name = "";

    START_ACTIONS(Stack);

    Construct(&Stack, 9);
    printf("00");
    stack_dump(&Stack);
    printf("\nafter 1 dump\n");

    push_stack(&Stack, 'g');
    printf("after 1 push\n");

    push_stack(&Stack, 'h');
    printf("after 2 push\n");

    push_stack(&Stack, 'g');
    printf("after 3 push\n");
    stack_dump(&Stack);

    push_stack(&Stack, 'u');
    stack_dump(&Stack);

    //Stack.data[2] = 24;// hack of the stack

    pop_stack(&Stack);
    pop_stack(&Stack);
    pop_stack(&Stack);
    pop_stack(&Stack);
    stack_dump(&Stack);

    stack_destruct(&Stack);
    //stack_destruct(&Stack);

    START_ACTIONS(Stack2);
    Construct(&Stack2, 5);

    stack_dump(&Stack2);

    push_stack(&Stack2, 'f');
    stack_dump(&Stack2);

    printf("FUCKING INSANE");

    return 0;
}
