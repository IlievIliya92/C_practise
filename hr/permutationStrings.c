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

static unsigned char outBuff[9][MAX_STR_SIZE];

static
unsigned long hashCalc(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c;

    return hash;
}

static
void permutation (char **arr, int n, int x)
{
    int i = 0;
    int j = 0;

    static int idx = 0;

    if(x == n - 1)
    {
        for (i = 0; i < n; i++) {
            strcat(outBuff[idx], arr[i]);
            strcat(outBuff[idx], " ");
        }
        idx++;
    }

    for (j = x; j < n; j++)
    {
        swap(arr[j], arr[x]);
        permutation (arr, n , x + 1);
        swap(arr[j], arr[x]);
    }
}



static
int processInput(char **array, int n)
{
    int i = 0;
    int j = 0;
    unsigned long hash[n];

    memset(outBuff, 0x0, (MAX_STR_SIZE + 2*9) * 9);

    permutation(array, n, 0);

    for(i = 0; i < n; i++)
    {
        hash[i] = hashCalc(outBuff[i]);
        printf("%s > %lu\n", outBuff[i], hash[i]);
    }

    return 0;
}

int main()
{
    int i = 0;
    int ret = 0;

    inputStatus_t rc;
    char inNstr[2];
    int  n = 0;
    char **array;

    rc = getInput(inNstr, sizeof(inNstr));
    if (rc != OK) {
        ret = -1;
        goto exit1;
    }
    n = atoi(inNstr);
    /* validate n*/
    if (n < MIN_IN || n > MAX_IN) {
        ret = -1;
        goto exit1;
    }

    array = (char **)malloc(sizeof(char *));
    if (array == NULL)
    {
        ret = -1;
        goto exit1;
    }

    for (i = 0; i < n; i++) {
        array[i] = (char *)malloc(MAX_STR_SIZE);
        if (array[i] == NULL) {
            ret = -1;
            goto exit0;
        }

        rc = getInput(array[i], sizeof(array[i]));
        if (rc != OK) {
            ret = -1;
            goto exit0;
        }
    }

    processInput(array, n);

exit0:
    for(i = 0; i < n; i++) {
        free(array[i]);
    }

exit1:

    return ret;
}

#define main my_main
static int next_permutation(int n, char **s)
{
    return 0;
};

int main()
{
    char **s;
    int n;
    scanf("%d", &n);
    s = calloc(n, sizeof(char*));
    for (int i = 0; i < n; i++)
    {
        s[i] = calloc(11, sizeof(char));
        scanf("%s", s[i]);
    }
    do
    {
        for (int i = 0; i < n; i++)
            printf("%s%c", s[i], i == n - 1 ? '\n' : ' ');
    } while (next_permutation(n, s));
    for (int i = 0; i < n; i++)
        free(s[i]);
    free(s);
    return 0;
}