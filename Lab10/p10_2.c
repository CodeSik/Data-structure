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
Graph CreateGraph(int* node);
Graph InsertEdge(Graph graph, int a, int b);
Queue MakeNewQueue(int X);
int IsEmpty(Queue Q);
int IsFull(Queue Q);
int Dequeue(Queue Q);
void DeleteGraph(Graph G);
void Topsort(Graph G);
void Enqueue(Queue Q, int X);
void DeleteQueue(Queue Q);
void main(int argc, char* argv[]) {
 FILE* fp = fopen(argv[1], "r");
 Graph Graph;
 char line[105];
 int numbers[105];
 int* node;
 int linesize;
 int input1, input2;
 int i, j;
 int num = 0;
 fgets(line, 105, fp);
 for (i = 0, linesize = 0; i<105; i++) {
  if (line[i] == '\n' || line[i] == ' ') {
   numbers[linesize] = num;
   num = 0;
   linesize++;
  }
  else
   num = num * 10 + line[i] - '0';
  
  if (line[i] == '\n') break;
 }
 node = (int*)malloc(sizeof(int)*(linesize + 1));
 node[0] = linesize;
 for (i = 0; i <= linesize; i++) {
  node[i + 1] = numbers[i];
 }
 Graph = CreateGraph(node);
 free(node);
 while (fscanf(fp, "%d-%d", &input1, &input2) != EOF) {
  Graph = InsertEdge(Graph, input1, input2);
 }

 Topsort(Graph);
 printf("\n");
 DeleteGraph(Graph);
}
Graph CreateGraph(int* node) {
 Graph graph = NULL;
 int i, j;
 graph = (Graph)malloc(sizeof(struct struct_Graph));
 graph->size = node[0];
 graph->node = (int*)malloc(sizeof(int)*graph->size);
 
 for (i = 0; i<graph->size; i++) graph->node[i] = node[i + 1];
 graph->matrix = (int**)malloc(sizeof(int*)*graph->size);
 for (i = 0; i<graph->size; i++) {
  graph->matrix[i] = (int*)malloc(sizeof(int)*graph->size);
  for (j = 0; j<graph->size; j++) graph->matrix[i][j] = 0;
 }

 return graph;
}
Graph InsertEdge(Graph graph, int input1, int input2) {
 int i;
 for (i = 0; i<graph->size; i++) {
  if (input1 == graph->node[i])
   input1 = i;
  if (input2 == graph->node[i])
   input2 = i;
 }
 graph->matrix[input1][input2] = 1;
 return graph;
}
void Topsort(Graph G) {
 Queue Q;
 int v, i, j;
 int* indegree;
 Q = MakeNewQueue(G->size);
 indegree = (int*)malloc(sizeof(int)*G->size);
 for (i = 0; i<G->size; i++) {
  for (j = 0; j<G->size; j++) {
   if (G->matrix[j][i])
    indegree[i]++;
  }
 }
 for (i = 0; i<G->size; i++) {
  if (indegree[i] == 0)
   Enqueue(Q, i);
 }
 while (!IsEmpty(Q)) {
  v = Dequeue(Q);
  if (indegree[v] == 0)
   printf("%d ", G->node[v]);
  for (i = 0; i<G->size; i++) {
   if (G->matrix[v][i]) {
    if (--indegree[i] == 0)
     Enqueue(Q, i);
   }
  }
 }
 DeleteQueue(Q);
}
int IsEmpty(Queue Q) {
 if (Q->qsize == 0)
  return 1;
 else
  return 0;
}
int IsFull(Queue Q) {
 if (Q->qsize == Q->max_queue_size)
  return 1;
 else
  return 0;
}
void Enqueue(Queue Q, int X) {
 if (IsFull(Q))
  printf("Enqueue Failed : Queue is full!\n");
 else {
  Q->qsize++;
  Q->rear = (Q->rear + 1) % Q->max_queue_size;
  Q->key[Q->rear] = X;
 }
}
int Dequeue(Queue Q) {
 int r;
 if (IsEmpty(Q))
  printf("Dequeue Failed : Queue is empty!\n");
 else {
  r = Q->key[Q->first];
  Q->qsize--;
  Q->first = (Q->first + 1) % Q->max_queue_size;
 }
 return r;
}
void DeleteQueue(Queue Q) {
 free(Q->key);
 free(Q);
}
void DeleteGraph(Graph G) {
 int i;
 free(G->node);
 for (i = 0; i<G->size; i++) free(G->matrix[i]);
 free(G->matrix);
 free(G);
}
Queue MakeNewQueue(int X) {
 Queue newQueue = (Queue)malloc(sizeof(struct struct_Queue));
 newQueue->key = (int*)malloc(sizeof(int)*X);
 newQueue->first = 0;
 newQueue->rear = -1;
 newQueue->qsize = 0;
 newQueue->max_queue_size = X;
 return newQueue;
}
	
