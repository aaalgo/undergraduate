/* filename: queue.h
   by Dong Wei */

/* Functions and structures used to manage queues.
   The queue saves data of type void *
   
   The functions defined here are too simple to be made any comments on.
   Following are some examples showing how to used the functions.
   
   How to use:
   
   1)
   queue_t queue;
   queue_init(&queue);
   enqueue(&queue, "abc");
   for (;;)
   {
   	void *t = dequeue(&queue);
	if (t == NULL) break;
  	printf(t);
   }
   queue_destroy(&queue);

   2)
   queue_t *queue;
   queue = queue_alloc();
   enqueue(queue, "abc");
   ....
   queue_free(queue);
*/   
   

#ifndef __PASCAL_QUEUE__
#define __PASCAL_QUEUE__

typedef struct queue_node queue_node_t;
struct queue_node
{
	queue_node_t *next;
	void *text;
	int flag;
	int time;
};

struct queue
{
	queue_node_t *head;
	queue_node_t **last;
	queue_node_t *index;
};

typedef struct queue queue_t;

static __inline void queue_init (queue_t *queue)
{
	assert(queue != NULL);
	queue->head = NULL;
	queue->last = &queue->head;
	queue->index = NULL;
}

static __inline queue_t *queue_alloc (void)
{
	queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
	assert(queue != NULL);
	queue_init(queue);
	return queue;
}

static __inline void queue_destroy (queue_t *queue)
{
		assert(queue != NULL);
		assert(queue->head == NULL);
}

static __inline void queue_free (queue_t *queue)
{
	assert(queue != NULL);
	assert(queue->head == NULL);
	free(queue);
}

static __inline int queue_empty (queue_t *queue)
{
	return queue->head == NULL;
}

static __inline void enqueue3 (queue_t *queue, void *text, int flag, int time)
{
	queue_node_t *node;
	assert(queue != NULL && text != NULL);
	node = (queue_node_t *)malloc(sizeof(queue_node_t));
	assert(node != NULL);
	node->next = NULL;
	node->text = text;
	node->flag = flag;
	node->time = time;
	*queue->last = node;
	queue->last = &node->next;
}


static __inline void enqueue (queue_t *queue, void *text)
{
	enqueue3(queue, text, 0, 0);
}

static __inline void *queue_peep (queue_t *queue)
{
	assert(queue != NULL);
	if (queue->head == NULL) return NULL;
	return queue->head->text;
}

static __inline void *queue_peep3 (queue_t *queue, int *flag, int *time)
{
	assert(queue != NULL);
	if (queue->head == NULL) return NULL;
	if (flag != NULL) *flag = queue->head->flag;
	if (time != NULL) *time = queue->head->time;
	return queue->head->text;
}


static __inline void *dequeue3 (queue_t *queue, int *flag, int *time)
{
	queue_node_t *node;
	void *text;
	assert(queue != NULL);
	if (queue->head == NULL) return NULL;
	node = queue->head;
	queue->head = node->next;
	text = node->text;
	if (flag != NULL)
	{
		*flag = node->flag;
	}
	if (time != NULL)
	{
		*time = node->time;
	}
	if (queue->head == NULL)
	{
		queue->last = &(queue->head);
	}
	free(node);
	return text;
}

static __inline void *dequeue (queue_t *queue)
{
	queue_node_t *node;
	void *text;
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


static __inline void queue_free_content (queue_t *queue)
{
	assert(queue != NULL);
	for (;;)
	{
		if (dequeue(queue) ==  NULL) break;
	}
}
static __inline void queue_merge (queue_t *tgt, queue_t *src)
{
	void *t;
	if (src == NULL) return;
	assert(tgt != NULL);
	for (;;)
	{
		t = dequeue(src);
		if (t == NULL) break;
		enqueue(tgt, t);
	}
	queue_free(src);
}

static __inline void queue_reset (queue_t *q)
{
	assert(q != NULL);
	q->index = q->head;
}

static __inline void *queue_cur (queue_t *q)
{
	assert(q != NULL);
	if (q->index == NULL) return NULL;
	return q->index->text;
}

static __inline void queue_next (queue_t *q)
{
	assert(q != NULL);
	if (q->index != NULL) q->index = q->index->next;
}

static __inline int queue_tail (queue_t *q)
{	
	return q->index == NULL;
}
/*
static __inline queue_t *stack2queue (stack_t *s)
{
	queue_t *q;
	stack_t *t;
	void *e;
	assert(s != NULL);
	t = stack_alloc();
	for (;;)
	{
		if (stack_empty(s)) break;
		e = (void *)stack_pop(s);
		stack_push(t, (int)e);
	}
	stack_free(s);
	s = t;
	q = queue_alloc();
	for (;;)
	{
		if (stack_empty(s)) break;
		e = (void *)stack_pop(s);
		enqueue(q, e);
	}
	stack_free(s);
	return q;	
}
*/
#endif
