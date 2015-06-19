/* filename: vmgen.c
   by Dong Wei */

#include "pascal.h"

void type_process (expression_t *t)
{
	if (t == NULL) return;
	/* if type is compatible with integer
	   then type <- integer */
	if (t->type->type == ENTRY_ATOMIC)
	{
		if (t->type->a.atomic.type == ATOMIC_INTEGER)
		{
			t->type = int_entry;
		}
	}
}

static inline void convert2stack (expression_t *t)
{
	if (!HAS_POINTER(t) && HAS_VARIABLE(t))
	{
		t->flag &= ~EXPR_GLOBAL;
		t->flag |= EXPR_STACK;
	}
}

static inline void eliminate0 (expression_t *t)
{
	if ((t->integer == 0) && (t->flag != EXPR_CONST))
	{
		t->flag &= ~EXPR_CONST;
	}
	else if (t->integer != 0)
	{
		t->flag |= EXPR_CONST;
	}
}

void emit_merge (expression_t *t)
{
	eliminate0(t);
	if (HAS_CONST(t) && (HAS_VARIABLE(t) || HAS_POINTER(t)))
	{
		int temp = new_temp();
		EMIT_INT_TEMP(temp);
		EMIT(OP_ADD, STACK_ARG(temp, 0), VAR_ARG(t),
				CONST_ARG(t->integer));
		t->temp = temp;
		t->offset = 0;
		t->integer = 0;
		t->flag &= ~EXPR_CONST;
		convert2stack(t);
	}
}

void emit_peek (expression_t *t)
{
	int temp;
	if (t->flag & EXPR_POINTER)
	{
		emit_merge(t);
		temp = new_temp();
		EMIT_N_TEMP(temp, t->type->size);
		EMIT(OP_PEEK, STACK_ARG(temp, 0), 
				VAR_ARG(t), CONST_ARG(t->type->size));
		t->flag = EXPR_STACK;
		t->temp = temp;
		t->offset = 0;
	}
}

void emit_declaration (table_t *t)
{
	entry_t *e;
	int i;
	assert(t != NULL);
	e = t->entries;
	i = 0;
	while (e != NULL)
	{
		switch (e->type)
		{
			case ENTRY_STACK: i += e->size;
					  break;
		}
		e = e->next;
	}
	assert(i == -stack_top(record_stack));
	EMIT(OP_ALLOC, CONST_ARG(i), NULL_ARG, NULL_ARG);		
}

void emit_goto (char *t)
{
	entry_t *e = STACK_LOOKUP_TOP(t);
	if (e == NULL || e->type != ENTRY_LABEL)
	{
		ERROR("label %s not defined.\n", t);
	}
	else
	{
		if (e->a.label.label == 0)
		{
			if (e->a.label.queue == NULL)
			{
				e->a.label.queue = queue_alloc();
			}
			enqueue(e->a.label.queue, (char *)TEXT_NEXT);
		}
		EMIT(OP_JMP, LABEL_ARG(0), NULL_ARG, NULL_ARG);
	}
	free(t);
}

void emit_assign(expression_t *t, expression_t *s)
{
	type_process(t);
	type_process(t);
	if (t == NULL || s == NULL)
	{
	}
	else
	if (s->type != t->type)
	{
		ERROR("incompatible types in assignment.\n");
	}
	else
	{
		arg_t arg1;
		emit_peek(s);
		emit_merge(s);
		unmake_bool(s);
		if (HAS_CONST(s))
		{
			arg1 = CONST_ARG(s->integer);
		}
		else if (HAS_VARIABLE(s))
		{
			arg1 = VAR_ARG(s);
		}		
		if (HAS_VARIABLE(t))
		{
			EMIT(OP_MOVE, VAR_ARG(t),
					arg1, CONST_ARG(s->type->size));
		}
		else if (HAS_POINTER(t))
		{
			emit_merge(t);

			EMIT(OP_POKE, STACK_ARG(t->temp, t->offset),
				arg1, CONST_ARG(s->type->size));
			/* EMIT(OP_POKE, VAR_ARG(t), arg1, CONST_ARG(s->type->size));*/
		}
		else
			assert(0);
	}
	expr_free(s);
	expr_free(t);

}

void patch_label (queue_t *q, int label)
{
	int i;
	if (q == NULL) return;
	for (;;)
	{
		i = (int)dequeue(q);
		if (i == 0) break;
		text->data[i].arg[0].offset = label;
	}
	queue_free(q);
}

