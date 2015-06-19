typedef union {
	int value;
	char *text;
} YYSTYPE;
#define	OP_ALU	258
#define	OP_NOP	259
#define	OP_SALU	260
#define	OP_LOAD	261
#define	OP_STORE	262
#define	OP_LACC	263
#define	OP_CONST	264
#define	OP_JZ	265
#define	OP_JMP	266
#define	OP_JACC	267
#define	OP_JZACC	268
#define	COL	269
#define	SEM	270
#define	END	271
#define	DOT	272
#define	EQU	273
#define	INT	274
#define	LABEL	275


extern YYSTYPE yylval;
