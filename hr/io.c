#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_SIZE          (3 * 5 + 2)
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
    int b;
    int result[2];
} intInput_t;

typedef struct floatInput
{
    float a;
    float b;
    float result[2];
} floatInput_t;


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
void parseInt(char *buff, intInput_t *data)
{
    char *token = NULL;

    /* get the first token */
    token = strtok(buff, delim);
    data->a = atoi(token);

    if (token != NULL) {
        token = strtok(NULL, delim);
        data->b = atoi(token);
    }

    if (data->a > VALUE_LIMIT_UPPER || data->a < VALUE_LIMIT_LOWER)
        return;

    data->result[0] = data->a + data->b;
    data->result[1] = data->a - data->b;

    return;
}

static
void parseFloat(char *buff, floatInput_t *data)
{
    char *token = NULL;

    /* get the first token */
    token = strtok(buff, delim);
    data->a = atof(token);

    if (token != NULL) {
        token = strtok(NULL, delim);
        data->b = atof(token);
    }

    if (data->a > VALUE_LIMIT_UPPER || data->a < VALUE_LIMIT_LOWER)
        return;

    data->result[0] = data->a + data->b;
    data->result[1] = data->a - data->b;

    return;
}


// Test program for getLine().
int main (void)
{
    intInput_t intData;
    floatInput_t floatData;
    int i = 0;
    inputStatus_t rc;
    char buff[2][MAX_SIZE];

    for (i = 0; i < 2; i ++) {
        rc = getInput(buff[i], sizeof(buff[i]));
        if (rc == NO_INPUT) {
            // Extra NL since my system doesn't output that on EOF.
            return 1;
        }

        if (rc == TOO_LONG) {
            printf ("Input too long [%s]\n", buff[i]);
            return 1;
        }

    }

    parseInt(buff[0], &intData);
    printf("%d %d\n", intData.result[0], intData.result[1]);
    parseFloat(buff[1], &floatData);
    printf("%.1f %.1f\n", floatData.result[0], floatData.result[1]);

    return 0;
}