void emit_label (char *t)
{
	int i;
	entry_t *e = STACK_LOOKUP_TOP(t);
	if (e == NULL || e->type != ENTRY_LABEL)
	{
		ERROR("label %s not defined.\n", t);
	}
	else
	{
		e->a.label.label = next_label();
		EMIT(OP_LABEL, LABEL_ARG(new_label()), NULL_ARG, NULL_ARG);
		patch_label(e->a.label.queue, e->a.label.label);
		e->a.label.queue = NULL;
	}
	free(t);	
}

expression_t *emit_neg (expression_t *t)
{
	type_process(t);
	if (t->label == 0)
	{
			t->label = new_label();
			EMIT_LABEL(t->label);
	}
	if (t->type == int_entry)
	{
		emit_peek(t);
		if (HAS_VARIABLE(t))
		{
			int temp = new_temp();
			EMIT_INT_TEMP(temp);
			EMIT(OP_NEG, STACK_ARG(temp, 0),
				VAR_ARG(t), NULL_ARG);
			t->temp = temp;
			t->offset = 0;
			convert2stack(t);
		}
		if (HAS_CONST(t))
		{
			t->integer = -t->integer;
		}
	}
	return t;
}

expression_t *emit_plus (expression_t *e1, 
		expression_t *e2)
{	
	int fl;
	assert(e1 != NULL && e2 != NULL);
	if (e1->label != 0)
	{
			fl = e1->label;
	}
	else if (e2->label != 0)
	{
			fl = e2->label;
	}
	else
	{
			fl = new_label();
			EMIT_LABEL(fl);
	}
	type_process(e1);
	type_process(e2);
	if (e1->type != e2->type)
	{
		ERROR("Type mismatch.\n");
		expr_free(e1);
		expr_free(e2);
		return NULL;
	}
	emit_peek(e1);
	emit_peek(e2);
	if (e1->type == int_entry)
	{
		if (!HAS_VARIABLE(e1))
		{
			expression_t *t = e1;
			e1 = e2, e2 = t;
		}
		e1->integer += e2->integer;
		eliminate0(e1);
		if (HAS_VARIABLE(e2))
		{
			int temp = new_temp();
			EMIT_INT_TEMP(temp);
			EMIT(OP_ADD, STACK_ARG(temp, 0),
				VAR_ARG(e1),
				VAR_ARG(e2));
			e1->temp = temp;
			e1->offset = 0;
			convert2stack(e1);
		}
		expr_free(e2);
		e1->label = fl;
		return e1;
	}
	else
	{
		ERROR("Not supported.\n");
		return NULL;
	}
}

expression_t *emit_minus (expression_t *e1, expression_t *e2)
{
	int fl;
	assert(e1 != NULL && e2 != NULL);
	if (e1->label != 0)
	{
			fl = e1->label;
	}
	else if (e2->label != 0)
	{
			fl = e2->label;
	}
	else
	{
			fl = new_label();
			EMIT_LABEL(fl);
	}
	type_process(e1);
	type_process(e2);
	if (e1->type != e2->type)
	{
		ERROR("Type mismatch.\n");
		expr_free(e1);
		expr_free(e2);
		return NULL;
	}
	emit_peek(e1);
	emit_peek(e2);
	if (e1->type == int_entry)
	{
		e1->integer -= e2->integer;
		eliminate0(e1);
		if (HAS_VARIABLE(e2))
		{
			int temp = new_temp();
			EMIT_INT_TEMP(temp);
			if ((e1->flag & EXPR_STACK) != 0)
			{
				EMIT(OP_SUB, STACK_ARG(temp, 0),
					VAR_ARG(e1),
					VAR_ARG(e2));	
			}
			else
			{
				EMIT(OP_NEG, STACK_ARG(temp, 0),
					VAR_ARG(e2),
					NULL_ARG);
			}
			e1->flag |= EXPR_STACK;
			e1->temp = temp;
			e1->offset = 0;
			convert2stack(e1);
		}
		free(e2);
		e1->label = fl;
		return e1;
	}
	else
	{
		ERROR("Not supported.\n");
	}
}

