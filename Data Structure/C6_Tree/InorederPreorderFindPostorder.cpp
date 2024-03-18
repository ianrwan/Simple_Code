#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define MAX 50

char preorderList[MAX];
char inorderList[MAX];

typedef struct node
{
	char value;
	struct node *right, *left;
}TREE;

TREE *createNode(int nodeValue)
{
	TREE *newNode = (TREE*)malloc(sizeof(TREE));
	newNode->value = nodeValue;
	newNode->right = NULL;
	newNode->left = NULL;
	
	return newNode;
}

int findInorderRoot(char value, char *data)
{
	int i = 0;
	while( data[i] != value )
	{
		i++;
	}
	return i;
}

TREE *createTree(TREE *father, char *preorderSub, char *inorderSub)
{
	char nodeValue = preorderSub[0];
	char *leftPre = NULL, *leftIn = NULL, *rightPre = NULL, *rightIn = NULL;
	
	if( father == NULL )
	{
		father = createNode(nodeValue);
	}
	
	int rootInPos;
	rootInPos = findInorderRoot(nodeValue, inorderSub);
//	printf("%d\n", rootInPos);
	
	if( rootInPos != 0 )
	{
		leftPre = (char*)malloc(sizeof(char)*rootInPos);
		leftIn = (char*)malloc(sizeof(char)*rootInPos);
		for( int i = 0 ; i < rootInPos ; i++ )
		{
			leftPre[i] = preorderSub[i+1];
			leftIn[i] = inorderSub[i];
		}
		leftPre[rootInPos] = '\0';
		leftIn[rootInPos] = '\0';
		
		father->left = createTree(father->left, leftPre, leftIn);
	}
	
	if( rootInPos != strlen(preorderSub)-1 )
	{
		rightPre = (char*)malloc(sizeof(char)*(strlen(preorderSub)-rootInPos));
		rightIn = (char*)malloc(sizeof(char)*strlen(preorderSub)-rootInPos);
		
		rightPre[strlen(preorderSub)-rootInPos-1] = '\0';
		rightIn[strlen(preorderSub)-rootInPos-1] = '\0';
		for( int i = strlen(preorderSub)-1, j = strlen(preorderSub)-rootInPos-2 ; i > rootInPos ; i--, j-- )
		{
			rightPre[j] = preorderSub[i];
			rightIn[j] = inorderSub[i];
		}
		
		father->right = createTree(father->right, rightPre, rightIn);
	}
	free(preorderSub);
	free(inorderSub);
	
//	printf("%s %s %s %s\n", leftPre, leftIn, rightPre, rightIn);
	
	return father;
}

void treePostorder(TREE *ptr)
{
	if( ptr != NULL )
	{
		treePostorder(ptr->left);
		treePostorder(ptr->right);
		printf("%c", ptr->value);
	}
}

int main(void)
{	
	printf("Please enter characters.\n");
	printf("For Example: BAGHCDIJK.\n");
	printf("Please enter preorder list: ");
	scanf("%s", preorderList);
	printf("Please enter inorder list: ");
	scanf("%s", inorderList);
	
	TREE *treePtr = NULL;
	char *treePre = (char*)malloc((sizeof(char)*strlen(preorderList+1))), *treeIn = (char*)malloc((sizeof(char)*strlen(preorderList+1)));
	strcpy(treePre, preorderList);
	strcpy(treeIn, inorderList);
	
	treePtr = createTree(treePtr, treePre, treeIn);
	printf("Postorder result: ");
	treePostorder(treePtr);
	printf("\n");
	
	system("pause");
}
