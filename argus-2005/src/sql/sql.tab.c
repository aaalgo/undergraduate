
/*  A Bison parser, made from sql.y with Bison version GNU Bison version 1.24
  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse sqlparse
#define yylex sqllex
#define yyerror sqlerror
#define yylval sqllval
#define yychar sqlchar
#define yydebug sqldebug
#define yynerrs sqlnerrs
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

#line 1 "sql.y"

#include <argus.h>

void sqlerror (char *);
int sqllex (void);

int source_parsed;

#line 10 "sql.y"
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

#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		121
#define	YYFLAG		-32768
#define	YYNTBASE	35

#define YYTRANSLATE(x) ((unsigned)(x) <= 289 ? yytranslate[x] : 66)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     3,     4,    15,    18,    19,    21,    23,    28,
    31,    35,    39,    41,    45,    49,    51,    53,    58,    63,
    67,    69,    73,    75,    79,    81,    82,    87,    89,    91,
    92,    96,    99,   103,   106,   109,   112,   115,   118,   119,
   122,   123,   127,   129,   133,   137,   141,   146,   148,   150,
   152,   154,   156,   161,   162,   166,   168,   171,   172,   176,
   178,   182,   186,   188,   193,   197,   198,   202
};

static const short yyrhs[] = {    36,
     0,     0,     0,    29,    39,    37,    40,    15,    46,    38,
    54,    58,    64,     0,    32,    20,     0,     0,     6,     0,
    41,     0,    41,     9,    42,    53,     0,    42,    53,     0,
    42,     3,    43,     0,    42,    31,    43,     0,    43,     0,
    43,     6,    44,     0,    43,    11,    44,     0,    44,     0,
    45,     0,    10,    21,     6,    27,     0,    19,    21,    45,
    27,     0,    21,    42,    27,     0,    57,     0,    19,    24,
    19,     0,    19,     0,    46,     9,    47,     0,    47,     0,
     0,    19,    48,    49,    53,     0,    50,     0,    51,     0,
     0,    12,    20,    26,     0,    12,    52,     0,    25,    20,
    26,     0,    25,    52,     0,    20,    28,     0,    20,    22,
     0,    20,    18,     0,     5,    19,     0,     0,    34,    55,
     0,     0,    55,     4,    56,     0,    56,     0,    45,     8,
    57,     0,    57,     8,    45,     0,    45,     8,    45,     0,
    19,    21,    45,    27,     0,    30,     0,    20,     0,    14,
     0,    33,     0,    13,     0,    16,     7,    59,    60,     0,
     0,    59,     9,    45,     0,    45,     0,    17,    61,     0,
     0,    61,     4,    62,     0,    62,     0,    63,     8,    57,
     0,    57,     8,    63,     0,    45,     0,    19,    21,    45,
    27,     0,    23,     7,    65,     0,     0,    65,     9,    45,
     0,    45,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    77,    80,    84,    87,    91,    95,    98,   102,   105,   109,
   115,   126,   136,   142,   153,   164,   170,   182,   193,   217,
   221,   233,   251,   271,   272,   275,   292,   301,   305,   309,
   312,   317,   323,   328,   334,   338,   342,   349,   353,   359,
   360,   363,   364,   367,   376,   386,   395,   402,   410,   416,
   422,   428,   436,   437,   440,   444,   450,   451,   454,   455,
   458,   462,   469,   475,   487,   488,   491,   492
};

static const char * const yytname[] = {   "$","error","$undefined.","K_ADD",
"K_AND","K_AS","K_ASTERISK","K_BY","K_CMP","K_COMMA","K_COUNT","K_DIV","K_EVERY",
"K_FALSE","K_FLOAT","K_FROM","K_GROUP","K_HAVING","K_HOUR","K_ID","K_INTEGER",
"K_LP","K_MINUTE","K_ORDER","K_PERIOD","K_PRECEDING","K_ROW","K_RP","K_SECOND",
"K_SELECT","K_STRING","K_SUB","K_TOP","K_TRUE","K_WHERE","session","query","@1",
"@2","opt_topN","select","expr_list","expr","term","factor","field","source_list",
"source","@3","opt_window","tumble","slide","time","opt_rename","opt_where",
"bool_expr","compare","constant","opt_group","group_list","opt_having","having_expr",
"having_compare","grouped_field","opt_order","order_list",""
};
#endif

static const short yyr1[] = {     0,
    35,    37,    38,    36,    39,    39,    40,    40,    41,    41,
    42,    42,    42,    43,    43,    43,    44,    44,    44,    44,
    44,    45,    45,    46,    46,    48,    47,    49,    49,    49,
    50,    50,    51,    51,    52,    52,    52,    53,    53,    54,
    54,    55,    55,    56,    56,    56,    56,    57,    57,    57,
    57,    57,    58,    58,    59,    59,    60,    60,    61,    61,
    62,    62,    63,    63,    64,    64,    65,    65
};

static const short yyr2[] = {     0,
     1,     0,     0,    10,     2,     0,     1,     1,     4,     2,
     3,     3,     1,     3,     3,     1,     1,     4,     4,     3,
     1,     3,     1,     3,     1,     0,     4,     1,     1,     0,
     3,     2,     3,     2,     2,     2,     2,     2,     0,     2,
     0,     3,     1,     3,     3,     3,     4,     1,     1,     1,
     1,     1,     4,     0,     3,     1,     2,     0,     3,     1,
     3,     3,     1,     4,     3,     0,     3,     1
};

static const short yydefact[] = {     0,
     6,     1,     0,     2,     5,     0,     7,     0,    52,    50,
    23,    49,     0,    48,    51,     0,     8,    39,    13,    16,
    17,    21,     0,     0,     0,     0,     0,     0,     0,     0,
     0,    10,     0,     0,     0,    23,     0,    22,    20,    26,
     3,    25,    39,    11,    38,    12,    14,    15,    18,    19,
    30,     0,    41,     9,     0,     0,    39,    28,    29,    24,
     0,    54,     0,    32,     0,    34,    27,    23,     0,    40,
    43,     0,     0,    66,    37,    36,    31,    35,    33,     0,
     0,     0,     0,     0,     0,     4,     0,    46,    44,    42,
    45,    56,    58,     0,    47,     0,     0,    53,    68,    65,
    55,    23,    63,     0,    57,    60,     0,     0,     0,     0,
     0,     0,    67,     0,    62,    59,    61,    64,     0,     0,
     0
};

static const short yydefgoto[] = {   119,
     2,     6,    53,     4,    16,    17,    18,    19,    20,    21,
    41,    42,    51,    57,    58,    59,    64,    32,    62,    70,
    71,    22,    74,    93,    98,   105,   106,   107,    86,   100
};

static const short yypact[] = {   -22,
   -17,-32768,     7,-32768,-32768,     0,-32768,     5,-32768,-32768,
    15,-32768,    21,-32768,-32768,    34,    36,    -2,     6,-32768,
-32768,-32768,    49,    46,    47,     1,    50,    21,    21,    52,
    21,-32768,    21,    21,    53,    51,    65,-32768,-32768,-32768,
    70,-32768,    -2,     6,-32768,     6,-32768,-32768,-32768,-32768,
    -7,    50,    40,-32768,    78,    79,    95,-32768,-32768,-32768,
    48,    85,    91,-32768,    94,-32768,-32768,    22,    96,    98,
-32768,   103,    99,    80,-32768,-32768,-32768,-32768,-32768,    46,
    63,    48,    46,    46,   107,-32768,    88,-32768,-32768,-32768,
-32768,-32768,    -1,    46,-32768,    46,    75,-32768,-32768,   109,
-32768,    23,-32768,   113,   119,-32768,   116,    46,    46,   106,
    75,    77,-32768,   100,-32768,-32768,-32768,-32768,   126,   128,
-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,-32768,-32768,    -4,    19,    30,   -24,
-32768,    81,-32768,-32768,-32768,-32768,    73,   -32,-32768,-32768,
    54,   -59,-32768,-32768,-32768,-32768,    20,    24,-32768,-32768
};


#define	YYLAST		136


static const short yytable[] = {    37,
    29,    72,    30,    29,    55,     7,     1,    96,    26,     8,
    54,    33,     9,    10,     3,    97,    34,    56,    11,    12,
    13,    89,    72,    43,    67,    23,     5,    39,    31,    14,
     8,    31,    15,     9,    10,    24,    69,   104,    25,    11,
    12,    13,    80,   109,    28,    25,    25,    44,    27,    46,
    14,   104,   117,    15,    35,    87,    88,    69,    91,    92,
     9,    10,    47,    48,    36,    38,    68,    12,    40,    99,
    45,   101,   103,    61,    25,     9,    10,    14,    52,    49,
    15,    36,    12,   113,   114,   103,   103,     9,    10,     9,
    10,    50,    14,   102,    12,    15,    12,    63,    65,    30,
    73,    82,    85,    81,    14,    84,    14,    15,    75,    15,
    83,    75,    76,    94,    95,    76,    77,   108,    78,    79,
   110,    78,   111,   112,   102,   120,   118,   121,    66,     0,
   116,     0,    60,   115,     0,    90
};

static const short yycheck[] = {    24,
     3,    61,     5,     3,    12,     6,    29,     9,    13,    10,
    43,     6,    13,    14,    32,    17,    11,    25,    19,    20,
    21,    81,    82,    28,    57,    21,    20,    27,    31,    30,
    10,    31,    33,    13,    14,    21,    61,    97,    24,    19,
    20,    21,    21,    21,     9,    24,    24,    29,    15,    31,
    30,   111,   112,    33,     6,    80,    81,    82,    83,    84,
    13,    14,    33,    34,    19,    19,    19,    20,    19,    94,
    19,    96,    97,    34,    24,    13,    14,    30,     9,    27,
    33,    19,    20,   108,   109,   110,   111,    13,    14,    13,
    14,    27,    30,    19,    20,    33,    20,    20,    20,     5,
    16,     4,    23,     8,    30,     7,    30,    33,    18,    33,
     8,    18,    22,     7,    27,    22,    26,     9,    28,    26,
     8,    28,     4,     8,    19,     0,    27,     0,    56,    -1,
   111,    -1,    52,   110,    -1,    82
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/local/share/bison.simple"
/* This file comes from bison-1.28.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

#ifndef YYSTACK_USE_ALLOCA
#ifdef alloca
#define YYSTACK_USE_ALLOCA
#else /* alloca not defined */
#ifdef __GNUC__
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#define YYSTACK_USE_ALLOCA
#include <alloca.h>
#else /* not sparc */
/* We think this test detects Watcom and Microsoft C.  */
/* This used to test MSDOS, but that is a bad idea
   since that symbol is in the user namespace.  */
