/* A Bison parser, made by GNU Bison 1.875.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software Foundation, Inc.

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

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     K_AND = 258,
     K_ARRAY = 259,
     K_BEGIN = 260,
     K_CASE = 261,
     K_CDECL = 262,
     K_CONST = 263,
     K_DIV = 264,
     K_DO = 265,
     K_DOWNTO = 266,
     K_ELSE = 267,
     K_END = 268,
     K_EXTERNEL = 269,
     K_FALSE = 270,
     K_FILE = 271,
     K_FOR = 272,
     K_FUNCTION = 273,
     K_GOTO = 274,
     K_IF = 275,
     K_IN = 276,
     K_NEG = 277,
     K_NOT = 278,
     K_OF = 279,
     K_OR = 280,
     K_LABEL = 281,
     K_MOD = 282,
     K_NIL = 283,
     K_PASCAL = 284,
     K_PACKED = 285,
     K_POS = 286,
     K_PROCEDURE = 287,
     K_PROGRAM = 288,
     K_RECORD = 289,
     K_READ = 290,
     K_READLN = 291,
     K_REPEAT = 292,
     K_SET = 293,
     K_THEN = 294,
     K_TO = 295,
     K_TRUE = 296,
     K_TYPE = 297,
     K_UNTIL = 298,
     K_VAR = 299,
     K_WHILE = 300,
     K_WITH = 301,
     K_WRITE = 302,
     K_WRITELN = 303,
     K_XOR = 304,
     AT = 305,
     CARET = 306,
     COLON = 307,
     COMMA = 308,
     DIVIDE = 309,
     DOTDOT = 310,
     EQUALS = 311,
     GE = 312,
     GT = 313,
     IS = 314,
     LBRACKET = 315,
     LE = 316,
     LPAREN = 317,
     LT = 318,
     MINUS = 319,
     NE = 320,
     PERIOD = 321,
     PLUS = 322,
     RBRACKET = 323,
     RPAREN = 324,
     SCOLON = 325,
     TIMES = 326,
     IDENTIFIER = 327,
     INTEGER = 328,
     REAL = 329,
     STRING = 330,
     POS = 331,
     NEG = 332,
     LABEL = 333
   };
#endif
#define K_AND 258
#define K_ARRAY 259
#define K_BEGIN 260
#define K_CASE 261
#define K_CDECL 262
#define K_CONST 263
#define K_DIV 264
#define K_DO 265
#define K_DOWNTO 266
#define K_ELSE 267
#define K_END 268
#define K_EXTERNEL 269
#define K_FALSE 270
#define K_FILE 271
#define K_FOR 272
#define K_FUNCTION 273
#define K_GOTO 274
#define K_IF 275
#define K_IN 276
#define K_NEG 277
#define K_NOT 278
#define K_OF 279
#define K_OR 280
#define K_LABEL 281
#define K_MOD 282
#define K_NIL 283
#define K_PASCAL 284
#define K_PACKED 285
#define K_POS 286
#define K_PROCEDURE 287
#define K_PROGRAM 288
#define K_RECORD 289
#define K_READ 290
#define K_READLN 291
#define K_REPEAT 292
#define K_SET 293
#define K_THEN 294
#define K_TO 295
#define K_TRUE 296
#define K_TYPE 297
#define K_UNTIL 298
#define K_VAR 299
#define K_WHILE 300
#define K_WITH 301
#define K_WRITE 302
#define K_WRITELN 303
#define K_XOR 304
#define AT 305
#define CARET 306
#define COLON 307
#define COMMA 308
#define DIVIDE 309
#define DOTDOT 310
#define EQUALS 311
#define GE 312
#define GT 313
#define IS 314
#define LBRACKET 315
#define LE 316
#define LPAREN 317
#define LT 318
#define MINUS 319
#define NE 320
#define PERIOD 321
#define PLUS 322
#define RBRACKET 323
#define RPAREN 324
#define SCOLON 325
#define TIMES 326
#define IDENTIFIER 327
#define INTEGER 328
#define REAL 329
#define STRING 330
#define POS 331
#define NEG 332
#define LABEL 333




/* Copy the first part of user declarations.  */
#line 4 "pascal.y"

