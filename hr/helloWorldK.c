#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main(void)
{
    int i;
    char c;
    char buff[40];

    for(i = 0; (c = getchar()) != '\n'; i++)
    {
        buff[i] = c;
    }
    buff[++i] = '\0';

    printf("%s\n", "Hello World");
    printf("%s\n", buff);

}