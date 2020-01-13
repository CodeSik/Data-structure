#include <stdio.h>
#include <stdlib.h>

typedef struct CircularQueue 
{ 
int *key;
int front; 
int rear;
int qsize; 
int max_queue_size;
} CircularQueue;


CircularQueue* MakeEmpty(int max);
int IsEmpty(CircularQueue* Q);
int IsFull(CircularQueue* Q);
void Enqueue(CircularQueue* Q, int X);
void Dequeue(CircularQueue* Q);
void PrintFirst(CircularQueue* Q);
void PrintRear(CircularQueue* Q);
void DeleteQueue(CircularQueue* Q);


void main(int argc, char * argv[])
{
	FILE *fi = fopen(argv[1], "r");
	CircularQueue * queue;
	int key, size;
	char input_char = fgetc(fi);

	while (input_char != EOF)
	{
		switch (input_char)
		{
		case 'e':
			fscanf(fi,"%d", &key);
			Enqueue(queue, key);
			break;
		case 'd':
			Dequeue(queue);
			break;
		case 'f':
			PrintFirst(queue);
			break;
		case 'r':
			PrintRear(queue);
			break;
		case 'n':
			fscanf(fi, "%d", &size);
			queue = MakeEmpty(size);
			break;
		}
		input_char = fgetc(fi);
	}
	DeleteQueue(queue);
}


CircularQueue* MakeEmpty(int max)
{
	CircularQueue * newQueue = (CircularQueue*)malloc(sizeof(CircularQueue));
	newQueue->key = (int*)malloc(sizeof(int)*max);
	newQueue->front = 0;
	newQueue->rear = -1;
	newQueue->qsize = 0;
	newQueue->max_queue_size = max;
	return newQueue;
}

int IsEmpty(CircularQueue * Q)
{
	if (Q->qsize == 0)
	{
		return 1;
	}
	else
		return 0;
}

int IsFull(CircularQueue* Q)
{
	if (Q->qsize == Q->max_queue_size)
		return 1;
	else
		return 0;
}

void Enqueue(CircularQueue * Q, int X)
{
	if (IsFull(Q))
	{
		printf("Enqueue Failed : Queue is full!\n");
	}
	else {
		Q->qsize++;
		Q->rear = ++Q->rear % Q->max_queue_size;
		Q->key[Q->rear] = X;
	}
}

void Dequeue(CircularQueue * Q)
{
	if (IsEmpty(Q))
	{
		printf("Dequeue Failed : Queue is empty!\n");
	}
	else
	{
		if (Q->front + 1 < Q->max_queue_size)
			Q->front++;
		else 
			Q->front = 0;
		Q->qsize--;
	}
}


void PrintFirst(CircularQueue* Q) {
	if (IsEmpty(Q)) {
		printf("Print Failed : Queue is empty!\n");
	}
	else
		printf("First element is %d\n", Q->key[Q->front]);
}

void PrintRear(CircularQueue* Q) {
	if (IsEmpty(Q)) {
		printf("Print Failed, Queue is empty!\n");
	}
	else 
		printf("Last element is %d\n", Q->key[Q->rear]);
}

void DeleteQueue(CircularQueue * Q)
{
	free(Q->key);
}

