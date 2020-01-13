#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Stack {
	int* key;
	int top;
	int max_stack_size;
}Stack;

Stack* CreateStack(int max);
void Push(Stack *S, int X);
int Pop(Stack* S);

void DeleteStack(Stack* S);
int IsEmpty(Stack* S);
int IsFull(Stack * S);
char Top(Stack* S);
	
void main()
{
	FILE* fi = fopen("lab5_input2.txt", "r");
	Stack* stack;
	char input_str[101];
	int max, i = 0, a, b, result;

	fgets(input_str, 101, fi);
	max = strlen(input_str);
	printf("Pushed numbers :");

	stack = CreateStack(max);

	while (input_str[i] != '#')
	{
		if (input_str[i] == '+')
		{
			a = Pop(stack);
			b = Pop(stack);
			Push(stack, b+a);
			printf(" %d", stack->key[stack->top]);
		}
		else if (input_str[i] == '%')
		{
			a = Pop(stack);
			b = Pop(stack);
			Push(stack, b%a);
			printf(" %d", stack->key[stack->top]);
		}
		else if (input_str[i] == '*')
		{
			a = Pop(stack);
			b = Pop(stack);
			Push(stack, b*a);
			printf(" %d", stack->key[stack->top]);
		}
		else if (input_str[i] == '/')
		{
			a = Pop(stack);
			b = Pop(stack);
			Push(stack, b /a);
			printf(" %d", stack->key[stack->top]);
		}

		else if (input_str[i] == '-')
		{
			a = Pop(stack);
			b = Pop(stack);
			Push(stack, b -a);
			printf(" %d", stack->key[stack->top]);
		}
		else {
			Push(stack, (int)input_str[i]-48);
			printf(" %d", stack->key[stack->top]);
		}
		i++;
	}
	result = Pop(stack);
	printf("\nevaluatuon result: %d\n", result);
	fclose(fi);
	DeleteStack(stack);
	
}

Stack* CreateStack(int max)
{
	Stack* S = NULL;
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
	}
}

int Pop(Stack* S)
{
	if (IsEmpty(S)) {
		printf("ERROR!\n");
		exit(-1);
	}
	else
	{
		
		return S->key[S->top--];
	}
}

int IsFull(Stack* S) {
	if (S->max_stack_size == S->top)
		return 1;
	else
		return 0;
}

int IsEmpty(Stack* S) {
	if (S->top == -1) 
		return 1;
	else 
		return 0;
}

char Top(Stack* S) {
	if (IsEmpty(S)) {
		printf("ERROR!\n");
		exit(-1);
	}
	else 
		return S->key[S->top];
}

void DeleteStack(Stack* S)
{
	free(S->key);
	free(S);	
}