#if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#if 0 /* No need for malloc.h, which pollutes the namespace;
	 instead, just don't use alloca.  */
#include <malloc.h>
#endif
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
/* I don't know what this was needed for, but it pollutes the namespace.
   So I turned it off.   rms, 2 May 1997.  */
/* #include <malloc.h>  */
 #pragma alloca
#define YYSTACK_USE_ALLOCA
#else /* not MSDOS, or __TURBOC__, or _AIX */
#if 0
#ifdef __hpux /* haible@ilog.fr says this works for HPUX 9.05 and up,
		 and on HPUX 10.  Eventually we can turn this on.  */
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#endif /* __hpux */
#endif
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc */
#endif /* not GNU C */
#endif /* alloca not defined */
#endif /* YYSTACK_USE_ALLOCA not defined */

#ifdef YYSTACK_USE_ALLOCA
#define YYSTACK_ALLOC alloca
#else
#define YYSTACK_ALLOC malloc
#endif

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Define __yy_memcpy.  Note that the size argument
   should be passed with type unsigned int, because that is what the non-GCC
   definitions require.  With GCC, __builtin_memcpy takes an arg
   of type size_t, but it can handle unsigned int.  */

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     unsigned int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, unsigned int count)
{
  register char *t = to;
  register char *f = from;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 217 "/usr/local/share/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
#ifdef YYPARSE_PARAM
int yyparse (void *);
#else
int yyparse (void);
#endif
#endif

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;
  int yyfree_stacks = 0;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  if (yyfree_stacks)
	    {
	      free (yyss);
	      free (yyvs);
#ifdef YYLSP_NEEDED
	      free (yyls);
#endif
	    }
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
#ifndef YYSTACK_USE_ALLOCA
      yyfree_stacks = 1;
#endif
      yyss = (short *) YYSTACK_ALLOC (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1,
		   size * (unsigned int) sizeof (*yyssp));
      yyvs = (YYSTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1,
		   size * (unsigned int) sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1,
		   size * (unsigned int) sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 2:
#line 82 "sql.y"
{ source_parsed = 0; ;
    break;}
case 3:
#line 85 "sql.y"
{ sql_resolve_aggre(); source_parsed = 1; ;
    break;}
case 5:
#line 92 "sql.y"
{
			query.topN = yyvsp[0].int_value;
		;
    break;}
case 7:
#line 99 "sql.y"
{
			query.sel_all = 1;
		;
    break;}
case 9:
#line 106 "sql.y"
{
			sql_append_map(yyvsp[-1].expr, yyvsp[0].text);
		;
    break;}
case 10:
#line 110 "sql.y"
{
			sql_append_map(yyvsp[-1].expr, yyvsp[0].text);
		;
    break;}
case 11:
#line 116 "sql.y"
{
			struct sql_expr *expr;
			expr = type_alloc(struct sql_expr);
			expr->flag = EXPR_PRE_IN;
			expr->nfunc = strdup("add");
			expr->lc = yyvsp[-2].expr;
			expr->rc = yyvsp[0].expr;
			yyval.expr = expr;
			
		;
    break;}
case 12:
#line 127 "sql.y"
{
			struct sql_expr *expr;
			expr = type_alloc(struct sql_expr);
			expr->flag = EXPR_PRE_IN;
			expr->nfunc = strdup("sub");
			expr->lc = yyvsp[-2].expr;
			expr->rc = yyvsp[0].expr;
			yyval.expr = expr;
		;
    break;}
case 13:
#line 137 "sql.y"
{
			yyval.expr = yyvsp[0].expr;
		;
    break;}
case 14:
#line 143 "sql.y"
{
			struct sql_expr *expr;
			expr = type_alloc(struct sql_expr);
			expr->flag = EXPR_PRE_IN;
			expr->nfunc = strdup("mul");
			expr->lc = yyvsp[-2].expr;
			expr->rc = yyvsp[0].expr;
			yyval.expr = expr;
			
		;
    break;}
case 15:
#line 154 "sql.y"
{
			struct sql_expr *expr;
			expr = type_alloc(struct sql_expr);
			expr->flag = EXPR_PRE_IN;
			expr->nfunc = strdup("div");
			expr->lc = yyvsp[-2].expr;
			expr->rc = yyvsp[0].expr;
			yyval.expr = expr;
			
		;
    break;}
case 16:
#line 165 "sql.y"
{
			yyval.expr = yyvsp[0].expr;
		;
    break;}
case 17:
#line 171 "sql.y"
{
			struct sql_expr *expr;
			expr = type_alloc(struct sql_expr);
			expr->flag = EXPR_PRE_FIELD;
			expr->nsource = yyvsp[0].field.nsource;
			expr->nfield = yyvsp[0].field.nfield;
			expr->nfunc = NULL;
			expr->naggre = NULL;
			yyval.expr = expr;
			
		;
    break;}
case 18:
#line 183 "sql.y"
{
			struct sql_expr *expr;
			sql_append_aggre("count", NULL, NULL);
			expr = type_alloc(struct sql_expr);
			expr->flag = EXPR_PRE_FIELD;
			expr->nsource = NULL;
			expr->nfield = NULL;
			expr->naggre = strdup("count");
			yyval.expr = expr;
		;
    break;}
case 19:
#line 194 "sql.y"
{
			struct sql_expr *expr;
			int func = is_aggre(yyvsp[-3].text);
			expr = type_alloc(struct sql_expr);
			if (func)
			{
				sql_append_aggre(yyvsp[-3].text, yyvsp[-1].field.nsource, yyvsp[-1].field.nfield);
				expr->flag = EXPR_PRE_FIELD;
				expr->nsource = yyvsp[-1].field.nsource;
				expr->nfield = yyvsp[-1].field.nfield;
				expr->naggre = yyvsp[-3].text;
				expr->func = NULL;
			}
			else
			{
				expr->flag = EXPR_PRE_LEAF;
			      	expr->nsource = yyvsp[-1].field.nsource;
				expr->nfield = yyvsp[-1].field.nfield;
				expr->nfunc = yyvsp[-3].text;
				expr->naggre = NULL;
			}
			yyval.expr = expr;
		;
    break;}
case 20:
#line 218 "sql.y"
{
			yyval.expr = yyvsp[-1].expr;
		;
    break;}
case 21:
#line 222 "sql.y"
{
			struct sql_expr *expr;
			expr = type_alloc(struct sql_expr);
			expr->flag = EXPR_PRE_DATA;
			expr->type = yyvsp[0].constant.type;
			expr->data = yyvsp[0].constant.data;
			expr->func = NULL;
			yyval.expr = expr;
		;
    break;}
case 22:
#line 234 "sql.y"
{
			if (source_parsed)
			{
				int fld, ret;
				struct sql_source *src;
				ret = sql_lookup_field(yyvsp[-2].text, yyvsp[0].text, &src, &fld);
				if (ret != 0) sql_ok = 0;
				yyval.field.source = src;
				yyval.field.field = fld;
				free(yyvsp[-2].text); free(yyvsp[0].text);
			}
			else
			{
				yyval.field.nsource = yyvsp[-2].text;
				yyval.field.nfield = yyvsp[0].text;
			}
		;
    break;}
case 23:
#line 252 "sql.y"
{
			if (source_parsed)
			{
				int fld, ret;
				struct sql_source *src;
				ret = sql_lookup_field(NULL, yyvsp[0].text, &src, &fld);
				if (ret != 0) sql_ok = 0;
				yyval.field.source = src;
				yyval.field.field = fld;
				free(yyvsp[0].text);
			}
			else
			{
				yyval.field.nsource = NULL;
				yyval.field.nfield = yyvsp[0].text;
			}
		;
    break;}
case 26:
#line 276 "sql.y"
{
			query.last_source = type_alloc(struct sql_source);
			query.last_source->flag = SOURCE_STREAM;
			query.last_source->stream = stream_from_name(yyvsp[0].text);
			if (query.last_source->stream == NULL)
			{
				query.last_source->flag = SOURCE_TABLE;
				query.last_source->table = table_from_name(yyvsp[0].text);
			}
			if (query.last_source->stream == NULL) sql_ok = 0;
			query.last_source->type = 0;
			query.last_source->size = 0;
			query.last_source->count = 0;
			query.last_source->start = 1;
			free(yyvsp[0].text);
		;
    break;}
case 27:
#line 293 "sql.y"
{
			query.last_source->alias = yyvsp[0].text;
			llist_init(&(query.last_source->filter));
			llist_append(&query.source, query.last_source);
			query.last_source = NULL;
		;
    break;}
case 28:
#line 302 "sql.y"
{
			query.last_source->type |= WINDOW_TUMBLE;
		;
    break;}
case 29:
#line 306 "sql.y"
{
			query.last_source->type |= WINDOW_SLIDE;
		;
    break;}
case 31:
#line 313 "sql.y"
{
			query.last_source->type |= WINDOW_ROW;
			query.last_source->size = yyvsp[-1].int_value;
		;
    break;}
case 32:
#line 318 "sql.y"
{
			query.last_source->type |= WINDOW_TIME;
		;
    break;}
case 33:
#line 324 "sql.y"
{
			query.last_source->type |= WINDOW_ROW;
			query.last_source->size = yyvsp[-1].int_value;
		;
    break;}
case 34:
#line 329 "sql.y"
{
			query.last_source->type |= WINDOW_TIME;
		;
    break;}
case 35:
#line 335 "sql.y"
{
			query.last_source->size = yyvsp[-1].int_value;
		;
    break;}
case 36:
#line 339 "sql.y"
{
			query.last_source->size = yyvsp[-1].int_value * 60;
		;
    break;}
case 37:
#line 343 "sql.y"
{
			query.last_source->size = yyvsp[-1].int_value * 3600;
		;
    break;}
case 38:
#line 350 "sql.y"
{
			yyval.text = yyvsp[0].text;
		;
    break;}
case 39:
#line 354 "sql.y"
{
			yyval.text = NULL;
		;
    break;}
case 44:
#line 368 "sql.y"
{
			func_t *f;
			type_t *ft = sql_field_type(yyvsp[-2].field.source, yyvsp[-2].field.field);
/* check for memory leak */
			f = func_load(cmp2text(yyvsp[-1].int_value), ft, yyvsp[0].constant.type);
			if (f == NULL) sql_ok = 0;
			sql_append_src_filter(f, yyvsp[-2].field.source, yyvsp[-2].field.field, yyvsp[0].constant.data, yyvsp[0].constant.type);
		;
    break;}
case 45:
#line 377 "sql.y"
{
			func_t *f;
			type_t *ft = sql_field_type(yyvsp[0].field.source, yyvsp[0].field.field);
/* check for memory leak */
			yyvsp[-1].int_value = cmp_inv(yyvsp[-1].int_value);
			f = func_load(cmp2text(yyvsp[-1].int_value), yyvsp[-2].constant.type, ft);
			if (f == NULL) sql_ok = 0;
			sql_append_src_filter(f, yyvsp[0].field.source, yyvsp[0].field.field, yyvsp[-2].constant.data, yyvsp[-2].constant.type);
		;
    break;}
case 46:
#line 387 "sql.y"
{
			type_t *ft1 = sql_field_type(yyvsp[-2].field.source, yyvsp[-2].field.field);
			type_t *ft2 = sql_field_type(yyvsp[0].field.source, yyvsp[0].field.field);
			func_t *f;
			f = func_load(cmp2text(yyvsp[-1].int_value), ft1, ft2);
			if (f == NULL) sql_ok = 0;
			sql_append_filter(f, yyvsp[-2].field.source, yyvsp[-2].field.field, yyvsp[0].field.source, yyvsp[0].field.field);
		;
    break;}
case 47:
#line 396 "sql.y"
{
			free(yyvsp[-3].text);
			sql_ok = 0;
		;
    break;}
case 48:
#line 403 "sql.y"
{
			char **tmp;
			yyval.constant.type = TYPE_STRING;
			tmp = type_alloc(char *);
			*tmp = yyvsp[0].text;
			yyval.constant.data = tmp;
		;
    break;}
case 49:
#line 411 "sql.y"
{
			yyval.constant.type = TYPE_INT;
			yyval.constant.data = type_alloc(int);
		       	*(int *)yyval.constant.data	= yyvsp[0].int_value;
		;
    break;}
case 50:
#line 417 "sql.y"
{
			yyval.constant.type = TYPE_FLOAT;
			yyval.constant.data = type_alloc(float);
			*(float *)yyval.constant.data = yyvsp[0].float_value;
		;
    break;}
case 51:
#line 423 "sql.y"
{
			yyval.constant.type = TYPE_BOOL;
			yyval.constant.data = type_alloc(int);
		       	*(int *)yyval.constant.data	= 1;
		;
    break;}
case 52:
#line 429 "sql.y"
{
			yyval.constant.type = TYPE_BOOL;
			yyval.constant.data = type_alloc(int);
		       	*(int *)yyval.constant.data	= 0;
		;
    break;}
case 55:
#line 441 "sql.y"
{
			sql_append_group(yyvsp[0].field.source, yyvsp[0].field.field);
		;
    break;}
case 56:
#line 445 "sql.y"
{
			sql_append_group(yyvsp[0].field.source, yyvsp[0].field.field);
		;
    break;}
case 61:
#line 459 "sql.y"
{
			sql_append_group_filter_pre(yyvsp[-1].int_value, yyvsp[-2].field.source, yyvsp[-2].field.field, yyvsp[-2].field.aggre, yyvsp[0].constant.data, yyvsp[0].constant.type); 
		;
    break;}
case 62:
#line 463 "sql.y"
{
			sql_append_group_filter_pre(cmp_inv(yyvsp[-1].int_value), yyvsp[0].field.source, yyvsp[0].field.field, yyvsp[0].field.aggre, yyvsp[-2].constant.data, yyvsp[-2].constant.type); 

		;
    break;}
case 63:
#line 470 "sql.y"
{
			yyval.field.aggre = NULL;
			yyval.field.source = yyvsp[0].field.source;
			yyval.field.field = yyvsp[0].field.field;
		;
    break;}
case 64:
#line 476 "sql.y"
{
			yyval.field.aggre = NULL;
			yyval.field.source = yyvsp[-1].field.source;
			yyval.field.field = yyvsp[-1].field.field;
			yyval.field.aggre = aggre_load(yyvsp[-3].text, yyvsp[-1].field.source->stream->schema->field[yyvsp[-1].field.field].type);
			free(yyvsp[-3].text);
			if (yyval.field.aggre == NULL) sql_ok = 0;
			else sql_append_aggre_resolved(yyval.field.aggre, yyvsp[-1].field.source, yyvsp[-1].field.field);
		;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 543 "/usr/local/share/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;

 yyacceptlab:
  /* YYACCEPT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 0;

 yyabortlab:
  /* YYABORT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 1;
}
#line 495 "sql.y"


void sqlerror (char *msg)
{
		sql_ok = 0;		
		puts(msg);
}

