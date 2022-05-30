#include<stdio.h>
#include<stdlib.h>

#define MAX 30000 // 借计皚羆秖 
#define DIGITMAX 10 // 计だ澄皚羆秖 
#define RIGHTMAX 200 // 篒祏皚羆秖 
#define LEFTMAX 1000 // オ篒祏ㄧΑ羆秖 

void findPrime( int a[] ); // т借计ㄧΑ 
int primeCheck( int ); // オ篒祏借计т碝ㄧΑ 

void primeOut( int a[], int ); // 块ㄧΑ 

void digitSplit( int a[], int digitDis[] ); // 盢借计秈︽计だ澄ㄧΑ 
int truncatablePrimeLeft( int digitDis[], int ); // オ篒祏借计ㄧΑ 
int truncatablePrimeRight( int * , int , int * ); // 篒祏借计ㄧΑ 

int left[LEFTMAX], right[RIGHTMAX]; // オ篒祏ㄧΑ皚篒祏ㄧΑ皚 

int main(void)
{
	int a[MAX], digitDis[DIGITMAX]; // 羆借计皚计だ澄皚 
	
	printf("笲衡い叫祔\n");
	
	printf("30000 借计い碝тオ篒祏借计\n");
	findPrime(a);
	/*
	primeOut(a, 1);
	*/
	printf("\n");
	putchar('\n');
	
	digitSplit(a, digitDis);
	
	printf("篒祏借计\n");
	primeOut(right, 2);
	
	printf("\n");
	putchar('\n');
	
	printf("オ篒祏借计\n");
	primeOut(left, 3);
	
	printf("\n");
	puts("籓い毙▅厩_窾甪蝴_级糶\n");
	
	putchar('\n');
	
	system("pause");
	return 0;
}

int counter = 0; // 璸衡借计璸计竟 

/* ﹍т碝借计ㄧΑ */ 
void findPrime( int a[] )
{
	int flag = 1, j = 2; // flag to check if the number is prime, flag = 1 is prime 
	
	for( int i = 2 ; i <= 1e9 ; i++ ) // i mod j
	{
		for( int j = 2 ; j < i ; j++ )
		{
			flag = 1;
			
			if( i%j == 0 ) // i mod j = 0 means i isn;t a prime, so break
			{
				flag = 0;
				break;
			}
		}
		
		if( flag == 1 )
		{
			a[counter] = i;
			counter++;
		}
		
		if( counter == MAX ) // if counter is over the array index, findprime func stops 
			break;
	}
	
	return;
}

/* 癸オ篒祏借计ぇ耞ㄧΑ */ 
int primeCheck( int a )
{
	int flag;
	
	for( int i = 2 ; i < a || a == 1 ; i++ )
	{
		flag = 1;
		
		if( a%i == 0 || a == 1 ) // 1 isn't prime
		{
			flag = 0;
			return 0;
		}
	}
	
	if( flag == 1 )
	{
		return a;
	}
}

/* 借计块 */ 
void primeOut( int a[], int ins )
{
	int x;
	
	switch(ins) // check which prime will be output
	{
		case 1:
			x = counter;
				break;
				
		case 2:
			x = RIGHTMAX;
				break;
		
		case 3:
			x = LEFTMAX;
				break;
	}
	
	for( int i = 0 ; i < x ; i++ )
	{
		if( a[i] == 0 ) // if the a[i] = 0, it means there is no number inside the array, break
			break;
		
		printf("%d ", a[i]);
	}
	return;
}

/* 盢计秈︽计だ澄ㄧΑ */ 

void digitSplit( int a[], int digitDis[] )
{
	int flag = 1, countDig = 0, origin, leftBool, rightBool; 
	int countRight = 0, countLeft = 0;
	
	for( int i = 0 ;  i < counter ; i++ )
	{
		origin = a[i]; // let the original number gives to origin
		
		do // try to split the number to each digit
		{
			flag = origin/10; // flag stores other digits
			digitDis[countDig] = origin-flag*10; // origin-flag can get one digit
			origin = flag; // origin will refresh to flag
			
			countDig++; // countDig is the counter of digits
			
		}while( flag > 0 ); // flag < 0 means all the digits is splitted 
		
		
		leftBool = truncatablePrimeLeft( digitDis, countDig ); //  耞ヘ玡计琌琌オ篒祏借计leftBool = 0 琌 
		
		if( leftBool ) // 盢オ篒祏借计纗皚 
		{
			left[countLeft] = a[i];
			countLeft++;
		}
		
		rightBool = truncatablePrimeRight( digitDis, countDig, &a[i] ); //  耞ヘ玡计琌琌篒祏借计rightBool 琌 
		
		if( rightBool ) // 盢篒祏借计纗皚  
		{
			right[countRight] = a[i];
			countRight++;
		}
		
		countDig = 0; // let countDig retrieve initiality 
	}
}

/*
だ澄计纗皚穦は筁ㄓ 
计233
皚いa[0] = 3, a[1] = 3, a[2] = 2
*/ 

/* オ篒祏借计ㄧΑ */ 
int truncatablePrimeLeft( int digitDis[] , int countDig )
{
	int times = 1, x = 0; // times ノㄓ璸衡计 1 10... 
	
	for( int i = 0 ; i < countDig-1 ; i++ ) // ノㄓ浪琩琌オ篒祏程计ぃノ璸衡 countDig 惠璶 -1 
	{
		x = x + digitDis[i]*times; // オ篒祏パ计秨﹍浪琩ㄌΩ计... 
		
		if( !primeCheck(x) || !digitDis[i] ) // 借计浪琩ゼ硄筁计 0ぃ琌オ篒祏 
		{
			return 0;
		}
		
		times = times*10; 
	}
	
	return 1;
}

/* 篒祏借计ㄧΑ */ 
int truncatablePrimeRight( int *ptrSplitNum , int countDig, int *ptrOriNum )
{
	int i = 0, fx; // 才 f(k) = ( f(k-1)*a[k] )/10┮Τ计衡Ч计穦 0 
	
	for( i ; i < countDig ; i++ )
	{
		if( i == 0 ) // ﹍ 
			fx = (*ptrOriNum - *(ptrSplitNum+i))/10;
			
		else if( i > 0 && i < countDig )
			fx = (fx - *(ptrSplitNum+i))/10;
		
		if( i != countDig-1 ) // 程ぃノ璸衡 countDig 惠璶 -1 
			if( !primeCheck(fx) || ! *(ptrSplitNum+i)) // 借计浪琩ゼ硄筁计 0ぃ琌篒祏 
				return 0;
	}
	
	return 1;
}
