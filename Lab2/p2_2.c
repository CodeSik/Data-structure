#include <stdio.h>



int main()
{
	printf("enter your name:\n");
	char* name[30];
	gets(name);
	printf("your name is ");
	puts(name);
}