%{
#include <argus.h>
#include "sql.tab.h"

static char *yytext2string (char *s)
{
	char *t;
	s++;
	t = s;
	while (*t != 0) t++;
	t--;
	*t = 0;
	return strdup(s);
}
%}

%option noyywrap

DIGIT [0-9]
ALPHA [a-zA-Z]

%%
and				return K_AND;
as				return K_AS;
by				return K_BY;
count				return K_COUNT;
every				return K_EVERY;
false				return K_FALSE;
from				return K_FROM;
group				return K_GROUP;
having				return K_HAVING;
hour				return K_HOUR;
hours				return K_HOUR;
minute				return K_MINUTE;
minutes				return K_MINUTE;
order				return K_ORDER;
preceding 			return K_PRECEDING;
row				return K_ROW;
rows				return K_ROW;
second				return K_SECOND;
seconds				return K_SECOND;
select				return K_SELECT;
top				return K_TOP;
true				return K_TRUE;
where				return K_WHERE;
"*"				return K_ASTERISK;
","				return K_COMMA;
"."				return K_PERIOD;
[_a-zA-Z][_a-zA-Z0-9]*		sqllval.text = strdup(sqltext); return K_ID;
[0-9]+				sqllval.int_value = atoi(sqltext); return K_INTEGER;
[0-9]+\.[0-9]+			sqllval.float_value = (float)atof(sqltext); return K_FLOAT;
'[^\']*'			sqllval.text = yytext2string(sqltext); return K_STRING;
"="				sqllval.int_value = CMP_EQU; return K_CMP;
">"				sqllval.int_value = CMP_GT; return K_CMP;
"<"				sqllval.int_value = CMP_LT; return K_CMP;
">="				sqllval.int_value = CMP_GE; return K_CMP;
"<="				sqllval.int_value = CMP_LE; return K_CMP;
"!="				sqllval.int_value = CMP_NE; return K_CMP;
"<>"				sqllval.int_value = CMP_NE; return K_CMP;
"("				return K_LP;
")"				return K_RP;
"+"				return K_ADD;
"-"				return K_SUB;
"/"				return K_DIV;
[ \t\n]

%%

