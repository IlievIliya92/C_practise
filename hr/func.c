#include <stdio.h>


/*
Add `int max_of_four(int a, int b, int c, int d)` here.
*/

static
int max_of_four(int a, int b, int c, int d)
{
    int max1 = 0;
    int max2 = 0;

    max1 = (a < b) ? b : a;
    max2 =(c < d) ? d : c;

    return (max1 < max2) ? max2 : max1;
}


int main() {
    int a, b, c, d;
    int ans = 0;

    scanf("%d %d %d %d", &a, &b, &c, &d);

    ans = max_of_four(a, b, c, d);
    printf("%d\n", ans);

    return 0;
}