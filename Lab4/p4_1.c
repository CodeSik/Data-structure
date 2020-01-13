#include <stdio.h>
#include <stdlib.h>


typedef struct CircularQueue
{ int *key;
  int front;
  int rear;
  int qsize; 
  int max_queue_size; 
}CircularQueue;

CircularQueue MakeEmpty(int max);
int IsEmpty(CircularQueue* Q);
int IsFull(CircularQueue* Q);
void Enqueue(CircularQueue* Q, char X);

int main(int argc, char *argv[]) {
	FILE *fi = fopen(argv[1], "r");
	CircularQueue Queue;
	while (!feof(fi)) {
		char option;
		int x;
		fscanf(fi, "%c", &option);
		if (option == 'n')
		{
			fscanf(fi, "%d", &x);
			Queue = MakeEmpty(x);
		}
		else if (option == 'e')
		{
			fscanf(fi, " %c", &option);
			
			Enqueue(&Queue, option);
		}


	}
	return 0;
}
CircularQueue MakeEmpty(int max)
{
	CircularQueue Q;
	Q.key = (char*)malloc(sizeof(char)*max);
	Q.front = 1;
	Q.rear = 0;
	Q.qsize = 0;
	Q.max_queue_size = max;
	return Q;
}

int IsEmpty(CircularQueue* Q)
{
	if (Q->qsize == 0)
		return 1;
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

void Enqueue(CircularQueue* Q, char X)
{
	
	if (IsFull(Q))
		printf("Enqueue Failed : Queue is full!\n");
	else {
		Q->qsize++;
		Q->rear = ++Q->rear %Q->max_queue_size;
		Q->key[Q->rear] = X;
	}
}