expression_t *emit_or (expression_t *e1, expression_t *e2)
{
	int fl;	
	assert(e1 != NULL && e2 != NULL);
	if (e1->label != 0)
	{
			fl = e1->label;
	}
	else if (e2->label != 0)
	{
			fl = e2->label;
	}
	else
	{
			fl = new_label();
			EMIT_LABEL(fl);
	}
	type_process(e1);
	type_process(e2);
	if (e1->type != e2->type)
	{
		ERROR("Type mismatch.\n");
		return NULL;
	}
	if (e1->type == bool_entry)
	{
	   	if (e1->flag == EXPR_BOOL || e2->flag == EXPR_BOOL)
		{	
			if (e1->flag != EXPR_BOOL)
			{
				make_bool(e1);
			}
			if (e2->flag != EXPR_BOOL)
			{
				make_bool(e2);
			}
			if (e1->true_list == NULL)
			{
				expression_t *e = e1;
				e1 = e2;
				e2 = e;
			}
			queue_merge(e1->true_list, e2->true_list);
			patch_label(e1->false_list, e2->label);
			e1->false_list = e2->false_list;
			e1->label = fl;
			return e1;
		}
		else
		{
			if (e1->flag == EXPR_CONST && e2->flag == EXPR_CONST)
			{
				e1->integer |= e2->integer;
				e1->integer &= 1;
			}
			else
			{
				int temp = new_temp();
				emit_peek(e1);
				emit_peek(e2);
				emit_merge(e1);
				emit_merge(e2);
				EMIT_INT_TEMP(temp);
				EMIT(OP_OR, STACK_ARG(temp, 0),
					DAT_ARG(e1), DAT_ARG(e2));
				e1->temp = temp;
				e1->offset = 0;
				convert2stack(e1);
			}
		}
		expr_free(e2);
		e1->label = fl;
		return e1;
	}
	assert(0);
	return NULL;
}

expression_t *emit_times (expression_t *e1, expression_t *e2)
{
	int fl;
	assert(e1 != NULL && e2 != NULL);
	if (e1->label != 0)
	{
			fl = e1->label;
	}
	else if (e2->label != 0)
	{
			fl = e2->label;
	}
	else
	{
			fl = new_label();
			EMIT_LABEL(fl);
	}
	type_process(e1);
	type_process(e2);
	if (e1->type != e2->type)
	{
		ERROR("Type mismatch.\n");
		return NULL;
	}
	if (e1->type == int_entry)
	{
		emit_peek(e1);
		emit_peek(e2);
		emit_merge(e1);
		emit_merge(e2);
		if (!HAS_VARIABLE(e1))
		{
			expression_t *r;
			r = e1, e1 = e2, e2 = r;
		}
		if (!HAS_VARIABLE(e1))
		{
			e1->integer *= e2->integer;
		}
		else
		{
			int temp = new_temp();
			EMIT_INT_TEMP(temp);
			EMIT(OP_MUL, STACK_ARG(temp, 0),
				DAT_ARG(e1),
				DAT_ARG(e2));
			e1->temp = temp;
			e1->offset = 0;
			convert2stack(e1);
		}
		free(e2);
		e1->label = fl;
		return e1;
	}
	else
	{
		ERROR("Not supported.\n");
	}
}

expression_t *emit_div (expression_t *e1, expression_t *e2)
{
	int fl;
	assert(e1 != NULL && e2 != NULL);
	if (e1->label != 0)
	{
			fl = e1->label;
	}
	else if (e2->label != 0)
	{
			fl = e2->label;
	}
	else
	{
			fl = new_label();
			EMIT_LABEL(fl);
	}
	type_process(e1);
	type_process(e2);
	if (e1->type != e2->type)
	{
		ERROR("Type mismatch.\n");
		return NULL;
	}
	if (e1->type == int_entry)
	{
		emit_peek(e1);
		emit_peek(e2);
		emit_merge(e1);
		emit_merge(e2);
		if (e1->flag == EXPR_CONST && e2->flag == EXPR_CONST)
		{
			e1->integer /= e2->integer;
		}
		else
		{
			int temp = new_temp();
			EMIT_INT_TEMP(temp);
			EMIT(OP_DIV, STACK_ARG(temp, 0),
					DAT_ARG(e1), DAT_ARG(e2));
			e1->temp = temp;
			e1->offset = 0;
			convert2stack(e1);
		}
		free(e2);
		e1->label = fl;
		return e1;
	}
	else
	{
		ERROR("Not supported.\n");
	}
}

expression_t *emit_divide (expression_t *e1, expression_t *e2)
{
	assert(0);
	return NULL;
}


expression_t *emit_mod (expression_t *e1, expression_t *e2)
{
	int fl;	
	assert(e1 != NULL && e2 != NULL);
	if (e1->label != 0)
	{
			fl = e1->label;
	}
	else if (e2->label != 0)
	{
			fl = e2->label;
	}
	else
	{
			fl = new_label();
			EMIT_LABEL(fl);
	}
	type_process(e1);
	type_process(e2);
	if (e1->type != e2->type)
	{
		ERROR("Type mismatch.\n");
		return NULL;
	}
	if (e1->type == int_entry)
	{
		emit_peek(e1);
		emit_peek(e2);
		emit_merge(e1);
		emit_merge(e2);
		if (e1->flag == EXPR_CONST && e2->flag == EXPR_CONST)
		{
			e1->integer %= e2->integer;
		}
		else
		{
			int temp = new_temp();
			EMIT_INT_TEMP(temp);
			EMIT(OP_MOD, STACK_ARG(temp, 0),
				DAT_ARG(e1), DAT_ARG(e2));
			e1->temp = temp;
			e1->offset = 0;
			convert2stack(e1);
		}
		free(e2);
		e1->label = fl;
		return e1;
	}
	else
	{
		ERROR("Not supported.\n");
	}
}

