#include<stdio.h>
#include<stdlib.h>

#define MULTX 99999 // �B��̰���Ƥ��\�� 

int digitCheck( int * ); // �P�_��ƨ禡 
void factorial( int * , int, int ); // �����禡 

int main(void)
{
	int a[MULTX];
	int multy, digitCount; // multy �Q�p�⪺�����ơAdigitCount ���
	
	do
	{
		printf("�п�J�A�Q�⪺�����ơ]�Y�����p��W�L %d ��Ʒ|�o�Ϳ��~�^: ", MULTX);
		scanf("%d", &multy);
		
		if( multy < 0 )
		{
			printf("�п�J�����\n");
			putchar('\n');
		}
		
	}while( multy < 0 );
	
	
	a[0] = 1;
	a[1] = -1; // -1 �N��w��F�Ʀr�̰����
	
	switch( multy ) // ���ƧP�_ 0! 1! �i������X 
	{
		case 0:
			printf("%d", a[0]);
				break;
			
		case 1: 
			printf("%d", a[0]);
				break;
				
		default:
			for( int counter = 2 ; counter <= multy ; counter++ ) // counter �O���� 
			{
				digitCount = digitCheck(a);
				factorial( a, counter, digitCount);
			}
			
			digitCount = digitCheck(a);
	
			if( digitCount <= MULTX )
				for( int i = digitCount-1 ; i >= 0 ; i--)
					printf("%d", a[i]);
			
			else
				printf("���~�G�B���ƶW�L�F %d �W��", MULTX);
	}
	
	printf("\n");
	
	system("pause");
	return 0;
}

int digitCheck( int *ptr )
{
	int digitCount = 0, digitMax = 0; // ��ơB�̰���� 
	
	while( digitMax != -1 )
	{
		digitCount++;
		digitMax = *(ptr+digitCount);
	}
	
	return digitCount;
}

void factorial( int *ptr, int counter, int max) // �Ʀr�B���ơB�̰���� 
{
	int store[MULTX];
	int digitUp = 0; // �T�{�O�_�i���̰���� 
	
	for( int i = 0 ; i < MULTX ; i++ ) // �N store �Ʀr�k�s 
		store[i] = 0;
	
	for( int i = 0 ; i < max ; i++ )
		store[i] = *(ptr+i); // store �x�s�Ʀr 
	
	for( int i = 1 ; i < counter ; i++ ) // �s�[ counter �� 
	{
		for( int j = 0 ; j < max ; j++ ) // ��Ƥ��i��[�k 
		{
			*(ptr+j) += *(store+j); 
			
			if( *(ptr+j) >= 10 ) // �i��B�� 
			{
				*(ptr+j) -= 10;
				
				if( *(ptr+j+1) == -1 ) // �i���̰���� 
				{
					*(ptr+j+2) = -1;
					*(ptr+j+1) = 1;
					digitUp = 1;
				}
				
				else
					*(ptr+j+1) += 1;
			}
		}
		
		if( digitUp ) // �i���A��ƭn������ 
		{
			max++;
			digitUp = 0;
		}
		
		if( max > MULTX )
			return;
	}
	
	return;
}
