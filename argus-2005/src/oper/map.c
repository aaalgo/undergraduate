#include <argus.h>

struct dt_pair
{
	int temp;
	type_t *type;
	void *data;
};

struct map
{
	operator_t opr;
	int noe;
	int size;
	void *old;
	int noc;
	struct dt_pair *constant;
	schema_t *outSchema;
	expr_t *expr[1];
	
} *map;

int map_receive (struct map *opr, int type, int time, tuple_t *tup)
{
	if (type & (TUPLE_INS | TUPLE_DEL))
	{
		int ofs, i;
		void *temp;
		tuple_t *ntup = tuple_alloc(opr->size, opr->outSchema);
		ofs = 0;
		for (i = 0; i < opr->noe; i++)
		{
			temp = tup->data;
			expr_patch(opr->expr[i], &opr->old, &temp);
			expr_evaluate(opr->expr[i]);
			if (opr->expr[i]->tresult->copy)
			{
				opr->expr[i]->tresult->copy(ntup->data + ofs, opr->expr[i]->result);
			}
			else
			{
				memcpy(ntup->data + ofs, opr->expr[i]->result, opr->expr[i]->tresult->size);
			}
			ofs += opr->expr[i]->tresult->size;
		}
		opr->old = tup->data;
		ntup->id = tup->id;
		tuple_unlock(tup);
		dispatch_tuple(opr->opr.schedopr, type, time, ntup);
		for (i = 0; i < opr->noc; i++)
			if (opr->constant[i].temp)
			{
				if (opr->constant[i].type->free)
					opr->constant[i].type->free(opr->constant[i].data);
			}
	}
	else dispatch_tuple(opr->opr.schedopr, type, time, tup);
	return 0;
}

int map_destroy (struct map *opr)
{
	int i;
	for ( i = 0; i < opr->noc; i++)
	{
		if (opr->constant[i].type->free != NULL)
			if (opr->constant[i].temp == 0)
			opr->constant[i].type->free(opr->constant[i].data);
		free(opr->constant[i].data);
	}
	if (opr->constant != NULL) free(opr->constant);
	for (i = 0; i < opr->noe; i++)
	{
		expr_destroy(opr->expr[i]);
	}
	free(opr->outSchema);
	free(opr);
	return 0;
}

static void count_const (struct sql_expr *expr)
{
	if (expr->flag == EXPR_PRE_DATA) map->noc++;
	else if (expr->flag == EXPR_PRE_LEAF) map->noc++;
	else if (expr->flag == EXPR_PRE_IN)
	{
		map->noc++;
		count_const(expr->lc);
		count_const(expr->rc);
	}
}

static int const_id;

struct operand
{
	void *addr;
	int patch;
};

static struct operand make_expr_help (expr_t *ret, struct sql_expr *expr)
{
	struct operand result;
	if (expr->flag == EXPR_PRE_IN)
	{
		struct operand lc, rc;
		result.addr = malloc(expr->type->size);
		result.patch = -1;
		map->constant[const_id].type = expr->type;
		map->constant[const_id].data = result.addr;
		map->constant[const_id].temp = 1;
		const_id++;
		lc = make_expr_help(ret, expr->lc);
		rc = make_expr_help(ret, expr->rc);
		expr_append_opr(ret, expr->func->id, result.addr, lc.addr, rc.addr, -1, lc.patch, rc.patch);
	}
	else if (expr->flag == EXPR_PRE_LEAF)
	{
		result.addr = malloc(expr->type->size);
		result.patch = -1;
		map->constant[const_id].type = expr->type;
		map->constant[const_id].data = result.addr;
		map->constant[const_id].temp = 1;
		const_id++;
		expr_append_opr(ret, expr->func->id, result.addr, (void *)expr->offset, NULL, -1, 0, -1);	
	}
	else if (expr->flag == EXPR_PRE_FIELD)
	{
		result.addr = (void *)expr->offset;
		result.patch = 0;
	}
	else if (expr->flag == EXPR_PRE_DATA)
	{
		result.addr = expr->data;
		result.patch = -1;
		map->constant[const_id].type = expr->type;
		map->constant[const_id].data = expr->data;
		map->constant[const_id].temp = 0;
		const_id++;
	}
	return result;
}

static expr_t *make_expr (struct sql_expr *expr)
{
	struct operand r;
	expr_t *e = expr_create();
	r = make_expr_help(e, expr);
	expr_set_result(e, r.addr, r.patch, expr->type);
	expr_preevaluate(e);
	return e;
}

operator_t *map_create (schema_t *inSchema, schema_t *outSchema, lnode_t sel)
{
	int i;
	int n = llist_count(sel);
	struct sql_map *expr;
	struct map *opr;
	opr = (struct map *)xmalloc(sizeof(struct map) + (n-1) * sizeof(expr_t *));
	map = opr;
	opr->opr.receive = (operator_receive_f)map_receive;
	opr->opr.destroy = (operator_destroy_f)map_destroy;
	opr->noe = n;
	opr->old = NULL;
	opr->size = 0;
	opr->noc = 0;
	opr->outSchema = schema_dup(outSchema);
	expr = (struct sql_map *)llist_next(sel);
	i = 0;
	while (expr != NULL)
	{
		opr->size += expr->expr->type->size;
		count_const(expr->expr);
		i++;
		expr = (struct sql_map *)llist_next(expr->link);
	}
	opr->constant = NULL;
	if (opr->noc > 0)
	{
		opr->constant = type_calloc(opr->noc, struct dt_pair);
	}
	const_id = 0;
	expr = (struct sql_map *)llist_next(sel);
	i = 0;
	while (expr != NULL)
	{
		opr->expr[i] = make_expr(expr->expr);
		expr = (struct sql_map *)llist_next(expr->link);
		i++;
	}
	map = NULL;
	return (operator_t *)opr;	
}

