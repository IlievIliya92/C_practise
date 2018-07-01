#ifndef _VECTOR_OBJECT_
#define _VECTOR_OBJECT_

void *vector_create(int);
void vector_destroy(void *);
int vector_dim(void *);
int vector_get_component(void *, int, double *);
int vector_set_component(void *, int, double);
double vector_len(void *);
int vector_inner_product(void *, void *, double *);
int vector_add2(void *, void *); /* first += second */
int vector_sub2(void *, void *); /* first -= second */
int vector_add3(void *, void *, void *); /* first = second + thrid */
int vector_sub3(void *, void *, void *); /* first = second - third */
void vector_scale2(void *, double);
int vector_scale3(void *, void *, double);

#endif
