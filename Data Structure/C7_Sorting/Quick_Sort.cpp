#include<stdio.h>
#include<stdlib.h>

int max;
void arrayOutput(int *data)
{
	for( int i = 0 ; i < max ; i++ )
	{
		printf("%d ", data[i]);
	}
	printf("\n");
}

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int partition(int *data, int front, int end)
{
	int j = front;
	for(int i = front+1 ; i <= end ; i++)
	{
		if(data[i] >= data[front])
			continue;
		
		j++;
		swap(data+i, data+j);
	}
	swap(data+front, data+j);
	return j;
}

void quickSort(int *data, int front, int end)
{
	if(front >= end)
		return;	
	arrayOutput(data);
	int pivot = partition(data, front, end);
	quickSort(data, front, pivot-1);
	quickSort(data, pivot+1, end);	
} 

int main(void)
{
	printf("Please enter array count: ");
	scanf("%d", &max);
	int data[max];
	
	printf("Please enter num in array: ");
	for( int i = 0 ; i < max ; i++)
	{
		scanf("%d", &data[i]);
	}
	quickSort(data, 0, max-1);
	arrayOutput(data);
	
	system("pause");
}
