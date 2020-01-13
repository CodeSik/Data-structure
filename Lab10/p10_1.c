#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct struct_Queue* Queue;
typedef struct struct_Graph* Graph;

struct struct_Queue
{
	int* key;
	int first;
	int rear;
	int qsize;
	int max_queue_size;
};

struct struct_Graph
{
	int size;
	int* node;
	int**matrix;
};

Graph CreateGraph(int* nodes);
Graph InsertEdge(Graph graph, int a, int b);

void main(int argc, char* argv[]) {

	FILE* fp = fopen(argv[1], "r");
	Graph Graph;
	char line[105];
	int numbers[105];
	int* node;
	int linesize;
	int	a;
	int b;
	int i, j;
	int num = 0;

	fgets(line, 105, fp);

	for (i = 0, linesize = 0; i<105; i++) {
		if (line[i] == '\n' || line[i] == ' ') {
			numbers[linesize] = num;
			num = 0;
			linesize++;
		}
		else {
			num = num * 10 + line[i] - '0';
		}
	}

	node = (int*)malloc(sizeof(int)*(linesize + 1));
	node[0] = linesize;
	for (i = 0; i <= linesize; i++) {
		node[i + 1] = numbers[i];
	}

	Graph = CreateGraph(node);

	while (fscanf(fp, "%d-%d", &a, &b) != EOF) {
		Graph = InsertEdge(Graph, a, b);
	}

	
	printf("  ");
	for (i = 0; i<Graph->size; i++) printf("%d ", Graph->node[i]);
	printf("\n");
	for (i = 0; i<Graph->size; i++) {
		printf("%d ", Graph->node[i]);
		for (j = 0; j<Graph->size; j++) {
			printf("%d ", Graph->matrix[i][j]);
		}
		printf("\n");
	}

}

Graph CreateGraph(int* nodes) {
	Graph graph = NULL;
	int i, j;
	graph = (Graph)malloc(sizeof(struct struct_Graph));
	graph->size = nodes[0];

	graph->node = (int*)malloc(sizeof(int)*graph->size);
	graph->node = nodes + 1;
	graph->matrix = (int**)malloc(sizeof(int*)*graph->size);

	for (i = 0; i<graph->size; i++) {
		graph->matrix[i] = (int*)malloc(sizeof(int)*graph->size);
		for (j = 0; j<graph->size; j++) graph->matrix[i][j] = 0;
	}


	return graph;
}

Graph InsertEdge(Graph graph, int a, int b) {
	int i;
	for (i = 0; i<graph->size; i++) {
		if (a == graph->node[i])
		{
			a = i;
		}
		if (b == graph->node[i]) 
		{
			b = i;
		}
	}
	graph->matrix[a][b] = 1;
	return graph;
}