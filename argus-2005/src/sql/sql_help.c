#include <argus.h>

struct sql_query query;
int sql_ok;


int cmp_inv (int cmp)
{
	if (cmp == CMP_GT) return CMP_LT;
	if (cmp == CMP_GE) return CMP_LE;
	if (cmp == CMP_LT) return CMP_GT;
	if (cmp == CMP_GE) return CMP_GE;
	return cmp;
}

char *cmp2text (int cmp)
{
	static char *text[] = {"null", "equ", "gt", "ge", "lt", "le", "ne"};
	if (cmp < CMPNUM) return text[cmp];
	return NULL;
}

type_t *sql_field_type (struct sql_source *src, int fld)
{
	if (src->flag == SOURCE_STREAM)
		return src->stream->schema->field[fld].type;
	return NULL;
}

/* recalculate the offset data */
	
static struct sql_source *lookup_source_field (struct sql_source *src, char *name, int *fld)
{
	if (src->stream != NULL)
	{
		*fld = schema_field(src->stream->schema, name);
		return *fld >= 0 ? src : NULL;
	}
	else if (src->table != NULL)
	{
		sql_ok = 0;
		return NULL;
	}
	else assert(0);	
	return NULL;
}

int sql_lookup_field (char *nsrc, char *nfld, struct sql_source **src, int *fld)
{
	if (nsrc == NULL)
	{
		struct sql_source *i;
		if (nfld == NULL)
		{
			*src = NULL;
			*fld = 0;
			return 0;
		}
		i = (struct sql_source *)llist_next(query.source);
		while (i != NULL)
		{
			*src = lookup_source_field(i, nfld, fld);
			if (*src != NULL) return 0;
			i = (struct sql_source *)llist_next(i->link);
		}
		*src = NULL;
		return -1;	
	}
	else
	{
		struct sql_source *i = (struct sql_source *)llist_next(query.source);
		while (i != NULL)
		{
			if (strcmp(i->stream->name, nsrc) == 0) break;
			if (strcmp(i->alias, nsrc) == 0) break;
			i = (struct sql_source *)llist_next(i->link);
		}
		if (i == NULL)
		{
			sql_ok = 0;
			*src = NULL;
			return -1;
		}
		*src = lookup_source_field(i, nsrc, fld);
		return *src != NULL ? 0 : -1;
	}
}

int sql_append_map (struct sql_expr *expr, char *alias)
{
	struct sql_map *map;
	map = type_alloc(struct sql_map);
	map->expr = expr;
	map->alias = alias;
	llist_append(&query.map, map);
	return 0;
}

int sql_append_src_filter (func_t *comp, struct sql_source *src, int fld, void *data, type_t *type)
{
	struct sql_filter *filter;
	filter = type_alloc(struct sql_filter) ;
	filter->source = src;
	filter->field = fld;
	filter->data = data;
	filter->type = type;
	filter->comp = comp;
	llist_append(&(src->filter), filter);
	return 0;
}

int sql_append_filter (func_t *func, struct sql_source *src1, int fld1, struct sql_source *src2, int fld2)
{
	struct sql_filter *filter;
	filter = type_alloc(struct sql_filter);
	filter->source = src1;
	filter->field = fld1;
	filter->source2 = src2;
	filter->field2 = fld2;
	filter->comp = func;
	llist_append(&(query.filter), filter);
	return 0;
}

int sql_append_group (struct sql_source *src, int fld)
{
	struct sql_group *grp;
	grp = type_alloc(struct sql_group);
	grp->source = src;
	grp->field = fld;
	llist_append(&query.group, grp);
	return 0;
}

int sql_append_aggre (char *func, char *src, char *fld)
{
	struct sql_aggre *aggre;
	aggre = type_alloc(struct sql_aggre);
	aggre->naggre = func;
	aggre->nsource = src;
	aggre->nfield = fld;
	llist_append(&(query.aggre), aggre);
	return 0;
}

int sql_resolve_aggre (void)
{
	struct sql_aggre *aggre;
	aggre = (struct sql_aggre *)llist_next(query.aggre);
	while(aggre != NULL)
	{
		struct sql_source *src;
		int field, ret;
		aggre_t *ag;
		if (aggre->nsource == NULL && aggre->nfield == NULL)
		{
			aggre->source = NULL;
			aggre->field = -1;
			aggre->aggre = aggre_load(aggre->naggre, TYPE_VOID);
		}
		else
		{
			ret = sql_lookup_field(aggre->nsource, aggre->nfield, &src, &field);
			aggre->source = src;
			aggre->field = field;
			ag = NULL;
			if (ret == 0)
			{
				ag = aggre_load(aggre->naggre, src->stream->schema->field[field].type);
			}
			aggre->aggre = ag;
			if (aggre->aggre == NULL) sql_ok = 0;
		}
		aggre = (struct sql_aggre *)llist_next(aggre->link);
	}
	return 0;
}