expression_t *emit_and (expression_t *e1, expression_t *e2)
{
	int fl;
	assert(e1 != NULL && e2 != NULL);
	type_process(e1);
	type_process(e2);
	if (e1->label != 0)
	{
			fl = e1->label;
	}
	else if (e2->label != 0)
	{
			fl = e2->label;
	}
	else
	{
			fl = new_label();
			EMIT_LABEL(fl);
	}
	if (e1->type != e2->type)
	{
		ERROR("Type mismatch.\n");
		return NULL;
	}
	if (e1->type == bool_entry)
	{
		if (e1->flag == EXPR_BOOL || e2->flag == EXPR_BOOL)
		{
			e1 = make_bool(e1);
			e2 = make_bool(e2);
			if (e1->false_list == NULL)
			{
				expression_t *e = e1;
				e1 = e2;
				e2 = e;
			}
			if (e1->false_list == NULL)
			{
				e1->false_list = queue_alloc();
			}
			queue_merge(e1->false_list, e2->false_list);
			patch_label(e1->true_list, e2->label);
			e1->true_list = e2->true_list;
			expr_free(e2);
			e1->label = fl;
			return e1;
		}
		else
		{	
			if (e1->flag == EXPR_CONST && e2->flag == EXPR_CONST)
			{
				e1->integer &= e2->integer;
			}
			else
			{
				int temp = new_temp();
				emit_peek(e1);
				emit_peek(e2);
				emit_merge(e1);
				emit_merge(e2);
				EMIT_INT_TEMP(temp);
				EMIT(OP_AND, STACK_ARG(temp, 0),
					DAT_ARG(e1), DAT_ARG(e2));
				e1->temp = temp;
				e1->offset = 0;
				convert2stack(e1);
			}
			expr_free(e2);
			e1->label = fl;
			return e1;	
		}
	}
	else { assert(0);}
}

expression_t *emit_not (expression_t *e)
{
	type_process(e);
	if (e->label == 0)
	{
			e->label = new_label();
			EMIT_LABEL(e->label);
	}
	if (e->type == bool_entry)
	{
		if (e->flag == EXPR_BOOL)
		{
			queue_t *q;
			q = e->true_list;
			e->true_list = e->false_list;
			e->false_list = q;
			return e;
		}
		else if (e->flag == ENTRY_CONST)
		{
			e->integer = ! e->integer;
			return e;
		}
		else
		{
			int temp;
			emit_peek(e);
			emit_merge(e);
			temp = new_temp();
			EMIT_BOOL_TEMP(temp);
			EMIT(OP_NOT, STACK_ARG(temp, 0),
					VAR_ARG(e), NULL_ARG);
			EMIT(OP_AND, STACK_ARG(temp, 0),
					STACK_ARG(temp, 0), CONST_ARG(1));				e->temp = temp;
			e->offset = 0;
			convert2stack(e);
			return e;
		}
	}
	else if (e->type == int_entry)
	{
		if (e->flag == EXPR_CONST)
		{
			e->integer = ~e->integer;
		}
		else if (HAS_VARIABLE(e))
		{
			int temp;
			emit_peek(e);
			emit_merge(e);
			temp = new_temp();
			EMIT_INT_TEMP(temp);
			EMIT(OP_NOT, STACK_ARG(temp, 0),
					VAR_ARG(e),
					NULL_ARG);
			e->temp = temp;
			e->offset = 0;
			convert2stack(e);
		}
		return e;
	}
	assert(0);
}

expression_t *emit_true (void)
{
	expression_t *e;
	e = expr_alloc();
	e->flag = EXPR_CONST;
	e->type = bool_entry;
	e->integer = 0x1;
	return e;
}

expression_t *emit_false (void)
{
	expression_t *e;
	e = expr_alloc();
 	e->flag = EXPR_CONST;
 	e->type = bool_entry;
	e->integer = 0;
	return e;
}