#include "pascal.h"


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 9 "pascal.y"
typedef union YYSTYPE {
	char *text;
	int integer;
	double real;
	stack_t *stack;
	queue_t *queue;
	entry_t *entry;
	expression_t *expr;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 245 "pascal.tab.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 257 "pascal.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   470

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  79
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  78
/* YYNRULES -- Number of rules. */
#define YYNRULES  161
/* YYNRULES -- Number of states. */
#define YYNSTATES  314

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   333

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     4,     5,     6,    15,    16,    20,    23,
      24,    26,    28,    30,    32,    34,    36,    40,    44,    46,
      48,    50,    53,    56,    58,    63,    65,    68,    71,    73,
      78,    80,    82,    84,    86,    88,    91,    94,    98,   102,
     104,   106,   113,   117,   119,   120,   125,   128,   132,   134,
     138,   140,   144,   145,   153,   156,   158,   159,   160,   169,
     170,   174,   177,   179,   184,   185,   186,   192,   196,   199,
     202,   203,   208,   216,   223,   233,   237,   238,   241,   245,
     250,   252,   257,   261,   265,   267,   269,   273,   275,   277,
     279,   281,   283,   285,   287,   291,   295,   299,   301,   305,
     309,   313,   317,   321,   323,   325,   327,   331,   336,   339,
     342,   345,   349,   351,   353,   357,   359,   361,   363,   365,
     366,   371,   373,   377,   382,   384,   389,   394,   399,   404,
     406,   409,   410,   411,   419,   425,   426,   427,   434,   435,
     441,   442,   452,   453,   463,   468,   470,   471,   475,   476,
     477,   482,   483,   486,   487,   489,   491,   495,   499,   501,
     505,   509
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short yyrhs[] =
{
      80,     0,    -1,    -1,    -1,    -1,    33,    72,    81,    70,
      82,    84,    83,    66,    -1,    -1,    86,    85,   149,    -1,
      86,    87,    -1,    -1,    88,    -1,    91,    -1,    95,    -1,
     116,    -1,   120,    -1,     1,    -1,    26,    89,    70,    -1,
      89,    53,    90,    -1,    90,    -1,    73,    -1,    72,    -1,
       8,    92,    -1,    92,    93,    -1,    93,    -1,    72,    56,
      94,    70,    -1,   130,    -1,    42,    96,    -1,    96,    97,
      -1,    97,    -1,    72,    56,    98,    70,    -1,    99,    -1,
      72,    -1,   100,    -1,   101,    -1,   102,    -1,    30,   102,
      -1,    51,    98,    -1,    62,   156,    69,    -1,   130,    55,
     130,    -1,   103,    -1,   105,    -1,     4,    60,   104,    68,
      24,    98,    -1,   104,    53,    98,    -1,    98,    -1,    -1,
      34,   106,   107,    13,    -1,   108,   152,    -1,   108,    70,
     110,    -1,   110,    -1,   108,    70,   109,    -1,   109,    -1,
     156,    52,    98,    -1,    -1,     6,    72,    52,    98,    24,
     111,   112,    -1,   112,   113,    -1,   113,    -1,    -1,    -1,
     129,    52,    62,   114,   107,   115,    69,    70,    -1,    -1,
      44,   117,   118,    -1,   118,   119,    -1,   119,    -1,   156,
      52,    98,    70,    -1,    -1,    -1,   124,   121,    84,   122,
      70,    -1,   124,    14,    70,    -1,     7,    70,    -1,    29,
      70,    -1,    -1,    32,    72,    70,   123,    -1,    32,    72,
      62,   125,    69,    70,   123,    -1,    18,    72,    52,    98,
      70,   123,    -1,    18,    72,    62,   125,    69,    52,    98,
      70,   123,    -1,   125,    70,   127,    -1,    -1,   126,   127,
      -1,   156,    52,    98,    -1,    44,   156,    52,    98,    -1,
      72,    -1,   128,    60,   129,    68,    -1,   128,    66,    72,
      -1,   129,    53,   130,    -1,   130,    -1,   132,    -1,   132,
     131,   132,    -1,    56,    -1,    65,    -1,    58,    -1,    63,
      -1,    57,    -1,    61,    -1,   133,    -1,   132,    67,   133,
      -1,   132,    64,   133,    -1,   132,    25,   133,    -1,   134,
      -1,   133,    71,   134,    -1,   133,    54,   134,    -1,   133,
       9,   134,    -1,   133,    27,   134,    -1,   133,     3,   134,
      -1,   128,    -1,    73,    -1,    75,    -1,    62,   130,    69,
      -1,    72,    62,   129,    69,    -1,    76,   134,    -1,    77,
     134,    -1,    23,   134,    -1,    60,   135,    68,    -1,    41,
      -1,    15,    -1,   135,    53,   136,    -1,   136,    -1,   130,
      -1,   101,    -1,   139,    -1,    -1,    90,   138,    52,   139,
      -1,     1,    -1,   128,    59,   130,    -1,    35,    62,   129,
      69,    -1,    36,    -1,    36,    62,   129,    69,    -1,    47,
      62,   129,    69,    -1,    48,    62,   129,    69,    -1,    72,
      62,   129,    69,    -1,    72,    -1,    19,    90,    -1,    -1,
      -1,    20,   130,    39,   140,   137,   141,   147,    -1,     6,
     130,    24,   154,    13,    -1,    -1,    -1,    45,   142,   130,
     143,    10,   137,    -1,    -1,    37,   144,   151,    43,   130,
      -1,    -1,    17,   128,    59,   130,    40,   130,    10,   145,
     137,    -1,    -1,    17,   128,    59,   130,    11,   130,    10,
     146,   137,    -1,    46,   128,    10,   137,    -1,   149,    -1,
      -1,    12,   148,   137,    -1,    -1,    -1,     5,   150,   151,
      13,    -1,    -1,   153,   152,    -1,    -1,    70,    -1,   137,
      -1,   153,    70,   137,    -1,   154,    70,   155,    -1,   155,
      -1,   129,    52,   137,    -1,   156,    53,    72,    -1,    72,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   113,   113,   122,   130,   112,   141,   140,   150,   151,
     154,   155,   156,   157,   158,   159,   165,   168,   170,   174,
     176,   180,   183,   184,   187,   194,   214,   217,   218,   221,
     239,   252,   263,   265,   267,   269,   271,   283,   289,   296,
     298,   302,   318,   326,   337,   336,   348,   349,   350,   353,
     354,   357,   375,   374,   392,   393,   397,   408,   396,   416,
     415,   422,   423,   426,   445,   481,   444,   494,   504,   508,
     513,   518,   523,   531,   536,   544,   546,   546,   553,   575,
     599,   609,   622,   637,   642,   652,   656,   671,   672,   673,
     674,   675,   676,   679,   683,   696,   709,   724,   728,   741,
     754,   767,   780,   795,   799,   803,   815,   819,   827,   831,
     835,   839,   844,   848,   854,   855,   857,   858,   861,   866,
     865,   870,   876,   880,   884,   888,   892,   896,   900,   906,
     912,   917,   939,   916,   943,   948,   954,   947,   970,   969,
     986,   985,  1008,  1007,  1029,  1033,  1037,  1036,  1056,  1070,
    1069,  1079,  1080,  1084,  1085,  1088,  1089,  1092,  1093,  1096,
    1102,  1107
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "K_AND", "K_ARRAY", "K_BEGIN", "K_CASE", 
  "K_CDECL", "K_CONST", "K_DIV", "K_DO", "K_DOWNTO", "K_ELSE", "K_END", 
  "K_EXTERNEL", "K_FALSE", "K_FILE", "K_FOR", "K_FUNCTION", "K_GOTO", 
  "K_IF", "K_IN", "K_NEG", "K_NOT", "K_OF", "K_OR", "K_LABEL", "K_MOD", 
  "K_NIL", "K_PASCAL", "K_PACKED", "K_POS", "K_PROCEDURE", "K_PROGRAM", 
  "K_RECORD", "K_READ", "K_READLN", "K_REPEAT", "K_SET", "K_THEN", "K_TO", 
  "K_TRUE", "K_TYPE", "K_UNTIL", "K_VAR", "K_WHILE", "K_WITH", "K_WRITE", 
  "K_WRITELN", "K_XOR", "AT", "CARET", "COLON", "COMMA", "DIVIDE", 
  "DOTDOT", "EQUALS", "GE", "GT", "IS", "LBRACKET", "LE", "LPAREN", "LT", 
  "MINUS", "NE", "PERIOD", "PLUS", "RBRACKET", "RPAREN", "SCOLON", 
  "TIMES", "IDENTIFIER", "INTEGER", "REAL", "STRING", "POS", "NEG", 
  "LABEL", "$accept", "program", "@1", "@2", "@3", "block", "@4", 
  "list_declaration", "declaration", "label_declaration_part", 
  "list_label", "label", "constant_definition_part", 
  "list_constant_definition", "constant_definition", "constant", 
  "type_definition_part", "list_type_definition", "type_definition", 
  "type", "type_def", "scalar_type", "subrange", "structured_type", 
  "array_type", "list_type", "record_type", "@5", "field_list", 
  "list_record_section", "record_section", "variant_part", "@6", 
  "list_variant", "variant", "@7", "@8", "variable_declaration_part", 
  "@9", "list_variable_declaration", "variable_declaration", 
  "function_declaration", "@10", "@11", "function_property", 
  "function_heading", "list_parameter_group", "@12", "parameter_group", 
  "variable", "list_expression", "expression", "relop", "sexpr", "term", 
  "factor", "list_element", "element", "statement", "@13", 
  "unlabelled_statement", "@14", "@15", "@16", "@17", "@18", "@19", "@20", 
  "else_part", "@21", "compound_statement", "@22", "list_statement", 
  "scolon_or_none", "real_list_statement", "list_case_list_element", 
  "case_list_element", "list_identifier", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    79,    81,    82,    83,    80,    85,    84,    86,    86,
      87,    87,    87,    87,    87,    87,    88,    89,    89,    90,
      90,    91,    92,    92,    93,    94,    95,    96,    96,    97,
      98,    99,    99,    99,    99,    99,    99,   100,   101,   102,
     102,   103,   104,   104,   106,   105,   107,   107,   107,   108,
     108,   109,   111,   110,   112,   112,   114,   115,   113,   117,
     116,   118,   118,   119,   121,   122,   120,   120,   123,   123,
     123,   124,   124,   124,   124,   125,   126,   125,   127,   127,
     128,   128,   128,   129,   129,   130,   130,   131,   131,   131,
     131,   131,   131,   132,   132,   132,   132,   133,   133,   133,
     133,   133,   133,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   135,   135,   136,   136,   137,   138,
     137,   137,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   140,   141,   139,   139,   142,   143,   139,   144,   139,
     145,   139,   146,   139,   139,   139,   148,   147,   147,   150,
     149,   151,   151,   152,   152,   153,   153,   154,   154,   155,
     156,   156
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     0,     0,     8,     0,     3,     2,     0,
       1,     1,     1,     1,     1,     1,     3,     3,     1,     1,
       1,     2,     2,     1,     4,     1,     2,     2,     1,     4,
       1,     1,     1,     1,     1,     2,     2,     3,     3,     1,
       1,     6,     3,     1,     0,     4,     2,     3,     1,     3,
       1,     3,     0,     7,     2,     1,     0,     0,     8,     0,
       3,     2,     1,     4,     0,     0,     5,     3,     2,     2,
       0,     4,     7,     6,     9,     3,     0,     2,     3,     4,
       1,     4,     3,     3,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     1,     3,     3,
       3,     3,     3,     1,     1,     1,     3,     4,     2,     2,
       2,     3,     1,     1,     3,     1,     1,     1,     1,     0,
       4,     1,     3,     4,     1,     4,     4,     4,     4,     1,
       2,     0,     0,     7,     5,     0,     0,     6,     0,     5,
       0,     9,     0,     9,     4,     1,     0,     3,     0,     0,
       4,     0,     2,     0,     1,     1,     3,     3,     1,     3,
       3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     2,     1,     0,     3,     9,     4,     0,
       0,    15,     0,     0,     0,     0,     0,    59,     0,     8,
      10,    11,    12,    13,    14,    64,     5,     0,    21,    23,
       0,    20,    19,     0,    18,     0,     0,    26,    28,     0,
     149,     7,     0,     9,     0,    22,     0,    76,     0,    16,
      76,    70,     0,    27,   161,    60,    62,     0,     0,    67,
      65,   113,     0,   112,     0,     0,    80,   104,   105,     0,
       0,     0,   103,    25,    85,    93,    97,     0,     0,    44,
       0,     0,    80,     0,    30,    32,    33,    34,    39,    40,
       0,     0,     0,    17,     0,     0,     0,    71,     0,    61,
       0,     0,   121,     0,     0,     0,     0,     0,   124,   138,
     135,     0,     0,     0,   129,   119,     0,   155,   118,   145,
       0,   153,     0,   110,   117,   116,     0,   115,     0,     0,
     108,   109,    24,     0,     0,     0,    87,    91,    89,    92,
      90,     0,    88,     0,     0,     0,     0,     0,     0,     0,
       0,    35,     0,    36,    80,     0,    70,     0,     0,     0,
       0,    77,     0,     0,    68,    69,    29,     0,   160,     0,
      80,     0,   130,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   150,     0,   152,    66,     0,   111,
     106,     0,    84,     0,    82,    96,    95,    94,    86,   102,
     100,   101,    99,    98,    43,     0,     0,     0,   153,    50,
      48,     0,    37,    73,    38,     0,    75,     0,     0,    70,
      63,     0,     0,   131,     0,     0,     0,   136,     0,     0,
       0,     0,     0,   122,   156,   114,     0,   107,    81,     0,
       0,     0,    45,   154,    46,     0,     0,     0,    78,    72,
       0,     0,   158,     0,     0,   123,   125,     0,     0,   144,
     126,   127,   128,   129,   120,    83,    42,     0,     0,    49,
      47,    51,    70,    79,     0,   134,     0,     0,     0,   132,
     139,     0,    41,     0,    74,   159,   157,     0,     0,   148,
     137,    52,   142,   140,   146,   133,     0,     0,     0,     0,
      53,    55,     0,   143,   141,   147,    54,     0,    56,     0,
      57,     0,     0,    58
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     2,     5,     7,    10,     8,    18,     9,    19,    20,
      33,   115,    21,    28,    29,    71,    22,    37,    38,    83,
      84,    85,    86,    87,    88,   205,    89,   152,   207,   208,
     209,   210,   296,   300,   301,   309,   311,    23,    39,    55,
      56,    24,    43,   122,    97,    25,    91,    92,   161,    72,
     250,    90,   144,    74,    75,    76,   126,   127,   117,   182,
     118,   254,   289,   177,   258,   176,   298,   297,   295,   299,
     119,    58,   120,   186,   121,   251,   252,   211
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -176
static const short yypact[] =
{
      17,    19,    55,  -176,  -176,    33,  -176,  -176,  -176,   426,
      15,  -176,    48,    66,   -40,   100,   102,  -176,   105,  -176,
    -176,  -176,  -176,  -176,  -176,    63,  -176,    71,    48,  -176,
     -38,  -176,  -176,   -26,  -176,   -27,   103,   102,  -176,   104,
    -176,  -176,   111,  -176,    11,  -176,   150,  -176,   -40,  -176,
    -176,     1,   150,  -176,  -176,   104,  -176,    94,   278,  -176,
    -176,  -176,    11,  -176,    11,    11,   121,  -176,  -176,    11,
      11,   123,   119,  -176,    51,     9,  -176,   129,     7,  -176,
     150,   366,    87,   125,  -176,  -176,  -176,  -176,  -176,  -176,
     109,   134,   -16,  -176,   138,   135,   139,  -176,   141,  -176,
     150,   144,  -176,    11,   158,   -40,    11,   177,   184,  -176,
    -176,   158,   186,   189,   101,  -176,    92,  -176,  -176,  -176,
     240,   187,   188,  -176,  -176,   109,     4,  -176,   190,    11,
    -176,  -176,  -176,    11,   182,    11,  -176,  -176,  -176,  -176,
    -176,    11,  -176,    11,    11,    11,    11,    11,    11,    11,
     150,  -176,    -2,  -176,    16,   -30,     1,    11,   203,   -16,
     104,  -176,   162,   191,  -176,  -176,  -176,   193,  -176,   236,
    -176,   128,  -176,   223,    11,    11,   299,    11,    38,    11,
      11,    11,   212,    11,  -176,   230,  -176,  -176,    11,  -176,
    -176,   -24,  -176,    37,  -176,     9,     9,     9,   -18,  -176,
    -176,  -176,  -176,  -176,  -176,    49,   196,   256,   200,  -176,
    -176,   168,  -176,  -176,  -176,   150,  -176,   176,   150,     1,
    -176,    11,    11,  -176,     5,    72,   228,  -176,   347,    76,
      79,    81,   368,  -176,  -176,  -176,    11,  -176,  -176,   150,
     248,   222,  -176,    -2,  -176,   150,   210,   150,  -176,  -176,
     185,    12,  -176,     2,   347,  -176,  -176,    11,   271,  -176,
    -176,  -176,  -176,   140,  -176,  -176,  -176,   150,   150,  -176,
    -176,  -176,     1,  -176,   347,  -176,    11,    11,    11,  -176,
    -176,   347,  -176,   258,  -176,  -176,  -176,   275,   276,   277,
    -176,  -176,  -176,  -176,  -176,  -176,    11,   347,   347,   347,
      11,  -176,   192,  -176,  -176,  -176,  -176,   225,  -176,    -2,
    -176,   219,   220,  -176
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -176,  -176,  -176,  -176,  -176,   249,  -176,  -176,  -176,  -176,
    -176,    -8,  -176,  -176,   265,  -176,  -176,  -176,   257,   -49,
    -176,  -176,   -62,   218,  -176,  -176,  -176,  -176,   -10,  -176,
      58,    64,  -176,  -176,     6,  -176,  -176,  -176,  -176,  -176,
     253,  -176,  -176,  -176,  -151,  -176,   259,  -176,   151,   -57,
    -114,   -44,  -176,   167,    27,   -53,  -176,   124,  -175,  -176,
      85,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
     302,  -176,   145,   114,  -176,  -176,    52,   -17
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -162
static const short yytable[] =
{
      73,   116,   124,    98,   206,   213,    34,   135,    95,   123,
     234,    77,   145,   277,    46,   191,   130,   131,   146,   193,
     125,   128,    57,   101,    47,   275,    61,    48,   160,   236,
      96,   153,    31,    32,    62,    50,   147,   128,    57,   212,
      93,    79,   278,    51,    49,   237,   141,   171,   228,   143,
       1,   167,    63,   259,   178,     4,    54,   188,   236,   169,
     224,   225,   173,   148,   155,   229,   230,   231,   249,  -161,
      54,    64,   189,    65,   255,   162,   135,    42,   129,   279,
     149,    26,   276,    66,    67,   192,    68,    69,    70,   192,
     236,     3,   199,   200,   201,   202,   203,   172,   133,   285,
     -31,   204,   239,     6,   134,   238,   290,   136,   137,   138,
      40,   -31,   139,   214,   140,   141,   142,   240,   143,   116,
      27,   284,   303,   304,   305,   236,   124,    44,   116,   236,
     192,   192,   236,   227,   236,   192,   192,   192,    30,   233,
     -31,   256,   162,   217,   125,   260,   100,   101,   261,   129,
     262,   183,   133,   -20,    77,   -31,   -31,   -31,   134,    52,
     -80,   -80,   195,   181,   157,    61,   246,   -80,   196,   248,
     197,   116,    35,    62,    36,   116,    54,   192,   253,   133,
      78,    59,   302,   129,    79,   134,   302,   222,   133,   150,
     266,    63,   265,   132,   134,   156,   271,   116,   273,   -80,
     -80,    80,   181,   158,   159,   164,   -80,   163,   159,   165,
      64,   166,    81,   280,   218,   101,   168,   116,   282,   283,
     245,   101,    82,    67,   116,    68,    69,    70,   247,   101,
     170,   102,   192,   287,   288,    40,   103,   274,   236,   174,
     116,   116,   116,  -154,   307,   236,   175,   104,   179,   105,
     106,   180,   192,   184,   194,   215,   192,   185,   187,   190,
     221,   219,   223,   220,   232,   107,   108,   109,   241,   242,
     243,   257,   267,  -154,   268,   110,   111,   112,   113,   102,
     272,   281,   291,    40,   103,   292,   293,   308,   312,   294,
     313,  -151,    60,    45,    53,   104,   151,   105,   106,   310,
     102,   269,   114,    32,    40,   103,   306,   270,    99,    94,
     216,   198,   235,   107,   108,   109,   104,   264,   105,   106,
      41,   226,   244,   110,   111,   112,   113,     0,   286,     0,
       0,     0,     0,     0,   107,   108,   109,     0,     0,     0,
       0,     0,  -151,     0,   110,   111,   112,   113,   102,     0,
     114,    32,    40,   103,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   104,     0,   105,   106,     0,     0,
       0,   114,    32,    40,   103,     0,     0,     0,     0,     0,
       0,    61,   107,   108,   109,   104,     0,   105,   106,    62,
       0,     0,   110,   111,   112,   113,     0,     0,     0,     0,
       0,     0,     0,   107,   108,   109,     0,    63,     0,     0,
       0,     0,     0,   110,   111,   112,   113,     0,     0,   114,
      32,     0,     0,     0,     0,     0,    64,    11,    65,     0,
       0,    -6,     0,     0,    12,     0,     0,     0,   154,    67,
     263,    68,    69,    70,    13,     0,     0,     0,     0,     0,
       0,     0,    14,     0,     0,     0,     0,     0,    15,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    16,     0,
      17
};

static const short yycheck[] =
{
      44,    58,    64,    52,     6,   156,    14,    25,     7,    62,
     185,     4,     3,    11,    52,   129,    69,    70,     9,   133,
      64,    65,    39,    53,    62,    13,    15,    53,    44,    53,
      29,    80,    72,    73,    23,    62,    27,    81,    55,    69,
      48,    34,    40,    70,    70,    69,    64,   104,    10,    67,
      33,   100,    41,   228,   111,     0,    72,    53,    53,   103,
     174,   175,   106,    54,    81,   179,   180,   181,   219,    53,
      72,    60,    68,    62,    69,    92,    25,    14,    62,   254,
      71,    66,    70,    72,    73,   129,    75,    76,    77,   133,
      53,    72,   145,   146,   147,   148,   149,   105,    60,   274,
      13,   150,    53,    70,    66,    68,   281,    56,    57,    58,
       5,    24,    61,   157,    63,    64,    65,    68,    67,   176,
      72,   272,   297,   298,   299,    53,   188,    56,   185,    53,
     174,   175,    53,   177,    53,   179,   180,   181,    72,   183,
      53,    69,   159,   160,   188,    69,    52,    53,    69,    62,
      69,    59,    60,    52,     4,    68,    69,    70,    66,    56,
      59,    60,   135,    62,    55,    15,   215,    66,   141,   218,
     143,   228,    72,    23,    72,   232,    72,   221,   222,    60,
      30,    70,   296,    62,    34,    66,   300,    59,    60,    60,
     239,    41,   236,    70,    66,    70,   245,   254,   247,    59,
      60,    51,    62,    69,    70,    70,    66,    69,    70,    70,
      60,    70,    62,   257,    52,    53,    72,   274,   267,   268,
      52,    53,    72,    73,   281,    75,    76,    77,    52,    53,
      72,     1,   276,   277,   278,     5,     6,    52,    53,    62,
     297,   298,   299,    13,    52,    53,    62,    17,    62,    19,
      20,    62,   296,    13,    72,    52,   300,    70,    70,    69,
      24,    70,    39,    70,    52,    35,    36,    37,    72,    13,
      70,    43,    24,    43,    52,    45,    46,    47,    48,     1,
      70,    10,    24,     5,     6,    10,    10,    62,    69,    12,
      70,    13,    43,    28,    37,    17,    78,    19,    20,   309,
       1,   243,    72,    73,     5,     6,   300,   243,    55,    50,
     159,   144,   188,    35,    36,    37,    17,   232,    19,    20,
      18,   176,   208,    45,    46,    47,    48,    -1,   276,    -1,
      -1,    -1,    -1,    -1,    35,    36,    37,    -1,    -1,    -1,
      -1,    -1,    43,    -1,    45,    46,    47,    48,     1,    -1,
      72,    73,     5,     6,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    -1,    19,    20,    -1,    -1,
      -1,    72,    73,     5,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    15,    35,    36,    37,    17,    -1,    19,    20,    23,
      -1,    -1,    45,    46,    47,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    36,    37,    -1,    41,    -1,    -1,
      -1,    -1,    -1,    45,    46,    47,    48,    -1,    -1,    72,
      73,    -1,    -1,    -1,    -1,    -1,    60,     1,    62,    -1,
      -1,     5,    -1,    -1,     8,    -1,    -1,    -1,    72,    73,
      72,    75,    76,    77,    18,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    32,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    -1,
      44
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    33,    80,    72,     0,    81,    70,    82,    84,    86,
      83,     1,     8,    18,    26,    32,    42,    44,    85,    87,
      88,    91,    95,   116,   120,   124,    66,    72,    92,    93,
      72,    72,    73,    89,    90,    72,    72,    96,    97,   117,
       5,   149,    14,   121,    56,    93,    52,    62,    53,    70,
      62,    70,    56,    97,    72,   118,   119,   156,   150,    70,
      84,    15,    23,    41,    60,    62,    72,    73,    75,    76,
      77,    94,   128,   130,   132,   133,   134,     4,    30,    34,
      51,    62,    72,    98,    99,   100,   101,   102,   103,   105,
     130,   125,   126,    90,   125,     7,    29,   123,    98,   119,
      52,    53,     1,     6,    17,    19,    20,    35,    36,    37,
      45,    46,    47,    48,    72,    90,   128,   137,   139,   149,
     151,   153,   122,   134,   101,   130,   135,   136,   130,    62,
     134,   134,    70,    60,    66,    25,    56,    57,    58,    61,
      63,    64,    65,    67,   131,     3,     9,    27,    54,    71,
      60,   102,   106,    98,    72,   156,    70,    55,    69,    70,
      44,   127,   156,    69,    70,    70,    70,    98,    72,   130,
      72,   128,    90,   130,    62,    62,   144,   142,   128,    62,
      62,    62,   138,    59,    13,    70,   152,    70,    53,    68,
      69,   129,   130,   129,    72,   133,   133,   133,   132,   134,
     134,   134,   134,   134,    98,   104,     6,   107,   108,   109,
     110,   156,    69,   123,   130,    52,   127,   156,    52,    70,
      70,    24,    59,    39,   129,   129,   151,   130,    10,   129,
     129,   129,    52,   130,   137,   136,    53,    69,    68,    53,
      68,    72,    13,    70,   152,    52,    98,    52,    98,   123,
     129,   154,   155,   130,   140,    69,    69,    43,   143,   137,
      69,    69,    69,    72,   139,   130,    98,    24,    52,   109,
     110,    98,    70,    98,    52,    13,    70,    11,    40,   137,
     130,    10,    98,    98,   123,   137,   155,   130,   130,   141,
     137,    24,    10,    10,    12,   147,   111,   146,   145,   148,
     112,   113,   129,   137,   137,   137,   113,    52,    62,   114,
     107,   115,    69,    70
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylineno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylineno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 113 "pascal.y"
    {	
				SET_TITLE(yyvsp[0].text); 
				EMIT(OP_TITLE, SYMBOL_ARG(yyvsp[0].text),
					NULL_ARG, NULL_ARG);
				reset_global();
				reset_label();
				reset_proc();
			;}
    break;

  case 3:
#line 122 "pascal.y"
    {
				STACK_PUSH;
				stack_push(proc_stack, (int)yyvsp[-2].text);
				stack_push(proc_stack, 0);
				stack_push(record_stack, 0);
				stack_push(proc_stack, new_proc());
			;}
    break;

  case 4:
#line 130 "pascal.y"
    {
				EMIT(OP_ENDP, NULL_ARG, NULL_ARG, NULL_ARG);
				STACK_POP;
			;}
    break;

  case 5:
#line 135 "pascal.y"
    {
				EMIT(OP_END, NULL_ARG, NULL_ARG, NULL_ARG);
			;}
    break;

  case 6:
#line 141 "pascal.y"
    {
				EMIT(OP_PROC, SYMBOL_ARG((char *)stack_pop(proc_stack)), CONST_ARG(stack_pop(proc_stack)), CONST_ARG(stack_pop(proc_stack)));				
				reset_temp();
				emit_declaration(STACK_TOP);
				stack_pop(record_stack);
			;}
    break;

  case 15:
#line 160 "pascal.y"
    {
					yyok = 0;
			;}
    break;

  case 17:
#line 169 "pascal.y"
    { APPEND_LABEL(yyvsp[0].text); ;}
    break;

  case 18:
#line 171 "pascal.y"
    { APPEND_LABEL(yyvsp[0].text); ;}
    break;

  case 19:
#line 175 "pascal.y"
    { yyval.text = itoa(yyvsp[0].integer); ;}
    break;

  case 20:
#line 177 "pascal.y"
    { yyval.text = yyvsp[0].text; ;}
    break;

  case 24:
#line 188 "pascal.y"
    { 
				if (yyvsp[-1].expr != NULL) APPEND_CONST(yyvsp[-3].text, yyvsp[-1].expr);
				else free(yyvsp[-3].text);
			;}
    break;

  case 25:
#line 195 "pascal.y"
    {
				if (yyvsp[0].expr == NULL) yyval.expr = NULL;
				else
				if ((yyvsp[0].expr->flag != EXPR_CONST)
				&& (yyvsp[0].expr->flag != EXPR_GLOBAL
					|| yyvsp[0].expr->type != string_entry)) 
				{
					ERROR("Invalid constant definition.");
					expr_free(yyvsp[0].expr);
					yyval.expr = NULL;
				}
				else
				{
					yyval.expr = yyvsp[0].expr;
				}
			;}
    break;

  case 29:
#line 222 "pascal.y"
    {
				if (yyvsp[-1].entry == NULL) free(yyvsp[-3].text);
				else
				{
					if (yyvsp[-1].entry->name != NULL)
					{
						yyvsp[-1].entry = entry_copy(yyvsp[-1].entry);
						free(yyvsp[-1].entry->name);
						yyvsp[-1].entry->name = NULL;
						APPEND_TYPE(yyvsp[-1].entry);
					}
					yyvsp[-1].entry->name = yyvsp[-3].text;
					STACK_HASH_APPEND(yyvsp[-1].entry);
				}
			;}
    break;

  case 30:
#line 240 "pascal.y"
    {
				if (yyvsp[0].entry != NULL)
				{
					if (yyvsp[0].entry->name == NULL)
					{
						APPEND_TYPE(yyvsp[0].entry);
					}
				}
				yyval.entry = yyvsp[0].entry;
			;}
    break;

  case 31:
#line 253 "pascal.y"
    {
				entry_t *e = STACK_LOOKUP(yyvsp[0].text, NULL);
				if (e == NULL)
				{
					ERROR("type %s not found.\n", yyvsp[0].text);
					yyval.entry = NULL;
				}
				else yyval.entry = e;	
				free(yyvsp[0].text);
			;}
    break;

  case 32:
#line 264 "pascal.y"
    { yyval.entry = yyvsp[0].entry; ;}
    break;

  case 33:
#line 266 "pascal.y"
    { yyval.entry = yyvsp[0].entry; ;}
    break;

  case 34:
#line 268 "pascal.y"
    { yyval.entry = yyvsp[0].entry; ;}
    break;

  case 35:
#line 270 "pascal.y"
    { yyval.entry = yyvsp[0].entry; ;}
    break;

  case 36:
#line 272 "pascal.y"
    {
				if (yyvsp[0].entry != NULL)
				{
					yyvsp[0].entry->flag = yyvsp[0].entry->type;
					yyvsp[0].entry->type = ENTRY_POINTER;
					yyval.entry = yyvsp[0].entry;
				}
				else yyval.entry = NULL;
			;}
    break;

  case 37:
#line 284 "pascal.y"
    {
				yyval.entry = scalar_alloc(yyvsp[-1].queue);
			;}
    break;

  case 38:
#line 290 "pascal.y"
    { 
				yyval.entry = subrange_alloc(yyvsp[-2].expr, yyvsp[0].expr); 
			;}
    break;

  case 39:
#line 297 "pascal.y"
    { yyval.entry = yyvsp[0].entry; ;}
    break;

  case 40:
#line 299 "pascal.y"
    { yyval.entry = yyvsp[0].entry; ;}
    break;

  case 41:
#line 304 "pascal.y"
    {
				if (yyvsp[0].entry != NULL)
				{
					yyval.entry = array_alloc(yyvsp[0].entry, yyvsp[-3].queue);
				}
				else
				{
					queue_free_content(yyvsp[-3].queue);
					queue_free(yyvsp[-3].queue);
					yyval.entry = NULL;
				}
			;}
    break;

  case 42:
#line 319 "pascal.y"
    {
				if (yyvsp[0].entry != NULL)
				{
					enqueue(yyvsp[-2].queue, (char*)yyvsp[0].entry);
				}
				yyval.queue = yyvsp[-2].queue;
			;}
    break;

  case 43:
#line 327 "pascal.y"
    {
				yyval.queue = queue_alloc();
				if (yyvsp[0].entry != NULL)
				{
					enqueue(yyval.queue, (char *)yyvsp[0].entry);
				}
			;}
    break;

  case 44:
#line 337 "pascal.y"
    {
				stack_push(record_stack, 0);
				recstack_push();
			;}
    break;

  case 45:
#line 342 "pascal.y"
    {
				yyval.entry = record_alloc(recstack_pop());
				stack_pop(record_stack);
			;}
    break;

  case 51:
#line 358 "pascal.y"
    {
				int offset = stack_pop(record_stack);
				char *name;
				for (;;)
				{
					name = dequeue(yyvsp[-2].queue);
					if (name == NULL) break;
					table_append(recstack, 
						field_alloc(yyvsp[0].entry, name, offset));
					offset += yyvsp[0].entry->size;
				}
				queue_free(yyvsp[-2].queue);
				stack_push(record_stack, offset);
			;}
    break;

  case 52:
#line 375 "pascal.y"
    {
				int offset = stack_pop(record_stack);
				if (yyvsp[-1].entry->type != ENTRY_ATOMIC &&
					yyvsp[-1].entry->type != ENTRY_SUBRANGE &&
					yyvsp[-1].entry->type != ENTRY_SCALAR)
				{
					ERROR("Invalid type.\n");
				}
				table_append(recstack,
					field_alloc(yyvsp[-1].entry, yyvsp[-3].text, offset));
				offset += yyvsp[-1].entry->size;
				stack_push(record_stack, offset);
				INFO("VARIANT\n");
			;}
    break;

  case 56:
#line 397 "pascal.y"
    { 
				expression_t *e;
				while (!stack_empty(yyvsp[-2].stack))
				{
					e = (expression_t *)stack_pop(yyvsp[-2].stack);
					expr_free(e);
				}
				stack_free(yyvsp[-2].stack);
				stack_push(record_stack, stack_top(record_stack)); 
			;}
    break;

  case 57:
#line 408 "pascal.y"
    {
				stack_pop(record_stack);
			;}
    break;

  case 59:
#line 416 "pascal.y"
    { 
				INFO("K_VAR\n");
			;}
    break;

  case 63:
#line 427 "pascal.y"
    {
				char *name;
				int i;
				i = stack_pop(record_stack);
				for (;;)
				{
					name = dequeue(yyvsp[-3].queue);
					if (name == NULL) break;
					i -= yyvsp[-1].entry->size;
				STACK_APPEND(variable_alloc(yyvsp[-1].entry, name,i));
				}
				queue_free(yyvsp[-3].queue);
				stack_push(record_stack, i);
				INFO("variable of type %s\n", yyvsp[-1].entry->name);
			;}
    break;

  case 64:
#line 445 "pascal.y"
    {
				entry_t *e;
				INFO("FUNCTION BEGIN %s\n", yyvsp[0].entry->name);
				STACK_APPEND(yyvsp[0].entry);
				INFO("A\n");
				STACK_PUSH;
				INFO("B\n");
				if (yyvsp[0].entry->a.procedure.rtype != NULL)
				{
					INFO("C\n");
					STACK_APPEND(
					variable_alloc(
					yyvsp[0].entry->a.procedure.rtype,
					strdup(make_ret_name(yyvsp[0].entry->name)),
					-yyvsp[0].entry->a.procedure.rtype->size));
					stack_push(record_stack,
						-yyvsp[0].entry->a.procedure.rtype->size);
				}
				else stack_push(record_stack, 0);
				INFO("D\n");
				if (yyvsp[0].entry->a.procedure.param == NULL)
					e = NULL;
				else
					e = yyvsp[0].entry->a.procedure.param->entries;
				INFO("BEGIN WHILE\n");
				while (e != NULL)
				{
					STACK_APPEND(entry_copy(e));
					e = e->next;
				}
				INFO("END WHILE\n");
				stack_push(proc_stack, (int)yyvsp[0].entry->name);		
				stack_push(proc_stack, yyvsp[0].entry->a.procedure.psize);
				stack_push(proc_stack, yyvsp[0].entry->a.procedure.id);
			;}
    break;

  case 65:
#line 481 "pascal.y"
    {
				if (yyvsp[-2].entry->a.procedure.rtype != NULL)
				{
					EMIT(OP_RET, STACK_ARG(0,
					-yyvsp[-2].entry->a.procedure.rtype->size),
					CONST_ARG(yyvsp[-2].entry->a.procedure.rtype->size),
					NULL_ARG);
				}
				EMIT(OP_ENDP, NULL_ARG, NULL_ARG, NULL_ARG);
				STACK_POP;
				INFO("FUNCTION END\n");
			;}
    break;

  case 67:
#line 496 "pascal.y"
    {
				yyvsp[-2].entry->a.procedure.id = 0;
				STACK_APPEND(yyvsp[-2].entry);
				append_string(yyvsp[-2].entry->name);
				enqueue(external, strdup(yyvsp[-2].entry->name));
			;}
    break;

  case 68:
#line 505 "pascal.y"
    {
				yyval.integer = PROCEDURE_CDECL;
			;}
    break;

  case 69:
#line 509 "pascal.y"
    {
				yyval.integer = PROCEDURE_PASCAL;
			;}
    break;

  case 70:
#line 513 "pascal.y"
    {
				yyval.integer = PROCEDURE_PASCAL;
			;}
    break;

  case 71:
#line 520 "pascal.y"
    {
				yyval.entry = proc_alloc(yyvsp[-2].text, NULL, NULL, yyvsp[0].integer, 0);
			;}
    break;

  case 72:
#line 525 "pascal.y"
    {
				INFO("ENTER\n");
				yyval.entry = proc_alloc(yyvsp[-5].text, NULL, recstack_pop(), yyvsp[0].integer,
					stack_pop(record_stack));
				INFO("EXIT\n");
			;}
    break;

  case 73:
#line 533 "pascal.y"
    {
				yyval.entry = proc_alloc(yyvsp[-4].text, yyvsp[-2].entry, NULL, yyvsp[0].integer, 0);
			;}
    break;

  case 74:
#line 538 "pascal.y"
    {
				yyval.entry = proc_alloc(yyvsp[-7].text, yyvsp[-2].entry, recstack_pop(), yyvsp[0].integer,
					stack_pop(record_stack));
			;}
    break;

  case 76:
#line 546 "pascal.y"
    {
				recstack_push();
				stack_push(record_stack, machine_state_size);
			;}
    break;

  case 78:
#line 554 "pascal.y"
    {
				entry_t *e;
				char *name;
				int offset;
				if (yyvsp[0].entry != NULL)
				{
					offset = stack_pop(record_stack);
					for (;;)
					{
						name = dequeue(yyvsp[-2].queue);
						if (name == NULL) break;
						e = param_alloc(yyvsp[0].entry, name,
						offset, PARAM_BYVALUE);
						offset += (yyvsp[0].entry->size + 3)
							& (~(int)3);
						table_append(recstack, e);
					}
					stack_push(record_stack, offset);
				}
				queue_free(yyvsp[-2].queue);
			;}
    break;

  case 79:
#line 576 "pascal.y"
    {
				entry_t *e;
				char *name;
				int offset;
				if (yyvsp[0].entry != NULL)
				{
					offset= stack_pop(record_stack);
					for (;;)
					{
						name = dequeue(yyvsp[-2].queue);
						if (name == NULL) break;
						e = param_alloc(yyvsp[0].entry, name,
						offset, PARAM_BYREFERENCE);
						offset += 4;
						table_append(recstack, e);
					}
					stack_push(record_stack, offset);
				}
				queue_free(yyvsp[-2].queue);
			;}
    break;

  case 80:
#line 600 "pascal.y"
    {
				int l = new_label();
				EMIT_LABEL(l);
				yyval.expr = emit_variable(yyvsp[0].text);
				if (yyval.expr != NULL)
				{
					yyval.expr->label = l;
				}
			;}
    break;

  case 81:
#line 610 "pascal.y"
    {
				if (yyvsp[-3].expr != NULL && yyvsp[-1].stack != NULL)
				{
					int l = yyvsp[-3].expr->label;
					yyval.expr = emit_array_element(yyvsp[-3].expr, stack2queue(yyvsp[-1].stack));
					if (yyval.expr != NULL)
					{
						yyval.expr->label = l;
					}
				}
				else yyval.expr = NULL;
			;}
    break;

  case 82:
#line 623 "pascal.y"
    {
				if (yyvsp[-2].expr != NULL)
				{
					int l = yyvsp[-2].expr->label;
					yyval.expr = emit_record_field(yyvsp[-2].expr, yyvsp[0].text);
					if (yyval.expr != NULL)
					{
							yyval.expr->label = l;
					}
				}
				else yyval.expr = NULL;
			;}
    break;

  case 83:
#line 638 "pascal.y"
    {
					stack_push(yyvsp[-2].stack, (int)yyvsp[0].expr);
					yyval.stack = yyvsp[-2].stack;
			;}
    break;

  case 84:
#line 643 "pascal.y"
    {
				stack_t *s;
				s = stack_alloc();
				assert(yyvsp[0].expr != NULL);
				stack_push(s, (int)yyvsp[0].expr);
				yyval.stack = s;
			;}
    break;

  case 85:
#line 653 "pascal.y"
    {
				yyval.expr = yyvsp[0].expr;
			;}
    break;

  case 86:
#line 657 "pascal.y"
    {
				if (yyvsp[-2].expr != NULL && yyvsp[0].expr != NULL)
				{
					yyval.expr = emit_relop(yyvsp[-2].expr, yyvsp[0].expr, yyvsp[-1].integer);
				}
				else
				{
						if (yyvsp[-2].expr != NULL) expr_free(yyvsp[-2].expr);
						if (yyvsp[0].expr != NULL) expr_free(yyvsp[0].expr);
						yyval.expr = NULL;
				}
			;}
    break;

  case 87:
#line 671 "pascal.y"
    { yyval.integer = OP_JEQ; ;}
    break;

  case 88:
#line 672 "pascal.y"
    { yyval.integer = OP_JNE; ;}
    break;

  case 89:
#line 673 "pascal.y"
    { yyval.integer = OP_JGT; ;}
    break;

  case 90:
#line 674 "pascal.y"
    { yyval.integer = OP_JLT; ;}
    break;

  case 91:
#line 675 "pascal.y"
    { yyval.integer = OP_JGE; ;}
    break;

  case 92:
#line 676 "pascal.y"
    { yyval.integer = OP_JLE; ;}
    break;

  case 93:
#line 680 "pascal.y"
    {
				yyval.expr = yyvsp[0].expr;
			;}
    break;

  case 94:
#line 684 "pascal.y"
    {
				if (yyvsp[-2].expr != NULL && yyvsp[0].expr != NULL)
				{
					yyval.expr = emit_plus(yyvsp[-2].expr, yyvsp[0].expr);
				}
				else
				{
						expr_free(yyvsp[-2].expr);
						expr_free(yyvsp[0].expr);
						yyval.expr = NULL;
				}
			;}
    break;

  case 95:
#line 697 "pascal.y"
    {
				if (yyvsp[-2].expr != NULL && yyvsp[0].expr != NULL)
				{
					yyval.expr = emit_minus(yyvsp[-2].expr, yyvsp[0].expr);
				}
				else
				{
						expr_free(yyvsp[-2].expr);
						expr_free(yyvsp[0].expr);
						yyval.expr = NULL;
				}
			;}
    break;

  case 96:
#line 710 "pascal.y"
    {
				if (yyvsp[-2].expr != NULL && yyvsp[0].expr != NULL)
				{
					yyval.expr = emit_or(yyvsp[-2].expr, yyvsp[0].expr);
				}
				else
				{
						expr_free(yyvsp[-2].expr);
						expr_free(yyvsp[0].expr);
						yyval.expr = NULL;
				}
			;}
    break;

  case 97:
#line 725 "pascal.y"
    {
				yyval.expr = yyvsp[0].expr;
			;}
    break;

  case 98:
#line 729 "pascal.y"
    {
				if (yyvsp[-2].expr != NULL && yyvsp[0].expr != NULL)
				{
					yyval.expr = emit_times(yyvsp[-2].expr, yyvsp[0].expr);
				}
				else
				{
						expr_free(yyvsp[-2].expr);
						expr_free(yyvsp[0].expr);
						yyval.expr = NULL;
				}
			;}
    break;

  case 99:
#line 742 "pascal.y"
    {
				if (yyvsp[-2].expr != NULL && yyvsp[0].expr != NULL)
				{
					yyval.expr = emit_divide(yyvsp[-2].expr, yyvsp[0].expr);
				}
				else
				{
						expr_free(yyvsp[-2].expr);
						expr_free(yyvsp[0].expr);
						yyval.expr = NULL;
				}
			;}
    break;

  case 100:
#line 755 "pascal.y"
    {
				if (yyvsp[-2].expr != NULL && yyvsp[0].expr != NULL)
				{
					yyval.expr = emit_div(yyvsp[-2].expr, yyvsp[0].expr);
				}
				else
				{
						expr_free(yyvsp[-2].expr);
						expr_free(yyvsp[0].expr);
						yyval.expr = NULL;
				}
			;}
    break;

  case 101:
#line 768 "pascal.y"
    {
				if (yyvsp[-2].expr != NULL && yyvsp[0].expr != NULL)
				{
					yyval.expr = emit_mod(yyvsp[-2].expr, yyvsp[0].expr);
				}
				else
				{
						expr_free(yyvsp[-2].expr);
						expr_free(yyvsp[0].expr);
						yyval.expr = NULL;
				}
			;}
    break;

  case 102:
#line 781 "pascal.y"
    {
				if (yyvsp[-2].expr != NULL && yyvsp[0].expr != NULL)
				{
					yyval.expr = emit_and(yyvsp[-2].expr, yyvsp[0].expr);
				}
				else
				{
						expr_free(yyvsp[-2].expr);
						expr_free(yyvsp[0].expr);
						yyval.expr = NULL;
				}
			;}
    break;

  case 103:
#line 796 "pascal.y"
    {
				yyval.expr = yyvsp[0].expr;
			;}
    break;

  case 104:
#line 800 "pascal.y"
    {
				yyval.expr = make_int_expr(yyvsp[0].integer);
			;}
    break;

  case 105:
#line 804 "pascal.y"
    {
				if (strlen(yyvsp[0].text) == 1)
				{
					yyval.expr = make_char_expr(*yyvsp[0].text);
					free(yyvsp[0].text);
				}
				else
				{
					yyval.expr = make_string_expr(yyvsp[0].text);
				}
			;}
    break;

  case 106:
#line 816 "pascal.y"
    {
				yyval.expr = yyvsp[-1].expr;
			;}
    break;

  case 107:
#line 820 "pascal.y"
    {
				yyval.expr = emit_invoke(yyvsp[-3].text, yyvsp[-1].stack);
				if (yyval.expr == NULL)
				{
					ERROR("Error invoking function.\n");
				}
			;}
    break;

  case 108:
#line 828 "pascal.y"
    {
					yyval.expr = yyvsp[0].expr;
			;}
    break;

  case 109:
#line 832 "pascal.y"
    {
					yyval.expr = emit_neg(yyvsp[0].expr);
			;}
    break;

  case 110:
#line 836 "pascal.y"
    {
				yyval.expr = emit_not(yyvsp[0].expr);
			;}
    break;

  case 111:
#line 840 "pascal.y"
    {
				yyval.expr = NULL;
				ERROR("Set not supported.\n");
			;}
    break;

  case 112:
#line 845 "pascal.y"
    {
				yyval.expr = emit_true();
			;}
    break;

  case 113:
#line 849 "pascal.y"
    {
				yyval.expr = emit_false();
			;}
    break;

  case 118:
#line 862 "pascal.y"
    {
				INFO("STATEMENT\n");
			;}
    break;

  case 119:
#line 866 "pascal.y"
    {
				emit_label(yyvsp[0].text);
			;}
    break;

  case 121:
#line 871 "pascal.y"
    {
					yyok = 0;
			;}
    break;

  case 122:
#line 877 "pascal.y"
    {
				emit_assign(yyvsp[-2].expr, yyvsp[0].expr);
			;}
    break;

  case 123:
#line 881 "pascal.y"
    {
				emit_read(yyvsp[-1].stack, 0);
			;}
    break;

  case 124:
#line 885 "pascal.y"
    {
				emit_read(NULL, 1);
			;}
    break;

  case 125:
#line 889 "pascal.y"
    {
				emit_read(yyvsp[-1].stack, 1);
			;}
    break;

  case 126:
#line 893 "pascal.y"
    {
				emit_write(yyvsp[-1].stack, 0);
			;}
    break;

  case 127:
#line 897 "pascal.y"
    {
				emit_write(yyvsp[-1].stack, 1);
			;}
    break;

  case 128:
#line 901 "pascal.y"
    {
				expression_t *e;
				e = emit_invoke(yyvsp[-3].text, yyvsp[-1].stack);
				if (e != NULL) expr_free(e);
			;}
    break;

  case 129:
#line 907 "pascal.y"
    {
				expression_t *e;
				e = emit_invoke(yyvsp[0].text, NULL);
				if (e != NULL) expr_free(e);
			;}
    break;

  case 130:
#line 913 "pascal.y"
    {
				emit_goto(yyvsp[0].text);
			;}
    break;

  case 131:
#line 917 "pascal.y"
    {
				yyvsp[-1].expr = make_bool(yyvsp[-1].expr);
				if ((yyvsp[-1].expr == NULL) || (yyvsp[-1].expr->type != bool_entry) 
					|| (yyvsp[-1].expr->flag != EXPR_BOOL))
				{

					ERROR("invalid branch condition.\n");
					expr_free(yyvsp[-1].expr);
					yyvsp[-1].expr = NULL;
				}
				else
				{
					int label = new_label();
					EMIT_LABEL(label);
					if (yyvsp[-1].expr->true_list != NULL)
					{
					patch_label(yyvsp[-1].expr->true_list, label);
					}
					
				}
			;}
    break;

  case 132:
#line 939 "pascal.y"
    {
				stack_push(proc_stack, (int)yyvsp[-3].expr);
			;}
    break;

  case 134:
#line 944 "pascal.y"
    {
				ERROR("Case statement supported.\n");
			;}
    break;

  case 135:
#line 948 "pascal.y"
    {
				int l = new_label();
				stack_push(record_stack, l);
				EMIT_LABEL(l);
			;}
    break;

  case 136:
#line 954 "pascal.y"
    {
				int l = new_label();
				yyvsp[0].expr = make_bool(yyvsp[0].expr);
				patch_label(yyvsp[0].expr->true_list, l);
				EMIT_LABEL(l);
			;}
    break;

  case 137:
#line 961 "pascal.y"
    {
				int l = new_label();			
				EMIT(OP_JMP, LABEL_ARG(stack_pop(record_stack)),
							NULL_ARG, NULL_ARG);
				patch_label(yyvsp[-3].expr->false_list, l);
				EMIT_LABEL(l);
				expr_free(yyvsp[-3].expr);
			;}
    break;

  case 138:
#line 970 "pascal.y"
    {
				int l = new_label();
				stack_push(record_stack, l);
				EMIT_LABEL(l);
			;}
    break;

  case 139:
#line 976 "pascal.y"
    {
				int l = new_label();
				yyvsp[0].expr = make_bool(yyvsp[0].expr);
				patch_label(yyvsp[0].expr->false_list,
						stack_pop(record_stack));
				patch_label(yyvsp[0].expr->true_list, l);
				EMIT_LABEL(l);
				expr_free(yyvsp[0].expr);
			;}
    break;

  case 140:
#line 986 "pascal.y"
    {
				int l = new_label();
				int m = new_label();
				emit_assign(expr_copy(yyvsp[-5].expr), yyvsp[-3].expr);
				EMIT_LABEL(l);
				yyvsp[-3].expr = emit_relop(expr_copy(yyvsp[-5].expr), yyvsp[-1].expr, OP_JLE);	
				EMIT_LABEL(m);
				patch_label(yyvsp[-3].expr->true_list, m);
				yyvsp[-1].expr = (expression_t *)l;
			;}
    break;

  case 141:
#line 997 "pascal.y"
    {
				int l = new_label();
				expression_t *e = make_int_expr(1);
				emit_assign(yyvsp[-7].expr, emit_plus(expr_copy(yyvsp[-7].expr), e));
				EMIT(OP_JMP, LABEL_ARG((int)yyvsp[-3].expr), NULL_ARG,
						NULL_ARG);
				EMIT_LABEL(l);
				patch_label(yyvsp[-5].expr->false_list, l);
				expr_free(yyvsp[-5].expr);
			;}
    break;

  case 142:
#line 1008 "pascal.y"
    {
				int l = new_label();
				int m = new_label();
				emit_assign(expr_copy(yyvsp[-5].expr), yyvsp[-3].expr);
				EMIT_LABEL(l);
				yyvsp[-3].expr = emit_relop(expr_copy(yyvsp[-5].expr), yyvsp[-1].expr, OP_JGE);	
				EMIT_LABEL(m);
				patch_label(yyvsp[-3].expr->true_list, m);
				yyvsp[-1].expr = (expression_t *)l;
			;}
    break;

  case 143:
#line 1019 "pascal.y"
    {
				int l = new_label();
				expression_t *e = make_int_expr(1);
				emit_assign(yyvsp[-7].expr, emit_minus(expr_copy(yyvsp[-7].expr), e));
				EMIT(OP_JMP, LABEL_ARG((int)yyvsp[-3].expr), NULL_ARG,
						NULL_ARG);
				EMIT_LABEL(l);
				patch_label(yyvsp[-5].expr->false_list, l);
				expr_free(yyvsp[-5].expr);
			;}
    break;

  case 144:
#line 1030 "pascal.y"
    {
				ERROR("With statement not supported.\n");
			;}
    break;

  case 146:
#line 1037 "pascal.y"
    {
				int label = new_label();
				expression_t *c = (expression_t *)stack_pop(proc_stack);
				stack_push(record_stack, label);
				EMIT(OP_JMP, LABEL_ARG(label), NULL_ARG,
						NULL_ARG);
				if (c != NULL && c->false_list != NULL)
				{
					label = new_label();
					EMIT_LABEL(label);
					patch_label(c->false_list, label);
				}
				expr_free(c);
			;}
    break;

  case 147:
#line 1052 "pascal.y"
    {
				EMIT_LABEL(stack_pop(record_stack));
			;}
    break;

  case 148:
#line 1056 "pascal.y"
    {
				int label;
				expression_t *c = (expression_t *)stack_pop(proc_stack);
				if (c != NULL && c->false_list != NULL)
				{
					label = new_label();
					EMIT_LABEL(label);
					patch_label(c->false_list, label);
				}
				expr_free(c);				
			;}
    break;

  case 149:
#line 1070 "pascal.y"
    {
				INFO("BEGIN\n");
			;}
    break;

  case 150:
#line 1074 "pascal.y"
    {
				INFO("END\n");
			;}
    break;

  case 159:
#line 1097 "pascal.y"
    {
				assert(0);
			;}
    break;

  case 160:
#line 1103 "pascal.y"
    {
				enqueue(yyvsp[-2].queue, yyvsp[0].text);
				yyval.queue = yyvsp[-2].queue;
			;}
    break;

  case 161:
#line 1108 "pascal.y"
    {
				queue_t *tmp = queue_alloc();
				enqueue(tmp, yyvsp[0].text);
				yyval.queue = tmp;
				INFO("%s\n", yyvsp[0].text);
			;}
    break;


    }

/* Line 999 of yacc.c.  */
#line 2666 "pascal.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("syntax error, unexpected ") + 1;
	  yysize += yystrlen (yytname[yytype]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 1116 "pascal.y"


extern char *yytext;
int yyerror (char *msg)
{
	ERROR("%s near `%s\'\n", msg, yytext);
	return 0;
}


