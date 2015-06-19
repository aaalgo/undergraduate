#include <argus.h>

char sql_buf[256];

int sql_dump_expr (struct sql_expr *expr)
{
	if (expr->flag == EXPR_PRE_DATA)
	{
		expr->type->to_string(expr->data, sql_buf, 256);
		printf("(DATA %s)", sql_buf);
	}
	else if (expr->flag == EXPR_PRE_FIELD)
	{
/*		if (expr->aggre)
		{
			printf("FIELD (%s %d)", expr->aggre->name, expr->index);
		}
		else
		{*/
			printf("FIELD (%d)", expr->index);
/*		}*/
	}
	else if (expr->flag == EXPR_PRE_LEAF)
	{
		if (expr->func)
		{
			printf("LEAF (%s %d)", expr->func->name, expr->index);
		}
		else assert(0);
	}
	else if (expr->flag == EXPR_PRE_IN)
	{
		if (expr->func)
		{
			printf("%s (", expr->func->name);
			sql_dump_expr(expr->lc);
			printf(", ");
			sql_dump_expr(expr->rc);
			printf(")");
		}
		else assert(0);
	}
	return 0;
}



int sql_dump (void)
{
	struct sql_source *src;
	struct sql_filter *flt;
	struct sql_group *grp;
	struct sql_aggre *agg;
	struct sql_map *map;
	printf("Dumping SQL query....\n");
	src = (struct sql_source *)llist_next(query.source);
	printf("SOURCES:\n");
	while (src != NULL)
	{
		assert(src->flag == SOURCE_STREAM);
		printf("\tNAME: %s\n", src->stream->name);
		if (src->alias != NULL)
			printf("ALIAS %s\n", src->alias);
		printf("\tTYPE: %d\n", src->type);
		printf("\tSIZE: %d\n", src->size);
		printf("\tSTART: %d\n", src->start);
		printf("\tCOUNT: %d\n", src->count);
		flt = (struct sql_filter *)llist_next(src->filter);
		if (flt != NULL) printf("\tFILTER:\n");
		while (flt != NULL)
		{
			assert(flt->source == src);
			flt->type->to_string(flt->data, sql_buf, 256);
			printf("\t\t#%d %s %s\n", flt->field, flt->comp->name, sql_buf);
			flt = (struct sql_filter *)llist_next(flt->link);
		}
		printf("\n");
		src = (struct sql_source *)llist_next(src->link);
	}
	flt = (struct sql_filter *)llist_next(query.filter);
	if (flt != NULL) printf("JOIN FILTER:\n");
	while (flt != NULL)
	{
		printf("\t%s#%d %s %s#%d\n", flt->source->stream->name, flt->field,
				flt->comp->name, flt->source->stream->name, flt->field);
		flt = (struct sql_filter *)llist_next(flt->link);
	}
	grp = (struct sql_group *)llist_next(query.group);
	if (grp != NULL) printf("GROUP BY:\n");
	while (grp != NULL)
	{
		printf("%d\n", grp->field);
		grp = (struct sql_group *)llist_next(grp->link);
	}
	agg = (struct sql_aggre *)llist_next(query.aggre);
	if (agg != NULL) printf("AGGREGATE:\n");
	while (agg != NULL)
	{
		printf("\t%s(%d)\n", agg->aggre->name, agg->field);
		agg = (struct sql_aggre *)llist_next(agg->link);		
	}
	flt = (struct sql_filter *)llist_next(query.group_filter);
	if (flt != NULL) printf("HAVING:\n");
	while (flt != NULL)
	{
		flt->type->to_string(flt->data, sql_buf, 256);
		printf("\t%d %s %s\n", flt->field,
				flt->comp->name, sql_buf);
		flt = (struct sql_filter *)llist_next(flt->link);
	}
	map = (struct sql_map *)llist_next(query.map);
	if (query.joined_schema)
	{
		printf("Joined Schema:\n");
		schema_dump(query.joined_schema);
	}
	if (query.grouped_schema)
	{
		printf("Grouped Schema:\n");
		schema_dump(query.grouped_schema);
	}
	if (query.mapped_schema)
	{
		printf("Mapped Schema:\n");
		schema_dump(query.mapped_schema);
	}
	printf("SELECT:\n");
	while (map != NULL)
	{
		printf("\t");
		sql_dump_expr(map->expr);
		if (map->alias != NULL)
		{
			printf(" AS %s\n", map->alias);
		}
		else printf("\n");
		map = (struct sql_map *)llist_next(map->link);
	}	
	printf("\nSQL query dumped.\n");
	return 0;
}

