/*
    Given an array A of size N, print second largest element from an array.

    Input:
    The first line of input contains an integer T denoting the number of test cases. T testcases follow. Each testcase contains two lines of input. The first line contains an integer N denoting the size of the array. The second line contains the N space seperated intgers of the array

    Output:
    For each testcase, in a new line, print the second largest element.

    Constraints:
    1 ≤ T ≤ 50
    1 ≤ N ≤ 500
    1 ≤ Ai ≤ 1200

    Example:
    Input
    2
    5
    89 24 75 11 23
    6
    56 42 21 23 65 20
    Output
    75
    56
*/

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // For INT_MIN

/* Typedefs */
typedef struct _data {
    /* in */
    int t;
    int *arr;
    int n;
    /* out */
    int max1;
    int max2;
} data_t, *data_tPtr;

/* Local functions */
void arraySearchSecondLargest(data_tPtr data) {
    int i = 0;

    data->max1 = INT_MIN;
    data->max2 = INT_MIN;

    for (i = 0; i < data->n; i++) {
        if (data->arr[i] > data->max1) {
            data->max2 = data->max1;
            data->max1 = data->arr[i];
        } else if (data->arr[i] > data->max2 && data->arr[i] < data->max1) {
            data->max2 = data->arr[i];
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

        arraySearchSecondLargest(&data);

        printf("%d", data.max2);

        free(data.arr);

        data.t--;
    }

    return 0;
}