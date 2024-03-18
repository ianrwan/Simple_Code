#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

//the array max number of queue 
#define MAX 5
//the input word number
#define MAX_VALID_WORDS 5

//create a queue
typedef struct 
{
    int key;
}queue;

queue queue1[MAX];
//queue is a FIFO so we set queue to front = -1 and rear = -1
int front = -1, rear = -1;

/*
check() = -1, the queue is empty
check() = 0, the queue can keep storing
check() = 1, the queue is full
check() = 1.5, the queue rear is over MAX but there are still blanks to input the element( front isn't -1 )
*/
float check( void )
{
    if( front == rear )
    {
    	front = -1;
    	rear = -1;
        return -1;
	}

    
    else if( rear == MAX-1 )
    {
        switch( front )
        {
            case -1:
                return 1;
            default:
                return 1.5;
        }
    }
    else
        return 0;
}

//if there are still blanks to put elements when rear is MAX-1, we will reput the element starting from 0 
void elementMove( void )
{
//	move the element
	for( int i = 0 ; i <= rear-front  ; i++ )
	{
		queue1[i].key = queue1[front+i+1].key;
	}
	
//	reset rear and front
	rear -= front+1;
	front = -1;
}

void inqueue( void )
{
    if( check() == 1 )
        puts("The queue is full, so you can't input more elements.");
    else if( check() == 1.5 )
    {
    	printf("Please enter the number you wanna input: ");
    	elementMove();
    	scanf("%d", &(queue1[++rear].key));
	}
	    else
	    {
	        printf("Please enter the number you wanna input: ");
				scanf("%d", &(queue1[++rear].key));
	    }
}

void dequeue( void )
{
	if( check() == -1 )
		puts("The queue is empty, so you can't ouptut any element.");
	else
	{
		printf("The number dequeue: %d\n", queue1[++front].key);
	}
}

void empty( void )
{
	if( check() == -1 )
		puts("The queue is empty, so youe can't empty the queue again.");
	else
	{
		front = -1;
		rear = -1;
	}
}

void traverse( void )
{
	if( check() == -1 )
		puts("There is nothing in the queue.");
	else
	{
		printf("Traverse result: ");
		for( int i = front+1 ; i <= rear ; i++ )
		{
			printf("%d ", queue1[i].key);
		}
		putchar('\n');
	}
	printf("rear = %d, front = %d.\n", rear, front);
}

int main(void)
{
//	check if the entered word is valid 
    int countValidWords = -1;
//  end of the queue
    bool isEnd = false;
    char typeIn[10];
    char *validWords[MAX_VALID_WORDS] = { "inqueue", "dequeue", "empty", "traverse", "end" };

    do
    {
    	printf("\n");
        puts("The valid input is \"inqueue, dequeue, empty, traverse, end\".");
        printf("Please enter the instruction you want to do: ");
        fflush(stdin);
        scanf("%s", typeIn);
		
//		check the word input is valid or not
        for( int i = 0 ; i < MAX_VALID_WORDS ; i++ )
        {
            if( strcmp(typeIn, validWords[i]) == 0)
            {
                countValidWords = i;
                break;
            }
        }

        switch( countValidWords )
        {
            case 0:
                inqueue();
                    break;
            case 1:
                dequeue();
                    break;
            case 2:
                empty();
                    break;
            case 3:
                traverse();
                    break;
            case 4:
                isEnd = true;
                    break;
            default:
                puts("The input is incorrect, please answer again.");
        }
//      reset the number
        countValidWords = -1;
    } while( !isEnd );
     
    return 0;
}
