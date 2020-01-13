
#include<stdio.h>
#include<stdlib.h>

typedef struct Node *PtrToNode; 
typedef PtrToNode List; 
typedef PtrToNode Position;
typedef int ElementType; 
struct Node
{	 ElementType element; 
	Position          next; 
};
 
List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
void Delete(ElementType X, List L);
Position FindPrevious(ElementType X, List L);
Position Find(ElementType X, List L);
void Insert(ElementType X, List L, Position P);
void DeletList(List L);

List B;

int main(int argc, char* argv[]) {
	FILE* fi = fopen(argv[1], "r");
	B = MakeEmpty(B);

	char option;
	int x, y;

	while (fscanf(fi, "%c", &option) != EOF) {
		if (option == 'i') {
			fscanf(fi, "%d %d", &x, &y);
			if (y != -1) {
				Position List = Find(y, B);
				if (List == NULL) printf("Insertion(%d) Failed : element %d is not in the list\n", x, y);
				else Insert(x, B ,List);
			}
			else {
				Insert(x, B, B);
			}
		}

		else if (option == 'd') {
			fscanf(fi, "%d", &x);
			Position tmp = Find(x, B);
			if (tmp == NULL)printf("Deletion failed : element %d is not in the list\n", x);
			else Delete(x, B);
		}

		else if (option == 'f') {
			fscanf(fi, "%d", &x);
			if (FindPrevious(x, B) == B)
				printf("Key of the previous node of %d is header\n", x);
			else if (Find(x, B) == NULL)
				printf("Could not find %d in the list\n", x);
			else
				printf("Key of the previous node of %d is %d\n", x, FindPrevious(x, B)->element);
		}

		else if (option == 'p') {
			List temp1 = B;
			List temp2;
			while (temp1->next != NULL) {
				temp2 = temp1->next;
				printf("key:%d\t", temp2->element);
				temp1 = temp1->next;
			}
		}
	}
	fclose(fi);
	DeletList(B);
	return 0;
}

List MakeEmpty(List L) {
	if (L != NULL) DeletList(L);
	L = (List)malloc(sizeof(struct Node));
	if (L == NULL) {
		printf("ERROR\n");
		exit(-1);
	}
	L->element = 0;
	L->next = NULL;
	return L;
}


int IsEmpty(List L) {
	return L->next == NULL;
}

int IsLast(Position P, List L) {
	return P->next == NULL;
}

void Delete(ElementType X, List L) {
	Position P, tmp;

	P = FindPrevious(X, L);

	if (!IsLast(P, L)) {
		tmp = P->next;
		P->next = tmp->next;
		free(tmp);
	}
}

Position FindPrevious(ElementType X, List L) {
	Position P;
	P = L;
	while (P->next != NULL && P->next->element != X)
		P = P->next;
	return P;
}

Position Find(ElementType X, List L) {
	Position P;

	P = L->next;
	while (P != NULL && P->element != X) 
		P = P->next;

	return P;
}

void Insert(ElementType X, List L, Position P) {
	Position temp;

	temp = (Position)malloc(sizeof(struct Node));
	if (temp == NULL) {
		printf("Critical ERROR!\n");
		exit(-1);
	}
	temp->element = X;
	temp->next = P->next;
	P->next = temp;

}

void DeletList(List L) {
	Position P, temp;
	P = L->next;
	L->next = NULL;
	while (P != NULL)
	{
		temp = P->next;
		free(P);
		P = temp;
	}
}



