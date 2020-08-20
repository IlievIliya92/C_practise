/*
    Given the first 2 terms A and B of a Geometric Series. The task is to find the Nth term of the series.

    Input:
    First line contains an integer, the number of test cases 'T'. T testcases follow. Each test case in its first line contains two integer A and B (First 2 terms of GP). In the second line of every test case it contains of an integer N.

    Output:
    In each seperate line print the Nth term of the Geometric Progression. Print the floor ( floor(2.3)=2 ) of the answer. Both the terms A and B forms a valid GP.

    Constraints:
    1 <= T <= 30
    -100 <= A <= 100
    -100 <= B <= 100
    1 <= N <= 5

    Example:
    Input:
    2
    2 3
    1
    1 2
    2

    Output:
    2
    2

    Explanation:
    Testcase 2: The second term of series whose common ratio is 2 will be 2.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define VALUE_LIMIT_UPPER     100
#define VALUE_LIMIT_LOWER     (-100)

#define N_LIMIT_UPPER         5
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
    //an = a1*r^(n-1)
    //r = a2/a1
    //an = a1* ((a2/a1)^(n-1))
    return data->terms[A] * pow(data->terms[B]/data->terms[A], data->n - 1);
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
