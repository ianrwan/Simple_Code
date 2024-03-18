#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int counter = 0, total = 0;

typedef struct node
{
	int data;
	int bf, leftHeight, rightHeight;
	struct node *right, *left;
}TREE;

// 建立新節點 
TREE *newNode(int value)
{
	TREE *ptr = (TREE*)malloc(sizeof(TREE));
	ptr->right = NULL;
	ptr->left = NULL;
	ptr->data = value;
	ptr->leftHeight = 0;
	ptr->rightHeight = 0;
	ptr->bf = ptr->leftHeight-ptr->rightHeight;
	
	return ptr;
}

// 建樹 
TREE *treeCreate(TREE *node, int value)
{
	if( node == NULL )
	{
		node = newNode(value);
		return node;
	}	
	if( value < node->data )
	{
		node->left = treeCreate(node->left, value);
	}
	else if( value > node->data )
	{
		node->right = treeCreate(node->right, value);
	}
}

// 計算節點與總和 
void inorderTree( TREE *node )
{
	if( node != NULL )
	{
		inorderTree(node->left);
		printf("%5d %2d\n", node->data, node->bf);
		inorderTree(node->right);
		
		counter++;
		total += node->data;
	}
}

// 計算 BF  
int calculateBF( TREE *node )
{
	if( node == NULL )
		return 0;
		
	int leftHeight, rightHeight;
	leftHeight = calculateBF(node->left); 
	rightHeight = calculateBF(node->right);
	
	node->leftHeight = leftHeight;
	node->rightHeight = rightHeight;
	node->bf = leftHeight-rightHeight;
	
	if( leftHeight >= rightHeight )
		return leftHeight+1;
	else
		return rightHeight+1; 
}

// 左右子樹交換 拷貝 
TREE *cloneTree( TREE *node, TREE *newNode)
{
	if( node->right == NULL )
		newNode->left = NULL;
	else
		newNode->left = (TREE*)malloc(sizeof(TREE));
	if( node->left == NULL )
		newNode->right = NULL;
	else
		newNode->right = (TREE*)malloc(sizeof(TREE));
	
	newNode->data = node->data;
	newNode->leftHeight = node->leftHeight;
	newNode->rightHeight = node->rightHeight;
	newNode->bf = node->bf;
	
	return newNode;
}

// 左右子樹交換 
TREE *reverseTree( TREE *node, TREE *newNode)
{	
	if( node != NULL )
	{
		cloneTree(node, newNode);
		reverseTree(node->left, newNode->right);
		reverseTree(node->right, newNode->left);	
	}
}

int main(void)
{
	int temp = 0;
	bool end = false;
	TREE *node = NULL, *reverse = (TREE*)malloc(sizeof(TREE));
	
	printf("Please enter 0 to end up the input.( Each numbers should be different number )\n");
	printf("For example: 10 5 8 4 3 80 0\n");
	printf("Your enter: ");
	scanf("%d", &temp);
	node = treeCreate(node, temp);
	while( !end )
	{
		scanf("%d", &temp);
		if( temp == 0)
			end = true;
		if( !end )
			treeCreate(node, temp);
	} 
	
	calculateBF(node);
	reverseTree(node, reverse);
	printf("VALUE BF\n");
	inorderTree(node);
	printf("\nThe binary tree has %d nodes, and the sum is %d.\n", counter, total);
	printf("\nThe result of the reversed tree:\n");
	printf("VALUE BF\n");
	inorderTree(reverse);
	
	system("pause");
	return 0;
}
