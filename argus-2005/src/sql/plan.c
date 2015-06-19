#include <argus.h>

static plan_t *plans[MAX_QUERY];

int query_init (void)
{
	memset(&plans, 0, sizeof plans);
	return 0;
}

/* remove every query plan */
int query_cleanup (void)
{
	int i;
	for (i = 0; i < MAX_QUERY; i++)
	{
		if (plans[i] != NULL) deregister_query(i);
	}
	return 0;
}

int deregister_query (int id)
{
	int i;
	argus_callback_f cb;
	void *cbdata;
	if (id < 0 || id >= MAX_QUERY) return -1;
	if (plans[id] == NULL) return -1;
	cb = plans[id]->callback;
	cbdata = plans[id]->callback_param;
	for (i = 0; i < plans[id]->nos; i++)
	{
		sched_remove_dest(plans[id]->stream[i]->opr, plans[id]->stream_dest[i]);
		if (plans[id]->window[i] != NULL)
			sched_remove_operator(plans[id]->window[i]);
		if (plans[id]->filter[i] != NULL)
			sched_remove_operator(plans[id]->filter[i]);
	}
	if (plans[id]->join != NULL) sched_remove_operator(plans[id]->join);
	if (plans[id]->group != NULL) sched_remove_operator(plans[id]->group);
	if (plans[id]->having != NULL) sched_remove_operator(plans[id]->having);
	if (plans[id]->map != NULL) sched_remove_operator(plans[id]->map);
	if (plans[id]->sender != NULL) sched_remove_operator(plans[id]->sender);
	free(plans[id]->stream);
	free(plans[id]->stream_dest);
	free(plans[id]->window);
	free(plans[id]->filter);
	free(plans[id]);
	plans[id] = NULL;
	cb(cbdata, ARGUS_DEREGISTERED, 0, NULL);
	return 0;
}


