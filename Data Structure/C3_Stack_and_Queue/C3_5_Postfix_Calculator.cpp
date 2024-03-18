#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"headfile/stack2.h"
#include"headfile/queue.h"

#define MAX 102
#define DATA_MAX 20
enum attribute{opr, opd};

void output( float **ptr)
{
	int i = 0;
	
	while( ptr[i][1] != -1 )
	{
		printf("%f %f\n", ptr[i][0], ptr[i][1]);
		i++;
	}
}

//trim the front blank and rear blank
void trim(char *ptr)
{
	int leng = strlen(ptr)+1;
	int count = 0;
	char *front, *rear;
	
	front = ptr+0;
	
	if( isspace(*front) )
	{
		while( isspace(*front) )
		{
			front++;
			count++;
		}
		
		for( int i = count ; i < leng ; i++ )
		{
			ptr[i-count] = ptr[i];
			ptr[i] = ' '; 
		}	
	}
	
	leng = strlen(ptr)+1;
	rear = ptr+leng-2;
	
	while( isspace(*rear))
	{
		*(rear) = *(rear+1);
		
		*(rear+leng-1) = ' '; 
		leng = strlen(ptr)+1;
		rear--; 
	}
}

//store the string's character into the queue
QUEUE *storeQueue(char *ptr)
{
	QUEUE *dataStream = createQueue();
	int i = -1;
	
	do
	{
		i++;
		enQueue(dataStream, ptr[i]);
	}while( ptr[i] != '\0');
	
	return dataStream;
}

//let data get into array
float **dataOrg(QUEUE *ptr)
{
	char temp;
	char num[MAX];
	float **dataArray = (float**)malloc(sizeof(float*)*DATA_MAX);
	int i = 0, count = 0;
	
	do
	{
		do
		{
			temp = deQueue(ptr);
			num[i++] = temp;	
		}while( temp != ' ' && temp != '\0');
		i = 0;
		
		dataArray[count] = (float*)malloc(sizeof(float)*2);
		
		if(num[0] == '+' || num[0] == '-' || num[0] == '/' || num[0] == '*' )
		{
			if( num[1] == ' ' || num[1] == '\0')
			{
				dataArray[count][0] = float(num[0]);
				dataArray[count][1] = opr;				
			}
			else
			{
				dataArray[count][0] = atof(num);
				dataArray[count][1] = opd;
			}
		}
		else
		{
			dataArray[count][0] = atof(num);
			dataArray[count][1] = opd;
		}
//		printf("%f %f\n", dataArray[count][0], dataArray[count][1]);
		
		count++;
	}while( temp != '\0');
	
	dataArray[count] = (float*)malloc(sizeof(float)*2);
	dataArray[count][0] = 0;
	dataArray[count][1] = -1; 
	
	return dataArray;
}

float postorderCalculate( float **ptr)
{
	STACK *store = createStack();
	float *temp1, *temp2;
	int i = 0;
	
	while( ptr[i][1] != -1 )
	{
		if( ptr[i][1] == opd )
			push(store, ptr[i]);
			
		else if( ptr[i][1] == opr )
		{
			temp1 = pop(store);
			temp2 = pop(store);
			
			switch( char(ptr[i][0]))
			{
				case '+':
					ptr[i][0] = temp2[0]+temp1[0];
					 	break;
				case '-':
					ptr[i][0] = temp2[0]-temp1[0];
					 	break;
				case '*':
					ptr[i][0] = temp2[0]*temp1[0];
					 	break;
				case '/':
					ptr[i][0] = temp2[0]/temp1[0];
					 	break;
			}
			
			ptr[i][1] = opr;
			push(store, ptr[i]);
		}
//		traverseStack(store);
		i++;
	}
	
	return *(pop(store)+0);
}

int main(void)
{
	QUEUE *dataStream;
	char opt[MAX], test[10];
	float **dataArray, result;
	
	printf("Please use blank to split your operand and operator.\n");
	printf("For example: 10 5.2 8 * + or -5 2 / -4 3 + *\n");
	printf("Please enter your operation: ");
	gets(opt);
	trim(opt);
	dataStream = storeQueue(opt);
	dataArray = dataOrg(dataStream);
//	output(dataArray);
	result = postorderCalculate(dataArray);
	printf("The result is %g\n", result);
	
	system("pause");
	return 0;
}
