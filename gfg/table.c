/*
    Print the table of a given number N.

    Input:
    First line contains an integer, the number of test cases 'T'. T testcases follow. Each testcase cotains one line of input denoting N.

    Output:
    For each testcase, print the table of N upto 10.

    Constraints:
    1 <= T <= 100
    1 <= N <= 1000

    Example:
    Input:
    1
    9

    Output:
    9 18 27 36 45 54 63 72 81 90
*/

#include <stdio.h>

#define TABLE_MAX 11
#define TABLE_MIN 1

static void printTable(int n) {
    int i = 0;
    int j = 0;

    for (i = TABLE_MIN; i < TABLE_MAX; i++)
        printf("%d ", i * n);


}


int main() {

    int t = 0;

    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        printTable(n);
        printf("\n");
    }

    return 0;
}