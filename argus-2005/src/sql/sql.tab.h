typedef union {
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
} YYSTYPE;
#define	K_ADD	258
#define	K_AND	259
#define	K_AS	260
#define	K_ASTERISK	261
#define	K_BY	262
#define	K_CMP	263
#define	K_COMMA	264
#define	K_COUNT	265
#define	K_DIV	266
#define	K_EVERY	267
#define	K_FALSE	268
#define	K_FLOAT	269
#define	K_FROM	270
#define	K_GROUP	271
#define	K_HAVING	272
#define	K_HOUR	273
#define	K_ID	274
#define	K_INTEGER	275
#define	K_LP	276
#define	K_MINUTE	277
#define	K_ORDER	278
#define	K_PERIOD	279
#define	K_PRECEDING	280
#define	K_ROW	281
#define	K_RP	282
#define	K_SECOND	283
#define	K_SELECT	284
#define	K_STRING	285
#define	K_SUB	286
#define	K_TOP	287
#define	K_TRUE	288
#define	K_WHERE	289


extern YYSTYPE sqllval;
