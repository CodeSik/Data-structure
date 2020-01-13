#include <stdio.h>
#include <stdlib.h>

int main()
{
	int number,i;
	while (1) {
		scanf("%d", &number);
		if (number < 2)
			printf("Please input the number more than 2\n3");
		else
			break;

	}
	
	printf("enter %d names: \n",number);
	
	getchar();
	char c;
	char* name = (char*)malloc(30*number);
	fgets(name, 30 * number, stdin);
	printf("the names you enterd:\n");
	
	int checknum = 0;

	for (i = 0; i<30*number ; i++)
	{
		if (name[i] != ' ')
			printf("%c", name[i]);
		else if (name[i] == ' ')
		{
			checknum++;
			printf("\n");
		}

		if (name[i] == '\0')
			break;


		if (checknum == number)
		{
			printf("You entered over %d names. So program only prints %d names.", number,number);
			break;
		}
	}
	

	free(name);
}