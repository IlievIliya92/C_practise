#include <stdlib.h>

#include "graph.h"
#include "queue_object.h"

graph *graph_create(int n) {
	int i, j;
	graph *g;
	
	g = (graph *)calloc(1, sizeof (graph));
	if (!g) goto bad0;
	g->n = n;
	
	g->g = (void **)calloc(n, sizeof (void *));
	if (!g->g) goto bad1;
	
	for (i = 0; i < n; i++) {
		g->g[i] = queue_create();
		if (!g->g[i]) {
			for (j = 0; j < i; j++)
				queue_destroy(g->g[j]);
			goto bad2;
		}
	}
	
	return g;
bad2:
	free(g->g);
bad1:
	free(g);
bad0:
	return NULL;
}

void graph_destroy(graph *g) {
	int j;
	
	for (j = 0; j < g->n; j++)
		queue_destroy(g->g[j]);
	
	free(g->g);
	free(g);
	
	return;
}

