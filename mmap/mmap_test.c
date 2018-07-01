#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main(void) {
	int fd, r = 0;
	off_t size;
	size_t j;
	void *map;
	char *cmap;
	pid_t pid;
	
	fd = open("mmap_test", O_RDWR);
	if (fd < 0) {
		perror("open");
		r = -1;
		goto bad0;
	}
	
	size = lseek(fd, 0, SEEK_END);
	if (size < 0) {
		perror("lseek");
		r = -1;
		goto bad1;
	}
	
	map = mmap(NULL, (size_t)size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (map == MAP_FAILED) {
		perror("mmap");
		r = -1;
		goto bad1;
	}
	
	if (mprotect(map, (size_t)size, PROT_READ | PROT_WRITE) < 0) {
		perror("mprotect");
	}
	
	cmap = (char *)map;
	
	pid = fork();
	if (!pid) { /* child */
		for (j = 0; j < (size_t)size; j++) {
			cmap[j] = (j & 1) ? 'D' : 'C';
			sleep(1);
		}
	} if (pid > 0) {
		while (1) {
			for (j = 0; j < (size_t)size; j++)
				fputc(cmap[j], stdout);
			fputc('\n', stdout);
			sleep(1);
		}
	} else {
		perror("fork");
		r = -1;
	}
	
	if (munmap(map, (size_t)size) < 0) {
		perror("munmap");
		r = -1;
	}
	
bad1:
	close(fd);
bad0:
	return r;
}

