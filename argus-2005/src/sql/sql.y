%{
#include <argus.h>

void sqlerror (char *);
int sqllex (void);

int source_parsed;
%}

%union {
	char *text;
	int int_value;
	float float_value;
	struct {
		aggre_t *aggre;
		union {
			struct {
/* A: */			struct sql_source *source;
/* A: */			int field;
			};
			struct {
/* P: */			char *nsource;
/* P: */			char *nfield;
			};
		};
	} field;
	struct {
		type_t *type;
		void *data;
	} constant;
	struct sql_expr *expr;
}

%token K_ADD
%token K_AND
%token K_AS
%token K_ASTERISK
%token K_BY
%token <int_value>K_CMP
%token K_COMMA
%token K_COUNT
%token K_DIV
%token K_EVERY
%token K_FALSE
%token <float_value>K_FLOAT
%token K_FROM
%token K_GROUP
%token K_HAVING
%token K_HOUR
%token <text>K_ID
%token <int_value>K_INTEGER
%token K_LP
%token K_MINUTE
%token K_ORDER
%token K_PERIOD
%token K_PRECEDING
%token K_ROW
%token K_RP
%token K_SECOND
%token K_SELECT
%token <text>K_STRING
%token K_SUB
%token K_TOP
%token K_TRUE
%token K_WHERE

%type <text>opt_rename
%type <field>field
%type <field>grouped_field
%type <constant>constant
%type <expr>expr
%type <expr>term
%type <expr>factor

%%

session		: query
		;
		
query		: K_SELECT
		opt_topN
		{ source_parsed = 0; }
		select
		K_FROM source_list
		{ sql_resolve_aggre(); source_parsed = 1; }
		opt_where
		opt_group
		opt_order
		;

opt_topN	: K_TOP K_INTEGER
		{
			query.topN = $2;
		}
		|
		;
		
select		: K_ASTERISK	/* SELECT * FROM ... */
		{
			query.sel_all = 1;
		}
		| expr_list
		;

expr_list	: expr_list K_COMMA expr opt_rename
		{
			sql_append_map($3, $4);
		}
		| expr opt_rename
		{
			sql_append_map($1, $2);
		}
		;

expr		: expr K_ADD term
		{
			struct sql_expr *expr;
			expr = type_alloc(struct sql_expr);
			expr->flag = EXPR_PRE_IN;
			expr->nfunc = strdup("add");
			expr->lc = $1;
			expr->rc = $3;
			$$ = expr;
			
		}
		| expr K_SUB term
		{
			struct sql_expr *expr;
			expr = type_alloc(struct sql_expr);
			expr->flag = EXPR_PRE_IN;
			expr->nfunc = strdup("sub");
			expr->lc = $1;
			expr->rc = $3;
			$$ = expr;
		}
		| term
		{
			$$ = $1;
		}
		;

term		: term K_ASTERISK factor
		{
			struct sql_expr *expr;
			expr = type_alloc(struct sql_expr);
			expr->flag = EXPR_PRE_IN;
			expr->nfunc = strdup("mul");
			expr->lc = $1;
			expr->rc = $3;
			$$ = expr;
			
		}
		| term K_DIV factor
		{
			struct sql_expr *expr;
			expr = type_alloc(struct sql_expr);
			expr->flag = EXPR_PRE_IN;
			expr->nfunc = strdup("div");
			expr->lc = $1;
			expr->rc = $3;
			$$ = expr;
			
		}
		| factor
		{
			$$ = $1;
		}
		;

