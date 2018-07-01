#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>

struct comm_channel {
	sem_t lock;
	sem_t exit_lock;
	int val, data_good;
};

static void *map;
static struct comm_channel *c;

void parent(void) {
	int exit_status;
	
	while (!sem_wait(&c->lock)) {
		if (c->data_good) {
			printf("%d\n", c->val);
			c->data_good = 0;
		}
		if (!sem_trywait(&c->exit_lock)) {
			(void)wait(&exit_status);
			printf("child exited, status %d\n", exit_status);
			break;
		}
		sem_post(&c->lock);
	}
	return;
}

void child(void) {
	int j;
	
	for (j = 0; j < 50;) {
		if (!sem_wait(&c->lock)) {
			if (!c->data_good) {
				c->val = j;
				c->data_good = 1;
				j++;
			}
			sem_post(&c->lock);
		}
	}
	
	sem_post(&c->exit_lock);
	
	return;
}

int main(void) {
	int zerofd;
	pid_t p;
	
	if ((zerofd = open("/dev/zero", O_RDWR)) < 0) {
		perror("open");
		exit(errno);
	}
	map = mmap(
			NULL,
			sizeof (struct comm_channel),
			PROT_READ | PROT_WRITE,
			MAP_SHARED,
			zerofd, 0
	);
	if (map == MAP_FAILED) {
		perror("mmap");
		close(zerofd);
		exit(errno);
	}
	close(zerofd);
	
	c = (struct comm_channel *)map;
	sem_init(&c->lock, 1, 1);
	sem_init(&c->exit_lock, 1, 1);
	sem_wait(&c->exit_lock);
	c->data_good = 0;
	
	if ((p = fork()) < 0) {
		perror("fork");
		exit(errno);
	} else if (p) {
		parent();
	} else {
		child();
	}
	
	munmap(map, sizeof (struct comm_channel));
	
	return 0;
}

