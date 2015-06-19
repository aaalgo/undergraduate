%{
#include <stdio.h>
#include <stdlib.h>
#define MAXSYM 256
#define MAXINST 1024

#define alloca(n) _alloca(n)

struct sym
{
	char *name;
	unsigned short value;
};

struct sym syms[MAXSYM];
int nsym;

struct inst
{
	char *addr;
	unsigned short value;
};

struct inst inst[MAXINST];
int ninst;

int ok;
int nline;

int add_sym (char *name, int value)
{
	int i, c;
	i = nsym;
	for (;;)
	{
		if (i == 0) break;
		c = strcmp(syms[i-1].name, name);
		if (c == 0)
		{
			fprintf(stderr, "Label %s already defined.\n", name);
			free(name);
			ok = 0;
			return -1;
		}
		if (c < 0) break;
		syms[i] = syms[i-1];
		i--;
	}
	syms[i].name = name;
	syms[i].value = value;
	nsym++;
	return 0;	
}


%}

%union {
	int value;
	char *text;
}

%token <value>OP_ALU
%token <value>OP_SALU
%token COL
%token SEM
%token END
%token DOT
%token EQU
%token <value>INT
%token <text>LABEL

%%

program		: END DOT
	 	| line program
		;

line		:instruction {ninst++;} SEM
      		| LABEL COL
		{
			add_sym($1, ninst);
		}
		instruction {ninst++;} SEM
		| LABEL EQU INT SEM
		{
			add_sym($1, $3);
		}

instruction	: OP_SALU
		{
			inst[ninst].value |= $1; 
		}
		| OP_ALU	addr
		{
			inst[ninst].value |= $1;
		}
		;

addr		: LABEL
      		{
			inst[ninst].addr = $1;
		}
      		| INT
		{
			inst[ninst].value |= $1;
		}
		;

%%

int yyerror (char *msg)
{
	fprintf(stderr, "Line %d : %s\n", nline, msg);
	ok = 0;
	return 0;
}

FILE *yyinput;

int main (int argc, char *argv[])
{
	int i, j;
	FILE *fout;
	yyinput = stdin;
	if (argc == 2)
	{
		yyinput = fopen(argv[1], "r");
		if (yyinput == NULL)
		{
			fprintf(stderr, "Cannot open file %s for input.\n", argv[1]);
			return 0;
		}
	}
	ninst = 0;
	nsym = 0;
	ok = 1;
	nline = 0;
	memset(inst, 0, sizeof inst);
	yyparse();
	for (i = 0; i < ninst; i++)
		if (inst[i].addr != NULL)
		{
			for (j = 0; j < nsym; j++)
				if (strcmp(syms[j].name, inst[i].addr) == 0) break;
			if (j >= nsym)
			{
				fprintf(stderr, "Symbol %s not found.\n", inst[i].addr);
				ok = 0;
			}
			else
			{
				inst[i].value |= syms[j].value;
			}
			free(inst[i].addr);
		}
	if (ninst > 0xff)
	{
		fprintf(stderr, "Program too large.\n");
	}
	if (ok)
	{
		fout = fopen("rom.mif", "w");
		fprintf(fout, "DEPTH\t=\t256\n");
		fprintf(fout, "WIDTH\t=\t16\n");
		fprintf(fout, "ADDRESS_RADIX\t=\tHEX\n");
		fprintf(fout, "DATA_RADIX\t=\tHEX\n");
		fprintf(fout, "CONTENT\tBEGIN\n");
		for (i = 0; i < ninst; i++)
			fprintf(fout, "\t%4X\t: %04X;\n", i, inst[i].value);
		if (ninst < 0xff)
		{
			fprintf(fout, "\t[%d..FF]\t: 0000;\n", ninst);
		}
		fprintf(fout, "END\n");
		fclose(fout);
	}
	return 0;	
}

