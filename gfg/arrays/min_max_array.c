/*
    Given an array A of size N of integers. Your task is to find the minimum and maximum elements in the array.

    Input:
    The first line of input contains an integer T denoting the number of test cases.
    T testcases follow. Each testcase contains 2 lines of input.
    The first line of each testcase contains the size of array N.
    The following line contains elements of the array separated by spaces.

    Output:
    For each testcase, print the minimum and maximum element of the array.

    Constraints:
    1 <= T <= 100
    1 <= N <= 1000
    1 <= Ai <=1012

    Example:
    Input:
    2
    6
    3 2 1 56 10000 167
    5
    1 345 234 21 56789
    Output:
    1 10000
    1 56789
*/

/* Includes */
#include <stdio.h>
#include <stdlib.h>

/* Typedefs */
typedef struct _data {
    /* in */
    int t;
    int *arr;
    int n;
    /* out */
    int min;
    int max;
} data_t, *data_tPtr;

/* Local functions */
void arraySearchMinMax(data_tPtr data) {
    int i = 0;

    if (1 == data->n) {
        data->min = data->arr[0];
        data->max = data->arr[0];
        return;
    }

    if (data->arr[0] > data->arr[1]) {
        data->max = data->arr[0];
        data->min = data->arr[1];
    } else {
        data->max = data->arr[1];
        data->min = data->arr[0];
    }

    for (i = 2; i < data->n; i++)
    {
        if (data->arr[i] > data->max) {
            data->max = data->arr[i];
        }

        if (data->arr[i] < data->min) {
            data->min = data->arr[i];
        }
    }

    return;
}


/* Main */
int main() {
    data_t data;
    int i = 0;

    scanf("%d", &data.t);
    if (data.t < 1 || data.t > 100) {
        fprintf(stderr, "[%s] Invalid T parameter!\n", __func__);
        return 0;
    }

    while (data.t) {
        scanf("%d", &data.n);
        if (data.n < 1 || data.n > 1000) {
            fprintf(stderr, "[%s] Invalid N parameter!\n", __func__);
            return 0;
        }

        data.arr = (int *)malloc(data.n * sizeof(int));
        if (data.arr == NULL) {
            fprintf(stderr, "[%s] Memory allocation failed!\n", __func__);
            return -1;
        }

        for (i = 0; i < data.n; i++) {
            scanf("%d", &data.arr[i]);
            if (data.arr[i] < 1 || data.arr[i] > 0x7FFFFFFF) {
                fprintf(stderr, "[%s] Invalid Array parameter! (%d) \n", __func__, data.arr[i]);
                return 0;
            }
        }

        arraySearchMinMax(&data);

        printf("%d %d", data.min, data.max);

        free(data.arr);

        data.t--;
    }

    return 0;
}