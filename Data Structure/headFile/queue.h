typedef struct node
{
	int key;
	struct node *next;
}ELEMENT, *CHECK_POS;

typedef struct
{
	CHECK_POS front, rear;
}QUEUE;

QUEUE *createQueue()
{
	QUEUE *ptr;
	ptr = (QUEUE*) malloc(sizeof(QUEUE));
	ptr->front = ptr->rear = NULL;
	
	return ptr;
}

void enQueue( QUEUE *queue, int data )
{
	if( queue->rear == NULL )
	{
		ELEMENT *ptr = (ELEMENT*) malloc(sizeof(ELEMENT));
		queue->rear = queue->front = ptr;
		queue->rear->key = data;
		queue->rear->next = NULL;
	}
	else
	{
		ELEMENT *ptr = (ELEMENT*) malloc(sizeof(ELEMENT));
		queue->rear->next = ptr;
		queue->rear = ptr;
		queue->rear->key = data;
		queue->rear->next = NULL;
	}
//	printf("enqueu success\n");
}

int deQueue( QUEUE *queue)
{	
	if( queue->front == NULL)
		return NULL;
	
	int output;
	ELEMENT *temp; 
	temp = queue->front;
	output = queue->front->key;
	queue->front = queue->front->next;
	free(temp);
	
	if( queue->front == NULL )
		queue->rear = NULL;
	
	return output;
}

void traverseQueue( QUEUE *queue )
{
	ELEMENT *tra;
	tra = queue->front;
	while( tra != NULL )
	{
		printf("%c", tra->key);
		tra = tra->next;
	}
	putchar('\n');
}

void deleteQueue( QUEUE *queue )
{
	if( queue -> front == NULL )
	{
		printf("The queue is empty.\n");
	}
	
	else
	{
		ELEMENT *tra, *temp;
		temp = queue->front;
		tra = queue->front->next;
		while( tra != NULL )
		{
			free(temp);
			temp = tra;
			tra = temp->next;
		}
		queue->front = NULL;
		queue->rear= NULL;		
	}
}
