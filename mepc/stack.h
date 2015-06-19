
#ifndef __PASCAL_STACK__
#define __PASCAL_STACK__
/**
 * \file stack.h
 * \author Dong Wei
 *
 * Types and functions used to manage the stack structure.
 * The stack saves int values.
 *
 * The stack element must of the same size as int.
 *
 * How to use:
 *
 * stack_t *stack;
 * stack = stack_alloc();
 * stack_push(stack, data1);
 * data2 = stack_top(stack);
 * data3 = stack_pop(stack);
 * while (!stack_empty(stack))
 * {
 * 	stack_pop(stack);
 * }
 * stack_free(stack);
 **/
   
/// The stack type.
typedef struct stack
{
	/// Next element.
	struct stack *next;
	/// Related data.
	int data;
} stack_t;

/// Allocate and initialize a stack.
static inline stack_t *stack_alloc ()
{
	stack_t *s;
	s = (stack_t*)malloc(sizeof(stack_t));
	assert(s != NULL);
	s->next = NULL;
	s->data = 0;
	return s;
}

/// Free a stack.
static inline void stack_free (stack_t *stack)
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


/// Get the top element of the stack.
static inline int stack_top (stack_t *stack)
{
	assert(stack != NULL);
	assert(stack->next != NULL);
	return stack->next->data;
}

/// As the name.
static inline void stack_push (stack_t *stack, int d)
{
	stack_t *s;
	assert(stack != NULL);
	s = (stack_t *)malloc(sizeof(stack_t));
	assert(s != NULL);
	s->next = stack->next;
	s->data = d;
	stack->next = s;	
}

/// As the name.
static inline int stack_pop (stack_t *stack)
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

/// Test whether the stack is empty.
static inline int stack_empty (stack_t *stack)
{
	assert(stack != NULL);
	return stack->next == NULL;
}

#endif
