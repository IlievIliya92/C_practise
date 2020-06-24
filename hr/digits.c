#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_SIZE          (1000000 + 2)
#define VALUE_LIMIT_UPPER 10000
#define VALUE_LIMIT_LOWER 1

typedef enum inputStatus
{
    OK = 0,
    NO_INPUT,
    TOO_LONG
} inputStatus_t;

typedef struct intInput
{
    int a;
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
int parseInt(char *buff, intInput_t *data)
{
    char *token = NULL;

    /* get the first token */
    token = strtok(buff, delim);
    if (token != NULL) {
        data->a = atoi(token);
        return 0;
    }

    return -1;
}

static
void processInput(intInput_t *data)
{
    switch(data->a)
    {
        case 1:
            fprintf(stdout, "one\n");
        break;

        case 2:
            fprintf(stdout, "two\n");
        break;

        case 3:
            fprintf(stdout, "three\n");
        break;

        case 4:
            fprintf(stdout, "four\n");
        break;

        case 5:
            fprintf(stdout, "five\n");
        break;

        case 6:
            fprintf(stdout, "six\n");
        break;

        case 7:
            fprintf(stdout, "seven\n");
        break;

        case 8:
            fprintf(stdout, "eight\n");
        break;

        case 9:
            fprintf(stdout, "nine\n");
        break;

        default:
            if (data->a > 9)
                fprintf(stdout, "Greater than 9\n");
        break;
    }

    return;
}

int main (void)
{
    intInput_t intData;
    inputStatus_t rc;
    char buff[MAX_SIZE];

    rc = getInput(buff, sizeof(buff));
    if (rc == OK) {
        if(parseInt(buff, &intData) == 0)
            processInput(&intData);
    }
    else
    {
        return -1;
    }

    return 0;
}
