/*
The maximum sum subarray problem consists in finding the maximum sum of a contiguous subsequence in an array or list of integers:

maxSequence({-2, 1, -3, 4, -1, 2, 1, -5, 4}, 9)
// should return 6, from sub-array: {4, -1, 2, 1}

Easy case is when the list is made up of only positive numbers and the maximum sum is the sum of the whole array. If the list is made up of only negative numbers, return 0 instead.

Empty list is considered to have zero greatest sum. Note that the empty list or array is also a valid sublist/subarray.
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>




int maxSequence(const int* array, size_t n) {
    int max_so_far = 0;
    int max_ending_here = 0;
    int i = 0;

    for (i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    for (i = 0; i < n; i++)
    {
        max_ending_here = max_ending_here + array[i];
        if (max_so_far < max_ending_here)
            max_so_far = max_ending_here;

        if (max_ending_here < 0)
            max_ending_here = 0;

        printf("%d max_ending_here %d max_so_far %d\n", i, max_ending_here, max_so_far);
    }

    return max_so_far;
}

int main (void)
{
    int res = 0;

    const int arr[] = {-2, 1, -3, 4, -1, 2, 1, -5, 9};

    res = maxSequence(arr, 9);

    printf("%d\n", res);


    return 0;
}





