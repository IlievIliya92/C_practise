#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
	size_t len = strlen(argv[0]);
	char *c;
	
	if (!(c = (char *)malloc(len + 3))) return -1;
	
	strcpy(c, argv[0]);
	strcat(c, ".l");
	
/*
	if (link(argv[0], c) < 0) {
		perror("link");
	}
*/
/*
	if (symlink(argv[0], c) < 0) {
		perror("link");
	}
*/
	printf("Hello world!\n");
	
	free(c);
	
	return 0;
}

