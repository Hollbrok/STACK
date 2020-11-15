#include "stack.h"

int ERROR_STATE              = 0;
int DOUBLE_CONSTRUCT         = 0;
int FILE_PRINT_ERROR         = 1;
int FILE_PRINT_DUMP          = 1;
char* mode_error             = "w";
char* mode_dump              = "w";

void stack_construct(int max_c, stack_t* Stack)
{

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
        fprintf(res, "******************************************************************\n");
        ERROR_STATE = CAPACITY_LESS_ZERO;
        fprintf(res, "ERROR №%d: %s.\n", ERROR_STATE, error_print(ERROR_STATE));
        fprintf(res, "******************************************************************\n");
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

    ASSERT_OK
}

void stack_destruct(stack_t* Stack)
{
    ASSERT_OK

    for(int i = -1; i <= Stack->capacity; i++)
        Stack->data[i] = POISON;
    free(Stack->data - 1);

    Stack->data = nullptr;

    Stack->cur_size = POISON;
    Stack->capacity = POISON;
}

void push_stack(stack_t* Stack, double push_num)
{
    assert(Stack);
    assert(push_num);

    ASSERT_OK

    FILE* res = fopen("log_stack.txt", "ab");

    if(fpclassify(push_num) != FP_NORMAL)
    {
        fclose(res);
        stack_dump(Stack);
        return;
    }

    else if(Stack->cur_size == Stack->capacity)
    {
        add_memory(Stack);
        fclose(res);
        Stack->data[Stack->cur_size++] = push_num;
    }

    else
    {

        fclose(res);
        Stack->data[Stack->cur_size++] = push_num;
    }

}

double pop_stack(stack_t* Stack)
{
    if(ERROR_STATE)
        return NAN;

    if(stack_verify(Stack))
        return NAN;

    if(Stack->cur_size <= Stack->capacity / 2)
    {
        add_memory(Stack);
        Stack->cur_size--;
        double temp = Stack->data[Stack->cur_size];
        Stack->data[Stack->cur_size] = POISON;
        return temp;
    }

    else if(Stack->cur_size > 0)
    {
        Stack->data[Stack->cur_size - 1] = POISON;

        return (Stack->data[Stack->cur_size--]);
    }
}

void stack_dump(stack_t* Stack)
{

    FILE* res = fopen("log_stack.txt", "ab");

    fprintf(res, "******************************************************************\n");


    if(ERROR_STATE)
    {
        fprintf(res, "Stack (ERROR #%d : %s) [%p]\n", ERROR_STATE, error_print(ERROR_STATE), Stack);
    }

    else
    {
        fprintf(res, "Stack(OK) [%p]\n", Stack);
        fprintf(res, "size      = %d\n", Stack->cur_size);
        fprintf(res, "capacity  = %d\n", Stack->capacity);

        int cap = Stack->capacity;
        int cur = Stack->cur_size;

        for(int i = 0; i < cap; i++)
        {
            if(i < cur) fprintf(res, "*[%d] data = %.3lf\n", i, Stack->data[i]);
            else fprintf(res, "[%d]  data = %.3lf\n", i, Stack->data[i]);

        }
    }


    fprintf(res, "******************************************************************\n\n\n");
    fclose(res);
}

int stack_verify(stack_t* Stack)
{

    if(Stack == nullptr)
    {

        ERROR_STATE = NULL_STACK_PTR;
        return NULL_STACK_PTR;
    }

    else if(Stack->data == nullptr)
    {
        ERROR_STATE = NULL_DATA_PTR;
        return NULL_DATA_PTR;
    }

    else if(Stack->cur_size > Stack->capacity)
    {
        ERROR_STATE = CUR_BIGGER_CAPACITY;
        return CUR_BIGGER_CAPACITY;
    }

    else if(Stack->cur_size < 0)
    {
        ERROR_STATE = CUR_LESS_ZERO;
        return CUR_LESS_ZERO;

    }

    else if(fpclassify(Stack->capacity) != FP_NORMAL)
    {
        ERROR_STATE = CLASSIFY_CAPACITY;
        return CLASSIFY_CAPACITY;
    }



    else if(Stack->capacity < 0)
    {
        ERROR_STATE = CAPACITY_LESS_ZERO;
        return CAPACITY_LESS_ZERO;
    }


    else if(fpclassify(Stack->cur_size) != FP_NORMAL && Stack->cur_size > 0)
    {
        ERROR_STATE = CLASSIFY_CUR;
        return CLASSIFY_CUR;
    }

    else if(Stack->data[-1] != CANARY_LEFT_DATA)
    {
        ERROR_STATE = ERROR_DATA_LEFT;
        return ERROR_DATA_LEFT;

    }

    else if(Stack->data[Stack->capacity] != CANARY_RIGHT_DATA)
    {
        ERROR_STATE = ERROR_DATA_RIGHT;
        return ERROR_DATA_RIGHT;
    }

    else if(Stack->canary_left_stack != CANARY_LEFT_STACK)
    {
        ERROR_STATE = ERROR_STACK_LEFT;
        return ERROR_STACK_LEFT;
    }

    else if(Stack->canary_right_stack != CANARY_RIGHT_STACK)
    {
        ERROR_STATE = ERROR_STACK_RIGHT;
        return ERROR_STACK_RIGHT;
    }

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
    else if(ERROR_STATE ==  9)
        return "ERROR_DATA_LEFT";
    else if(ERROR_STATE ==  10)
        return "ERROR_DATA_RIGHT";
    else if(ERROR_STATE ==  11)
        return "ERROR_STACK_LEFT";
    else if(ERROR_STATE ==  12)
        return "ERROR_STACK_RIGHT";
}

void add_memory(stack_t* Stack)
{

    ASSERT_OK

    if(Stack->cur_size == Stack->capacity)
    {
        Stack->capacity *= 2;

        Stack->data = (double*) realloc(Stack->data - 1, (Stack->capacity + 2) * sizeof(double));

        for(int i = Stack->capacity / 2 + 1; i <= Stack->capacity; i++)
            Stack->data[i] = POISON;

        Stack->data++;
        Stack->data[Stack->capacity] = CANARY_RIGHT_DATA;

    }

    else if(Stack->cur_size <= Stack->capacity / 4 + 1) //как только уменьшиться кол-во элементов в 2 раза(не включительно)
    {
        Stack->capacity /= 2;
        Stack->data = (double*) realloc(Stack->data - 1, (Stack->capacity +2) * sizeof(double));

        Stack->data++;
        Stack->data[Stack->capacity] = CANARY_RIGHT_DATA;

    }

    ASSERT_OK
}
