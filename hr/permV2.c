#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_IN            9
#define MIN_IN            2
#define MAX_STR_SIZE      10

typedef enum inputStatus
{
    OK = 0,
    NO_INPUT,
    TOO_LONG
} inputStatus_t;

typedef enum inputArgs
{
    N = 0,
    DATA,
    TOTAL_ARGS
} inputArgs_t;

typedef struct data
{
    char inBuff[2];
    int  n;
    char **array;
} data_t;


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
void swap (char *x, char*y)
{
    char t[MAX_STR_SIZE];

    strcpy(t, x);
    strcpy(x, y);
    strcpy(y, t);

    return;
}

static
unsigned long hashCalc(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c;

    return hash;
}

int permutation(char **s, int n){
    int i = n-1;
    while(i>0 && strcmp(s[i-1],s[i])>=0)
        i--;
    if (i<=0)
        return 0;

    int j = n-1;
    while(strcmp(s[i-1],s[j])>=0)
        j--;

    char *tmp = s[i-1];
    s[i-1] = s[j];
    s[j] = tmp;

    j = n-1;
    while(i<j)
    {
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
        i++;
        j--;
    }

    return 1;
}



static
int processInput(data_t *data)
{
    int i = 0;

    do
    {
        for (int i = 0; i < data->n; i++)
            printf("%s%c", data->array[i], i == data->n - 1 ? '\n' : ' ');
    } while (permutation(data->array, data->n));

    return 0;
}

int main()
{
    int i = 0;
    int ret = 0;
    data_t inData;
    inputStatus_t rc;

    rc = getInput(inData.inBuff, sizeof(inData.inBuff));
    if (rc != OK) {
        ret = -1;
        goto exit1;
    }
    inData.n = atoi(inData.inBuff);

    /* validate n*/
    if (inData.n < MIN_IN || inData.n > MAX_IN) {
        ret = -1;
        goto exit1;
    }

    inData.array = (char **)malloc(sizeof(char *) * inData.n);
    if (inData.array == NULL)
    {
        ret = -1;
        goto exit1;
    }

    for (i = 0; i < inData.n; i++) {
        inData.array[i] = (char *)malloc(MAX_STR_SIZE);
        if (inData.array[i] == NULL) {
            ret = -1;
            goto exit0;
        }

        rc = getInput(inData.array[i], sizeof(inData.array[i]));
        if (rc != OK) {
            ret = -1;
            goto exit0;
        }
    }

    processInput(&inData);

exit0:
    for(i = 0; i < inData.n; i++) {
        free(inData.array[i]);
    }

    free(inData.array);

exit1:

    return ret;
}

#define main my_main
static int next_permutation(int n, char **s)
{
    return 0;
};
