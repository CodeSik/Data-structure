#include <stdio.h>
#include <stdlib.h>

typedef struct HeapStruct
{
	int Capacity;
	int Size;
	int *Element;
}Heap;

Heap* CreateHeap(int heapSize);
void Insert(Heap* heap, int value);
void Find(Heap* heap, int value);
int IsEmpty(Heap* heap);
int IsFull(Heap* heap);

void main(int argc, char* argv[])
{
	FILE *fi = fopen(argv[1], "r");
	char cv;
	Heap* maxHeap;
	int heapSize, key;
	while (!feof(fi))
	{
		fscanf(fi, "%c", &cv);
		switch (cv)
		{
		case 'n':
			fscanf(fi, "%d", &heapSize);
			maxHeap = CreateHeap(heapSize);
			break;
		case 'i':
			fscanf(fi, "%d", &key);
			Insert(maxHeap, key);
			break;
		case 'f':
			fscanf(fi, "%d", &key);
			Find(maxHeap, key);
			break;
		default:
			break;
		}
	}
}



void Insert(Heap* heap, int value)
{
	int i;
	int check = 0;
	for (i = 0; i <= heap->Size; i++)
	{
		if (heap->Element[i] == value)
		{
			check = 1;
		}
		else
		{
			;
		}
	}

	if (IsFull(heap))
		printf("Error: heap is full.\n");
	else if (check == 1)
	{
		printf("%d is already in the tree\n", value);
		return;
	}
	else if (IsEmpty(heap))
	{
		heap->Element[1] = value;
		heap->Size++;
		printf("insert %d\n", value);
	}
	else
	{
		int i;
		i = ++(heap->Size);

		while ((i != 1) && (value > heap->Element[i / 2]))
		{
			heap->Element[i] = heap->Element[i / 2];
			i /= 2;
		}
		heap->Element[i] = value;
		printf("insert %d\n", value);
	}

}


Heap* CreateHeap(int heapSize)
{
	Heap* tmp = (Heap*)malloc(sizeof(Heap));
	tmp->Capacity = heapSize;
	tmp->Element = (int*)malloc(sizeof(int) * (heapSize + 1));
	tmp->Element[0] = 0xfffffff;
	tmp->Size = 0;
	return tmp;
}

int IsFull(Heap* heap) {
	return heap->Capacity <= heap->Size;
}
int IsEmpty(Heap* heap) {
	return heap->Size == 0;
}

void Find(Heap* heap, int value)
{
	int i;
	int check=0;
	for (i = 0; i <= heap->Size; i++)
	{
		if (heap->Element[i] == value)
		{
			check = 1;
		}
		else
		{
			;
		}
	}
	if (check == 1)
	{
		printf("%d is in the tree\n", value);
	}
	else
		printf("%d is not in the tree\n", value);
}