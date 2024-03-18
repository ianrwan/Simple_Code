#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node
{
	int data;
	struct node *right, *left;
}TREE;

TREE *newNode(int data)
{
	TREE *ptr = (TREE*)malloc(sizeof(TREE));
	ptr->right = NULL;
	ptr->left = NULL;
	ptr->data = data;
	
	return ptr;
}

TREE *insertNode(TREE *node, int data)
{
	if( node == NULL )
	{
		node = newNode(data);
		printf("%p\n", node);	
	}
	else if( data < node->data )
		node->left = insertNode(node->left, data);
	else if( data > node->data )
		node->right = insertNode(node->right, data);
	return node;
}

void inorderNode(TREE *node)
{
	if( node != NULL )
	{
		inorderNode(node->left);
		printf("%d ", node->data);
		inorderNode(node->right);	
	}
	return;
}

void preorderNode(TREE *node)
{
	if( node != NULL )
	{
		printf("%d ", node->data);
		preorderNode(node->left);
		preorderNode(node->right);	
	}
	return;
}

void postorderNode(TREE *node)
{
	if( node != NULL )
	{
		postorderNode(node->left);
		postorderNode(node->right);
		printf("%d ", node->data);
	}
}

int main(void)
{
	int temp; 
	bool reverse = false;
	TREE *rootNode = NULL;
	rootNode = insertNode(rootNode, 2);
	for( int i = 0 ; i < 10 ; i++ )
	{
		temp = i;
		if( reverse )
			insertNode(rootNode, temp);
		else
			insertNode(rootNode, -temp);
		reverse = !reverse;
	}
	postorderNode(rootNode);
}
