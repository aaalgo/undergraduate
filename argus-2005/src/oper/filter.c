#include <argus.h>

/*
 * filter takes over the ownership of the data field of a comparator */

struct __comp
{
	int offset;
	int (*free)(void *);
	void *data;
	func_f comp;
};

struct __filter
{
	operator_t opr;
	int n;
	struct __comp comp[1];
};

int filter_receive (struct __filter *o, int type, int time, tuple_t *tuple)
{
	if (type & (TUPLE_INS | TUPLE_DEL))
	{		
		int i;
		int res;
		for (i = 0; i < o->n; i++)
		{
			o->comp[i].comp(&res, tuple->data + o->comp[i].offset,
					o->comp[i].data);
			if (res == 0) break;					
		}
		if (i < o->n) tuple_unlock(tuple);
		else dispatch_tuple(o->opr.schedopr, type, time, tuple);
	}
	else
	{
		dispatch_tuple(o->opr.schedopr, type, time, tuple);
	}
	return 0;
}

int filter_destroy (struct __filter *o)
{
	int i;
	for (i = 0; i < o->n; i++)
	{
		if (o->comp[i].free != NULL)
			o->comp[i].free(o->comp[i].data);
		free(o->comp[i].data);
	}
	free(o);
	return 0;
}

operator_t *filter_create (schema_t *schema, lnode_t f)
{
	struct __filter *o;
	struct sql_filter *i;
	int j, n;
	n = llist_count(f);
	o = (struct __filter *)xmalloc(sizeof(struct __filter)
			+ (n-1)*sizeof(struct __comp));
	o->opr.receive = (operator_receive_f)filter_receive;
	o->opr.destroy = (operator_destroy_f)filter_destroy;
	o->n = n;
	i = (struct sql_filter *)llist_next(f);
	j = 0;
	while (i != NULL)
	{
		o->comp[j].offset = schema->field[i->field].offset;
		o->comp[j].free = i->type->free;
		o->comp[j].data = i->data;
		assert(o->comp[j].data != NULL);
		o->comp[j].comp = i->comp->func;
		j++;
		i = (struct sql_filter *)llist_next(i->link);
	}
	return (operator_t *)o;
}

