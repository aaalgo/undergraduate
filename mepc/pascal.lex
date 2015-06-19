/* filename: pascal.lex
   by Dong Wei */
%{
#include <ctype.h>
#include "pascal.h"
#include "pascal.tab.h"

void pas_str_preproc (char *s)
{
	char *t = s;
	for (;;)
	{
		if (*s == 0) break;
		if (*s == '\'')
		{
			s++;
			assert(*s == '\'');
		}
		*t = *s;
		t++;
		s++;
	}
	*t = 0;
}

void lowercase (char *s)
{
		while (*s)
		{
				*s = tolower(*s);
				s++;
		}
}
%}

%s BINARY
%option noyywrap

%%
and		BEGIN(0); return K_AND;
array		return K_ARRAY;
begin		return K_BEGIN;
case		return K_CASE;
cdecl		return K_CDECL;
const		return K_CONST;
div		BEGIN(0); return K_DIV;
do		return K_DO;
downto		return K_DOWNTO;
else		return K_ELSE;
end		return K_END;
external	return K_EXTERNEL;
false		BEGIN(BINARY); return K_FALSE;
for		return K_FOR;
function	return K_FUNCTION;
goto		return K_GOTO;
if		return K_IF;
in		return K_IN;
not		BEGIN(0); return K_NOT;
of		return K_OF;
or		BEGIN(0); return K_OR;
label		return K_LABEL;
mod		BEGIN(0); return K_MOD;
nil		BEGIN(BINARY); return K_NIL;
packed		return K_PACKED;
procedure	return K_PROCEDURE;
program		return K_PROGRAM;
record		return K_RECORD;
repeat		return K_REPEAT;
set		return K_SET;
then		return K_THEN;
to		return K_TO;
true		BEGIN(BINARY); return K_TRUE;
type		return K_TYPE;
until		return K_UNTIL;
var		return K_VAR;
while		return K_WHILE;
with		return K_WITH;
write		return K_WRITE;
writeln		return K_WRITELN;
read		return K_READ;
readln		return K_READLN;
xor		BEGIN(0); return K_XOR;

"{"		{
			int c;
			for (;;)
			{
				c = input();
				if (c == '}') break;
				if (c == EOF)
				{
					fprintf(stderr, "EOF in comment.\n");
					break;	
				}
			}
		}
"#"		{
			int c;
			for (;;)
			{
					c = input();
					if (c == '\n') break;
					if (c == EOF)
					{
							fprintf(stderr, "EOF in comment.\n");
							break;
					}
			}
#ifndef NONSTDCOMMONT
			fprintf(stderr, "Warning!!!Line %d: non-standard comment format.\n", yyline);
#endif
		}
"^"		return CARET;
,		BEGIN(0); return COMMA;
"/"		BEGIN(0); return DIVIDE;
".."		BEGIN(0); return DOTDOT;
"<>"		BEGIN(0); return NE;
">="		BEGIN(0); return GE;
">"		BEGIN(0); return GT;
":="	BEGIN(0); return IS;
=		BEGIN(0); return EQUALS;
":"		return COLON;
@		return AT;
"["		return LBRACKET;
"("		return LPAREN;
"<="		BEGIN(0); return LE;
"<"		BEGIN(0); return LT;
<BINARY>"-"	BEGIN(0); return MINUS;
"-"		return NEG;
"."		return PERIOD;
<BINARY>"+"	BEGIN(0); return PLUS;
"+"		return POS;
"]"		BEGIN(BINARY); return RBRACKET;
")"		BEGIN(BINARY); return RPAREN;
;		BEGIN(0); return SCOLON;
"*"		BEGIN(0); return TIMES;
\n		yyline++;
[_a-zA-Z]([_0-9a-zA-Z])* BEGIN(BINARY); { if (tolowercase){lowercase(yytext);} char *t = strdup(yytext); entry_t *e = STACK_LOOKUP(yytext, NULL); if (e != NULL && e->type == ENTRY_PROCEDURE && e->a.procedure.rtype != NULL) {	char c;	for (;;) { c = input();	if (c != ' ' && c != '\t' && c != '\n') break; } unput(c); if (c != ':') { yylval.text = t; return IDENTIFIER; } else {yylval.text = strdup(make_ret_name(t)); free(t); return IDENTIFIER; } }	else { yylval.text = t; return IDENTIFIER;	} }
'([^\']|\'\')*' BEGIN(BINARY); yylval.text = strdup(yytext + 1); yylval.text[strlen(yylval.text)-1] = 0; pas_str_preproc(yylval.text); return STRING;
[0-9]+		BEGIN(BINARY); yylval.integer = atoi(yytext); return INTEGER;
[0-9]+(\.[0-9]+)?((E|e)[0-9]+)?	BEGIN(BINARY); yylval.real = atof(yytext); return REAL;
[\ \t]

%%
