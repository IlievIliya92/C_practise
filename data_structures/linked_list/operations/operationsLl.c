/******************************** INCLUDE FILES *******************************/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/********************************** DEFINES ***********************************/
#define MIDDLE(x)   (x/2)
/********************************* TYPEDEFS ***********************************/
typedef enum
{
    EXE_NAME = 0,
    N,
    ARGUMENTS_N
} spArguments_t;

typedef struct Node {
    int32_t data;
    struct Node *next;
} Node, *NodePtr;

/******************************* LOCAL FUNCTIONS ******************************/
static
void usage(const char *bin)
{
    fprintf(stdout, "%s ./%s [N]\n", __func__, bin);
    exit(-1);
}

static
void printList(struct Node *node)
{
    while(node != NULL)
    {
        fprintf(stdout, "%s %d\n", __func__, node->data);
        node = node->next;
    }
}

/******************************* INSERTION FUNCTIONS ******************************/
static
void push(NodePtr *headRef, int32_t data)
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
void insertAfter(NodePtr prevNode, int data)
{
    if (NULL == prevNode) {
        fprintf(stderr, "%s Invalid previous node for data %d\n", __func__, data);
        return;
    }

    NodePtr newNode = NULL;

    newNode = (NodePtr)malloc(sizeof(Node));
    if(NULL == newNode)
    {
        fprintf(stderr, "%s Failed to allocate node for data %d\n", __func__, data);
    }
    newNode->data = data;
    newNode->next = prevNode->next;
    prevNode->next = newNode;

    return;
}

static
int getlength(NodePtr headRef)
{
    int len = -1;

    while (headRef != NULL)
    {
        headRef = headRef->next;
        len++;
    }

    fprintf(stdout, "%s List length: %d\n ", __func__, len);
    return len;
}

static
void insertNth(NodePtr *headRef, int data, int n)
{
    int cnt = -1;

    cnt = getlength(*headRef);
    if (n > cnt) {
        fprintf(stderr, "%s Insert operation after element %d not possible!\n", __func__, n);
        return;
    }
    NodePtr newNode = NULL;

    newNode = (NodePtr)malloc(sizeof(Node));
    if(NULL == newNode)
    {
        fprintf(stderr, "%s Failed to allocate node for data %d\n", __func__, data);
    }
    newNode->data = data;
    newNode->next = NULL;

    newNode = headRef;
    cnt = 0;
    while(cnt != n) {
        newNode = newNode->next;
        cnt++;
    }

    return;
}

static
void append(NodePtr *headRef, int data)
{
    NodePtr newNode = NULL;
    NodePtr lastNode = NULL;

    newNode = (NodePtr)malloc(sizeof(Node));
    if(NULL == newNode)
    {
        fprintf(stderr, "%s Failed to allocate node for data %d\n", __func__, data);
    }
    newNode->data  = data;
    newNode->next = NULL;

    if (*headRef == NULL)
    {
       *headRef = newNode;
       return;
    }

    lastNode = *headRef;
    while(lastNode->next != NULL) {
        lastNode = lastNode->next;
    }
    lastNode->next = newNode;

    return;
}

/********************************* MAIN ***********************************/
int main(int argc, char *argv[])
{
    NodePtr head = NULL;

    int32_t i = 0;
    uint32_t elements = 0;

    if (ARGUMENTS_N != argc) {
        usage(argv[0]);
     }

    elements = atoi(argv[N]);
    if (elements < 0) {
        usage(argv[0]);
    }

    for (i = 0; i < elements; i++)
        push(&head, i);

    for (i = 0; i < elements; i++)
        append(&head, i);

    insertAfter(head->next, i);
    insertNth(&head, 77, MIDDLE(elements));

    printList(head);

    return 0;
}
