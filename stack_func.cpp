#include "stack.h"

void stack_construct(int max_c, stack_t* Stack)
{
    if(stack_verify(Stack) == 4 || stack_verify(Stack) == 5)
    {
        //DEBUG PRINTF в log_stack;
        return;
    }

    else
    {
        Stack->cur_size = 0;

        if(max_c > 0)
        {
            Stack->capacity = max_c;
        }

        else
        {
            printf("ERROR");
            return;
        }

        Stack->data = (double*)calloc(max_c, sizeof(double));

        if (Stack->data == nullptr)
        {
            stack_dump(Stack);
            return;
        }

        for(int i = 0; i < max_c; i++)
        {
            Stack->data[i] = POISON;

        }

        Stack->data++;

    }

    if(stack_verify(Stack) == 4 || stack_verify(Stack) == 5)
    {
        //DEBUG PRINTF в log_stack;
        return;
    }
}

void stack_destruct(stack_t* Stack)
{
    if(stack_verify(Stack))
    {
        //DEBUG PRINTF в log_stack;
        return;
    }

    Stack->capacity = -2;
    Stack->data = nullptr;
    free(Stack);
}

void push_stack(stack_t* Stack, double push_num)
{
    assert(Stack);
    assert(push_num);

    if(stack_verify(Stack))
    {
        FILE* res = fopen("log_stack.txt", "w");
        fprintf(res, "Error is %d\nCUR_SIZE = %d", stack_verify(Stack), Stack->cur_size);//DEBUG PRINTF в log_stack;
        fclose(res);

        return;
    }

    else if(fpclassify(push_num) != FP_NORMAL)//fpclassify(push_num) == FP_NAN || fpclassify(push_num) == FP_INFINITE || fpclassify(push_num) == -0 || push_num == EOF)
    {
        printf("\n                    Trying of hacking stack if failed, returned\n");
        return;
    }

    else if(Stack->cur_size >= Stack->capacity)
    {
        printf("                     В ходе push'a был достигнут максимально возможный размер стэка = %d\n", Stack->capacity);
        return;
    }

    else if(Stack->cur_size >= 0 && Stack->capacity > 0)
    {
        Stack->data[Stack->cur_size++] = push_num;
    }
}

double pop_stack(stack_t* Stack)
{

    if(stack_verify(Stack))
    {
        //DEBUG PRINTF в log_stack;
        return NAN;
    }

    else if(Stack->cur_size >0)
    {
        return (Stack->data[Stack->cur_size--]);
    }

}

void stack_dump(stack_t* Stack)
{

    FILE* res = fopen("log_stack.txt", "w");

    fprintf(res, "******************************************************************\n");

    if(stack_verify(Stack) == NULL_STACK_PTR)
    {
        fprintf(res, "\n                    THERE IS NO STACK ..\n");
        fprintf(res, "******************************************************************\n");
        fclose(res);
        return;
    }

    else
    {
        fprintf(res, "Currently size = %d\n", Stack->cur_size);
        fprintf(res, "Max size = %d\n", Stack->capacity);

        int j = Stack->cur_size;

        for(int i = 0; i < j; i++)
        {
            fprintf(res, "[%d] data = %.3lf\n", i, Stack->data[i]);
            if(i == j - 1)
            {
                fprintf(res, "******************************************************************");
            }
        }

        /*int j = Stack->cur_size;
        if(!j)
            fprintf(res, "\n Stack is empty\n");
        for(int i = 0; i < j; i++)
        {
            if(i == 0) fprintf(res, "                    @*********************@\n");
            fprintf(res, "                    @Number[%d] = %6lf @\n", i + 1, Stack->data[i]);
            if(i == j - 1) fprintf(res, "                    @*********************@\n");
        }*/
    }

    fprintf(res, "******************************************************************");
    fclose(res);
}

int stack_verify(stack_t* Stack)
{
    if(Stack == nullptr)
    {
        //DEBUG PRINTF в log_stack сделать
        return NULL_STACK_PTR;
    }

    else if(Stack->data == nullptr)
    {
        //DEBUG PRINTF в log_stack сделать
        return NULL_DATA_PTR;
    }

    else if(Stack->cur_size >= Stack->capacity)
    {
        //DEBUG PRINTF в log_stack сделать
        return CUR_BIGGER_CAPACITY;
    }

    else if(Stack->cur_size < 0)
    {
        //DEBUG PRINTF в log_stack сделать
        return CUR_LESS_ZERO;

    }

    else if(Stack->capacity < 0)
    {
        //DEBUG PRINTF в log_stack сделать
        return CAPCITY_LESS_ZERO;
    }

    else if(fpclassify(Stack->capacity) != FP_NORMAL)
    {
        //DEBUG PRINTF в log_stack сделать
        return CLASSIFY_CAPACITY;
    }

    else if(fpclassify(Stack->cur_size) != FP_NORMAL && Stack->cur_size > 0)
    {
        //DEBUG PRINTF в log_stack сделать
        return CLASSIFY_CUR;
    }

    else
    {
        //DEBUG PRINTF в log_stack сделать
        return 0;

    }
}
