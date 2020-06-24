#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_DIGITS        1000
#define MAX_SIZE          1000 * 7

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

typedef struct intInput
{
    int n;
    int *array;
} intInput_t;

typedef struct Node
{
    int data;
    struct Node *next;
} Node, *NodePtr;


static
void listPush(NodePtr *headRef, int data)
{
    NodePtr newNode = NULL;

    newNode = (NodePtr)malloc(sizeof(Node));
    if(NULL == newNode)
    {
        fprintf(stderr, "%s Failed to allocate node for data %d\n", __func__, data);
    }

    newNode->data = data;
    newNode->next = (*headRef);
    (*headRef) = newNode;

    return;
}


static
void listPrint(struct Node *node)
{
    while(node != NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
}

static
void listFree(struct Node *node)
{
    NodePtr tmp;

    while(node != NULL)
    {
        tmp = node;
        node = node->next;
        free(tmp);
    }
}


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
int processInput(char *buff, intInput_t *data)
{
    NodePtr head = NULL;
    int i = 0;
    char *token = NULL;
    const char delim[2] = " ";

    /* get the first token */
    token = strtok(buff, delim);
    data->array[0] = atoi(token);

    if (token != NULL)
    for(i = 1; i < data->n; i++)
    {
        token = strtok(NULL, delim);
        if (token != NULL) {
            data->array[i] = atoi(token);
        }
    }

    for(i = 0; i < data->n; i ++)
        listPush(&head, data->array[i]);

    listPrint(head);

    return 0;
}

int main (void)
{
    intInput_t intData;
    inputStatus_t rc;
    char buff[TOTAL_ARGS][MAX_SIZE];

    rc = getInput(buff[N], sizeof(buff[N]));
    if (rc != OK)
        return -1;

    intData.n = atoi(buff[N]);
    intData.array = (int *)malloc(intData.n * sizeof(int));
    if (intData.array == NULL)
        return -1;

    rc = getInput(buff[DATA], sizeof(buff[DATA]));
    if (rc != OK)
        return -1;

    processInput(buff[DATA], &intData);

    free(intData.array);

    return 0;
}
