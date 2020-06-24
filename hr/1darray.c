#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_DIGITS        1000
#define MAX_SIZE          1000 * 7

typedef enum inputStatus
{
    OK = 0,
    NO_INPUT,
    TOO_LONG
} inputStatus_t;

typedef struct intInput
{
    int n;
    int *array;
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

    return OK;
}

static
int processInput(char *buff, intInput_t *data)
{
    int i = 0;
    char *token = NULL;
    const char delim[2] = " ";

    /* get the first token */
    token = strtok(buff, delim);
    data->array[0] = atoi(token);
    data->result += data->array[0];

    if (token != NULL)
    for(i = 1; i < data->n; i++)
    {
        token = strtok(NULL, delim);
        if (token != NULL) {
            data->array[i] = atoi(token);
            data->result += data->array[i];
        }
    }

    return 0;
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

    intData.n = atoi(buff[0]);
    intData.array = (int *)malloc(intData.n * sizeof(int));
    if (intData.array == NULL)
        return -1;

    rc = getInput(buff[1], sizeof(buff[1]));
    if (rc != OK)
        return -1;

    processInput(buff[1], &intData);
    printf("%d\n", intData.result);

    free(intData.array);

    return 0;
}
