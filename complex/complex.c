#include <stdio.h>

#include "complex.h"

int main(void) {
	complex z;

	EULER(z, 1.0, M_PI / 6.0);
	
	printf("(%lf, %lf)\n", Re(z), Im(z));
	printf("(%lf, %lf)\n", LEN(z), ARG(z));

	return 0;
}
