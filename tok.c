#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char digit[16] = {
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
};

int main(void) {
	char *s = "123a456b789c012d345";
	char *sep = "abcd";
	char *dup, *p;
	char *state = NULL;
	
	dup = strdup(s);
	if (!dup) return 1;
	
	printf("%s %s\n", dup, sep);
	
	printf("status initialis dup = %p, state = %p\n", dup, state);
	p = strtok_r(dup, sep, &state);
	printf("status post strtok_r state = %p\n", state);
	
	for (; p; p = strtok_r(NULL, sep, &state)) {
		printf("%p %s\n", state, p);
	}
	
	free(dup);
	
	return 0;
}

