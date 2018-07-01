#include <stdlib.h>
#include <math.h>

#include "internal/vector.h"
#include "vector_object.h"

void *vector_create(int N) {
	vector *t = (vector *)malloc(sizeof (vector));
	
	if (!t) return NULL;
	
	t->N = N;
	
	t->components = (double *)malloc(N * sizeof (double));
	if (!t->components) {
		free(t);
		return NULL;
	}

	return (void *)t;
}

void vector_destroy(void *_ctx) {
	vector *ctx = (vector *)_ctx;
	
	free(ctx->components);
	free(ctx);
	
	return;
}

int vector_dim(void *_ctx) {
	vector *ctx = (vector *)_ctx;
	
	return ctx->N;
}

int vector_get_component(void *_ctx, int N, double *component) {
	vector *ctx = (vector *)_ctx;

	if ((N < 0) || (N >= ctx->N)) return 0;
	*component = ctx->components[N];
	return 1;
}

int vector_set_component(void *_ctx, int N, double component) {
	vector *ctx = (vector *)_ctx;

	if ((N < 0) || (N >= ctx->N)) return 0;
	ctx->components[N] = component;
	return 1;
}

double vector_len(void *_v) {
	vector *v = (vector *)_v;
	double len;
	int j;
	
	len = 0.0;
	
	for (j = 0; j < v->N; j++)
		len += (v->components[j] * v->components[j]);
	
	return sqrt(len);
}

int vector_inner_product(void *_v1, void *_v2, double *result) {
	vector *v1 = (vector *)_v1;
	vector *v2 = (vector *)_v2;
	int j;
	
	if (v1->N != v2->N) return 0;
	
	*result = 0.0;

	for (j = 0; j < v1->N; j++)
		*result += (v1->components[j] * v2->components[j]);
	
	return 1;
}

int vector_add2(void *_v1, void *_v2) {
	vector *v1 = (vector *)_v1;
	vector *v2 = (vector *)_v2;
	int j;
	
	if (v1->N != v2->N) return 0;
	
	for (j = 0; j < v1->N; j++)
		v1->components[j] += v2->components[j];
	
	return 1;
}

int vector_sub2(void *_v1, void *_v2) {
	vector *v1 = (vector *)_v1;
	vector *v2 = (vector *)_v2;
	int j;
	
	if (v1->N != v2->N) return 0;
	
	for (j = 0; j < v1->N; j++)
		v1->components[j] -= v2->components[j];
	
	return 1;
}

int vector_add3(void *_v1, void *_v2, void *_v3) {
	vector *v1 = (vector *)_v1;
	vector *v2 = (vector *)_v2;
	vector *v3 = (vector *)_v3;
	int j;
	
	if (
			(v1->N != v2->N) ||
			(v1->N != v3->N)
	)
		return 0;
	
	for (j = 0; j < v1->N; j++)
		v1->components[j] = v2->components[j] + v3->components[j];
	
	return 1;
}

int vector_sub3(void *_v1, void *_v2, void *_v3) {
	vector *v1 = (vector *)_v1;
	vector *v2 = (vector *)_v2;
	vector *v3 = (vector *)_v3;
	int j;
	
	if (
			(v1->N != v2->N) ||
			(v1->N != v3->N)
	)
		return 0;
	
	for (j = 0; j < v1->N; j++)
		v1->components[j] = v2->components[j] - v3->components[j];
	
	return 1;
}

void vector_scale2(void *_v, double a) {
	vector *v = (vector *)_v;
	int j;
	
	for (j = 0; j < v->N; j++)
		v->components[j] *= a;
	
	return;
}

int vector_scale3(void *_v1, void *_v2, double a){
	vector *v1 = (vector *)_v1;
	vector *v2 = (vector *)_v2;
	int j;
	
	if (v1->N != v2->N) return 0;
	
	for (j = 0; j < v1->N; j++)
		v1->components[j] = v2->components[j] * a;
	
	return 1;
}

