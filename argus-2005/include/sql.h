#ifndef __ARGUS_SQL__
#define __ARGUS_SQL__

#define WINDOW_NONE	0x0
#define WINDOW_SLIDE	0x1
#define WINDOW_TUMBLE	0x2
#define WINDOW_TIME	0x10
#define WINDOW_ROW	0x20

#define CMP_NULL	0x0
#define CMP_EQU		0x1
#define CMP_GT		0x2
#define CMP_GE		0x3
#define CMP_LT		0x4
#define CMP_LE		0x5
#define CMP_NE		0x6
#define CMPNUM		0x7

#define AGGRE_COUNT	0x0
#define AGGRE_SUM	0x1
#define AGGRE_MAX	0x2
#define AGGRE_MIN	0x3
#define AGGRENUM	0x4


typedef struct table table_t;

/* source can be a table or a stream,
   of .table and .stream only one is used and the other must be NULL */
struct sql_source
{
#define SOURCE_STREAM	1
#define SOURCE_TABLE	2
	lnode_t link;
	int flag;	/* indicates STREAM/TABLE */
	union {
		table_t *table;
		stream_t *stream;
	};
	char *alias;
	int type;
	int size;	/* window size in seconds */
	int start;	/* start time, used in TUMBLING windows */
	int count;
	lnode_t filter;	/* a linked list of filters */
};


struct sql_filter
{
	lnode_t link;	/* linked list */
	struct sql_source *source;	/* index to the source array in struct sql_query */
	int field;
/* one of (source2, field2) (data == NULL) and data  (data != NULL) is used */
	union {
		struct {
			struct sql_source *source2;
			int field2;
		};
		struct {
			type_t *type;	/* type of the data */
			void *data;
		};
	};
	func_t *comp;
};

/* List of fields grouped by */
struct sql_group
{
		lnode_t link;
/* P: */	struct sql_source *source;
/* A/P: */	int field;
/* Before resolving, (source field) indicates the sourse and field,
 * after ressolving, field indicates the field in the joined_schema to be grouped by */
};

struct sql_aggre
{
	lnode_t link;
	/* when func == AGGRE_COUNT, source and field can both be "" */
	union {
/* P: */		struct {
				/* these pointers should not be freed */
/* P: */			char *naggre;
/* P: */			char *nsource;
/* P: */			char *nfield;
				};
				struct {
/* A: */			aggre_t *aggre;
/* like sql_group */
/* A: */			struct sql_source *source;
/* A/P: */			int field;
				};
		};
};


/* used the represent the expression before FROM clause is reached,
 * when the streams involved are still unknown.
 * marker [P:] means pre-resovle
 *        [A:] means post-resovle
 *        no marker: can be accessed all the time
 */
struct sql_expr
{
#define EXPR_PRE_DATA	1	/* CONSTANT DATA */
#define EXPR_PRE_FIELD	2	/* LEAF NODE, FIELD */
#define EXPR_PRE_LEAF	3 	/* LEAF NODE, FIELD WITH FUNCTION */
#define EXPR_PRE_IN	4	/* INTERNAL NODE */	
	int flag;		/* ONE OF THE PREVIOUS 4 TYPES */
	union {	/* only used when there is a function */
/* P: */		char *nfunc; /* leaf node can have func */
/* A: */		func_t *func; /* usable after resolving */
	};
/* A: */type_t *type;
	union {
		union {
			struct {
/* P: */			char *nsource;
/* P: */			char *nfield;
/* P: */			char *naggre; /* whether an aggre function is applied on the field */
			};
			struct {
/* A: */			int index; /* index of the field in joined/grouped schema, usable after resolving */
/* A: */			int offset;
				aggre_t *aggre;
			};
		};
		void *data;
		struct {
			struct sql_expr *lc, *rc;
		};
	};
};

struct sql_map
{
	lnode_t link;
	struct sql_expr *expr;
	char *alias;
};

struct sql_group_filter
{
	lnode_t link;
/* P: */	aggre_t *aggre;
/* P: */	struct sql_source *source;
/* P & A: */	int field;
	type_t *type;
	void *data;
	func_t *comp;
};

struct sql_query
{
/* SELECT ... */
	int sel_all; /* SELECT * FROM ..., if sel_all == 1 then no_map must be 0 */
	/* select a series of expressions */
	lnode_t map;
/* FROM ... WHERE */
	struct sql_source *last_source;	/* for temporary use */
	lnode_t source;
	/* Join filters */
	lnode_t filter;
/* GROUP BY ... */ 
	lnode_t group;
	/* Aggregates */
	lnode_t aggre;
/* HAVING ... */
	union {
		lnode_t group_filter;
	};
/* ------------------------------------ */
	schema_t *joined_schema;
	schema_t *grouped_schema;
	schema_t *mapped_schema;
	int topN;
};

extern struct sql_query query;

int sql_append_map (struct sql_expr *, char *alias);
int sql_append_src_filter (func_t *comp, struct sql_source *src, int fld, void *data, type_t *type);
int sql_append_filter (func_t *comp, struct sql_source *src1, int fld1, struct sql_source *src2, int fld2);
int sql_append_group_filter_pre (int comp, struct sql_source *src, int fld, aggre_t *aggre, void *data, type_t *type);

int sql_append_group (struct sql_source *src, int fld);
int sql_append_aggre (char *aggre, char *src, char *fld);
int sql_resolve_aggre (void);
int sql_append_aggre_resolved (aggre_t *aggre, struct sql_source *src, int fld);

int sql_lookup_field (char *nsrc, char *nfld, struct sql_source **src, int *fld);
type_t *sql_field_type (struct sql_source *src, int fld);

int cmp_inv (int cmp);
char *cmp2text (int cmp);
int aggre_field_name (char *buf, char *aggre, struct sql_source *src, int fld);
int schema_field (schema_t *s, char *name);
int joined_field_name (char *buf, struct sql_source *src, int fld);

int make_joined_scheme (void);
int make_grouped_schema (void);
int sql_resolve_group_filter (void);
/* change sql_map_pre int the big query struct to sql_map */
int sql_resolve_map (void);

/* optimization functions */
int reorder_join (void);
int sql_dump (void);

int sql_compile (char *);
int explain_sql (char *sql);
int sql_cleanup_query(void);

extern int sql_ok;

static __inline table_t *table_from_name (char *name)
{
	return NULL;
}

extern char sql_buf[];
#endif
