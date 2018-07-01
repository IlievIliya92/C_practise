#include <stdio.h>
#include <stdlib.h>

struct example {
	int key;
	void *value;
};
typedef struct example example;

int compare(const void *_t0, const void *_t1) {
	const example *t0 = (const example *)_t0;
	const example *t1 = (const example *)_t1;
	
	printf("compare callback t0->key == %d, t1->key == %d\n", t0->key, t1->key);
	
	if (t0->key > t1->key) return 1;
	else if (t0->key < t1->key) return -1;
	else return 0;
}

int main(void) {
	example t[20];
	int j;
	
	for (j = 0; j < 20; j++) {
		t[j].key = rand();
		(*(t + j)).value = NULL;
		printf("ante\t%d\t%d\n", j, t[j].key);
	}
	
	qsort((void *)t, 20, sizeof (example), &compare);
	
	for (j = 0; j < 20; j++)
		printf("post\t%d\t%d\n", j, t[j].key);
	
	return 0;
}