int sql_append_aggre_resolved (aggre_t *func, struct sql_source *src, int fld)
{
	struct sql_aggre *aggre;
	aggre = type_alloc(struct sql_aggre);
	aggre->aggre = func;
	aggre->source = src;
	aggre->field = fld;
	llist_append(&(query.aggre), aggre);
	return 0;
}


int sql_append_group_filter_pre (int cmp, struct sql_source *src, int fld, aggre_t *aggre, void *data, type_t *type)
{
	func_t *f;
	struct sql_group_filter *pre;
	pre = type_alloc(struct sql_group_filter);
	pre->aggre = aggre;
	pre->source = src;
	pre->field = fld;
	pre->type = type;
	pre->data = data;
	f = func_load(cmp2text(cmp), aggre->otype, type);
	if (f == NULL) sql_ok = 0;
	pre->comp = f;
	llist_append(&(query.aggre), pre);
	return 0;
}


/* ---------------------------------------------------------------------- */

int joined_field_name (char *buf, struct sql_source *src, int fld)
{
	sprintf(buf, "%s#%d", src->stream->name, fld);
	return 0;
}

int aggre_field_name (char *buf, char *aggre, struct sql_source *src, int fld)
{
	if (aggre != NULL)
	{
		if (src == NULL)
		{
			sprintf(buf, "%s#*", aggre);
		}
		else
		{
			sprintf(buf, "%s#%s#%d", aggre, src->stream->name, fld);
		}
	}
	else
		sprintf(buf, "%s#%d", src->stream->name, fld);
	return 0;
}

int make_joined_schema (void)
{
	int nof, j;
	schema_t *sch;
	struct sql_source *i;
	nof = 0;
	i = (struct sql_source *)llist_next(query.source);
	while (i != NULL)
	{
		nof += i->stream->schema->nof;
		i = (struct sql_source *)llist_next(i->link);		
	}
	sch = (schema_t *)xmalloc(sizeof(schema_t) + nof * sizeof(field_t));
	sch->nof = nof;
	i = (struct sql_source *)llist_next(query.source);
	nof = 0;
	while (i != NULL)
	{
		for (j = 0; j < i->stream->schema->nof; j++)
		{
			joined_field_name(sch->field[nof].name, i, j);
			sch->field[nof].type = i->stream->schema->field[j].type;
			nof++;
		}
		i = (struct sql_source *)llist_next(i->link);
	}
	fix_schema(sch);
	query.joined_schema = sch;
	return 0;
}


int make_grouped_schema  (void)
{
	int nof;
	schema_t *sch;
	struct sql_group *grp;
	struct sql_aggre *agg;
	stream_t *str;
	int no_group, no_aggre;
	no_group = llist_count(query.group);
	no_aggre = llist_count(query.aggre);
	nof = no_group + no_aggre;
	if (nof == 0) return 0;
	sch = schema_alloc(nof);
	sch->nof = nof;
	grp = (struct sql_group *)llist_next(query.group);
	nof = 0;
	while (grp != NULL)
	{
		str = grp->source->stream;
		joined_field_name(sch->field[nof].name, grp->source, grp->field);
		sch->field[nof].type = str->schema->field[grp->field].type;
		grp = (struct sql_group *)llist_next(grp->link);
		nof++;
	}
	agg = (struct sql_aggre *)llist_next(query.aggre);
	while (agg != NULL)
	{
		aggre_field_name(sch->field[nof].name, agg->aggre->name, agg->source, agg->field);
		sch->field[nof].type = agg->aggre->otype;
		agg = (struct sql_aggre *)llist_next(agg->link);
		nof++;
	}
	fix_schema(sch);
	query.grouped_schema = sch;
	return 0;
}

int make_mapped_schema (void)
{
	int nof;
	schema_t *sch;
	struct sql_map *i;
	if (query.sel_all)
	{
		if (query.grouped_schema != NULL)
			query.mapped_schema = schema_dup(query.grouped_schema);
		else
			query.mapped_schema = schema_dup(query.joined_schema);
		return 0;
	}
	nof = llist_count(query.map);
	sch = schema_alloc(nof);
	sch->nof = nof;
	nof = 0;
	i = (struct sql_map *)llist_next(query.map);
	while (i != NULL)
	{
		if (i->alias == NULL)
		{
			strcpy(sch->field[nof].name, "");
		}
		else
		{
			strcpy(sch->field[nof].name, i->alias);
		}
		sch->field[nof].type = i->expr->type;
		i = (struct sql_map *)llist_next(i->link);
		nof++;
	}
	fix_schema(sch);
	query.mapped_schema = sch;
	return 0;	
}

