#ifndef _QUEUE_
#define _QUEUE_

#include <pthread.h>

#include "queue_object.h"

struct list {
	queue_datum d;
	struct list *n;
};
typedef struct list list;

struct queue {
	pthread_mutex_t mtx;
	list *B, *E;
	list *iter;
};
typedef struct queue queue;

#endif
