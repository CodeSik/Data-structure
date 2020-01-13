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

typedef struct Stack {
	int* content;
	int top;
	int max_stack_size;
}stack;



int IsEmpty_Q(queue* Q) {
	if (Q->qsize == 0) return 1;
	else return 0;
}

int IsFull_Q(queue* Q) {
	if (Q->qsize == Q->max_queue_size) return 1;
	else return 0;
}

int IsFull_S(stack* S) {
	if (S->max_stack_size == S->top) return 1; 
	else return 0;
}
int IsEmpty_S(stack* S) {
	if (S->top == -1) return 1;
	else return 0;
}

stack* create_stack(int num);
void push(stack* s, int value);
int pop(stack* s);
void close_stack(stack* s);


graph makeGraph(FILE* fi);

void BFS(graph g, int start, int end);
void DFS_recursive(graph g, int start, int end);
void DFS_iterative(graph g, int start, int end);

queue* create_queue(int size);
void enqueue(queue* q, int value);
int dequeue(queue* q);
void close_queue(queue* q);

graph reset_visit(graph g);

int ans = 0;
void main(int argc, char* argv[]) {
	FILE *fi = fopen(argv[1], "r");
	graph g = makeGraph(fi);
	int start, end;
	fscanf(fi, "%d-%d", &start, &end);

	printf("DFS recursive: ");
	DFS_recursive(g, start, end);
	if (g.check_visit[end] == 0)
		printf("cannot find");
	//reset g.check_visit
	g = reset_visit(g);

	printf("\nDFS iterative: ");
	DFS_iterative(g, start, end);
	if (g.check_visit[end] == 0)
		printf("cannot find");
	//reset g.check_visit;
	g = reset_visit(g);

	printf("\nBFS : ");
	BFS(g, start, end);
	if (g.check_visit[end] == 0)
		printf("cannot find");
	printf("\n");
	/** free all the memory
	close the file        **/

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
		int tmp, i, b;
		if (IsEmpty_Q(Q)) {
			printf("Print failed, queue is EMPTY!\n");
			break;
		}
		else
			tmp = Q->content[Q->first];
		printf("%d ", tmp);
		b = dequeue(Q);
		if (tmp == end)
			break;
		for (i = start; i < g.num+2 ; i++)
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

void DFS_recursive(graph g, int start, int end)
{
	
	int i;
	if (ans == 1)
		return;
	if (g.check_visit[start] == 1)
		return;
	else
	{ 
		if (start == end)
			ans = 1;
		g.check_visit[start] = 1;

	
		printf("%d ", start);
	
		for (i = 1; i < g.num+2; i++)
		{
			if (g.weight[start][i] == 1 && g.check_visit[i] == 0)
			{
				DFS_recursive(g, i, end);
			}
		}
	}
}
void DFS_iterative(graph g, int start, int end)
{
	int i, printing;
	stack* s= create_stack(300);
	push(s, start);
	g.check_visit[start] = 1;

	while (!IsEmpty_S(s))
	{
		if (IsEmpty_S(s)) {
			printf("Print failed, queue is EMPTY!\n");
			break;
		}
		else
			printing = pop(s);
		printf("%d ", printing);
		
		if (printing == end)
			break;
		for (i = start; i < g.num + 2; i++)
		{
			if (g.check_visit[i] == 0 && g.weight[printing][i] == 1)
			{
				g.check_visit[i] = 1;
				push(s, i);
			}
		}

	}
	close_stack(s);
}

graph makeGraph(FILE* fi)
{
	graph G;
	int size, i, j;
	fscanf(fi, "%d", &size);
	G.num = size;
	G.weight = (int**)malloc(sizeof(int)*(size+2));

	for (i = 0; i <= size+2 ; i++)
	{
		G.weight[i] = (int*)malloc(sizeof(int)*(size+2));
		for (j = 0; j <= size+2 ; j++)
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


graph reset_visit(graph G)
{
	int i;
	for (i = 1; i < 300; i++)
	{
		G.check_visit[i] = 0;
	}

	return G;
}

void close_stack(stack* s)
{
	free(s->content);
}

stack* create_stack(int num)
{
	stack* S = (stack*)malloc(sizeof(stack));
	S->content = (int*)malloc(sizeof(int)*num);
	if (S->content == NULL)
	{
		printf("Error");
		exit(-1);
	}
	S->max_stack_size = num;
	S->top = -1;
}
void push(stack* s, int value)
{
	if (IsFull_S(s))
	{
		printf("Error\n");
		exit(-1);
	}
	else s->content[++s->top] = value;
}

int pop(stack* s)
{
	if (IsEmpty_S(s))
	{
		printf("Error\n");
		exit(-1);
	}
	else return s->content[s->top--];
}
