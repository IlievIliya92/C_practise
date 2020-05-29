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
int growArray_init(grow_array_t *arr, int initial_size, int size_increment)
{
    arr->head = (void *)malloc(initial_size * sizeof(void *));
    if (arr->head == NULL)
        return -1;

    arr->used = 0;
    arr->free = initial_size;
    arr->current = initial_size;
    arr->size_increment = size_increment;

    return 0;
}

int growArray_insert(grow_array_t *arr, void *new_element)
{

    void *new_head;

    if (arr->free == 0) {
        new_head = realloc(arr->head, (arr->current + arr->size_increment) * sizeof(void*));
        if (new_head == NULL) {
            return -1;
        }

        arr->free = arr->size_increment;
        arr->current += arr->size_increment;
        arr->head = new_head;
    }
    arr->head[arr->used++] = new_element;
    arr->free--;

    return 0;
}

void *growArray_get(grow_array_t arr, int index)
{
    return arr.head[index];
}


void growArray_free(grow_array_t arr)
{
    free(arr.head);
    arr.head = NULL;

    return;
}

int growArray_getUsed(grow_array_t a)
{
    return a.used;
}