int register_query (void)
{
	struct sql_source *i;
	int j;
	plan_t *plan;
	int no_stream;
	schedopr_t *str_last[MAX_SOURCE];
	schedopr_t *all_last;
	no_stream = llist_count(query.source);
	assert(no_stream == 1);
	plan = type_alloc(plan_t);
	plan->nos = no_stream;
	plan->callback = __callback;
	plan->callback_param = __callback_param;
	plan->stream = type_calloc(no_stream, stream_t *);
	plan->stream_dest = type_calloc(no_stream, schedopr_t *);
	plan->window = type_calloc(no_stream, schedopr_t *);
	plan->filter = type_calloc(no_stream, schedopr_t *);
	i = (struct sql_source *)llist_next(query.source);
	j = 0;
	while (i != NULL)
	{
		if (i->stream != NULL)
		{
			plan->stream[j] = i->stream;
			str_last[j] = plan->stream[j]->opr;
			if (i->type == WINDOW_NONE)
			{
				plan->stream_dest[j] = NULL;
				plan->window[j] = NULL;
			}
			else if (i->type == (WINDOW_SLIDE | WINDOW_TIME))
			{
				operator_t *opr = time_slide_create(i->size, i->size > 100 ? i->size /100 : 1);
				sched_add_operator(opr, 0);
				sched_add_dest(plan->stream[j]->opr, opr->schedopr);
				plan->window[j] = opr->schedopr;
				plan->stream_dest[j] = opr->schedopr;
				str_last[j] = opr->schedopr;
			}
			else if (i->type == (WINDOW_SLIDE | WINDOW_ROW))
			{
				operator_t *opr = count_slide_create(i->size);
				sched_add_operator(opr, 0);
				sched_add_dest(plan->stream[j]->opr, opr->schedopr);
				plan->window[j] = opr->schedopr;
				plan->stream_dest[j] = opr->schedopr;
				str_last[j] = opr->schedopr;
			}
			else if (i->type == (WINDOW_TUMBLE | WINDOW_TIME))
			{
				operator_t *opr = time_tumble_create(i->size, i->count);
				sched_add_operator(opr, 0);
				sched_add_dest(plan->stream[j]->opr, opr->schedopr);
				plan->window[j] = opr->schedopr;
				plan->stream_dest[j] = opr->schedopr;				
				str_last[j] = opr->schedopr;
			}
			else if (i->type == (WINDOW_TUMBLE | WINDOW_ROW))
			{
				operator_t *opr = count_tumble_create(i->size);
				sched_add_operator(opr, 0);
				sched_add_dest(plan->stream[j]->opr, opr->schedopr);
				plan->window[j] = opr->schedopr;
				plan->stream_dest[j] = opr->schedopr;
				str_last[j] = opr->schedopr;
			}
			else assert(0);
			if (!llist_empty(i->filter) > 0)
			{
				operator_t *opr = filter_create(i->stream->schema, i->filter);
				sched_add_operator(opr, 0);
				plan->filter[j] = opr->schedopr;
				if (plan->stream_dest[j] == NULL)
				{
					plan->stream_dest[j] = opr->schedopr;
					sched_add_dest(plan->stream[j]->opr, opr->schedopr);
				}
				else
				{
					sched_add_dest(plan->stream_dest[j], opr->schedopr);
				}
				str_last[j] = opr->schedopr;
			}
		}
		else assert(0);
		i = (struct sql_source *)llist_next(i->link);
		j++;
	}
	if (no_stream > 1)
	{
		/* Join */
		operator_t *j1, *j2;
		struct sql_filter *f;
		struct sql_source *src1, *src2;
		assert(no_stream == 2);

		src1 = (struct sql_source *)llist_next(query.source);
		src2 = (struct sql_source *)llist_next(src1->link);

		f = (struct sql_filter*)llist_next(query.filter);
		while (f != NULL)
		{
			assert(f->source == src1);
			assert(f->source2 == src2);
			f = (struct sql_filter*)llist_next(f->link);
		}
		join_pair_create(query.filter, query.joined_schema, &j1, &j2);
		sched_add_operator(j1, 0);
		sched_add_operator(j2, 0);
		sched_add_dest(str_last[0], j1->schedopr);
		sched_add_dest(str_last[1], j2->schedopr);
		str_last[0] = j1->schedopr;

	}
/*	else*/
	{
		operator_t *opr;
		plan->join = NULL;
		all_last = str_last[0];
		plan->group = NULL;
		if (llist_count(query.group) + llist_count(query.aggre) != 0)
		{
			opr = group_create(query.grouped_schema, query.joined_schema,
					query.group, query.aggre);
			sched_add_operator(opr, 0);
			sched_add_dest(all_last, opr->schedopr);
			all_last = opr->schedopr;
			plan->group = opr->schedopr;
			if (plan->stream_dest[0] == NULL)
				plan->stream_dest[0] = opr->schedopr;
		}
		plan->having = NULL;
		/* Group */
		/* Having */
		plan->map = NULL;
		if (!query.sel_all)
		{
			opr = map_create(query.grouped_schema == NULL ? query.joined_schema : query.grouped_schema, query.mapped_schema, query.map);
			sched_add_operator(opr, 0);
			sched_add_dest(all_last, opr->schedopr);
			plan->map = opr->schedopr;
			all_last = opr->schedopr;
			if (plan->stream_dest[0] == NULL)
				plan->stream_dest[0] = opr->schedopr;

		}
		opr = (operator_t *)sender_create(__callback, __callback_param);
		sched_add_operator(opr, 0);
		sched_add_dest(all_last, opr->schedopr);
		plan->sender = opr->schedopr;
		if (plan->stream_dest[0] == NULL)
			plan->stream_dest[0] = opr->schedopr;

	}
	for (j = 0; j <  MAX_QUERY; j++)
		if (plans[j] == NULL)
		{
			plans[j] = plan;
			return j;
		}
	assert(0);
	return -1;
}

