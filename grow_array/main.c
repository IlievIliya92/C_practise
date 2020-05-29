/******************************** INCLUDE FILES *******************************/
#include "grow_array.h"

#include <stdio.h>
#include <string.h>
#include <malloc.h>

/******************************** LOCAL DEFINES *******************************/

/********************************* LOCAL DATA *********************************/


/******************************* INTERFACE DATA *******************************/


/******************************* LOCAL FUNCTIONS ******************************/


/***************************** INTERFACE FUNCTIONS ****************************/

void test_putSomeDataIn(void *arg)
{
    for (int i = 0; i < 2; i ++) {
        growArray_insert(arg, (void *)"this is a test1");
        growArray_insert(arg, (void *)"this is a test2");
        growArray_insert(arg, (void *)"this is a test3");
        growArray_insert(arg, (void *)"this is a test4");
    }

    return;
}

int main(int argc, char* argv[]) {
    grow_array_t array;

    growArray_init(&array, 5, 1);

    test_putSomeDataIn(&array);

    for (int i = 0; i < growArray_getUsed(array); i++)
        printf("%s\n", (char *)growArray_get(array, i));

    printf("USED %d\n", growArray_getUsed(array));

    growArray_free(array);

    return 0;
}
