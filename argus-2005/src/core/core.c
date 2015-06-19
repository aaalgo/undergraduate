/**
  * \file schedule.c
  * \author Dong Wei
  */
#include <argus.h>
#include <buffer.h>

int tuple_id;

struct __schedopr
{
	/** Self */
	operator_t *operator;
	/** Operator destroy function */
	operator_destroy_f destroy;
	/** Operator receive function */
	operator_receive_f receive;
	/** Number/maximum of destination. */
	int nod, maxd;
	/** List of destination. */
	schedopr_t **dest;
	/* linkage */
	schedopr_t *prev, *next; /* LIKE index, protected my sched_mutex */
#ifndef NO_SCHED
	/** Input buffer and its mutex */
	buffer_t *buffer;
	/** Static priority. */
	int priority;
	/** is free */
	int free;
	/** Index of the bucket */
	int index;
#endif
};

/* Index of the first bucket in `sched_bucket'. */
int first_bucket;
/* Buckets waiting for processing. */
schedopr_t sched_bucket[SCHED_BUCKET_NUM+1];
#define sched_free (sched_bucket[SCHED_BUCKET_NUM]) 

DECLARE_MUTEX(sched_mutex);
#ifndef NO_SCHED
DECLARE_THREAD(worker);
DECLARE_SEMAPHORE(job);

void worker_func (void *dumb);

/* Modify the index.inl to change the behavior of scheduler. */
#include "index.inl"

#endif

static __inline schedopr_t *schedopr_alloc (operator_t *opr)
{
	schedopr_t *s = type_alloc(schedopr_t);
	s->operator = opr;
	s->receive = opr->receive;
	s->destroy = opr->destroy;
	s->nod = 0;
	s->maxd = DEFAULT_DEST_NUM;
	s->dest = type_calloc(DEFAULT_DEST_NUM, schedopr_t *);
	s->prev = s->next = NULL;

#ifndef NO_SCHED
	s->buffer = buffer_alloc();
	s->free = 1;
	
	s->priority = 0;
	s->index = 0;
#endif
	return s;
}

static __inline int schedopr_free (schedopr_t *s)
{
	assert(s != NULL);
#ifndef NO_SCHED
	assert(s->free = 1);
#endif
	s->destroy(s->operator);
	free(s->dest);
#ifndef NO_SCHED
	buffer_free(s->buffer);
#endif
	free(s);
	return 0;
}

int sched_init (void)
{
	int i;
	tuple_id = 0;
	first_bucket = 0;
	for (i = 0; i <= SCHED_BUCKET_NUM; i++)
	{
		sched_bucket[i].prev = sched_bucket[i].next
			= &sched_bucket[i];
	}
	MUTEX_CREATE(sched_mutex);
#ifndef NO_SCHED
	SEMAPHORE_CREATE(job, 1024);
#endif
	return 0;
}

int sched_cleanup (void)
{
	int i;
#ifndef NO_SCHED
	SEMAPHORE_DESTROY(job);
#endif
	MUTEX_DESTROY(sched_mutex);
	for (i = 0; i <= SCHED_BUCKET_NUM; i++)
	{
		schedopr_t *opr, *tmp;
		opr = sched_bucket[i].next;
		for (;;)
		{
			if (opr == &sched_bucket[i]) break;
			tmp = opr;
			opr = opr->next;
			schedopr_free(tmp);
		}
	}
	return 0;
}

int sched_start (void)
{
#ifndef NO_SCHED
	MUTEX_LOCK(sched_mutex);
	THREAD_CREATE(worker, worker_func, NULL);
	MUTEX_UNLOCK(sched_mutex);
#endif
	return 0;
}

int sched_stop (void)
{
#ifndef NO_SCHED
	MUTEX_LOCK(sched_mutex);
	THREAD_DESTROY(worker);	
#endif
	return 0;
}


int sched_add_dest (schedopr_t *s, schedopr_t *dest)
{
	assert(s != NULL && dest != NULL);
	MUTEX_LOCK(sched_mutex);
	if (s->nod >= s->maxd)
	{
		s->maxd += DEFAULT_DEST_NUM;
		s->dest = type_realloc(s->dest, s->maxd, schedopr_t *);
	}
	s->dest[s->nod] = dest;
	s->nod++;
	MUTEX_UNLOCK(sched_mutex);
	return 0;
}

int sched_remove_dest (schedopr_t *s, schedopr_t *dest)
{
	int i;
	assert(s != NULL && dest != NULL);
	for (i = 0; i < s->nod; i++)
	{
		if (s->dest[i] == dest) break;
	}
	if (i >= s->nod) return -1;
	MUTEX_LOCK(sched_mutex);
	s->nod--;
	while (i < s->nod)
	{
		s->dest[i] = s->dest[i+1];
		i++;
	}
	MUTEX_UNLOCK(sched_mutex);
	return 0;
}