expression_t *emit_relop (expression_t *e1, expression_t *e2, int OP)
{
	int fl;
	expression_t *e;
	assert(e1 != NULL && e2 != NULL);
	e = NULL;
	if (e1->label != 0)
	{
			fl = e1->label;
	}
	else if (e2->label != 0)
	{
			fl = e2->label;
	}
	else
	{
			fl = new_label();
			EMIT_LABEL(fl);
	}
	type_process(e1);
	type_process(e2);
	if (e1->type != e2->type)
	{
		ERROR("Type mismatch.\n");
		return NULL;
	}
	if (e1->type == int_entry)
	{
		arg_t arg1, arg2;
		INFO("GEN RELOP %s\n", opcode_symbol[OP]);
		e = expr_alloc();
		e->flag = EXPR_BOOL;
		e->type = bool_entry;
		if (e1->label != 0)
		{
				e->label = e1->label;
		}
		else if (e2->label != 0)
		{
				e->label = e2->label;
		}
		else
		{
				e->label = new_label();
				EMIT_LABEL(e->label);
		}
		e->true_list = queue_alloc();
		e->false_list = queue_alloc();
		emit_peek(e1);
		emit_peek(e2);
		emit_merge(e1);
		emit_merge(e2);
		if (e1->flag == EXPR_CONST) arg1 = CONST_ARG(e1->integer);
		else arg1 = VAR_ARG(e1);
		if (e2->flag == EXPR_CONST) arg2 = CONST_ARG(e2->integer);
		else arg2 = VAR_ARG(e2);
		enqueue(e->true_list, (char *)TEXT_NEXT);
		EMIT(OP, LABEL_ARG(0), arg1, arg2);
		enqueue(e->false_list, (char *)TEXT_NEXT);
		EMIT(OP_JMP, LABEL_ARG(0), NULL_ARG, NULL_ARG);
		expr_free(e1);
		expr_free(e2);
	}
	e->label = fl;
	return e;
}

expression_t *emit_variable (char *s)
{
	int level;
	expression_t *expr;
	entry_t *e = STACK_LOOKUP(s, &level);
	expr = NULL;
	if (e == NULL)
	{
		ERROR("symbol %s not defined.\n", s);
	}
	else
	{
		expr = expr_alloc();
		if ((e->type == ENTRY_STACK) || (e->type == ENTRY_PARAM))
	 	{
			if (level == 0)
			{
				expr->flag = EXPR_STACK;
				expr->type = e->a.stack.type;
				expr->offset = e->a.stack.offset;
			}
			else
			{
				int temp = new_temp();
				int l = new_label();
				expr->flag = EXPR_POINTER;
				expr->type = e->a.stack.type;
				expr->offset = 0;
				expr->temp = temp;
				EMIT_N_TEMP(temp, e->size);
				EMIT(OP_ANS, STACK_ARG(temp, 0),
					CONST_ARG(level),
					CONST_ARG(e->a.stack.offset));
			}
			if (e->type == ENTRY_PARAM
				&& e->flag == PARAM_BYREFERENCE)
			{
				if (expr->flag == EXPR_POINTER)
				{
					entry_t *t = expr->type;
					expr->type = int_entry;
					emit_peek(expr);
					expr->type = t;
				}
				expr->flag = EXPR_POINTER;
			}
		}
		else if (e->type == ENTRY_CONST)
		{
			expr->flag = EXPR_CONST;
			expr->type = e->a.constant.type;
			expr->integer = e->a.constant.expr->integer;
		}
		else if (e->type == ENTRY_PROCEDURE)
		{
			int l = new_label();
			expr->address = l;
			EMIT_LABEL(l);	
			return emit_invoke(s, NULL);
		}
		else
		{
			ERROR("invalid symbol %s.\n", s);
			expr_free(expr);
			expr = NULL;
		}
	}
	free(s);
	return expr;
}

expression_t *emit_record_field (expression_t *e, char *s)
{
	entry_t *f;
	if (e == NULL)
	{
		free(s);
		return NULL;
	}
	if (e->type->type == ENTRY_RECORD)
	{
		f = table_lookup(e->type->a.record.fields, s);
		if (f == NULL)
		{
			ERROR("invalid field.\n");
			expr_free(e);
			e = NULL;			
		}
		else
		{
			e->type = f->a.stack.type;
			if (HAS_VARIABLE(e))
			{
				e->offset += f->a.field.offset;
			}
			else if (HAS_POINTER(e))
			{
				e->integer += f->a.field.offset;
				e->flag |= EXPR_CONST;
			}
		}
	}
	else
	{
		ERROR("Invalid type.\n");
		free(e);
		e = NULL;
	}
	free(s);
	return e; 
}

