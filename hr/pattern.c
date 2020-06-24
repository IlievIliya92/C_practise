#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_DIGITS        4
#define MAX_SIZE          (MAX_DIGITS + 2)
#define VALUE_LIMIT_UPPER 1000
#define VALUE_LIMIT_LOWER 1

typedef enum inputStatus
{
    OK = 0,
    NO_INPUT,
    TOO_LONG
} inputStatus_t;

typedef struct intInput
{
    int number;
} intInput_t;


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
void parseInt(char *buff, intInput_t *data)
{
    char *token = NULL;
    const char delim[2] = " ";

    /* get the first token */
    token = strtok(buff, delim);
    data->number = atoi(token);

    if (data->number > VALUE_LIMIT_UPPER || data->number < VALUE_LIMIT_LOWER)
        return;

    return;
}


static
void processData(intInput_t *data, int *outBuff)
{
    int i = 0;
    int j = 0;
    int min = 0;
    int len = data->number * 2 - 1;

    for(i = 0; i < len; i++) {
        for(j = 0; j < len; j++) {
            min = i < j ? i : j;
            min = min < len - i ? min : len - i - 1;
            min = min < len - j - 1 ? min : len - j - 1;
            *outBuff = data->number - min;
            outBuff++;
            //printf("%d ", data->number - min);
        }
        //*outBuff = '\n';
        //printf("\n");
    }

    return;
}

int main (void)
{
    intInput_t intData;
    inputStatus_t rc;
    char buff[MAX_SIZE];
    int outBuffLen = 0;
    int *outBuff = NULL;
    int i = 0;

    rc = getInput(buff, sizeof(buff));
    if (rc != OK)
        return -1;

    parseInt(buff, &intData);

    outBuffLen = intData.number * 2 - 1 ;
    outBuffLen *= outBuffLen;
    outBuff = (int *)malloc(sizeof(int) * outBuffLen);
    if (outBuff == NULL)
        return -1;

    memset(outBuff, 0x00, outBuffLen);
    processData(&intData, outBuff);

    printf("len %d\n", outBuffLen);

    for(i = 0; i < outBuffLen; i++) {
        printf("%d", outBuff[i]);

        if (i % 3 == 0)
            printf("\n");
    }

    free(outBuff);

    return 0;
}

