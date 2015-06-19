/* filename: queue.h
 *  by Dong Wei 
 *
 * Functions and structures used to manage queues.
 * The queue saves data of type char *
 * 
 * The functions defined here are too simple to be made any comments on.
 * Following are some examples showing how to used the functions.
 * 
 * How to use:
 * 
 * 1)
 * queue_t queue;
 * queue_init(&queue);
 * enqueue(&queue, "abc");
 * for (;;)
 * {
 *	char *t = dequeue(&queue);
 *	if (t == NULL) break;
 *	printf(t);
 * }
 * queue_destroy(&queue);
 *
 * 2)
 * queue_t *queue;
 * queue = queue_alloc();
 * enqueue(queue, "abc");
 * ....
 * queue_free(queue);
 */   
 

#ifndef __PASCAL_QUEUE__
#define __PASCAL_QUEUE__
struct queue_node;
typedef struct queue_node queue_node_t;
struct queue_node
{
	queue_node_t *next;
	char *text;
};
/// The queue type.
struct queue
{
	/// Link to the queue head.
	queue_node_t *head;
	/// Link to the queue tail.
	queue_node_t **last;
	/// The cursor.
	queue_node_t *index;
};

/// The queue type.
typedef struct queue queue_t;

/// Initialize a static queue.
static inline void queue_init (queue_t *queue)
{
	assert(queue != NULL);
	queue->head = NULL;
	queue->last = &queue->head;
	queue->index = NULL;
}

/// Allocate and initialize a queue.
static inline queue_t *queue_alloc (void)
{
	queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
	assert(queue != NULL);
	queue_init(queue);
	return queue;
}

/// Free a queue.
static inline void queue_free (queue_t *queue)
{
	assert(queue != NULL);
	assert(queue->head == NULL);
	free(queue);
}

/// Test whether the queue is empty.
static inline int queue_empty (queue_t *queue)
{
	return queue->head == NULL;
}

/// As its name.
static inline void enqueue (queue_t *queue, char *text)
{
	queue_node_t *node;
	assert(queue != NULL && text != NULL);
	node = (queue_node_t *)malloc(sizeof(queue_node_t));
	assert(node != NULL);
	node->next = NULL;
	node->text = text;
	*queue->last = node;
	queue->last = &node->next;
}

/// As the name.
static inline char *dequeue (queue_t *queue)
{
	queue_node_t *node;
	char *text;
	assert(queue != NULL);
	if (queue->head == NULL) return NULL;
	node = queue->head;
	queue->head = node->next;
	text = node->text;
	if (queue->head == NULL)
	{
		queue->last = &(queue->head);
	}
	free(node);
	return text;
}

/// Empty a queue(remove all the elements).
static inline void queue_free_content (queue_t *queue)
{
	assert(queue != NULL);
	for (;;)
	{
		if (dequeue(queue) ==  NULL) break;
	}
}

/// Merge two queues. Every element of the second queue is enqueued into the first queue.
static inline void queue_merge (queue_t *tgt, queue_t *src)
{
	char *t;
	if (src == NULL) return;
	assert(tgt != NULL);
	for (;;)
	{
		t = dequeue(src);
		if (t == NULL) break;
		enqueue(tgt, t);
		INFO("DEQUEUE");
	}
	queue_free(src);
}

/// Reset the cursor.
static inline void queue_reset (queue_t *q)
{
	assert(q != NULL);
	q->index = q->head;
}

/// Referring current element.
static inline char *queue_cur (queue_t *q)
{
	assert(q != NULL);
	if (q->index == NULL) return NULL;
	return q->index->text;
}
/// Move the cursor to the next place.
static inline void queue_next (queue_t *q)
{
	assert(q != NULL);
	if (q->index != NULL) q->index = q->index->next;
}
/// Test whether the cursor is at the end of the queue.
static inline int queue_tail (queue_t *q)
{	
	return q->index == NULL;
}
/// Make a queue from the stack.
static inline queue_t *stack2queue (stack_t *s)
{
	queue_t *q;
	stack_t *t;
	char *e;
	assert(s != NULL);
	t = stack_alloc();
	for (;;)
	{
		if (stack_empty(s)) break;
		e = (char *)stack_pop(s);
		stack_push(t, (int)e);
	}
	stack_free(s);
	s = t;
	q = queue_alloc();
	for (;;)
	{
		if (stack_empty(s)) break;
		e = (char *)stack_pop(s);
		enqueue(q, e);
	}
	stack_free(s);
	return q;	
}

#endif