expression_t *emit_array_element (expression_t *x, queue_t *e)
{
	expression_t *ofs, *sub;
	entry_t *bas, *t;
	queue_t *subq;
	assert(x != NULL && e != NULL);
	if (x->type->type != ENTRY_ARRAY)
	{
			ERROR("subscripted object is not an array or string.\n");
			for (;;)
			{
					sub = (expression_t *)dequeue(e);
					if (sub == NULL) break;
					expr_free(sub);
			}
			expr_free(x);
			queue_free(e);
			return NULL;
			
	}
	subq = x->type->a.array.sub;
	ofs = make_int_expr(0);
	queue_reset(subq);
	for (;;)
	{
		sub = (expression_t *)dequeue(e);
		if (sub == NULL) break;
		bas = (entry_t *)queue_cur(subq);
		queue_next(subq);
		assert((bas->type == ENTRY_ATOMIC)
			|| (bas->type == ENTRY_SCALAR)
			|| (bas->type == ENTRY_SUBRANGE));
	ofs = emit_times(ofs, 
		make_int_expr(bas->a.atomic.max - bas->a.atomic.min + 1));
		sub = emit_minus(sub, make_int_expr(bas->a.atomic.min));
		ofs = emit_plus(ofs, sub);
	}
	queue_free(e);
	assert(queue_tail(subq));
	ofs = emit_times(ofs, make_int_expr(x->type->a.array.base->size));
	if (x->flag & EXPR_POINTER)
	{
		t = x->type;
		x->type = int_entry;
		x->flag = EXPR_STACK;
		x = emit_plus(x, ofs);
		x->type = t->a.array.base;
		x->flag = EXPR_POINTER;
	}
	else if ((x->flag == EXPR_STACK) || (x->flag == EXPR_GLOBAL))
	{
		x->type = x->type->a.array.base;
		if (ofs->flag == EXPR_CONST)
		{
			x->offset += ofs->integer;
			expr_free(ofs);
		}
		else
		{
			int temp = new_temp();
			EMIT_INT_TEMP(temp);
			EMIT(OP_ADDR, STACK_ARG(temp, 0),
					VAR_ARG(x), CONST_ARG(4));
			emit_merge(ofs);
			EMIT(OP_ADD, STACK_ARG(temp, 0),
					STACK_ARG(temp, 0), VAR_ARG(ofs));
			x->flag = EXPR_POINTER;
			x->temp = temp;
			x->offset = 0;
			x->integer = 0;
		}
	}
	else 
	{
			printf("%d\n", x->flag);
			assert(0);
	}
	return x;
}

expression_t *make_bool (expression_t *e)
{
	if (e->flag == EXPR_BOOL) return e;
	if (e->type == bool_entry)
	{
		int l = new_label();
		EMIT_LABEL(l);
		if (e->label == 0)
		{
			e->label = l;
		}
		if (e->flag == EXPR_CONST)
		{
			if (e->integer)
			{
				e->true_list = queue_alloc();
				enqueue(e->true_list, (char *)TEXT_NEXT);
				EMIT(OP_JMP, LABEL_ARG(0), NULL_ARG, NULL_ARG);
				e->false_list = NULL;
			}
			else
			{
				e->false_list = queue_alloc();
				enqueue(e->false_list, (char *)TEXT_NEXT);
				EMIT(OP_JMP, LABEL_ARG(0), NULL_ARG, NULL_ARG);
				e->true_list = NULL;
			}
			e->flag = EXPR_BOOL;
			return e;
		}
		if (e->flag == EXPR_POINTER)
		{
			emit_peek(e);
		}
		if (HAS_VARIABLE(e))
		{
			e->true_list = queue_alloc();
			e->false_list = queue_alloc();
			enqueue(e->false_list, (char *)TEXT_NEXT);
			EMIT(OP_JEQ, LABEL_ARG(0), VAR_ARG(e), CONST_ARG(0));
			enqueue(e->true_list, (char *)TEXT_NEXT);
			EMIT(OP_JMP, LABEL_ARG(0), NULL_ARG, NULL_ARG);
			e->flag = EXPR_BOOL;
			return e;
		}
	}
	assert(0);
}

expression_t *unmake_bool (expression_t *e)
{
	if (e->flag == EXPR_BOOL)
	{
		int temp, l, m;
		if (e->label == 0)
		{
				e->label = new_label();
				EMIT_LABEL(e->label);
		}
		temp = new_temp();
		EMIT_BOOL_TEMP(temp);
		m = new_label();
		if (e->true_list != NULL)
		{
			l = new_label();	
			EMIT_LABEL(l);
			patch_label(e->true_list, l);
			EMIT(OP_MOVE, STACK_ARG(temp, 0), CONST_ARG(1),
					CONST_ARG(4));
			EMIT(OP_JMP, LABEL_ARG(m), NULL_ARG, NULL_ARG);
		}
		if (e->false_list != NULL)
		{
			l = new_label();
			EMIT_LABEL(l);
			patch_label(e->false_list, l);
			EMIT(OP_MOVE, STACK_ARG(temp, 0), CONST_ARG(0),
					CONST_ARG(4));
			EMIT(OP_JMP, LABEL_ARG(m), NULL_ARG, NULL_ARG);
		}
		EMIT_LABEL(m);
		e->flag = EXPR_STACK;
		e->temp = temp;
		e->offset = 0;		
	}
	return e;
}

