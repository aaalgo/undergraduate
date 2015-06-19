#ifndef __ARGUS_PLAN__
#define __ARGUS_PLAN__

typedef struct
{
	int nos;	/* number of streams */
	stream_t **stream;
	/* the dest opr of each stream operator */
	schedopr_t **stream_dest;
	schedopr_t **window;
	/* the filter on every stream, if exist */
	schedopr_t **filter;
	/* the joins on every stream, if exist */
	schedopr_t *join;
	schedopr_t *group;
	schedopr_t *having;
	schedopr_t *map;
	schedopr_t *sender;
	argus_callback_f callback;
	void *callback_param;
} plan_t;

int query_init (void);
int query_cleanup (void);
int register_query (void);
int deregister_query (int id);

#endif