factor		: field
		{
			struct sql_expr *expr;
			expr = type_alloc(struct sql_expr);
			expr->flag = EXPR_PRE_FIELD;
			expr->nsource = $1.nsource;
			expr->nfield = $1.nfield;
			expr->nfunc = NULL;
			expr->naggre = NULL;
			$$ = expr;
			
		}
		| K_COUNT K_LP K_ASTERISK K_RP
		{
			struct sql_expr *expr;
			sql_append_aggre("count", NULL, NULL);
			expr = type_alloc(struct sql_expr);
			expr->flag = EXPR_PRE_FIELD;
			expr->nsource = NULL;
			expr->nfield = NULL;
			expr->naggre = strdup("count");
			$$ = expr;
		}
		| K_ID K_LP field K_RP
		{
			struct sql_expr *expr;
			int func = is_aggre($1);
			expr = type_alloc(struct sql_expr);
			if (func)
			{
				sql_append_aggre($1, $3.nsource, $3.nfield);
				expr->flag = EXPR_PRE_FIELD;
				expr->nsource = $3.nsource;
				expr->nfield = $3.nfield;
				expr->naggre = $1;
				expr->func = NULL;
			}
			else
			{
				expr->flag = EXPR_PRE_LEAF;
			      	expr->nsource = $3.nsource;
				expr->nfield = $3.nfield;
				expr->nfunc = $1;
				expr->naggre = NULL;
			}
			$$ = expr;
		}
		| K_LP expr K_RP
		{
			$$ = $2;
		}
		| constant
		{
			struct sql_expr *expr;
			expr = type_alloc(struct sql_expr);
			expr->flag = EXPR_PRE_DATA;
			expr->type = $1.type;
			expr->data = $1.data;
			expr->func = NULL;
			$$ = expr;
		}
		;

field	 	: K_ID K_PERIOD K_ID
		{
			if (source_parsed)
			{
				int fld, ret;
				struct sql_source *src;
				ret = sql_lookup_field($1, $3, &src, &fld);
				if (ret != 0) sql_ok = 0;
				$$.source = src;
				$$.field = fld;
				free($1); free($3);
			}
			else
			{
				$$.nsource = $1;
				$$.nfield = $3;
			}
		}
		| K_ID
		{
			if (source_parsed)
			{
				int fld, ret;
				struct sql_source *src;
				ret = sql_lookup_field(NULL, $1, &src, &fld);
				if (ret != 0) sql_ok = 0;
				$$.source = src;
				$$.field = fld;
				free($1);
			}
			else
			{
				$$.nsource = NULL;
				$$.nfield = $1;
			}
		}
		;

source_list	: source_list K_COMMA source
		| source
		;

source		: K_ID
		{
			query.last_source = type_alloc(struct sql_source);
			query.last_source->flag = SOURCE_STREAM;
			query.last_source->stream = stream_from_name($1);
			if (query.last_source->stream == NULL)
			{
				query.last_source->flag = SOURCE_TABLE;
				query.last_source->table = table_from_name($1);
			}
			if (query.last_source->stream == NULL) sql_ok = 0;
			query.last_source->type = 0;
			query.last_source->size = 0;
			query.last_source->count = 0;
			query.last_source->start = 1;
			free($1);
		}
       		opt_window opt_rename
		{
			query.last_source->alias = $4;
			llist_init(&(query.last_source->filter));
			llist_append(&query.source, query.last_source);
			query.last_source = NULL;
		}
		;

opt_window	: tumble
		{
			query.last_source->type |= WINDOW_TUMBLE;
		}
		| slide
		{
			query.last_source->type |= WINDOW_SLIDE;
		}
		|
		;

tumble		: K_EVERY K_INTEGER K_ROW
		{
			query.last_source->type |= WINDOW_ROW;
			query.last_source->size = $2;
		}
		| K_EVERY time
		{
			query.last_source->type |= WINDOW_TIME;
		}
		;

slide		: K_PRECEDING K_INTEGER K_ROW
		{
			query.last_source->type |= WINDOW_ROW;
			query.last_source->size = $2;
		}
		| K_PRECEDING time
		{
			query.last_source->type |= WINDOW_TIME;
		}
		;
		
time		: K_INTEGER K_SECOND
		{
			query.last_source->size = $1;
		}
		| K_INTEGER K_MINUTE
		{
			query.last_source->size = $1 * 60;
		}
		| K_INTEGER K_HOUR
		{
			query.last_source->size = $1 * 3600;
		}
		;
		
		