expression_t *emit_invoke (char *s, stack_t *p)
{
	table_t *t;
	entry_t *e, *ee;
	expression_t *x;
	int op;
	int l;
	int error;
	int fl;
	expression_t *ret;
	arg_t arg1;
	ee = STACK_LOOKUP(s, &l);
	if (ee == NULL)
	{
			ERROR("symbol %s not defined.\n", s);
			free(s);
			return NULL;
	}
	if (ee->type != ENTRY_PROCEDURE)
	{
			ERROR("expression used as a statement.\n");
			free(s);
			return NULL;
			
	}
	t = ee->a.procedure.param;
	if (t == NULL) e = NULL;
	else e = t->entries;
	error = 0;
	fl = new_label();
	EMIT_LABEL(fl);
	if (p != NULL)
	for (;;)
	{
		if (stack_empty(p)) break;
		x = (expression_t *)stack_pop(p);
		if (x == NULL) break;
		if (x->label != 0) fl = x->label;
		if (e == NULL)
		{
			error = 1;
			continue;			
		}
		if (x->type != e->a.param.type)
		{
			ERROR("incompatible type for argument `%s'.\n", e->name);
		}	
		else
		if (e->flag == PARAM_BYVALUE)
		{
			emit_peek(x);
			emit_merge(x);
			EMIT(OP_PARAM, DAT_ARG(x), 
					CONST_ARG(e->size), NULL_ARG);
		}
		else if (e->flag == PARAM_BYREFERENCE)
		{
			if (HAS_POINTER(x))
			{
				emit_merge(x);
				EMIT(OP_PARAM, STACK_ARG(x->temp, x->offset),
						CONST_ARG(4), NULL_ARG);
			}
			else if (HAS_VARIABLE(x) && ! HAS_CONST(x))
			{
				int temp = new_temp();
				EMIT_INT_TEMP(temp);
				EMIT(OP_ADDR, STACK_ARG(temp, 0),
						VAR_ARG(x), NULL_ARG);
				EMIT(OP_PARAM, STACK_ARG(temp, 0),
						CONST_ARG(4), NULL_ARG);
			}
			else assert(0);
		}
		else assert(0);
		expr_free(x);
		e = e->next;
	}
	if (e != NULL || error)
	{
		ERROR("argument mismatch.\n");
	}
	if (ee->flag == PROCEDURE_PASCAL)
	{
		op = OP_CALL;
		arg1 = CONST_ARG(l);
	}
	else if (ee->flag == PROCEDURE_CDECL)
	{
		op = OP_CCALL;
		arg1 = NULL_ARG;
	}
	else assert(0);
	
	EMIT(op, SYMBOL_ARG(hash_lookup(string_table, s)),
			arg1, LABEL_ARG(ee->a.procedure.id));
	free(s);
	if (p != NULL) stack_free(p);
	ret = NULL;
	if (ee->a.procedure.rtype != NULL)
	{
		ret = expr_alloc();
		l = new_temp();
		op = ee->a.procedure.rtype->size;
		EMIT(OP_TEMP, STACK_ARG(l, 0), CONST_ARG(op), NULL_ARG);
		EMIT(OP_MRET, STACK_ARG(l, 0), CONST_ARG(op), NULL_ARG);
		ret->type = ee->a.procedure.rtype;
		ret->flag = EXPR_STACK;
		ret->temp = l;
		ret->offset = 0;
		ret->label = fl;
	}
	return ret;
}

static char format[256], format2[256];
static void catstr (char *c)
{
	strcpy(format2, format);
	strcpy(format, c);
	strcat(format, format2);
}

