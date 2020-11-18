#include "stack.h"

int ERROR_STATE      = 0;
int DOUBLE_CONSTRUCT = 0;
char* addres   = "C:\\Users\\Danik\\Documents\\Задачи_СИ\\Projects\\Stack\\bin\\Debug\\log_stack.txt";


void stack_construct(stack_t* Stack, int max_c, char* name)
{
    if(Stack == nullptr || DOUBLE_CONSTRUCT)
    {
        ERROR_STATE = DOUBLE_CONSTRUCT;
        stack_dump(Stack);
        //system(R"(C:\Users\Danik\Documents\Задачи СИ\Projects\Stack\bin\Debug\log_stack.txt)");
        return;
    }

    if(Stack->canary_left_stack == CANARY_LEFT_STACK || Stack->canary_right_stack == CANARY_RIGHT_STACK)
    {
        DOUBLE_CONSTRUCT = 8;
        return;
    }

    Stack->canary_left_stack = CANARY_LEFT_STACK;
    Stack->canary_right_stack = CANARY_RIGHT_STACK;


    Stack->cur_size   = 0;
    Stack->hash_stack = 0;
    Stack->name       = name;

    if(max_c >= 0)
    {
        Stack->capacity = max_c;
    }

    else
    {
        FILE* res = fopen("log_stack.txt", "ab");
        fprintf(res, "******************************************************************\n");
        ERROR_STATE = CAPACITY_LESS_ZERO;
        fprintf(res, "ERROR №%d: %s.\n", ERROR_STATE, error_print());
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
        hash_stack(Stack);
    }

    else
    {

        fclose(res);
        Stack->data[Stack->cur_size++] = push_num;
        hash_stack(Stack);
    }

}

double pop_stack(stack_t* Stack)
{
    if(ERROR_STATE)
        return NAN;

    if(stack_verify(Stack))
        return NAN;

    if(Stack->cur_size <= Stack->capacity / REAL_MULTIPLIER + 1)
    {
        add_memory(Stack);
        Stack->cur_size--;
        double temp = Stack->data[Stack->cur_size];
        Stack->data[Stack->cur_size] = POISON;
        hash_stack(Stack);
        return temp;
    }

    else if(Stack->cur_size > 0)
    {
        double temp = Stack->data[Stack->cur_size - 1];
        Stack->cur_size--;
        Stack->data[Stack->cur_size] = POISON;
        hash_stack(Stack);
        return temp;
    }

    return 0;
}

void stack_dump(stack_t* Stack)
{
    char mass[67] = "******************************************************************";

    FILE* res = fopen("log_stack.txt", "ab");

    fprintf(res, "%*s\n", 66, mass);


    if(ERROR_STATE)
    {
        fprintf(res, "Stack (ERROR #%d : %s) [%p]. \n", ERROR_STATE, error_print(), Stack, Stack->hash_stack);

        char* addres_n = "notepad ";
        char* addres_f = (char*) calloc(100, sizeof(char));
        addres_f = strcat(addres_f, addres_n);
        addres_f = strcat(addres_f, addres);
        //printf("%s", addres_f);

        //printf("Stack (ERROR #%d : %s) [%p]. \n", ERROR_STATE, error_print(), Stack, Stack->hash_stack);
        system(addres_f);
        free(addres_f);
    }

    else
    {
        fprintf(res, "Stack(OK) [%p]. \"%s\"\n", Stack, Stack->name);
        //fprintf(res, "The Name is \"%s\"\n", Stack->name);
        fprintf(res, "Hash        = %d\n", Stack->hash_stack);
        fprintf(res, "size        = %d\n", Stack->cur_size);
        fprintf(res, "capacity    = %d\n", Stack->capacity);

        int cap = Stack->capacity;
        int cur = Stack->cur_size;

        for(int i = 0; i < cap; i++)
        {
            if(i < cur) fprintf(res, "*[%d] data   = %.3lf\n", i, Stack->data[i]);
            else fprintf(res, "[%d]  data   = %.3lf\n", i, Stack->data[i]);

        }
    }


    fprintf(res, "%*s\n\n", 66, mass);
    fclose(res);
}

