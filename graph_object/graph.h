#ifndef _GRAPH_
#define _GRAPH_

struct graph {
	int n;
	void **g;
};
typedef struct graph graph;

graph *graph_create(int);
void graph_destroy(graph *);

#endif
