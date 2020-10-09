/** @addtogroup xxx_group
 * @{
 */

#ifndef GROW_ARRAY_H_
#define GROW_ARRAY_H_

/******************************** INCLUDE FILES *******************************/
#include <stdio.h>

/*********************************** DEFINES **********************************/


/************************** INTERFACE DATA DEFINITIONS ************************/
typedef struct {
    void **head;
    size_t used;
    size_t free;
    size_t current;
    size_t size_increment;
} grow_array_t;

/************************* INTERFACE FUNCTION PROTOTYPES **********************/
int growArray_init(grow_array_t *arr, int initial_size, int size_increment);
int growArray_insert(grow_array_t *arr, void *new_element);
void growArray_free(grow_array_t arr);
void *growArray_get(grow_array_t arr, int index);
int growArray_getUsed(grow_array_t a);

#endif /* GROW_ARRAY_H_ */

