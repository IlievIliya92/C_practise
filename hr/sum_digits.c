#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_DIGITS        5
#define MAX_SIZE          (MAX_DIGITS + 2)
#define VALUE_LIMIT_UPPER 99999


typedef enum inputStatus
{
    OK = 0,
    NO_INPUT,
    TOO_LONG
} inputStatus_t;

typedef struct intInput
{
    int number;
    int result;
} intInput_t;


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

    if (strlen(buff) != MAX_DIGITS)
        return NO_INPUT;

    return OK;
}

static
int processInput(char *buff, intInput_t *data)
{
    int i = 0;

    data->number = atoi(buff);
    data->result = 0;

    for(i = 0; i < MAX_DIGITS; i ++) {
        data->result += data->number % 10;
        data->number /= 10;
        printf("%d %d\n",data->number, data->result);
    }

    return 0;
}


int main (void)
{
    intInput_t intData;
    inputStatus_t rc;
    char buff[MAX_SIZE];
    int i = 0;

    rc = getInput(buff, sizeof(buff));
    if (rc != OK)
        return -1;

    processInput(buff, &intData);
    printf("%d\n", intData.result);

    return 0;
}
