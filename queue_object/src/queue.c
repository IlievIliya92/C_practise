#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <string.h>

#include "internal/queue.h"
#include "queue_object.h"

void *queue_create(void) {
	queue *t = (queue *)malloc(sizeof (queue));
	pthread_mutex_t _mtx = PTHREAD_MUTEX_INITIALIZER;
	
	if (!t) return NULL;
	
	(void)memcpy(&t->mtx, &_mtx, sizeof (_mtx));
	t->B = NULL;
	t->E = NULL;
	t->iter = NULL;
	
	return (void *)t;
}

void queue_destroy(void *_ctx) {
	queue *ctx = (queue *)_ctx;
	queue_datum t;
	
	while (queue_get(_ctx, &t));
	
	free(_ctx);
	return;
}

int queue_put(void *_ctx, queue_datum d) {
	queue *ctx = (queue *)_ctx;
	list *l;
	
	pthread_mutex_lock(&ctx->mtx);
	
	l =  (list *)malloc(sizeof (list));
	if (!l) {
		pthread_mutex_unlock(&ctx->mtx);
		return 0;
	}

	l->d = d;
	l->n = NULL;

	if (ctx->E) {
		ctx->E->n = l;
		ctx->E = l;
	} else {
		ctx->B = ctx->E = l;
	}
	
	pthread_mutex_unlock(&ctx->mtx);
	return 1;
}

int queue_get(void *_ctx, queue_datum *d) {
	queue *ctx = (queue *)_ctx;
	list *l;
	
	pthread_mutex_lock(&ctx->mtx);
	
	if (!ctx->B) {
		pthread_mutex_unlock(&ctx->mtx);
		return 0;
	}
	
	l = ctx->B;
	ctx->B = ctx->B->n;
	if (!ctx->B) ctx->E = NULL;
	
	*d = l->d;
	free(l);
	
	pthread_mutex_unlock(&ctx->mtx);
	return 1;
}

int stack_push(void *_ctx, queue_datum d) {
	queue *ctx = (queue *)_ctx;
	list *l;
	
	pthread_mutex_lock(&ctx->mtx);
	
	l = (list *)malloc(sizeof (list));
	if (!l) {
		pthread_mutex_unlock(&ctx->mtx);
		return 0;
	}
	
	l->d = d;
	l->n = NULL;
	
	if (ctx->B) {
		l->n = ctx->B;
		ctx->B = l;
	} else {
		ctx->B = ctx->E = l;
	}
	
	pthread_mutex_unlock(&ctx->mtx);
	return 1;
}

int stack_pop(void *_ctx, queue_datum *d) {
	return queue_get(_ctx, d);
}

void queue_iter_begin(void *_ctx) {
	queue *ctx = (queue *)_ctx;
	
	pthread_mutex_lock(&ctx->mtx);
	ctx->iter = ctx->B;
	return;
}

void queue_iter_end(void *_ctx) {
	queue *ctx = (queue *)_ctx;
	
	ctx->iter = NULL;
	pthread_mutex_unlock(&ctx->mtx);
	return;
}

int queue_iter(void *_ctx, queue_datum *d) {
	queue *ctx = (queue *)_ctx;
	
	if (ctx->iter) {
		*d = ctx->iter->d;
		ctx->iter = ctx->iter->n;
		return 1;
	}
	
	return 0;
}