/* ------------------------------------------------------------ */
void sql_free_expr (struct sql_expr *expr)
{
	if (expr->flag == EXPR_PRE_IN)
	{
		sql_free_expr(expr->lc);
		sql_free_expr(expr->rc);
	}
	else if (expr->flag == EXPR_PRE_DATA)
	{
		if (!sql_ok)
		{
			if (expr->type->free != NULL)
				expr->type->free(expr->data);
		}
	}
	free(expr);
}

int sql_cleanup_query (void)
{
	void *lnode;
	struct sql_map *map;
	struct sql_source *src;
	struct sql_filter *filter;
	struct sql_group_filter *gfp;
	map = (struct sql_map *)llist_next(query.map);
	while (map != NULL)
	{
		sql_free_expr(map->expr);
		if (map->alias != NULL) free(map->alias);
		lnode = map;
		map = (struct sql_map *)llist_next(map->link);
		free(lnode);
	}
	src = (struct sql_source *)llist_next(query.source);
	while (src != NULL)
	{
		if (src->alias != NULL) free(src->alias);
		filter = (struct sql_filter *)llist_next(src->filter);
		while (filter != NULL)
		{
			if (!sql_ok)
			{
				if (filter->type->free != NULL)
					filter->type->free(filter->data);
				free(filter->data);
			}
			lnode = filter;
			filter = (struct sql_filter *)llist_next(filter->link);
			free(lnode);
		}
		lnode = src;
		src = (struct sql_source *)llist_next(src->link);
		free(lnode);
	}
	llist_free_lazy(&query.group);
	llist_free_lazy(&query.aggre);
	gfp = (struct sql_group_filter *)llist_next(query.group_filter);
	while (gfp != NULL)
	{
		if (gfp->type->free != NULL)
			gfp->type->free(gfp->data);
		free(gfp->data);
		lnode = gfp;
		gfp = (struct sql_group_filter *)llist_next(gfp->link);
		free(lnode);
	}
	if (query.joined_schema != NULL) free(query.joined_schema);
	if (query.grouped_schema != NULL) free(query.grouped_schema);
	if (query.mapped_schema != NULL) free(query.mapped_schema);
	return 0;
}

/* ------------------------------------------------------------- */

int sql_resolve_group_filter (void)
{
	int i;
	struct sql_group_filter *tmp;
	tmp = (struct sql_group_filter *)llist_next(query.group_filter);
	while (tmp != NULL)
	{
		aggre_field_name (sql_buf, tmp->aggre == NULL ? NULL : tmp->aggre->name, tmp->source, tmp->field);		
		i = schema_field(query.grouped_schema, sql_buf);
		tmp->field = i;	
	}
	return 0;
}

int sql_resolve_group (void)
{
	struct sql_group *grp;
	struct sql_aggre *agg;
	char buf[MAX_ID_LEN];
	grp = (struct sql_group *)llist_next(query.group);
	while (grp != NULL)
	{
		int field;
		joined_field_name(buf, grp->source, grp->field);
		field = schema_field(query.joined_schema, buf);
		assert(field >= 0);
		grp->source = NULL;
		grp->field = field;
		grp = (struct sql_group *)llist_next(grp->link);
	}
	agg = (struct sql_aggre *)llist_next(query.aggre);
	while (agg != NULL)
	{
		int field;
		if (agg->source == NULL)
		{
			field = 0;
		}
		else
		{
			joined_field_name(buf, agg->source, agg->field);
			field = schema_field(query.joined_schema, buf);
			assert(field >= 0);
		}
		agg->source = NULL;
		agg->field = field;
		agg = (struct sql_aggre *)llist_next(agg->link);
	}
	return 0;
}

void sql_scan_string (char *);
int sqlparse (void);

int sql_compile (char *sql)
{
	memset(&query, 0, sizeof query);
	sql_ok = 1;
	sql_scan_string(sql);
	sqlparse();
	if (sql_ok) reorder_join();
	if (sql_ok) make_joined_schema();
	if (sql_ok) make_grouped_schema();
	if (sql_ok) sql_resolve_group();
	if (sql_ok) sql_resolve_group_filter();
	if (sql_ok) sql_resolve_map();
	if (sql_ok) make_mapped_schema();
	return 0;	
}

int explain_sql (char *sql)
{
	sql_compile(sql);
	if (sql_ok)
	{
		sql_dump();
	}
	else printf("PARSE ERROR.\n");
	sql_cleanup_query();
	return 0;	
}
