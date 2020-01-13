#include <stdio.h>
#include <stdlib.h>

typedef struct HeapStruct { 
	int Capacity;
	int Size; 
	int * Element;
}Heap;

Heap* CreateHeap(int heapSize);
void Insert(Heap* heap, int value);

void main(int argc, char* argv[])
{
	FILE *fi = fopen(argv[1], "r");
	char cv;
	Heap * maxHeap;
	int heapSize, key;
	while (!feof(fi))
	{
		fscanf(fi, "%c", &cv);
		switch (cv)
		{
		case 'n' :
			fscanf(fi, "%d", &heapSize);
			printf("n\n");
			maxHeap = CreateHeap(heapSize);
			break;
		case 'i':
			fscanf(fi, "%d", &key);
			Insert(maxHeap, key);
			break;
		}
	}
}


Heap* CreateHeap(int heapSize)
{
	Heap* tmp;
	tmp = malloc(sizeof(Heap));
	tmp->Capacity = heapSize;
	tmp->Element = malloc(sizeof(int)*heapSize);
	tmp->Size = 0;
	return tmp;
}

void Insert(Heap* heap, int value)
{
	int i,j;
	i = ++(heap->Capacity);
	for (j = 0; j < heap->Capacity; j++)
	{
		if (heap->Element[j] == value)
		{
			printf("Insertion Error : There is already %d in the tree\n", value);
			return 0;
		}
	}
	while ((i != 1) && (value > heap ->Element[i / 2]))
	{
		heap->Element[i] = heap->Element[i / 2];
		i /= 2;
	}


	heap->Element[i] = value;
	printf("Insert %d\n", heap->Element[i]);

}
