#include<stdio.h>
#include<stdlib.h>

#define MAX 100001 // �}�C�`�ơA�h 1 �O���F�T�w������m 

void findPrime( int * );  // �M���� 

void output( int a[], int); // ��X 

void splitPrime( int a[], int result[] ); // �N�Ʀr���� 
short int palindromic( int ); // �M��j���� 

int main(void)
{ 
	int a[MAX-1], result[MAX]; // a ��Ʀs���m result �j���Ʀs���m 
	
	for( int i = 0 ; i < MAX ; i++ )
		result[i] = 0; // �N�Ʀr�k�s 
	
	printf("�p�� %d �ӽ�ơG\n", MAX-1);
	printf("�p�⤤�еy��\n");
	findPrime(a);
	output(a, 1);
	
	printf("\n");
	putchar('\n');
	
	puts("�j���ơG");
	splitPrime(a,result);
	output(result, 2);
	
	printf("\n");
	putchar('\n');
	
	system("pause");
	return 0;
}

int counter = 0; // �p���`�@��ƶq 

void findPrime( int *ptr )
{
	int flag = 0; // �P�_�O�_����� 
	
	*(ptr+0) = 2; // ��l�]�w�Ĥ@��m�� 2 
	counter++;
	
	*(ptr+1) = -1; // �Ʀr������m 
	
	for( int i = 3 ; i < 1e9 ; i++ )
	{
		flag = 1;
			
		for( int j = 0 ; *(ptr+j) < i && *(ptr+j) > 0 ; j++ ) // �P�_�Ʀr�O�_�Q��ƾ㰣 
		{
			if( i % *(ptr+j) == 0 ) // �㰣���O��� 
			{
				flag = 0;
				break;
			}
		}
			
		if( flag == 1 )
		{
			*(ptr+counter+1) = -1; // �����V��� 
			*(ptr+counter) = i; 
			counter++;
		}
			
		if( counter == MAX-1 ) // ��F�}�C�W�� break 
			break;
	}
}

void output( int a[MAX], int x )
{
	switch(x)
	{
		case 1:
			for( int i = 0 ; i < counter ; i++ )
				printf("%d ", a[i]);
					break;
			
		case 2:
			int i = 0;
			while( a[i] != 0 )
			{
				printf("%d ", a[i]);
				i++;
			}
					break;
	}
	return;
}

int splitTemp[50]; // �s����μƦr 

void splitPrime( int a[MAX], int result[MAX] )
{
	int digitCount, temp, resultInput = 0; // �p���ơB�s�񥿦b�p�⪺��ơBresult ���s��q 
	short int flag; // �P�_�O�_�j�� 
	
	for( int i = 0 ; i < MAX-1 ; i++ )
	{
		temp = a[i];
		digitCount = 0;
		flag = 0;  
		
		while( temp != 0 ) // ���Φs�� 
		{
			splitTemp[digitCount] = temp%10;
			temp /= 10;
			digitCount++;
		}
		
		if( digitCount%2 != 0 && digitCount > 2 ) // ��Ʃ_�Ƥ~����� 
			flag = palindromic(digitCount);
			
		if( flag || digitCount == 1 || a[i] == 11 ) // �j��s�� 
		{
			result[resultInput] = a[i];
			resultInput++;
		}
	}
	
	return;
}

short int palindromic( int digitCount )
{
	int middle = digitCount/2; // �p�⤤����� 
	
	for( int i = 0 ; i < middle ; i++ ) // �P�_�j�� 
	{
		if( splitTemp[i] != splitTemp[digitCount-1-i] )
			return 0;
	}
	
	return 1;
}
