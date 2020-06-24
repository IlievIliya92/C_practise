#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_SIZE          1000

typedef enum inputStatus
{
    OK = 0,
    NO_INPUT,
    TOO_LONG
} inputStatus_t;

static
inputStatus_t getInput(char *buff, size_t sz)
{
    int ch, extra;

    // Get line with buffer overrun protection.
    if (fgets (buff, sz, stdin) == NULL)
        return NO_INPUT;

    if (buff[strlen(buff)-1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }
    buff[strlen(buff)-1] = '\0';

    return OK;
}

static
int processInput(char *buff)
{
    char *token = NULL;
    const char delim[2] = " ";

    /* get the first token */
    token = strtok(buff, delim);
    printf("%s\n", token);

    while(token != NULL)
    {
        token = strtok(NULL, delim);
        if (token != NULL) {
            printf("%s\n", token);
        }
    }

    return 0;
}

int main (void)
{
    inputStatus_t rc;
    char buff[MAX_SIZE];

    rc = getInput(buff, sizeof(buff));
    if (rc != OK)
        return -1;

    processInput(buff);

    return 0;
}
