/* filename: entry.h
   by Dong Wei */
#include "pascal.h"

/**
  * \param entry The entry to be freed.
  */
void entry_free (entry_t *entry)
{
	entry_t *e;
	assert(entry != NULL);
	switch(entry->type)
	{
		case ENTRY_CONST: expr_free(entry->a.constant.expr); break;
		case ENTRY_ARRAY: for (;;)
				{
				e = (entry_t *)dequeue(entry->a.array.sub);
				if (e == NULL) break;
				}
				  entry->name = NULL;
				  queue_free(entry->a.array.sub); break;
		case ENTRY_RECORD: table_free(entry->a.record.fields); break;
		case ENTRY_LABEL: if (entry->a.label.queue != NULL)
					queue_free(entry->a.label.queue); break;
		case ENTRY_PROCEDURE: if (entry->a.procedure.param != NULL)
					table_free(entry->a.procedure.param);
	}
	if (entry->name != NULL) free(entry->name);
	free(entry);
}

/**
  * \result Pointer to the entry created.
  */
entry_t *entry_alloc (void)
{
	entry_t *entry = (entry_t *)malloc(sizeof(entry_t));
	assert(entry != NULL);
	bzero(entry, sizeof(entry_t));
	return entry;
}

/**
  * \param name Name of the entry.
  * \param e Value of the constant.
  * \result Pointer to the entry created.
  */
entry_t *const_alloc (char *name, expression_t *e)
{
	entry_t *entry = NULL;
	assert(name != NULL);
	if (e == NULL) free(name);
	else
	{
		entry = entry_alloc();
		entry->type = ENTRY_CONST;
		entry->a.constant.type = e->type;
		entry->a.constant.expr = e;
		entry->name = name;
	}
	return entry;
}

/**
  * \param name Name of the entry.
  * \result Pointer to the entry created.
  */
entry_t *label_alloc (char *name)
{
	entry_t *entry;
	entry = entry_alloc();
	entry->type = ENTRY_LABEL;
	entry->name = name;
	return entry;
}

/**
  * \param name Name of the entry.
  * \param type Type of the atomic type.
  * \param size Size of the type.
  * \param min Minimum value of the type.
  * \param max Maximum value of the type.
  * \result Pointer to the entry created.
  */
entry_t *atomic_alloc (char *name, int type, int size, int min,
		int max)
{
	entry_t *entry;
	entry = entry_alloc();
	entry->type = ENTRY_ATOMIC;
	entry->flag = 0;
	entry->name = name;
	entry->a.atomic.type = type;
	entry->a.atomic.min = min;
	entry->a.atomic.max = max;
	entry->size = size;
	return entry;
}

/**
  * \param min Minimum value of the type.
  * \param max Maximum value of the type.
  * \result Pointer to the entry created.
  */
entry_t *subrange_alloc (expression_t *min, expression_t *max)
{
	entry_t *entry = NULL;
	assert(min != NULL && max != NULL);
	assert(min->flag == EXPR_CONST && max->flag == EXPR_CONST);
	if (min->type != max->type)
	{
		ERROR("type mismatch.\n");
	}
	else
	if (min->type->type != ENTRY_ATOMIC &&
			min->type->type != ENTRY_SCALAR )
	{
		ERROR("type can not be used in subrange.\n");
	}
	else
	{
		entry = entry_alloc();
		entry->type = ENTRY_SUBRANGE;
		entry->flag = 0;
		entry->size = min->type->size;
		entry->a.subrange.base = min->type;
		entry->a.subrange.min = min->integer;
		entry->a.subrange.max = max->integer;
		entry->name = NULL;
		if (max->integer < min->integer)
		{
				ERROR("invalid subrange type.\n");
		}
	}
	free(min);
	free(max);
	return entry;	
}

/**
  * \param base Element type of the array.
  * \param sub A list of dimensions.
  * \result Pointer to the entry created.
  */
entry_t *array_alloc(entry_t *base, queue_t *sub)
{
	int i;
	int size = 1;
	entry_t *s;
	assert(base != NULL && sub != NULL);
	queue_reset(sub);
	for (;;)
	{
		s = (entry_t *)queue_cur(sub);
		if (s == NULL) break;
		if (s->type != ENTRY_ATOMIC
		&& s->type != ENTRY_SUBRANGE
		&& s->type != ENTRY_SCALAR) break;
		queue_next(sub);
		size *= (s->a.atomic.max - s->a.atomic.min + 1);
	}
	s = NULL;
	if (queue_tail(sub))
	{
		s = entry_alloc();
		s->type = ENTRY_ARRAY;
		s->flag = 0;
		s->a.array.base = base;
		s->a.array.sub = sub;
		s->size = (size * base->size);
		s->name = NULL;
	}
	else
	{
		queue_free(sub);
	}
	return s;
}

/**
  * \param fields The fields of the record to be created.
  * \result Pointer to the entry created.
  */
entry_t *record_alloc (table_t *fields)
{
	int max = 0;
	entry_t *e;
	assert(fields != NULL);
	e = fields->entries;
	while (e != NULL)
	{
		if (e->type != ENTRY_FIELD) break;
		if (e->a.field.offset + e->size > max)
		{
			max = e->a.field.offset + e->size;
		}
		e = e->next;
	}
	if (e != NULL)
	{
		table_free(fields);
		e = NULL;
	}
	else
	{
		e = entry_alloc();
		e->type = ENTRY_RECORD;
		e->flag = 0;
		e->size = max;
		e->name = NULL;
		e->a.record.fields = fields;
		INFO("RECORD_SIZE = %d\n", max);
	}
	return e;
}

