#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE          1000

typedef enum inputStatus
{
    OK = 0,
    NO_INPUT,
    TOO_LONG
} inputStatus_t;

typedef enum digit
{
    ZERO = 0,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    DIGITS,
    INVALID
} digit_t;


typedef struct Node
{
    int data;
    struct Node *next;
} Node, *NodePtr;

static
inputStatus_t getInput(char *buff, size_t sz)
{
    int ch, extra;

    // Get line with buffer overrun protection.
    if (fgets (buff, sz, stdin) == NULL)
        return NO_INPUT;

    if (buff[strlen(buff)-1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }
    buff[strlen(buff)-1] = '\0';

    return OK;
}

static
digit_t translateToDigit(int data)
{
    digit_t ret = INVALID;

    switch (data)
    {
        case ZERO:
            ret = ZERO;
            break;
        case ONE:
            ret = ONE;
            break;
        case TWO:
            ret = TWO;
            break;
        case THREE:
            ret = THREE;
            break;
        case FOUR:
            ret = FOUR;
            break;
        case FIVE:
            ret = FIVE;
            break;
        case SIX:
            ret = SIX;
            break;
        case SEVEN:
            ret = SEVEN;
            break;
        case EIGHT:
            ret = EIGHT;
            break;
        case NINE:
            ret = NINE;
            break;
        default:
            ret = INVALID;
            break;
    }

    return ret;
}

static
int processInput(char *buff)
{
    int occurances[DIGITS] = {0};
    int data;
    int i = 0;
    digit_t d = INVALID;

    while(*buff != '\0')
    {
        if (isdigit(*buff)) {
            data = *buff - '0';
            d = translateToDigit(data);
            if (d != INVALID)
                occurances[d]++;
        }

        buff++;
    }

    for (i = 0; i < DIGITS; i++)
        printf("%d ", occurances[i]);

    return 0;
}

int main (void)
{
    inputStatus_t rc;
    char buff[MAX_SIZE];

    rc = getInput(buff, sizeof(buff));
    if (rc != OK)
        return -1;

    processInput(buff);


    return 0;
}
