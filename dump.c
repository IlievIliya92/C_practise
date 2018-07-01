#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <string.h>

static const char digits[16] = {
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
};

void dump(FILE *stream, void *_obj, size_t n_bytes) {
	uint8_t *obj = (uint8_t *)_obj;
	size_t i;
	
	for (i = 0; i < n_bytes; i++) {
		fprintf(stream, "%c", digits[obj[i] >> 4]);
		fprintf(stream, "%c", digits[obj[i] & 0x0fu]);
		if ((i & 0x0fu) == 0x0fu) fprintf(stream, "\n");
		else fprintf(stream, " ");
	}
	
	fprintf(stream, "\n");
	
	return;
}

void *get_dereference(void *mem, size_t size, size_t el) {
	uint8_t *m = (uint8_t *)mem;
	
	return (void *)(m + size * el);
}

void set_dereference(void *mem, size_t size, size_t el, void *val) {
	uint8_t *m = ((uint8_t *)mem) + size * el;
	
	(void)memcpy((void *)m, val, size);
	return;
}

#ifdef MAIN1
int main(void) {
#pragma pack(1)
	struct test {
		uint32_t a;
		void *p;
	} t;
#pragma pack()
	
	t.a = 0xdeadbeefu;
	t.p = (void *)&t;
	
	printf("%p\t%p\t%p\n", &t, &t.a, &t.p);
	
	dump(stdout, &t, sizeof (struct test));
	
	return 0;
}
#else
int main(void) {
	int a[10];
	int i;
	
	for (i = 0; i < 10; i++)
		set_dereference(&a, sizeof (int), i, &i);
	
	for (i = 0; i < 10; i++)
		printf("%d\n", *((int *)(get_dereference(&a, sizeof (int), i))));
	return 0;
}
#endif
