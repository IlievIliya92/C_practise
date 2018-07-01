#include <stdio.h>
#include <stdlib.h>

void walk(int start, int **g, int n, int *visited, int depth) {
	int j;
	
	visited[start] = 1;
	
	for (j = 0; j < depth; j++)
		printf("\t");
	
	printf("%d\n", start);
	
	for (j = 0; j < n; j++)
		if (g[start][j] && !visited[j])
			walk(j, g, n, visited, depth + 1);
	
	visited[start] = 0;
	
	return;
}

int main(void) {
	int **g, n, start, *visited;
	int i, j;
	
	scanf("%d%d", &n, &start);
	if ((start < 0) || (start >= n)) return 1;
	
	g = (int **)malloc(n * sizeof (int *));
	for (j = 0; j < n; j++)
		g[j] = (int *)calloc(n, sizeof (int));
	visited = (int *)calloc(n, sizeof (int));
	
	while (1) {
		scanf("%d%d", &i, &j);
		if (
				(i < 0) || (i >= n) ||
				(j < 0) || (j >= n))
			break;
		g[i][j] = 1;
		*(*(g + i) + j) = 1;
	}
	
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			printf("%d%c", g[i][j],
					(j == (n - 1) ? '\n' : ' '));
	
	walk(start, g, n, visited, 0);
	
	free(visited);
	for (j = 0; j < n; j++)
		free(g[j]);
	free(g);
	
	return 0;
}