/**
  * \param o The entry to copy.
  * \result Pointer to the new entry.
  */
entry_t *entry_copy (entry_t *o)
{
	entry_t *n;
	if (o == NULL) return NULL;
	assert(o->type != ENTRY_LABEL);
	n = entry_alloc();
	*n = *o;
	n->name = strdup(o->name);
	n->next = NULL;
/*	if (n->type == ENTRY_ARRAY)
	{
		n->a.array.sub = (subscript_t *)malloc(sizeof(subscript_t));
		*(n->a.array.sub) = *(o->a.array.sub);
	}*/
	assert(n->type != ENTRY_ARRAY);
	if (n->type == ENTRY_RECORD)
	{
		n->a.record.fields->ref++;
	}
	return n;
}

/**
  * \param q A list of elements.
  * \result Pointer to the entry created.
  */
entry_t *scalar_alloc (queue_t *q)
{
	char *text;
	int last;
	expression_t *c;
	entry_t *entry = entry_alloc();
	assert(q != NULL);
	entry->name = NULL;
	entry->flag = 0;
	entry->type = ENTRY_SCALAR;
	entry->a.scalar.min = 0;
	last = 0;
	for (;;)
	{
		text = dequeue(q);
		if (text == NULL) break;
		c = scalar_elem_alloc(entry, last++);
		APPEND_CONST(text, c);
	}
	entry->a.scalar.max = last - 1;
	queue_free(q);
	return entry;
}


/**
  * \param base Base type.
  * \param value Value of the element.
  * \result Pointer to the entry created.
  */
expression_t *scalar_elem_alloc (entry_t *base, int value)
{
	expression_t *e;
	e = expr_alloc();
	e->flag = EXPR_CONST;
	e->type = base;
	e->integer = value;
	return e;
}

/**
  * \param type Type of the parameter.
  * \param name Name of the Parameter.
  * \param offset Offset of the parameter.
  * \param flag Further information.
  * \result Pointer to the entry created.
  */
entry_t *param_alloc (entry_t *type, char *name, int offset, int flag)
{
	entry_t *entry;
	assert(entry != NULL && name != NULL);
	entry = entry_alloc();
	entry->flag = flag;
	entry->type = ENTRY_PARAM;
	entry->a.param.type = type;
	entry->name = name;
	entry->size = type->size;
	entry->a.param.offset = offset;
	INFO("%s param %s : %s @ %d allocated.\n", 
			flag == PARAM_BYVALUE ? "byvalue" : "byreference", 
			name, type->name, offset);
	return entry;
}


/**
  * \param type Type of the field.
  * \param name Name of the field.
  * \param offset Offset of the field.
  * \result Pointer to the entry created.
  */
entry_t *field_alloc (entry_t *type, char *name, int offset)
{
	entry_t *entry;
	assert(entry != NULL && name != NULL);
	entry = entry_alloc();
	entry->flag = 0;
	entry->type = ENTRY_FIELD;
	entry->a.field.type = type;
	entry->name = name;
	entry->a.field.offset = offset;
	entry->size = type->size;
	INFO("field %s : %s @ %d allocated.\n", name, type->name, offset);
	return entry;
}

/**
  * \param type Type of the variable.
  * \param name Name of the variable.
  * \param offset Offset(from frame base) of the variable
  * \result Pointer to the entry created.
  */
entry_t *variable_alloc (entry_t *type, char *name, int offset)
{
	entry_t *e;
	assert(type != NULL && name != NULL);
	INFO("variable alloc %s of type %s.\n", name, type->name);
	e = entry_alloc();
	e->type = ENTRY_STACK;
	e->flag = 0;
	e->name = name;
	e->size = type->size;
	e->a.stack.type = type;
	e->a.stack.offset = offset;
/*	text_emit(text, OP_BIND, 0, e->a.stack.tmp, (int)e, 0);*/
	return e;
}

/*
entry_t *int_alloc (int i)
{
	entry_t *e;
	e = entry_alloc();
	e->type = ENTRY_CONST;
	e->a.constant.type = int_entry;
	e->a.constant.value = i;
	e->name = NULL;
	e->size = 4;
	return e;
}*/

/**
  * \param name Name of the procedure.
  * \param rtype Return type of the procedure.
  * \param param A list of parameters.
  * \param flag Further information.
  * \param psize Total size of all parameters.
  * \result Pointer to the entry created.
  */
entry_t *proc_alloc (char *name, entry_t *rtype, table_t *param, int flag,
		int psize)
{
	entry_t *e;
	e = entry_alloc();
	e->type = ENTRY_PROCEDURE;
	e->flag = flag;
	e->name = name;
	e->a.procedure.rtype = rtype;
	e->a.procedure.param = param;
	e->a.procedure.psize = psize;
	e->a.procedure.id = new_proc();
	return e;
}

/**
  * \param name Name of the entry.
  * \param type Type of the result.
  * \result Pointer to the entry created.
  */
entry_t *result_alloc (char *name, entry_t *type)
{
	entry_t *e;
	assert(type != NULL && name != NULL);
	INFO("result alloc %s of type %s.\n", name, type->name);
	e = entry_alloc();
	e->type = ENTRY_RESULT;
	e->flag = 0;
	e->name = name;
	e->a.stack.type = type;
	return e;
}
