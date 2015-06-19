/* filename: main.c
   by Dong Wei */
#include "pascal.h"

int main (int argc, char *argv[])
{
	INFO("initing...\n");
	parse_args(argc, argv);
	if (file_in == NULL)
		file_in = strdup("hello.p");
	if (file_out == NULL)
		file_out = strdup("hello.asm");
	O++;
	pre_parse();
	if (file_in == NULL)
	{
		yyin = stdin;
	}
	else
	{
		yyin = fopen(file_in, "r");
		if (yyin == NULL)
		{
			perror(file_in);
			exit(-1);
		}
	}
	INFO("calling yyparse...\n");
	yyparse();
	INFO("returned from yyparse...\n");
	fclose(yyin);	
	if (yyok)
	{
		int i;
		for (i = 0; i < O; i++)
		{
			optimize();
		}
		md_optimize();
		if (file_out == NULL) output = stdout;
		else
		{
			output = fopen(file_out, "w");
			if (output == NULL)
			{
				fprintf(stderr, "Error opening output file.\n");
				cleanup();
				exit(-1);
			}
		}
		codegen();
		fclose(output);
	}
	cleanup();
	return !yyok;
}

