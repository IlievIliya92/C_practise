#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
/*
	write a function void tokenise(char *string, char *sep, char **tokens);
	which splits string based on separator sep, filling the char * array tokens
	with the tokens found, the rest set to NULL. tokens may hold up to strlen(string) char pointers.
	e.g.
		if string points to a writable "abcdefgcdefgcde" and sep points to "cde"
		the resulting char **tokens array should be like
			tokens[0] -> "ab"
			tokens[1] -> "fg"
			tokens[2] -> "fg"
			tokens[3] -> ""
			tokens[4] ... -> NULL
		the initial string should bebecome this in memory, together with the tokens pointers:
			tokens[0]          tokens[1]          tokens[2]         tokens[4]
			   |                  |                  |                 |
			   v                  v                  v                 v
			{ 'a', 'b', 0, 0, 0, 'f', 'g', 0, 0, 0, 'f', 'g', 0, 0, 0, 0 }
*/
	char *s1 = "abcdefgcdefgcde";
	char *s2 = "cde";
	char *dest, *p, *pnext;
	int j;
	
	dest = strdup(s1);
	if (!dest) return 1;
	
	pnext = dest;
	printf("initial %p; strlen is %d\n", pnext, strlen(pnext));
	for (p = strstr(pnext, s2); p; p = strstr(pnext, s2)) {
		printf("found at %p; strlen is %d; ", p, strlen(p));
		for (j = 0; j < strlen(s2); j++)
			p[j] = (char)toupper((int)p[j]);
		pnext = p + strlen(s2);
		printf("pnext is now %p\n", pnext);

	}
	
	printf("%s\n", dest);
	
	free(dest);
	
	return 0;
}
