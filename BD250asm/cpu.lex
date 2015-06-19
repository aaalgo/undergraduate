%{
#include <stdio.h>
#include <string.h>
#include "cpu_tab.h"
extern int nline;
%}


%option noyywrap

%%

NOP	return OP_NOP;
ADD	yylval.value = 0x4000; return OP_ALU;
ADDC	yylval.value = 0x4200; return OP_ALU;
SUB	yylval.value = 0x4400; return OP_ALU;
SUBC	yylval.value = 0x4600; return OP_ALU;
NOT	yylval.value = 0x5000; return OP_SALU;
SHL	yylval.value = 0x5400; return OP_SALU;
SHLC	yylval.value = 0x5600; return OP_SALU;
SHR	yylval.value = 0x5800; return OP_SALU;
SHRC	yylval.value = 0x5A00; return OP_SALU;
AND	yylval.value = 0x4800; return OP_ALU;
OR	yylval.value = 0x4C00; return OP_ALU;
ADDI	yylval.value = 0x6000; return OP_ALU;
ADDIC	yylval.value = 0x6200; return OP_ALU;
SUBI	yylval.value = 0x6400; return OP_ALU;
SUBIC	yylval.value = 0x6600; return OP_ALU;
ANDI	yylval.value = 0x6800; return OP_ALU;
ORI	yylval.value = 0x6C00; return OP_ALU;
LOAD	return OP_LOAD;
STORE	return OP_STORE;
LACC	return OP_LACC;
CONST	return OP_CONST;
JZ	return OP_JZ;
JMP	return OP_JMP;
JACC	return OP_JACC;
JZACC	return OP_JZACC;
END	return END;
"."	return DOT;
":"	return COL;
";"	{
		int c;
		for (;;)
		{
			c = input();
			if (c == '\n') break;
			if (c == EOF)
			{
				fprintf(stderr, "Line %d : EOF in comment.\n", nline);
				break;
			}
		}
		nline++;
		return SEM;
	}
"="	return EQU;
[0-9]+	sscanf(yytext, "%d", &yylval.value); return INT;
0x[0-9A-Z]+	sscanf(yytext+2, "%x", &yylval.value);	return INT;
[_a-zA-Z][_0-9a-zA-Z]*	yylval.text = strdup(yytext); return LABEL;
\n	nline++;
[ \t]

%%

