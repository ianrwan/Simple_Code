#include<stdio.h>
#include<stdlib.h>

#define MULTX 99999 // 笲衡程蔼计す砛 

int digitCheck( int * ); // 耞计ㄧΑ 
void factorial( int * , int, int ); // 顶ㄧΑ 

int main(void)
{
	int a[MULTX];
	int multy, digitCount; // multy 稱璸衡顶计digitCount 计
	
	do
	{
		printf("叫块稱衡顶计璝顶璸衡禬筁 %d 计穦祇ネ岿粇: ", MULTX);
		scanf("%d", &multy);
		
		if( multy < 0 )
		{
			printf("叫块タ俱计\n");
			putchar('\n');
		}
		
	}while( multy < 0 );
	
	
	a[0] = 1;
	a[1] = -1; // -1 笷计程蔼计
	
	switch( multy ) // 顶计耞 0! 1! 钡块 
	{
		case 0:
			printf("%d", a[0]);
				break;
			
		case 1: 
			printf("%d", a[0]);
				break;
				
		default:
			for( int counter = 2 ; counter <= multy ; counter++ ) // counter 琌顶计 
			{
				digitCount = digitCheck(a);
				factorial( a, counter, digitCount);
			}
			
			digitCount = digitCheck(a);
	
			if( digitCount <= MULTX )
				for( int i = digitCount-1 ; i >= 0 ; i--)
					printf("%d", a[i]);
			
			else
				printf("岿粇笲衡计禬筁 %d ", MULTX);
	}
	
	printf("\n");
	
	system("pause");
	return 0;
}

int digitCheck( int *ptr )
{
	int digitCount = 0, digitMax = 0; // 计程蔼计 
	
	while( digitMax != -1 )
	{
		digitCount++;
		digitMax = *(ptr+digitCount);
	}
	
	return digitCount;
}

void factorial( int *ptr, int counter, int max) // 计顶计程蔼计 
{
	int store[MULTX];
	int digitUp = 0; // 絋粄琌秈程蔼计 
	
	for( int i = 0 ; i < MULTX ; i++ ) // 盢 store 计耴箂 
		store[i] = 0;
	
	for( int i = 0 ; i < max ; i++ )
		store[i] = *(ptr+i); // store 纗计 
	
	for( int i = 1 ; i < counter ; i++ ) // 硈 counter Ω 
	{
		for( int j = 0 ; j < max ; j++ ) // 计ず秈︽猭 
		{
			*(ptr+j) += *(store+j); 
			
			if( *(ptr+j) >= 10 ) // 秈笲衡 
			{
				*(ptr+j) -= 10;
				
				if( *(ptr+j+1) == -1 ) // 秈程蔼计 
				{
					*(ptr+j+2) = -1;
					*(ptr+j+1) = 1;
					digitUp = 1;
				}
				
				else
					*(ptr+j+1) += 1;
			}
		}
		
		if( digitUp ) // 秈计璶暗э跑 
		{
			max++;
			digitUp = 0;
		}
		
		if( max > MULTX )
			return;
	}
	
	return;
}
