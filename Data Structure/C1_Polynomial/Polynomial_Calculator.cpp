#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
#include"headFile/queue.h"

#define STRING_MAX 102
#define DATA_MAX 10

//This output is for test
void output( double **ptr, int counter )
{
	for( int i = 0 ; i < counter ; i++ )
	{
		for( int j = 0 ; j < 2 ; j++ )
		{
			printf("%f ", ptr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

//the output of the answer
void resultOut(double **poly, int counter )
{	
	for( int i = 0 ; i < counter ; i++ )
	{
//		check if the number is on the first
		if( i != 0 )
		{
//			check if the number is x^1 or constant
			if( poly[i][0] != 0 && poly[i][0] != 1 )
			{
//				check if the number is 1*x or -1*x 
				if( abs(poly[i][1]) != 1 )
				{
					printf(" %+gx^%g", poly[i][1], poly[i][0] );
				}
				else if( poly[i][1] == 1 )
				{
					printf(" +x^%g", poly[i][0]);
				}
				else if( poly[i][1] == -1 )
				{
					printf(" -x^%g", poly[i][0]);
				}
			}
			
			else if( poly[i][0] == 1 )
			{
				if( abs(poly[i][1]) != 1 )
				{
					printf(" %+gx", poly[i][1] );
				}
				else if( poly[i][1] == 1 )
				{
					printf(" +x");
				}
				else if( poly[i][1] == -1 )
				{
					printf(" -x");
				}
			}
		
//			if the number is constant and it will output simply
			else if( poly[i][0] == 0 )
			{
				printf(" %+g", poly[i][1]);
			}			
		}
		
		else
		{
			if( poly[i][0] != 0 && poly[i][0] != 1 )
			{
				if( abs(poly[i][1]) != 1 )
				{
					printf("%gx^%g", poly[i][1], poly[i][0] );
				}
				else if( poly[i][1] == 1 )
				{
					printf("x^%g", poly[i][0]);
				}
				else if( poly[i][1] == -1 )
				{
					printf("-x^%g", poly[i][0]);
				}
			}
			
			else if( poly[i][0] == 1 )
			{
				if( abs(poly[i][1]) != 1 )
				{
					printf("%gx", poly[i][1] );
				}
				else if( poly[i][1] == 1 )
				{
					printf("x");
				}
				else if( poly[i][1] == -1 )
				{
					printf("-x");
				}
			}
			
			else if( poly[i][0] == 0 )
			{
				printf("%g", poly[i][1]);
			}			
		}
	}
	printf("\n");
}

//let the string to change many character, and let the item's form be easy for computer 
void inputQueue( QUEUE *ptr, char *word )
{
	int i = 0;
//	check if the number is in front of the current number
	char nextFront = NULL;
	bool isCrossX = false, isCrossUp = false;
	
//	check if the string is over
	while( *(word+i) != '\0' )
	{	
		if( !isCrossX )
		{
			if( isdigit(*(word+i)) || *(word+i) == '.')
				enQueue(ptr, *(word+i));
		}
		
		if( *(word+i) == 'x' || *(word+i) == 'X' )
		{
			if( isdigit(nextFront))
				enQueue(ptr, 'x');
			
			else
			{
				enQueue(ptr, '1');
				enQueue(ptr, 'x');
			}
			
			isCrossX = true;
		}
		
		if( *(word+i) == '^' )
			isCrossUp = true;
		
		if( isCrossUp && isdigit(*(word+i)))
				enQueue(ptr, *(word+i));
		
		if( *(word+i+1) == '\0' )
		{
			if( *(word+i) == 'x' || *(word+i) == 'X' )
					enQueue(ptr,'1');
					
			if(!isCrossX)
			{
				enQueue(ptr, 'x');
				enQueue(ptr, '0');
				enQueue(ptr, ',');
			}
			
			if( isCrossX)
				enQueue(ptr, ',');
			isCrossX = false;
			isCrossUp = false;
		}
		
		if( *(word+i) == '+' || *(word+i) == '-')
		{
			if( nextFront == 'x' || nextFront == 'X' )
					enQueue(ptr,'1');
			
			if( !isCrossX && isdigit(nextFront) )
			{
				enQueue(ptr, 'x');
				enQueue(ptr, '0');
				enQueue(ptr, ',');
			}
			
			if( isCrossX )
				enQueue(ptr, ',');
			enQueue(ptr, *(word+i));
			isCrossX = false;
			isCrossUp = false;
		}
		
		if( *(word+i) != ' ')
			nextFront = *(word+i);
			
		i++;
	}
}

//store the Number into the two dimentional array
double **storeNumber( QUEUE *ptr, int &counter)
{
	double **storePoly = (double **) malloc(sizeof(double *)*DATA_MAX);
	int i = 0;
//	the array will store the number temporary
	char num[10];
//	store the string's char
	char temp;
	
//	counter for the item of the poly
	counter = 0;
	while( ptr->front != NULL )
	{
		storePoly[counter] = (double*) malloc(sizeof(double)*2);
		
		temp = deQueue(ptr);
		while( temp != 'x')
		{
			num[i] = temp;
			temp = deQueue(ptr);
			i++;
		}
		
		num[i] = '\0';
		storePoly[counter][1] = atof(num);
		i = 0;
		
		temp = deQueue(ptr);
//		, is for spilt the item
		while( temp != ',')
		{
			num[i] = temp;
			temp = deQueue(ptr);
			i++;
		}
		
		num[i] = '\0';
		storePoly[counter][0] = atof(num);
		
		i = 0;
		counter++;
	}
	
	return storePoly;
}

//sort the number to let it easy to plus
void bubbleSort( double **arr, int counter )
{
	int temp[1][2], k = 2;
	bool flag = true;
	
	for( int i = 1 ; i <= counter-1 && flag; i++ )
	{
		flag = false;
		for( int j = 0 ; j <= counter-k ; j++ )
		{
			if( arr[j][0] < arr[j+1][0] )
			{
				temp[0][0] = arr[j][0];
				temp[0][1] = arr[j][1];
				arr[j][0] = arr[j+1][0];
				arr[j][1] = arr[j+1][1];
				arr[j+1][0] = temp[0][0];
				arr[j+1][1] = temp[0][1];
				flag = true; 
			} 
		}
	}
}

//if the same exponent if over 2, it will add it together, and the function will clear the surplus item 
double **polySumUnion( double **workPlace, int polyCount, int &counter)
{
	counter = 0;
	int i;
//	store the number with each item
	int temp[1][2];
	
	bubbleSort(workPlace, polyCount);
	for( i = 1 ; i < polyCount ; i++ )
	{
		temp[1][0] = workPlace[i-1][0];
		
		if( workPlace[i][0] == temp[1][0] )
		{
			workPlace[i][1] += workPlace[i-1][1];
			workPlace[i-1][0] = -1;
			counter++;
		}
	}
	
	double **result = (double**)malloc(sizeof(double*)*(polyCount-counter));
	counter = 0;
	
	for( i = 0 ; i < polyCount ; i++)
	{
		if(workPlace[i][0] != -1 && workPlace[i][1] != 0 )
		{
			result[counter] = (double*)malloc(sizeof(double)*2);
			result[counter][0] = workPlace[i][0];
			result[counter][1] = workPlace[i][1];
			counter++;  
		}
	}
	
	if( counter == 0 )
	{
		result[counter] = (double*)malloc(sizeof(double)*2);
		result[counter][0] = 0;
		result[counter][1] = 0;
		counter++; 
	}
	
	return result;
}

double **polySum( double **polyA, double **polyB, int polyACount, int polyBCount, int &polyTCount)
{
	int counter = 0, i = 0;
	int temp[1][2];
	double **workPlace = (double**)malloc(sizeof(double*)*(polyACount+polyBCount));
	double **result;
	
	for( counter = 0 ; counter < polyACount+polyBCount ; counter++)
	{
		if( counter < polyACount )
		{
			workPlace[counter] = (double*)malloc(sizeof(double)*2);
			workPlace[counter][0] = polyA[i][0];
			workPlace[counter][1] = polyA[i][1];
		}
		
		if( counter == polyACount )
		{
			i = 0;
		}
		
		if( counter >= polyACount )
		{
			workPlace[counter] = (double*)malloc(sizeof(double)*2);
			workPlace[counter][0] = polyB[i][0];
			workPlace[counter][1] = polyB[i][1];
		}
		i++;
	}
	
	counter = 0;
//	output(workPlace, polyACount+polyBCount);
	result = polySumUnion(workPlace, polyACount+polyBCount, counter);
//	output(workPlace, polyACount+polyBCount);
	free(workPlace);
	polyTCount = counter;
	
	return result;
}

double **polyMinus(double **polyA, double **polyB, int polyACount, int polyBCount, int &polyTCount)
{
//	output(polyA, polyACount);
//	output(polyB, polyBCount);
	double **workPlace = (double**)malloc(sizeof(double*)*polyBCount);
	double **temp;
	for( int i = 0 ; i < polyBCount ; i++ )
	{
		workPlace[i] = (double*)malloc(sizeof(double)*2);
		workPlace[i][0] = polyB[i][0];
		workPlace[i][1] = polyB[i][1]*-1;
	}
	temp = polySum(polyA, workPlace, polyACount, polyBCount, polyTCount);
	free(workPlace);
	return temp;
}

double **polyMultiply(double **polyA, double **polyB, int polyACount ,int polyBCount, int &polyTCount)
{
	double **workPlace = (double**)malloc(sizeof(double*)*(polyACount*polyBCount));
	double **result;
	int i, j, counter = 0;
	
	for( i = 0 ; i < polyACount ; i++ )
	{
		for( j = 0 ; j < polyBCount ; j++ )
		{
			workPlace[counter] = (double*)malloc(sizeof(double)*2);
			workPlace[counter][0] = polyA[i][0]+polyB[j][0];
			workPlace[counter][1] = polyA[i][1]*polyB[j][1];
			counter++;
//			output(workPlace, counter);
		}
	}
	
	counter = 0;
	result = polySumUnion(workPlace, polyACount*polyBCount, counter);
	polyTCount = counter;
	free(workPlace);
	
	return result;
}

double **putZero(double **poly, int polyCount )
{
	int counter = 0, total = poly[0][0]+1, temp;
	double **ptr = (double**)malloc(sizeof(double*)*total);
	
	temp = total - 1;
//	printf("counter %d total %d temp %d\n", counter, total, temp);
	for(int i = 0 ; i < total ; i++ )
	{
		ptr[i] = (double*)malloc(sizeof(double)*2);
		if( counter < polyCount && poly[counter][0] == temp )
		{
			ptr[i][0] = poly[counter][0];
			ptr[i][1] = poly[counter][1];
			counter++;
		}
		else
		{
			ptr[i][0] = temp;
			ptr[i][1] = 0;
		}
		temp--;
	}
	
	return ptr;
}

void  polyDivision(double **polyA, double **polyB, int polyACount ,int polyBCount, int &polyTCount)
{
	double **polyAInZero = putZero(polyA, polyACount), **polyBInZero = putZero(polyB ,polyBCount);
	int a = polyAInZero[0][0]+1, b = polyBInZero[0][0]+1;
//	output(polyBInZero, b);
//	output(polyAInZero, a);
	int qTotal = polyAInZero[0][0]-polyBInZero[0][0]+1, i, workCount;
	
//	商數 
	double **quotient = (double**)malloc(sizeof(double*)*qTotal);
	
//	商數佔存 
	double **temp = (double**)malloc(sizeof(double*)*1);
	temp[0] = (double*)malloc(sizeof(double)*2);
	
//	相減所得資料 
	double **workPlace;
	
	qTotal = 0;
	for( i = 0 ; polyAInZero[0][0] >= polyBInZero[0][0] ; i++ )
	{
		quotient[i] = (double*)malloc(sizeof(double)*2);
		quotient[i][0] = polyAInZero[0][0]-polyBInZero[0][0];
		quotient[i][1] = polyAInZero[0][1]/polyBInZero[0][1];
		
		temp[0][0] = quotient[i][0];
		temp[0][1] = quotient[i][1];
//		printf("%f %f\n\n", temp[0][0], temp[0][1]);
		
		workPlace = polyMultiply(polyBInZero, temp, b, 1, workCount);
		qTotal++;
		workPlace = putZero(workPlace, workCount);
//		output(workPlace, b);
		polyAInZero = polyMinus(polyAInZero, workPlace, a, a, workCount);
//		output(polyAInZero, workCount);
		polyAInZero = putZero(polyAInZero, a);
		a = polyAInZero[0][0]+1;
//		output(polyAInZero, a);
		
		if( polyAInZero[0][0] == 0)
			break;
	}
	
	free(polyBInZero);
	free(temp);
	free(workPlace);
	
	polyTCount = 0;
	printf("quotient: ");
	quotient = polySumUnion(quotient, qTotal, polyTCount);
	resultOut(quotient, polyTCount);
	polyTCount = 0;
	printf("remainder: ");
	polyAInZero = polySumUnion(polyAInZero, a, polyTCount);
	resultOut(polyAInZero, polyTCount);
}

int main(void)
{
	char polyA[STRING_MAX], polyB[STRING_MAX];
	double **storePolyA, **storePolyB, **storePolySum, **storePolyMinus, **storePolyMultiply;
	int polyACount, polyBCount, polySumCount, polyMinusCount, polyMultiplyCount, polyTCount;
	char redo;
	QUEUE *ptr1 = createQueue(), *ptr2 = createQueue();
//	printf("%p\n", ptr);
	
	do
	{
		puts("Please enter the polynomial like the example.");
		puts("ex: x^1000-5 or 3x^2+5x+7 or 8x or 1");
		printf("Please enter the first polynomial( it can only be input 100 strings ): ");
		do
		{
			gets(polyA);
			inputQueue(ptr1, polyA);
			if( strlen(polyA) >= STRING_MAX-1 )
			{
				puts("The string is over 100. Please enter again.");	
			}		
		}while( strlen(polyA) >= STRING_MAX-1 );
	//	traverseQueue(ptr1);
		
		printf("Please enter the second polynomial( it can only be input 100 strings ): ");
		do
		{
			gets(polyB);
			inputQueue(ptr2, polyB);
			if( strlen(polyB) >= STRING_MAX-1 )
			{
				puts("The string is over 100. Please enter again.");	
			}		
		}while( strlen(polyB) >= STRING_MAX-1 );
	
	//	traverseQueue(ptr2);
		putchar('\n');
		
		storePolyA = storeNumber(ptr1, polyACount);
		storePolyB = storeNumber(ptr2, polyBCount);
		
		storePolySum = polySum(storePolyA, storePolyB, polyACount, polyBCount, polySumCount);
		storePolyMinus = polyMinus(storePolyA, storePolyB, polyACount, polyBCount, polyMinusCount);
		storePolyMultiply = polyMultiply(storePolyA, storePolyB, polyACount, polyBCount, polyMultiplyCount);
		
		printf("%s + %s = ", polyA, polyB);
		resultOut(storePolySum, polySumCount);
		putchar('\n');
		printf("%s - %s = ", polyA, polyB);
		resultOut(storePolyMinus, polyMinusCount);
		putchar('\n');
		printf("%s * %s = ", polyA, polyB);
		resultOut(storePolyMultiply, polyMultiplyCount);
		putchar('\n');
		
		printf("%s / %s : ",polyA, polyB );
		if( storePolyA[0][0] < storePolyB[0][0] )
		{
			printf("NULL\n");
			putchar('\n');
		}
		else if( polyBCount == 1 && storePolyB[0][0] == 0 && storePolyB[0][1] == 0 )
		{
			printf("NULL\n");
			putchar('\n');
		}
		else
		{
			polyDivision(storePolyA, storePolyB, polyACount, polyBCount, polyTCount);
			putchar('\n');		
		}
		
		do
		{
			printf("Do you want to redo again?[y/n]: ");
			scanf("%c", &redo);
			switch( redo )
			{
				case 'y':
					free(storePolyA);
					free(storePolyB);
					free(storePolySum);
					free(storePolyMultiply);
					free(storePolyMinus);
						break;
				case'n':
					break;
				default:
					puts("The enter is incorrect please enter again.");
			}
			fflush(stdin);
		}while(redo != 'y' && redo != 'n');
		putchar('\n');
	}while( redo == 'y');
}

