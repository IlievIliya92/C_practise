/*
    Given the first 2 terms A and B of an Arithmetic Series, tell the Nth term of the series.

    Input:
    The first line of input contains an integer, the number of test cases T. T testcases follow. Each testcase in its first line should contain two positive integer A and B(First 2 terms of AP). In the second line of every testcase it contains of an integer N.

    Output:
    For each testcase, in a new line, print the Nth term of the Arithmetic Progression.

    Constraints:
    1 <= T <= 100
    -103 <= A <= 103
    -103 <= B <= 103
    1 <= N <= 104

    Example:
    Input:
    2
    2 3
    4
    1 2
    10

    Output:
    5
    10
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE              1000

#define VALUE_LIMIT_UPPER     1000
#define VALUE_LIMIT_LOWER     (-1000)

#define N_LIMIT_UPPER         10000
#define N_LIMIT_LOWER         1


typedef enum inputStatus
{
    OK = 0,
    NO_INPUT,
    TOO_LONG
} inputStatus_t;

typedef enum input
{
    A = 0,
    B,
    TERMS,
    T,
    N
} input_t;

typedef struct data
{
    int t;
    int terms[TERMS];
    int n;
} data_t;


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
    buff[strlen(buff) - 1] = '\0';

    return OK;
}

static
int parseIn(char *buff, data_t *data, input_t inType)
{
    const char delim[2] = " ";
    char *token = NULL;
    int i = 0;

    switch(inType)
    {
        case TERMS:
            /* get the first token */
            token = strtok(buff, delim);
            if (token != NULL) {
                data->terms[A] = atoi(token);
                if (data->terms[A] > VALUE_LIMIT_UPPER || data->terms[A] < VALUE_LIMIT_LOWER)
                    return -1;
            }
            else
            {
                return -1;
            }

            token = strtok(NULL, delim);
            if (token != NULL) {
                data->terms[B] = atoi(token);
                if (data->terms[B] > VALUE_LIMIT_UPPER || data->terms[B] < VALUE_LIMIT_LOWER)
                       return -1;
            }
            else
            {
                return -1;
            }
            break;

        case N:
            token = strtok(buff, delim);
            if (token != NULL) {
                data->n = atoi(token);
                if (data->n > N_LIMIT_UPPER || data->n < N_LIMIT_LOWER)
                    return -1;
            }
            else {
                return -1;
            }
            break;

        case T:
            token = strtok(buff, delim);
            if (token != NULL) {
                data->t = atoi(token);
            }
            else {
                return -1;
            }
            break;

        default:
            break;
    }

    return 0;
}

static int processIn(data_t *data)
{
    return data->terms[A] + (data->n - 1) * (data->terms[B] - data->terms[A]);
}

int main (void)
{
    int i = 0;
    data_t data;
    inputStatus_t rc = NO_INPUT;
    char buff[MAX_SIZE];
    int result = 0;

    memset(buff, 0x00, MAX_SIZE);

    rc = getInput(buff, sizeof(buff));
    if (rc == OK) {
        if(parseIn(buff, &data, T) != 0) {
            fprintf(stderr, "Failed to parse T argument!\n");
            return -1;
        }
    }

    for (i = 0; i < data.t; i++)
    {
        rc = getInput(buff, sizeof(buff));
        if (rc == OK) {
            if(parseIn(buff, &data, TERMS) != 0) {
                fprintf(stderr, "Failed to parse TERMS argument!\n");
                return -1;
            }
        }

        rc = getInput(buff, sizeof(buff));
        if (rc == OK) {
            if(parseIn(buff, &data, N) != 0) {
                fprintf(stderr, "Failed to parse N argument!\n");
                return -1;
            }
        }

        result = processIn(&data);
        printf("%d \n", result);
    }

    return 0;
}
