#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EmptyTos (-1)

typedef struct Stack
{   int* key; 
	int top; 
	int max_stack_size;
}Stack;
Stack* CreateStack(int max); 
void Push(Stack* S, int X); 
int IsFull(Stack *S);



void main(int argc,char* argv[])
{
	FILE* fi = fopen(argv[1], "r");

	Stack * stack;
	char input_str[101];
	int max, i = 0, a, b, result=0;

	fgets(input_str, 101, fi);
	max = strlen(input_str);
	stack = CreateStack(max);
	while (input_str[i] != '#')
	{
		Push(stack, input_str[i]);
		
		i++;
	}
	
	fclose(fi);
	
}

Stack* CreateStack(int max)
{
	Stack * S = NULL;
	S = (Stack*)malloc(sizeof(max));
	S->key = (int*)malloc(sizeof(int)*max);
	S->max_stack_size = max;
	S->top = -1;
	return S;
}

void Push(Stack *S, int X) {
	if (IsFull(S)) {
		printf("ERROR!\n");
		exit(-1);
	}
	else {
		S->key[++S->top] = X;
		printf("%c inserted\n", X);
	}
}



int IsFull(Stack* S) {
	if (S->max_stack_size == S->top) 
		return 1;
	else
		return 0;
}
