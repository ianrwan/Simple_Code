#include<stdio.h>
#include<stdlib.h>

#define MAX 100001 // 陣列總數，多 1 是為了確定結束位置 

void findPrime( int * );  // 尋找質數 

void output( int a[], int); // 輸出 

void splitPrime( int a[], int result[] ); // 將數字分割 
short int palindromic( int ); // 尋找迴文質數 

int main(void)
{ 
	int a[MAX-1], result[MAX]; // a 質數存放位置 result 迴文質數存放位置 
	
	for( int i = 0 ; i < MAX ; i++ )
		result[i] = 0; // 將數字歸零 
	
	printf("計算 %d 個質數：\n", MAX-1);
	printf("計算中請稍後\n");
	findPrime(a);
	output(a, 1);
	
	printf("\n");
	putchar('\n');
	
	puts("迴文質數：");
	splitPrime(a,result);
	output(result, 2);
	
	printf("\n");
	putchar('\n');
	
	system("pause");
	return 0;
}

int counter = 0; // 計算總共質數量 

void findPrime( int *ptr )
{
	int flag = 0; // 判斷是否為質數 
	
	*(ptr+0) = 2; // 初始設定第一位置為 2 
	counter++;
	
	*(ptr+1) = -1; // 數字結尾位置 
	
	for( int i = 3 ; i < 1e9 ; i++ )
	{
		flag = 1;
			
		for( int j = 0 ; *(ptr+j) < i && *(ptr+j) > 0 ; j++ ) // 判斷數字是否被質數整除 
		{
			if( i % *(ptr+j) == 0 ) // 整除不是質數 
			{
				flag = 0;
				break;
			}
		}
			
		if( flag == 1 )
		{
			*(ptr+counter+1) = -1; // 結尾向後推 
			*(ptr+counter) = i; 
			counter++;
		}
			
		if( counter == MAX-1 ) // 到達陣列上限 break 
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

int splitTemp[50]; // 存放分割數字 

void splitPrime( int a[MAX], int result[MAX] )
{
	int digitCount, temp, resultInput = 0; // 計算位數、存放正在計算的質數、result 的存放量 
	short int flag; // 判斷是否迴文 
	
	for( int i = 0 ; i < MAX-1 ; i++ )
	{
		temp = a[i];
		digitCount = 0;
		flag = 0;  
		
		while( temp != 0 ) // 分割存放 
		{
			splitTemp[digitCount] = temp%10;
			temp /= 10;
			digitCount++;
		}
		
		if( digitCount%2 != 0 && digitCount > 2 ) // 位數奇數才做比較 
			flag = palindromic(digitCount);
			
		if( flag || digitCount == 1 || a[i] == 11 ) // 迴文存放 
		{
			result[resultInput] = a[i];
			resultInput++;
		}
	}
	
	return;
}

short int palindromic( int digitCount )
{
	int middle = digitCount/2; // 計算中間位數 
	
	for( int i = 0 ; i < middle ; i++ ) // 判斷迴文 
	{
		if( splitTemp[i] != splitTemp[digitCount-1-i] )
			return 0;
	}
	
	return 1;
}
