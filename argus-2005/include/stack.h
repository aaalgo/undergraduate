/* filename: stack.h
   by Dong Wei */

#ifndef __PASCAL_STACK__
#define __PASCAL_STACK__

/* Types and functions used to manage the stack structure.
   The stack saves int values.

   How to use:

   stack_t *stack;
   stack = stack_alloc();
   stack_push(stack, data1);
   data2 = stack_top(stack);
   data3 = stack_pop(stack);
   while (!stack_empty(stack))
   {
   	stack_pop(stack);
   }
   stack_free(stack);

*/
   

struct stack
{
	struct stack *next;
	int data;
};

typedef struct stack stack_t;

static __inline stack_t *stack_alloc ()
{
	stack_t *s;
	s = (stack_t*)malloc(sizeof(stack_t));
	assert(s != NULL);
	s->next = NULL;
	s->data = 0;
	return s;
}

static __inline void stack_free (stack_t *stack)
{
	stack_t *tmp;
	assert(stack != NULL);
	while (stack != NULL)
	{
		tmp = stack;
		stack = stack->next;
		free(tmp);
	}
}

static __inline int stack_top (stack_t *stack)
{
	assert(stack != NULL);
	assert(stack->next != NULL);
	return stack->next->data;
}

static __inline void stack_push (stack_t *stack, int d)
{
	stack_t *s;
	assert(stack != NULL);
	s = (stack_t *)malloc(sizeof(stack_t));
	assert(s != NULL);
	s->next = stack->next;
	s->data = d;
	stack->next = s;	
}

static __inline int stack_pop (stack_t *stack)
{
	stack_t *tmp;
	int data;
	assert(stack != NULL && stack->next != NULL);
	tmp = stack->next;
	stack->next = tmp->next;
	data = tmp->data;
	free(tmp);
	return data;	
}

static __inline int stack_empty (stack_t *stack)
{
	assert(stack != NULL);
	return stack->next == NULL;
}

#endif
