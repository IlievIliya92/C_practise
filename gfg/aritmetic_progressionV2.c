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
    INVALID
} inputStatus_t;

typedef enum input
{
    A = 0,
    B,
    TERMS
} input_t;

typedef struct data
{
    int t;
    int terms[TERMS];
    int n;
} data_t;

static
inputStatus_t getInput(data_t *data)
{
    scanf("%d %d", &data->terms[A], &data->terms[B]);
    if (data->terms[A] > VALUE_LIMIT_UPPER || data->terms[A] < VALUE_LIMIT_LOWER)
        return INVALID;
    if (data->terms[B] > VALUE_LIMIT_UPPER || data->terms[B] < VALUE_LIMIT_LOWER)
        return INVALID;

    scanf("%d", &data->n);
    if (data->n > N_LIMIT_UPPER || data->n < N_LIMIT_LOWER)
        return INVALID;

    return OK;
}

static int processIn(data_t *data)
{
    return data->terms[A] + (data->n - 1) * (data->terms[B] - data->terms[A]);
}

int main (void)
{
    int i = 0;
    data_t data;
    int result = 0;

    scanf("%d", &data.t);
    while(data.t)
    {
        if(OK == getInput(&data))
        {
            result = processIn(&data);
            printf("%d \n", result);
        }

        data.t--;
    }

    return 0;
}
