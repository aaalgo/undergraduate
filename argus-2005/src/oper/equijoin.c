#include <argus.h>
#include <queue.h>

struct __comp
{	
	int offset1;
	int offset2;
	func_f comp;
};

struct __join
{
	operator_t opr;
	struct __join *peer;
	int left;	/* boolean value, whether the tuple of this opr appears in the left */
	schema_t *schema;
	queue_t pool;
	queue_t pre;
	int data_size;
	int n;
	struct __comp *comp;
};

static tuple_t *join_join (struct __join *o, tuple_t *l, tuple_t *r)
{
		int i, j, res;
		tuple_t *ret;
		int left_size, right_size;
		for (i = 0; i < o->n; i++)
		{
			o->comp[i].comp(&res, l->data + o->comp[i].offset1,
					r->data + o->comp[i].offset2);
			if (res == 0) break;					
		}
		if (i < o->n) return NULL;
		ret = tuple_alloc(o->data_size, o->schema);
		left_size = schema_data_size(l->schema);
		right_size = schema_data_size(r->schema);
		memcpy(ret->data, l->data, left_size);
		memcpy(ret->data + left_size, r->data, right_size);
		assert(left_size + right_size == o->data_size);
		i = 0;
		for (j = 0; j < l->schema->nof; j++)
		{
			if (l->schema->field[j].type->copy != NULL)
			{
				l->schema->field[j].type->copy(
					ret->data + l->schema->field[j].offset,
					l->data + l->schema->field[j].offset);
			}
			i++;
		}
		for (j = 0; j < r->schema->nof; j++)
		{
			if (r->schema->field[j].type->copy != NULL)
			{
				r->schema->field[j].type->copy(
					ret->data + left_size + r->schema->field[j].offset,
					r->data + r->schema->field[j].offset);
			}
			i++;
		}
		return ret;
}

/* 1 if still to be precessed, otherwise 0 */
static int join_process (struct __join *early, struct __join *late)
{
	tuple_t *e, *l, *t, *s;
	int flag;
	int ltime, etime;
	l = (tuple_t *)queue_peep3(&late->pre, NULL, &ltime);
	if (l == NULL) return 0;
	for (;;)
	{
		e = (tuple_t *)queue_peep3(&early->pre, NULL, &etime);
		if (e == NULL) return 1;
		if (etime > ltime) return 1;
		dequeue3(&early->pre, &flag, NULL);
		
		queue_reset(&late->pool);
		for (;;)
		{
			t = queue_cur(&late->pool);
			if (t == NULL) break;
			if (early->left)
			{
				s = join_join(early, e, t);
				if (s != NULL)
				{
					dispatch_tuple(early->opr.schedopr, flag, ltime, s);
				}
			}
			else
			{
				s = join_join(late, t, e);
				if (s != NULL)
				{
					dispatch_tuple(late->opr.schedopr, flag, ltime, s);
				}
			}
			queue_next(&late->pool);
		}

		if (flag == TUPLE_INS)
		{
			enqueue(&early->pool, e);
		}
		else
		{
			/* TODO : test it ! */
			t = dequeue(&early->pool);
			assert(t == e);
			tuple_unlock(e);
		}
	}
}

static int join_receive (struct __join *o, int type, int time, tuple_t *tuple)
{
	if (type & (TUPLE_INS | TUPLE_DEL))
	{
		enqueue3(&o->pre, tuple, TUPLE_INS, time);
		for (;;)
		{
			if (join_process(o->peer, o)) break;
			if (join_process(o, o->peer)) break;
		}
	}
	else 
	{
		assert(type != TUPLE_REPLACE);
	}
	return 0;
}

static int join_destroy (struct __join *o)
{
	tuple_t *tuple;
	for (;;)
	{
		tuple = dequeue(&o->pool);
		if (tuple == NULL) break;
		tuple_unlock(tuple);
	}
	for (;;)
	{
		tuple = dequeue(&o->pre);
		if (tuple == NULL) break;
		tuple_unlock(tuple);
	}
	if (o->peer != NULL) o->peer->peer = NULL;
	else
	{
		free(o->schema);
		free(o->comp);
	}
	/* TODO free all the tuples stored */
	queue_destroy(&(o->pre));
	queue_destroy(&(o->pool));
	return 0;
}


/* the creator of join operator is different for it creates a pair of join
	operators */
int join_pair_create (lnode_t f, schema_t *schema,
					  operator_t **join1, operator_t **join2)
{
	struct __join *j1, *j2;
	struct sql_filter *t;
	int n, i;
	j1 = type_alloc(struct __join);
	j2 = type_alloc(struct __join);
	j1->opr.receive = j2->opr.receive = (operator_receive_f)join_receive;
	j1->opr.destroy = j2->opr.destroy = (operator_destroy_f)join_destroy;
	j1->peer = j2;
	j2->peer = j1;
	j1->left = 1;
	j2->left = 0;
	j1->schema = j2->schema = schema_dup(schema);
	queue_init(&(j1->pre));
	queue_init(&(j2->pre));
	queue_init(&(j1->pool));
	queue_init(&(j2->pool));
	n = llist_count(f);
	j1->n = j2->n = n;
	j1->comp = j2->comp = (struct __comp *)xmalloc(sizeof(struct __join)
			+ (n-1)*sizeof(struct __comp));
	i = 0;
	t = (struct sql_filter *)llist_next(f);
	j1->data_size = j2->data_size 
		= schema_data_size(schema);
	while (t != NULL)
	{
		j1->comp[i].offset1 = t->source->stream->schema->field[t->field].offset;
		j1->comp[i].offset1 = t->source2->stream->schema->field[t->field2].offset;
		j1->comp[i].comp = t->comp->func;		
		i++;
		t = (struct sql_filter *)llist_next(t->link);
	}
	*join1 = (operator_t *)j1;
	*join2 = (operator_t *)j2;
	return 0;
}
