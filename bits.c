#include <sys/types.h>
#include <stdio.h>
#include <string.h>

void setbit(uint32_t *i, int n, int val) {
	uint32_t mask = 1u << n;
	
	if (val) *i |= mask;
	else *i &= ~mask;
	
	return;
}

int getbit(uint32_t i, int n) {
	uint32_t mask = 1u << n;
	
	return !!(i & mask);
}

uint32_t getbits(uint32_t i, int from, int to) {
	return (i >> from) & ((1u << (to - from + 1u)) - 1u);
}

void setbool(uint32_t *i, int n, int val) {
	int idx = n / 32;
	uint32_t mask = 1u << (n % 32);
	
	if (val) i[idx] |= mask;
	else i[idx] &= ~mask;
	
	return;
}

int getbool(uint32_t *i, int n) {
	int idx = n / 32;
	uint32_t mask = 1u << (n % 32);
	
	return !!(i[idx] & mask);
}

#define GETBOOL(TYPE, I, N) (!!((I)[(N) / (sizeof (TYPE) * 8)] & (1u << ((N) % (sizeof (TYPE) * 8)))))

#define SETBOOL(TYPE, I, N, VAL) do { \
	if (VAL) (I)[(N) / (sizeof (TYPE) * 8)] |= 1u << ((N) % (sizeof (TYPE) * 8)); \
	else (I)[(N) / (sizeof (TYPE) * 8)] &= ~((N) % (sizeof (TYPE) * 8)); \
} while (0)

int main(void) {
/*
	uint32_t boolean[4];
	int j, k;

	(void)memset(boolean, 0, sizeof (boolean));
	
	for (j = 0; j < 128; j++)
		setbool(boolean, j, 1);
	
	for (j = 2; j < 128; j++)
		if (getbool(boolean, j))
			for (k = 2 * j; k < 128; k += j)
				setbool(boolean, k, 0);
	
	for (j = 0; j < 128; j++) {
		k = GETBOOL(uint32_t, boolean, j);
		printf("%d\t%d\t%d\n", j, getbool(boolean, j), k);
	}
*/
/*
	int32_t i, k;
	int j;
	
	for (i = -127; i <= 0; i++) {
		printf("%d\t", i);
		for (j = 31; j >= 0; j--)
			printf("%d", getbool((uint32_t *)&i, j));
		k = i >> 4;
		printf("\t%d\t", k);
		for (j = 31; j >= 0; j--)
			printf("%d", getbool((uint32_t *)&k, j));
		printf("\n");
	}
*/
	
	printf("%x\n", getbits(0xf00f1000u, 12, 19));
	return 0;
}

