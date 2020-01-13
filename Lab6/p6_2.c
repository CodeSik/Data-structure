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
Tree* deleteNode(int key, Tree* T);
void Finder(int key, Tree* T);
Tree* FindMin(Tree* T);
void printPreorder(Tree* T);
void printPostorder(Tree* T);
void printInorder(Tree* T);
void DeleteTree(Tree* T);
Tree* Deletion(int key, Tree* T);

int main()
{
	Tree* root = NULL;
	char cv;
	int key;
	FILE *fi = fopen("input_test.txt", "r");
	while (!feof(fi)) {
		fscanf(fi, "%c", &cv);
		switch (cv) {

		case 'i':
			fscanf(fi, "%d", &key);
			root = Insertion(key, root);
			break;
		case 'd':
			fscanf(fi, "%d", &key);
			Deletion(key,root);
			break;
		case 'f':
			fscanf(fi, "%d", &key);
			Finder(key, root);
			break;
		case'p':
			fscanf(fi, "%c", &cv);
			if (cv == 'i')
				printInorder(root);
			else if (cv == 'r')
				printPreorder(root);
			else if (cv == 'o')
				printPostorder(root);
			printf("\n");
			break;

		}
	}
	DeleteTree(root);
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

		printf("%d is not in the Tree\n", key);
	}
}

Tree* deleteNode(int key, Tree* T)
{
	Tree * tmp;
	if (T == NULL)
		printf("ERROR.\n");
	else if (key < T->value)
		T->left = deleteNode(key, T->left);
	else if (key >T->value)
		T->right = deleteNode(key, T->right);

	else if (T->left&&T->right) {

		tmp = FindMin(T->right);
		T->value = tmp->value;
		T->right = deleteNode(T->value, T->right);
	}

	else {

		tmp = T;
		if (T->left == NULL)
			T = T->right;
		else if (T->right == NULL)
			T = T->left;
		free(tmp);
	}
	
	return T;
}

Tree* Deletion(int key, Tree* T) {

	if (findNode(key, T) != NULL) {

		T = deleteNode(key, T);
		printf("Delete %d\n", key);
		
	}
	else {

		printf("Deletion Error: %d is not in the Tree.\n", key);
	}
	return T;
}

Tree* FindMin(Tree* T) {

	if (T == NULL) {
		printf("FindMin ERROR : No tree!\n");
	}
	else {
		while (T->left != NULL) {
			T = T->left;
		}
	}
	return T;
}

void printPreorder(Tree* T) {

	printf("%d ", T->value);
	if (T->left != NULL)
		printPreorder(T->left);
	if (T->right != NULL)
		printPreorder(T->right);
}
void printPostorder(Tree* T) {

	if (T->left != NULL)
		printPostorder(T->left);
	if (T->right != NULL)
		printPostorder(T->right);
	printf("%d ", T->value);
}
void printInorder(Tree* T) {

	if (T->left != NULL)
		printInorder(T->left);
	if (T->right != NULL) {
		printf("%d ", T->value);
		printInorder(T->right);
	}
	else
		printf("%d ", T->value);
}
void DeleteTree(Tree* T) {

	if (T->left != NULL)
		DeleteTree(T->left);
	if (T->right != NULL)
		DeleteTree(T->right);
	free(T);
}