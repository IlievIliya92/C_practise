#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

const int num_thr = 20;
const int num_cycles = 10;
int done = 0;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *thr(void *_id) {
	long id = (long)_id;
	int j;
	
	for (j = 0; j < num_cycles; j++) {
		printf("id = %ld, cycle = %d of %d\n", id, j, num_cycles);
		sleep(1);
	}
	
	pthread_mutex_lock(&mtx);
	done++;
	printf("id = %ld done\n", id);
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mtx);
	
	return NULL;
}

int main(void) {
	pthread_t threads[num_thr];
	int j;
	
	for (j = 0; j < num_thr; j++)
		pthread_create(&threads[j], NULL, &thr, (void *)((long)j));
	
	pthread_mutex_lock(&mtx);
	
	while (done < num_thr) {
		printf("%d threads done\n", done);
		pthread_cond_wait(&cond, &mtx);
		printf("got wakeup\n");
	}
	
	printf("before return: %d threads done\n", done);
	
	pthread_mutex_unlock(&mtx);
	
	return 0;
}