opt_rename	: K_AS K_ID
		{
			$$ = $2;
		}
		|
		{
			$$ = NULL;
		}
		;

opt_where	: K_WHERE bool_expr
		|
		;

bool_expr	: bool_expr K_AND compare
		| compare
		;

compare		: field K_CMP constant
		{
			func_t *f;
			type_t *ft = sql_field_type($1.source, $1.field);
/* check for memory leak */
			f = func_load(cmp2text($2), ft, $3.type);
			if (f == NULL) sql_ok = 0;
			sql_append_src_filter(f, $1.source, $1.field, $3.data, $3.type);
		}
		| constant K_CMP field
		{
			func_t *f;
			type_t *ft = sql_field_type($3.source, $3.field);
/* check for memory leak */
			$2 = cmp_inv($2);
			f = func_load(cmp2text($2), $1.type, ft);
			if (f == NULL) sql_ok = 0;
			sql_append_src_filter(f, $3.source, $3.field, $1.data, $1.type);
		}
		| field K_CMP field
		{
			type_t *ft1 = sql_field_type($1.source, $1.field);
			type_t *ft2 = sql_field_type($3.source, $3.field);
			func_t *f;
			f = func_load(cmp2text($2), ft1, ft2);
			if (f == NULL) sql_ok = 0;
			sql_append_filter(f, $1.source, $1.field, $3.source, $3.field);
		}
		| K_ID K_LP field K_RP
		{
			free($1);
			sql_ok = 0;
		}
		;

constant 	: K_STRING
		{
			char **tmp;
			$$.type = TYPE_STRING;
			tmp = type_alloc(char *);
			*tmp = $1;
			$$.data = tmp;
		}
		| K_INTEGER
		{
			$$.type = TYPE_INT;
			$$.data = type_alloc(int);
		       	*(int *)$$.data	= $1;
		}
		| K_FLOAT
		{
			$$.type = TYPE_FLOAT;
			$$.data = type_alloc(float);
			*(float *)$$.data = $1;
		}
		| K_TRUE
		{
			$$.type = TYPE_BOOL;
			$$.data = type_alloc(int);
		       	*(int *)$$.data	= 1;
		}
		| K_FALSE
		{
			$$.type = TYPE_BOOL;
			$$.data = type_alloc(int);
		       	*(int *)$$.data	= 0;
		}
		;

opt_group	: K_GROUP K_BY group_list opt_having
		|
		;

group_list	: group_list K_COMMA field
		{
			sql_append_group($3.source, $3.field);
		}
		| field
		{
			sql_append_group($1.source, $1.field);
		}
		;

opt_having	: K_HAVING having_expr
		|
		;

having_expr	: having_expr K_AND having_compare
		| having_compare
		;

having_compare	: grouped_field K_CMP constant
		{
			sql_append_group_filter_pre($2, $1.source, $1.field, $1.aggre, $3.data, $3.type); 
		}
		| constant K_CMP grouped_field
		{
			sql_append_group_filter_pre(cmp_inv($2), $3.source, $3.field, $3.aggre, $1.data, $1.type); 

		}
		;
		
grouped_field	: field
		{
			$$.aggre = NULL;
			$$.source = $1.source;
			$$.field = $1.field;
		}
		| K_ID K_LP field K_RP
		{
			$$.aggre = NULL;
			$$.source = $3.source;
			$$.field = $3.field;
			$$.aggre = aggre_load($1, $3.source->stream->schema->field[$3.field].type);
			free($1);
			if ($$.aggre == NULL) sql_ok = 0;
			else sql_append_aggre_resolved($$.aggre, $3.source, $3.field);
		}
		;

opt_order	: K_ORDER K_BY order_list
		|
		;

order_list	: order_list K_COMMA field
		| field
		;

%%

void sqlerror (char *msg)
{
		sql_ok = 0;		
		puts(msg);
}

