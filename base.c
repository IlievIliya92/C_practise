#include <stdio.h>
#include <stdlib.h>

static const char digits[16] = {
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
};

int *convert_stack(int num, int base, int *len) {
	int n = 8, *stack = NULL, *tmp, p = 0;
	
	if ((base < 2) || (base > 16)) goto end;
	
	stack = (int *)malloc(n * sizeof (int));
	if (!stack) goto end;
	
	while (num) {
		if (p == n) {
			n *= 2;
			tmp = (int *)realloc(stack, n * sizeof (int));
			if (!tmp) {
				free(stack);
				stack = NULL;
				goto end;
			}
		}
		printf("%d / %d = %d + %d\n", num, base, num / base, num % base);
		stack[p++] = num % base;
		num /= base;
	}
	
	*len = p;
	
end:
	return stack;
}

int convert_decimal(int *conv, int len, int base) {
	int acc = 0, pwr = 1, j;
	
	for (j = 0; j < len; j++) {
		printf("%d*%d^%d%s", conv[j], base, j, (j == len - 1) ? "\n" : " + ");
		acc += conv[j] * pwr;
		pwr *= base;
	}
	
	return acc;
}

void convert(int num, int base) {
	int mod = num % base;
	
	if ((base < 2) || (base > 16)) return;
	if (!num) return;
	convert(num / base, base);
	printf("%c", digits[mod]);
	
	return;
}

int main(void) {
	int *conv, len, j;
	
	conv = convert_stack(1230, 8, &len);
	if (!conv) return 1;
	
	for (j = len - 1; j >= 0; j--)
		printf("%c", digits[conv[j]]);
	printf("\n");
	
	printf("%d\n", convert_decimal(conv, len, 8));
	
	free(conv);
	
	return 0;
}

