#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#define MAX 5

int main(void)
{
	int a[MAX], findSmall, temp, k = 0;
	for( int i = 0 ; i < MAX ; i++ )
		scanf("%d", &a[i]);
		
	for( int i = 1 ; i <= MAX-1 ; i++ )
	{
		findSmall = k;
		for( int j = k ; j < MAX ; j++ )
		{
			if(a[j] < a[findSmall])
			{
				findSmall = j;
			} 
		}
		
		temp = a[k];
		a[k++] = a[findSmall];
		a[findSmall] = temp;
		
		for( int j = 0 ; j < MAX ; j++ )
		{
			printf("%d ", a[j] );
		}
		printf("\n");
	}
	
	system("pause");
	return 0;
}
