#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_STR_SIZE      2500
#define MAX_IN            50
#define MIN_IN            1

typedef enum inputStatus
{
    OK = 0,
    NO_INPUT,
    TOO_LONG
} inputStatus_t;

typedef struct input
{
    int n;
    char **arr;
} input_t;

typedef enum sortFuncs
{
    LEX = 0,
    LEX_REV,
    DIFFS,
    LEN,
    SORT_METHODS
} sortFuncs_t;

typedef enum direction
{
    FORWARD = 0,
    REVERSE
} direction_t;

typedef void (*sortFuncCall)(input_t *);
typedef char bool_t;

bool_t TRUE = 1;
bool_t FALSE = 0;

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
void swapStrings(char *a, char *b, direction_t direction)
{
    char temp [MAX_STR_SIZE];

    if (FORWARD == direction)
    {
        strcpy(temp, a);
        strcpy(a, b);
        strcpy(b, temp);
    }
    else if (REVERSE == direction)
    {
        strcpy(temp, b);
        strcpy(b, a);
        strcpy(a, temp);
    }

    return;
}

static
void lexicographic_sort(input_t *data, direction_t direction)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < data->n; ++i) {
        for (j = i + 1; j < data->n; ++j) {
            if (FORWARD == direction)
            {
                if (strcmp(data->arr[i], data->arr[j]) > 0)
                {
                    swapStrings(data->arr[i], data->arr[j], FORWARD);
                }
            }
            else if (REVERSE == direction)
            {
                if (strcmp(data->arr[i], data->arr[j]) < 0)
                {
                    swapStrings(data->arr[i], data->arr[j], REVERSE);
                }
            }

        }
    }

    return;
}

static
void lexicographic_sort_forward(input_t *data)
{
    lexicographic_sort(data, FORWARD);

    return;
}

static
void lexicographic_sort_reverse(input_t *data)
{
    lexicographic_sort(data, REVERSE);

    return;
}

#define CHARS 26
static
int CountUniqueCharacters(char  *str)
{
    int dist = 0;
    int chars[CHARS] = {0};

    while (*str != '\0') {
        int chr = (*str++) - 'a';
        if (chr < CHARS)
            chars[chr]++;
    }

    for (int i = 0; i < CHARS; i++)
        if (chars[i])
            dist++;

    return dist;


}

static
void sort_by_number_of_distinct_characters(input_t *data)
{
    int i = 0;
    int j = 0;
    int auc = 0;
    int buc = 0;

    for (i = 0; i < data->n; ++i) {
        for (j = i + 1; j < data->n; ++j) {
            auc = CountUniqueCharacters(data->arr[i]);
            buc = CountUniqueCharacters(data->arr[j]);
            if (auc > buc)
            {
                swapStrings(data->arr[i], data->arr[j], FORWARD);
            }
            else  if (auc == buc)
            {
                if (strcmp(data->arr[i], data->arr[j]) > 0)
                    swapStrings(data->arr[i], data->arr[j], REVERSE);
            }
        }
    }

    return;
}

static
void sort_by_length(input_t *data)
{
    char temp[MAX_STR_SIZE];

    for (int i=1 ;i<data->n; i++)
    {
        strcpy(temp, data->arr[i]);

        int j = i - 1;
        while (j >= 0 && strlen(temp) < strlen(data->arr[j]))
        {
            strcpy(data->arr[j+1], data->arr[j]);
            j--;
        }
        strcpy(data->arr[j+1], temp);
    }
    return;
}

static
void processInput(input_t *data)
{
    int i = 0;
    int j = 0;

    sortFuncCall sortFunc[SORT_METHODS] = {&lexicographic_sort_forward,
                                           &lexicographic_sort_reverse,
                                           &sort_by_number_of_distinct_characters,
                                           &sort_by_length};
    printf("\n");

    for (i = 0; i < SORT_METHODS; i++) {
        sortFunc[i](data);
        for (j = 0; j < data->n; j++) {
            printf("%s\n", data->arr[j]);
        }
        printf("\n");
    }

    return;
}

int main (void)
{
    input_t inData;
    inputStatus_t rc;
    int ret = 0;
    int i = 0;
    char buff[MAX_STR_SIZE];

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

    inData.arr = (char **)malloc(sizeof(char *) * inData.n);
    if (inData.arr == NULL)
    {
        ret = -1;
        goto exit0;
    }

    for (i = 0; i < inData.n; i++)
    {
        inData.arr[i] = (char *)malloc(sizeof(char) * MAX_STR_SIZE);
        if (inData.arr[i] == NULL)
        {
            ret = -1;
            goto exit0;
        }

        rc = getInput(inData.arr[i], MAX_STR_SIZE);
    }
    processInput(&inData);


exit0:
    for (i = 0; i < inData.n; i++)
        if (inData.arr[i] != NULL)
            free(inData.arr[i]);

    free(inData.arr);
exit1:

    return ret;
}
