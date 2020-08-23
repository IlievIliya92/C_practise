/*
PUSH
1. If TOP = SIZE – 1, then:
(a) Display “The stack is in overflow condition”
(b) Exit

2. TOP = TOP + 1
3. STACK [TOP] = ITEM
4. Exit

POP
1. If TOP < 0, then
(a) Display “The Stack is empty”
(b) Exit

2. Else remove the Top most element
3. DATA = STACK[TOP]
4. TOP = TOP – 1
5. Exit

*/

/******************************** INCLUDE FILES *******************************/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/********************************** DEFINES ***********************************/
#define STACK_SIZE      100
#define STACK_EMPTY     (-1)

/********************************* TYPEDEFS ***********************************/
typedef struct stack_t {
    int storage[STACK_SIZE];
    int top;
} _stack_t, *_stack_tPtr;

/******************************* LOCAL FUNCTIONS ******************************/
static void stack_init(_stack_tPtr stack)
{
    stack->top = STACK_EMPTY;
    memset(stack->storage, 0x0, STACK_SIZE);

    return;
}

static bool stack_push(_stack_tPtr stack, int data)
{
    bool ret = false;

    if (stack->top == STACK_SIZE - 1)
    {
        fprintf(stderr, "[%s] The stack is in overflow condition! \n", __func__);
        ret = false;
    }
    else
    {
        /* Insert new data in the stack */
        stack->storage[++stack->top] = data;
        ret = true;
    }

    return ret;
}

static bool stack_pop(_stack_tPtr stack, int *data)
{
    bool ret = false;

    if (stack->top == STACK_EMPTY)
    {
        fprintf(stderr, "[%s] The Stack is empty! \n", __func__);
        ret = false;
    }
    else
    {
        /* Get the the data from the stack */
        *data = stack->storage[stack->top--];
        ret = true;
    }

    return ret;
}


static bool stack_traverse(_stack_tPtr stack)
{
    bool ret = false;

    if (stack->top == STACK_EMPTY)
    {
        fprintf(stderr, "[%s] The Stack is empty! \n", __func__);
        ret = false;
    }
    else
    {
        /* traverse the stack */
        for (int i = stack->top; i > 0; i--)
            fprintf(stdout, "[%s] idx: %d val: %d\n", __func__, i, stack->storage[i]);

        ret = true;
    }

    return ret;
}


/********************************* MAIN ***********************************/
int main(int argc, char *argv[])
{
    _stack_t stack;
    int dataOut = 0;
    int i = 0;

    stack_init(&stack);

    for (i = 0; i < STACK_SIZE; i++)
        stack_push(&stack, i);

    stack_traverse(&stack);

    for (i = 0; i < STACK_SIZE; i++)
    {
        stack_pop(&stack, &dataOut);
        fprintf(stdout, "[%s] %d\n", __func__, dataOut);
    }

    return 0;
}
