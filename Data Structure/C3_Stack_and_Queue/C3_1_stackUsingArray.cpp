#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h> 

#define MAX 100
#define VALID_WORDS_NUM 5 

typedef struct
{
	int key;
}stack;

stack stack1[MAX];
int top = -1;

void push( stack *ptr )
{
	printf("Please enter the element you wanna input: ");
	int element;
	scanf("%d", &element);

	stack1[++top].key = element;	
}

void pop( stack *ptr )
{
	printf("%d\n", stack1[top--].key);
}

void empty( stack *ptr )
{
	top = -1;
}

void traverse( stack *ptr )
{
	for( int i = 0 ; i <= top ; i++ )
		printf("%d ", (stack1+i) -> key );
}

int main(void)
{
	char typeIn[10];
	char *validInput[VALID_WORDS_NUM] = {"push", "pop", "empty", "traverse", "end"};
	int inputWordNum;
	bool isValidInputWord = false, isEnd = false;

	do
	{
		printf("Please enter your instruction.\n");
		fflush(stdin);
		gets(typeIn);

		for( int i = 0 ; i < VALID_WORDS_NUM ; i++ )
		{
			if( strcmp( typeIn, validInput[i] ) == 0 )
			{
				isValidInputWord = true;
				inputWordNum = i;
				break;
			}
		}

		if( isValidInputWord )
		{
			switch(inputWordNum)
			{
				case 0:
					if( top < MAX )
						push(stack1);
					else
						printf("You can't push the element when the stack is full.\n");
						break;
				case 1:
					if( top > -1 )
						pop(stack1);
					else
						printf("You can't pop the element when nothing in the stack.\n");
						break;
				case 2:
					if( top > -1 )
						empty(stack1);
					else
						printf("You can't empty the stack when nothing in the stack.\n");
						break;
				case 3:
					if( top > -1 )
					{
						traverse(stack1);
						putchar('\n');						
					}
					else
						printf("There is nothing in the stack.\n");
						break;
				case 4:
					isEnd = 1;
					break;
			}
		}
	}while( !isEnd );
	return 0;
}
