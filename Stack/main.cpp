#include "for_user.h"

int main()
{

    setlocale(LC_ALL, "russian");

    FILE* res = fopen("log_stack.txt", "w");
    fclose(res);
    char* name = nullptr;

    START_ACTIONS(Stack);

    Construct(&Stack, 2);
    //printf("before dumpRRRRRRRRRRRRRRRRRRRRRRRR\n");
    stack_dump(&Stack);
//printf("after dump\n");
    push_stack(&Stack, 0);
    push_stack(&Stack, 2);
    push_stack(&Stack, 0);
    push_stack(&Stack, 2);
    push_stack(&Stack, 0);
    push_stack(&Stack, 2);
    push_stack(&Stack, 0);
    push_stack(&Stack, 2);
    push_stack(&Stack, 0);
    push_stack(&Stack, 2);
    push_stack(&Stack, 0);
    push_stack(&Stack, 2);
    stack_dump(&Stack);
    pop_stack(&Stack);
    pop_stack(&Stack);
    pop_stack(&Stack);
    pop_stack(&Stack);
    pop_stack(&Stack);
    pop_stack(&Stack);
    pop_stack(&Stack);
    pop_stack(&Stack);
    //Stack.data[1] = 22;
    stack_dump(&Stack);
//printf("before pushDSAFASFASFAF\n");
    push_stack(&Stack, 1);
    //printf("before dump\n");
    stack_dump(&Stack);
    //printf("before pop\n");
    pop_stack(&Stack);
    pop_stack(&Stack);
//printf("after pop\n");
    stack_dump(&Stack);

    stack_destruct(&Stack);

    START_ACTIONS(Stack2);
    Construct(&Stack2, 1);

    stack_dump(&Stack2);

    push_stack(&Stack2, 3);
    push_stack(&Stack2, 6);
    push_stack(&Stack2, 5);
    push_stack(&Stack2, 1);
    stack_dump(&Stack2);

    printf("FUCKING INSANE");
    getch();

    return 0;
}
