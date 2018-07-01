#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void vararg(int num, ...) {
	va_list var;
	int j;
	
	va_start(var, num);
	for (j = 0; j < num; j++)
		printf("%d%c", va_arg(var, int),
				(j == (num - 1)) ? '\n' : ' ');
	va_end(var);
	
	return;
}

int main(void) {
	vararg(5, 1, 2, 3, 4, 5);
	vararg(3, 6, 7, 8);
	return 0;
}
