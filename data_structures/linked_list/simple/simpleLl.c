/******************************** INCLUDE FILES *******************************/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/********************************** DEFINES ***********************************/

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
    fprintf(stdout, "%s ./%s  [N]\n", __func__, bin);
    exit(-1);
}


/********************************* MAIN ***********************************/
int main(int argc, char *argv[])
{
    int32_t i = 0;
    uint32_t elements = 0;

    if (ARGUMENTS_N != argc) {
        usage(argv[0]);
     }

    elements = atoi(argv[N]);
    if (elements < 0) {
        usage(argv[0]);
    }

    Node node[elements];

    /* Link the nodes & place some data*/
    for (i = 0; i < elements; i++) {
        node[i].data = i;
        node[i].next = &node[i + 1];
    }

    for (i = 0; i < elements; i++) {
        fprintf(stdout, "%d\n", node[i].data);
    }

    return 0;
}
