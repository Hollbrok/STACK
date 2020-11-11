#include "stack.h"

int ERROR_STATE              = 0;
int DOUBLE_CONSTRUCT         = 0;
int FILE_PRINT_ERROR         = 1;
int FILE_PRINT_DUMP          = 1;
char* mode_error             = "w";
char* mode_dump              = "w";

void stack_construct(int max_c, stack_t* Stack)
{
    //FILE* res = fopen("log_stack_error.txt", "w");

    if(Stack == nullptr || DOUBLE_CONSTRUCT)
    {
        ERROR_STATE = DOUBLE_CONSTRUCT;
        stack_dump(Stack);
        return;
    }

    Stack->canary_left_stack = CANARY_LEFT_STACK;
    Stack->canary_right_stack = CANARY_RIGHT_STACK;


    Stack->cur_size = 0;

    if(max_c > 0)
    {
        Stack->capacity = max_c;
    }

    else
    {
        FILE* res = fopen("log_stack.txt", "ab");
        ERROR_STATE = CAPACITY_LESS_ZERO;
        fprintf(res, "ERROR №%d: %s.\n", ERROR_STATE, error_print(ERROR_STATE));
        return;
    }

    Stack->data = (double*)calloc(max_c + 2, sizeof(double));

    if (Stack->data == nullptr)
    {
        stack_dump(Stack);
        return;
    }

    else
    {
        Stack->data[0] = CANARY_LEFT_DATA;
        Stack->data[max_c + 1] = CANARY_RIGHT_DATA;

        for(int i = 1; i < max_c + 1; i++)
        {
            Stack->data[i] = POISON;
        }

        Stack->data++;
        DOUBLE_CONSTRUCT = 8;

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

    if(ERROR_STATE)
        return;

    if(FILE_PRINT_DUMP)
    {
        FILE_PRINT_DUMP = 0;
    }

    else
    {
        mode_dump = "a";
    }

    FILE* res = fopen("log_stack.txt", mode_dump);

    if(stack_verify(Stack))
    {
        //fprintf(res, "Error is %d\nCUR_SIZE = %d", stack_verify(Stack), Stack->cur_size);
        fclose(res);
        return;
    }

    else if(fpclassify(push_num) != FP_NORMAL)//fpclassify(push_num) == FP_NAN || fpclassify(push_num) == FP_INFINITE || fpclassify(push_num) == -0 || push_num == EOF)
    {
        //fprintf(res, "\nsomebody was trying to do something BAD\n");
        fclose(res);
        return;
    }

    else if(Stack->cur_size >= Stack->capacity)
    {
        printf("                     В ходе push'a был достигнут максимально возможный размер стэка = %d\n", Stack->capacity);
        fclose(res);
        return;
    }

    else if(Stack->cur_size >= 0 && Stack->capacity > 0)
    {
        fclose(res);
        Stack->data[Stack->cur_size++] = push_num;
    }
}

double pop_stack(stack_t* Stack)
{
    if(ERROR_STATE)
        exit(1);

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
    if(Stack == nullptr)
        return;

    if(FILE_PRINT_DUMP)
    {
        FILE_PRINT_DUMP = 0;
    }

    else
    {
        mode_dump = "a";
    }


    FILE* res = fopen("log_stack.txt", mode_dump);

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
        if(ERROR_STATE)
        {
         fprintf(res, "Stack (ERROR #%d : %s)", ERROR_STATE, error_print(ERROR_STATE));
        }
        fprintf(res, "Currently size = %d\n", Stack->cur_size);
        fprintf(res, "Max size = %d\n", Stack->capacity);

        int j = Stack->cur_size;

        for(int i = 0; i < j; i++)
        {
            fprintf(res, "[%d] data = %.3lf\n", i, Stack->data[i]);
            if(i == j - 1)
            {
                //fprintf(res, "******************************************************************");
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

    fprintf(res, "******************************************************************\n\n\n");
    fclose(res);
}

int stack_verify(stack_t* Stack)
{
    //FILE* res = fopen("log_stack_error.txt", "w");

    if(Stack == nullptr)
    {
        //fprintf(res, "Stack == nullptr\n");
        //fclose(res);
        ERROR_STATE = NULL_STACK_PTR;
        return NULL_STACK_PTR;
    }

    else if(Stack->data == nullptr)
    {
        //fprintf(res, "data == nullptr\n");
        //fclose(res);
        ERROR_STATE = NULL_DATA_PTR;
        return NULL_DATA_PTR;
    }

    else if(Stack->cur_size >= Stack->capacity)
    {
        //fprintf(res, "CUR_SIZE >= CAPACITY   (%d >= %d)\n", Stack->cur_size, Stack->capacity);
        //fclose(res);
        ERROR_STATE = CUR_BIGGER_CAPACITY;
        return CUR_BIGGER_CAPACITY;
    }

    else if(Stack->cur_size < 0)
    {
        //fprintf(res, "CUR_SIZE < 0, (%d)\n", Stack->cur_size);
        //fclose(res);
        ERROR_STATE = CUR_LESS_ZERO;
        return CUR_LESS_ZERO;

    }

    else if(fpclassify(Stack->capacity) != FP_NORMAL)
    {
        //fprintf(res, "CAPACITY is not a FP_NORMAL\n");
        //fclose(res);
        ERROR_STATE = CLASSIFY_CAPACITY;
        return CLASSIFY_CAPACITY;
    }



    else if(Stack->capacity < 0)
    {
        //fprintf(res, "CAPACITY < 0\n, (%d)", Stack->capacity);
        //fclose(res);
        ERROR_STATE = CAPACITY_LESS_ZERO;
        return CAPACITY_LESS_ZERO;
    }


    else if(fpclassify(Stack->cur_size) != FP_NORMAL && Stack->cur_size > 0)
    {
        //fprintf(res, "CUR_SIZE is not a FP_NORMAL\n");
        //fclose(res);
        ERROR_STATE = CLASSIFY_CUR;
        return CLASSIFY_CUR;
    }

    /*else if(DOUBLE_CONSTRUCT)
    {
        fprintf(res, "double construct of stack");
        fclose(res);
        ERROR_STATE = 1;
        return DOUBLE_CONSTRUCT;
    } */

    else
    {
        return 0;
    }
}

char* error_print(int ERROR_STATE)
{
    if(ERROR_STATE == 1)
        return "NULL STACK PTR";
    else if(ERROR_STATE == 2)
        return "NULL DATA PTR";
    else if(ERROR_STATE == 3)
        return "CUR BIGGER THAN CAPACITY";
    else if(ERROR_STATE == 4)
        return "CUR LESS THAN ZERO";
    else if(ERROR_STATE == 5)
        return "CAPACITY LESS THAN ZERO";
    else if(ERROR_STATE == 6)
        return "CAPACITY IS NOT A NORMAL NUMBER";
    else if(ERROR_STATE == 7)
        return "CUR_SIZE IS NOT A NORMAL NUMBER";
    else if(ERROR_STATE == 8)
        return "DOUBLE CONSTRUCT";
}
