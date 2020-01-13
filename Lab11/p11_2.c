#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 987654321

typedef struct Node {
	int vertex;
	int dist; //distance
	int prev;
}Node;

typedef struct Graph
{
	int size; //number of vertex
	int ** vertices; 
	Node *nodes;
}Graph;

typedef struct Heap
{
	int Capacity;
	int Size;
	Node* Element;
}Heap;

Graph CreateGraph(int size);
void printShortestPath(Graph g);
Heap* createMinHeap(int heapSize);
void insertToMinHeap(Heap* minHeap, int vertex, int distance);
Node deleteMin(Heap* minHeap);
void printEachRoute(Graph g, int i);
int IsFull(Heap* heap);
int IsEmpty(Heap* heap);

void main(int argc, char* argv[])
{
	FILE *fi = fopen(argv[1], "r");
	Graph g;

	int size;
	fscanf(fi, "%d\n", &size);
	g = CreateGraph(size + 1);
	char temp = 0;
	while (temp != '\n')
	{
		int node1, node2, weight;
		fscanf(fi, "%d - %d - %d", &node1, &node2, &weight);
		g.vertices[node1][node2] = weight;
		temp = fgetc(fi);
	}
	printShortestPath(g);
	fclose(fi);
}

Graph CreateGraph(int size)
{
	Graph graph;
	int i, j;
	graph.size = size - 1;
	graph.vertices = (int**)malloc(sizeof(int)*(size));

	for (i = 0; i < size; i++)
	{
		graph.vertices[i] = (int*)malloc(sizeof(int)*(size));
		for (j = 0; j < size; j++)
		{
			graph.vertices[i][j] = 0;
		}
	}

	graph.nodes = (Node*)malloc(sizeof(struct Node)*size);
	return graph;

}

Heap* createMinHeap(int heapSize)
{
	Heap* minheap = (Heap*)malloc(sizeof(Heap));
	minheap->Size = 0;
	minheap->Capacity = heapSize;
	minheap->Element = (Node*)malloc(sizeof(Node) * heapSize);

	return minheap;
}

void insertToMinHeap(Heap* minHeap, int vertex, int distance)
{
	int i;

	if (IsFull(minHeap))
	{
		printf("Insertion Error: Max Heap is full.\n");
	}
		
		i = ++(minHeap->Size);

		while ((i != 1) && (vertex > minHeap->Element[i].dist))
		{
			minHeap->Element[i] = minHeap->Element[i / 2];
			i /= 2;
		}
		minHeap->Element[i].vertex = vertex;
		minHeap->Element[i].dist = distance;
		//printf("insert %d\n", value);

}

int IsFull(Heap* heap) {
	return heap->Capacity <= heap->Size;
}
int IsEmpty(Heap* heap) {
	return heap->Size == 0;
}

Node deleteMin(Heap* minHeap)
{
	Node* tmp;
	tmp = (Node*)malloc(sizeof(Node));

	int i, child;
	Node min, last;
	min = minHeap->Element[1];
	last = minHeap->Element[minHeap->Size--];

	for (i = 1; i * 2 <= minHeap->Size; i = child)
	{
		child = i * 2;
		if (child != minHeap->Size && minHeap->Element[child + 1].dist < minHeap->Element[child].dist)
			child++;
		if (last.dist > minHeap->Element[child].dist)
			minHeap->Element[i] = minHeap->Element[child];
		else
			break;
	}
	minHeap->Element[i].dist = last.dist;
	minHeap->Element[i].vertex = last.vertex;

	return min;
}

void printShortestPath(Graph g)
{
	int i, vertex, dist, prev;
	Node node;
	Heap* minheap = createMinHeap((g.size)*(g.size));
	for (i = 1 ;i <= g.size; i++)
	{
		node.vertex = i;
		node.dist = INF;
		node.prev = -1;
		g.nodes[i] = node;
	}
	insertToMinHeap(minheap, 1, 0);
	g.nodes[1].dist = 0;

	while (!IsEmpty(minheap))
	{
		node = deleteMin(minheap);
		vertex = node.vertex;
		dist = node.dist;
		if (dist <= g.nodes[vertex].dist) {
			g.nodes[vertex].dist = dist;
			for (i = 1; i <= g.size; i++) {
				if (g.vertices[vertex][i] != 0) {
					if (dist + g.vertices[vertex][i] < g.nodes[i].dist) {
						g.nodes[i].dist = dist + g.vertices[vertex][i];
						g.nodes[i].prev = vertex;
						insertToMinHeap(minheap, i, dist + g.vertices[vertex][i]);
					}
				}
			}
		}
	}
	for (i = 2; i <= g.size; i++)
	{
		printEachRoute(g, i);
		printf("%d( cost: %d)\n", g.nodes[i].vertex, g.nodes[i].dist);
	}
	

	free(g.nodes);

}

void printEachRoute(Graph g, int i) {
	if (g.nodes[i].prev != -1) {
		printEachRoute(g, g.nodes[i].prev);
		printf("%d->", g.nodes[i].prev);
	}
}
