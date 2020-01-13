#include <stdio.h>
#include <stdlib.h>

#define max(a,b)    (((a) > (b)) ? (a) : (b))

struct AVLNode;
typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;
typedef int ElementType;

struct AVLNode
{
	ElementType Element;
	AVLTree Left;
	AVLTree Right;
	int Height;
};

AVLTree Insert(ElementType X, AVLTree T);
void PrintInorder(AVLTree T);

Position SingleRotateWithLeft(Position node);
Position SingleRotateWithRight(Position node);
static Position DoubleRotateWithLeft(Position node);
static Position DoubleRotateWithRight(Position node);

int Height(Position P);


void main(int argc, char* argv[]) {

	FILE *fp = fopen(argv[1], "r");
	AVLTree myTree = NULL;
	int element;

	while (fscanf(fp, "%d", &element) != EOF)
	{
		myTree = Insert(element, myTree);
		PrintInorder(myTree);
		printf("\n");
	}

	//Delete Tree 
	fclose(fp);
}

AVLTree Insert(ElementType X, AVLTree T)
{

	if (T == NULL)
	{
		T = (AVLTree)malloc(sizeof(struct AVLNode));
		if (T == NULL)
		{
			printf("Error.");
			exit(1);
		}
		else
		{
			T->Element = X;
			T->Left = T->Right = NULL;
			T->Height = 0;
		}
	}

	else if (X < T->Element)
	{
		T->Left = Insert(X, T->Left);
		if (Height(T->Left) - Height(T->Right) == 2) {
			if (X < T->Left->Element)
				T = SingleRotateWithLeft(T);
			else
				T = DoubleRotateWithLeft(T);
		}

	}
	else if (X > T->Element)
	{
		T->Right = Insert(X, T->Right);
		if (Height(T->Right) - Height(T->Left) == 2) {
			if (X > T->Right->Element)
				T = SingleRotateWithRight(T);
			else
				T = DoubleRotateWithRight(T);
		}
	}
	else
	{
		;
	}
	T->Height = max(Height(T->Left), Height(T->Right)) + 1;
	return T;
}


int Height(Position P) {
	if (P == NULL)
		return -1;
	else
		return P->Height;
}


void PrintInorder(AVLTree T)
{
	if (T == NULL)
		return;

	PrintInorder(T->Left);
	printf("%d(%d) ", T->Element, T->Height);
	PrintInorder(T->Right);
}

Position  SingleRotateWithLeft(Position K2)   /* LL */ 
{
	Position K1;
	K1 = K2->Left; 
	K2->Left = K1->Right;             /* Y */   
	K1->Right = K2;
	K2->Height = max(Height(K2->Left), Height(K2->Right)) + 1;  
	K1->Height = max(Height(K1->Left), K2->Height) + 1;
	return K1;                               /* New root */
}

Position SingleRotateWithRight(Position K2)
{
	Position K1;
	K1 = K2->Right;
	K2->Right = K1->Left;
	K1->Left = K2;
	K2->Height = max(Height(K2->Right), Height(K2->Left)) + 1;
	K1->Height = max(Height(K1->Right), K2->Height) + 1;
	return K1;
}


static Position DoubleRotateWithLeft(Position K3)    /*LR */ 
{	/* rotate between K1 and K2  */  
	K3->Left = SingleRotateWithRight(K3->Left);
	/* k2 */
	/* rotate between K3 and K2   */ 
	return SingleRotateWithLeft(K3);                     /* K2  */
}

static Position DoubleRotateWithRight(Position K3)
{
	K3->Right = SingleRotateWithLeft(K3->Right);

	return SingleRotateWithRight(K3);
}
