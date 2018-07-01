#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue_object.h"
#include "graph.h"

void walk_dfs(int start, graph *g, int *visited, int depth) {
	queue_datum next;
	int j;
	
	if (!depth) (void)memset(visited, 0, g->n * sizeof (int));
	
	visited[start] = 1;
	
	for (j = 0; j < depth; j++)
		printf("\t");
	
	printf("%d\n", start);
	
	queue_iter_begin(g->g[start]);
	while (queue_iter(g->g[start], &next))
		if (!visited[next.d.i])
			walk_dfs(next.d.i, g, visited, depth + 1);
	queue_iter_end(g->g[start]);
	
	visited[start] = 0;
	
	return;
}

int walk_bfs(int start, graph *g, int *visited, int *walked) {
	void *queue;
	queue_datum d, next;
	int k;
	int j;
	
	for (j = 0; j < g->n; j++) {
		visited[j] = 0;
		walked[j] = 0;
	}
	
	queue = queue_create();
	if (!queue) goto bad0;
	
	d.type = INTEGER;
	next.type = INTEGER;
	k = 0;
	
	visited[start] = 1;
	d.d.i = start;
	if (!queue_put(queue, d)) goto bad1;
	
	while (queue_get(queue, &d)) {
		walked[k++] = d.d.i;
		queue_iter_begin(g->g[d.d.i]);
		while (queue_iter(g->g[d.d.i], &next)) {
			if (!visited[next.d.i]) {
				if (!queue_put(queue, next)) goto bad1;
				visited[next.d.i] = 1;
			}
		}
		queue_iter_end(g->g[d.d.i]);
	}
	
	queue_destroy(queue);
	return 1;
bad1:
	queue_destroy(queue);
bad0:
	return 0;
}

int main(void) {
	graph *g;
	int n, start, *visited, *walked;
	queue_datum d;
	int i, j;
	int ret = 0;
	
	scanf("%d%d", &n, &start);
	if ((start < 0) || (start >= n)) {
		ret = 1;
		goto bad0;
	}
	
	g = graph_create(n);
	if (!g) {
		ret = 1;
		goto bad0;
	}
	visited = (int *)calloc(n, sizeof (int));
	if (!visited) {
		ret = 1;
		goto bad1;
	}
	walked = (int *)calloc(n, sizeof (int));
	if (!walked) {
		ret = 1;
		goto bad2;
	}
	
	d.type = INTEGER;
	while (1) {
		scanf("%d%d", &i, &j);
		if (
				(i < 0) || (i >= n) ||
				(j < 0) || (j >= n))
			break;
		d.d.i = j;
		if (!queue_put(g->g[i], d)) {
			ret = 1;
			goto bad3;
		}
	}
	
	if (!walk_bfs(start, g, visited, walked)) {
		ret = 1;
		goto bad3;
	}
	
	for (j = 0; j < n; j++)
		printf("(%d, %d) ", walked[j], visited[j]);
	printf("\n");
	
	walk_dfs(start, g, visited, 0);
	
bad3:
	free(walked);
bad2:
	free(visited);
bad1:
	graph_destroy(g);
bad0:
	return ret;
}
