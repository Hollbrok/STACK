#define CHAR_T
#include "stack.h"
#undef CHAR_T

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

    Stack->data = (type_data*)calloc(max_c + 2, sizeof(type_data));

    if (Stack->data == nullptr)
    {
        stack_dump(Stack);
        return;
    }

    else
    {
        Stack->data[0] = (type_data) CANARY_LEFT_DATA;
        Stack->data[max_c + 1] = (type_data) CANARY_RIGHT_DATA;

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

    Stack->cur_size = POISON_SIZES;
    Stack->capacity = POISON_SIZES;
}

void push_stack(stack_t* Stack, type_data push_num)
{
    assert(push_num);
    //printf("ffff\n");
    ASSERT_OK

    if(push_num >= POISON)
    {
        //printf("ffff\n");
        stack_dump(Stack);

        return;
    }

    FILE* res = fopen("log_stack.txt", "ab");

    /*if(!isalpha(push_num))
        if(isnan(push_num))
        {
            fclose(res);
            stack_dump(Stack);
            return;
        }
      */
    if(isnan(push_num))
    {
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

type_data pop_stack(stack_t* Stack)
{
    if(ERROR_STATE)
        return POISON;

    if(stack_verify(Stack))
        return POISON;

    if(Stack->cur_size <= Stack->capacity / REAL_MULTIPLIER + 1)
    {
        add_memory(Stack);
        Stack->cur_size--;
        type_data temp = Stack->data[Stack->cur_size];
        Stack->data[Stack->cur_size] = POISON;
        hash_stack(Stack);
        return temp;
    }

    else if(Stack->cur_size > 0)
    {
        type_data temp = Stack->data[Stack->cur_size - 1];
        Stack->cur_size--;
        Stack->data[Stack->cur_size] = POISON;
        hash_stack(Stack);
        return temp;
    }

    return  POISON;
}

void stack_dump(stack_t* Stack)
{
    char mass[67] = "******************************************************************";

    FILE* res = fopen("log_stack.txt", "ab");
    printf("9\n");
    fprintf(res, "%*s\n", 66, mass);
    printf("10\n");
    //printf("7");
    if(ERROR_STATE)
    {
        //printf("9");
        fprintf(res, "Stack (ERROR #%d : %s) [%p]. \n", ERROR_STATE, error_print(), Stack, Stack->hash_stack);
        //printf("9");
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

        char* type_string = "";
        //printf("\n11\n");
        if(FORMAT == "lg")
        {
            type_string = "double";
            //printf("double");
        }
        else if(FORMAT == "d")
        {
            type_string = "int";
            //printf("int");
        }
        else if(FORMAT == "c")
        {
            type_string = "char";
            //printf("char");
        }
        else if(FORMAT == "s")
        {
            type_string = "string";
            //printf("string");
        }
        else
        {
            type_string = "ERROR";
            //printf("ERROR");
        }

        //printf("%s", type_string);
        fprintf(res, "Type of data is %s\n", type_string);
        fprintf(res, "Hash        = %d\n", Stack->hash_stack);
        fprintf(res, "size        = %d\n", Stack->cur_size);
        fprintf(res, "capacity    = %d\n", Stack->capacity);
        printf("\nStack_dump\n");
        int cap = Stack->capacity;
        int cur = Stack->cur_size;
        printf("capacity = ");
        printf("%d\n", Stack->capacity);
        printf("cur = ");
        printf("%d", Stack->cur_size);

        for(int i = 0; i < cap; i++)
        {
            printf("\ni = %d\n", i);
            if(i < cur)
            {
                printf("Stack ->data = ");
                printf("%c", Stack->data[i]);
                fprintf(res, "*[%d] data   = %" FORMAT "\n", i, Stack->data[i]);
                printf("AFTER 1printf = %d", i);
            }

            else
            {
                printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                printf(FORMAT);
                printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                printf("Stack ->data = ");
                printf("%c\n", Stack->data[i]);
                fprintf(res, "*[%d] data   = %" FORMAT " (POISON)\n", i, POISON);

                printf("GOOD");

            }
        }
        printf("AFTER PRINTF all stack");
    }


    fprintf(res, "%*s\n\n", 66, mass);
    fclose(res);
}

int stack_verify(stack_t* Stack)
{

    if(Stack == nullptr)
    {
    printf("2222\n");
        ERROR_STATE = NULL_STACK_PTR;
        //printf("1\n");
        return NULL_STACK_PTR;
    }

    else if(Stack->hash_stack != hash_stack(Stack))
    {
        printf("2222\n");
        ERROR_STATE = HACK_STACK;
        //printf("1\n");
        return HACK_STACK;
    }

    else if(Stack->data == nullptr)
    {
        printf("2222\n");
        ERROR_STATE = NULL_DATA_PTR;
        //printf("1\n");
        return NULL_DATA_PTR;
    }

    else if(Stack->cur_size > Stack->capacity)
    {
        ERROR_STATE = CUR_BIGGER_CAPACITY;
        //printf("1\n");
        return CUR_BIGGER_CAPACITY;
    }

    else if(Stack->cur_size < 0)
    {
        printf("2222\n");
        ERROR_STATE = CUR_LESS_ZERO;
        //printf("1\n");
        return CUR_LESS_ZERO;

    }

    else if(isdigit(Stack->capacity))
        {
            if(!isnan(Stack->capacity))
            {
                printf("2222\n");
                ERROR_STATE = CLASSIFY_CAPACITY;
                //printf("1\n");
                return CLASSIFY_CAPACITY;
            }
        }
    else if(Stack->capacity < 0)
    {
        printf("2222\n");
        ERROR_STATE = CAPACITY_LESS_ZERO;
        //printf("1\n");
        return CAPACITY_LESS_ZERO;
    }


    else if(isdigit(Stack->cur_size))
        {
            if(isnan(Stack->cur_size) && Stack->cur_size > 0)
            {
                printf("2222\n");
                ERROR_STATE = CLASSIFY_CUR;
                //printf("1\n");
                return CLASSIFY_CUR;
            }
        }
    else if(Stack->data[-1] != CANARY_LEFT_DATA)
    {
        printf("2222\n");
        ERROR_STATE = ERROR_DATA_LEFT;
        //printf("1\n");
        return ERROR_DATA_LEFT;

    }

    else if(Stack->data[Stack->capacity] != (type_data) CANARY_RIGHT_DATA)
    {
        printf("2222\n");
        ERROR_STATE = ERROR_DATA_RIGHT;
        //printf("1\n");
        return ERROR_DATA_RIGHT;
    }

    else if(Stack->canary_left_stack != (type_data) CANARY_LEFT_STACK)
    {
        //printf("2222\n");
        ERROR_STATE = ERROR_STACK_LEFT;
        //printf("1\n");
        return ERROR_STACK_LEFT;
    }

    else if(Stack->canary_right_stack != CANARY_RIGHT_STACK)
    {
        ERROR_STATE = ERROR_STACK_RIGHT;
        //printf("1\n");
        return ERROR_STACK_RIGHT;
    }

    else
    {
        printf("1\n");
        return 0;
    }

    //printf("3\n");
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
        Stack->data     = (type_data*) realloc(Stack->data - 1, (Stack->capacity + 2) * sizeof(type_data));

        for(int i = 0; i <= Stack->capacity; i++)
        {
            Stack->data[i] = POISON;
        }

        Stack->data++;
        Stack->data[Stack->capacity] = (type_data) CANARY_RIGHT_DATA;
        hash_stack(Stack);
    }

    else if(Stack->cur_size == Stack->capacity)
    {
        Stack->capacity *= 2;

        Stack->data = (type_data*) realloc(Stack->data - 1, (Stack->capacity + 2) * sizeof(type_data));

        for(int i = Stack->capacity / 2 + 1; i <= Stack->capacity; i++)
            Stack->data[i] = POISON;

        Stack->data++;
        Stack->data[Stack->capacity] = (type_data) CANARY_RIGHT_DATA;
        hash_stack(Stack);

    }

    else if(Stack->cur_size <= REAL_ADDER)
    {
        return;
    }



    else if(Stack->cur_size <= Stack->capacity / REAL_REDUCER + 1) //как только уменьшиться кол-во элементов в 4 раза(не включительно)
    {
        Stack->capacity /= 2;
        Stack->data = (type_data*) realloc(Stack->data - 1, (Stack->capacity + 2) * sizeof(type_data));

        Stack->data++;
        Stack->data[Stack->capacity] = (type_data) CANARY_RIGHT_DATA;
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


    double trash = 0;

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
            Hash += (int) ( N *  modf(A * (int) Stack->data[i], &trash) );
            Hash += Stack->capacity;
            Hash += (int) Stack->data >> 2;
            Hash += (int) Stack->name >> Stack->cur_size % 3;
        }
    }

    Stack->hash_stack = Hash;
    return Hash;
}
