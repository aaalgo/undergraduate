/**
  * \file buffer.h
  * \author Dong Wei
  *
  * When an operator insert(enqueue) a tuple into a buffer, it
  * gives up the ownership of the tuple; when an operator get
  * a tuple through invoking dequeue, it get the ownership of the
  * tuple, and when the tuple is no longer needed, the operator
  * has to free the resources used by the tuple.
  * buffer_current only get the reference of the tuple, not the
  * ownership.
  */

#ifndef __DSMS_BUFFER__

/** Input queue to an operator. */
struct __buf_node
{
	int type;
	int time;
	tuple_t *tuple;
	struct __buf_node *next;
};

struct __buffer
{
	int count;
	struct __buf_node *last;
	struct __buf_node head;
};


/** Allocate an input queue. */
static __inline buffer_t *buffer_alloc (void)
{
		buffer_t *buf = type_alloc(buffer_t);
		buf->last = &(buf->head);
		buf->head.next = NULL;
		buf->count = 0;
		return buf;
}

/** Cleanup an input queue. */


static __inline int buffer_free (buffer_t *buf)
{
		assert(buf->count == 0);
		free(buf);
		return 0;
}

/** Tuples in the queue. */

static __inline int buffer_count (buffer_t *buf)
{
		return buf->count;
}

/** Get queue head. */

static __inline struct __buf_node *buffer_current (buffer_t *buf)
{
		return buf->head.next;
}

/** Get next tuple in the queue and remove it from the queue. */

static __inline struct __buf_node *buffer_dequeue (buffer_t *buf)
{
		struct __buf_node *t = buf->head.next;
		if (t == NULL) return NULL;
		buf->head.next = t->next;
		if (t->next == NULL) buf->last = &(buf->head);
		buf->count--;
		return t;
}

/** Insert an tuple to an queue. */

static __inline int buffer_enqueue (buffer_t *buf, int type, int time, tuple_t *tup)
{
		struct __buf_node *n = type_alloc(struct __buf_node);
		n->type = type;
		n->time = time;
		n->tuple = tup;
		n->next = NULL;
		buf->last->next = n;
		buf->last = n;
		buf->count++;
		return 0;
}

/** Test whether the queue is empty. */
static __inline int buffer_empty (buffer_t *buf)
{
		return buf->head.next == NULL;
}

 
#endif

