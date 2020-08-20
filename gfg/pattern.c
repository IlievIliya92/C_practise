/*
    You a given a number N. You need to print the pattern for the given value of N.
    for N=2 the pattern will be
    2 2 1 1
    2 1
    for N=3 the pattern will be
    3 3 3 2 2 2 1 1 1
    3 3 2 2 1 1
    3 2 1

    Input Format:
    The first line of input is the number of testcases T. The T test cases follow. The first line of each test case is an integer N.

    Output Format:
    For each test case, in a new line, print the required pattern in a singleline .
    Note : Instead of printing new line print a "$" without quotes.

    Your Task:
    Since this is a function problem, you don't need to worry about the testcases. Your task is to complete the function printPat which takes one argument 'N' denoting the length of the pattern.

    Constraints:
    1 <= T <= 20
    1 <= N <= 40

    Example:
    Input
    2
    2
    3
    Output
    2 2 1 1 $2 1 $
    3 3 3 2 2 2 1 1 1 $3 3 2 2 1 1 $3 2 1 $
*/

#include<stdio.h>

void printPat(int n);

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        printPat(n);
        printf("\n");
    }

    return 0;
}


/*You are required to complete this method*/
void printPat(int n)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int m = n;
    int t = n;

    for (i = 0; i < n; i++) {
        m = n;
        k = 0;
        while (k < n) {
            for (j = 0; j < t; j++) {
                printf("%d ", m);
            }
            m--;
            k++;
        }
        t--;
        printf("$");
    }

    return;
}
