#include <stdio.h>
#include <stdlib.h>

static
void update(int *a,int *b) {
    int tmp = 0;

    tmp = *a;
    *a = *a + *b;
    *b = abs(tmp - *b);

    return;
}

int main() {
    int a, b;
    int *pa = &a, *pb = &b;

    scanf("%d %d", &a, &b);
    update(pa, pb);
    printf("%d %d\n", a, b);


    return 0;
}
