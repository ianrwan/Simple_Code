#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"headFile/stack.h"

#define MAX 102

int checkOperator( char x )
{
	if( x == '(')
		return 0;
	else if( x == '+' || x == '-')
		return 1;
	else if( x == '*' || x == '/')
		return 2;
	return 0;
}

int main(void)
{ 
	STACK *store = createStack();
	char oper[MAX], result[MAX];
	char temp;
	int i = 0, count = 0;
	
	puts("The input of the example: a+b*c or (a+b)*(c+d)");
	puts("The input operands need to be English alphabets");
	printf("Please enter your operation( it can only input %d characters.): ", MAX-2);
	do
	{
		gets(oper);
		if( strlen(oper) > 100 )
		{
			printf("The chracter amounts is over %d, please enter again.", MAX-2);
			fflush(stdin);
		}
	}while( strlen(oper) > 100 );
	
	
	while( oper[i] != '\0' )
	{
		if( isalpha(oper[i]) )
			result[count++] = oper[i];
		else if( oper[i] == '(')
			push(store, oper[i]);
		else if( oper[i] == ')')
		{
			temp = '0';
			while( temp != '(')
			{
				temp = pop(store);
				if( temp != '(')
					result[count++] = temp;
			}
		}
		else
		{
			while( checkOperator((store->top != NULL) ? store->top->key : '0') >= checkOperator(oper[i]))
				result[count++] = pop(store);
			push(store, oper[i]);
		}
		i++;
	}
	
	while( store->top != NULL )
	{
		result[count++] = pop(store);
	}
	result[count++] = '\0';
	printf("%s\n", result);
	
	system("pause");
	return 0;
}
