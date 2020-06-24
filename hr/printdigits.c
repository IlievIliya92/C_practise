#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define VALUE_LIMIT_UPPER 1000000
#define VALUE_LIMIT_LOWER 1

#define MAX_SIZE          (7 * 2 + 2)

typedef enum inputStatus
{
    OK = 0,
    NO_INPUT,
    TOO_LONG
} inputStatus_t;

typedef struct intInput
{
    int a;
    int b;
} intInput_t;


static const char delim[2] = " ";

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
int parseInt(char *buff, int *data)
{
    char *token = NULL;

    /* get the first token */
    token = strtok(buff, delim);
    if (token != NULL) {
        *data = atoi(token);
    }
    else
    {
        return -1;
    }

    return 0;
}

static
void processInput(int data)
{
    switch(data)
    {
        case 1:
            printf("one\n");
        break;

        case 2:
            printf("two\n");
        break;

        case 3:
            printf("three\n");
        break;

        case 4:
            printf("four\n");
        break;

        case 5:
            printf("five\n");
        break;

        case 6:
            printf("six\n");
        break;

        case 7:
            printf("seven\n");
        break;

        case 8:
            printf("eight\n");
        break;

        case 9:
            printf("nine\n");
        break;

        default:
            if (data > 9) {
                if (data % 2 == 0) {
                    printf("even\n");
                } else {
                    printf("odd\n");
                }

            }
        break;
    }

    return;
}

int main (void)
{
    intInput_t intData;
    inputStatus_t rc;
    char buff[2][MAX_SIZE];
    int i = 0;

    rc = getInput(buff[0], sizeof(buff[0]));
    if (rc != OK)
        return -1;

    if(parseInt(buff[0], &intData.a) != 0)
        return -1;

    rc = getInput(buff[1], sizeof(buff[1]));
    if (rc != OK)
        return -1;

    if(parseInt(buff[1], &intData.b) != 0)
        return -1;

    if (intData.a < intData.b)
        for (i = intData.a; i <= intData.b; i++)
            processInput(i);

    return 0;
}
