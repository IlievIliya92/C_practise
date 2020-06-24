#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_SIZE          100000
#define MIN_SIDE_SIZE     1
#define MAX_SIDE_SIZE     70

typedef enum inputStatus
{
    OK = 0,
    NO_INPUT,
    TOO_LONG
} inputStatus_t;

typedef enum sides
{
    A = 0,
    B,
    C,
    SIDES
} sides_t;


typedef struct triangData
{
    int side[3];
    int S;
} triangData_t;

static const char delim[2] = " ";

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
int parseInt(char *buff, sides_t *data)
{
    char *token = NULL;
    int i = 0;

    /* get the first token */
    token = strtok(buff, delim);
    data->side[A] = atoi(token);

    for(i = A; i < SIDES; i++)
    {
        if (token != NULL) {
            token = strtok(NULL, delim);
            data->side[i] = atoi(token);
        }
    }
    else
    {
        return -1;
    }

    return 0;
}

int main() {
    triangData_t data;
    inputStatus_t rc;

    char buff[MAX_SIZE];


    rc = getInput(buff, sizeof(buff));
    if (rc == OK)
    {
        if (parseInt(buff, &inData) < 0)
        {
            fprintf(stderr, "[%s] Failed to parse the input data!\n", __func__);
            return -1;
        }
        update(pa, pb);
        fprintf(stdout, "%d %d\n", *pa, *pb);
    }
    else
    {
        fprintf(stderr, "[%s] Failed to obtain input!  %s\n", __func__, (rc == TOO_LONG) ? "Input too long": "Wrong input");
        return -1;
    }
    return 0;
}