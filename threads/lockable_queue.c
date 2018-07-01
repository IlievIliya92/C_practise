#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>

#include "queue_object.h"

#define SEM_VAL 2

struct lockable_queue {
	sem_t term;
	void *queue;
};
typedef struct lockable_queue lockable_queue;

void *consumer_thread(void *arg) {
	lockable_queue *queue = (lockable_queue *)arg;
	queue_datum d;
	int val;
	
	while (1) {
		if (queue_get(queue->queue, &d)) {
			if (d.type == INTEGER) printf("CONSUMER INTEGER %d\n", d.d.i);
			else if (d.type == POINTER) printf("CONSUMER POINTER %p\n", d.d.v);
		} else {
			sem_getvalue(&queue->term, &val);
			if (val == SEM_VAL) {
				printf("CONSUMER TERMINATING %d\n", errno);
				break;
			}
		}
	}
	return NULL;
}

void *producer0_thread(void *arg) {
	lockable_queue *queue = (lockable_queue *)arg;
	queue_datum d;
	
	d.type = INTEGER;
	for (d.d.i = 0; d.d.i < 1000; d.d.i++) {
		printf("PRODUCER %d\n", d.d.i);
		queue_put(queue->queue, d);
	}
	
	sem_post(&queue->term);
	
	return NULL;
}

void *producer1_thread(void *arg) {
	lockable_queue *queue = (lockable_queue *)arg;
	queue_datum d;
	int j;
	
	d.type = POINTER;
	d.d.v = arg;
	for (j = 0; j < 1000; j++) {
		printf("PRODUCER %d %p\n", j, d.d.v);
		queue_put(queue->queue, d);
	}
	
	sem_post(&queue->term);
	
	return NULL;
}

int main(void) {
	pthread_t producer0, producer1, consumer;
	lockable_queue queue;
		
	sem_init(&queue.term, 0, SEM_VAL);
	sem_wait(&queue.term);
	sem_wait(&queue.term);
	
	queue.queue = queue_create();
	
	pthread_create(&consumer, NULL, &consumer_thread, &queue);
	pthread_create(&producer0, NULL, &producer0_thread, &queue);
	pthread_create(&producer1, NULL, &producer1_thread, &queue);
		
	pthread_join(producer0, NULL);
	pthread_join(producer1, NULL);
	pthread_join(consumer, NULL);
	
	queue_destroy(queue.queue);
	
	sem_destroy(&queue.term);
	
	return 0;
}

