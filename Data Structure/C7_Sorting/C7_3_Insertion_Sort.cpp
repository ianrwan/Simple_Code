#include<stdio.h>
#include<stdlib.h>

#define MAX 5

typedef struct node
{
	int key;
	struct node *next;
}ELEMENT;

//make a link and put the value inside it
ELEMENT *createLink(void)
{
	ELEMENT *current, *previous, *first;
	
	for( int i = 0 ; i < MAX ; i++ )
	{
		current = (ELEMENT*)malloc(sizeof(ELEMENT));
		scanf("%d", &(current->key));
		
		if( i==0 )
			first = current;
		else
			previous->next = current;
		previous = current;
		current->next = NULL;
	}
	
	return first;
}

void outputLink( ELEMENT *first )
{
	ELEMENT *current = first;
	int i = 0;
	
	while( current != NULL )
	{
		if( i==0 )
			current = first;
		else
			current = current->next;
		
		if( current != NULL )	
			printf("%d ", current->key);
		i++;
	}
	
	return;
}

void insertion( ELEMENT *first )
{
//	current is the node which needs to be compared
//	front is the front of the new linked list
//	rear is the rear of the new linked list
//	tempCurrent is the node which needs to compares with current
//	tempPrevious is the node which was just compared before tempCurrent  
	ELEMENT *current, *front, *rear, *tempCurrent, *tempPrevious;
	
//	isSort checks if the list is already ordered
	
	current = first;
	first = first->next;
	current->next = NULL;
	front = current;
	rear = front;
	
	for( int i = 1 ; i < MAX ; i++ )
	{
		current = first;
		first = first->next;
		
		if( current->key <= front->key )
		{
			current->next = front;
			front = current;
		}
		else if( current->key > rear->key )
		{
			rear->next = current;
			rear = current;
			rear->next = NULL;
		}
		else
		{
			tempCurrent = front->next;
			tempPrevious = front;
			for( int j = 1 ; j < i ; j++ )
			{
				if( current->key <= tempCurrent->key )
				{
					current->next = tempCurrent;
					tempPrevious->next = current;
					break;
				}
				tempCurrent = tempCurrent->next;
				tempPrevious = tempPrevious->next;
			}
		}
		outputLink(front);
		outputLink(first);
		printf("\n");
	}
}

int main(void)
{
	ELEMENT *link1;
	printf("Please %d numbers: ", MAX);
	link1 = createLink();
	printf("This is your input: ");
	outputLink(link1);
	printf("\n");
	putchar('\n');
	
	insertion(link1);
	
	system("pause");
	return 0;
}
