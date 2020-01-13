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
	}
	else if (X > T->Element)
	{
	
		T->Right = Insert(X, T->Right);
	}
	else
	{
		printf("There is %d in the Tree\n", X);
	}
	T->Height = max(Height(T->Left), Height(T->Right)) + 1;
	return T;
}


int Height(Position P) { 
	if (P == NULL)       
		return -1 ;      
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
