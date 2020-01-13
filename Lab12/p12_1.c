#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Graph {
	int num;
	int **weight;
	int* check_visit;
}graph;

typedef struct CircularQueue
{
	int* content;
	int first;
	int rear;
	int qsize;
	int max_queue_size;
}queue;

int IsEmpty_Q(queue* Q) {
	if (Q->qsize == 0) return 1;
	else return 0;
}

int IsFull_Q(queue* Q) {
	if (Q->qsize == Q->max_queue_size) return 1;
	else return 0;
}

graph makeGraph(FILE* fi);
void BFS(graph g, int start, int end);


queue* create_queue(int size);
void enqueue(queue* q, int value);
int dequeue(queue* q);
void close_queue(queue* q);



void main(int argc, char* argv[]) {
	FILE *fi = fopen(argv[1], "r");
	graph g = makeGraph(fi);     
	int i,start, end;    
	fscanf(fi, "%d-%d", &start, &end);
 
	printf("BFS : ");
	BFS(g, start, end);
	if (g.check_visit[end] == 0)
		printf("cannot find");
	
	printf("\n");
		/** free all the memory     
		close the file        **/
	free(g.check_visit);
	//fclose(fi);
	for(i=0;i<g.num+2;i++)
	{
		free(g.weight[i]);	
	}
	free(g.weight);
}
queue* create_queue(int size)
{
	queue* Q = (queue*)malloc(sizeof(queue));
	Q->content = (int*)malloc(sizeof(int) * size);
	Q->first = 1;
	Q->rear = 0;
	Q->qsize = 0;
	Q->max_queue_size = size;
	return Q;
}


void enqueue(queue* q, int value)
{
	if (IsFull_Q(q))
	{
		printf("Insertion failed. queue is full.\n");
	}
	else
	{
		q->qsize++;
		q->rear = ++q->rear % q->max_queue_size;
		q->content[q->rear] = value;
	}
}

int dequeue(queue* q)
{
	if (IsEmpty_Q(q))
		printf("Deletion failed. queue is empty.\n");
	else
	{
		if (q->first + 1 < q->max_queue_size)
			q->first++;
		else
			q->first = 0;
		q->qsize--;
	}
}

void close_queue(queue* q)
{
	free(q->content);
}

void BFS(graph g, int start, int end)
{
	queue* Q = create_queue(300);
	enqueue(Q, start);
	g.check_visit[start] = 1;

	while (!IsEmpty_Q(Q))
	{
		int tmp,b,i;
		if (IsEmpty_Q(Q)) {
			printf("Print failed, queue is EMPTY!\n");
			break;
		}
		else 
			tmp = Q->content[Q->first];
		printf("%d ", tmp);
		b=dequeue(Q);
		if (tmp == end)
			break;
		for (i = 1; i < g.num+2; i++)
		{
			if (g.check_visit[i] == 0 && g.weight[tmp][i] == 1)
			{
				g.check_visit[i] = 1;
				enqueue(Q, i);
			}
		}

		
	}
	close_queue(Q);
}

graph makeGraph(FILE* fi)
{
	graph G;
	int size,i,j;
	fscanf(fi, "%d", &size);
	G.num = size;
	G.weight = (int**)malloc(sizeof(int*)*(size+2));

	for (i = 0; i < size+2; i++)
	{
		G.weight[i] = (int*)malloc(sizeof(int)*(size+2));
		for (j = 0; j < size+2; j++)
		{
			G.weight[i][j] = 0;
		}
	}

	G.check_visit = (int*)malloc(sizeof(int) * 300);

	for (i = 1; i < 300; i++)
	{
		G.check_visit[i] = 0;
	}

	char temp = 0;
	
	while (temp != '\n')
	{
		int node1, node2;
		fscanf(fi, "%d-%d", &node1, &node2);
		G.weight[node1][node2] = 1;
		temp = fgetc(fi);
	}
	
	return G;
}
