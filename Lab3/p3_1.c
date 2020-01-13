#include <stdio.h>
#include <stdlib.h>

typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;
struct Node
{
	ElementType element;
	Position	next;
};

List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
void Insert(ElementType X, List L, Position P);
void PrintList(List L);

int main(int argc, char** argv)
{
	List list = (List)malloc(sizeof(struct Node));
	list = MakeEmpty(list); //������
	FILE *fi;// ���� ������� ����
	fi = fopen(argv[1], "r"); //�ֿܼ��� �Է¹���
	char option;// �ɼ� �Է� ������ ����
	int x, y; //����� ��ġ�� �� ������ ���� ����

	while (fscanf(fi, "%c %d %d", &option, &x, &y) != EOF) //������ ���� �� ���� ����
	{
		if (option == 'i') //�Է�
		{
			Insert(x, list, list);

		}
		if (option == 'p') //����Ʈ
		{
			PrintList(list);
		}

		fscanf(fi, "%c %d %d", &option, &x, &y); //����ؼ� ���� �Է� ����
	}

}

List MakeEmpty(List L) //��� �����
{
	L->element = 0;
	L->next = NULL;
	return L;
}

int IsEmpty(List L) //������� Ȯ��
{
	return L->next == NULL;
}

int IsLast(Position P, List L) //���������� Ȯ��
{
	return P->next == NULL;
}

void Insert(ElementType X, List L, Position P)
{
	Position TmpCell; //�ӽ� ��带 ���� (�Է��� ���)
	TmpCell = malloc(sizeof(struct Node));
	if (TmpCell == NULL) 
		printf("Out of space!");

	TmpCell->element = X;// �� ����
	TmpCell->next = P->next; //�Է¹��� ����� ������ ����
	P->next = TmpCell;

}

void PrintList(List L)// ����Ʈ �Լ�
{
	List temp = L;
	int prenode; // ���� ����� element�� ����
	temp = temp->next;//head �������� ���� �̵�
	printf("Key of the previous node of %d is header\n", temp->element);

	while (temp->next != NULL)
	{
		prenode = temp->element;
		temp = temp->next; //�� �̵��ϸ鼭 ����Ʈ����.
		printf("Key of the previous node of %d is %d\n", temp->element, prenode);

	}
	printf("End of the list.\n");
}
