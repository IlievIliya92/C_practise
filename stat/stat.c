#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	struct stat s;
	
	if (stat(argv[0], &s) < 0) {
		perror("stat");
		exit(-1);
	}
	
	printf("%d\n", time(NULL));
	printf("%ld %d %d %d\n", s.st_size, s.st_uid, s.st_gid, s.st_mtime);
	
	return 0;
}

