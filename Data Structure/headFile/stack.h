typedef struct nodeStack
{
	char key;
	struct nodeStack *next;
}ELEMENT_STACK;

typedef struct
{
	ELEMENT_STACK *top;
}STACK;

STACK *createStack(void)
{
	STACK *ptr;
	ptr = (STACK*)malloc(sizeof(STACK));
	ptr->top = NULL;
	return ptr;
}

void push( STACK *stack, char data )
{
	if( stack->top == NULL )
	{
		ELEMENT_STACK *ptr = (ELEMENT_STACK*)malloc(sizeof(ELEMENT_STACK));
		stack->top = ptr;
		stack->top->key = data;
		stack->top->next = NULL;
	}
	else
	{
		ELEMENT_STACK *ptr = (ELEMENT_STACK*)malloc(sizeof(ELEMENT_STACK));
		ptr->next = stack->top;
		stack->top = ptr;
		stack->top->key = data;
	}
}

char pop( STACK *stack )
{
	if( stack->top == NULL )
		return NULL;
	
	char output;
	ELEMENT_STACK *temp;
	output = stack->top->key;
	temp = stack->top;
	stack->top = stack->top->next;
	free(temp);
	
	return output;
}

void traverseStack( STACK *stack )
{
	ELEMENT_STACK *current;
	current = stack->top;
	while( current != NULL )
	{
		printf("%c ", current->key);
		current = current->next;
	}
	printf("\n");
}