int stack_verify(stack_t* Stack)
{

    if(Stack == nullptr)
    {

        ERROR_STATE = NULL_STACK_PTR;
        return NULL_STACK_PTR;
    }

    else if(Stack->hash_stack != hash_stack(Stack))
    {
        ERROR_STATE = HACK_STACK;
        return HACK_STACK;
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

char* error_print()
{
    switch(ERROR_STATE)
    {
        case 1:
            return "NULL STACK PTR";
        case 2:
            return "NULL DATA PTR";
        case 3:
            return "CUR BIGGER THAN CAPACITY";
        case 4:
            return "CUR LESS THAN ZERO";
        case 5:
            return "CAPACITY LESS THAN ZERO";
        case 6:
            return "CAPACITY IS NOT A NORMAL NUMBER";
        case 7:
            return "CUR_SIZE IS NOT A NORMAL NUMBER";
        case 8:
            return "DOUBLE CONSTRUCT";
        case 9:
            return "ERROR_DATA_LEFT";
        case 10:
            return "ERROR_DATA_RIGHT";
        case 11:
            return "ERROR_STACK_LEFT";
        case 12:
            return "ERROR_STACK_RIGHT";
        case 13:
            return "Somebody is trying to hack a stack";
        default:
            return "ERROR IN error_print();\n";

    }
}

void add_memory(stack_t* Stack)
{
    ASSERT_OK

    if(Stack->capacity == 0)
    {
        Stack->capacity = REAL_ADDER;
        Stack->data     = (double*) realloc(Stack->data - 1, (Stack->capacity + 2) * sizeof(double));

        for(int i = 0; i <= Stack->capacity; i++)
        {
            Stack->data[i] = POISON;
        }

        Stack->data++;
        Stack->data[Stack->capacity] = CANARY_RIGHT_DATA;
        hash_stack(Stack);
    }

    else if(Stack->capacity < REAL_ADDER)
    {
        return;
    }

    else if(Stack->cur_size == Stack->capacity)
    {
        Stack->capacity *= 2;

        Stack->data = (double*) realloc(Stack->data - 1, (Stack->capacity + 2) * sizeof(double));

        for(int i = Stack->capacity / 2 + 1; i <= Stack->capacity; i++)
            Stack->data[i] = POISON;

        Stack->data++;
        Stack->data[Stack->capacity] = CANARY_RIGHT_DATA;
        hash_stack(Stack);

    }

    else if(Stack->cur_size <= Stack->capacity / REAL_REDUCER + 1) //как только уменьшиться кол-во элементов в 4 раза(не включительно)
    {
        Stack->capacity /= 2;
        Stack->data = (double*) realloc(Stack->data - 1, (Stack->capacity + 2) * sizeof(double));

        Stack->data++;
        Stack->data[Stack->capacity] = CANARY_RIGHT_DATA;
        hash_stack(Stack);

    }

    ASSERT_OK
}

int hash_stack(stack_t* Stack)
{
    if(Stack == nullptr)
    {
        stack_dump(Stack);
        return 0;
    }

    if(Stack->cur_size == 0)
    {
        Stack->hash_stack = 0;
        return 0;
    }

    int Hash = 1;
    int N    = Stack->cur_size;
    double A = (sqrt(5) - 1) / 2;


    for(int i = 0; i < N; i++)
    {
        if(i > 0)
        {
            Hash += (int) (N * ((double)(A * ((int) (Stack->data[i]) | (int) (Stack->data[i - 1]))) - (int) (A * ((int) (Stack->data[i]) | (int) (Stack->data[i - 1]))))) + (int) (Stack->data[i]) ^ (int) (Stack->data[i - 1]) - (int) (Stack->data[i]) & (int) (Stack->data[i - 1]);
            Hash += Stack->capacity;
            Hash += (int) Stack->data >> i;
            Hash += (int) Stack->name >> i % 2;
        }

        else
        {
            Hash += (int) ( N * ((double) (A * Stack->data[i])  - (int) (A * Stack->data[i])));
            Hash += Stack->capacity;
            Hash += (int) Stack->data >> 2;
            Hash += (int) Stack->name >> Stack->cur_size % 3;
        }
    }

    Stack->hash_stack = Hash;
    return Hash;
}
