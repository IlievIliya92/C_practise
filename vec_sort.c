#include <stdio.h>
#include <stdlib.h>

#include "vector_object.h"

int compare(const void *_t0, const void *_t1) {
	const void **t0 = (const void **)_t0;
	const void **t1 = (const void **)_t1;
	
	if (vector_len(*t0) > vector_len(*t1)) return 1;
	else if (vector_len(*t0) < vector_len(*t1)) return -1;
	else return 0;
}

int main(void) {
	void *t[20];
	int i, j;
	
	for (i = 0; i < 20; i++) {
		t[i] = vector_create(3);
		for (j = 0; j < 3; j++)
			(void)vector_set_component(t[i], j, (double)rand());
		printf("ante\t%d\t%lf\n", i, vector_len(t[i]));
	}
	
	qsort((void *)t, 20, sizeof (void *), &compare);
	
	for (i = 0; i < 20; i++) {
		printf("post\t%d\t%lf\n", i, vector_len(t[i]));
		vector_destroy(t[i]);
	}

	return 0;
}

