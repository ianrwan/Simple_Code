#include<stdio.h>
#include<stdlib.h>

#define MAX 6

int main(void)
{
	int a[MAX], temp, flag = 0;
	
	for( int i = 0 ; i < MAX ; i++ )
		scanf("%d", &a[i]);
		
	for( int i = 1 ; i <= MAX-1 ; i++ )
	{
		flag = 0;
		for( int j = 0 ; j < MAX-i ; j++ )
		{
			if( a[j] > a[j+1])
			{
				temp = a[j+1];
				a[j+1] = a[j];
				a[j] = temp;
				
				flag = 1;
			}
		}
		
		for( int i = 0 ; i < MAX ; i++ )
		{
			printf("%d ", a[i]);
		}		
		printf("\n");
		
		if( !flag )
			break;
	}
}
