/*
    Given an array A of size N, print the reverse of it.

    Input:
    First line contains an integer denoting the test cases 'T'. T testcases follow. Each testcase contains two lines of input. First line contains N the size of the array A. The second line contains the elements of the array.

    Output:
    For each testcase, in a new line, print the array in reverse order.

    Constraints:
    1 <= T <= 100
    1 <= N <=100
    0 <= Ai <= 100

    Example:
    Input:
    1
    4
    1 2 3 4
    Output:
    4 3 2 1
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
} data_t, *data_tPtr;

/* Local functions */
static void arrayReverse(data_tPtr data) {
    int i = 0;
    int arrEnd = data->n - 1;
    int arrStart = 0;

    while(arrStart < arrEnd)
    {
        data->arr[arrStart] ^= data->arr[arrEnd];
        data->arr[arrEnd] ^= data->arr[arrStart];
        data->arr[arrStart] ^= data->arr[arrEnd];

        arrEnd--;
        arrStart++;
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

        arrayReverse(&data);

        for (i = 0; i < data.n; i++)
            printf("%d ", data.arr[i]);

        free(data.arr);

        data.t--;
    }

    return 0;
}