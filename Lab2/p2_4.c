#include <stdio.h>

void swap(int *num1, int *num2)
{
	int temp;
	temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}



int main()
{
	printf("enter 2 integers\n");
	int num1;
	int num2;
	scanf("%d", &num1);
	scanf("%d", &num2);
	printf("you entered %d %d \n", num1, num2);
	int* pt_num1;
	int* pt_num2;
	pt_num1 = &num1;
	pt_num2 = &num2;

	printf("after swapping ");
	swap(pt_num1, pt_num2);
	printf("%d, %d", num1, num2);

}