#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_DIGITS        5
#define MAX_SIZE          (MAX_DIGITS*2 + 2)
#define VALUE_LIMIT_UPPER 10000
#define VALUE_LIMIT_LOWER 2

typedef enum inputStatus
{
    OK = 0,
    NO_INPUT,
    TOO_LONG
} inputStatus_t;

typedef struct intInput
{
    int n;
    int k;
    int maxAnd;
    int maxOr;
    int maxXor;
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
void parseInt(char *buff, intInput_t *data)
{
    char *token = NULL;
    const char delim[2] = " ";

    /* get the first token */
    token = strtok(buff, delim);
    data->n = atoi(token);

    if (token != NULL) {
        token = strtok(NULL, delim);
        data->k = atoi(token);
    }

    if (data->n > VALUE_LIMIT_UPPER || data->n < VALUE_LIMIT_LOWER)
        return;

    if (data->k > data->n || data->k < VALUE_LIMIT_LOWER)
        return;

    return;
}

static
void processData(intInput_t *data)
{
    data->maxAnd = 0;
    data->maxOr  = 0;
    data->maxXor = 0;

    for (int i=1; i<=data->n; i++) {
        for (int j=i+1; j<=data->n; j++) {
            if (((i&j) > data->maxAnd) && ((i&j) < data->k)) {
                data->maxAnd = i&j;
            }
            if (((i|j) > data->maxOr) && ((i|j) < data->k)) {
                data->maxOr = i|j;
            }
            if (((i^j) > data->maxXor) && ((i^j) < data->k)) {
                data->maxXor = i^j;
            }
        }
    }

    return;
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

    parseInt(buff, &intData);
    processData(&intData);

    printf("%d\n%d\n%d\n", intData.maxAnd, intData.maxOr , intData.maxXor);

    return 0;
}
