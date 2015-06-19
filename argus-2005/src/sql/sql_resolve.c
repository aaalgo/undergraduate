#include <argus.h>

/* Schema used by the select expression */
static schema_t *reschema;

static int resolve_help (struct sql_expr *e)
{
	if (e->flag == EXPR_PRE_FIELD || e->flag == EXPR_PRE_LEAF)
	{
		struct sql_source *s;
		aggre_t *aggre;
		type_t *itype;
		func_t *func;
		int f, i;
		char buf[256];
		sql_lookup_field(e->nsource, e->nfield, &s, &f);
		free(e->nsource);
		free(e->nfield);
		if (e->flag == EXPR_PRE_FIELD)
		{
			aggre = NULL;
			if (e->naggre != NULL)
			{
				if (s != NULL)
				{
					aggre = aggre_load(e->naggre, s->stream->schema->field[f].type);
				}
				else
				{
					aggre = aggre_load(e->naggre, TYPE_VOID);
				}
				free(e->naggre);
				if (aggre == NULL) { sql_ok = 0; return -1;}
				e->type = aggre->otype;
				e->aggre = aggre;
				aggre_field_name(buf, e->aggre->name, s, f);
				i = schema_field(reschema, buf);
				assert(i >= 0);
				e->index = i;
				e->offset = reschema->field[i].offset;
			}
			else
			{
				e->aggre = NULL;
				joined_field_name(buf, s, f);
				i = schema_field(reschema, buf);
				if (i < 0) sql_ok = 0;
				e->index = i;
				e->offset = reschema->field[i].offset;
				e->type = reschema->field[i].type;
			}
		}
		else
		{
			joined_field_name(buf, s, f);
			i = schema_field(reschema, buf);
			assert(i >= 0);
			e->index = i;
			e->offset = reschema->field[i].offset;
			itype = reschema->field[i].type;
			func = func_load(e->nfunc, itype, TYPE_NULL);
			free(e->nfunc);
			e->func = func;
			e->type = func->result;
		}
	}
	else if (e->flag == EXPR_PRE_IN)
	{
		func_t *func;
		resolve_help(e->lc);
		resolve_help(e->rc);
		func = func_load(e->nfunc, e->lc->type,
				e->rc->type);
		assert(func != NULL);
		e->func = func;
		e->type = func->result;
	}
	return 0;
}

int sql_resolve_map (void)
{
	struct sql_map *i;
	reschema = query.joined_schema;
	if (query.grouped_schema != NULL)
		reschema = query.grouped_schema;
	i = (struct sql_map *)llist_next(query.map);
	while (i != NULL)
	{
		resolve_help(i->expr);
		i = (struct sql_map *)llist_next(i->link);
	}
	return 0;
}