void emit_read (stack_t *p, int ln)
{
	expression_t *x;
	format[0] = 0;
	if (p != NULL)
	for (;;)
	{
		if (stack_empty(p)) break;
		x = (expression_t *)stack_pop(p);
		if (x == NULL) break;
		if (x->type->type == ENTRY_ATOMIC)
		{
			if (x->type->a.atomic.type == ATOMIC_INTEGER)
			{
				catstr("%d");
			}
			else if (x->type->a.atomic.type == ATOMIC_CHAR)
			{
				catstr("%c");
			}
			else if (x->type->a.atomic.type == ATOMIC_REAL)
			{
				catstr("%lf");
			}
			else
			{
				ERROR("Format not supported.\n")
			}
		}
		if (HAS_POINTER(x))
		{
			emit_merge(x);
			EMIT(OP_PARAM, STACK_ARG(x->temp, x->offset),
					CONST_ARG(4), NULL_ARG);
		}
		else if (HAS_VARIABLE(x) && ! HAS_CONST(x))
		{
			int temp = new_temp();
			EMIT_INT_TEMP(temp);
			EMIT(OP_ADDR, STACK_ARG(temp, 0),
					VAR_ARG(x), NULL_ARG);
			EMIT(OP_PARAM, STACK_ARG(temp, 0),
					CONST_ARG(4), NULL_ARG);
		}
		else
		{
			ERROR("Format not supported.\n");
		}
		expr_free(x);
	}
	x = make_string_expr(strdup(format));	
	EMIT(OP_PARAM, GADDR_ARG(x->temp, 0), CONST_ARG(4), NULL_ARG);
	EMIT(OP_CCALL, SYMBOL_ARG(hash_lookup(string_table, "scanf")),
			NULL_ARG, NULL_ARG);
	expr_free(x);
	if (p != NULL)
	stack_free(p);
}

void emit_write (stack_t *p, int ln)
{
	expression_t *x;
	int s;
	format[0] = 0;
	for (;;)
	{
		if (stack_empty(p)) break;
		x = (expression_t *)stack_pop(p);
		if (x == NULL) break;
		if (x->type->type == ENTRY_ATOMIC)
		{
			if (x->type->a.atomic.type == ATOMIC_INTEGER)
			{
				catstr("%d");
			}
			else if (x->type->a.atomic.type == ATOMIC_CHAR)
			{
				catstr("%c");
			}
			else if (x->type->a.atomic.type == ATOMIC_REAL)
			{
				catstr("%lf");
			}
			else if (x->type->a.atomic.type == ATOMIC_STRING)
			{
				catstr("%s");
			}
			else if (x->type->a.atomic.type == ATOMIC_BOOL)
			{
					catstr("%s");					
			}
			else
			{
				ERROR("Format not supported.\n");
			}
		}
		s = x->type->size;
		if (s < 4)
			s = 4;
		if (x->type->type == ENTRY_ATOMIC
			&& x->type->a.atomic.type == ATOMIC_STRING)
		{
			EMIT(OP_PARAM, GADDR_ARG(x->temp, x->offset),
					CONST_ARG(4), NULL_ARG);
		}
		else if (x->type->type == ENTRY_ATOMIC
			&& x->type->a.atomic.type == ATOMIC_BOOL)
		{
				int l1 = new_label();
				int l2 = new_label();
				expression_t *expr_true = make_string_expr(strdup("True"));
				expression_t *expr_false = make_string_expr(strdup("False"));
				x = unmake_bool(x);
				emit_peek(x);
				emit_merge(x);
				if (x->flag == (EXPR_CONST | EXPR_BOOL))
				{
						if (x->integer)
						{
								EMIT(OP_PARAM, GADDR_ARG(expr_true->temp, expr_false->offset), CONST_ARG(4), NULL_ARG);
						}
						else
						{
								EMIT(OP_PARAM, GADDR_ARG(expr_false->temp, expr_false->offset), CONST_ARG(4), NULL_ARG);
						}
				}
				else
				{
					int temp = new_temp();
					EMIT_INT_TEMP(temp);				
					EMIT(OP_JNE, LABEL_ARG(l1), DAT_ARG(x), CONST_ARG(0));
					EMIT(OP_MOVE, STACK_ARG(temp, 0), GADDR_ARG(expr_false->temp, expr_false->offset), CONST_ARG(4));
					EMIT(OP_JMP, LABEL_ARG(l2), NULL_ARG, NULL_ARG);
					EMIT_LABEL(l1);
					EMIT(OP_MOVE, STACK_ARG(temp, 0), GADDR_ARG(expr_true->temp, expr_true->offset), CONST_ARG(4));
					EMIT_LABEL(l2);
					EMIT(OP_PARAM, STACK_ARG(temp, 0), CONST_ARG(4), NULL_ARG);
				}
				expr_free(expr_true);
				expr_free(expr_false);
		}
		else
		{
			emit_peek(x);
			emit_merge(x);
			EMIT(OP_PARAM, DAT_ARG(x), 
					CONST_ARG(s), NULL_ARG);
			expr_free(x);
		}
	}
	if (ln)
	{
		strcat(format, "\n");
	}
	x = make_string_expr(strdup(format));
	EMIT(OP_PARAM, GADDR_ARG(x->temp, x->offset),
			CONST_ARG(4), NULL_ARG);
	expr_free(x);
	EMIT(OP_CCALL, SYMBOL_ARG(hash_lookup(string_table, "printf")),
			NULL_ARG, NULL_ARG);
	stack_free(p);
}

