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
/* Line 1240 of yacc.c.  */
#line 202 "pascal.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



