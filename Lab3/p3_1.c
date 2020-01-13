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
	list = MakeEmpty(list); //노드생성
	FILE *fi;// 파일 입출력을 위함
	fi = fopen(argv[1], "r"); //콘솔에서 입력받음
	char option;// 옵션 입력 구분을 위함
	int x, y; //노드의 위치와 값 저장을 위한 변수

	while (fscanf(fi, "%c %d %d", &option, &x, &y) != EOF) //파일이 끝날 때 까지 돌림
	{
		if (option == 'i') //입력
		{
			Insert(x, list, list);

		}
		if (option == 'p') //프린트
		{
			PrintList(list);
		}

		fscanf(fi, "%c %d %d", &option, &x, &y); //계속해서 값을 입력 받음
	}

}

List MakeEmpty(List L) //노드 만들기
{
	L->element = 0;
	L->next = NULL;
	return L;
}

int IsEmpty(List L) //비었는지 확인
{
	return L->next == NULL;
}

int IsLast(Position P, List L) //마지막인지 확인
{
	return P->next == NULL;
}

void Insert(ElementType X, List L, Position P)
{
	Position TmpCell; //임시 노드를 만듬 (입력할 노드)
	TmpCell = malloc(sizeof(struct Node));
	if (TmpCell == NULL) 
		printf("Out of space!");

	TmpCell->element = X;// 값 저장
	TmpCell->next = P->next; //입력받은 노드의 다음을 지정
	P->next = TmpCell;

}

void PrintList(List L)// 프린트 함수
{
	List temp = L;
	int prenode; // 그전 노드의 element값 저장
	temp = temp->next;//head 앞쪽으로 먼저 이동
	printf("Key of the previous node of %d is header\n", temp->element);

	while (temp->next != NULL)
	{
		prenode = temp->element;
		temp = temp->next; //쭉 이동하면서 프린트해줌.
		printf("Key of the previous node of %d is %d\n", temp->element, prenode);

	}
	printf("End of the list.\n");
}
