#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_SIZE          (100)
#define MAX_IN            1000
#define MIN_IN            1
#define HIGHEST_GRADE     6
#define LOWEST_GRADE      1

typedef enum inputStatus
{
    OK = 0,
    NO_INPUT,
    TOO_LONG
} inputStatus_t;

typedef enum gender {
    b = 0,
    g
} gender_t;

typedef struct input
{
    int n;
    int *grades;
    int gender;
} input_t;



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
void processInput(input_t *data)
{
    int i = 0;
    int sum = 0;

    for (i = 0; i < data->n; i++) {
        if (data->gender == b)
        {
            if (i % 2 == 0) {
                sum += *data->grades;
            }
        }
        else if (data->gender == g)
        {
            if (i % 2 != 0) {
                sum += *data->grades;
            }
        }
        data->grades++;
    }

    printf("%d\n", sum);

    return;
}
int main (void)
{
    input_t inData;
    inputStatus_t rc;
    int ret = 0;
    int i = 0;
    char buff[MAX_SIZE];

    rc = getInput(buff, sizeof(buff));
    if (rc != OK) {
        ret = -1;
        goto exit1;
    }
    inData.n = atoi(buff);
    /* validate n*/
    if (inData.n < MIN_IN || inData.n > MAX_IN)
    {
        ret = -1;
        goto exit1;
    }


    inData.grades = (int *)malloc(sizeof(int) * inData.n);
    if (inData.grades == NULL)
    {
        ret = -1;
        goto exit0;
    }

    for (i = 0; i < inData.n; i++)
    {
        rc = getInput(buff, sizeof(buff));
        *inData.grades = atoi(buff);
        if (*inData.grades < LOWEST_GRADE ||
            *inData.grades > HIGHEST_GRADE)
        {
            ret = -1;
            goto exit0;
        }
        inData.grades++;
    }
    inData.grades -= inData.n;

    rc = getInput(buff, sizeof(buff));
    if (strcmp(buff, "b") == 0)
    {
        inData.gender = b;
    }
    else if (strcmp(buff, "g") == 0)
    {
        inData.gender = g;
    }

    processInput(&inData);
    inData.grades -= inData.n;

exit0:
    free(inData.grades);

exit1:

    return ret;
}