schedopr_t *sched_add_operator (operator_t *o, int priority)
{
	schedopr_t *s;
	assert(o != NULL);
	s = schedopr_alloc(o);
#ifndef NO_SCHED
	s->priority = priority;
#endif
	MUTEX_LOCK(sched_mutex);
	s->next = &sched_free;
	s->prev = sched_free.prev;
	sched_free.prev->next = s;
	sched_free.prev = s;
	o->schedopr = s;
	o->receive(o, TUPLE_ADDED, TIME(), NULL);
	MUTEX_UNLOCK(sched_mutex);
	return s;
}

#ifndef NO_SCHED
static __inline void renice (schedopr_t *s)
{
	int i, j, free;
	int actual_index;
	if (buffer_empty(s->buffer)) return;
	actual_index = (s->index + SCHED_BUCKET_NUM - first_bucket) % SCHED_BUCKET_NUM;	
	j = index(s);
	free = s->free;
	if (j < actual_index || s->free)
	{
		s->next->prev = s->prev;
		s->prev->next = s->next;
		i = (first_bucket + j) % SCHED_BUCKET_NUM;
		s->index = i;
		s->next = &sched_bucket[i];	
		s->prev = sched_bucket[i].prev;
		sched_bucket[i].prev->next = s;
		sched_bucket[i].prev = s;
		s->free = 0;
	}
	if (free) SEMAPHORE_POST(job);
}

/* when this function is invoked, o should not be in running queue */
static __inline consume_tuples (schedopr_t *s)
{
		buffer_t *buf;
		int i;
		struct __buf_node *node;
		buf = s->buffer;
		s->buffer = buffer_alloc();
		for (;;)
		{
			node = buffer_dequeue(buf);
			if (node == NULL) break;
			s->receive(s->operator, node->type, node->time, node->tuple);
			free(node);
		}
		s->receive(s->operator, TUPLE_SCHEDULE, TIME(), NULL);
		buffer_free(buf);
		for (i = 0; i < s->nod; i++)
		{
				renice(s->dest[i]);
		}
}

#endif 
int sched_remove_operator (schedopr_t *s)
{
	assert(s != NULL);
	MUTEX_LOCK(sched_mutex);
	s->prev->next = s->next;
	s->next->prev = s->prev;
#ifndef NO_SCHED
	consume_tuples(s);
#endif
	schedopr_free(s);
	MUTEX_UNLOCK(sched_mutex);
	return 0;
}

int send_tuple (schedopr_t *s, int type, int time, tuple_t *p, int resched)
{
#ifdef NO_SCHED
	s->receive(s->operator, type, time, p);
#else
	assert(s != NULL);
	buffer_enqueue(s->buffer, type, time, p);
	if (resched || s->free)
	{
		renice(s);
	}
#endif
	return 0;
}

int send_tuple_async (schedopr_t *s, int type, int time, tuple_t *p, int resched)
{
	MUTEX_LOCK(sched_mutex);
	send_tuple(s, type, time, p, resched);
	MUTEX_UNLOCK(sched_mutex);
	return 0;
}

int sched_flush_tuple (schedopr_t *s)
{
#ifndef NO_SCHED
	assert(s != NULL);
	MUTEX_LOCK(sched_mutex);
	consume_tuples(s);
	MUTEX_UNLOCK(sched_mutex);
#endif
	return 0;
}

/* ONLY CALL IN operator->receive */
int dispatch_tuple (schedopr_t *s, int type, int time, tuple_t *t)
{
	int i;
	assert(s != NULL);
	if (t != NULL)
	{
		t->lock += s->nod;
		tuple_unlock(t);
	}
	for (i = 0; i < s->nod; i++)
	{
#ifdef NO_SCHED
		s->dest[i]->receive(s->dest[i]->operator, type, t);
#else
		buffer_enqueue(s->dest[i]->buffer, type, time, t);
#endif

	}
	return 0;
}

#ifndef NO_SCHED
void worker_func (void *dumb)
{	
	dumb = NULL;
	/* Never stop ? */
	for (;;)
	{
		int i, c;
		schedopr_t *s;
		SEMAPHORE_WAIT(job);
		MUTEX_LOCK(sched_mutex);
		i = first_bucket;
		c = 0;
		/* there must be one bucket not empty. */
		for (;;)
		{
			if (sched_bucket[i].next != &sched_bucket[i]) break;
			i++;
			c++;
			i %= SCHED_BUCKET_NUM;
			if (c >= SCHED_BUCKET_NUM) goto next;
		}
		s = sched_bucket[i].next;
		/* remove o from the original list */
		sched_bucket[i].next = s->next;
		s->next->prev = &sched_bucket[i];
		/* if the bucket becomes empty, set the next bucket the first
		   bucket */
		if (sched_bucket[i].next == &sched_bucket[i])
		{
			first_bucket = i + 1;
			first_bucket %= SCHED_BUCKET_NUM;
		}
		/* if SLEEP, put it to the sleep list */
		assert(!s->free);
		s->next = &sched_free;
		s->prev = sched_free.prev;
		s->free = 1;
		sched_free.prev->next = s;
		sched_free.prev = s;
		consume_tuples(s);
next:		MUTEX_UNLOCK(sched_mutex);
		/* process the buffer */
	}
}
#endif
