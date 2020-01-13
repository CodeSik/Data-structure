#include <stdio.h>
#include <stdlib.h>



typedef struct Tree {

	int value;
	struct Tree* left;
	struct Tree* right;
}Tree;

Tree* findNode(int key, Tree* T);
Tree* insertNode(int key, Tree* T);
Tree* Insertion(int key, Tree* T);
void Finder(int key, Tree* T);


int main(int argc , char* argv[])
{
	Tree* T = NULL;
	char cv;
	int key;
	FILE *fi = fopen( argv[1], "r");
	while (!feof(fi)) {
		fscanf(fi, "%c", &cv);
		switch (cv) {

		case 'i':
			fscanf(fi, "%d", &key);
			T = Insertion(key, T);
			break;
		case 'f':
			fscanf(fi, "%d", &key);
			Finder(key, T);
			break;
		
		}
	}
}

Tree * findNode(int key, Tree* T) {

	if (T == NULL)
		return NULL;

	if (key < T->value)
		return findNode(key, T->left);
	else if (key>T->value)
		return findNode(key, T->right);
	else
		return T;
}

Tree* insertNode(int key, Tree* T) {

	if (T == NULL) {

		T = malloc(sizeof(Tree));
		if (T == NULL) {

			printf("Out of space!!!");
			return 0;
		}
		else {

			T->value = key;
			T->left = NULL;
			T->right = NULL;
		}
	}
	else if (key < T->value) {
		T->left = insertNode(key, T->left);
	}
	else if (key > T->value) {
		T->right = insertNode(key, T->right);
	}
	return T;
}

Tree* Insertion(int key, Tree* T) {

	if (findNode(key, T) != NULL) {

		printf("Insertion Error: There is already %d in the Tree.\n", key);
	}
	else {

		T = insertNode(key, T);
		printf("insert %d\n", key);
	}
	return T;
}
void Finder(int key, Tree* T) {

	if (findNode(key, T) != NULL) {

		printf("%d is in the Tree\n", key);
	}
	else {

		printf("%d is not in the Tree\n",key);
	}
}
