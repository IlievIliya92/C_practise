#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>

#include "queue_object.h"

#define SEM_VAL 2

struct lockable_queue {
	sem_t mtx, term;
	pthread_barrier_t bar;
	void *queue;
};
typedef struct lockable_queue lockable_queue;

void *consumer0_thread(void *arg) {
	lockable_queue *queue = (lockable_queue *)arg;
	queue_datum d;
	int val;
	
	while (1) {
		sem_wait(&queue->mtx);
		if (queue_get(queue->queue, &d)) {
			if (d.type == INTEGER) printf("CONSUMER0 INTEGER %d\n", d.d.i);
			else if (d.type == POINTER) printf("CONSUMER0 POINTER %p\n", d.d.v);
		} else {
			sem_getvalue(&queue->term, &val);
			if (val == SEM_VAL) {
				sem_post(&queue->mtx);
				break;
			}
		}
		sem_post(&queue->mtx);
	}
	
	printf("CONSUMER0 TERMINATING\n");
	
	return NULL;
}

void *consumer1_thread(void *arg) {
	lockable_queue *queue = (lockable_queue *)arg;
	queue_datum d;
	int val;
	
	while (1) {
		sem_wait(&queue->mtx);
		if (queue_get(queue->queue, &d)) {
			if (d.type == INTEGER) printf("CONSUMER1 INTEGER %d\n", d.d.i);
			else if (d.type == POINTER) printf("CONSUMER1 POINTER %p\n", d.d.v);
		} else {
			sem_getvalue(&queue->term, &val);
			if (val == SEM_VAL) {
				sem_post(&queue->mtx);
				break;
			}
		}
		sem_post(&queue->mtx);
	}
	
	printf("CONSUMER1 TERMINATING\n");
	
	return NULL;
}

void *producer0_thread(void *arg) {
	lockable_queue *queue = (lockable_queue *)arg;
	queue_datum d;
	
	d.type = INTEGER;
	for (d.d.i = 0; d.d.i < 100; d.d.i++) {
		sem_wait(&queue->mtx);
		printf("PRODUCER %d\n", d.d.i);
		queue_put(queue->queue, d);
		sem_post(&queue->mtx);
	}
	
	pthread_barrier_wait(&queue->bar);
	
	for (d.d.i = 100; d.d.i < 200; d.d.i++) {
		sem_wait(&queue->mtx);
		printf("PRODUCER %d\n", d.d.i);
		queue_put(queue->queue, d);
		sem_post(&queue->mtx);
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
	for (j = 0; j < 10; j++) {
		sem_wait(&queue->mtx);
		printf("PRODUCER %d %p\n", j, d.d.v);
		queue_put(queue->queue, d);
		sem_post(&queue->mtx);
	}
	
	sleep(10);
	
	pthread_barrier_wait(&queue->bar);
	
	for (j = 10; j < 100; j++) {
		sem_wait(&queue->mtx);
		printf("PRODUCER %d %p\n", j, d.d.v);
		queue_put(queue->queue, d);
		sem_post(&queue->mtx);
	}
	
	sem_post(&queue->term);
	
	return NULL;
}

int main(void) {
	pthread_attr_t qattr;
	pthread_t producer0, producer1, consumer0, consumer1;
	lockable_queue queue;
	
	sem_init(&queue.mtx, 0, 1);
	
	sem_init(&queue.term, 0, SEM_VAL);
	sem_wait(&queue.term);
	sem_wait(&queue.term);
	
	pthread_barrier_init(&queue.bar, NULL, 2);
	
	queue.queue = queue_create();
	
	pthread_attr_init(&qattr);
	pthread_create(&consumer0, &qattr, &consumer0_thread, &queue);
	pthread_create(&consumer1, &qattr, &consumer1_thread, &queue);
	pthread_create(&producer0, &qattr, &producer0_thread, &queue);
	pthread_create(&producer1, &qattr, &producer1_thread, &queue);
		
	pthread_join(producer0, NULL);
	pthread_join(producer1, NULL);
	pthread_join(consumer0, NULL);
	pthread_join(consumer1, NULL);
	
	queue_destroy(queue.queue);
	
	pthread_barrier_destroy(&queue.bar);
	
	sem_destroy(&queue.term);
	sem_destroy(&queue.mtx);
	pthread_attr_destroy(&qattr);
	
	return 0;
}

