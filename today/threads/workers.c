#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "queue_object.h"

const int num_workers = 1;
const int matrix_size = 1000;

struct thr_arg {
	int n;
	double **c, **a, **b;
	void *stack;
};
typedef struct thr_arg thr_arg;

static double mul_rc(int n, int i, int j, double **a, double **b) {
	double t = 0.0;
	int k;
	
	for (k = 0; k < n; k++)
		t += a[i][k] * b[k][j];
	
	return t;
}

void *worker(void *_arg) {
	thr_arg *arg = (thr_arg *)_arg;
	queue_datum d;
	double t;
	int k, j;
	
	while (stack_pop(arg->stack, &d)) {
		for (j = 0; j < arg->n; j++) {
			t = 0.0;
			for (k = 0; k < arg->n; k++)
				t += arg->a[d.d.i][k] * arg->b[k][j];
			arg->c[d.d.i][j] = t;
		}
/*
			arg->c[d.d.i][j] = mul_rc(arg->n, d.d.i, j, arg->a, arg->b);
*/
	}
	
	return NULL;
}

int main(void) {
	thr_arg matrix;
	pthread_t workers[num_workers];
	queue_datum d;
	int n = matrix_size, i, j;
	
	matrix.n = n;
	
	matrix.c = (double **)malloc(n * sizeof (double *));
	for (j = 0; j < n; j++)
		matrix.c[j] = (double *)malloc(n * sizeof (double));
	
	matrix.a = (double **)malloc(n * sizeof (double *));
	for (j = 0; j < n; j++)
		matrix.a[j] = (double *)malloc(n * sizeof (double));
	
	matrix.b = (double **)malloc(n * sizeof (double *));
	for (j = 0; j < n; j++)
		matrix.b[j] = (double *)malloc(n * sizeof (double));
	
	matrix.stack = queue_create();
	
	d.type = INTEGER;
	for (j = 0; j < n; j++) {
		d.d.i = j;
		stack_push(matrix.stack, d);
	}
	
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			if (i == j) matrix.a[i][j] = 1.0;
			else matrix.a[i][j] = 0.0;
			matrix.b[i][j] = 1.0;
		}
	
	for (i = 0; i < num_workers; i++)
		pthread_create(&workers[i], NULL, worker, &matrix);
	
	for (i = 0; i < num_workers; i++)
		pthread_join(workers[i], NULL);
	
/*
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			printf("%lf ", matrix.c[i][j]);
		printf("\n");
	}
*/
	
	queue_destroy(matrix.stack);
	
	for (j = 0; j < n; j++)
		free(matrix.b[j]);
	free(matrix.b);
	
	for (j = 0; j < n; j++)
		free(matrix.a[j]);
	free(matrix.a);
	
	for (j = 0; j < n; j++)
		free(matrix.c[j]);
	free(matrix.c);
	
	return 0;
}

